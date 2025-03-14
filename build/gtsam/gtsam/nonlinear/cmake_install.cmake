# Install script for directory: /home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/gtsam/nonlinear" TYPE FILE FILES
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/AdaptAutoDiff.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/BatchFixedLagSmoother.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/CustomFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/DoglegOptimizer.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/DoglegOptimizerImpl.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/Expression-inl.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/Expression.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/ExpressionFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/ExpressionFactorGraph.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/ExtendedKalmanFilter-inl.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/ExtendedKalmanFilter.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/FixedLagSmoother.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/FunctorizedFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/GaussNewtonOptimizer.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/GncOptimizer.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/GncParams.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/GraphvizFormatting.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/ISAM2-impl.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/ISAM2.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/ISAM2Clique.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/ISAM2Params.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/ISAM2Result.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/ISAM2UpdateParams.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/LevenbergMarquardtOptimizer.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/LevenbergMarquardtParams.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/LinearContainerFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/Marginals.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/NonlinearConjugateGradientOptimizer.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/NonlinearEquality.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/NonlinearFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/NonlinearFactorGraph.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/NonlinearISAM.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/NonlinearOptimizer.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/NonlinearOptimizerParams.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/PriorFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/Symbol.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/Values-inl.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/Values.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/WhiteNoiseFactor.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/expressionTesting.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/expressions.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/factorTesting.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/nonlinearExceptions.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/utilities.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/gtsam/nonlinear/internal" TYPE FILE FILES
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/internal/CallRecord.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/internal/ChiSquaredInverse.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/internal/ExecutionTrace.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/internal/ExpressionNode.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/internal/JacobianMap.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/internal/LevenbergMarquardtState.h"
    "/home/aliare/livox_ros2_ws/src/gtsam/gtsam/nonlinear/internal/NonlinearOptimizerState.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/aliare/livox_ros2_ws/build/gtsam/gtsam/nonlinear/tests/cmake_install.cmake")
endif()

