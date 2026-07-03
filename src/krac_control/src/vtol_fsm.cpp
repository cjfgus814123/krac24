#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <geometry_msgs/msg/twist.hpp> 
#include <sensor_msgs/msg/nav_sat_fix.hpp> // 💡 GPS 구독용
#include <mavros_msgs/msg/state.hpp>
#include <mavros_msgs/msg/waypoint_reached.hpp>
#include <mavros_msgs/msg/waypoint_list.hpp> // 💡 미션 리스트 구독용
#include <mavros_msgs/msg/position_target.hpp> 
#include <mavros_msgs/srv/set_mode.hpp>
#include <mavros_msgs/srv/waypoint_set_current.hpp>
#include <mavros_msgs/srv/command_long.hpp> 
#include <std_srvs/srv/trigger.hpp>
#include <std_srvs/srv/set_bool.hpp> 

#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Matrix3x3.h>

#include <chrono>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std::chrono_literals;

enum MissionPhase {
    PHASE_MISSION_FLYING = 0,        
    PHASE_PREPARE_OFFBOARD = 99,     
    PHASE_RESCUE_DESCENT = 1,        
    PHASE_LANDING_AND_GRAB = 2,      
    PHASE_ASCEND_WITH_VICTIM = 3,    
    PHASE_ALIGN_HEADING = 4,         // 💡 자동 계산된 목적지를 향해 기수 정렬
    PHASE_VERTIPORT_DESCENT = 5,     
    PHASE_FINAL_LANDING = 6          
};

class RescueMissionNode : public rclcpp::Node {
public:
    RescueMissionNode() : Node("rescue_mission_node") {
        auto qos = rclcpp::SensorDataQoS();

        this->declare_parameter("rescue_wp_seq", 6);     
        this->declare_parameter("resume_wp_seq", 7);     
        this->declare_parameter("landing_wp_seq", 13);   
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
            
        // 💡 [추가] 현재 글로벌 GPS와 전체 미션(웨이포인트) 리스트를 받아옵니다.
        global_gps_sub_ = this->create_subscription<sensor_msgs::msg::NavSatFix>(
            "mavros/global_position/global", qos, std::bind(&RescueMissionNode::gps_cb, this, std::placeholders::_1));
        waypoints_sub_ = this->create_subscription<mavros_msgs::msg::WaypointList>(
            "mavros/mission/waypoints", qos, std::bind(&RescueMissionNode::waypoints_cb, this, std::placeholders::_1));

        lander_vel_sub_ = this->create_subscription<geometry_msgs::msg::Twist>(
            "/precision_lander/cmd_vel", 10, std::bind(&RescueMissionNode::lander_vel_cb, this, std::placeholders::_1));

        vel_setpoint_pub_ = this->create_publisher<geometry_msgs::msg::Twist>("mavros/setpoint_velocity/cmd_vel_unstamped", 10);
        
        set_mode_client_ = this->create_client<mavros_msgs::srv::SetMode>("mavros/set_mode");
        set_mission_current_client_ = this->create_client<mavros_msgs::srv::WaypointSetCurrent>("mavros/mission/set_current");
        lander_client_ = this->create_client<std_srvs::srv::SetBool>("precision_lander/enable");
        command_client_ = this->create_client<mavros_msgs::srv::CommandLong>("mavros/cmd/command");

        manual_trigger_server_ = this->create_service<std_srvs::srv::Trigger>(
            "cmd/mission_proceed", std::bind(&RescueMissionNode::manual_proceed_cb, this, std::placeholders::_1, std::placeholders::_2));

        timer_ = this->create_wall_timer(50ms, std::bind(&RescueMissionNode::control_loop, this));
        
        RCLCPP_INFO(this->get_logger(), "=========================================");
        RCLCPP_INFO(this->get_logger(), "🛸 KRAC VTOL 프록시 FSM 제어기 가동");
        RCLCPP_INFO(this->get_logger(), "🔥 [목적지 오토 에임(Auto-Aim) 및 강제 천이] 탑재 완료");
        RCLCPP_INFO(this->get_logger(), "=========================================");
    }

private:
    MissionPhase current_phase_ = PHASE_MISSION_FLYING;
    MissionPhase next_phase_after_prep_ = PHASE_MISSION_FLYING; 
    
    int offboard_prep_counter_ = 0; 
    int align_counter_ = 0; 
    bool offboard_enabled_ = false; 
    int last_processed_wp_ = -1; 
    double current_yaw_ = 0.0;   
    double target_yaw_rad_ = 0.0; // 💡 자동 계산된 다음 웨이포인트 방향

    int rescue_wp_seq_, resume_wp_seq_, landing_wp_seq_;
    double safe_ascend_alt_;
    bool manual_ok_ = false;
    
    mavros_msgs::msg::State current_state_;
    geometry_msgs::msg::PoseStamped current_local_pose_;
    geometry_msgs::msg::Twist latest_lander_vel_; 
    rclcpp::Time last_lander_vel_time_;

    // 💡 [추가] GPS 및 웨이포인트 저장 변수
    sensor_msgs::msg::NavSatFix current_gps_;
    std::vector<mavros_msgs::msg::Waypoint> wp_list_;

    rclcpp::Subscription<mavros_msgs::msg::State>::SharedPtr state_sub_;
    rclcpp::Subscription<mavros_msgs::msg::WaypointReached>::SharedPtr mission_reached_sub_;
    rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr local_pose_sub_;
    rclcpp::Subscription<sensor_msgs::msg::NavSatFix>::SharedPtr global_gps_sub_;
    rclcpp::Subscription<mavros_msgs::msg::WaypointList>::SharedPtr waypoints_sub_;
    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr lander_vel_sub_; 
    
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr vel_setpoint_pub_;

    rclcpp::Client<mavros_msgs::srv::SetMode>::SharedPtr set_mode_client_;
    rclcpp::Client<mavros_msgs::srv::WaypointSetCurrent>::SharedPtr set_mission_current_client_;
    rclcpp::Client<std_srvs::srv::SetBool>::SharedPtr lander_client_;
    rclcpp::Client<mavros_msgs::srv::CommandLong>::SharedPtr command_client_; 
    rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr manual_trigger_server_;
    rclcpp::TimerBase::SharedPtr timer_;

    void state_cb(const mavros_msgs::msg::State::SharedPtr msg) { current_state_ = *msg; }
    void gps_cb(const sensor_msgs::msg::NavSatFix::SharedPtr msg) { current_gps_ = *msg; }
    void waypoints_cb(const mavros_msgs::msg::WaypointList::SharedPtr msg) { wp_list_ = msg->waypoints; }
    
    void local_pose_cb(const geometry_msgs::msg::PoseStamped::SharedPtr msg) { 
        current_local_pose_ = *msg; 
        tf2::Quaternion q(msg->pose.orientation.x, msg->pose.orientation.y, msg->pose.orientation.z, msg->pose.orientation.w);
        tf2::Matrix3x3 m(q);
        double roll, pitch;
        m.getRPY(roll, pitch, current_yaw_);
    }
    
    void lander_vel_cb(const geometry_msgs::msg::Twist::SharedPtr msg) {
        latest_lander_vel_ = *msg;
        last_lander_vel_time_ = this->now();
    }

    void manual_proceed_cb(const std::shared_ptr<std_srvs::srv::Trigger::Request>, std::shared_ptr<std_srvs::srv::Trigger::Response> res) {
        manual_ok_ = true;
        res->success = true;
        RCLCPP_WARN(this->get_logger(), "▶️ [Handshake] 파지 후 이륙(상승) 명령이 수신되었습니다!");
    }

    void switch_to_offboard() {
        auto req = std::make_shared<mavros_msgs::srv::SetMode::Request>();
        req->custom_mode = "OFFBOARD";
        set_mode_client_->async_send_request(req);
    }

    void set_precision_lander(bool enable) {
        auto req = std::make_shared<std_srvs::srv::SetBool::Request>();
        req->data = enable;
        lander_client_->async_send_request(req);
    }

    void mission_reached_cb(const mavros_msgs::msg::WaypointReached::SharedPtr msg) {
        if (msg->wp_seq == last_processed_wp_) return; 
        last_processed_wp_ = msg->wp_seq; 

        if (current_phase_ != PHASE_MISSION_FLYING) return;

        RCLCPP_INFO(this->get_logger(), "🎯 Waypoint Reached: [WP %d]", msg->wp_seq);

        if (msg->wp_seq == rescue_wp_seq_) { 
            RCLCPP_WARN(this->get_logger(), "🚨 구조 WP(%d번) 도달! 오프보드 강제 진입.", rescue_wp_seq_);
            offboard_enabled_ = true;
            offboard_prep_counter_ = 0;
            next_phase_after_prep_ = PHASE_RESCUE_DESCENT;
            current_phase_ = PHASE_PREPARE_OFFBOARD;
        } 
        else if (msg->wp_seq == landing_wp_seq_) { 
            RCLCPP_WARN(this->get_logger(), "🛬 버티포트(%d번) 도달! 오프보드 강제 진입.", landing_wp_seq_);
            offboard_enabled_ = true;
            offboard_prep_counter_ = 0;
            next_phase_after_prep_ = PHASE_VERTIPORT_DESCENT;
            current_phase_ = PHASE_PREPARE_OFFBOARD;
        }
    }

    void control_loop() {
        if (current_phase_ == PHASE_MISSION_FLYING) return;

        if (offboard_enabled_ && current_state_.mode != "OFFBOARD" && current_phase_ != PHASE_FINAL_LANDING) 
        {
            switch_to_offboard();
            geometry_msgs::msg::Twist hold_cmd;
            vel_setpoint_pub_->publish(hold_cmd);
            return; 
        }

        geometry_msgs::msg::Twist vel_cmd;
        bool publish_vel = false;

        switch (current_phase_) {
            case PHASE_PREPARE_OFFBOARD:
                publish_vel = true;
                vel_cmd.linear.x = 0.0; vel_cmd.linear.y = 0.0; vel_cmd.linear.z = 0.0; vel_cmd.angular.z = 0.0;
                
                offboard_prep_counter_++;
                if (offboard_prep_counter_ >= 20) {
                    set_precision_lander(true);
                    current_phase_ = next_phase_after_prep_;
                }
                break;

            case PHASE_RESCUE_DESCENT:
            case PHASE_VERTIPORT_DESCENT:
                publish_vel = true;
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
                
                RCLCPP_INFO_THROTTLE(this->get_logger(), *this->get_clock(), 2000, 
                    "⏳ [수동 개입 대기] 파지 후 '이륙 서비스 콜'을 전송해주세요.");

                if (manual_ok_) {
                    manual_ok_ = false;
                    current_phase_ = PHASE_ASCEND_WITH_VICTIM;
                }
                break;

            case PHASE_ASCEND_WITH_VICTIM:
                publish_vel = true;
                vel_cmd.linear.x = 0.0; vel_cmd.linear.y = 0.0; vel_cmd.linear.z = 1.2; vel_cmd.angular.z = 0.0; 

                if (current_local_pose_.pose.position.z >= safe_ascend_alt_) {
                    // =========================================================================
                    // 💡 [핵심] 30m 도달 시점: 다음 웨이포인트(실제 목적지)를 찾아 방위각을 자동 계산합니다!
                    // =========================================================================
                    target_yaw_rad_ = current_yaw_; // 기본값(실패 시 현재 유지)
                    
                    // 💡 컴파일 경고 방지를 위해 size_t로 형변환하여 비교합니다.
                    if (!wp_list_.empty() && static_cast<size_t>(resume_wp_seq_) < wp_list_.size()) {
                        size_t search_seq = resume_wp_seq_; // 💡 int 대신 size_t 사용
                        
                        // 천이 명령(3000번) 등 좌표가 없는 커맨드는 건너뛰고 진짜 다음 좌표를 찾습니다.
                        while (search_seq < wp_list_.size() && (wp_list_[search_seq].command == 3000 || wp_list_[search_seq].x_lat == 0.0)) {
                            search_seq++;
                        }

                        if (search_seq < wp_list_.size()) {
                            double lat1 = current_gps_.latitude * M_PI / 180.0;
                            double lon1 = current_gps_.longitude * M_PI / 180.0;
                            double lat2 = wp_list_[search_seq].x_lat * M_PI / 180.0;
                            double lon2 = wp_list_[search_seq].y_long * M_PI / 180.0;

                            // Haversine 기반 방위각(Bearing) 도출
                            double dLon = lon2 - lon1;
                            double y = sin(dLon) * cos(lat2);
                            double x = cos(lat1) * sin(lat2) - sin(lat1) * cos(lat2) * cos(dLon);
                            double bearing = atan2(y, x); // 북쪽 기준 (North=0, CW)

                            // MAVROS 로컬 좌표계(ENU: 동쪽=0, CCW)로 변환
                            target_yaw_rad_ = -bearing + (M_PI / 2.0);
                            
                            // 각도 정규화 [-pi, pi]
                            while (target_yaw_rad_ > M_PI) target_yaw_rad_ -= 2.0 * M_PI;
                            while (target_yaw_rad_ < -M_PI) target_yaw_rad_ += 2.0 * M_PI;

                            RCLCPP_INFO(this->get_logger(), "📌 다음 목적지(WP %zu) 탐색 완료! 목표 헤딩(%.1f도)으로 기수를 자동 조준합니다.", 
                                        search_seq, target_yaw_rad_ * 180.0 / M_PI);
                        }
                    }

                    align_counter_ = 0;
                    current_phase_ = PHASE_ALIGN_HEADING;
                }
                break;

            case PHASE_ALIGN_HEADING:
                {
                    publish_vel = true;
                    align_counter_++;

                    // 계산해둔 target_yaw_rad_를 향해 최단 거리로 회전
                    double yaw_err = target_yaw_rad_ - current_yaw_;
                    while (yaw_err > M_PI)  yaw_err -= 2.0 * M_PI;
                    while (yaw_err < -M_PI) yaw_err += 2.0 * M_PI;

                    // X, Y, Z 이동 차단, 제자리 회전만 수행
                    vel_cmd.linear.x = 0.0; vel_cmd.linear.y = 0.0; vel_cmd.linear.z = 0.0; 
                    vel_cmd.angular.z = std::clamp(yaw_err * 0.8, -0.5, 0.5); 

                    if (align_counter_ % 20 == 0) {
                        RCLCPP_INFO(this->get_logger(), "🔄 [자동 조준 중] 남은 오차: %.1f도", std::abs(yaw_err * 180.0 / M_PI));
                    }
                    
                    // 정확히 4.0초 대기 (충분한 회전 시간 확보)
                    if (align_counter_ >= 80) {
                        RCLCPP_WARN(this->get_logger(), "✈️ 기수 정렬 완벽. 고정익(FW) 강제 천이 커맨드 발사!");
                        
                        auto wp_req = std::make_shared<mavros_msgs::srv::WaypointSetCurrent::Request>();
                        wp_req->wp_seq = resume_wp_seq_;
                        set_mission_current_client_->async_send_request(wp_req);

                        // 고정익 강제 천이 발동 (Command 3000, Param 4)
                        auto transition_req = std::make_shared<mavros_msgs::srv::CommandLong::Request>();
                        transition_req->command = 3000;  
                        transition_req->param1 = 4.0;    
                        command_client_->async_send_request(transition_req);
                        
                        auto mode_req = std::make_shared<mavros_msgs::srv::SetMode::Request>();
                        mode_req->custom_mode = "AUTO.MISSION";
                        set_mode_client_->async_send_request(mode_req);
                        
                        offboard_enabled_ = false; 
                        current_phase_ = PHASE_MISSION_FLYING;
                    }
                }
                break;

            case PHASE_FINAL_LANDING:
                {
                    auto req = std::make_shared<mavros_msgs::srv::SetMode::Request>();
                    req->custom_mode = "AUTO.LAND";
                    set_mode_client_->async_send_request(req);
                    
                    offboard_enabled_ = false;
                    RCLCPP_WARN(this->get_logger(), "🏁 [임무 종료] 기체 안착 및 AUTO.LAND 전환 완료.");
                    rclcpp::shutdown();
                }
                break;
                
            default:
                break;
        }

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
