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
CMAKE_SOURCE_DIR = /s/chopin/g/under/rileyr3/ct301/hw5

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /s/chopin/g/under/rileyr3/ct301/hw5

# Include any dependencies generated for this target.
include CMakeFiles/game_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/game_test.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/game_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/game_test.dir/flags.make

CMakeFiles/game_test.dir/game_test.cc.o: CMakeFiles/game_test.dir/flags.make
CMakeFiles/game_test.dir/game_test.cc.o: game_test.cc
CMakeFiles/game_test.dir/game_test.cc.o: CMakeFiles/game_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/s/chopin/g/under/rileyr3/ct301/hw5/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/game_test.dir/game_test.cc.o"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/game_test.dir/game_test.cc.o -MF CMakeFiles/game_test.dir/game_test.cc.o.d -o CMakeFiles/game_test.dir/game_test.cc.o -c /s/chopin/g/under/rileyr3/ct301/hw5/game_test.cc

CMakeFiles/game_test.dir/game_test.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/game_test.dir/game_test.cc.i"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /s/chopin/g/under/rileyr3/ct301/hw5/game_test.cc > CMakeFiles/game_test.dir/game_test.cc.i

CMakeFiles/game_test.dir/game_test.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/game_test.dir/game_test.cc.s"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /s/chopin/g/under/rileyr3/ct301/hw5/game_test.cc -o CMakeFiles/game_test.dir/game_test.cc.s

# Object files for target game_test
game_test_OBJECTS = \
"CMakeFiles/game_test.dir/game_test.cc.o"

# External object files for target game_test
game_test_EXTERNAL_OBJECTS =

game_test: CMakeFiles/game_test.dir/game_test.cc.o
game_test: CMakeFiles/game_test.dir/build.make
game_test: libHW5.a
game_test: CMakeFiles/game_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/s/chopin/g/under/rileyr3/ct301/hw5/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable game_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/game_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/game_test.dir/build: game_test
.PHONY : CMakeFiles/game_test.dir/build

CMakeFiles/game_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/game_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/game_test.dir/clean

CMakeFiles/game_test.dir/depend:
	cd /s/chopin/g/under/rileyr3/ct301/hw5 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /s/chopin/g/under/rileyr3/ct301/hw5 /s/chopin/g/under/rileyr3/ct301/hw5 /s/chopin/g/under/rileyr3/ct301/hw5 /s/chopin/g/under/rileyr3/ct301/hw5 /s/chopin/g/under/rileyr3/ct301/hw5/CMakeFiles/game_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/game_test.dir/depend

