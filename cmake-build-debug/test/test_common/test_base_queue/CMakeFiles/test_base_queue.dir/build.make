# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/yunjie.shi/Documents/gitwork/relaxserver

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/yunjie.shi/Documents/gitwork/relaxserver/cmake-build-debug

# Include any dependencies generated for this target.
include test/test_common/test_base_queue/CMakeFiles/test_base_queue.dir/depend.make

# Include the progress variables for this target.
include test/test_common/test_base_queue/CMakeFiles/test_base_queue.dir/progress.make

# Include the compile flags for this target's objects.
include test/test_common/test_base_queue/CMakeFiles/test_base_queue.dir/flags.make

test/test_common/test_base_queue/CMakeFiles/test_base_queue.dir/test_base_queue.cpp.o: test/test_common/test_base_queue/CMakeFiles/test_base_queue.dir/flags.make
test/test_common/test_base_queue/CMakeFiles/test_base_queue.dir/test_base_queue.cpp.o: ../test/test_common/test_base_queue/test_base_queue.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/yunjie.shi/Documents/gitwork/relaxserver/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/test_common/test_base_queue/CMakeFiles/test_base_queue.dir/test_base_queue.cpp.o"
	cd /Users/yunjie.shi/Documents/gitwork/relaxserver/cmake-build-debug/test/test_common/test_base_queue && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_base_queue.dir/test_base_queue.cpp.o -c /Users/yunjie.shi/Documents/gitwork/relaxserver/test/test_common/test_base_queue/test_base_queue.cpp

test/test_common/test_base_queue/CMakeFiles/test_base_queue.dir/test_base_queue.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_base_queue.dir/test_base_queue.cpp.i"
	cd /Users/yunjie.shi/Documents/gitwork/relaxserver/cmake-build-debug/test/test_common/test_base_queue && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/yunjie.shi/Documents/gitwork/relaxserver/test/test_common/test_base_queue/test_base_queue.cpp > CMakeFiles/test_base_queue.dir/test_base_queue.cpp.i

test/test_common/test_base_queue/CMakeFiles/test_base_queue.dir/test_base_queue.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_base_queue.dir/test_base_queue.cpp.s"
	cd /Users/yunjie.shi/Documents/gitwork/relaxserver/cmake-build-debug/test/test_common/test_base_queue && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/yunjie.shi/Documents/gitwork/relaxserver/test/test_common/test_base_queue/test_base_queue.cpp -o CMakeFiles/test_base_queue.dir/test_base_queue.cpp.s

test/test_common/test_base_queue/CMakeFiles/test_base_queue.dir/test_base_queue.cpp.o.requires:

.PHONY : test/test_common/test_base_queue/CMakeFiles/test_base_queue.dir/test_base_queue.cpp.o.requires

test/test_common/test_base_queue/CMakeFiles/test_base_queue.dir/test_base_queue.cpp.o.provides: test/test_common/test_base_queue/CMakeFiles/test_base_queue.dir/test_base_queue.cpp.o.requires
	$(MAKE) -f test/test_common/test_base_queue/CMakeFiles/test_base_queue.dir/build.make test/test_common/test_base_queue/CMakeFiles/test_base_queue.dir/test_base_queue.cpp.o.provides.build
.PHONY : test/test_common/test_base_queue/CMakeFiles/test_base_queue.dir/test_base_queue.cpp.o.provides

test/test_common/test_base_queue/CMakeFiles/test_base_queue.dir/test_base_queue.cpp.o.provides.build: test/test_common/test_base_queue/CMakeFiles/test_base_queue.dir/test_base_queue.cpp.o


# Object files for target test_base_queue
test_base_queue_OBJECTS = \
"CMakeFiles/test_base_queue.dir/test_base_queue.cpp.o"

# External object files for target test_base_queue
test_base_queue_EXTERNAL_OBJECTS =

test/test_common/test_base_queue/test_base_queue: test/test_common/test_base_queue/CMakeFiles/test_base_queue.dir/test_base_queue.cpp.o
test/test_common/test_base_queue/test_base_queue: test/test_common/test_base_queue/CMakeFiles/test_base_queue.dir/build.make
test/test_common/test_base_queue/test_base_queue: test/test_common/test_base_queue/CMakeFiles/test_base_queue.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/yunjie.shi/Documents/gitwork/relaxserver/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_base_queue"
	cd /Users/yunjie.shi/Documents/gitwork/relaxserver/cmake-build-debug/test/test_common/test_base_queue && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_base_queue.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/test_common/test_base_queue/CMakeFiles/test_base_queue.dir/build: test/test_common/test_base_queue/test_base_queue

.PHONY : test/test_common/test_base_queue/CMakeFiles/test_base_queue.dir/build

test/test_common/test_base_queue/CMakeFiles/test_base_queue.dir/requires: test/test_common/test_base_queue/CMakeFiles/test_base_queue.dir/test_base_queue.cpp.o.requires

.PHONY : test/test_common/test_base_queue/CMakeFiles/test_base_queue.dir/requires

test/test_common/test_base_queue/CMakeFiles/test_base_queue.dir/clean:
	cd /Users/yunjie.shi/Documents/gitwork/relaxserver/cmake-build-debug/test/test_common/test_base_queue && $(CMAKE_COMMAND) -P CMakeFiles/test_base_queue.dir/cmake_clean.cmake
.PHONY : test/test_common/test_base_queue/CMakeFiles/test_base_queue.dir/clean

test/test_common/test_base_queue/CMakeFiles/test_base_queue.dir/depend:
	cd /Users/yunjie.shi/Documents/gitwork/relaxserver/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/yunjie.shi/Documents/gitwork/relaxserver /Users/yunjie.shi/Documents/gitwork/relaxserver/test/test_common/test_base_queue /Users/yunjie.shi/Documents/gitwork/relaxserver/cmake-build-debug /Users/yunjie.shi/Documents/gitwork/relaxserver/cmake-build-debug/test/test_common/test_base_queue /Users/yunjie.shi/Documents/gitwork/relaxserver/cmake-build-debug/test/test_common/test_base_queue/CMakeFiles/test_base_queue.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/test_common/test_base_queue/CMakeFiles/test_base_queue.dir/depend
