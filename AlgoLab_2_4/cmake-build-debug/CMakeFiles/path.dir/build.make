# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2018.3.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2018.3.1\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Zver\CLionProjects\AlgoLab_2_4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Zver\CLionProjects\AlgoLab_2_4\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/path.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/path.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/path.dir/flags.make

CMakeFiles/path.dir/path.cpp.obj: CMakeFiles/path.dir/flags.make
CMakeFiles/path.dir/path.cpp.obj: ../path.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Zver\CLionProjects\AlgoLab_2_4\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/path.dir/path.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\path.dir\path.cpp.obj -c C:\Users\Zver\CLionProjects\AlgoLab_2_4\path.cpp

CMakeFiles/path.dir/path.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/path.dir/path.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Zver\CLionProjects\AlgoLab_2_4\path.cpp > CMakeFiles\path.dir\path.cpp.i

CMakeFiles/path.dir/path.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/path.dir/path.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Zver\CLionProjects\AlgoLab_2_4\path.cpp -o CMakeFiles\path.dir\path.cpp.s

# Object files for target path
path_OBJECTS = \
"CMakeFiles/path.dir/path.cpp.obj"

# External object files for target path
path_EXTERNAL_OBJECTS =

path.exe: CMakeFiles/path.dir/path.cpp.obj
path.exe: CMakeFiles/path.dir/build.make
path.exe: CMakeFiles/path.dir/linklibs.rsp
path.exe: CMakeFiles/path.dir/objects1.rsp
path.exe: CMakeFiles/path.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Zver\CLionProjects\AlgoLab_2_4\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable path.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\path.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/path.dir/build: path.exe

.PHONY : CMakeFiles/path.dir/build

CMakeFiles/path.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\path.dir\cmake_clean.cmake
.PHONY : CMakeFiles/path.dir/clean

CMakeFiles/path.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Zver\CLionProjects\AlgoLab_2_4 C:\Users\Zver\CLionProjects\AlgoLab_2_4 C:\Users\Zver\CLionProjects\AlgoLab_2_4\cmake-build-debug C:\Users\Zver\CLionProjects\AlgoLab_2_4\cmake-build-debug C:\Users\Zver\CLionProjects\AlgoLab_2_4\cmake-build-debug\CMakeFiles\path.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/path.dir/depend
