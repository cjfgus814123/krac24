#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from geometry_msgs.msg import PoseStamped, Twist  # [추가됨] 고도 및 제어 속도 구독용
from krac_interfaces.msg import TargetError
from cv_bridge import CvBridge
import cv2
import numpy as np
import math  # [추가됨] 거리 및 각도 변환용
from ultralytics import YOLO

class VisionTracker(Node):
    def __init__(self):
        super().__init__('vision_tracker_node')
        self.bridge = CvBridge()
        self.image_sub = self.create_subscription(Image, '/camera/image_raw', self.image_callback, 10)
        self.error_pub = self.create_publisher(TargetError, '/vision/target_error', 10)
        
        # [추가됨] 디버깅 이미지 퍼블리셔 및 데이터 서브스크라이버
        self.dbg_pub = self.create_publisher(Image, '/vision/dbg_image', 10)
        self.pose_sub = self.create_subscription(PoseStamped, '/mavros/local_position/pose', self.pose_cb, 10)
        self.cmd_sub = self.create_subscription(Twist, '/mavros/setpoint_velocity/cmd_vel_unstamped', self.cmd_cb, 10)
        
        # [추가됨] 디버깅용 외부 데이터 저장 변수
        self.current_alt = 0.0
        self.current_cmd = Twist()
        
        # OBB 모델 로드 (1024 해상도에 최적화된 TensorRT 엔진 사용 권장)
        self.model = YOLO('/home/kch/ros2_ws/src/krac_vision/weights/best.pt') 
        
        # 🌟 OBB 추론 해상도에 맞춘 1024x1024 세팅
        self.img_size = 1024
        self.center_x = self.img_size / 2.0  # 512.0
        self.center_y = self.img_size / 2.0  # 512.0
        
        # 칼만 필터 초기화
        self.kf = cv2.KalmanFilter(4, 2)
        self.kf.measurementMatrix = np.array([[1, 0, 0, 0], [0, 1, 0, 0]], np.float32)
        self.kf.transitionMatrix = np.array([[1, 0, 1, 0], [0, 1, 0, 1], [0, 0, 1, 0], [0, 0, 0, 1]], np.float32)
        self.kf.processNoiseCov = np.eye(4, dtype=np.float32) * 0.03
        self.kf_initialized = False

    # [추가됨] 콜백 함수: 외부 제어 상태 수신
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

        # 🌟 카메라 원본 비율을 무시하고 1024x1024로 리사이즈하여 추론
        resized_img = cv2.resize(cv_image, (self.img_size, self.img_size))
        
        # [추가됨] 디버깅용 이미지 복사본 (여기에 그림을 그립니다)
        dbg_img = resized_img.copy()

        # [추가됨] 화면 중앙 십자선 시각화 (초록색)
        cv2.line(dbg_img, (int(self.center_x) - 30, int(self.center_y)), (int(self.center_x) + 30, int(self.center_y)), (0, 255, 0), 2)
        cv2.line(dbg_img, (int(self.center_x), int(self.center_y) - 30), (int(self.center_x), int(self.center_y) + 30), (0, 255, 0), 2)

        results = self.model(resized_img, imgsz=self.img_size, conf=0.6, verbose=False)
        target_msg = TargetError()
        target_msg.is_detected = False

        # 시각화용 변수 초기화
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
            
            # 1024x1024 평면 기준의 픽셀 오차 발행
            target_msg.pixel_err_x = filtered_cx - self.center_x
            target_msg.pixel_err_y = self.center_y - filtered_cy 
            target_msg.yaw_err_rad = theta
            target_msg.is_detected = True

            # [추가됨] 타겟 중심점 거리 및 시각화
            dist_px = math.hypot(target_msg.pixel_err_x, target_msg.pixel_err_y)
            
            # OBB 바운딩 박스 그리기 (파란색)
            try:
                obb_pts = best_obb.xyxyxyxy[0].cpu().numpy().astype(int)
                cv2.polylines(dbg_img, [obb_pts], isClosed=True, color=(255, 0, 0), thickness=2)
            except Exception:
                pass # 좌표 변환 실패 시 생략

            # 칼만 필터가 적용된 목표점 (빨간 점) 및 중심점과의 추종 선 (노란 선)
            t_x, t_y = int(filtered_cx), int(filtered_cy)
            cv2.circle(dbg_img, (t_x, t_y), 6, (0, 0, 255), -1)
            cv2.line(dbg_img, (int(self.center_x), int(self.center_y)), (t_x, t_y), (0, 255, 255), 2)

        else:
            # 미탐지 시 KF 예측값으로 관성 유지
            if self.kf_initialized:
                predicted = self.kf.predict()
                target_msg.pixel_err_x = predicted[0][0] - self.center_x
                target_msg.pixel_err_y = self.center_y - predicted[1][0]
                target_msg.is_detected = False 
                
                # 미탐지 관성 중일 때의 위치 (회색 점)
                t_x, t_y = int(predicted[0][0]), int(predicted[1][0])
                cv2.circle(dbg_img, (t_x, t_y), 6, (150, 150, 150), -1)
                cv2.putText(dbg_img, "LOST (KF Tracking)", (t_x + 10, t_y), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (150, 150, 150), 2)

        self.error_pub.publish(target_msg)

        # ----------------------------------------------------------------------
        # [추가됨] 화면 좌측 상단 HUD (Heads-Up Display) 텍스트 출력
        # ----------------------------------------------------------------------
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
            color = status_color if i == 0 else (0, 255, 255) # 상태만 초록/빨강, 나머진 노란색
            # 검은색 테두리(그림자) 추가하여 가독성 확보
            cv2.putText(dbg_img, line, (22, y_offset + 2), cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0, 0, 0), 3)
            cv2.putText(dbg_img, line, (20, y_offset), cv2.FONT_HERSHEY_SIMPLEX, 0.8, color, 2)
            y_offset += 35
        # ----------------------------------------------------------------------

        # [추가됨] 완성된 디버깅 이미지를 rqt_image_view용으로 퍼블리시
        self.dbg_pub.publish(self.bridge.cv2_to_imgmsg(dbg_img, "bgr8"))

def main(args=None):
    rclpy.init(args=args)
    node = VisionTracker()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
