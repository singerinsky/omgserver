# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/gl/server/c_server/omgserver/db_server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gl/server/c_server/omgserver/db_server

# Include any dependencies generated for this target.
include objs/common/CMakeFiles/common.dir/depend.make

# Include the progress variables for this target.
include objs/common/CMakeFiles/common.dir/progress.make

# Include the compile flags for this target's objects.
include objs/common/CMakeFiles/common.dir/flags.make

objs/common/CMakeFiles/common.dir/IJob.o: objs/common/CMakeFiles/common.dir/flags.make
objs/common/CMakeFiles/common.dir/IJob.o: /home/gl/server/c_server/omgserver/common/IJob.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gl/server/c_server/omgserver/db_server/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object objs/common/CMakeFiles/common.dir/IJob.o"
	cd /home/gl/server/c_server/omgserver/db_server/objs/common && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/common.dir/IJob.o -c /home/gl/server/c_server/omgserver/common/IJob.cpp

objs/common/CMakeFiles/common.dir/IJob.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/common.dir/IJob.i"
	cd /home/gl/server/c_server/omgserver/db_server/objs/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gl/server/c_server/omgserver/common/IJob.cpp > CMakeFiles/common.dir/IJob.i

objs/common/CMakeFiles/common.dir/IJob.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/common.dir/IJob.s"
	cd /home/gl/server/c_server/omgserver/db_server/objs/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gl/server/c_server/omgserver/common/IJob.cpp -o CMakeFiles/common.dir/IJob.s

objs/common/CMakeFiles/common.dir/IJob.o.requires:
.PHONY : objs/common/CMakeFiles/common.dir/IJob.o.requires

objs/common/CMakeFiles/common.dir/IJob.o.provides: objs/common/CMakeFiles/common.dir/IJob.o.requires
	$(MAKE) -f objs/common/CMakeFiles/common.dir/build.make objs/common/CMakeFiles/common.dir/IJob.o.provides.build
.PHONY : objs/common/CMakeFiles/common.dir/IJob.o.provides

objs/common/CMakeFiles/common.dir/IJob.o.provides.build: objs/common/CMakeFiles/common.dir/IJob.o
.PHONY : objs/common/CMakeFiles/common.dir/IJob.o.provides.build

objs/common/CMakeFiles/common.dir/CThread.o: objs/common/CMakeFiles/common.dir/flags.make
objs/common/CMakeFiles/common.dir/CThread.o: /home/gl/server/c_server/omgserver/common/CThread.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gl/server/c_server/omgserver/db_server/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object objs/common/CMakeFiles/common.dir/CThread.o"
	cd /home/gl/server/c_server/omgserver/db_server/objs/common && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/common.dir/CThread.o -c /home/gl/server/c_server/omgserver/common/CThread.cpp

objs/common/CMakeFiles/common.dir/CThread.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/common.dir/CThread.i"
	cd /home/gl/server/c_server/omgserver/db_server/objs/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gl/server/c_server/omgserver/common/CThread.cpp > CMakeFiles/common.dir/CThread.i

objs/common/CMakeFiles/common.dir/CThread.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/common.dir/CThread.s"
	cd /home/gl/server/c_server/omgserver/db_server/objs/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gl/server/c_server/omgserver/common/CThread.cpp -o CMakeFiles/common.dir/CThread.s

objs/common/CMakeFiles/common.dir/CThread.o.requires:
.PHONY : objs/common/CMakeFiles/common.dir/CThread.o.requires

objs/common/CMakeFiles/common.dir/CThread.o.provides: objs/common/CMakeFiles/common.dir/CThread.o.requires
	$(MAKE) -f objs/common/CMakeFiles/common.dir/build.make objs/common/CMakeFiles/common.dir/CThread.o.provides.build
.PHONY : objs/common/CMakeFiles/common.dir/CThread.o.provides

objs/common/CMakeFiles/common.dir/CThread.o.provides.build: objs/common/CMakeFiles/common.dir/CThread.o
.PHONY : objs/common/CMakeFiles/common.dir/CThread.o.provides.build

objs/common/CMakeFiles/common.dir/MD5.o: objs/common/CMakeFiles/common.dir/flags.make
objs/common/CMakeFiles/common.dir/MD5.o: /home/gl/server/c_server/omgserver/common/MD5.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gl/server/c_server/omgserver/db_server/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object objs/common/CMakeFiles/common.dir/MD5.o"
	cd /home/gl/server/c_server/omgserver/db_server/objs/common && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/common.dir/MD5.o -c /home/gl/server/c_server/omgserver/common/MD5.cpp

objs/common/CMakeFiles/common.dir/MD5.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/common.dir/MD5.i"
	cd /home/gl/server/c_server/omgserver/db_server/objs/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gl/server/c_server/omgserver/common/MD5.cpp > CMakeFiles/common.dir/MD5.i

objs/common/CMakeFiles/common.dir/MD5.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/common.dir/MD5.s"
	cd /home/gl/server/c_server/omgserver/db_server/objs/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gl/server/c_server/omgserver/common/MD5.cpp -o CMakeFiles/common.dir/MD5.s

objs/common/CMakeFiles/common.dir/MD5.o.requires:
.PHONY : objs/common/CMakeFiles/common.dir/MD5.o.requires

objs/common/CMakeFiles/common.dir/MD5.o.provides: objs/common/CMakeFiles/common.dir/MD5.o.requires
	$(MAKE) -f objs/common/CMakeFiles/common.dir/build.make objs/common/CMakeFiles/common.dir/MD5.o.provides.build
.PHONY : objs/common/CMakeFiles/common.dir/MD5.o.provides

objs/common/CMakeFiles/common.dir/MD5.o.provides.build: objs/common/CMakeFiles/common.dir/MD5.o
.PHONY : objs/common/CMakeFiles/common.dir/MD5.o.provides.build

objs/common/CMakeFiles/common.dir/CThreadManage.o: objs/common/CMakeFiles/common.dir/flags.make
objs/common/CMakeFiles/common.dir/CThreadManage.o: /home/gl/server/c_server/omgserver/common/CThreadManage.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gl/server/c_server/omgserver/db_server/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object objs/common/CMakeFiles/common.dir/CThreadManage.o"
	cd /home/gl/server/c_server/omgserver/db_server/objs/common && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/common.dir/CThreadManage.o -c /home/gl/server/c_server/omgserver/common/CThreadManage.cpp

objs/common/CMakeFiles/common.dir/CThreadManage.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/common.dir/CThreadManage.i"
	cd /home/gl/server/c_server/omgserver/db_server/objs/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gl/server/c_server/omgserver/common/CThreadManage.cpp > CMakeFiles/common.dir/CThreadManage.i

objs/common/CMakeFiles/common.dir/CThreadManage.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/common.dir/CThreadManage.s"
	cd /home/gl/server/c_server/omgserver/db_server/objs/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gl/server/c_server/omgserver/common/CThreadManage.cpp -o CMakeFiles/common.dir/CThreadManage.s

objs/common/CMakeFiles/common.dir/CThreadManage.o.requires:
.PHONY : objs/common/CMakeFiles/common.dir/CThreadManage.o.requires

objs/common/CMakeFiles/common.dir/CThreadManage.o.provides: objs/common/CMakeFiles/common.dir/CThreadManage.o.requires
	$(MAKE) -f objs/common/CMakeFiles/common.dir/build.make objs/common/CMakeFiles/common.dir/CThreadManage.o.provides.build
.PHONY : objs/common/CMakeFiles/common.dir/CThreadManage.o.provides

objs/common/CMakeFiles/common.dir/CThreadManage.o.provides.build: objs/common/CMakeFiles/common.dir/CThreadManage.o
.PHONY : objs/common/CMakeFiles/common.dir/CThreadManage.o.provides.build

objs/common/CMakeFiles/common.dir/CPoolThread.o: objs/common/CMakeFiles/common.dir/flags.make
objs/common/CMakeFiles/common.dir/CPoolThread.o: /home/gl/server/c_server/omgserver/common/CPoolThread.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gl/server/c_server/omgserver/db_server/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object objs/common/CMakeFiles/common.dir/CPoolThread.o"
	cd /home/gl/server/c_server/omgserver/db_server/objs/common && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/common.dir/CPoolThread.o -c /home/gl/server/c_server/omgserver/common/CPoolThread.cpp

objs/common/CMakeFiles/common.dir/CPoolThread.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/common.dir/CPoolThread.i"
	cd /home/gl/server/c_server/omgserver/db_server/objs/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gl/server/c_server/omgserver/common/CPoolThread.cpp > CMakeFiles/common.dir/CPoolThread.i

objs/common/CMakeFiles/common.dir/CPoolThread.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/common.dir/CPoolThread.s"
	cd /home/gl/server/c_server/omgserver/db_server/objs/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gl/server/c_server/omgserver/common/CPoolThread.cpp -o CMakeFiles/common.dir/CPoolThread.s

objs/common/CMakeFiles/common.dir/CPoolThread.o.requires:
.PHONY : objs/common/CMakeFiles/common.dir/CPoolThread.o.requires

objs/common/CMakeFiles/common.dir/CPoolThread.o.provides: objs/common/CMakeFiles/common.dir/CPoolThread.o.requires
	$(MAKE) -f objs/common/CMakeFiles/common.dir/build.make objs/common/CMakeFiles/common.dir/CPoolThread.o.provides.build
.PHONY : objs/common/CMakeFiles/common.dir/CPoolThread.o.provides

objs/common/CMakeFiles/common.dir/CPoolThread.o.provides.build: objs/common/CMakeFiles/common.dir/CPoolThread.o
.PHONY : objs/common/CMakeFiles/common.dir/CPoolThread.o.provides.build

objs/common/CMakeFiles/common.dir/JobDequeue.o: objs/common/CMakeFiles/common.dir/flags.make
objs/common/CMakeFiles/common.dir/JobDequeue.o: /home/gl/server/c_server/omgserver/common/JobDequeue.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gl/server/c_server/omgserver/db_server/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object objs/common/CMakeFiles/common.dir/JobDequeue.o"
	cd /home/gl/server/c_server/omgserver/db_server/objs/common && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/common.dir/JobDequeue.o -c /home/gl/server/c_server/omgserver/common/JobDequeue.cpp

objs/common/CMakeFiles/common.dir/JobDequeue.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/common.dir/JobDequeue.i"
	cd /home/gl/server/c_server/omgserver/db_server/objs/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gl/server/c_server/omgserver/common/JobDequeue.cpp > CMakeFiles/common.dir/JobDequeue.i

objs/common/CMakeFiles/common.dir/JobDequeue.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/common.dir/JobDequeue.s"
	cd /home/gl/server/c_server/omgserver/db_server/objs/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gl/server/c_server/omgserver/common/JobDequeue.cpp -o CMakeFiles/common.dir/JobDequeue.s

objs/common/CMakeFiles/common.dir/JobDequeue.o.requires:
.PHONY : objs/common/CMakeFiles/common.dir/JobDequeue.o.requires

objs/common/CMakeFiles/common.dir/JobDequeue.o.provides: objs/common/CMakeFiles/common.dir/JobDequeue.o.requires
	$(MAKE) -f objs/common/CMakeFiles/common.dir/build.make objs/common/CMakeFiles/common.dir/JobDequeue.o.provides.build
.PHONY : objs/common/CMakeFiles/common.dir/JobDequeue.o.provides

objs/common/CMakeFiles/common.dir/JobDequeue.o.provides.build: objs/common/CMakeFiles/common.dir/JobDequeue.o
.PHONY : objs/common/CMakeFiles/common.dir/JobDequeue.o.provides.build

objs/common/CMakeFiles/common.dir/CTimerEventHandler.o: objs/common/CMakeFiles/common.dir/flags.make
objs/common/CMakeFiles/common.dir/CTimerEventHandler.o: /home/gl/server/c_server/omgserver/common/CTimerEventHandler.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gl/server/c_server/omgserver/db_server/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object objs/common/CMakeFiles/common.dir/CTimerEventHandler.o"
	cd /home/gl/server/c_server/omgserver/db_server/objs/common && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/common.dir/CTimerEventHandler.o -c /home/gl/server/c_server/omgserver/common/CTimerEventHandler.cpp

objs/common/CMakeFiles/common.dir/CTimerEventHandler.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/common.dir/CTimerEventHandler.i"
	cd /home/gl/server/c_server/omgserver/db_server/objs/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gl/server/c_server/omgserver/common/CTimerEventHandler.cpp > CMakeFiles/common.dir/CTimerEventHandler.i

objs/common/CMakeFiles/common.dir/CTimerEventHandler.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/common.dir/CTimerEventHandler.s"
	cd /home/gl/server/c_server/omgserver/db_server/objs/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gl/server/c_server/omgserver/common/CTimerEventHandler.cpp -o CMakeFiles/common.dir/CTimerEventHandler.s

objs/common/CMakeFiles/common.dir/CTimerEventHandler.o.requires:
.PHONY : objs/common/CMakeFiles/common.dir/CTimerEventHandler.o.requires

objs/common/CMakeFiles/common.dir/CTimerEventHandler.o.provides: objs/common/CMakeFiles/common.dir/CTimerEventHandler.o.requires
	$(MAKE) -f objs/common/CMakeFiles/common.dir/build.make objs/common/CMakeFiles/common.dir/CTimerEventHandler.o.provides.build
.PHONY : objs/common/CMakeFiles/common.dir/CTimerEventHandler.o.provides

objs/common/CMakeFiles/common.dir/CTimerEventHandler.o.provides.build: objs/common/CMakeFiles/common.dir/CTimerEventHandler.o
.PHONY : objs/common/CMakeFiles/common.dir/CTimerEventHandler.o.provides.build

objs/common/CMakeFiles/common.dir/CEventThread.o: objs/common/CMakeFiles/common.dir/flags.make
objs/common/CMakeFiles/common.dir/CEventThread.o: /home/gl/server/c_server/omgserver/common/CEventThread.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gl/server/c_server/omgserver/db_server/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object objs/common/CMakeFiles/common.dir/CEventThread.o"
	cd /home/gl/server/c_server/omgserver/db_server/objs/common && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/common.dir/CEventThread.o -c /home/gl/server/c_server/omgserver/common/CEventThread.cpp

objs/common/CMakeFiles/common.dir/CEventThread.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/common.dir/CEventThread.i"
	cd /home/gl/server/c_server/omgserver/db_server/objs/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gl/server/c_server/omgserver/common/CEventThread.cpp > CMakeFiles/common.dir/CEventThread.i

objs/common/CMakeFiles/common.dir/CEventThread.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/common.dir/CEventThread.s"
	cd /home/gl/server/c_server/omgserver/db_server/objs/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gl/server/c_server/omgserver/common/CEventThread.cpp -o CMakeFiles/common.dir/CEventThread.s

objs/common/CMakeFiles/common.dir/CEventThread.o.requires:
.PHONY : objs/common/CMakeFiles/common.dir/CEventThread.o.requires

objs/common/CMakeFiles/common.dir/CEventThread.o.provides: objs/common/CMakeFiles/common.dir/CEventThread.o.requires
	$(MAKE) -f objs/common/CMakeFiles/common.dir/build.make objs/common/CMakeFiles/common.dir/CEventThread.o.provides.build
.PHONY : objs/common/CMakeFiles/common.dir/CEventThread.o.provides

objs/common/CMakeFiles/common.dir/CEventThread.o.provides.build: objs/common/CMakeFiles/common.dir/CEventThread.o
.PHONY : objs/common/CMakeFiles/common.dir/CEventThread.o.provides.build

objs/common/CMakeFiles/common.dir/circular_buffer.o: objs/common/CMakeFiles/common.dir/flags.make
objs/common/CMakeFiles/common.dir/circular_buffer.o: /home/gl/server/c_server/omgserver/common/circular_buffer.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gl/server/c_server/omgserver/db_server/CMakeFiles $(CMAKE_PROGRESS_9)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object objs/common/CMakeFiles/common.dir/circular_buffer.o"
	cd /home/gl/server/c_server/omgserver/db_server/objs/common && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/common.dir/circular_buffer.o -c /home/gl/server/c_server/omgserver/common/circular_buffer.cpp

objs/common/CMakeFiles/common.dir/circular_buffer.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/common.dir/circular_buffer.i"
	cd /home/gl/server/c_server/omgserver/db_server/objs/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gl/server/c_server/omgserver/common/circular_buffer.cpp > CMakeFiles/common.dir/circular_buffer.i

objs/common/CMakeFiles/common.dir/circular_buffer.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/common.dir/circular_buffer.s"
	cd /home/gl/server/c_server/omgserver/db_server/objs/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gl/server/c_server/omgserver/common/circular_buffer.cpp -o CMakeFiles/common.dir/circular_buffer.s

objs/common/CMakeFiles/common.dir/circular_buffer.o.requires:
.PHONY : objs/common/CMakeFiles/common.dir/circular_buffer.o.requires

objs/common/CMakeFiles/common.dir/circular_buffer.o.provides: objs/common/CMakeFiles/common.dir/circular_buffer.o.requires
	$(MAKE) -f objs/common/CMakeFiles/common.dir/build.make objs/common/CMakeFiles/common.dir/circular_buffer.o.provides.build
.PHONY : objs/common/CMakeFiles/common.dir/circular_buffer.o.provides

objs/common/CMakeFiles/common.dir/circular_buffer.o.provides.build: objs/common/CMakeFiles/common.dir/circular_buffer.o
.PHONY : objs/common/CMakeFiles/common.dir/circular_buffer.o.provides.build

# Object files for target common
common_OBJECTS = \
"CMakeFiles/common.dir/IJob.o" \
"CMakeFiles/common.dir/CThread.o" \
"CMakeFiles/common.dir/MD5.o" \
"CMakeFiles/common.dir/CThreadManage.o" \
"CMakeFiles/common.dir/CPoolThread.o" \
"CMakeFiles/common.dir/JobDequeue.o" \
"CMakeFiles/common.dir/CTimerEventHandler.o" \
"CMakeFiles/common.dir/CEventThread.o" \
"CMakeFiles/common.dir/circular_buffer.o"

# External object files for target common
common_EXTERNAL_OBJECTS =

objs/game_lib/libcommon.a: objs/common/CMakeFiles/common.dir/IJob.o
objs/game_lib/libcommon.a: objs/common/CMakeFiles/common.dir/CThread.o
objs/game_lib/libcommon.a: objs/common/CMakeFiles/common.dir/MD5.o
objs/game_lib/libcommon.a: objs/common/CMakeFiles/common.dir/CThreadManage.o
objs/game_lib/libcommon.a: objs/common/CMakeFiles/common.dir/CPoolThread.o
objs/game_lib/libcommon.a: objs/common/CMakeFiles/common.dir/JobDequeue.o
objs/game_lib/libcommon.a: objs/common/CMakeFiles/common.dir/CTimerEventHandler.o
objs/game_lib/libcommon.a: objs/common/CMakeFiles/common.dir/CEventThread.o
objs/game_lib/libcommon.a: objs/common/CMakeFiles/common.dir/circular_buffer.o
objs/game_lib/libcommon.a: objs/common/CMakeFiles/common.dir/build.make
objs/game_lib/libcommon.a: objs/common/CMakeFiles/common.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library ../game_lib/libcommon.a"
	cd /home/gl/server/c_server/omgserver/db_server/objs/common && $(CMAKE_COMMAND) -P CMakeFiles/common.dir/cmake_clean_target.cmake
	cd /home/gl/server/c_server/omgserver/db_server/objs/common && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/common.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
objs/common/CMakeFiles/common.dir/build: objs/game_lib/libcommon.a
.PHONY : objs/common/CMakeFiles/common.dir/build

objs/common/CMakeFiles/common.dir/requires: objs/common/CMakeFiles/common.dir/IJob.o.requires
objs/common/CMakeFiles/common.dir/requires: objs/common/CMakeFiles/common.dir/CThread.o.requires
objs/common/CMakeFiles/common.dir/requires: objs/common/CMakeFiles/common.dir/MD5.o.requires
objs/common/CMakeFiles/common.dir/requires: objs/common/CMakeFiles/common.dir/CThreadManage.o.requires
objs/common/CMakeFiles/common.dir/requires: objs/common/CMakeFiles/common.dir/CPoolThread.o.requires
objs/common/CMakeFiles/common.dir/requires: objs/common/CMakeFiles/common.dir/JobDequeue.o.requires
objs/common/CMakeFiles/common.dir/requires: objs/common/CMakeFiles/common.dir/CTimerEventHandler.o.requires
objs/common/CMakeFiles/common.dir/requires: objs/common/CMakeFiles/common.dir/CEventThread.o.requires
objs/common/CMakeFiles/common.dir/requires: objs/common/CMakeFiles/common.dir/circular_buffer.o.requires
.PHONY : objs/common/CMakeFiles/common.dir/requires

objs/common/CMakeFiles/common.dir/clean:
	cd /home/gl/server/c_server/omgserver/db_server/objs/common && $(CMAKE_COMMAND) -P CMakeFiles/common.dir/cmake_clean.cmake
.PHONY : objs/common/CMakeFiles/common.dir/clean

objs/common/CMakeFiles/common.dir/depend:
	cd /home/gl/server/c_server/omgserver/db_server && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gl/server/c_server/omgserver/db_server /home/gl/server/c_server/omgserver/common /home/gl/server/c_server/omgserver/db_server /home/gl/server/c_server/omgserver/db_server/objs/common /home/gl/server/c_server/omgserver/db_server/objs/common/CMakeFiles/common.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : objs/common/CMakeFiles/common.dir/depend

