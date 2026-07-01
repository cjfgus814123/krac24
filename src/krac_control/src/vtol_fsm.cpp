#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <geometry_msgs/msg/twist.hpp> // 💡 상승 구간 제어를 위한 Twist 헤더
#include <mavros_msgs/msg/state.hpp>
#include <mavros_msgs/msg/waypoint_reached.hpp>
#include <mavros_msgs/srv/set_mode.hpp>
#include <mavros_msgs/srv/waypoint_set_current.hpp>
#include <std_srvs/srv/trigger.hpp>
#include <std_srvs/srv/set_bool.hpp> // 💡 Lander 노드를 켜고 끄기 위한 서비스

#include <chrono>
#include <algorithm>

using namespace std::chrono_literals;

// FSM 상태 정의 (vtol_fsm_P의 안정적인 흐름 반영)
enum MissionPhase {
    PHASE_MISSION_FLYING = 0,        // QGC로 수동 시작 후 미션 순항 중 (대기 상태)
    PHASE_RESCUE_DESCENT = 1,        // [구조] 정밀 착륙 노드(Lander) 활성화 및 하강 감시
    PHASE_LANDING_AND_GRAB = 2,      // [구조] 지면 도달 후 대기 및 그리퍼 작동 (수동 트리거 대기)
    PHASE_ASCEND_WITH_VICTIM = 3,    // [구조] 조난자 확보 후 안전 고도까지 Offboard 수직 상승
    PHASE_RESUME_MISSION = 4,        // [구조] 복귀 웨이포인트(WP 8) 지정 후 미션 모드 재진입
    PHASE_VERTIPORT_DESCENT = 5,     // [복귀] 복귀지점 도착 후 Lander 활성화 및 최종 하강 감시
    PHASE_FINAL_LANDING = 6          // [복귀] 완전 착륙 후 AUTO.LAND 전환 및 시동 종료
};

class RescueMissionNode : public rclcpp::Node {
public:
    RescueMissionNode() : Node("rescue_mission_node") {
        auto qos = rclcpp::SensorDataQoS();

        // 파라미터 선언 및 로드
        this->declare_parameter("rescue_wp_seq", 7);     // 구조 지점 웨이포인트 번호
        this->declare_parameter("resume_wp_seq", 8);     // 복귀 시작 웨이포인트 번호
        this->declare_parameter("landing_wp_seq", 14);   // 최종 버티포트 착륙 웨이포인트 번호
        this->declare_parameter("safe_ascend_alt", 10.0); // 구조 후 안전 상승 고도

        rescue_wp_seq_ = this->get_parameter("rescue_wp_seq").as_int();
        resume_wp_seq_ = this->get_parameter("resume_wp_seq").as_int();
        landing_wp_seq_ = this->get_parameter("landing_wp_seq").as_int();
        safe_ascend_alt_ = this->get_parameter("safe_ascend_alt").as_double();

        // 구독 및 발행 설정
        state_sub_ = this->create_subscription<mavros_msgs::msg::State>(
            "mavros/state", qos, std::bind(&RescueMissionNode::state_cb, this, std::placeholders::_1));
        mission_reached_sub_ = this->create_subscription<mavros_msgs::msg::WaypointReached>(
            "mavros/mission/reached", 10, std::bind(&RescueMissionNode::mission_reached_cb, this, std::placeholders::_1));
        local_pose_sub_ = this->create_subscription<geometry_msgs::msg::PoseStamped>(
            "mavros/local_position/pose", qos, std::bind(&RescueMissionNode::local_pose_cb, this, std::placeholders::_1));

        // 상승 제어 시 필요한 Offboard 속도 발행용 퍼블리셔
        vel_setpoint_pub_ = this->create_publisher<geometry_msgs::msg::Twist>("mavros/setpoint_velocity/cmd_vel_unstamped", 10);

        // 서비스 클라이언트 설정
        set_mode_client_ = this->create_client<mavros_msgs::srv::SetMode>("mavros/set_mode");
        set_mission_current_client_ = this->create_client<mavros_msgs::srv::WaypointSetCurrent>("mavros/mission/set_current");
        lander_client_ = this->create_client<std_srvs::srv::SetBool>("precision_lander/enable");

        // 매뉴얼 그리퍼/이탈 트리거 서버
        manual_trigger_server_ = this->create_service<std_srvs::srv::Trigger>(
            "cmd/mission_proceed", std::bind(&RescueMissionNode::manual_proceed_cb, this, std::placeholders::_1, std::placeholders::_2));

        // 💡 20Hz 주기로 상태 머신 루프 구동 (50ms)
        timer_ = this->create_wall_timer(50ms, std::bind(&RescueMissionNode::control_loop, this));
        
        RCLCPP_INFO(this->get_logger(), "=========================================");
        RCLCPP_INFO(this->get_logger(), "🛸 KRAC VTOL 수동 시작 모드 FSM 켜짐");
        RCLCPP_INFO(this->get_logger(), "💡 QGC에서 미션을 업로드하고 직접 시동/출발을 눌러주세요.");
        RCLCPP_INFO(this->get_logger(), "=========================================");
    }

private:
    // 초기 상태를 Flying(순항 모니터링)으로 두어 강제 이륙 코드를 제거합니다.
    MissionPhase current_phase_ = PHASE_MISSION_FLYING;
    int rescue_wp_seq_, resume_wp_seq_, landing_wp_seq_;
    double safe_ascend_alt_;
    bool manual_ok_ = false;
    
    mavros_msgs::msg::State current_state_;
    geometry_msgs::msg::PoseStamped current_local_pose_;

    rclcpp::Subscription<mavros_msgs::msg::State>::SharedPtr state_sub_;
    rclcpp::Subscription<mavros_msgs::msg::WaypointReached>::SharedPtr mission_reached_sub_;
    rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr local_pose_sub_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr vel_setpoint_pub_;

    rclcpp::Client<mavros_msgs::srv::SetMode>::SharedPtr set_mode_client_;
    rclcpp::Client<mavros_msgs::srv::WaypointSetCurrent>::SharedPtr set_mission_current_client_;
    rclcpp::Client<std_srvs::srv::SetBool>::SharedPtr lander_client_;
    rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr manual_trigger_server_;
    rclcpp::TimerBase::SharedPtr timer_;

    // 콜백 함수 정의
    void state_cb(const mavros_msgs::msg::State::SharedPtr msg) { current_state_ = *msg; }
    void local_pose_cb(const geometry_msgs::msg::PoseStamped::SharedPtr msg) { current_local_pose_ = *msg; }

    void manual_proceed_cb(const std::shared_ptr<std_srvs::srv::Trigger::Request>, std::shared_ptr<std_srvs::srv::Trigger::Response> res) {
        manual_ok_ = true;
        res->success = true;
        RCLCPP_WARN(this->get_logger(), "▶️ [Handshake] 인간의 진행 명령 수신완료!");
    }

    // 오프보드 모드 전환 함수
    void switch_to_offboard() {
        auto req = std::make_shared<mavros_msgs::srv::SetMode::Request>();
        req->custom_mode = "OFFBOARD";
        set_mode_client_->async_send_request(req);
    }

    // 정밀 착륙(Lander) 노드 On/Off 스위치 함수
    void set_precision_lander(bool enable) {
        auto req = std::make_shared<std_srvs::srv::SetBool::Request>();
        req->data = enable;
        lander_client_->async_send_request(req);
        RCLCPP_INFO(this->get_logger(), "⚙️ 정밀 착륙(Precision Lander) 노드 서비스 신호 전송 -> %s", enable ? "ON" : "OFF");
    }

    // 웨이포인트 도달 이벤트 처리 (여기서 수동 비행 중 가로챕니다)
    void mission_reached_cb(const mavros_msgs::msg::WaypointReached::SharedPtr msg) {
        if (current_phase_ != PHASE_MISSION_FLYING) return;

        RCLCPP_INFO(this->get_logger(), "🎯 Waypoint Reached: [WP %d]", msg->wp_seq);

        if (msg->wp_seq == rescue_wp_seq_) {
            RCLCPP_WARN(this->get_logger(), "🚨 [상태 전이] 구조 웨이포인트 도달! OFFBOARD 전환 및 정밀착륙 가동.");
            switch_to_offboard();
            set_precision_lander(true); // 착륙 근육 노드 ON
            current_phase_ = PHASE_RESCUE_DESCENT;
        } 
        else if (msg->wp_seq == landing_wp_seq_) {
            RCLCPP_WARN(this->get_logger(), "🛬 [상태 전이] 최종 버티포트 도달! OFFBOARD 전환 및 정밀착륙 가동.");
            switch_to_offboard();
            set_precision_lander(true); // 착륙 근육 노드 ON
            current_phase_ = PHASE_VERTIPORT_DESCENT;
        }
    }

    // 메인 주기 제어 루프 (20Hz)
    void control_loop() {
        // 수동 모드로 비행 중일 때는 이 루프에서 아무런 명령도 주지 않고 가만히 지켜만 봅니다.
        if (current_phase_ == PHASE_MISSION_FLYING) {
            RCLCPP_INFO_THROTTLE(this->get_logger(), *this->get_clock(), 5000, "상태: [순항 중] 사용자의 수동 비행 및 웨이포인트 도달 감시 중...");
            return;
        }

        geometry_msgs::msg::Twist vel_cmd;

        switch (current_phase_) {
            case PHASE_RESCUE_DESCENT:
                // 조종 주도권은 'precision_lander_node'가 쥐고 있습니다. 
                // 본 FSM(두뇌) 노드는 하강 고도만 체크하는 심판 역할을 수행합니다.
                RCLCPP_INFO_THROTTLE(this->get_logger(), *this->get_clock(), 1000, "상태: [구조 정밀하강] 현재 고도: %.2fm", current_local_pose_.pose.position.z);
                
                if (current_local_pose_.pose.position.z < 0.4) { // 지면 근접 시
                    RCLCPP_WARN(this->get_logger(), "📌 지면 근접 감지. 착륙 통제권을 회수하고 Lander 노드를 정지합니다.");
                    set_precision_lander(false); // Lander 노드 중복 명령 차단을 위해 꺼줌
                    manual_ok_ = false;
                    current_phase_ = PHASE_LANDING_AND_GRAB;
                }
                break;

            case PHASE_LANDING_AND_GRAB:
                // 완벽한 안착을 위해 하방으로 약한 누름 추력 인가
                vel_cmd.linear.z = -0.2;
                vel_setpoint_pub_->publish(vel_cmd);
                
                RCLCPP_INFO_THROTTLE(this->get_logger(), *this->get_clock(), 2000, "상태: [바구니 안착] 파지 완료 후 'ros2 service call /cmd/mission_proceed std_srvs/srv/Trigger'를 주입하세요.");
                
                if (manual_ok_) {
                    RCLCPP_WARN(this->get_logger(), "🚨 [상태 전이] 파지 확인 완료! 수직 재이륙(상승) 시퀀스 돌입.");
                    manual_ok_ = false;
                    current_phase_ = PHASE_ASCEND_WITH_VICTIM;
                }
                break;

            case PHASE_ASCEND_WITH_VICTIM:
                // Offboard 모드 상태에서 수직으로 안전하고 신속하게 상승 (+1.2 m/s)
                vel_cmd.linear.x = 0.0;
                vel_cmd.linear.y = 0.0;
                vel_cmd.linear.z = 1.2; 
                vel_setpoint_pub_->publish(vel_cmd);

                RCLCPP_INFO_THROTTLE(this->get_logger(), *this->get_clock(), 1000, "상태: [구조 후 상승] 상승 고도: %.2fm / 목표: %.1fm", 
                                     current_local_pose_.pose.position.z, safe_ascend_alt_);
                
                if (current_local_pose_.pose.position.z >= safe_ascend_alt_) {
                    RCLCPP_WARN(this->get_logger(), "📌 안전 고도 도달 완료. 복귀 비행(미션 재개)을 요청합니다.");
                    current_phase_ = PHASE_RESUME_MISSION;
                }
                break;

            case PHASE_RESUME_MISSION:
                {
                    // 1. 복귀용 첫 번째 웨이포인트(예: WP 8)로 내부 인덱스 강제 변경
                    auto wp_req = std::make_shared<mavros_msgs::srv::WaypointSetCurrent::Request>();
                    wp_req->wp_seq = resume_wp_seq_;
                    set_mission_current_client_->async_send_request(wp_req);

                    // 2. PX4 모드를 자율 미션 비행(고정익 전환용) 모드로 복귀
                    auto mode_req = std::make_shared<mavros_msgs::srv::SetMode::Request>();
                    mode_req->custom_mode = "AUTO.MISSION";
                    set_mode_client_->async_send_request(mode_req);
                    
                    RCLCPP_INFO(this->get_logger(), "🔄 [모드 복귀] AUTO.MISSION 전환 및 WP %d 점프 완수.", resume_wp_seq_);
                    current_phase_ = PHASE_MISSION_FLYING; // 다시 대기 상태로 루프 리셋
                }
                break;

            case PHASE_VERTIPORT_DESCENT:
                // 최종 버티포트 정밀 하강 단계 (Lander 노드가 조종 중)
                RCLCPP_INFO_THROTTLE(this->get_logger(), *this->get_clock(), 1000, "상태: [버티포트 정밀하강] 현재 고도: %.2fm", current_local_pose_.pose.position.z);
                
                if (current_local_pose_.pose.position.z < 0.25) { // 완전 착륙 직전
                    RCLCPP_WARN(this->get_logger(), "📌 버티포트 안착 확인. Lander 노드를 끄고 엔진 disarm 절차를 밟습니다.");
                    set_precision_lander(false);
                    current_phase_ = PHASE_FINAL_LANDING;
                }
                break;

            case PHASE_FINAL_LANDING:
                {
                    // 완전 안착했으므로 PX4 내장 자동 착륙 기능을 켜서 스스로 Disarm(시동 종료)되게 유도합니다.
                    auto req = std::make_shared<mavros_msgs::srv::SetMode::Request>();
                    req->custom_mode = "AUTO.LAND";
                    set_mode_client_->async_send_request(req);
                    
                    RCLCPP_WARN(this->get_logger(), "🏁 [임무 종료] AUTO.LAND 전환 완료. 시스템을 종료해도 좋습니다.");
                    rclcpp::shutdown(); // 노드 자동 폭파 안전 종료
                }
                break;
                
            default:
                break;
        }
    }
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<RescueMissionNode>());
    rclcpp::shutdown();
    return 0;
}
