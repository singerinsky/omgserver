# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/gl/omgserver/client

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gl/omgserver/client

# Include any dependencies generated for this target.
include objs/net/CMakeFiles/net.dir/depend.make

# Include the progress variables for this target.
include objs/net/CMakeFiles/net.dir/progress.make

# Include the compile flags for this target's objects.
include objs/net/CMakeFiles/net.dir/flags.make

objs/net/CMakeFiles/net.dir/serversocket.cpp.o: objs/net/CMakeFiles/net.dir/flags.make
objs/net/CMakeFiles/net.dir/serversocket.cpp.o: /home/gl/omgserver/net/serversocket.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gl/omgserver/client/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object objs/net/CMakeFiles/net.dir/serversocket.cpp.o"
	cd /home/gl/omgserver/client/objs/net && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/net.dir/serversocket.cpp.o -c /home/gl/omgserver/net/serversocket.cpp

objs/net/CMakeFiles/net.dir/serversocket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net.dir/serversocket.cpp.i"
	cd /home/gl/omgserver/client/objs/net && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gl/omgserver/net/serversocket.cpp > CMakeFiles/net.dir/serversocket.cpp.i

objs/net/CMakeFiles/net.dir/serversocket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net.dir/serversocket.cpp.s"
	cd /home/gl/omgserver/client/objs/net && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gl/omgserver/net/serversocket.cpp -o CMakeFiles/net.dir/serversocket.cpp.s

objs/net/CMakeFiles/net.dir/serversocket.cpp.o.requires:
.PHONY : objs/net/CMakeFiles/net.dir/serversocket.cpp.o.requires

objs/net/CMakeFiles/net.dir/serversocket.cpp.o.provides: objs/net/CMakeFiles/net.dir/serversocket.cpp.o.requires
	$(MAKE) -f objs/net/CMakeFiles/net.dir/build.make objs/net/CMakeFiles/net.dir/serversocket.cpp.o.provides.build
.PHONY : objs/net/CMakeFiles/net.dir/serversocket.cpp.o.provides

objs/net/CMakeFiles/net.dir/serversocket.cpp.o.provides.build: objs/net/CMakeFiles/net.dir/serversocket.cpp.o

objs/net/CMakeFiles/net.dir/epoll_handler.cpp.o: objs/net/CMakeFiles/net.dir/flags.make
objs/net/CMakeFiles/net.dir/epoll_handler.cpp.o: /home/gl/omgserver/net/epoll_handler.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gl/omgserver/client/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object objs/net/CMakeFiles/net.dir/epoll_handler.cpp.o"
	cd /home/gl/omgserver/client/objs/net && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/net.dir/epoll_handler.cpp.o -c /home/gl/omgserver/net/epoll_handler.cpp

objs/net/CMakeFiles/net.dir/epoll_handler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net.dir/epoll_handler.cpp.i"
	cd /home/gl/omgserver/client/objs/net && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gl/omgserver/net/epoll_handler.cpp > CMakeFiles/net.dir/epoll_handler.cpp.i

objs/net/CMakeFiles/net.dir/epoll_handler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net.dir/epoll_handler.cpp.s"
	cd /home/gl/omgserver/client/objs/net && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gl/omgserver/net/epoll_handler.cpp -o CMakeFiles/net.dir/epoll_handler.cpp.s

objs/net/CMakeFiles/net.dir/epoll_handler.cpp.o.requires:
.PHONY : objs/net/CMakeFiles/net.dir/epoll_handler.cpp.o.requires

objs/net/CMakeFiles/net.dir/epoll_handler.cpp.o.provides: objs/net/CMakeFiles/net.dir/epoll_handler.cpp.o.requires
	$(MAKE) -f objs/net/CMakeFiles/net.dir/build.make objs/net/CMakeFiles/net.dir/epoll_handler.cpp.o.provides.build
.PHONY : objs/net/CMakeFiles/net.dir/epoll_handler.cpp.o.provides

objs/net/CMakeFiles/net.dir/epoll_handler.cpp.o.provides.build: objs/net/CMakeFiles/net.dir/epoll_handler.cpp.o

objs/net/CMakeFiles/net.dir/net_util.cpp.o: objs/net/CMakeFiles/net.dir/flags.make
objs/net/CMakeFiles/net.dir/net_util.cpp.o: /home/gl/omgserver/net/net_util.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gl/omgserver/client/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object objs/net/CMakeFiles/net.dir/net_util.cpp.o"
	cd /home/gl/omgserver/client/objs/net && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/net.dir/net_util.cpp.o -c /home/gl/omgserver/net/net_util.cpp

objs/net/CMakeFiles/net.dir/net_util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net.dir/net_util.cpp.i"
	cd /home/gl/omgserver/client/objs/net && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gl/omgserver/net/net_util.cpp > CMakeFiles/net.dir/net_util.cpp.i

objs/net/CMakeFiles/net.dir/net_util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net.dir/net_util.cpp.s"
	cd /home/gl/omgserver/client/objs/net && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gl/omgserver/net/net_util.cpp -o CMakeFiles/net.dir/net_util.cpp.s

objs/net/CMakeFiles/net.dir/net_util.cpp.o.requires:
.PHONY : objs/net/CMakeFiles/net.dir/net_util.cpp.o.requires

objs/net/CMakeFiles/net.dir/net_util.cpp.o.provides: objs/net/CMakeFiles/net.dir/net_util.cpp.o.requires
	$(MAKE) -f objs/net/CMakeFiles/net.dir/build.make objs/net/CMakeFiles/net.dir/net_util.cpp.o.provides.build
.PHONY : objs/net/CMakeFiles/net.dir/net_util.cpp.o.provides

objs/net/CMakeFiles/net.dir/net_util.cpp.o.provides.build: objs/net/CMakeFiles/net.dir/net_util.cpp.o

objs/net/CMakeFiles/net.dir/client_socket.cpp.o: objs/net/CMakeFiles/net.dir/flags.make
objs/net/CMakeFiles/net.dir/client_socket.cpp.o: /home/gl/omgserver/net/client_socket.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gl/omgserver/client/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object objs/net/CMakeFiles/net.dir/client_socket.cpp.o"
	cd /home/gl/omgserver/client/objs/net && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/net.dir/client_socket.cpp.o -c /home/gl/omgserver/net/client_socket.cpp

objs/net/CMakeFiles/net.dir/client_socket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net.dir/client_socket.cpp.i"
	cd /home/gl/omgserver/client/objs/net && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gl/omgserver/net/client_socket.cpp > CMakeFiles/net.dir/client_socket.cpp.i

objs/net/CMakeFiles/net.dir/client_socket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net.dir/client_socket.cpp.s"
	cd /home/gl/omgserver/client/objs/net && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gl/omgserver/net/client_socket.cpp -o CMakeFiles/net.dir/client_socket.cpp.s

objs/net/CMakeFiles/net.dir/client_socket.cpp.o.requires:
.PHONY : objs/net/CMakeFiles/net.dir/client_socket.cpp.o.requires

objs/net/CMakeFiles/net.dir/client_socket.cpp.o.provides: objs/net/CMakeFiles/net.dir/client_socket.cpp.o.requires
	$(MAKE) -f objs/net/CMakeFiles/net.dir/build.make objs/net/CMakeFiles/net.dir/client_socket.cpp.o.provides.build
.PHONY : objs/net/CMakeFiles/net.dir/client_socket.cpp.o.provides

objs/net/CMakeFiles/net.dir/client_socket.cpp.o.provides.build: objs/net/CMakeFiles/net.dir/client_socket.cpp.o

objs/net/CMakeFiles/net.dir/thread.cpp.o: objs/net/CMakeFiles/net.dir/flags.make
objs/net/CMakeFiles/net.dir/thread.cpp.o: /home/gl/omgserver/net/thread.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gl/omgserver/client/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object objs/net/CMakeFiles/net.dir/thread.cpp.o"
	cd /home/gl/omgserver/client/objs/net && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/net.dir/thread.cpp.o -c /home/gl/omgserver/net/thread.cpp

objs/net/CMakeFiles/net.dir/thread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net.dir/thread.cpp.i"
	cd /home/gl/omgserver/client/objs/net && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gl/omgserver/net/thread.cpp > CMakeFiles/net.dir/thread.cpp.i

objs/net/CMakeFiles/net.dir/thread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net.dir/thread.cpp.s"
	cd /home/gl/omgserver/client/objs/net && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gl/omgserver/net/thread.cpp -o CMakeFiles/net.dir/thread.cpp.s

objs/net/CMakeFiles/net.dir/thread.cpp.o.requires:
.PHONY : objs/net/CMakeFiles/net.dir/thread.cpp.o.requires

objs/net/CMakeFiles/net.dir/thread.cpp.o.provides: objs/net/CMakeFiles/net.dir/thread.cpp.o.requires
	$(MAKE) -f objs/net/CMakeFiles/net.dir/build.make objs/net/CMakeFiles/net.dir/thread.cpp.o.provides.build
.PHONY : objs/net/CMakeFiles/net.dir/thread.cpp.o.provides

objs/net/CMakeFiles/net.dir/thread.cpp.o.provides.build: objs/net/CMakeFiles/net.dir/thread.cpp.o

objs/net/CMakeFiles/net.dir/game_packet.cpp.o: objs/net/CMakeFiles/net.dir/flags.make
objs/net/CMakeFiles/net.dir/game_packet.cpp.o: /home/gl/omgserver/net/game_packet.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gl/omgserver/client/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object objs/net/CMakeFiles/net.dir/game_packet.cpp.o"
	cd /home/gl/omgserver/client/objs/net && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/net.dir/game_packet.cpp.o -c /home/gl/omgserver/net/game_packet.cpp

objs/net/CMakeFiles/net.dir/game_packet.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net.dir/game_packet.cpp.i"
	cd /home/gl/omgserver/client/objs/net && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gl/omgserver/net/game_packet.cpp > CMakeFiles/net.dir/game_packet.cpp.i

objs/net/CMakeFiles/net.dir/game_packet.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net.dir/game_packet.cpp.s"
	cd /home/gl/omgserver/client/objs/net && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gl/omgserver/net/game_packet.cpp -o CMakeFiles/net.dir/game_packet.cpp.s

objs/net/CMakeFiles/net.dir/game_packet.cpp.o.requires:
.PHONY : objs/net/CMakeFiles/net.dir/game_packet.cpp.o.requires

objs/net/CMakeFiles/net.dir/game_packet.cpp.o.provides: objs/net/CMakeFiles/net.dir/game_packet.cpp.o.requires
	$(MAKE) -f objs/net/CMakeFiles/net.dir/build.make objs/net/CMakeFiles/net.dir/game_packet.cpp.o.provides.build
.PHONY : objs/net/CMakeFiles/net.dir/game_packet.cpp.o.provides

objs/net/CMakeFiles/net.dir/game_packet.cpp.o.provides.build: objs/net/CMakeFiles/net.dir/game_packet.cpp.o

objs/net/CMakeFiles/net.dir/socketclient.cpp.o: objs/net/CMakeFiles/net.dir/flags.make
objs/net/CMakeFiles/net.dir/socketclient.cpp.o: /home/gl/omgserver/net/socketclient.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gl/omgserver/client/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object objs/net/CMakeFiles/net.dir/socketclient.cpp.o"
	cd /home/gl/omgserver/client/objs/net && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/net.dir/socketclient.cpp.o -c /home/gl/omgserver/net/socketclient.cpp

objs/net/CMakeFiles/net.dir/socketclient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net.dir/socketclient.cpp.i"
	cd /home/gl/omgserver/client/objs/net && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gl/omgserver/net/socketclient.cpp > CMakeFiles/net.dir/socketclient.cpp.i

objs/net/CMakeFiles/net.dir/socketclient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net.dir/socketclient.cpp.s"
	cd /home/gl/omgserver/client/objs/net && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gl/omgserver/net/socketclient.cpp -o CMakeFiles/net.dir/socketclient.cpp.s

objs/net/CMakeFiles/net.dir/socketclient.cpp.o.requires:
.PHONY : objs/net/CMakeFiles/net.dir/socketclient.cpp.o.requires

objs/net/CMakeFiles/net.dir/socketclient.cpp.o.provides: objs/net/CMakeFiles/net.dir/socketclient.cpp.o.requires
	$(MAKE) -f objs/net/CMakeFiles/net.dir/build.make objs/net/CMakeFiles/net.dir/socketclient.cpp.o.provides.build
.PHONY : objs/net/CMakeFiles/net.dir/socketclient.cpp.o.provides

objs/net/CMakeFiles/net.dir/socketclient.cpp.o.provides.build: objs/net/CMakeFiles/net.dir/socketclient.cpp.o

# Object files for target net
net_OBJECTS = \
"CMakeFiles/net.dir/serversocket.cpp.o" \
"CMakeFiles/net.dir/epoll_handler.cpp.o" \
"CMakeFiles/net.dir/net_util.cpp.o" \
"CMakeFiles/net.dir/client_socket.cpp.o" \
"CMakeFiles/net.dir/thread.cpp.o" \
"CMakeFiles/net.dir/game_packet.cpp.o" \
"CMakeFiles/net.dir/socketclient.cpp.o"

# External object files for target net
net_EXTERNAL_OBJECTS =

game_lib/libnet.a: objs/net/CMakeFiles/net.dir/serversocket.cpp.o
game_lib/libnet.a: objs/net/CMakeFiles/net.dir/epoll_handler.cpp.o
game_lib/libnet.a: objs/net/CMakeFiles/net.dir/net_util.cpp.o
game_lib/libnet.a: objs/net/CMakeFiles/net.dir/client_socket.cpp.o
game_lib/libnet.a: objs/net/CMakeFiles/net.dir/thread.cpp.o
game_lib/libnet.a: objs/net/CMakeFiles/net.dir/game_packet.cpp.o
game_lib/libnet.a: objs/net/CMakeFiles/net.dir/socketclient.cpp.o
game_lib/libnet.a: objs/net/CMakeFiles/net.dir/build.make
game_lib/libnet.a: objs/net/CMakeFiles/net.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library ../../game_lib/libnet.a"
	cd /home/gl/omgserver/client/objs/net && $(CMAKE_COMMAND) -P CMakeFiles/net.dir/cmake_clean_target.cmake
	cd /home/gl/omgserver/client/objs/net && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/net.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
objs/net/CMakeFiles/net.dir/build: game_lib/libnet.a
.PHONY : objs/net/CMakeFiles/net.dir/build

objs/net/CMakeFiles/net.dir/requires: objs/net/CMakeFiles/net.dir/serversocket.cpp.o.requires
objs/net/CMakeFiles/net.dir/requires: objs/net/CMakeFiles/net.dir/epoll_handler.cpp.o.requires
objs/net/CMakeFiles/net.dir/requires: objs/net/CMakeFiles/net.dir/net_util.cpp.o.requires
objs/net/CMakeFiles/net.dir/requires: objs/net/CMakeFiles/net.dir/client_socket.cpp.o.requires
objs/net/CMakeFiles/net.dir/requires: objs/net/CMakeFiles/net.dir/thread.cpp.o.requires
objs/net/CMakeFiles/net.dir/requires: objs/net/CMakeFiles/net.dir/game_packet.cpp.o.requires
objs/net/CMakeFiles/net.dir/requires: objs/net/CMakeFiles/net.dir/socketclient.cpp.o.requires
.PHONY : objs/net/CMakeFiles/net.dir/requires

objs/net/CMakeFiles/net.dir/clean:
	cd /home/gl/omgserver/client/objs/net && $(CMAKE_COMMAND) -P CMakeFiles/net.dir/cmake_clean.cmake
.PHONY : objs/net/CMakeFiles/net.dir/clean

objs/net/CMakeFiles/net.dir/depend:
	cd /home/gl/omgserver/client && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gl/omgserver/client /home/gl/omgserver/net /home/gl/omgserver/client /home/gl/omgserver/client/objs/net /home/gl/omgserver/client/objs/net/CMakeFiles/net.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : objs/net/CMakeFiles/net.dir/depend

