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
include exercises/CMakeFiles/ex_2_dot-product.dir/depend.make

# Include the progress variables for this target.
include exercises/CMakeFiles/ex_2_dot-product.dir/progress.make

# Include the compile flags for this target's objects.
include exercises/CMakeFiles/ex_2_dot-product.dir/flags.make

exercises/CMakeFiles/ex_2_dot-product.dir/ex_2_dot-product.cpp.o: exercises/CMakeFiles/ex_2_dot-product.dir/flags.make
exercises/CMakeFiles/ex_2_dot-product.dir/ex_2_dot-product.cpp.o: ../exercises/ex_2_dot-product.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA/build_lc_toss3-gcc-8.1.0/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object exercises/CMakeFiles/ex_2_dot-product.dir/ex_2_dot-product.cpp.o"
	cd /g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA/build_lc_toss3-gcc-8.1.0/exercises && /usr/tce/packages/gcc/gcc-8.1.0/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ex_2_dot-product.dir/ex_2_dot-product.cpp.o -c /g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA/exercises/ex_2_dot-product.cpp

exercises/CMakeFiles/ex_2_dot-product.dir/ex_2_dot-product.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ex_2_dot-product.dir/ex_2_dot-product.cpp.i"
	cd /g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA/build_lc_toss3-gcc-8.1.0/exercises && /usr/tce/packages/gcc/gcc-8.1.0/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA/exercises/ex_2_dot-product.cpp > CMakeFiles/ex_2_dot-product.dir/ex_2_dot-product.cpp.i

exercises/CMakeFiles/ex_2_dot-product.dir/ex_2_dot-product.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ex_2_dot-product.dir/ex_2_dot-product.cpp.s"
	cd /g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA/build_lc_toss3-gcc-8.1.0/exercises && /usr/tce/packages/gcc/gcc-8.1.0/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA/exercises/ex_2_dot-product.cpp -o CMakeFiles/ex_2_dot-product.dir/ex_2_dot-product.cpp.s

exercises/CMakeFiles/ex_2_dot-product.dir/ex_2_dot-product.cpp.o.requires:

.PHONY : exercises/CMakeFiles/ex_2_dot-product.dir/ex_2_dot-product.cpp.o.requires

exercises/CMakeFiles/ex_2_dot-product.dir/ex_2_dot-product.cpp.o.provides: exercises/CMakeFiles/ex_2_dot-product.dir/ex_2_dot-product.cpp.o.requires
	$(MAKE) -f exercises/CMakeFiles/ex_2_dot-product.dir/build.make exercises/CMakeFiles/ex_2_dot-product.dir/ex_2_dot-product.cpp.o.provides.build
.PHONY : exercises/CMakeFiles/ex_2_dot-product.dir/ex_2_dot-product.cpp.o.provides

exercises/CMakeFiles/ex_2_dot-product.dir/ex_2_dot-product.cpp.o.provides.build: exercises/CMakeFiles/ex_2_dot-product.dir/ex_2_dot-product.cpp.o


# Object files for target ex_2_dot-product
ex_2_dot__product_OBJECTS = \
"CMakeFiles/ex_2_dot-product.dir/ex_2_dot-product.cpp.o"

# External object files for target ex_2_dot-product
ex_2_dot__product_EXTERNAL_OBJECTS =

bin/ex_2_dot-product: exercises/CMakeFiles/ex_2_dot-product.dir/ex_2_dot-product.cpp.o
bin/ex_2_dot-product: exercises/CMakeFiles/ex_2_dot-product.dir/build.make
bin/ex_2_dot-product: lib/libRAJA.a
bin/ex_2_dot-product: exercises/CMakeFiles/ex_2_dot-product.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA/build_lc_toss3-gcc-8.1.0/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/ex_2_dot-product"
	cd /g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA/build_lc_toss3-gcc-8.1.0/exercises && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ex_2_dot-product.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
exercises/CMakeFiles/ex_2_dot-product.dir/build: bin/ex_2_dot-product

.PHONY : exercises/CMakeFiles/ex_2_dot-product.dir/build

exercises/CMakeFiles/ex_2_dot-product.dir/requires: exercises/CMakeFiles/ex_2_dot-product.dir/ex_2_dot-product.cpp.o.requires

.PHONY : exercises/CMakeFiles/ex_2_dot-product.dir/requires

exercises/CMakeFiles/ex_2_dot-product.dir/clean:
	cd /g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA/build_lc_toss3-gcc-8.1.0/exercises && $(CMAKE_COMMAND) -P CMakeFiles/ex_2_dot-product.dir/cmake_clean.cmake
.PHONY : exercises/CMakeFiles/ex_2_dot-product.dir/clean

exercises/CMakeFiles/ex_2_dot-product.dir/depend:
	cd /g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA/build_lc_toss3-gcc-8.1.0 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA /g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA/exercises /g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA/build_lc_toss3-gcc-8.1.0 /g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA/build_lc_toss3-gcc-8.1.0/exercises /g/g16/hornung1/AASD/RAJA-repo/raja-WORK/RAJA/build_lc_toss3-gcc-8.1.0/exercises/CMakeFiles/ex_2_dot-product.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : exercises/CMakeFiles/ex_2_dot-product.dir/depend

