cmake_minimum_required(VERSION 3.8)
project(lio_livox_ros2)

set(ament_cmake_DIR "/opt/ros/humble/share/ament_cmake/cmake")
find_package(ament_cmake REQUIRED)

# C++14を使用
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

# 必要なパッケージ

find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(PCL REQUIRED)
find_package(pcl_conversions REQUIRED)
find_package(GTSAM REQUIRED)

# インクルードディレクトリの設定
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${PCL_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIRS}
  ${GTSAM_INCLUDE_DIR}
)

# リンクディレクトリ
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

# ビルドターゲット
add_executable(scan_registration src/scan_registration.cpp)
ament_target_dependencies(scan_registration
  rclcpp
  sensor_msgs
  pcl_conversions
)

add_executable(pose_estimation src/pose_estimation.cpp)
ament_target_dependencies(pose_estimation
  rclcpp
  sensor_msgs
  nav_msgs
  tf2_ros
  pcl_conversions
)

target_link_libraries(scan_registration
  ${PCL_LIBRARIES}
)

target_link_libraries(pose_estimation
  ${PCL_LIBRARIES}
  gtsam
)

# インストール
install(TARGETS
  scan_registration
  pose_estimation
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
  include/
  DESTINATION include/${PROJECT_NAME}
)

install(DIRECTORY
  launch
  config
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
