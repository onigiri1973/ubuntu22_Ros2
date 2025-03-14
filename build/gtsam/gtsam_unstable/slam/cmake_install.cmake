# Install script for directory: /home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/slam

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/aliare/livox_ros2_ws/install/gtsam")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/gtsam_unstable/slam" TYPE FILE FILES
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/slam/AHRS.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/slam/BetweenFactorEM.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/slam/BiasedGPSFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/slam/DummyFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/slam/EquivInertialNavFactor_GlobalVel.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/slam/EquivInertialNavFactor_GlobalVel_NoBias.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/slam/GaussMarkov1stOrderFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/slam/InertialNavFactor_GlobalVelocity.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/slam/InvDepthFactor3.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/slam/InvDepthFactorVariant1.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/slam/InvDepthFactorVariant2.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/slam/InvDepthFactorVariant3.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/slam/LocalOrientedPlane3Factor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/slam/Mechanization_bRn2.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/slam/MultiProjectionFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/slam/PartialPriorFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/slam/PoseBetweenFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/slam/PosePriorFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/slam/PoseToPointFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/slam/ProjectionFactorPPP.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/slam/ProjectionFactorPPPC.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/slam/ProjectionFactorRollingShutter.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/slam/RelativeElevationFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/slam/SmartProjectionPoseFactorRollingShutter.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/slam/SmartRangeFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/slam/SmartStereoProjectionFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/slam/SmartStereoProjectionFactorPP.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/slam/SmartStereoProjectionPoseFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/slam/TOAFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/slam/TSAMFactors.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/slam/TransformBtwRobotsUnaryFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/slam/TransformBtwRobotsUnaryFactorEM.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/aliare/livox_ros2_ws/build/gtsam/gtsam_unstable/slam/tests/cmake_install.cmake")
endif()

