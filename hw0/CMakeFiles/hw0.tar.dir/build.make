# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_SOURCE_DIR = /s/chopin/g/under/rileyr3/ct301/hw0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /s/chopin/g/under/rileyr3/ct301/hw0

# Utility rule file for hw0.tar.

# Include any custom commands dependencies for this target.
include CMakeFiles/hw0.tar.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/hw0.tar.dir/progress.make

CMakeFiles/hw0.tar:
	tar -cf hw0.tar *.cc CMakeLists.txt

hw0.tar: CMakeFiles/hw0.tar
hw0.tar: CMakeFiles/hw0.tar.dir/build.make
.PHONY : hw0.tar

# Rule to build all files generated by this target.
CMakeFiles/hw0.tar.dir/build: hw0.tar
.PHONY : CMakeFiles/hw0.tar.dir/build

CMakeFiles/hw0.tar.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/hw0.tar.dir/cmake_clean.cmake
.PHONY : CMakeFiles/hw0.tar.dir/clean

CMakeFiles/hw0.tar.dir/depend:
	cd /s/chopin/g/under/rileyr3/ct301/hw0 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /s/chopin/g/under/rileyr3/ct301/hw0 /s/chopin/g/under/rileyr3/ct301/hw0 /s/chopin/g/under/rileyr3/ct301/hw0 /s/chopin/g/under/rileyr3/ct301/hw0 /s/chopin/g/under/rileyr3/ct301/hw0/CMakeFiles/hw0.tar.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/hw0.tar.dir/depend

