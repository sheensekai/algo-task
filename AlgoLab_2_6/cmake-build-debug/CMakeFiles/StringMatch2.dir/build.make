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
CMAKE_SOURCE_DIR = C:\Users\Zver\CLionProjects\AlgoLab\AlgoLab_2_6

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Zver\CLionProjects\AlgoLab\AlgoLab_2_6\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/StringMatch2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/StringMatch2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/StringMatch2.dir/flags.make

CMakeFiles/StringMatch2.dir/search2.cpp.obj: CMakeFiles/StringMatch2.dir/flags.make
CMakeFiles/StringMatch2.dir/search2.cpp.obj: ../search2.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Zver\CLionProjects\AlgoLab\AlgoLab_2_6\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/StringMatch2.dir/search2.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\StringMatch2.dir\search2.cpp.obj -c C:\Users\Zver\CLionProjects\AlgoLab\AlgoLab_2_6\search2.cpp

CMakeFiles/StringMatch2.dir/search2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/StringMatch2.dir/search2.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Zver\CLionProjects\AlgoLab\AlgoLab_2_6\search2.cpp > CMakeFiles\StringMatch2.dir\search2.cpp.i

CMakeFiles/StringMatch2.dir/search2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/StringMatch2.dir/search2.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Zver\CLionProjects\AlgoLab\AlgoLab_2_6\search2.cpp -o CMakeFiles\StringMatch2.dir\search2.cpp.s

# Object files for target StringMatch2
StringMatch2_OBJECTS = \
"CMakeFiles/StringMatch2.dir/search2.cpp.obj"

# External object files for target StringMatch2
StringMatch2_EXTERNAL_OBJECTS =

StringMatch2.exe: CMakeFiles/StringMatch2.dir/search2.cpp.obj
StringMatch2.exe: CMakeFiles/StringMatch2.dir/build.make
StringMatch2.exe: CMakeFiles/StringMatch2.dir/linklibs.rsp
StringMatch2.exe: CMakeFiles/StringMatch2.dir/objects1.rsp
StringMatch2.exe: CMakeFiles/StringMatch2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Zver\CLionProjects\AlgoLab\AlgoLab_2_6\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable StringMatch2.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\StringMatch2.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/StringMatch2.dir/build: StringMatch2.exe

.PHONY : CMakeFiles/StringMatch2.dir/build

CMakeFiles/StringMatch2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\StringMatch2.dir\cmake_clean.cmake
.PHONY : CMakeFiles/StringMatch2.dir/clean

CMakeFiles/StringMatch2.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Zver\CLionProjects\AlgoLab\AlgoLab_2_6 C:\Users\Zver\CLionProjects\AlgoLab\AlgoLab_2_6 C:\Users\Zver\CLionProjects\AlgoLab\AlgoLab_2_6\cmake-build-debug C:\Users\Zver\CLionProjects\AlgoLab\AlgoLab_2_6\cmake-build-debug C:\Users\Zver\CLionProjects\AlgoLab\AlgoLab_2_6\cmake-build-debug\CMakeFiles\StringMatch2.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/StringMatch2.dir/depend

