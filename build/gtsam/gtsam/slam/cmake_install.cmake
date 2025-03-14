# Install script for directory: /home/aliare/livox_ros2_ws/src/gtsam/gtsam/slam

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/gtsam/slam" TYPE FILE FILES
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/slam/AntiFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/slam/BearingFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/slam/BearingRangeFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/slam/BetweenFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/slam/BoundingConstraint.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/slam/EssentialMatrixConstraint.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/slam/EssentialMatrixFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/slam/FrobeniusFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/slam/GeneralSFMFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/slam/InitializePose.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/slam/InitializePose3.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/slam/JacobianFactorQ.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/slam/JacobianFactorQR.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/slam/JacobianFactorSVD.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/slam/KarcherMeanFactor-inl.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/slam/KarcherMeanFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/slam/OrientedPlane3Factor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/slam/PlanarProjectionFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/slam/PoseRotationPrior.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/slam/PoseTranslationPrior.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/slam/PriorFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/slam/ProjectionFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/slam/RangeFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/slam/ReferenceFrameFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/slam/RegularImplicitSchurFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/slam/RotateFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/slam/SmartFactorBase.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/slam/SmartFactorParams.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/slam/SmartProjectionFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/slam/SmartProjectionPoseFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/slam/SmartProjectionRigFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/slam/StereoFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/slam/TriangulationFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/slam/dataset.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/slam/expressions.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/slam/lago.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/aliare/livox_ros2_ws/build/gtsam/gtsam/slam/tests/cmake_install.cmake")
endif()

