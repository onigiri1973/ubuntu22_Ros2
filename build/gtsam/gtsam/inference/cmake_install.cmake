# Install script for directory: /home/aliare/livox_ros2_ws/src/gtsam/gtsam/inference

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/gtsam/inference" TYPE FILE FILES
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/inference/BayesNet-inst.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/inference/BayesNet.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/inference/BayesTree-inst.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/inference/BayesTree.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/inference/BayesTreeCliqueBase-inst.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/inference/BayesTreeCliqueBase.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/inference/ClusterTree-inst.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/inference/ClusterTree.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/inference/Conditional-inst.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/inference/Conditional.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/inference/DotWriter.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/inference/EdgeKey.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/inference/EliminateableFactorGraph-inst.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/inference/EliminateableFactorGraph.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/inference/EliminationTree-inst.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/inference/EliminationTree.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/inference/Factor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/inference/FactorGraph-inst.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/inference/FactorGraph.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/inference/ISAM-inst.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/inference/ISAM.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/inference/JunctionTree-inst.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/inference/JunctionTree.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/inference/Key.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/inference/LabeledSymbol.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/inference/MetisIndex-inl.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/inference/MetisIndex.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/inference/Ordering.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/inference/Symbol.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/inference/VariableIndex-inl.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/inference/VariableIndex.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/inference/VariableSlots.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/inference/graph-inl.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/inference/graph.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/inference/inference-inst.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/inference/inferenceExceptions.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/aliare/livox_ros2_ws/build/gtsam/gtsam/inference/tests/cmake_install.cmake")
endif()

