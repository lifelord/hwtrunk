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
include base/src/CMakeFiles/base.dir/depend.make

# Include the progress variables for this target.
include base/src/CMakeFiles/base.dir/progress.make

# Include the compile flags for this target's objects.
include base/src/CMakeFiles/base.dir/flags.make

base/src/CMakeFiles/base.dir/base_client_pool.cpp.o: base/src/CMakeFiles/base.dir/flags.make
base/src/CMakeFiles/base.dir/base_client_pool.cpp.o: ../base/src/base_client_pool.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/game/server/hwtrunk/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object base/src/CMakeFiles/base.dir/base_client_pool.cpp.o"
	cd /home/game/server/hwtrunk/build/base/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/base.dir/base_client_pool.cpp.o -c /home/game/server/hwtrunk/base/src/base_client_pool.cpp

base/src/CMakeFiles/base.dir/base_client_pool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/base.dir/base_client_pool.cpp.i"
	cd /home/game/server/hwtrunk/build/base/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/game/server/hwtrunk/base/src/base_client_pool.cpp > CMakeFiles/base.dir/base_client_pool.cpp.i

base/src/CMakeFiles/base.dir/base_client_pool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/base.dir/base_client_pool.cpp.s"
	cd /home/game/server/hwtrunk/build/base/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/game/server/hwtrunk/base/src/base_client_pool.cpp -o CMakeFiles/base.dir/base_client_pool.cpp.s

base/src/CMakeFiles/base.dir/base_client_pool.cpp.o.requires:

.PHONY : base/src/CMakeFiles/base.dir/base_client_pool.cpp.o.requires

base/src/CMakeFiles/base.dir/base_client_pool.cpp.o.provides: base/src/CMakeFiles/base.dir/base_client_pool.cpp.o.requires
	$(MAKE) -f base/src/CMakeFiles/base.dir/build.make base/src/CMakeFiles/base.dir/base_client_pool.cpp.o.provides.build
.PHONY : base/src/CMakeFiles/base.dir/base_client_pool.cpp.o.provides

base/src/CMakeFiles/base.dir/base_client_pool.cpp.o.provides.build: base/src/CMakeFiles/base.dir/base_client_pool.cpp.o


base/src/CMakeFiles/base.dir/base_epoll.cpp.o: base/src/CMakeFiles/base.dir/flags.make
base/src/CMakeFiles/base.dir/base_epoll.cpp.o: ../base/src/base_epoll.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/game/server/hwtrunk/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object base/src/CMakeFiles/base.dir/base_epoll.cpp.o"
	cd /home/game/server/hwtrunk/build/base/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/base.dir/base_epoll.cpp.o -c /home/game/server/hwtrunk/base/src/base_epoll.cpp

base/src/CMakeFiles/base.dir/base_epoll.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/base.dir/base_epoll.cpp.i"
	cd /home/game/server/hwtrunk/build/base/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/game/server/hwtrunk/base/src/base_epoll.cpp > CMakeFiles/base.dir/base_epoll.cpp.i

base/src/CMakeFiles/base.dir/base_epoll.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/base.dir/base_epoll.cpp.s"
	cd /home/game/server/hwtrunk/build/base/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/game/server/hwtrunk/base/src/base_epoll.cpp -o CMakeFiles/base.dir/base_epoll.cpp.s

base/src/CMakeFiles/base.dir/base_epoll.cpp.o.requires:

.PHONY : base/src/CMakeFiles/base.dir/base_epoll.cpp.o.requires

base/src/CMakeFiles/base.dir/base_epoll.cpp.o.provides: base/src/CMakeFiles/base.dir/base_epoll.cpp.o.requires
	$(MAKE) -f base/src/CMakeFiles/base.dir/build.make base/src/CMakeFiles/base.dir/base_epoll.cpp.o.provides.build
.PHONY : base/src/CMakeFiles/base.dir/base_epoll.cpp.o.provides

base/src/CMakeFiles/base.dir/base_epoll.cpp.o.provides.build: base/src/CMakeFiles/base.dir/base_epoll.cpp.o


base/src/CMakeFiles/base.dir/base_sandbox.cpp.o: base/src/CMakeFiles/base.dir/flags.make
base/src/CMakeFiles/base.dir/base_sandbox.cpp.o: ../base/src/base_sandbox.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/game/server/hwtrunk/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object base/src/CMakeFiles/base.dir/base_sandbox.cpp.o"
	cd /home/game/server/hwtrunk/build/base/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/base.dir/base_sandbox.cpp.o -c /home/game/server/hwtrunk/base/src/base_sandbox.cpp

base/src/CMakeFiles/base.dir/base_sandbox.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/base.dir/base_sandbox.cpp.i"
	cd /home/game/server/hwtrunk/build/base/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/game/server/hwtrunk/base/src/base_sandbox.cpp > CMakeFiles/base.dir/base_sandbox.cpp.i

base/src/CMakeFiles/base.dir/base_sandbox.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/base.dir/base_sandbox.cpp.s"
	cd /home/game/server/hwtrunk/build/base/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/game/server/hwtrunk/base/src/base_sandbox.cpp -o CMakeFiles/base.dir/base_sandbox.cpp.s

base/src/CMakeFiles/base.dir/base_sandbox.cpp.o.requires:

.PHONY : base/src/CMakeFiles/base.dir/base_sandbox.cpp.o.requires

base/src/CMakeFiles/base.dir/base_sandbox.cpp.o.provides: base/src/CMakeFiles/base.dir/base_sandbox.cpp.o.requires
	$(MAKE) -f base/src/CMakeFiles/base.dir/build.make base/src/CMakeFiles/base.dir/base_sandbox.cpp.o.provides.build
.PHONY : base/src/CMakeFiles/base.dir/base_sandbox.cpp.o.provides

base/src/CMakeFiles/base.dir/base_sandbox.cpp.o.provides.build: base/src/CMakeFiles/base.dir/base_sandbox.cpp.o


base/src/CMakeFiles/base.dir/base_signal.cpp.o: base/src/CMakeFiles/base.dir/flags.make
base/src/CMakeFiles/base.dir/base_signal.cpp.o: ../base/src/base_signal.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/game/server/hwtrunk/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object base/src/CMakeFiles/base.dir/base_signal.cpp.o"
	cd /home/game/server/hwtrunk/build/base/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/base.dir/base_signal.cpp.o -c /home/game/server/hwtrunk/base/src/base_signal.cpp

base/src/CMakeFiles/base.dir/base_signal.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/base.dir/base_signal.cpp.i"
	cd /home/game/server/hwtrunk/build/base/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/game/server/hwtrunk/base/src/base_signal.cpp > CMakeFiles/base.dir/base_signal.cpp.i

base/src/CMakeFiles/base.dir/base_signal.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/base.dir/base_signal.cpp.s"
	cd /home/game/server/hwtrunk/build/base/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/game/server/hwtrunk/base/src/base_signal.cpp -o CMakeFiles/base.dir/base_signal.cpp.s

base/src/CMakeFiles/base.dir/base_signal.cpp.o.requires:

.PHONY : base/src/CMakeFiles/base.dir/base_signal.cpp.o.requires

base/src/CMakeFiles/base.dir/base_signal.cpp.o.provides: base/src/CMakeFiles/base.dir/base_signal.cpp.o.requires
	$(MAKE) -f base/src/CMakeFiles/base.dir/build.make base/src/CMakeFiles/base.dir/base_signal.cpp.o.provides.build
.PHONY : base/src/CMakeFiles/base.dir/base_signal.cpp.o.provides

base/src/CMakeFiles/base.dir/base_signal.cpp.o.provides.build: base/src/CMakeFiles/base.dir/base_signal.cpp.o


base/src/CMakeFiles/base.dir/base_socket.cpp.o: base/src/CMakeFiles/base.dir/flags.make
base/src/CMakeFiles/base.dir/base_socket.cpp.o: ../base/src/base_socket.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/game/server/hwtrunk/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object base/src/CMakeFiles/base.dir/base_socket.cpp.o"
	cd /home/game/server/hwtrunk/build/base/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/base.dir/base_socket.cpp.o -c /home/game/server/hwtrunk/base/src/base_socket.cpp

base/src/CMakeFiles/base.dir/base_socket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/base.dir/base_socket.cpp.i"
	cd /home/game/server/hwtrunk/build/base/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/game/server/hwtrunk/base/src/base_socket.cpp > CMakeFiles/base.dir/base_socket.cpp.i

base/src/CMakeFiles/base.dir/base_socket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/base.dir/base_socket.cpp.s"
	cd /home/game/server/hwtrunk/build/base/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/game/server/hwtrunk/base/src/base_socket.cpp -o CMakeFiles/base.dir/base_socket.cpp.s

base/src/CMakeFiles/base.dir/base_socket.cpp.o.requires:

.PHONY : base/src/CMakeFiles/base.dir/base_socket.cpp.o.requires

base/src/CMakeFiles/base.dir/base_socket.cpp.o.provides: base/src/CMakeFiles/base.dir/base_socket.cpp.o.requires
	$(MAKE) -f base/src/CMakeFiles/base.dir/build.make base/src/CMakeFiles/base.dir/base_socket.cpp.o.provides.build
.PHONY : base/src/CMakeFiles/base.dir/base_socket.cpp.o.provides

base/src/CMakeFiles/base.dir/base_socket.cpp.o.provides.build: base/src/CMakeFiles/base.dir/base_socket.cpp.o


base/src/CMakeFiles/base.dir/base_socket_server.cpp.o: base/src/CMakeFiles/base.dir/flags.make
base/src/CMakeFiles/base.dir/base_socket_server.cpp.o: ../base/src/base_socket_server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/game/server/hwtrunk/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object base/src/CMakeFiles/base.dir/base_socket_server.cpp.o"
	cd /home/game/server/hwtrunk/build/base/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/base.dir/base_socket_server.cpp.o -c /home/game/server/hwtrunk/base/src/base_socket_server.cpp

base/src/CMakeFiles/base.dir/base_socket_server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/base.dir/base_socket_server.cpp.i"
	cd /home/game/server/hwtrunk/build/base/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/game/server/hwtrunk/base/src/base_socket_server.cpp > CMakeFiles/base.dir/base_socket_server.cpp.i

base/src/CMakeFiles/base.dir/base_socket_server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/base.dir/base_socket_server.cpp.s"
	cd /home/game/server/hwtrunk/build/base/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/game/server/hwtrunk/base/src/base_socket_server.cpp -o CMakeFiles/base.dir/base_socket_server.cpp.s

base/src/CMakeFiles/base.dir/base_socket_server.cpp.o.requires:

.PHONY : base/src/CMakeFiles/base.dir/base_socket_server.cpp.o.requires

base/src/CMakeFiles/base.dir/base_socket_server.cpp.o.provides: base/src/CMakeFiles/base.dir/base_socket_server.cpp.o.requires
	$(MAKE) -f base/src/CMakeFiles/base.dir/build.make base/src/CMakeFiles/base.dir/base_socket_server.cpp.o.provides.build
.PHONY : base/src/CMakeFiles/base.dir/base_socket_server.cpp.o.provides

base/src/CMakeFiles/base.dir/base_socket_server.cpp.o.provides.build: base/src/CMakeFiles/base.dir/base_socket_server.cpp.o


base/src/CMakeFiles/base.dir/base_stream.cpp.o: base/src/CMakeFiles/base.dir/flags.make
base/src/CMakeFiles/base.dir/base_stream.cpp.o: ../base/src/base_stream.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/game/server/hwtrunk/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object base/src/CMakeFiles/base.dir/base_stream.cpp.o"
	cd /home/game/server/hwtrunk/build/base/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/base.dir/base_stream.cpp.o -c /home/game/server/hwtrunk/base/src/base_stream.cpp

base/src/CMakeFiles/base.dir/base_stream.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/base.dir/base_stream.cpp.i"
	cd /home/game/server/hwtrunk/build/base/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/game/server/hwtrunk/base/src/base_stream.cpp > CMakeFiles/base.dir/base_stream.cpp.i

base/src/CMakeFiles/base.dir/base_stream.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/base.dir/base_stream.cpp.s"
	cd /home/game/server/hwtrunk/build/base/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/game/server/hwtrunk/base/src/base_stream.cpp -o CMakeFiles/base.dir/base_stream.cpp.s

base/src/CMakeFiles/base.dir/base_stream.cpp.o.requires:

.PHONY : base/src/CMakeFiles/base.dir/base_stream.cpp.o.requires

base/src/CMakeFiles/base.dir/base_stream.cpp.o.provides: base/src/CMakeFiles/base.dir/base_stream.cpp.o.requires
	$(MAKE) -f base/src/CMakeFiles/base.dir/build.make base/src/CMakeFiles/base.dir/base_stream.cpp.o.provides.build
.PHONY : base/src/CMakeFiles/base.dir/base_stream.cpp.o.provides

base/src/CMakeFiles/base.dir/base_stream.cpp.o.provides.build: base/src/CMakeFiles/base.dir/base_stream.cpp.o


base/src/CMakeFiles/base.dir/base_thread.cpp.o: base/src/CMakeFiles/base.dir/flags.make
base/src/CMakeFiles/base.dir/base_thread.cpp.o: ../base/src/base_thread.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/game/server/hwtrunk/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object base/src/CMakeFiles/base.dir/base_thread.cpp.o"
	cd /home/game/server/hwtrunk/build/base/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/base.dir/base_thread.cpp.o -c /home/game/server/hwtrunk/base/src/base_thread.cpp

base/src/CMakeFiles/base.dir/base_thread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/base.dir/base_thread.cpp.i"
	cd /home/game/server/hwtrunk/build/base/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/game/server/hwtrunk/base/src/base_thread.cpp > CMakeFiles/base.dir/base_thread.cpp.i

base/src/CMakeFiles/base.dir/base_thread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/base.dir/base_thread.cpp.s"
	cd /home/game/server/hwtrunk/build/base/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/game/server/hwtrunk/base/src/base_thread.cpp -o CMakeFiles/base.dir/base_thread.cpp.s

base/src/CMakeFiles/base.dir/base_thread.cpp.o.requires:

.PHONY : base/src/CMakeFiles/base.dir/base_thread.cpp.o.requires

base/src/CMakeFiles/base.dir/base_thread.cpp.o.provides: base/src/CMakeFiles/base.dir/base_thread.cpp.o.requires
	$(MAKE) -f base/src/CMakeFiles/base.dir/build.make base/src/CMakeFiles/base.dir/base_thread.cpp.o.provides.build
.PHONY : base/src/CMakeFiles/base.dir/base_thread.cpp.o.provides

base/src/CMakeFiles/base.dir/base_thread.cpp.o.provides.build: base/src/CMakeFiles/base.dir/base_thread.cpp.o


base/src/CMakeFiles/base.dir/base_unpack.cpp.o: base/src/CMakeFiles/base.dir/flags.make
base/src/CMakeFiles/base.dir/base_unpack.cpp.o: ../base/src/base_unpack.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/game/server/hwtrunk/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object base/src/CMakeFiles/base.dir/base_unpack.cpp.o"
	cd /home/game/server/hwtrunk/build/base/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/base.dir/base_unpack.cpp.o -c /home/game/server/hwtrunk/base/src/base_unpack.cpp

base/src/CMakeFiles/base.dir/base_unpack.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/base.dir/base_unpack.cpp.i"
	cd /home/game/server/hwtrunk/build/base/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/game/server/hwtrunk/base/src/base_unpack.cpp > CMakeFiles/base.dir/base_unpack.cpp.i

base/src/CMakeFiles/base.dir/base_unpack.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/base.dir/base_unpack.cpp.s"
	cd /home/game/server/hwtrunk/build/base/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/game/server/hwtrunk/base/src/base_unpack.cpp -o CMakeFiles/base.dir/base_unpack.cpp.s

base/src/CMakeFiles/base.dir/base_unpack.cpp.o.requires:

.PHONY : base/src/CMakeFiles/base.dir/base_unpack.cpp.o.requires

base/src/CMakeFiles/base.dir/base_unpack.cpp.o.provides: base/src/CMakeFiles/base.dir/base_unpack.cpp.o.requires
	$(MAKE) -f base/src/CMakeFiles/base.dir/build.make base/src/CMakeFiles/base.dir/base_unpack.cpp.o.provides.build
.PHONY : base/src/CMakeFiles/base.dir/base_unpack.cpp.o.provides

base/src/CMakeFiles/base.dir/base_unpack.cpp.o.provides.build: base/src/CMakeFiles/base.dir/base_unpack.cpp.o


# Object files for target base
base_OBJECTS = \
"CMakeFiles/base.dir/base_client_pool.cpp.o" \
"CMakeFiles/base.dir/base_epoll.cpp.o" \
"CMakeFiles/base.dir/base_sandbox.cpp.o" \
"CMakeFiles/base.dir/base_signal.cpp.o" \
"CMakeFiles/base.dir/base_socket.cpp.o" \
"CMakeFiles/base.dir/base_socket_server.cpp.o" \
"CMakeFiles/base.dir/base_stream.cpp.o" \
"CMakeFiles/base.dir/base_thread.cpp.o" \
"CMakeFiles/base.dir/base_unpack.cpp.o"

# External object files for target base
base_EXTERNAL_OBJECTS =

../Trd/lib/libbase.a: base/src/CMakeFiles/base.dir/base_client_pool.cpp.o
../Trd/lib/libbase.a: base/src/CMakeFiles/base.dir/base_epoll.cpp.o
../Trd/lib/libbase.a: base/src/CMakeFiles/base.dir/base_sandbox.cpp.o
../Trd/lib/libbase.a: base/src/CMakeFiles/base.dir/base_signal.cpp.o
../Trd/lib/libbase.a: base/src/CMakeFiles/base.dir/base_socket.cpp.o
../Trd/lib/libbase.a: base/src/CMakeFiles/base.dir/base_socket_server.cpp.o
../Trd/lib/libbase.a: base/src/CMakeFiles/base.dir/base_stream.cpp.o
../Trd/lib/libbase.a: base/src/CMakeFiles/base.dir/base_thread.cpp.o
../Trd/lib/libbase.a: base/src/CMakeFiles/base.dir/base_unpack.cpp.o
../Trd/lib/libbase.a: base/src/CMakeFiles/base.dir/build.make
../Trd/lib/libbase.a: base/src/CMakeFiles/base.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/game/server/hwtrunk/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX static library ../../../Trd/lib/libbase.a"
	cd /home/game/server/hwtrunk/build/base/src && $(CMAKE_COMMAND) -P CMakeFiles/base.dir/cmake_clean_target.cmake
	cd /home/game/server/hwtrunk/build/base/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/base.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
base/src/CMakeFiles/base.dir/build: ../Trd/lib/libbase.a

.PHONY : base/src/CMakeFiles/base.dir/build

base/src/CMakeFiles/base.dir/requires: base/src/CMakeFiles/base.dir/base_client_pool.cpp.o.requires
base/src/CMakeFiles/base.dir/requires: base/src/CMakeFiles/base.dir/base_epoll.cpp.o.requires
base/src/CMakeFiles/base.dir/requires: base/src/CMakeFiles/base.dir/base_sandbox.cpp.o.requires
base/src/CMakeFiles/base.dir/requires: base/src/CMakeFiles/base.dir/base_signal.cpp.o.requires
base/src/CMakeFiles/base.dir/requires: base/src/CMakeFiles/base.dir/base_socket.cpp.o.requires
base/src/CMakeFiles/base.dir/requires: base/src/CMakeFiles/base.dir/base_socket_server.cpp.o.requires
base/src/CMakeFiles/base.dir/requires: base/src/CMakeFiles/base.dir/base_stream.cpp.o.requires
base/src/CMakeFiles/base.dir/requires: base/src/CMakeFiles/base.dir/base_thread.cpp.o.requires
base/src/CMakeFiles/base.dir/requires: base/src/CMakeFiles/base.dir/base_unpack.cpp.o.requires

.PHONY : base/src/CMakeFiles/base.dir/requires

base/src/CMakeFiles/base.dir/clean:
	cd /home/game/server/hwtrunk/build/base/src && $(CMAKE_COMMAND) -P CMakeFiles/base.dir/cmake_clean.cmake
.PHONY : base/src/CMakeFiles/base.dir/clean

base/src/CMakeFiles/base.dir/depend:
	cd /home/game/server/hwtrunk/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/game/server/hwtrunk /home/game/server/hwtrunk/base/src /home/game/server/hwtrunk/build /home/game/server/hwtrunk/build/base/src /home/game/server/hwtrunk/build/base/src/CMakeFiles/base.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : base/src/CMakeFiles/base.dir/depend

