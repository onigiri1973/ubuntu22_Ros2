# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/aliare/livox_ros2_ws/src/gtsam

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/aliare/livox_ros2_ws/build/gtsam

# Utility rule file for testMFAS.run.

# Include any custom commands dependencies for this target.
include gtsam/sfm/tests/CMakeFiles/testMFAS.run.dir/compiler_depend.make

# Include the progress variables for this target.
include gtsam/sfm/tests/CMakeFiles/testMFAS.run.dir/progress.make

gtsam/sfm/tests/CMakeFiles/testMFAS.run: gtsam/sfm/tests/testMFAS
	cd /home/aliare/livox_ros2_ws/build/gtsam/gtsam/sfm/tests && ./testMFAS

testMFAS.run: gtsam/sfm/tests/CMakeFiles/testMFAS.run
testMFAS.run: gtsam/sfm/tests/CMakeFiles/testMFAS.run.dir/build.make
.PHONY : testMFAS.run

# Rule to build all files generated by this target.
gtsam/sfm/tests/CMakeFiles/testMFAS.run.dir/build: testMFAS.run
.PHONY : gtsam/sfm/tests/CMakeFiles/testMFAS.run.dir/build

gtsam/sfm/tests/CMakeFiles/testMFAS.run.dir/clean:
	cd /home/aliare/livox_ros2_ws/build/gtsam/gtsam/sfm/tests && $(CMAKE_COMMAND) -P CMakeFiles/testMFAS.run.dir/cmake_clean.cmake
.PHONY : gtsam/sfm/tests/CMakeFiles/testMFAS.run.dir/clean

gtsam/sfm/tests/CMakeFiles/testMFAS.run.dir/depend:
	cd /home/aliare/livox_ros2_ws/build/gtsam && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/aliare/livox_ros2_ws/src/gtsam /home/aliare/livox_ros2_ws/src/gtsam/gtsam/sfm/tests /home/aliare/livox_ros2_ws/build/gtsam /home/aliare/livox_ros2_ws/build/gtsam/gtsam/sfm/tests /home/aliare/livox_ros2_ws/build/gtsam/gtsam/sfm/tests/CMakeFiles/testMFAS.run.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : gtsam/sfm/tests/CMakeFiles/testMFAS.run.dir/depend

