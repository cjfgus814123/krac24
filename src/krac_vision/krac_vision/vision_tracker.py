#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import rclpy
from rclpy.node import Node
from rclpy.qos import qos_profile_sensor_data  # 💡 [추가됨] 센서 데이터용 QoS 임포트
from sensor_msgs.msg import Image
from geometry_msgs.msg import PoseStamped, Twist
from krac_interfaces.msg import TargetError
from cv_bridge import CvBridge
import cv2
import numpy as np
import math
from ultralytics import YOLO

class VisionTracker(Node):
    def __init__(self):
        super().__init__('vision_tracker_node')
        self.bridge = CvBridge()
        
        # 💡 [핵심 수정] 센서와 MAVROS 데이터를 받는 모든 구독자에 qos_profile_sensor_data 적용
        self.image_sub = self.create_subscription(
            Image, '/camera/image_raw', self.image_callback, qos_profile_sensor_data)
        self.pose_sub = self.create_subscription(
            PoseStamped, '/mavros/local_position/pose', self.pose_cb, qos_profile_sensor_data)
        self.cmd_sub = self.create_subscription(
            Twist, '/mavros/setpoint_velocity/cmd_vel_unstamped', self.cmd_cb, qos_profile_sensor_data)
        
        self.error_pub = self.create_publisher(TargetError, '/vision/target_error', 10)
        self.dbg_pub = self.create_publisher(Image, '/vision/dbg_image', 10)
        
        self.current_alt = 0.0
        self.current_cmd = Twist()
        
        # OBB 모델 로드
        self.model = YOLO('/home/kch/ros2_ws/src/krac_vision/weights/best.pt') 
        
        self.img_size = 1024
        self.center_x = self.img_size / 2.0  
        self.center_y = self.img_size / 2.0  
        
        # 칼만 필터 초기화
        self.kf = cv2.KalmanFilter(4, 2)
        self.kf.measurementMatrix = np.array([[1, 0, 0, 0], [0, 1, 0, 0]], np.float32)
        self.kf.transitionMatrix = np.array([[1, 0, 1, 0], [0, 1, 0, 1], [0, 0, 1, 0], [0, 0, 0, 1]], np.float32)
        self.kf.processNoiseCov = np.eye(4, dtype=np.float32) * 0.03
        self.kf_initialized = False

    def pose_cb(self, msg):
        self.current_alt = msg.pose.position.z

    def cmd_cb(self, msg):
        self.current_cmd = msg

    def image_callback(self, msg):
        try:
            cv_image = self.bridge.imgmsg_to_cv2(msg, "bgr8")
        except Exception as e:
            self.get_logger().error(f"CV Bridge Error: {e}")
            return

        resized_img = cv2.resize(cv_image, (self.img_size, self.img_size))
        dbg_img = resized_img.copy()

        cv2.line(dbg_img, (int(self.center_x) - 30, int(self.center_y)), (int(self.center_x) + 30, int(self.center_y)), (0, 255, 0), 2)
        cv2.line(dbg_img, (int(self.center_x), int(self.center_y) - 30), (int(self.center_x), int(self.center_y) + 30), (0, 255, 0), 2)

        results = self.model(resized_img, imgsz=self.img_size, conf=0.6, verbose=False)
        target_msg = TargetError()
        target_msg.is_detected = False

        dist_px = 0.0
        theta_val = 0.0

        if len(results[0].obb) > 0:
            best_obb = results[0].obb[0]
            cx, cy = float(best_obb.xywhr[0][0]), float(best_obb.xywhr[0][1])
            theta = float(best_obb.xywhr[0][4]) 
            theta_val = theta

            if not self.kf_initialized:
                self.kf.statePre = np.array([[cx], [cy], [0], [0]], np.float32)
                self.kf.statePost = np.array([[cx], [cy], [0], [0]], np.float32)
                self.kf_initialized = True
            
            measurement = np.array([[np.float32(cx)], [np.float32(cy)]])
            self.kf.correct(measurement)
            predicted = self.kf.predict()

            filtered_cx, filtered_cy = predicted[0][0], predicted[1][0]
            
            target_msg.pixel_err_x = filtered_cx - self.center_x
            target_msg.pixel_err_y = self.center_y - filtered_cy 
            target_msg.yaw_err_rad = theta
            target_msg.is_detected = True

            dist_px = math.hypot(target_msg.pixel_err_x, target_msg.pixel_err_y)
            
            try:
                obb_pts = best_obb.xyxyxyxy[0].cpu().numpy().astype(int)
                cv2.polylines(dbg_img, [obb_pts], isClosed=True, color=(255, 0, 0), thickness=2)
            except Exception:
                pass

            t_x, t_y = int(filtered_cx), int(filtered_cy)
            cv2.circle(dbg_img, (t_x, t_y), 6, (0, 0, 255), -1)
            cv2.line(dbg_img, (int(self.center_x), int(self.center_y)), (t_x, t_y), (0, 255, 255), 2)

        else:
            if self.kf_initialized:
                predicted = self.kf.predict()
                target_msg.pixel_err_x = predicted[0][0] - self.center_x
                target_msg.pixel_err_y = self.center_y - predicted[1][0]
                target_msg.is_detected = False 
                
                t_x, t_y = int(predicted[0][0]), int(predicted[1][0])
                cv2.circle(dbg_img, (t_x, t_y), 6, (150, 150, 150), -1)
                cv2.putText(dbg_img, "LOST (KF Tracking)", (t_x + 10, t_y), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (150, 150, 150), 2)

        self.error_pub.publish(target_msg)

        status_color = (0, 255, 0) if target_msg.is_detected else (0, 0, 255)
        text_lines = [
            f"Status: {'DETECTED' if target_msg.is_detected else 'LOST'}",
            f"Alt (Ground Height): {self.current_alt:.2f} m",
            f"Center Dist: {dist_px:.1f} px",
            f"OBB Theta: {theta_val:.3f} rad ({math.degrees(theta_val):.1f} deg)",
            f"Cmd_Vel X: {self.current_cmd.linear.x:.2f}, Y: {self.current_cmd.linear.y:.2f}",
            f"Cmd_Vel Z: {self.current_cmd.linear.z:.2f}, Yaw: {self.current_cmd.angular.z:.2f}"
        ]

        y_offset = 40
        for i, line in enumerate(text_lines):
            color = status_color if i == 0 else (0, 255, 255)
            cv2.putText(dbg_img, line, (22, y_offset + 2), cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0, 0, 0), 3)
            cv2.putText(dbg_img, line, (20, y_offset), cv2.FONT_HERSHEY_SIMPLEX, 0.8, color, 2)
            y_offset += 35

        self.dbg_pub.publish(self.bridge.cv2_to_imgmsg(dbg_img, "bgr8"))

def main(args=None):
    rclpy.init(args=args)
    node = VisionTracker()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
