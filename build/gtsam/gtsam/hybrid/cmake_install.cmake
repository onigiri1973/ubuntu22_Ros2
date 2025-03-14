# Install script for directory: /home/aliare/livox_ros2_ws/src/gtsam/gtsam/hybrid

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/gtsam/hybrid" TYPE FILE FILES
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/hybrid/HybridBayesNet.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/hybrid/HybridBayesTree.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/hybrid/HybridConditional.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/hybrid/HybridEliminationTree.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/hybrid/HybridFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/hybrid/HybridFactorGraph.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/hybrid/HybridGaussianConditional.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/hybrid/HybridGaussianFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/hybrid/HybridGaussianFactorGraph.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/hybrid/HybridGaussianISAM.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/hybrid/HybridGaussianProductFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/hybrid/HybridJunctionTree.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/hybrid/HybridNonlinearFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/hybrid/HybridNonlinearFactorGraph.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/hybrid/HybridNonlinearISAM.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/hybrid/HybridSmoother.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/hybrid/HybridValues.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/aliare/livox_ros2_ws/build/gtsam/gtsam/hybrid/tests/cmake_install.cmake")
endif()

