#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <krac_interfaces/msg/target_error.hpp> // 커스텀 메시지
#include <std_srvs/srv/set_bool.hpp>
#include <algorithm>
#include <cmath>
#include <chrono>

using namespace std::chrono_literals;

class PrecisionLander : public rclcpp::Node {
public:
    PrecisionLander() : Node("precision_lander_node") {
        vel_pub_ = this->create_publisher<geometry_msgs::msg::Twist>("/precision_lander/cmd_vel", 10);
        vision_sub_ = this->create_subscription<krac_interfaces::msg::TargetError>("/vision/target_error", 10, std::bind(&PrecisionLander::vision_cb, this, std::placeholders::_1));
        
        auto qos = rclcpp::SensorDataQoS();
        pose_sub_ = this->create_subscription<geometry_msgs::msg::PoseStamped>(
            "/mavros/local_position/pose", qos, std::bind(&PrecisionLander::pose_cb, this, std::placeholders::_1));
        
        enable_srv_ = this->create_service<std_srvs::srv::SetBool>("/precision_lander/enable", std::bind(&PrecisionLander::enable_cb, this, std::placeholders::_1, std::placeholders::_2));
        timer_ = this->create_wall_timer(50ms, std::bind(&PrecisionLander::control_loop, this));

        RCLCPP_INFO(this->get_logger(), "🛬 정밀 착륙(Precision Lander) 노드 가동 완료! (Yaw 정렬 포함)");
    }

private:
    bool enabled_ = false;
    krac_interfaces::msg::TargetError vision_err_;
    double current_alt_ = 0.0;

    // 실제 카메라 캘리브레이션을 1024x1024 해상도 비율로 변환한 값
    const double fx_ = 582.5; 
    const double fy_ = 1036.7;

    // PID 제어기 변수
    double prev_err_x_ = 0.0;
    double prev_err_y_ = 0.0;
    double sum_x_ = 0.0;
    double sum_y_ = 0.0;

    // 튜닝 파라미터
    const double KP_XY = 0.5;   
    const double KI_XY = 0.01;
    const double KD_XY = 0.1;
    const double MAX_XY_VEL = 1.0; 
    
    // 💡 [추가] 헤딩(Yaw) 정렬 파라미터
    const double KP_YAW = 0.6;         // 회전 민감도 (P 게인)
    const double MAX_YAW_VEL = 0.4;    // 최대 회전 속도 (rad/s)

    // 고도 강하 파라미터
    const double SEARCH_ALTITUDE = 7.0;       // 타겟 탐색을 시작할 목표 고도 (7m)
    const double BLIND_DESCENT_SPEED = -1.5;  // 타겟 안 보일 때 빠르게 내려갈 속도
    const double PRECISION_DESCEND_SPEED = -0.4; // 타겟 보일 때 정밀 하강할 속도

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr vel_pub_;
    rclcpp::Subscription<krac_interfaces::msg::TargetError>::SharedPtr vision_sub_;
    rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr pose_sub_;
    rclcpp::Service<std_srvs::srv::SetBool>::SharedPtr enable_srv_;
    rclcpp::TimerBase::SharedPtr timer_;

    void vision_cb(const krac_interfaces::msg::TargetError::SharedPtr msg) {
        vision_err_ = *msg;
    }

    void pose_cb(const geometry_msgs::msg::PoseStamped::SharedPtr msg) {
        current_alt_ = msg->pose.position.z;
    }

    void enable_cb(const std_srvs::srv::SetBool::Request::SharedPtr req,
                   std_srvs::srv::SetBool::Response::SharedPtr res) {
        enabled_ = req->data;
        res->success = true;
        
        if (enabled_) {
            sum_x_ = 0.0; sum_y_ = 0.0;
            prev_err_x_ = 0.0; prev_err_y_ = 0.0;
            RCLCPP_INFO(this->get_logger(), "✅ Lander 상태: ON (하강 및 Yaw 제어 시작)");
        } else {
            RCLCPP_INFO(this->get_logger(), "⛔ Lander 상태: OFF");
        }
    }

    void control_loop() {
        if (!enabled_) return;

        geometry_msgs::msg::Twist vel_cmd;

        // =======================================================
        // 1. 타겟이 보이지 않을 때의 예외 처리 (블라인드 하강 로직)
        // =======================================================
        if (!vision_err_.is_detected) {
            vel_cmd.linear.x = 0.0;
            vel_cmd.linear.y = 0.0;
            vel_cmd.angular.z = 0.0;

            if (current_alt_ > SEARCH_ALTITUDE) {
                vel_cmd.linear.z = BLIND_DESCENT_SPEED;
                RCLCPP_INFO_THROTTLE(this->get_logger(), *this->get_clock(), 1000, 
                    "👀 [Target LOST] 고도 %.1fm -> %.1fm까지 블라인드 고속 하강 중...", current_alt_, SEARCH_ALTITUDE);
            } else {
                vel_cmd.linear.z = -0.1; 
                RCLCPP_WARN_THROTTLE(this->get_logger(), *this->get_clock(), 1000, 
                    "⚠️ [Target LOST] 탐색 고도(%.1fm) 진입. 타겟 수색 중...", current_alt_);
            }
            vel_pub_->publish(vel_cmd); 
            return;
        }

        // =======================================================
        // 🎯 2. 타겟이 감지되었을 때 (정밀 정렬 및 하강)
        // =======================================================
        double alt_factor = std::max(current_alt_, 0.5); // 0으로 나누기 방지
        double err_x_m = vision_err_.pixel_err_x * (alt_factor / fx_);
        double err_y_m = vision_err_.pixel_err_y * (alt_factor / fy_);

        // PID 제어 연산 (X, Y 위치)
        sum_x_ = std::clamp(sum_x_ + err_x_m * 0.05, -1.0, 1.0);
        sum_y_ = std::clamp(sum_y_ + err_y_m * 0.05, -1.0, 1.0);

        double v_x = (KP_XY * err_x_m) + (KI_XY * sum_x_) + (KD_XY * (err_x_m - prev_err_x_) / 0.05);
        double v_y = (KP_XY * err_y_m) + (KI_XY * sum_y_) + (KD_XY * (err_y_m - prev_err_y_) / 0.05);

        prev_err_x_ = err_x_m; 
        prev_err_y_ = err_y_m;

        // X, Y 이동 명령 인가
        vel_cmd.linear.x = std::clamp(v_y, -MAX_XY_VEL, MAX_XY_VEL);
        vel_cmd.linear.y = std::clamp(v_x, -MAX_XY_VEL, MAX_XY_VEL);

        // =======================================================
        // 🔄 3. OBB 기반 헤딩(Yaw) 정렬 제어
        // =======================================================
        // YOLO의 OBB theta를 0으로 만들도록 드론을 회전시킵니다.
        // 💡 [주의] 만약 드론이 정렬되지 않고 반대 방향으로 계속 뱅글뱅글 돈다면,
        // 아래 식에서 KP_YAW 앞에 마이너스(-) 부호를 붙여주시면 됩니다.
        double yaw_cmd = vision_err_.yaw_err_rad * KP_YAW;
        vel_cmd.angular.z = std::clamp(yaw_cmd, -MAX_YAW_VEL, MAX_YAW_VEL);

        // =======================================================
        // ⬇️ 4. 오차 반경에 따른 강하 속도 조절
        // =======================================================
        double dist_m = std::hypot(err_x_m, err_y_m);
        // 각도 오차도 로그 출력을 위해 디그리(도) 단위로 변환
        double yaw_deg = vision_err_.yaw_err_rad * (180.0 / M_PI);

        if (dist_m < 0.5) {
            vel_cmd.linear.z = PRECISION_DESCEND_SPEED; 
            RCLCPP_INFO_THROTTLE(this->get_logger(), *this->get_clock(), 1000, 
                "🎯 [Aligned] 정밀 하강 중 (오차: %.2fm, 각도: %.1f도, 고도: %.1fm)", dist_m, yaw_deg, current_alt_);
        } else if (dist_m < 1.5) {
            vel_cmd.linear.z = PRECISION_DESCEND_SPEED * 0.5;
            RCLCPP_INFO_THROTTLE(this->get_logger(), *this->get_clock(), 1000, 
                "↘️ [Approaching] 센터 진입 중... (각도 정렬: %.1f도)", yaw_deg);
        } else {
            vel_cmd.linear.z = 0.0;
            RCLCPP_INFO_THROTTLE(this->get_logger(), *this->get_clock(), 1000, 
                "🔄 [Aligning] X/Y/Yaw 오차 수정 중... (현재 오차: %.2fm)", dist_m);
        }

        vel_pub_->publish(vel_cmd);
    }
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<PrecisionLander>());
    rclcpp::shutdown();
    return 0;
}
