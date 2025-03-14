# Install script for directory: /home/aliare/livox_ros2_ws/src/gtsam/gtsam/sfm

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/gtsam/sfm" TYPE FILE FILES
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/sfm/BinaryMeasurement.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/sfm/DsfTrackGenerator.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/sfm/MFAS.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/sfm/SfmData.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/sfm/SfmTrack.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/sfm/ShonanAveraging.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/sfm/ShonanFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/sfm/ShonanGaugeFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/sfm/TransferFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/sfm/TranslationFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/sfm/TranslationRecovery.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/aliare/livox_ros2_ws/build/gtsam/gtsam/sfm/tests/cmake_install.cmake")
endif()

