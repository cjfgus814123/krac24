#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <krac_interfaces/msg/target_error.hpp> // 정확한 경로
#include <std_srvs/srv/set_bool.hpp>
#include <algorithm>
#include <cmath>
#include <chrono> // std::chrono_literals를 위해 필수

using namespace std::chrono_literals;

class PrecisionLander : public rclcpp::Node {
public:
    PrecisionLander() : Node("precision_lander_node") {
        vel_pub_ = this->create_publisher<geometry_msgs::msg::Twist>("/mavros/setpoint_velocity/cmd_vel_unstamped", 10);
        vision_sub_ = this->create_subscription<krac_interfaces::msg::TargetError>("/vision/target_error", 10, std::bind(&PrecisionLander::vision_cb, this, std::placeholders::_1));
        pose_sub_ = this->create_subscription<geometry_msgs::msg::PoseStamped>("/mavros/local_position/pose", 10, std::bind(&PrecisionLander::pose_cb, this, std::placeholders::_1));
        
        enable_srv_ = this->create_service<std_srvs::srv::SetBool>("precision_lander/enable", std::bind(&PrecisionLander::enable_cb, this, std::placeholders::_1, std::placeholders::_2));
        timer_ = this->create_wall_timer(50ms, std::bind(&PrecisionLander::control_loop, this));
        RCLCPP_INFO(this->get_logger(), "Precision Lander Node Initialized. Waiting for Enable Service...");
    }

private:
    bool is_enabled_ = false;
    double current_alt_ = 5.0;
    krac_interfaces::msg::TargetError vision_err_;
    
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr vel_pub_;
    rclcpp::Subscription<krac_interfaces::msg::TargetError>::SharedPtr vision_sub_;
    rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr pose_sub_;
    rclcpp::Service<std_srvs::srv::SetBool>::SharedPtr enable_srv_;
    rclcpp::TimerBase::SharedPtr timer_;

    // PID gains
    const double KP_XY = 0.5, KI_XY = 0.05, KD_XY = 0.1;
    double sum_x_ = 0.0, sum_y_ = 0.0, prev_err_x_ = 0.0, prev_err_y_ = 0.0;
    const double fx_ = 720.0, fy_ = 720.0; // 1024 해상도 대응 초점거리

    void pose_cb(const geometry_msgs::msg::PoseStamped::SharedPtr msg) { current_alt_ = msg->pose.position.z; }
    void vision_cb(const krac_interfaces::msg::TargetError::SharedPtr msg) { vision_err_ = *msg; }
    void enable_cb(const std::shared_ptr<std_srvs::srv::SetBool::Request> req, 
                   std::shared_ptr<std_srvs::srv::SetBool::Response> res) {
        is_enabled_ = req->data;
        res->success = true;
        RCLCPP_INFO(this->get_logger(), "Precision Lander State: %s", is_enabled_ ? "ON" : "OFF");
    }

    void control_loop() {
        if (!is_enabled_ || !vision_err_.is_detected) {
            sum_x_ = 0.0; sum_y_ = 0.0;
            vel_pub_->publish(geometry_msgs::msg::Twist());
            return;
        }

        double err_x_m = vision_err_.pixel_err_x * (current_alt_ / fx_);
        double err_y_m = vision_err_.pixel_err_y * (current_alt_ / fy_);

        sum_x_ = std::clamp(sum_x_ + err_x_m * 0.05, -1.0, 1.0);
        sum_y_ = std::clamp(sum_y_ + err_y_m * 0.05, -1.0, 1.0);

        double v_x = (KP_XY * err_x_m) + (KI_XY * sum_x_) + (KD_XY * (err_x_m - prev_err_x_) / 0.05);
        double v_y = (KP_XY * err_y_m) + (KI_XY * sum_y_) + (KD_XY * (err_y_m - prev_err_y_) / 0.05);

        prev_err_x_ = err_x_m; prev_err_y_ = err_y_m;

        geometry_msgs::msg::Twist cmd;
        cmd.linear.x = std::clamp(v_x, -1.0, 1.0);
        cmd.linear.y = std::clamp(v_y, -1.0, 1.0);
        
        // 동적 하강: 정렬되었을 때만 하강
        cmd.linear.z = (std::hypot(err_x_m, err_y_m) < 0.2) ? -0.2 : 0.0;
        
        vel_pub_->publish(cmd);
    }
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<PrecisionLander>());
    rclcpp::shutdown();
    return 0;
}
