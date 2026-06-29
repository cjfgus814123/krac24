cmake_minimum_required(VERSION 3.8)
project(krac_control)

# 컴파일 옵션 설정
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(mavros_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(krac_interfaces REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(std_srvs REQUIRED)
find_package(sensor_msgs REQUIRED) 

# [팁] 공통 의존성 변수 정의
set(CONTROL_DEPENDENCIES
  rclcpp
  mavros_msgs
  geometry_msgs
  krac_interfaces
  tf2 
  tf2_geometry_msgs
  sensor_msgs
  std_srvs
)

include_directories(include)

# 실행 파일 정의 및 의존성 연결
add_executable(vtol_fsm src/vtol_fsm.cpp)
ament_target_dependencies(vtol_fsm ${CONTROL_DEPENDENCIES})

add_executable(vtol_fsm_P src/vtol_fsm_P.cpp)
ament_target_dependencies(vtol_fsm_P ${CONTROL_DEPENDENCIES})

add_executable(offboard src/offboard.cpp)
ament_target_dependencies(offboard ${CONTROL_DEPENDENCIES})

add_executable(precision_lander src/precision_lander.cpp)
ament_target_dependencies(precision_lander ${CONTROL_DEPENDENCIES})

# 설치 설정
install(TARGETS 
  vtol_fsm 
  vtol_fsm_P 
  offboard
  precision_lander
  DESTINATION lib/${PROJECT_NAME}
)



ament_package()
