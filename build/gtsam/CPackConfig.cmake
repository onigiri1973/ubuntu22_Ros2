# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


set(CPACK_BUILD_SOURCE_DIRS "/home/aliare/livox_ros2_ws/src/gtsam;/home/aliare/livox_ros2_ws/build/gtsam")
set(CPACK_CMAKE_GENERATOR "Unix Makefiles")
set(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
set(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libboost-dev (>= 1.65)")
set(CPACK_DEBIAN_PACKAGE_NAME "libgtsam-dev")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_FILE "/usr/share/cmake-3.22/Templates/CPack.GenericDescription.txt")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_SUMMARY "GTSAM built using CMake")
set(CPACK_GENERATOR "TGZ")
set(CPACK_INSTALL_CMAKE_PROJECTS "/home/aliare/livox_ros2_ws/build/gtsam;GTSAM;ALL;/")
set(CPACK_INSTALL_PREFIX "/home/aliare/livox_ros2_ws/install/gtsam")
set(CPACK_MODULE_PATH ";/home/aliare/livox_ros2_ws/src/gtsam/cmake")
set(CPACK_NSIS_DISPLAY_NAME "CMake .")
set(CPACK_NSIS_INSTALLER_ICON_CODE "")
set(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES")
set(CPACK_NSIS_PACKAGE_NAME "CMake .")
set(CPACK_NSIS_UNINSTALL_NAME "Uninstall")
set(CPACK_OUTPUT_CONFIG_FILE "/home/aliare/livox_ros2_ws/build/gtsam/CPackConfig.cmake")
set(CPACK_PACKAGE_CONTACT "Frank Dellaert, dellaert@cc.gatech.edu")
set(CPACK_PACKAGE_DEFAULT_LOCATION "/")
set(CPACK_PACKAGE_DESCRIPTION_FILE "/home/aliare/livox_ros2_ws/src/gtsam/README.md")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "GTSAM")
set(CPACK_PACKAGE_FILE_NAME "GTSAM-4.3.0-Linux")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "CMake .")
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "CMake .")
set(CPACK_PACKAGE_NAME "GTSAM")
set(CPACK_PACKAGE_RELOCATABLE "true")
set(CPACK_PACKAGE_VENDOR "Frank Dellaert, Georgia Institute of Technology")
set(CPACK_PACKAGE_VERSION "4.3.0")
set(CPACK_PACKAGE_VERSION_MAJOR "4")
set(CPACK_PACKAGE_VERSION_MINOR "3")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_RESOURCE_FILE_LICENSE "/home/aliare/livox_ros2_ws/src/gtsam/LICENSE")
set(CPACK_RESOURCE_FILE_README "/usr/share/cmake-3.22/Templates/CPack.GenericDescription.txt")
set(CPACK_RESOURCE_FILE_WELCOME "/usr/share/cmake-3.22/Templates/CPack.GenericWelcome.txt")
set(CPACK_SET_DESTDIR "OFF")
set(CPACK_SOURCE_GENERATOR "TGZ")
set(CPACK_SOURCE_IGNORE_FILES "/build*;/\\.;/makestats.sh$;/gtsam_unstable/;/package_scripts/")
set(CPACK_SOURCE_OUTPUT_CONFIG_FILE "/home/aliare/livox_ros2_ws/build/gtsam/CPackSourceConfig.cmake")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "gtsam-4.3.0")
set(CPACK_SYSTEM_NAME "Linux")
set(CPACK_THREADS "1")
set(CPACK_TOPLEVEL_TAG "Linux")
set(CPACK_WIX_SIZEOF_VOID_P "8")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "/home/aliare/livox_ros2_ws/build/gtsam/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()
