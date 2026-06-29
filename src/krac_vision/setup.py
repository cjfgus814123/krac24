from setuptools import setup
import os
from glob import glob

package_name = 'krac_vision'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        
        # 1. [가중치] weights 폴더 안의 모든 .pt 파일을 설치 폴더로 복사
        (os.path.join('share', package_name, 'weights'), glob('weights/*.pt')),
        
        # 2. [추가] launch 폴더 안의 모든 .launch.py 파일을 설치 폴더로 복사
        (os.path.join('share', package_name, 'launch'), glob('launch/*.launch.py')),
    ],
    install_requires=['setuptools', 'ultralytics', 'opencv-python'],
    zip_safe=True,
    maintainer='kch',
    maintainer_email='kch@todo.todo',
    description='Vision tracker package for OBB detection',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            # ros2 run krac_vision [이름] 명령어로 실행할 파일들 등록
            'yolo_node = krac_vision.vision_tracker:main',
        ],
    },
)
