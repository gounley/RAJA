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
CMAKE_COMMAND = /usr/tce/packages/cmake/cmake-3.9.2/bin/cmake

# The command to remove a file.
RM = /usr/tce/packages/cmake/cmake-3.9.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA/build_lc_toss3-gcc-8.1.0

# Include any dependencies generated for this target.
include test/unit/CMakeFiles/test-view.exe.dir/depend.make

# Include the progress variables for this target.
include test/unit/CMakeFiles/test-view.exe.dir/progress.make

# Include the compile flags for this target's objects.
include test/unit/CMakeFiles/test-view.exe.dir/flags.make

test/unit/CMakeFiles/test-view.exe.dir/test-view.cpp.o: test/unit/CMakeFiles/test-view.exe.dir/flags.make
test/unit/CMakeFiles/test-view.exe.dir/test-view.cpp.o: ../test/unit/test-view.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA/build_lc_toss3-gcc-8.1.0/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/unit/CMakeFiles/test-view.exe.dir/test-view.cpp.o"
	cd /g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA/build_lc_toss3-gcc-8.1.0/test/unit && /usr/tce/packages/gcc/gcc-8.1.0/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test-view.exe.dir/test-view.cpp.o -c /g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA/test/unit/test-view.cpp

test/unit/CMakeFiles/test-view.exe.dir/test-view.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test-view.exe.dir/test-view.cpp.i"
	cd /g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA/build_lc_toss3-gcc-8.1.0/test/unit && /usr/tce/packages/gcc/gcc-8.1.0/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA/test/unit/test-view.cpp > CMakeFiles/test-view.exe.dir/test-view.cpp.i

test/unit/CMakeFiles/test-view.exe.dir/test-view.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test-view.exe.dir/test-view.cpp.s"
	cd /g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA/build_lc_toss3-gcc-8.1.0/test/unit && /usr/tce/packages/gcc/gcc-8.1.0/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA/test/unit/test-view.cpp -o CMakeFiles/test-view.exe.dir/test-view.cpp.s

test/unit/CMakeFiles/test-view.exe.dir/test-view.cpp.o.requires:

.PHONY : test/unit/CMakeFiles/test-view.exe.dir/test-view.cpp.o.requires

test/unit/CMakeFiles/test-view.exe.dir/test-view.cpp.o.provides: test/unit/CMakeFiles/test-view.exe.dir/test-view.cpp.o.requires
	$(MAKE) -f test/unit/CMakeFiles/test-view.exe.dir/build.make test/unit/CMakeFiles/test-view.exe.dir/test-view.cpp.o.provides.build
.PHONY : test/unit/CMakeFiles/test-view.exe.dir/test-view.cpp.o.provides

test/unit/CMakeFiles/test-view.exe.dir/test-view.cpp.o.provides.build: test/unit/CMakeFiles/test-view.exe.dir/test-view.cpp.o


# Object files for target test-view.exe
test__view_exe_OBJECTS = \
"CMakeFiles/test-view.exe.dir/test-view.cpp.o"

# External object files for target test-view.exe
test__view_exe_EXTERNAL_OBJECTS =

test/test-view.exe: test/unit/CMakeFiles/test-view.exe.dir/test-view.cpp.o
test/test-view.exe: test/unit/CMakeFiles/test-view.exe.dir/build.make
test/test-view.exe: lib/libgtest_main.a
test/test-view.exe: lib/libgtest.a
test/test-view.exe: lib/libRAJA.a
test/test-view.exe: test/unit/CMakeFiles/test-view.exe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA/build_lc_toss3-gcc-8.1.0/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../test-view.exe"
	cd /g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA/build_lc_toss3-gcc-8.1.0/test/unit && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test-view.exe.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/unit/CMakeFiles/test-view.exe.dir/build: test/test-view.exe

.PHONY : test/unit/CMakeFiles/test-view.exe.dir/build

test/unit/CMakeFiles/test-view.exe.dir/requires: test/unit/CMakeFiles/test-view.exe.dir/test-view.cpp.o.requires

.PHONY : test/unit/CMakeFiles/test-view.exe.dir/requires

test/unit/CMakeFiles/test-view.exe.dir/clean:
	cd /g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA/build_lc_toss3-gcc-8.1.0/test/unit && $(CMAKE_COMMAND) -P CMakeFiles/test-view.exe.dir/cmake_clean.cmake
.PHONY : test/unit/CMakeFiles/test-view.exe.dir/clean

test/unit/CMakeFiles/test-view.exe.dir/depend:
	cd /g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA/build_lc_toss3-gcc-8.1.0 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA /g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA/test/unit /g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA/build_lc_toss3-gcc-8.1.0 /g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA/build_lc_toss3-gcc-8.1.0/test/unit /g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA/build_lc_toss3-gcc-8.1.0/test/unit/CMakeFiles/test-view.exe.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/unit/CMakeFiles/test-view.exe.dir/depend

