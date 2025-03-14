# Install script for directory: /home/aliare/livox_ros2_ws/src/gtsam/cmake

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
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/aliare/livox_ros2_ws/install/gtsam/lib/cmake/GTSAMCMakeTools/GTSAMCMakeToolsConfig.cmake;/home/aliare/livox_ros2_ws/install/gtsam/lib/cmake/GTSAMCMakeTools/Config.cmake.in;/home/aliare/livox_ros2_ws/install/gtsam/lib/cmake/GTSAMCMakeTools/dllexport.h.in;/home/aliare/livox_ros2_ws/install/gtsam/lib/cmake/GTSAMCMakeTools/GtsamBuildTypes.cmake;/home/aliare/livox_ros2_ws/install/gtsam/lib/cmake/GTSAMCMakeTools/GtsamMakeConfigFile.cmake;/home/aliare/livox_ros2_ws/install/gtsam/lib/cmake/GTSAMCMakeTools/GtsamTesting.cmake;/home/aliare/livox_ros2_ws/install/gtsam/lib/cmake/GTSAMCMakeTools/GtsamPrinting.cmake;/home/aliare/livox_ros2_ws/install/gtsam/lib/cmake/GTSAMCMakeTools/FindNumPy.cmake;/home/aliare/livox_ros2_ws/install/gtsam/lib/cmake/GTSAMCMakeTools/README.html")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/home/aliare/livox_ros2_ws/install/gtsam/lib/cmake/GTSAMCMakeTools" TYPE FILE FILES
    "/home/aliare/livox_ros2_ws/src/gtsam/cmake/GTSAMCMakeToolsConfig.cmake"
    "/home/aliare/livox_ros2_ws/src/gtsam/cmake/Config.cmake.in"
    "/home/aliare/livox_ros2_ws/src/gtsam/cmake/dllexport.h.in"
    "/home/aliare/livox_ros2_ws/src/gtsam/cmake/GtsamBuildTypes.cmake"
    "/home/aliare/livox_ros2_ws/src/gtsam/cmake/GtsamMakeConfigFile.cmake"
    "/home/aliare/livox_ros2_ws/src/gtsam/cmake/GtsamTesting.cmake"
    "/home/aliare/livox_ros2_ws/src/gtsam/cmake/GtsamPrinting.cmake"
    "/home/aliare/livox_ros2_ws/src/gtsam/cmake/FindNumPy.cmake"
    "/home/aliare/livox_ros2_ws/src/gtsam/cmake/README.html"
    )
endif()

