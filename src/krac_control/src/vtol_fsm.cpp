#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <geometry_msgs/msg/point.hpp>
#include <mavros_msgs/msg/state.hpp>
#include <mavros_msgs/msg/waypoint_reached.hpp>
#include <mavros_msgs/srv/set_mode.hpp>
#include <mavros_msgs/srv/waypoint_set_current.hpp>
#include <std_srvs/srv/trigger.hpp>
#include <std_msgs/msg/string.hpp>
#include <std_msgs/msg/bool.hpp>
#include <krac_interfaces/msg/target_error.hpp> 

#include <chrono>
#include <algorithm>
#include <cmath>

using namespace std::chrono_literals;

// FSM 상태 정의
enum MissionPhase {
    PHASE_MISSION_FLYING = 0,
    PHASE_VISION_ALIGN_RESCUE = 1,
    PHASE_LANDING_AND_GRAB = 2,
    PHASE_ASCEND_WITH_VICTIM = 3,
    PHASE_RESUME_MISSION = 4,
    PHASE_VISION_ALIGN_LAND = 5,
    PHASE_FINAL_LANDING = 6
};

class RescueMissionNode : public rclcpp::Node {
public:
    RescueMissionNode() : Node("rescue_mission_node") {
        auto qos = rclcpp::SensorDataQoS();
        last_vision_time_ = rclcpp::Time(0, 0, this->get_clock()->get_clock_type()); // 초기화

        // 파라미터 선언
        this->declare_parameter("rescue_wp_seq", 7);
        this->declare_parameter("resume_wp_seq", 8);
        this->declare_parameter("landing_wp_seq", 14);
        this->declare_parameter("safe_ascend_alt", 15.0);

        rescue_wp_seq_ = this->get_parameter("rescue_wp_seq").as_int();
        resume_wp_seq_ = this->get_parameter("resume_wp_seq").as_int();
        landing_wp_seq_ = this->get_parameter("landing_wp_seq").as_int();
        safe_ascend_alt_ = this->get_parameter("safe_ascend_alt").as_double();

        // 구독 및 발행
        state_sub_ = this->create_subscription<mavros_msgs::msg::State>(
            "mavros/state", qos, std::bind(&RescueMissionNode::state_cb, this, std::placeholders::_1));
        mission_reached_sub_ = this->create_subscription<mavros_msgs::msg::WaypointReached>(
            "mavros/mission/reached", 10, std::bind(&RescueMissionNode::mission_reached_cb, this, std::placeholders::_1));
        local_pose_sub_ = this->create_subscription<geometry_msgs::msg::PoseStamped>(
            "mavros/local_position/pose", qos, std::bind(&RescueMissionNode::local_pose_cb, this, std::placeholders::_1));
        vision_error_sub_ = this->create_subscription<geometry_msgs::msg::Point>(
            "camera/target_error", 10, std::bind(&RescueMissionNode::vision_cb, this, std::placeholders::_1));

        vel_setpoint_pub_ = this->create_publisher<geometry_msgs::msg::Twist>("mavros/setpoint_velocity/cmd_vel_unstamped", 10);
        target_label_pub_ = this->create_publisher<std_msgs::msg::String>("camera/set_target", 10);
        vision_enable_pub_ = this->create_publisher<std_msgs::msg::Bool>("camera/enable", 10);

        set_mode_client_ = this->create_client<mavros_msgs::srv::SetMode>("mavros/set_mode");
        set_mission_current_client_ = this->create_client<mavros_msgs::srv::WaypointSetCurrent>("mavros/mission/set_current");
        manual_trigger_server_ = this->create_service<std_srvs::srv::Trigger>(
            "cmd/mission_proceed", std::bind(&RescueMissionNode::manual_proceed_cb, this, std::placeholders::_1, std::placeholders::_2));

        timer_ = this->create_wall_timer(50ms, std::bind(&RescueMissionNode::control_loop, this));
        
        control_vision_node(false); // 초기 비전 OFF
        RCLCPP_INFO(this->get_logger(), "FSM Node Started.");
    }

private:
    MissionPhase current_phase_ = PHASE_MISSION_FLYING;
    int rescue_wp_seq_, resume_wp_seq_, landing_wp_seq_;
    double safe_ascend_alt_;
    bool offboard_enabled_ = false;
    bool manual_ok_ = false;
    
    mavros_msgs::msg::State current_state_;
    geometry_msgs::msg::PoseStamped current_local_pose_;
    geometry_msgs::msg::Point vision_error_;
    rclcpp::Time last_vision_time_;

    // 💡 매크로 대신 클래스 상수로 깔끔하게 정의
    const double VISION_P_GAIN = 0.005; 
    const double DESCEND_SPEED = -0.3;  
    const double MAX_ALIGN_SPEED = 0.5;

    rclcpp::Subscription<mavros_msgs::msg::State>::SharedPtr state_sub_;
    rclcpp::Subscription<mavros_msgs::msg::WaypointReached>::SharedPtr mission_reached_sub_;
    rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr local_pose_sub_;
    rclcpp::Subscription<geometry_msgs::msg::Point>::SharedPtr vision_error_sub_;

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr vel_setpoint_pub_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr target_label_pub_;
    rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr vision_enable_pub_;

    rclcpp::Client<mavros_msgs::srv::SetMode>::SharedPtr set_mode_client_;
    rclcpp::Client<mavros_msgs::srv::WaypointSetCurrent>::SharedPtr set_mission_current_client_;
    rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr manual_trigger_server_;
    rclcpp::TimerBase::SharedPtr timer_;

    // 콜백 함수들
    void state_cb(const mavros_msgs::msg::State::SharedPtr msg) { current_state_ = *msg; }
    void local_pose_cb(const geometry_msgs::msg::PoseStamped::SharedPtr msg) { current_local_pose_ = *msg; }
    
    void vision_cb(const geometry_msgs::msg::Point::SharedPtr msg) { 
        vision_error_ = *msg; 
        if(msg->z > 0.5) last_vision_time_ = this->now(); 
    }

    void manual_proceed_cb(const std::shared_ptr<std_srvs::srv::Trigger::Request>, std::shared_ptr<std_srvs::srv::Trigger::Response> res) {
        manual_ok_ = true;
        res->success = true;
        RCLCPP_INFO(this->get_logger(), "✅ Manual Trigger Received!");
    }

    void control_vision_node(bool enable, std::string target = "") {
        std_msgs::msg::Bool msg; msg.data = enable; vision_enable_pub_->publish(msg);
        if (enable) {
            std_msgs::msg::String t; t.data = target; target_label_pub_->publish(t);
        }
    }

    void switch_to_offboard() {
        auto req = std::make_shared<mavros_msgs::srv::SetMode::Request>();
        req->custom_mode = "OFFBOARD";
        set_mode_client_->async_send_request(req);
        offboard_enabled_ = true;
    }

    void mission_reached_cb(const mavros_msgs::msg::WaypointReached::SharedPtr msg) {
        if (current_phase_ != PHASE_MISSION_FLYING) return;

        if (msg->wp_seq == rescue_wp_seq_) {
            RCLCPP_WARN(this->get_logger(), "🚨 Rescue WP Reached! Switching to OFFBOARD.");
            switch_to_offboard();
            control_vision_node(true, "basket");
            current_phase_ = PHASE_VISION_ALIGN_RESCUE;
        } else if (msg->wp_seq == landing_wp_seq_) {
            RCLCPP_WARN(this->get_logger(), "🛬 Landing WP Reached! Switching to OFFBOARD.");
            switch_to_offboard();
            control_vision_node(true, "vertiport");
            current_phase_ = PHASE_VISION_ALIGN_LAND;
        }
    }

    // 💡 에러의 원인이었던 clamp_velocity 함수 추가!
    double clamp_velocity(double vel) {
        return std::clamp(vel, -MAX_ALIGN_SPEED, MAX_ALIGN_SPEED);
    }

    void control_loop() {
        if (!offboard_enabled_) return;

        // OFFBOARD 모드 유지 안전장치
        if (current_state_.mode != "OFFBOARD" && current_phase_ != PHASE_FINAL_LANDING) {
            switch_to_offboard();
        }

        geometry_msgs::msg::Twist vel_cmd;
        
        // 💡 에러의 원인이었던 object_detected 지역 변수 정의 추가! (최근 0.5초 이내에 봤는지 확인)
        bool object_detected = false;
        if (last_vision_time_.nanoseconds() > 0) {
            double elapsed = (this->now() - last_vision_time_).seconds();
            if (elapsed < 0.5) object_detected = true;
        }

        switch (current_phase_) {
            case PHASE_MISSION_FLYING:
                break;

            // ==========================================
            // [1] 조난자 구조 로직 (WP 7)
            // ==========================================
            case PHASE_VISION_ALIGN_RESCUE:
                if (object_detected) {
                    double dist_pixel = std::sqrt(vision_error_.x * vision_error_.x + vision_error_.y * vision_error_.y);
                    
                    vel_cmd.linear.x = clamp_velocity(-vision_error_.y * VISION_P_GAIN);
                    vel_cmd.linear.y = clamp_velocity(vision_error_.x * VISION_P_GAIN);
                    vel_cmd.angular.z = 0.0;
                    
                    if (dist_pixel < 40.0) vel_cmd.linear.z = DESCEND_SPEED;
                    else vel_cmd.linear.z = 0.0;

                    if (current_local_pose_.pose.position.z < 0.5) {
                        RCLCPP_INFO(this->get_logger(), "Near Target. Ready to Grab.");
                        current_phase_ = PHASE_LANDING_AND_GRAB;
                    }
                } else {
                    vel_cmd.linear.x = 0.0; vel_cmd.linear.y = 0.0; vel_cmd.linear.z = 0.0;
                }
                break;

            case PHASE_LANDING_AND_GRAB:
                vel_cmd.linear.z = -0.5; 
                if (manual_ok_) {
                    RCLCPP_INFO(this->get_logger(), "Victim Grabbed! Ascending...");
                    manual_ok_ = false;
                    current_phase_ = PHASE_ASCEND_WITH_VICTIM;
                }
                break;

            case PHASE_ASCEND_WITH_VICTIM:
                vel_cmd.linear.x = 0.0; vel_cmd.linear.y = 0.0;
                vel_cmd.linear.z = 1.5; 
                
                if (current_local_pose_.pose.position.z >= safe_ascend_alt_) {
                    control_vision_node(false); 
                    RCLCPP_INFO(this->get_logger(), "Ascent Complete. Jumping to WP %d", resume_wp_seq_);
                    current_phase_ = PHASE_RESUME_MISSION;
                }
                break;

            case PHASE_RESUME_MISSION:
                {
                    auto wp_req = std::make_shared<mavros_msgs::srv::WaypointSetCurrent::Request>();
                    wp_req->wp_seq = resume_wp_seq_;
                    set_mission_current_client_->async_send_request(wp_req);

                    auto mode_req = std::make_shared<mavros_msgs::srv::SetMode::Request>();
                    mode_req->custom_mode = "AUTO.MISSION";
                    set_mode_client_->async_send_request(mode_req);
                    
                    offboard_enabled_ = false;
                    current_phase_ = PHASE_MISSION_FLYING;
                }
                break;

            // ==========================================
            // [2] 버티포트 정밀 착륙 로직 (WP 14)
            // ==========================================
            case PHASE_VISION_ALIGN_LAND:
                if (object_detected) {
                    double dist_pixel = std::sqrt(vision_error_.x * vision_error_.x + vision_error_.y * vision_error_.y);
                    
                    vel_cmd.linear.x = clamp_velocity(-vision_error_.y * VISION_P_GAIN);
                    vel_cmd.linear.y = clamp_velocity(vision_error_.x * VISION_P_GAIN);
                    
                    if (dist_pixel < 30.0) vel_cmd.linear.z = DESCEND_SPEED;
                    else vel_cmd.linear.z = -0.1; 

                    if (current_local_pose_.pose.position.z < 0.3) {
                        RCLCPP_INFO(this->get_logger(), "Landed on Vertiport. Engaging AUTO.LAND for disarm.");
                        control_vision_node(false);
                        current_phase_ = PHASE_FINAL_LANDING;
                    }
                } else {
                    vel_cmd.linear.z = -0.2; 
                }
                break;

            case PHASE_FINAL_LANDING:
                {
                    auto req = std::make_shared<mavros_msgs::srv::SetMode::Request>();
                    req->custom_mode = "AUTO.LAND";
                    set_mode_client_->async_send_request(req);
                    offboard_enabled_ = false;
                }
                break;
                
            // 💡 Enum 경고 방지를 위한 default 케이스 추가
            default:
                break;
        }

        if (offboard_enabled_) {
            vel_setpoint_pub_->publish(vel_cmd);
        }
    }
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<RescueMissionNode>());
    rclcpp::shutdown();
    return 0;
}
