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
include CMakeFiles/write_batch_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/write_batch_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/write_batch_test.dir/flags.make

CMakeFiles/write_batch_test.dir/util/testharness.cc.o: CMakeFiles/write_batch_test.dir/flags.make
CMakeFiles/write_batch_test.dir/util/testharness.cc.o: ../util/testharness.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lk/learned_index/learned-leveldb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/write_batch_test.dir/util/testharness.cc.o"
	/opt/rh/devtoolset-9/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/write_batch_test.dir/util/testharness.cc.o -c /home/lk/learned_index/learned-leveldb/util/testharness.cc

CMakeFiles/write_batch_test.dir/util/testharness.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/write_batch_test.dir/util/testharness.cc.i"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lk/learned_index/learned-leveldb/util/testharness.cc > CMakeFiles/write_batch_test.dir/util/testharness.cc.i

CMakeFiles/write_batch_test.dir/util/testharness.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/write_batch_test.dir/util/testharness.cc.s"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lk/learned_index/learned-leveldb/util/testharness.cc -o CMakeFiles/write_batch_test.dir/util/testharness.cc.s

CMakeFiles/write_batch_test.dir/util/testutil.cc.o: CMakeFiles/write_batch_test.dir/flags.make
CMakeFiles/write_batch_test.dir/util/testutil.cc.o: ../util/testutil.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lk/learned_index/learned-leveldb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/write_batch_test.dir/util/testutil.cc.o"
	/opt/rh/devtoolset-9/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/write_batch_test.dir/util/testutil.cc.o -c /home/lk/learned_index/learned-leveldb/util/testutil.cc

CMakeFiles/write_batch_test.dir/util/testutil.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/write_batch_test.dir/util/testutil.cc.i"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lk/learned_index/learned-leveldb/util/testutil.cc > CMakeFiles/write_batch_test.dir/util/testutil.cc.i

CMakeFiles/write_batch_test.dir/util/testutil.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/write_batch_test.dir/util/testutil.cc.s"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lk/learned_index/learned-leveldb/util/testutil.cc -o CMakeFiles/write_batch_test.dir/util/testutil.cc.s

CMakeFiles/write_batch_test.dir/db/write_batch_test.cc.o: CMakeFiles/write_batch_test.dir/flags.make
CMakeFiles/write_batch_test.dir/db/write_batch_test.cc.o: ../db/write_batch_test.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lk/learned_index/learned-leveldb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/write_batch_test.dir/db/write_batch_test.cc.o"
	/opt/rh/devtoolset-9/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/write_batch_test.dir/db/write_batch_test.cc.o -c /home/lk/learned_index/learned-leveldb/db/write_batch_test.cc

CMakeFiles/write_batch_test.dir/db/write_batch_test.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/write_batch_test.dir/db/write_batch_test.cc.i"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lk/learned_index/learned-leveldb/db/write_batch_test.cc > CMakeFiles/write_batch_test.dir/db/write_batch_test.cc.i

CMakeFiles/write_batch_test.dir/db/write_batch_test.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/write_batch_test.dir/db/write_batch_test.cc.s"
	/opt/rh/devtoolset-9/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lk/learned_index/learned-leveldb/db/write_batch_test.cc -o CMakeFiles/write_batch_test.dir/db/write_batch_test.cc.s

# Object files for target write_batch_test
write_batch_test_OBJECTS = \
"CMakeFiles/write_batch_test.dir/util/testharness.cc.o" \
"CMakeFiles/write_batch_test.dir/util/testutil.cc.o" \
"CMakeFiles/write_batch_test.dir/db/write_batch_test.cc.o"

# External object files for target write_batch_test
write_batch_test_EXTERNAL_OBJECTS =

write_batch_test: CMakeFiles/write_batch_test.dir/util/testharness.cc.o
write_batch_test: CMakeFiles/write_batch_test.dir/util/testutil.cc.o
write_batch_test: CMakeFiles/write_batch_test.dir/db/write_batch_test.cc.o
write_batch_test: CMakeFiles/write_batch_test.dir/build.make
write_batch_test: libleveldb.a
write_batch_test: CMakeFiles/write_batch_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lk/learned_index/learned-leveldb/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable write_batch_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/write_batch_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/write_batch_test.dir/build: write_batch_test

.PHONY : CMakeFiles/write_batch_test.dir/build

CMakeFiles/write_batch_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/write_batch_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/write_batch_test.dir/clean

CMakeFiles/write_batch_test.dir/depend:
	cd /home/lk/learned_index/learned-leveldb/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lk/learned_index/learned-leveldb /home/lk/learned_index/learned-leveldb /home/lk/learned_index/learned-leveldb/build /home/lk/learned_index/learned-leveldb/build /home/lk/learned_index/learned-leveldb/build/CMakeFiles/write_batch_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/write_batch_test.dir/depend

