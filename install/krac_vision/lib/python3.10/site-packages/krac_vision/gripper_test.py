#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from mavros_msgs.srv import CommandLong
import time

class GripperController(Node):
    def __init__(self):
        super().__init__('gripper_controller')
        self.cli = self.create_client(CommandLong, '/mavros/cmd/command')
        while not self.cli.wait_for_service(timeout_sec=1.0):
            self.get_logger().info('MAVROS 커맨드 서비스 대기 중...')
        self.get_logger().info('그리퍼 제어 노드 준비 완료!')

    def set_servo(self, servo_channel, pwm_value):
        req = CommandLong.Request()
        req.command = 183          # MAV_CMD_DO_SET_SERVO
        req.param1 = float(servo_channel)
        req.param2 = float(pwm_value)
        self.cli.call_async(req)
        self.get_logger().info(f'서보 {servo_channel}번에 PWM {pwm_value} 전송')

    def control_gripper(self, action):
        if action == "rotation":
            self.get_logger().info('>>> 회전')
            self.set_servo(4, 2000) 
        elif action == "grab":
            self.get_logger().info('>>> 물체 파지 (Grab)')
            self.set_servo(5, 2000) # 왼쪽 서보 (조인트 구조에 따라 값 조정 필요)
            self.set_servo(6, 1000) # 오른쪽 서보
        elif action == "release":
            self.get_logger().info('>>> 물체 방출 (Release)')
            self.set_servo(5, 1500) 
            self.set_servo(6, 1500) 

def main(args=None):
    rclpy.init(args=args)
    node = GripperController()

    print("\n==================================")
    print(" 🕹️ 그리퍼 제어 테스트")
    print(" [0] 회전 (Rotation)")
    print(" [1] 파지 (Grab)")
    print(" [2] 놓기 (Release)")
    print(" [q] 종료")
    print("==================================\n")

    try:
        while rclpy.ok():
            cmd = input("명령을 입력하세요 (1/2/q): ")
            if cmd == '0':
                node.control_gripper("rotation")
            elif cmd == '1':
                node.control_gripper("grab")
            elif cmd == '2':
                node.control_gripper("release")
            elif cmd == 'q':
                break
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
