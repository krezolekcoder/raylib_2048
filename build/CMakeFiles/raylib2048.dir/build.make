# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.28.3/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.28.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/krezo/Programming/krezolekcoder/raylib_2048

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/krezo/Programming/krezolekcoder/raylib_2048/build

# Include any dependencies generated for this target.
include CMakeFiles/raylib2048.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/raylib2048.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/raylib2048.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/raylib2048.dir/flags.make

CMakeFiles/raylib2048.dir/src/main.c.o: CMakeFiles/raylib2048.dir/flags.make
CMakeFiles/raylib2048.dir/src/main.c.o: /Users/krezo/Programming/krezolekcoder/raylib_2048/src/main.c
CMakeFiles/raylib2048.dir/src/main.c.o: CMakeFiles/raylib2048.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/krezo/Programming/krezolekcoder/raylib_2048/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/raylib2048.dir/src/main.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/raylib2048.dir/src/main.c.o -MF CMakeFiles/raylib2048.dir/src/main.c.o.d -o CMakeFiles/raylib2048.dir/src/main.c.o -c /Users/krezo/Programming/krezolekcoder/raylib_2048/src/main.c

CMakeFiles/raylib2048.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/raylib2048.dir/src/main.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/krezo/Programming/krezolekcoder/raylib_2048/src/main.c > CMakeFiles/raylib2048.dir/src/main.c.i

CMakeFiles/raylib2048.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/raylib2048.dir/src/main.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/krezo/Programming/krezolekcoder/raylib_2048/src/main.c -o CMakeFiles/raylib2048.dir/src/main.c.s

CMakeFiles/raylib2048.dir/src/platform_port.c.o: CMakeFiles/raylib2048.dir/flags.make
CMakeFiles/raylib2048.dir/src/platform_port.c.o: /Users/krezo/Programming/krezolekcoder/raylib_2048/src/platform_port.c
CMakeFiles/raylib2048.dir/src/platform_port.c.o: CMakeFiles/raylib2048.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/krezo/Programming/krezolekcoder/raylib_2048/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/raylib2048.dir/src/platform_port.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/raylib2048.dir/src/platform_port.c.o -MF CMakeFiles/raylib2048.dir/src/platform_port.c.o.d -o CMakeFiles/raylib2048.dir/src/platform_port.c.o -c /Users/krezo/Programming/krezolekcoder/raylib_2048/src/platform_port.c

CMakeFiles/raylib2048.dir/src/platform_port.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/raylib2048.dir/src/platform_port.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/krezo/Programming/krezolekcoder/raylib_2048/src/platform_port.c > CMakeFiles/raylib2048.dir/src/platform_port.c.i

CMakeFiles/raylib2048.dir/src/platform_port.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/raylib2048.dir/src/platform_port.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/krezo/Programming/krezolekcoder/raylib_2048/src/platform_port.c -o CMakeFiles/raylib2048.dir/src/platform_port.c.s

CMakeFiles/raylib2048.dir/src/core_2048.c.o: CMakeFiles/raylib2048.dir/flags.make
CMakeFiles/raylib2048.dir/src/core_2048.c.o: /Users/krezo/Programming/krezolekcoder/raylib_2048/src/core_2048.c
CMakeFiles/raylib2048.dir/src/core_2048.c.o: CMakeFiles/raylib2048.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/krezo/Programming/krezolekcoder/raylib_2048/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/raylib2048.dir/src/core_2048.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/raylib2048.dir/src/core_2048.c.o -MF CMakeFiles/raylib2048.dir/src/core_2048.c.o.d -o CMakeFiles/raylib2048.dir/src/core_2048.c.o -c /Users/krezo/Programming/krezolekcoder/raylib_2048/src/core_2048.c

CMakeFiles/raylib2048.dir/src/core_2048.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/raylib2048.dir/src/core_2048.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/krezo/Programming/krezolekcoder/raylib_2048/src/core_2048.c > CMakeFiles/raylib2048.dir/src/core_2048.c.i

CMakeFiles/raylib2048.dir/src/core_2048.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/raylib2048.dir/src/core_2048.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/krezo/Programming/krezolekcoder/raylib_2048/src/core_2048.c -o CMakeFiles/raylib2048.dir/src/core_2048.c.s

# Object files for target raylib2048
raylib2048_OBJECTS = \
"CMakeFiles/raylib2048.dir/src/main.c.o" \
"CMakeFiles/raylib2048.dir/src/platform_port.c.o" \
"CMakeFiles/raylib2048.dir/src/core_2048.c.o"

# External object files for target raylib2048
raylib2048_EXTERNAL_OBJECTS =

raylib2048: CMakeFiles/raylib2048.dir/src/main.c.o
raylib2048: CMakeFiles/raylib2048.dir/src/platform_port.c.o
raylib2048: CMakeFiles/raylib2048.dir/src/core_2048.c.o
raylib2048: CMakeFiles/raylib2048.dir/build.make
raylib2048: /opt/homebrew/lib/libraylib.dylib
raylib2048: CMakeFiles/raylib2048.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/krezo/Programming/krezolekcoder/raylib_2048/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable raylib2048"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/raylib2048.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/raylib2048.dir/build: raylib2048
.PHONY : CMakeFiles/raylib2048.dir/build

CMakeFiles/raylib2048.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/raylib2048.dir/cmake_clean.cmake
.PHONY : CMakeFiles/raylib2048.dir/clean

CMakeFiles/raylib2048.dir/depend:
	cd /Users/krezo/Programming/krezolekcoder/raylib_2048/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/krezo/Programming/krezolekcoder/raylib_2048 /Users/krezo/Programming/krezolekcoder/raylib_2048 /Users/krezo/Programming/krezolekcoder/raylib_2048/build /Users/krezo/Programming/krezolekcoder/raylib_2048/build /Users/krezo/Programming/krezolekcoder/raylib_2048/build/CMakeFiles/raylib2048.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/raylib2048.dir/depend
