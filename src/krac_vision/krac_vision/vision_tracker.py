#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from custom_interfaces.msg import TargetError
from cv_bridge import CvBridge
import cv2
import numpy as np
from ultralytics import YOLO

class VisionTracker(Node):
    def __init__(self):
        super().__init__('vision_tracker_node')
        self.bridge = CvBridge()
        self.image_sub = self.create_subscription(Image, '/camera/image_raw', self.image_callback, 10)
        self.error_pub = self.create_publisher(TargetError, '/vision/target_error', 10)
        
        # OBB 모델 로드 (1024 해상도에 최적화된 TensorRT 엔진 사용 권장)
        self.model = YOLO('best.engine') 
        
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

    def image_callback(self, msg):
        try:
            cv_image = self.bridge.imgmsg_to_cv2(msg, "bgr8")
        except Exception as e:
            self.get_logger().error(f"CV Bridge Error: {e}")
            return

        # 🌟 카메라 원본 비율을 무시하고 1024x1024로 리사이즈하여 추론
        # (렌즈 왜곡이 우려된다면 패딩(Letterbox)을 추가하는 방식을 사용해도 좋습니다)
        resized_img = cv2.resize(cv_image, (self.img_size, self.img_size))

        results = self.model(resized_img, imgsz=self.img_size, conf=0.6, verbose=False)
        target_msg = TargetError()
        target_msg.is_detected = False

        if len(results[0].obb) > 0:
            best_obb = results[0].obb[0]
            cx, cy = float(best_obb.xywhr[0][0]), float(best_obb.xywhr[0][1])
            theta = float(best_obb.xywhr[0][4]) 

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

        else:
            # 미탐지 시 KF 예측값으로 관성 유지
            if self.kf_initialized:
                predicted = self.kf.predict()
                target_msg.pixel_err_x = predicted[0][0] - self.center_x
                target_msg.pixel_err_y = self.center_y - predicted[1][0]
                target_msg.is_detected = False 
                
        self.error_pub.publish(target_msg)

def main(args=None):
    rclpy.init(args=args)
    node = VisionTracker()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
