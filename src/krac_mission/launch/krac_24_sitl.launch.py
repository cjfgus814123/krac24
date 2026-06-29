import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import ExecuteProcess
from launch_ros.actions import Node

def generate_launch_description():
    pkg_fsm = 'krac_mission'
    home_dir = os.environ.get('HOME')
    px4_dir = os.path.join(home_dir, 'PX4-Autopilot')
    config_dir = os.path.join(get_package_share_directory(pkg_fsm), 'config')
    
    # plan 파일 경로
    plan_file_path = os.path.join(get_package_share_directory(pkg_fsm), 'missions', 'krac24.plan')
    
    # 💡 [추가] mission_loader.py 스크립트의 절대 경로 찾기
    # 패키지 내부의 실제 파일 위치를 지정하세요. (보통 패키지 폴더/src 또는 패키지 폴더/scripts)
    mission_loader_script = os.path.join('/home/kch/ros2_ws/src/krac_mission/src/mission_loader.py') 

    px4_sitl = ExecuteProcess(
        cmd=['make', 'px4_sitl', 'gz_standard_vtol'],
        cwd=px4_dir,
        output='screen',
        env={**os.environ, 'PX4_SIM_MODEL': 'standard_vtol'}
    )

    return LaunchDescription([
        px4_sitl,

        Node(
            package='mavros',
            executable='mavros_node',
            name='mavros',
            output='screen',
            parameters=[os.path.join(config_dir, 'mavros_params.yaml')],
            namespace='mavros',
            remappings=[('/mavros/setpoint_velocity/cmd_vel_unstamped', '/mavros/setpoint_velocity/cmd_vel_unstamped')]
        ),

        Node(
            package='krac_vision',
            executable='yolo_node',
            name='yolo_detector_node',
            output='screen',
            parameters=[{
                'model': '/home/kch/ros2_ws/src/krac_vision/weights/best.engine',
                'threshold': 0.6,
                'device': 'cuda:0'
            }],
            remappings=[('/camera', '/camera/image_raw')]
        ),

        Node(
            package='krac_control',
            executable='precision_lander',
            name='precision_lander_node',
            output='screen',
        ),

        Node(
            package='krac_control', # 앞서 krac_control로 수정했던 FSM 노드
            executable='vtol_fsm',
            name='vtol_fsm_node',
            output='screen',
            parameters=[os.path.join(config_dir, 'waypoints.yaml')]
        ),

        # 💡 Node 대신 ExecuteProcess를 사용하여 직접 python 스크립트 실행
        ExecuteProcess(
            cmd=['python3', mission_loader_script, '--ros-args', '-p', f'plan_file:={plan_file_path}'],
            output='screen'
        )
    ])
