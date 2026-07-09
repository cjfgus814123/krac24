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

        RCLCPP_INFO(this->get_logger(), "🛬 정밀 착륙 가동! (오프셋 15cm 보정 및 동적 하강 로직 적용)");
    }

private:
    bool enabled_ = false;
    krac_interfaces::msg::TargetError vision_err_;
    double current_alt_ = 0.0;

    // 실제 카메라 캘리브레이션 비율 (1024x1024 해상도 기준)
    const double fx_ = 582.5; 
    const double fy_ = 1036.7;

    // 📍 카메라 오프셋 (단위: m) - 그리퍼(기체 중심)보다 카메라가 15cm 앞에 있음
    const double CAMERA_OFFSET_X = 0.15;
    const double CAMERA_OFFSET_Y = 0.0;

    // PID 제어기 변수
    double prev_err_x_ = 0.0;
    double prev_err_y_ = 0.0;
    double sum_x_ = 0.0;
    double sum_y_ = 0.0;

    const double KP_XY = 0.25;      
    const double KI_XY = 0.005;     
    const double KD_XY = 0.02;      
    const double MAX_XY_VEL = 0.5;  
    
    const double KP_YAW = 0.3;         
    const double MAX_YAW_VEL = 0.2;    

    const double SEARCH_ALTITUDE = 7.0;       
    const double BLIND_DESCENT_SPEED = -1.5;  

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
            RCLCPP_INFO(this->get_logger(), "✅ Lander 상태: ON (동적 하강 제어 시작)");
        } else {
            RCLCPP_INFO(this->get_logger(), "⛔ Lander 상태: OFF");
        }
    }

    void control_loop() {
        if (!enabled_) return;

        geometry_msgs::msg::Twist vel_cmd;

        // =======================================================
        // 1. 타겟이 보이지 않을 때의 예외 처리
        // =======================================================
        if (!vision_err_.is_detected) {
            vel_cmd.linear.x = 0.0;
            vel_cmd.linear.y = 0.0;
            vel_cmd.angular.z = 0.0;

            if (current_alt_ > SEARCH_ALTITUDE) {
                vel_cmd.linear.z = BLIND_DESCENT_SPEED;
                RCLCPP_INFO_THROTTLE(this->get_logger(), *this->get_clock(), 1000, 
                    "👀 [Target LOST] 고도 %.1fm -> %.1fm까지 고속 하강 중...", current_alt_, SEARCH_ALTITUDE);
            } else {
                vel_cmd.linear.z = -0.1; 
                RCLCPP_WARN_THROTTLE(this->get_logger(), *this->get_clock(), 1000, 
                    "⚠️ [Target LOST] 타겟 수색 중...");
            }
            vel_pub_->publish(vel_cmd); 
            return;
        }

        // =======================================================
        // 🎯 2. 타겟 감지 시 기체(그리퍼) 중심 기반 정밀 정렬
        // =======================================================
        double alt_factor = std::max(current_alt_, 0.5); 
        
        // 픽셀 오차 -> 물리 미터(m) 오차 변환
        double cam_err_x_m = vision_err_.pixel_err_x * (alt_factor / fx_);
        double cam_err_y_m = vision_err_.pixel_err_y * (alt_factor / fy_);

        // 카메라 오프셋(15cm)을 반영하여 그리퍼 기준 오차로 변환
        double body_err_x = -cam_err_y_m + CAMERA_OFFSET_X; 
        double body_err_y = cam_err_x_m + CAMERA_OFFSET_Y;

        sum_x_ = std::clamp(sum_x_ + body_err_x * 0.05, -1.0, 1.0);
        sum_y_ = std::clamp(sum_y_ + body_err_y * 0.05, -1.0, 1.0);

        double v_x = (KP_XY * body_err_x) + (KI_XY * sum_x_) + (KD_XY * (body_err_x - prev_err_x_) / 0.05);
        double v_y = (KP_XY * body_err_y) + (KI_XY * sum_y_) + (KD_XY * (body_err_y - prev_err_y_) / 0.05);

        prev_err_x_ = body_err_x; 
        prev_err_y_ = body_err_y;

        if (std::abs(body_err_x) < 0.1) v_x = 0.0;
        if (std::abs(body_err_y) < 0.1) v_y = 0.0;

        vel_cmd.linear.x = std::clamp(v_x, -MAX_XY_VEL, MAX_XY_VEL); 
        vel_cmd.linear.y = std::clamp(v_y, -MAX_XY_VEL, MAX_XY_VEL); 

        // =======================================================
        // 🔄 3. 헤딩(Yaw) 정렬
        // =======================================================
        double target_yaw_err = vision_err_.yaw_err_rad;
        while (target_yaw_err > M_PI / 2.0) target_yaw_err -= M_PI;
        while (target_yaw_err < -M_PI / 2.0) target_yaw_err += M_PI;

        double yaw_cmd = target_yaw_err * KP_YAW;
        if (std::abs(target_yaw_err) < 0.05) yaw_cmd = 0.0;
        vel_cmd.angular.z = std::clamp(yaw_cmd, -MAX_YAW_VEL, MAX_YAW_VEL);

        // =======================================================
        // ⬇️ 4. [NEW] 오차에 비례한 동적 하강(Dynamic Descent) 로직
        // =======================================================
        double dist_m = std::hypot(body_err_x, body_err_y);
        double yaw_deg = target_yaw_err * (180.0 / M_PI); 

        if (dist_m < 1.5) {
            // 그리퍼가 타겟과 0m 차이일 때 align_ratio = 1.0 (정중앙)
            // 1.5m 차이일 때 align_ratio = 0.0 (외곽)
            double align_ratio = std::clamp(1.0 - (dist_m / 1.5), 0.0, 1.0);
            
            // 비율에 따라 0.1 m/s (최소) ~ 0.6 m/s (최대) 사이에서 속도가 부드럽게 변함
            double dynamic_z_speed = 0.1 + (0.5 * align_ratio);
            
            // 아래로 내려가야 하므로 음수(-) 기호 부착
            vel_cmd.linear.z = -dynamic_z_speed; 

            if (dist_m < 0.2) {
                RCLCPP_INFO_THROTTLE(this->get_logger(), *this->get_clock(), 1000, 
                    "🎯 [Perfect Align] 쾌속 하강 중! (속도: %.2f m/s, 오차: %.2fm)", vel_cmd.linear.z, dist_m);
            } else {
                RCLCPP_INFO_THROTTLE(this->get_logger(), *this->get_clock(), 1000, 
                    "↘️ [Dynamic Descent] 동적 하강 중... (속도: %.2f m/s, 오차: %.2fm)", vel_cmd.linear.z, dist_m);
            }
        } else {
            // 거리가 1.5m 이상이면 X, Y 이동에 집중하기 위해 Z축 하강을 멈춤
            vel_cmd.linear.z = 0.0;
            RCLCPP_INFO_THROTTLE(this->get_logger(), *this->get_clock(), 1000, 
                "🔄 [Aligning] 하강 정지, 수평 정렬 집중... (현재 오차: %.2fm)", dist_m);
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
