# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.5

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = D:\Cmake-3.5.2\bin\cmake.exe

# The command to remove a file.
RM = D:\Cmake-3.5.2\bin\cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = E:\Workspace\git_repo\lib\curl-7.49.1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\Workspace\git_repo\lib\curl-7.49.1-build

# Include any dependencies generated for this target.
include tests/libtest/CMakeFiles/lib510.dir/depend.make

# Include the progress variables for this target.
include tests/libtest/CMakeFiles/lib510.dir/progress.make

# Include the compile flags for this target's objects.
include tests/libtest/CMakeFiles/lib510.dir/flags.make

tests/libtest/CMakeFiles/lib510.dir/lib510.c.obj: tests/libtest/CMakeFiles/lib510.dir/flags.make
tests/libtest/CMakeFiles/lib510.dir/lib510.c.obj: tests/libtest/CMakeFiles/lib510.dir/includes_C.rsp
tests/libtest/CMakeFiles/lib510.dir/lib510.c.obj: E:/Workspace/git_repo/lib/curl-7.49.1/tests/libtest/lib510.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\Workspace\git_repo\lib\curl-7.49.1-build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/libtest/CMakeFiles/lib510.dir/lib510.c.obj"
	cd /d E:\Workspace\git_repo\lib\curl-7.49.1-build\tests\libtest && D:\CodeBlocks\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\lib510.dir\lib510.c.obj   -c E:\Workspace\git_repo\lib\curl-7.49.1\tests\libtest\lib510.c

tests/libtest/CMakeFiles/lib510.dir/lib510.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lib510.dir/lib510.c.i"
	cd /d E:\Workspace\git_repo\lib\curl-7.49.1-build\tests\libtest && D:\CodeBlocks\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E E:\Workspace\git_repo\lib\curl-7.49.1\tests\libtest\lib510.c > CMakeFiles\lib510.dir\lib510.c.i

tests/libtest/CMakeFiles/lib510.dir/lib510.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lib510.dir/lib510.c.s"
	cd /d E:\Workspace\git_repo\lib\curl-7.49.1-build\tests\libtest && D:\CodeBlocks\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S E:\Workspace\git_repo\lib\curl-7.49.1\tests\libtest\lib510.c -o CMakeFiles\lib510.dir\lib510.c.s

tests/libtest/CMakeFiles/lib510.dir/lib510.c.obj.requires:

.PHONY : tests/libtest/CMakeFiles/lib510.dir/lib510.c.obj.requires

tests/libtest/CMakeFiles/lib510.dir/lib510.c.obj.provides: tests/libtest/CMakeFiles/lib510.dir/lib510.c.obj.requires
	$(MAKE) -f tests\libtest\CMakeFiles\lib510.dir\build.make tests/libtest/CMakeFiles/lib510.dir/lib510.c.obj.provides.build
.PHONY : tests/libtest/CMakeFiles/lib510.dir/lib510.c.obj.provides

tests/libtest/CMakeFiles/lib510.dir/lib510.c.obj.provides.build: tests/libtest/CMakeFiles/lib510.dir/lib510.c.obj


tests/libtest/CMakeFiles/lib510.dir/first.c.obj: tests/libtest/CMakeFiles/lib510.dir/flags.make
tests/libtest/CMakeFiles/lib510.dir/first.c.obj: tests/libtest/CMakeFiles/lib510.dir/includes_C.rsp
tests/libtest/CMakeFiles/lib510.dir/first.c.obj: E:/Workspace/git_repo/lib/curl-7.49.1/tests/libtest/first.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\Workspace\git_repo\lib\curl-7.49.1-build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object tests/libtest/CMakeFiles/lib510.dir/first.c.obj"
	cd /d E:\Workspace\git_repo\lib\curl-7.49.1-build\tests\libtest && D:\CodeBlocks\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\lib510.dir\first.c.obj   -c E:\Workspace\git_repo\lib\curl-7.49.1\tests\libtest\first.c

tests/libtest/CMakeFiles/lib510.dir/first.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lib510.dir/first.c.i"
	cd /d E:\Workspace\git_repo\lib\curl-7.49.1-build\tests\libtest && D:\CodeBlocks\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E E:\Workspace\git_repo\lib\curl-7.49.1\tests\libtest\first.c > CMakeFiles\lib510.dir\first.c.i

tests/libtest/CMakeFiles/lib510.dir/first.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lib510.dir/first.c.s"
	cd /d E:\Workspace\git_repo\lib\curl-7.49.1-build\tests\libtest && D:\CodeBlocks\MinGW\bin\gcc.exe  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S E:\Workspace\git_repo\lib\curl-7.49.1\tests\libtest\first.c -o CMakeFiles\lib510.dir\first.c.s

tests/libtest/CMakeFiles/lib510.dir/first.c.obj.requires:

.PHONY : tests/libtest/CMakeFiles/lib510.dir/first.c.obj.requires

tests/libtest/CMakeFiles/lib510.dir/first.c.obj.provides: tests/libtest/CMakeFiles/lib510.dir/first.c.obj.requires
	$(MAKE) -f tests\libtest\CMakeFiles\lib510.dir\build.make tests/libtest/CMakeFiles/lib510.dir/first.c.obj.provides.build
.PHONY : tests/libtest/CMakeFiles/lib510.dir/first.c.obj.provides

tests/libtest/CMakeFiles/lib510.dir/first.c.obj.provides.build: tests/libtest/CMakeFiles/lib510.dir/first.c.obj


# Object files for target lib510
lib510_OBJECTS = \
"CMakeFiles/lib510.dir/lib510.c.obj" \
"CMakeFiles/lib510.dir/first.c.obj"

# External object files for target lib510
lib510_EXTERNAL_OBJECTS =

tests/libtest/lib510.exe: tests/libtest/CMakeFiles/lib510.dir/lib510.c.obj
tests/libtest/lib510.exe: tests/libtest/CMakeFiles/lib510.dir/first.c.obj
tests/libtest/lib510.exe: tests/libtest/CMakeFiles/lib510.dir/build.make
tests/libtest/lib510.exe: lib/libcurl_imp.lib
tests/libtest/lib510.exe: tests/libtest/CMakeFiles/lib510.dir/linklibs.rsp
tests/libtest/lib510.exe: tests/libtest/CMakeFiles/lib510.dir/objects1.rsp
tests/libtest/lib510.exe: tests/libtest/CMakeFiles/lib510.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\Workspace\git_repo\lib\curl-7.49.1-build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable lib510.exe"
	cd /d E:\Workspace\git_repo\lib\curl-7.49.1-build\tests\libtest && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\lib510.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/libtest/CMakeFiles/lib510.dir/build: tests/libtest/lib510.exe

.PHONY : tests/libtest/CMakeFiles/lib510.dir/build

tests/libtest/CMakeFiles/lib510.dir/requires: tests/libtest/CMakeFiles/lib510.dir/lib510.c.obj.requires
tests/libtest/CMakeFiles/lib510.dir/requires: tests/libtest/CMakeFiles/lib510.dir/first.c.obj.requires

.PHONY : tests/libtest/CMakeFiles/lib510.dir/requires

tests/libtest/CMakeFiles/lib510.dir/clean:
	cd /d E:\Workspace\git_repo\lib\curl-7.49.1-build\tests\libtest && $(CMAKE_COMMAND) -P CMakeFiles\lib510.dir\cmake_clean.cmake
.PHONY : tests/libtest/CMakeFiles/lib510.dir/clean

tests/libtest/CMakeFiles/lib510.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\Workspace\git_repo\lib\curl-7.49.1 E:\Workspace\git_repo\lib\curl-7.49.1\tests\libtest E:\Workspace\git_repo\lib\curl-7.49.1-build E:\Workspace\git_repo\lib\curl-7.49.1-build\tests\libtest E:\Workspace\git_repo\lib\curl-7.49.1-build\tests\libtest\CMakeFiles\lib510.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : tests/libtest/CMakeFiles/lib510.dir/depend
