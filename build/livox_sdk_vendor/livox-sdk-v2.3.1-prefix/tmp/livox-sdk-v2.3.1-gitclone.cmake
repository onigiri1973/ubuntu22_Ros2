
if(NOT "/home/aliare/livox_ros2_ws/build/livox_sdk_vendor/livox-sdk-v2.3.1-prefix/src/livox-sdk-v2.3.1-stamp/livox-sdk-v2.3.1-gitinfo.txt" IS_NEWER_THAN "/home/aliare/livox_ros2_ws/build/livox_sdk_vendor/livox-sdk-v2.3.1-prefix/src/livox-sdk-v2.3.1-stamp/livox-sdk-v2.3.1-gitclone-lastrun.txt")
  message(STATUS "Avoiding repeated git clone, stamp file is up to date: '/home/aliare/livox_ros2_ws/build/livox_sdk_vendor/livox-sdk-v2.3.1-prefix/src/livox-sdk-v2.3.1-stamp/livox-sdk-v2.3.1-gitclone-lastrun.txt'")
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E rm -rf "/home/aliare/livox_ros2_ws/build/livox_sdk_vendor/livox-sdk-v2.3.1-prefix/src/livox-sdk-v2.3.1"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: '/home/aliare/livox_ros2_ws/build/livox_sdk_vendor/livox-sdk-v2.3.1-prefix/src/livox-sdk-v2.3.1'")
endif()

# try the clone 3 times in case there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "/usr/bin/git"  clone --no-checkout --config "advice.detachedHead=false" "https://github.com/Livox-SDK/Livox-SDK.git" "livox-sdk-v2.3.1"
    WORKING_DIRECTORY "/home/aliare/livox_ros2_ws/build/livox_sdk_vendor/livox-sdk-v2.3.1-prefix/src"
    RESULT_VARIABLE error_code
    )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once:
          ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://github.com/Livox-SDK/Livox-SDK.git'")
endif()

execute_process(
  COMMAND "/usr/bin/git"  checkout v2.3.1 --
  WORKING_DIRECTORY "/home/aliare/livox_ros2_ws/build/livox_sdk_vendor/livox-sdk-v2.3.1-prefix/src/livox-sdk-v2.3.1"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: 'v2.3.1'")
endif()

set(init_submodules TRUE)
if(init_submodules)
  execute_process(
    COMMAND "/usr/bin/git"  submodule update --recursive --init 
    WORKING_DIRECTORY "/home/aliare/livox_ros2_ws/build/livox_sdk_vendor/livox-sdk-v2.3.1-prefix/src/livox-sdk-v2.3.1"
    RESULT_VARIABLE error_code
    )
endif()
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: '/home/aliare/livox_ros2_ws/build/livox_sdk_vendor/livox-sdk-v2.3.1-prefix/src/livox-sdk-v2.3.1'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy
    "/home/aliare/livox_ros2_ws/build/livox_sdk_vendor/livox-sdk-v2.3.1-prefix/src/livox-sdk-v2.3.1-stamp/livox-sdk-v2.3.1-gitinfo.txt"
    "/home/aliare/livox_ros2_ws/build/livox_sdk_vendor/livox-sdk-v2.3.1-prefix/src/livox-sdk-v2.3.1-stamp/livox-sdk-v2.3.1-gitclone-lastrun.txt"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: '/home/aliare/livox_ros2_ws/build/livox_sdk_vendor/livox-sdk-v2.3.1-prefix/src/livox-sdk-v2.3.1-stamp/livox-sdk-v2.3.1-gitclone-lastrun.txt'")
endif()

