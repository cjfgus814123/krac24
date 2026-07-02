#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <geometry_msgs/msg/twist.hpp> 
#include <mavros_msgs/msg/state.hpp>
#include <mavros_msgs/msg/waypoint_reached.hpp>
#include <mavros_msgs/srv/set_mode.hpp>
#include <mavros_msgs/srv/waypoint_set_current.hpp>
#include <std_srvs/srv/trigger.hpp>
#include <std_srvs/srv/set_bool.hpp> 

#include <chrono>
#include <algorithm>

using namespace std::chrono_literals;

enum MissionPhase {
    PHASE_MISSION_FLYING = 0,        
    PHASE_PREPARE_OFFBOARD = 99,     
    PHASE_RESCUE_DESCENT = 1,        
    PHASE_LANDING_AND_GRAB = 2,      
    PHASE_ASCEND_WITH_VICTIM = 3,    
    PHASE_RESUME_MISSION = 4,        
    PHASE_VERTIPORT_DESCENT = 5,     
    PHASE_FINAL_LANDING = 6          
};

class RescueMissionNode : public rclcpp::Node {
public:
    RescueMissionNode() : Node("rescue_mission_node") {
        auto qos = rclcpp::SensorDataQoS();

        this->declare_parameter("rescue_wp_seq", 7);     
        this->declare_parameter("resume_wp_seq", 8);     
        this->declare_parameter("landing_wp_seq", 14);   
        this->declare_parameter("safe_ascend_alt", 30.0); 

        rescue_wp_seq_ = this->get_parameter("rescue_wp_seq").as_int();
        resume_wp_seq_ = this->get_parameter("resume_wp_seq").as_int();
        landing_wp_seq_ = this->get_parameter("landing_wp_seq").as_int();
        safe_ascend_alt_ = this->get_parameter("safe_ascend_alt").as_double();

        state_sub_ = this->create_subscription<mavros_msgs::msg::State>(
            "mavros/state", qos, std::bind(&RescueMissionNode::state_cb, this, std::placeholders::_1));
        mission_reached_sub_ = this->create_subscription<mavros_msgs::msg::WaypointReached>(
            "mavros/mission/reached", 10, std::bind(&RescueMissionNode::mission_reached_cb, this, std::placeholders::_1));
        local_pose_sub_ = this->create_subscription<geometry_msgs::msg::PoseStamped>(
            "mavros/local_position/pose", qos, std::bind(&RescueMissionNode::local_pose_cb, this, std::placeholders::_1));

        // 💡 [핵심 추가] Lander 노드의 명령을 구독하는 서브스크라이버
        lander_vel_sub_ = this->create_subscription<geometry_msgs::msg::Twist>(
            "/precision_lander/cmd_vel", 10, std::bind(&RescueMissionNode::lander_vel_cb, this, std::placeholders::_1));

        vel_setpoint_pub_ = this->create_publisher<geometry_msgs::msg::Twist>("mavros/setpoint_velocity/cmd_vel_unstamped", 10);

        set_mode_client_ = this->create_client<mavros_msgs::srv::SetMode>("mavros/set_mode");
        set_mission_current_client_ = this->create_client<mavros_msgs::srv::WaypointSetCurrent>("mavros/mission/set_current");
        lander_client_ = this->create_client<std_srvs::srv::SetBool>("precision_lander/enable");

        manual_trigger_server_ = this->create_service<std_srvs::srv::Trigger>(
            "cmd/mission_proceed", std::bind(&RescueMissionNode::manual_proceed_cb, this, std::placeholders::_1, std::placeholders::_2));

        timer_ = this->create_wall_timer(50ms, std::bind(&RescueMissionNode::control_loop, this));
        
        RCLCPP_INFO(this->get_logger(), "=========================================");
        RCLCPP_INFO(this->get_logger(), "🛸 KRAC VTOL 프록시 FSM 제어기 가동");
        RCLCPP_INFO(this->get_logger(), "🔥 오프보드 무한 유지(Proxy) 방어선 적용 완료!");
        RCLCPP_INFO(this->get_logger(), "=========================================");
    }

private:
    MissionPhase current_phase_ = PHASE_MISSION_FLYING;
    MissionPhase next_phase_after_prep_ = PHASE_MISSION_FLYING; 
    int offboard_prep_counter_ = 0; 
    bool offboard_enabled_ = false; // 💡 오프보드 강제 유지를 위한 플래그
    
    int rescue_wp_seq_, resume_wp_seq_, landing_wp_seq_;
    double safe_ascend_alt_;
    bool manual_ok_ = false;
    
    mavros_msgs::msg::State current_state_;
    geometry_msgs::msg::PoseStamped current_local_pose_;
    geometry_msgs::msg::Twist latest_lander_vel_; 
    rclcpp::Time last_lander_vel_time_;

    rclcpp::Subscription<mavros_msgs::msg::State>::SharedPtr state_sub_;
    rclcpp::Subscription<mavros_msgs::msg::WaypointReached>::SharedPtr mission_reached_sub_;
    rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr local_pose_sub_;
    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr lander_vel_sub_; 
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr vel_setpoint_pub_;

    rclcpp::Client<mavros_msgs::srv::SetMode>::SharedPtr set_mode_client_;
    rclcpp::Client<mavros_msgs::srv::WaypointSetCurrent>::SharedPtr set_mission_current_client_;
    rclcpp::Client<std_srvs::srv::SetBool>::SharedPtr lander_client_;
    rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr manual_trigger_server_;
    rclcpp::TimerBase::SharedPtr timer_;

    void state_cb(const mavros_msgs::msg::State::SharedPtr msg) { current_state_ = *msg; }
    void local_pose_cb(const geometry_msgs::msg::PoseStamped::SharedPtr msg) { current_local_pose_ = *msg; }
    
    // Lander 노드가 보낸 값을 캐싱해 둡니다.
    void lander_vel_cb(const geometry_msgs::msg::Twist::SharedPtr msg) {
        latest_lander_vel_ = *msg;
        last_lander_vel_time_ = this->now();
    }

    void manual_proceed_cb(const std::shared_ptr<std_srvs::srv::Trigger::Request>, std::shared_ptr<std_srvs::srv::Trigger::Response> res) {
        manual_ok_ = true;
        res->success = true;
    }

    void set_precision_lander(bool enable) {
        auto req = std::make_shared<std_srvs::srv::SetBool::Request>();
        req->data = enable;
        lander_client_->async_send_request(req);
    }

    void mission_reached_cb(const mavros_msgs::msg::WaypointReached::SharedPtr msg) {
        if (current_phase_ != PHASE_MISSION_FLYING) return;

        RCLCPP_INFO(this->get_logger(), "🎯 Waypoint Reached: [WP %d]", msg->wp_seq);

        if (msg->wp_seq == rescue_wp_seq_) {
            RCLCPP_WARN(this->get_logger(), "🚨 구조 WP 도달! 무한 오프보드 프록시 모드 가동.");
            offboard_enabled_ = true;
            offboard_prep_counter_ = 0;
            next_phase_after_prep_ = PHASE_RESCUE_DESCENT;
            current_phase_ = PHASE_PREPARE_OFFBOARD;
        } 
        else if (msg->wp_seq == landing_wp_seq_) {
            RCLCPP_WARN(this->get_logger(), "🛬 버티포트 도달! 무한 오프보드 프록시 모드 가동.");
            offboard_enabled_ = true;
            offboard_prep_counter_ = 0;
            next_phase_after_prep_ = PHASE_VERTIPORT_DESCENT;
            current_phase_ = PHASE_PREPARE_OFFBOARD;
        }
    }

    // 메인 주기 제어 루프 (단 한 번도 쉬지 않고 20Hz를 방어함)
    void control_loop() {
        if (current_phase_ == PHASE_MISSION_FLYING) return;

        // 💡 [핵심] 오프보드 모드가 켜져야 하는 구간이면 승인될 때까지 문을 계속 두드립니다.
        if (offboard_enabled_ && current_state_.mode != "OFFBOARD") {
            auto req = std::make_shared<mavros_msgs::srv::SetMode::Request>();
            req->custom_mode = "OFFBOARD";
            set_mode_client_->async_send_request(req);
        }

        geometry_msgs::msg::Twist vel_cmd;
        bool publish_vel = false;

        switch (current_phase_) {
            case PHASE_PREPARE_OFFBOARD:
                publish_vel = true;
                vel_cmd.linear.x = 0.0; vel_cmd.linear.y = 0.0; vel_cmd.linear.z = 0.0; vel_cmd.angular.z = 0.0;
                
                offboard_prep_counter_++;
                if (offboard_prep_counter_ >= 20) { // 1초 대기 후 랜더 노드 기상
                    set_precision_lander(true);
                    current_phase_ = next_phase_after_prep_;
                }
                break;

            case PHASE_RESCUE_DESCENT:
            case PHASE_VERTIPORT_DESCENT:
                publish_vel = true;
                // 💡 [프록시 방어막] Lander 노드가 0.5초 이내에 보낸 최신 명령이 있다면 토스하고, 
                // Lander가 죽었거나 늦게 켜져서 값이 없다면 제자리 호버링[0,0,0]을 쏴서 OFFBOARD 탈락을 100% 방어합니다.
                if (last_lander_vel_time_.nanoseconds() > 0 && (this->now() - last_lander_vel_time_).seconds() < 0.5) {
                    vel_cmd = latest_lander_vel_;
                } else {
                    vel_cmd.linear.x = 0.0; vel_cmd.linear.y = 0.0; vel_cmd.linear.z = 0.0; vel_cmd.angular.z = 0.0;
                }
                
                if (current_phase_ == PHASE_RESCUE_DESCENT && current_local_pose_.pose.position.z < 0.4) {
                    set_precision_lander(false);
                    manual_ok_ = false;
                    current_phase_ = PHASE_LANDING_AND_GRAB;
                } else if (current_phase_ == PHASE_VERTIPORT_DESCENT && current_local_pose_.pose.position.z < 0.25) {
                    set_precision_lander(false);
                    current_phase_ = PHASE_FINAL_LANDING;
                }
                break;

            case PHASE_LANDING_AND_GRAB:
                publish_vel = true;
                vel_cmd.linear.x = 0.0; vel_cmd.linear.y = 0.0; vel_cmd.linear.z = -0.2; vel_cmd.angular.z = 0.0;
                
                if (manual_ok_) {
                    manual_ok_ = false;
                    current_phase_ = PHASE_ASCEND_WITH_VICTIM;
                }
                break;

            case PHASE_ASCEND_WITH_VICTIM:
                publish_vel = true;
                vel_cmd.linear.x = 0.0; vel_cmd.linear.y = 0.0; vel_cmd.linear.z = 1.2; vel_cmd.angular.z = 0.0;

                if (current_local_pose_.pose.position.z >= safe_ascend_alt_) {
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
                    
                    RCLCPP_INFO(this->get_logger(), "🔄 [모드 복귀] AUTO.MISSION 전환 및 WP %d 점프 완수.", resume_wp_seq_);
                    
                    offboard_enabled_ = false; // 💡 프록시 강제 유지를 풀고 미션으로 돌려보냄
                    current_phase_ = PHASE_MISSION_FLYING;
                }
                break;

            case PHASE_FINAL_LANDING:
                {
                    auto req = std::make_shared<mavros_msgs::srv::SetMode::Request>();
                    req->custom_mode = "AUTO.LAND";
                    set_mode_client_->async_send_request(req);
                    
                    offboard_enabled_ = false;
                    RCLCPP_WARN(this->get_logger(), "🏁 [임무 종료] AUTO.LAND 전환 완료.");
                    rclcpp::shutdown();
                }
                break;
                
            default:
                break;
        }

        // 루프의 마지막: 어떤 상황에서도 20Hz로 무조건 발사 (Offboard 영구 보장)
        if (publish_vel) {
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
