cmake_minimum_required(VERSION 3.8)
project(krac_mission)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 1. 의존성 패키지 로드
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(mavros_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(krac_interfaces REQUIRED) # [필수] 인터페이스 패키지 로드



# 3-2. 리소스 파일 설치 (launch, config, 폴더 통째로 복사)
install(DIRECTORY 
  launch 
  config 
  DESTINATION share/${PROJECT_NAME}
)

# 파이썬 스크립트를 ROS 2 실행 환경(lib 디렉토리)에 복사
install(PROGRAMS
  src/mission_loader.py # 스크립트의 상대 경로. 맞게 수정해야 함
  DESTINATION lib/${PROJECT_NAME}
  RENAME mission_loader # 설치될 때의 이름 (.py 제거)
)
# 4. 패키지 종료
ament_package()
