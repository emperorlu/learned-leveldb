# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake3

# The command to remove a file.
RM = /usr/bin/cmake3 -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lk/learned_index/learned-leveldb

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lk/learned_index/learned-leveldb/build

# Include any dependencies generated for this target.
include CMakeFiles/env_posix_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/env_posix_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/env_posix_test.dir/flags.make

CMakeFiles/env_posix_test.dir/util/testharness.cc.o: CMakeFiles/env_posix_test.dir/flags.make
CMakeFiles/env_posix_test.dir/util/testharness.cc.o: ../util/testharness.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lk/learned_index/learned-leveldb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/env_posix_test.dir/util/testharness.cc.o"
	/opt/rh/devtoolset-9/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/env_posix_test.dir/util/testharness.cc.o -c /home/lk/learned_index/learned-leveldb/util/testharness.cc

CMakeFiles/env_posix_test.dir/util/testharness.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/env_posix_test.dir/util/testharness.cc.i"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lk/learned_index/learned-leveldb/util/testharness.cc > CMakeFiles/env_posix_test.dir/util/testharness.cc.i

CMakeFiles/env_posix_test.dir/util/testharness.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/env_posix_test.dir/util/testharness.cc.s"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lk/learned_index/learned-leveldb/util/testharness.cc -o CMakeFiles/env_posix_test.dir/util/testharness.cc.s

CMakeFiles/env_posix_test.dir/util/testutil.cc.o: CMakeFiles/env_posix_test.dir/flags.make
CMakeFiles/env_posix_test.dir/util/testutil.cc.o: ../util/testutil.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lk/learned_index/learned-leveldb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/env_posix_test.dir/util/testutil.cc.o"
	/opt/rh/devtoolset-9/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/env_posix_test.dir/util/testutil.cc.o -c /home/lk/learned_index/learned-leveldb/util/testutil.cc

CMakeFiles/env_posix_test.dir/util/testutil.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/env_posix_test.dir/util/testutil.cc.i"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lk/learned_index/learned-leveldb/util/testutil.cc > CMakeFiles/env_posix_test.dir/util/testutil.cc.i

CMakeFiles/env_posix_test.dir/util/testutil.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/env_posix_test.dir/util/testutil.cc.s"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lk/learned_index/learned-leveldb/util/testutil.cc -o CMakeFiles/env_posix_test.dir/util/testutil.cc.s

CMakeFiles/env_posix_test.dir/util/env_posix_test.cc.o: CMakeFiles/env_posix_test.dir/flags.make
CMakeFiles/env_posix_test.dir/util/env_posix_test.cc.o: ../util/env_posix_test.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lk/learned_index/learned-leveldb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/env_posix_test.dir/util/env_posix_test.cc.o"
	/opt/rh/devtoolset-9/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/env_posix_test.dir/util/env_posix_test.cc.o -c /home/lk/learned_index/learned-leveldb/util/env_posix_test.cc

CMakeFiles/env_posix_test.dir/util/env_posix_test.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/env_posix_test.dir/util/env_posix_test.cc.i"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lk/learned_index/learned-leveldb/util/env_posix_test.cc > CMakeFiles/env_posix_test.dir/util/env_posix_test.cc.i

CMakeFiles/env_posix_test.dir/util/env_posix_test.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/env_posix_test.dir/util/env_posix_test.cc.s"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lk/learned_index/learned-leveldb/util/env_posix_test.cc -o CMakeFiles/env_posix_test.dir/util/env_posix_test.cc.s

# Object files for target env_posix_test
env_posix_test_OBJECTS = \
"CMakeFiles/env_posix_test.dir/util/testharness.cc.o" \
"CMakeFiles/env_posix_test.dir/util/testutil.cc.o" \
"CMakeFiles/env_posix_test.dir/util/env_posix_test.cc.o"

# External object files for target env_posix_test
env_posix_test_EXTERNAL_OBJECTS =

env_posix_test: CMakeFiles/env_posix_test.dir/util/testharness.cc.o
env_posix_test: CMakeFiles/env_posix_test.dir/util/testutil.cc.o
env_posix_test: CMakeFiles/env_posix_test.dir/util/env_posix_test.cc.o
env_posix_test: CMakeFiles/env_posix_test.dir/build.make
env_posix_test: libleveldb.a
env_posix_test: CMakeFiles/env_posix_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lk/learned_index/learned-leveldb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable env_posix_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/env_posix_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/env_posix_test.dir/build: env_posix_test

.PHONY : CMakeFiles/env_posix_test.dir/build

CMakeFiles/env_posix_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/env_posix_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/env_posix_test.dir/clean

CMakeFiles/env_posix_test.dir/depend:
	cd /home/lk/learned_index/learned-leveldb/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lk/learned_index/learned-leveldb /home/lk/learned_index/learned-leveldb /home/lk/learned_index/learned-leveldb/build /home/lk/learned_index/learned-leveldb/build /home/lk/learned_index/learned-leveldb/build/CMakeFiles/env_posix_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/env_posix_test.dir/depend

