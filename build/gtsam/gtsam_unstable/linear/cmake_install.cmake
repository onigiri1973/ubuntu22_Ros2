# Install script for directory: /home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/linear

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/gtsam_unstable/linear" TYPE FILE FILES
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/linear/ActiveSetSolver-inl.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/linear/ActiveSetSolver.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/linear/EqualityFactorGraph.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/linear/InequalityFactorGraph.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/linear/InfeasibleInitialValues.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/linear/InfeasibleOrUnboundedProblem.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/linear/LP.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/linear/LPInitSolver.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/linear/LPSolver.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/linear/LinearCost.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/linear/LinearEquality.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/linear/LinearInequality.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/linear/QP.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/linear/QPInitSolver.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/linear/QPSParser.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/linear/QPSParserException.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam_unstable/linear/QPSolver.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/aliare/livox_ros2_ws/build/gtsam/gtsam_unstable/linear/tests/cmake_install.cmake")
endif()

