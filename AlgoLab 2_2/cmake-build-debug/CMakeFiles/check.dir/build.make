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
CMAKE_SOURCE_DIR = "C:\Users\Zver\CLionProjects\AlgoLab 2_2"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\Zver\CLionProjects\AlgoLab 2_2\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/check.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/check.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/check.dir/flags.make

CMakeFiles/check.dir/check.cpp.obj: CMakeFiles/check.dir/flags.make
CMakeFiles/check.dir/check.cpp.obj: ../check.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\Zver\CLionProjects\AlgoLab 2_2\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/check.dir/check.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\check.dir\check.cpp.obj -c "C:\Users\Zver\CLionProjects\AlgoLab 2_2\check.cpp"

CMakeFiles/check.dir/check.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/check.dir/check.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Zver\CLionProjects\AlgoLab 2_2\check.cpp" > CMakeFiles\check.dir\check.cpp.i

CMakeFiles/check.dir/check.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/check.dir/check.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\Zver\CLionProjects\AlgoLab 2_2\check.cpp" -o CMakeFiles\check.dir\check.cpp.s

# Object files for target check
check_OBJECTS = \
"CMakeFiles/check.dir/check.cpp.obj"

# External object files for target check
check_EXTERNAL_OBJECTS =

check.exe: CMakeFiles/check.dir/check.cpp.obj
check.exe: CMakeFiles/check.dir/build.make
check.exe: CMakeFiles/check.dir/linklibs.rsp
check.exe: CMakeFiles/check.dir/objects1.rsp
check.exe: CMakeFiles/check.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\Zver\CLionProjects\AlgoLab 2_2\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable check.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\check.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/check.dir/build: check.exe

.PHONY : CMakeFiles/check.dir/build

CMakeFiles/check.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\check.dir\cmake_clean.cmake
.PHONY : CMakeFiles/check.dir/clean

CMakeFiles/check.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\Zver\CLionProjects\AlgoLab 2_2" "C:\Users\Zver\CLionProjects\AlgoLab 2_2" "C:\Users\Zver\CLionProjects\AlgoLab 2_2\cmake-build-debug" "C:\Users\Zver\CLionProjects\AlgoLab 2_2\cmake-build-debug" "C:\Users\Zver\CLionProjects\AlgoLab 2_2\cmake-build-debug\CMakeFiles\check.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/check.dir/depend

