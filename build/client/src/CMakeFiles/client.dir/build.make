# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/game/server/hwtrunk

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/game/server/hwtrunk/build

# Include any dependencies generated for this target.
include client/src/CMakeFiles/client.dir/depend.make

# Include the progress variables for this target.
include client/src/CMakeFiles/client.dir/progress.make

# Include the compile flags for this target's objects.
include client/src/CMakeFiles/client.dir/flags.make

client/src/CMakeFiles/client.dir/main.cpp.o: client/src/CMakeFiles/client.dir/flags.make
client/src/CMakeFiles/client.dir/main.cpp.o: ../client/src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/game/server/hwtrunk/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object client/src/CMakeFiles/client.dir/main.cpp.o"
	cd /home/game/server/hwtrunk/build/client/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client.dir/main.cpp.o -c /home/game/server/hwtrunk/client/src/main.cpp

client/src/CMakeFiles/client.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/main.cpp.i"
	cd /home/game/server/hwtrunk/build/client/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/game/server/hwtrunk/client/src/main.cpp > CMakeFiles/client.dir/main.cpp.i

client/src/CMakeFiles/client.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/main.cpp.s"
	cd /home/game/server/hwtrunk/build/client/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/game/server/hwtrunk/client/src/main.cpp -o CMakeFiles/client.dir/main.cpp.s

client/src/CMakeFiles/client.dir/main.cpp.o.requires:

.PHONY : client/src/CMakeFiles/client.dir/main.cpp.o.requires

client/src/CMakeFiles/client.dir/main.cpp.o.provides: client/src/CMakeFiles/client.dir/main.cpp.o.requires
	$(MAKE) -f client/src/CMakeFiles/client.dir/build.make client/src/CMakeFiles/client.dir/main.cpp.o.provides.build
.PHONY : client/src/CMakeFiles/client.dir/main.cpp.o.provides

client/src/CMakeFiles/client.dir/main.cpp.o.provides.build: client/src/CMakeFiles/client.dir/main.cpp.o


# Object files for target client
client_OBJECTS = \
"CMakeFiles/client.dir/main.cpp.o"

# External object files for target client
client_EXTERNAL_OBJECTS =

../bin/client: client/src/CMakeFiles/client.dir/main.cpp.o
../bin/client: client/src/CMakeFiles/client.dir/build.make
../bin/client: ../Trd/lib/libbase.a
../bin/client: ../Trd/lib/libcommon.a
../bin/client: ../Trd/lib/libprotobuf.a
../bin/client: client/src/CMakeFiles/client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/game/server/hwtrunk/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../../bin/client"
	cd /home/game/server/hwtrunk/build/client/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
client/src/CMakeFiles/client.dir/build: ../bin/client

.PHONY : client/src/CMakeFiles/client.dir/build

client/src/CMakeFiles/client.dir/requires: client/src/CMakeFiles/client.dir/main.cpp.o.requires

.PHONY : client/src/CMakeFiles/client.dir/requires

client/src/CMakeFiles/client.dir/clean:
	cd /home/game/server/hwtrunk/build/client/src && $(CMAKE_COMMAND) -P CMakeFiles/client.dir/cmake_clean.cmake
.PHONY : client/src/CMakeFiles/client.dir/clean

client/src/CMakeFiles/client.dir/depend:
	cd /home/game/server/hwtrunk/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/game/server/hwtrunk /home/game/server/hwtrunk/client/src /home/game/server/hwtrunk/build /home/game/server/hwtrunk/build/client/src /home/game/server/hwtrunk/build/client/src/CMakeFiles/client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : client/src/CMakeFiles/client.dir/depend

