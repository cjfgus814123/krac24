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
        pose_sub_ = this->create_subscription<geometry_msgs::msg::PoseStamped>("/mavros/local_position/pose", 10, std::bind(&PrecisionLander::pose_cb, this, std::placeholders::_1));
        
        enable_srv_ = this->create_service<std_srvs::srv::SetBool>("/precision_lander/enable", std::bind(&PrecisionLander::enable_cb, this, std::placeholders::_1, std::placeholders::_2));
        timer_ = this->create_wall_timer(50ms, std::bind(&PrecisionLander::control_loop, this));

        RCLCPP_INFO(this->get_logger(), "Precision Lander Ready (Standby Mode).");
    }

private:
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr vel_pub_;
    rclcpp::Subscription<krac_interfaces::msg::TargetError>::SharedPtr vision_sub_;
    rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr pose_sub_;
    rclcpp::Service<std_srvs::srv::SetBool>::SharedPtr enable_srv_;
    rclcpp::TimerBase::SharedPtr timer_;

    krac_interfaces::msg::TargetError vision_err_;
    double current_alt_ = 5.0; // 초기 안전 고도
    bool is_enabled_ = false;  // 초기 상태는 OFF

    // PID 제어 관련 변수
    double fx_ = 1092.2, fy_ = 1093.4; // 카메라 초점거리 (수정 필요)
    double sum_x_ = 0.0, sum_y_ = 0.0;
    double prev_err_x_ = 0.0, prev_err_y_ = 0.0;
    
    // PID 게인
    const double KP_XY = 0.8, KI_XY = 0.01, KD_XY = 0.1;
    const double KP_YAW = 0.5; // OBB 회전 제어 게인
    const double DESCEND_SPEED = -0.3; // 하강 속도

    void vision_cb(const krac_interfaces::msg::TargetError::SharedPtr msg) { vision_err_ = *msg; }
    void pose_cb(const geometry_msgs::msg::PoseStamped::SharedPtr msg) { current_alt_ = msg->pose.position.z; }

    void enable_cb(const std::shared_ptr<std_srvs::srv::SetBool::Request> req, 
                   std::shared_ptr<std_srvs::srv::SetBool::Response> res) {
        is_enabled_ = req->data;
        res->success = true;
        // 상태가 바뀔 때 적분항 초기화
        sum_x_ = 0.0; sum_y_ = 0.0; 
        RCLCPP_INFO(this->get_logger(), "Precision Lander State: %s", is_enabled_ ? "ON" : "OFF");
    }

    void control_loop() {
        if (!is_enabled_) return; // 💡 켜져 있지 않으면 아무것도 안함 (FSM이 알아서 조종함)

        geometry_msgs::msg::Twist vel_cmd;

        if (!vision_err_.is_detected) {
            // 타겟을 놓쳤을 경우 제자리 호버링
            vel_pub_->publish(vel_cmd); 
            return;
        }

        // 1. 카메라 픽셀 오차를 실제 물리 거리(m)로 스케일링
        double err_x_m = vision_err_.pixel_err_x * (current_alt_ / fx_);
        double err_y_m = vision_err_.pixel_err_y * (current_alt_ / fy_);

        // 2. I 제어 누적 및 안티 와인드업
        sum_x_ = std::clamp(sum_x_ + err_x_m * 0.05, -1.0, 1.0);
        sum_y_ = std::clamp(sum_y_ + err_y_m * 0.05, -1.0, 1.0);

        // 3. PID 속도 계산 (화면 중심 오차 기반)
        double v_x = (KP_XY * err_x_m) + (KI_XY * sum_x_) + (KD_XY * (err_x_m - prev_err_x_) / 0.05);
        double v_y = (KP_XY * err_y_m) + (KI_XY * sum_y_) + (KD_XY * (err_y_m - prev_err_y_) / 0.05);

        // 이전 값 갱신
        prev_err_x_ = err_x_m; prev_err_y_ = err_y_m;

        // 속도 제한 매핑 (전후/좌우 방향 주의)
        vel_cmd.linear.x = std::clamp(-v_y, -0.5, 0.5); // 이미지가 위로 치우치면 기체는 앞으로 전진
        vel_cmd.linear.y = std::clamp(v_x, -0.5, 0.5);  // 이미지가 우로 치우치면 기체는 우로 이동
        
        // 4. OBB 기반 Yaw 정렬 제어
        vel_cmd.angular.z = std::clamp(vision_err_.yaw_err_rad * KP_YAW, -0.3, 0.3);

        // 5. 오차가 좁혀졌을 때만 하강
        double dist_m = std::hypot(err_x_m, err_y_m);
        if (dist_m < 0.3) { // 30cm 이내로 들어오면 하강
            vel_cmd.linear.z = DESCEND_SPEED;
        } else {
            vel_cmd.linear.z = 0.0; // 멀면 고도 유지
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
