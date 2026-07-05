#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from std_msgs.msg import Float64  # Float64 메시지 타입 import
from mavros_msgs.srv import CommandLong
import time

class GripperController(Node):
    def __init__(self):
        super().__init__('gripper_controller')
        # 토픽 퍼블리셔 생성
        self.pub_s5 = self.create_publisher(Float64, '/model/amsr_vtol_0/servo_5', 10)
        self.pub_s6 = self.create_publisher(Float64, '/model/amsr_vtol_0/servo_6', 10)
        self.pub_s7 = self.create_publisher(Float64, '/model/amsr_vtol_0/servo_7', 10)
        self.get_logger().info('그리퍼 제어 노드 준비 완료!')

    def control_gripper(self, action):
        if action == "rotation":
            self.get_logger().info('>>> 회전')
            msg.data = 0.5 
            self.pub_s5.publish(msg)
        elif action == "grab":
            self.get_logger().info('>>> 물체 파지 (Grab)')
            msg.data = 0.5 
            self.pub_s6.publish(msg)
            msg.data = 0.5
            self.pub_s7.publish(msg)
        elif action == "release":
            self.get_logger().info('>>> 물체 방출 (Release)')
            msg.data = -0.5
            self.pub_s6.publish(msg)
            msg.data = -0.5
            self.pub_s7.publish(msg)
            
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
            cmd = input("명령을 입력하세요 (0/1/2/q): ")
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
