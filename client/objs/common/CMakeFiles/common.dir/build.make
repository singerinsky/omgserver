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
CMAKE_SOURCE_DIR = /home/gl/workspace/omgserver/client

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gl/workspace/omgserver/client

# Include any dependencies generated for this target.
include objs/common/CMakeFiles/common.dir/depend.make

# Include the progress variables for this target.
include objs/common/CMakeFiles/common.dir/progress.make

# Include the compile flags for this target's objects.
include objs/common/CMakeFiles/common.dir/flags.make

objs/common/CMakeFiles/common.dir/CThreadManage.cpp.o: objs/common/CMakeFiles/common.dir/flags.make
objs/common/CMakeFiles/common.dir/CThreadManage.cpp.o: /home/gl/workspace/omgserver/common/CThreadManage.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gl/workspace/omgserver/client/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object objs/common/CMakeFiles/common.dir/CThreadManage.cpp.o"
	cd /home/gl/workspace/omgserver/client/objs/common && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/common.dir/CThreadManage.cpp.o -c /home/gl/workspace/omgserver/common/CThreadManage.cpp

objs/common/CMakeFiles/common.dir/CThreadManage.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/common.dir/CThreadManage.cpp.i"
	cd /home/gl/workspace/omgserver/client/objs/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gl/workspace/omgserver/common/CThreadManage.cpp > CMakeFiles/common.dir/CThreadManage.cpp.i

objs/common/CMakeFiles/common.dir/CThreadManage.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/common.dir/CThreadManage.cpp.s"
	cd /home/gl/workspace/omgserver/client/objs/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gl/workspace/omgserver/common/CThreadManage.cpp -o CMakeFiles/common.dir/CThreadManage.cpp.s

objs/common/CMakeFiles/common.dir/CThreadManage.cpp.o.requires:
.PHONY : objs/common/CMakeFiles/common.dir/CThreadManage.cpp.o.requires

objs/common/CMakeFiles/common.dir/CThreadManage.cpp.o.provides: objs/common/CMakeFiles/common.dir/CThreadManage.cpp.o.requires
	$(MAKE) -f objs/common/CMakeFiles/common.dir/build.make objs/common/CMakeFiles/common.dir/CThreadManage.cpp.o.provides.build
.PHONY : objs/common/CMakeFiles/common.dir/CThreadManage.cpp.o.provides

objs/common/CMakeFiles/common.dir/CThreadManage.cpp.o.provides.build: objs/common/CMakeFiles/common.dir/CThreadManage.cpp.o

objs/common/CMakeFiles/common.dir/IJob.cpp.o: objs/common/CMakeFiles/common.dir/flags.make
objs/common/CMakeFiles/common.dir/IJob.cpp.o: /home/gl/workspace/omgserver/common/IJob.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gl/workspace/omgserver/client/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object objs/common/CMakeFiles/common.dir/IJob.cpp.o"
	cd /home/gl/workspace/omgserver/client/objs/common && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/common.dir/IJob.cpp.o -c /home/gl/workspace/omgserver/common/IJob.cpp

objs/common/CMakeFiles/common.dir/IJob.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/common.dir/IJob.cpp.i"
	cd /home/gl/workspace/omgserver/client/objs/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gl/workspace/omgserver/common/IJob.cpp > CMakeFiles/common.dir/IJob.cpp.i

objs/common/CMakeFiles/common.dir/IJob.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/common.dir/IJob.cpp.s"
	cd /home/gl/workspace/omgserver/client/objs/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gl/workspace/omgserver/common/IJob.cpp -o CMakeFiles/common.dir/IJob.cpp.s

objs/common/CMakeFiles/common.dir/IJob.cpp.o.requires:
.PHONY : objs/common/CMakeFiles/common.dir/IJob.cpp.o.requires

objs/common/CMakeFiles/common.dir/IJob.cpp.o.provides: objs/common/CMakeFiles/common.dir/IJob.cpp.o.requires
	$(MAKE) -f objs/common/CMakeFiles/common.dir/build.make objs/common/CMakeFiles/common.dir/IJob.cpp.o.provides.build
.PHONY : objs/common/CMakeFiles/common.dir/IJob.cpp.o.provides

objs/common/CMakeFiles/common.dir/IJob.cpp.o.provides.build: objs/common/CMakeFiles/common.dir/IJob.cpp.o

objs/common/CMakeFiles/common.dir/MD5.cpp.o: objs/common/CMakeFiles/common.dir/flags.make
objs/common/CMakeFiles/common.dir/MD5.cpp.o: /home/gl/workspace/omgserver/common/MD5.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gl/workspace/omgserver/client/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object objs/common/CMakeFiles/common.dir/MD5.cpp.o"
	cd /home/gl/workspace/omgserver/client/objs/common && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/common.dir/MD5.cpp.o -c /home/gl/workspace/omgserver/common/MD5.cpp

objs/common/CMakeFiles/common.dir/MD5.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/common.dir/MD5.cpp.i"
	cd /home/gl/workspace/omgserver/client/objs/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gl/workspace/omgserver/common/MD5.cpp > CMakeFiles/common.dir/MD5.cpp.i

objs/common/CMakeFiles/common.dir/MD5.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/common.dir/MD5.cpp.s"
	cd /home/gl/workspace/omgserver/client/objs/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gl/workspace/omgserver/common/MD5.cpp -o CMakeFiles/common.dir/MD5.cpp.s

objs/common/CMakeFiles/common.dir/MD5.cpp.o.requires:
.PHONY : objs/common/CMakeFiles/common.dir/MD5.cpp.o.requires

objs/common/CMakeFiles/common.dir/MD5.cpp.o.provides: objs/common/CMakeFiles/common.dir/MD5.cpp.o.requires
	$(MAKE) -f objs/common/CMakeFiles/common.dir/build.make objs/common/CMakeFiles/common.dir/MD5.cpp.o.provides.build
.PHONY : objs/common/CMakeFiles/common.dir/MD5.cpp.o.provides

objs/common/CMakeFiles/common.dir/MD5.cpp.o.provides.build: objs/common/CMakeFiles/common.dir/MD5.cpp.o

objs/common/CMakeFiles/common.dir/CPoolThread.cpp.o: objs/common/CMakeFiles/common.dir/flags.make
objs/common/CMakeFiles/common.dir/CPoolThread.cpp.o: /home/gl/workspace/omgserver/common/CPoolThread.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gl/workspace/omgserver/client/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object objs/common/CMakeFiles/common.dir/CPoolThread.cpp.o"
	cd /home/gl/workspace/omgserver/client/objs/common && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/common.dir/CPoolThread.cpp.o -c /home/gl/workspace/omgserver/common/CPoolThread.cpp

objs/common/CMakeFiles/common.dir/CPoolThread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/common.dir/CPoolThread.cpp.i"
	cd /home/gl/workspace/omgserver/client/objs/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gl/workspace/omgserver/common/CPoolThread.cpp > CMakeFiles/common.dir/CPoolThread.cpp.i

objs/common/CMakeFiles/common.dir/CPoolThread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/common.dir/CPoolThread.cpp.s"
	cd /home/gl/workspace/omgserver/client/objs/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gl/workspace/omgserver/common/CPoolThread.cpp -o CMakeFiles/common.dir/CPoolThread.cpp.s

objs/common/CMakeFiles/common.dir/CPoolThread.cpp.o.requires:
.PHONY : objs/common/CMakeFiles/common.dir/CPoolThread.cpp.o.requires

objs/common/CMakeFiles/common.dir/CPoolThread.cpp.o.provides: objs/common/CMakeFiles/common.dir/CPoolThread.cpp.o.requires
	$(MAKE) -f objs/common/CMakeFiles/common.dir/build.make objs/common/CMakeFiles/common.dir/CPoolThread.cpp.o.provides.build
.PHONY : objs/common/CMakeFiles/common.dir/CPoolThread.cpp.o.provides

objs/common/CMakeFiles/common.dir/CPoolThread.cpp.o.provides.build: objs/common/CMakeFiles/common.dir/CPoolThread.cpp.o

objs/common/CMakeFiles/common.dir/CThread.cpp.o: objs/common/CMakeFiles/common.dir/flags.make
objs/common/CMakeFiles/common.dir/CThread.cpp.o: /home/gl/workspace/omgserver/common/CThread.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gl/workspace/omgserver/client/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object objs/common/CMakeFiles/common.dir/CThread.cpp.o"
	cd /home/gl/workspace/omgserver/client/objs/common && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/common.dir/CThread.cpp.o -c /home/gl/workspace/omgserver/common/CThread.cpp

objs/common/CMakeFiles/common.dir/CThread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/common.dir/CThread.cpp.i"
	cd /home/gl/workspace/omgserver/client/objs/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gl/workspace/omgserver/common/CThread.cpp > CMakeFiles/common.dir/CThread.cpp.i

objs/common/CMakeFiles/common.dir/CThread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/common.dir/CThread.cpp.s"
	cd /home/gl/workspace/omgserver/client/objs/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gl/workspace/omgserver/common/CThread.cpp -o CMakeFiles/common.dir/CThread.cpp.s

objs/common/CMakeFiles/common.dir/CThread.cpp.o.requires:
.PHONY : objs/common/CMakeFiles/common.dir/CThread.cpp.o.requires

objs/common/CMakeFiles/common.dir/CThread.cpp.o.provides: objs/common/CMakeFiles/common.dir/CThread.cpp.o.requires
	$(MAKE) -f objs/common/CMakeFiles/common.dir/build.make objs/common/CMakeFiles/common.dir/CThread.cpp.o.provides.build
.PHONY : objs/common/CMakeFiles/common.dir/CThread.cpp.o.provides

objs/common/CMakeFiles/common.dir/CThread.cpp.o.provides.build: objs/common/CMakeFiles/common.dir/CThread.cpp.o

objs/common/CMakeFiles/common.dir/timer_manager.cpp.o: objs/common/CMakeFiles/common.dir/flags.make
objs/common/CMakeFiles/common.dir/timer_manager.cpp.o: /home/gl/workspace/omgserver/common/timer_manager.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gl/workspace/omgserver/client/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object objs/common/CMakeFiles/common.dir/timer_manager.cpp.o"
	cd /home/gl/workspace/omgserver/client/objs/common && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/common.dir/timer_manager.cpp.o -c /home/gl/workspace/omgserver/common/timer_manager.cpp

objs/common/CMakeFiles/common.dir/timer_manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/common.dir/timer_manager.cpp.i"
	cd /home/gl/workspace/omgserver/client/objs/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gl/workspace/omgserver/common/timer_manager.cpp > CMakeFiles/common.dir/timer_manager.cpp.i

objs/common/CMakeFiles/common.dir/timer_manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/common.dir/timer_manager.cpp.s"
	cd /home/gl/workspace/omgserver/client/objs/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gl/workspace/omgserver/common/timer_manager.cpp -o CMakeFiles/common.dir/timer_manager.cpp.s

objs/common/CMakeFiles/common.dir/timer_manager.cpp.o.requires:
.PHONY : objs/common/CMakeFiles/common.dir/timer_manager.cpp.o.requires

objs/common/CMakeFiles/common.dir/timer_manager.cpp.o.provides: objs/common/CMakeFiles/common.dir/timer_manager.cpp.o.requires
	$(MAKE) -f objs/common/CMakeFiles/common.dir/build.make objs/common/CMakeFiles/common.dir/timer_manager.cpp.o.provides.build
.PHONY : objs/common/CMakeFiles/common.dir/timer_manager.cpp.o.provides

objs/common/CMakeFiles/common.dir/timer_manager.cpp.o.provides.build: objs/common/CMakeFiles/common.dir/timer_manager.cpp.o

objs/common/CMakeFiles/common.dir/CEventThread.cpp.o: objs/common/CMakeFiles/common.dir/flags.make
objs/common/CMakeFiles/common.dir/CEventThread.cpp.o: /home/gl/workspace/omgserver/common/CEventThread.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gl/workspace/omgserver/client/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object objs/common/CMakeFiles/common.dir/CEventThread.cpp.o"
	cd /home/gl/workspace/omgserver/client/objs/common && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/common.dir/CEventThread.cpp.o -c /home/gl/workspace/omgserver/common/CEventThread.cpp

objs/common/CMakeFiles/common.dir/CEventThread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/common.dir/CEventThread.cpp.i"
	cd /home/gl/workspace/omgserver/client/objs/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gl/workspace/omgserver/common/CEventThread.cpp > CMakeFiles/common.dir/CEventThread.cpp.i

objs/common/CMakeFiles/common.dir/CEventThread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/common.dir/CEventThread.cpp.s"
	cd /home/gl/workspace/omgserver/client/objs/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gl/workspace/omgserver/common/CEventThread.cpp -o CMakeFiles/common.dir/CEventThread.cpp.s

objs/common/CMakeFiles/common.dir/CEventThread.cpp.o.requires:
.PHONY : objs/common/CMakeFiles/common.dir/CEventThread.cpp.o.requires

objs/common/CMakeFiles/common.dir/CEventThread.cpp.o.provides: objs/common/CMakeFiles/common.dir/CEventThread.cpp.o.requires
	$(MAKE) -f objs/common/CMakeFiles/common.dir/build.make objs/common/CMakeFiles/common.dir/CEventThread.cpp.o.provides.build
.PHONY : objs/common/CMakeFiles/common.dir/CEventThread.cpp.o.provides

objs/common/CMakeFiles/common.dir/CEventThread.cpp.o.provides.build: objs/common/CMakeFiles/common.dir/CEventThread.cpp.o

objs/common/CMakeFiles/common.dir/server_application.cpp.o: objs/common/CMakeFiles/common.dir/flags.make
objs/common/CMakeFiles/common.dir/server_application.cpp.o: /home/gl/workspace/omgserver/common/server_application.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gl/workspace/omgserver/client/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object objs/common/CMakeFiles/common.dir/server_application.cpp.o"
	cd /home/gl/workspace/omgserver/client/objs/common && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/common.dir/server_application.cpp.o -c /home/gl/workspace/omgserver/common/server_application.cpp

objs/common/CMakeFiles/common.dir/server_application.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/common.dir/server_application.cpp.i"
	cd /home/gl/workspace/omgserver/client/objs/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gl/workspace/omgserver/common/server_application.cpp > CMakeFiles/common.dir/server_application.cpp.i

objs/common/CMakeFiles/common.dir/server_application.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/common.dir/server_application.cpp.s"
	cd /home/gl/workspace/omgserver/client/objs/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gl/workspace/omgserver/common/server_application.cpp -o CMakeFiles/common.dir/server_application.cpp.s

objs/common/CMakeFiles/common.dir/server_application.cpp.o.requires:
.PHONY : objs/common/CMakeFiles/common.dir/server_application.cpp.o.requires

objs/common/CMakeFiles/common.dir/server_application.cpp.o.provides: objs/common/CMakeFiles/common.dir/server_application.cpp.o.requires
	$(MAKE) -f objs/common/CMakeFiles/common.dir/build.make objs/common/CMakeFiles/common.dir/server_application.cpp.o.provides.build
.PHONY : objs/common/CMakeFiles/common.dir/server_application.cpp.o.provides

objs/common/CMakeFiles/common.dir/server_application.cpp.o.provides.build: objs/common/CMakeFiles/common.dir/server_application.cpp.o

objs/common/CMakeFiles/common.dir/system_util.cpp.o: objs/common/CMakeFiles/common.dir/flags.make
objs/common/CMakeFiles/common.dir/system_util.cpp.o: /home/gl/workspace/omgserver/common/system_util.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gl/workspace/omgserver/client/CMakeFiles $(CMAKE_PROGRESS_9)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object objs/common/CMakeFiles/common.dir/system_util.cpp.o"
	cd /home/gl/workspace/omgserver/client/objs/common && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/common.dir/system_util.cpp.o -c /home/gl/workspace/omgserver/common/system_util.cpp

objs/common/CMakeFiles/common.dir/system_util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/common.dir/system_util.cpp.i"
	cd /home/gl/workspace/omgserver/client/objs/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gl/workspace/omgserver/common/system_util.cpp > CMakeFiles/common.dir/system_util.cpp.i

objs/common/CMakeFiles/common.dir/system_util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/common.dir/system_util.cpp.s"
	cd /home/gl/workspace/omgserver/client/objs/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gl/workspace/omgserver/common/system_util.cpp -o CMakeFiles/common.dir/system_util.cpp.s

objs/common/CMakeFiles/common.dir/system_util.cpp.o.requires:
.PHONY : objs/common/CMakeFiles/common.dir/system_util.cpp.o.requires

objs/common/CMakeFiles/common.dir/system_util.cpp.o.provides: objs/common/CMakeFiles/common.dir/system_util.cpp.o.requires
	$(MAKE) -f objs/common/CMakeFiles/common.dir/build.make objs/common/CMakeFiles/common.dir/system_util.cpp.o.provides.build
.PHONY : objs/common/CMakeFiles/common.dir/system_util.cpp.o.provides

objs/common/CMakeFiles/common.dir/system_util.cpp.o.provides.build: objs/common/CMakeFiles/common.dir/system_util.cpp.o

objs/common/CMakeFiles/common.dir/mtrand.cpp.o: objs/common/CMakeFiles/common.dir/flags.make
objs/common/CMakeFiles/common.dir/mtrand.cpp.o: /home/gl/workspace/omgserver/common/mtrand.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gl/workspace/omgserver/client/CMakeFiles $(CMAKE_PROGRESS_10)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object objs/common/CMakeFiles/common.dir/mtrand.cpp.o"
	cd /home/gl/workspace/omgserver/client/objs/common && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/common.dir/mtrand.cpp.o -c /home/gl/workspace/omgserver/common/mtrand.cpp

objs/common/CMakeFiles/common.dir/mtrand.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/common.dir/mtrand.cpp.i"
	cd /home/gl/workspace/omgserver/client/objs/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gl/workspace/omgserver/common/mtrand.cpp > CMakeFiles/common.dir/mtrand.cpp.i

objs/common/CMakeFiles/common.dir/mtrand.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/common.dir/mtrand.cpp.s"
	cd /home/gl/workspace/omgserver/client/objs/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gl/workspace/omgserver/common/mtrand.cpp -o CMakeFiles/common.dir/mtrand.cpp.s

objs/common/CMakeFiles/common.dir/mtrand.cpp.o.requires:
.PHONY : objs/common/CMakeFiles/common.dir/mtrand.cpp.o.requires

objs/common/CMakeFiles/common.dir/mtrand.cpp.o.provides: objs/common/CMakeFiles/common.dir/mtrand.cpp.o.requires
	$(MAKE) -f objs/common/CMakeFiles/common.dir/build.make objs/common/CMakeFiles/common.dir/mtrand.cpp.o.provides.build
.PHONY : objs/common/CMakeFiles/common.dir/mtrand.cpp.o.provides

objs/common/CMakeFiles/common.dir/mtrand.cpp.o.provides.build: objs/common/CMakeFiles/common.dir/mtrand.cpp.o

objs/common/CMakeFiles/common.dir/CTimerEventHandler.cpp.o: objs/common/CMakeFiles/common.dir/flags.make
objs/common/CMakeFiles/common.dir/CTimerEventHandler.cpp.o: /home/gl/workspace/omgserver/common/CTimerEventHandler.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gl/workspace/omgserver/client/CMakeFiles $(CMAKE_PROGRESS_11)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object objs/common/CMakeFiles/common.dir/CTimerEventHandler.cpp.o"
	cd /home/gl/workspace/omgserver/client/objs/common && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/common.dir/CTimerEventHandler.cpp.o -c /home/gl/workspace/omgserver/common/CTimerEventHandler.cpp

objs/common/CMakeFiles/common.dir/CTimerEventHandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/common.dir/CTimerEventHandler.cpp.i"
	cd /home/gl/workspace/omgserver/client/objs/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gl/workspace/omgserver/common/CTimerEventHandler.cpp > CMakeFiles/common.dir/CTimerEventHandler.cpp.i

objs/common/CMakeFiles/common.dir/CTimerEventHandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/common.dir/CTimerEventHandler.cpp.s"
	cd /home/gl/workspace/omgserver/client/objs/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gl/workspace/omgserver/common/CTimerEventHandler.cpp -o CMakeFiles/common.dir/CTimerEventHandler.cpp.s

objs/common/CMakeFiles/common.dir/CTimerEventHandler.cpp.o.requires:
.PHONY : objs/common/CMakeFiles/common.dir/CTimerEventHandler.cpp.o.requires

objs/common/CMakeFiles/common.dir/CTimerEventHandler.cpp.o.provides: objs/common/CMakeFiles/common.dir/CTimerEventHandler.cpp.o.requires
	$(MAKE) -f objs/common/CMakeFiles/common.dir/build.make objs/common/CMakeFiles/common.dir/CTimerEventHandler.cpp.o.provides.build
.PHONY : objs/common/CMakeFiles/common.dir/CTimerEventHandler.cpp.o.provides

objs/common/CMakeFiles/common.dir/CTimerEventHandler.cpp.o.provides.build: objs/common/CMakeFiles/common.dir/CTimerEventHandler.cpp.o

objs/common/CMakeFiles/common.dir/circular_buffer.cpp.o: objs/common/CMakeFiles/common.dir/flags.make
objs/common/CMakeFiles/common.dir/circular_buffer.cpp.o: /home/gl/workspace/omgserver/common/circular_buffer.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gl/workspace/omgserver/client/CMakeFiles $(CMAKE_PROGRESS_12)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object objs/common/CMakeFiles/common.dir/circular_buffer.cpp.o"
	cd /home/gl/workspace/omgserver/client/objs/common && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/common.dir/circular_buffer.cpp.o -c /home/gl/workspace/omgserver/common/circular_buffer.cpp

objs/common/CMakeFiles/common.dir/circular_buffer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/common.dir/circular_buffer.cpp.i"
	cd /home/gl/workspace/omgserver/client/objs/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gl/workspace/omgserver/common/circular_buffer.cpp > CMakeFiles/common.dir/circular_buffer.cpp.i

objs/common/CMakeFiles/common.dir/circular_buffer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/common.dir/circular_buffer.cpp.s"
	cd /home/gl/workspace/omgserver/client/objs/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gl/workspace/omgserver/common/circular_buffer.cpp -o CMakeFiles/common.dir/circular_buffer.cpp.s

objs/common/CMakeFiles/common.dir/circular_buffer.cpp.o.requires:
.PHONY : objs/common/CMakeFiles/common.dir/circular_buffer.cpp.o.requires

objs/common/CMakeFiles/common.dir/circular_buffer.cpp.o.provides: objs/common/CMakeFiles/common.dir/circular_buffer.cpp.o.requires
	$(MAKE) -f objs/common/CMakeFiles/common.dir/build.make objs/common/CMakeFiles/common.dir/circular_buffer.cpp.o.provides.build
.PHONY : objs/common/CMakeFiles/common.dir/circular_buffer.cpp.o.provides

objs/common/CMakeFiles/common.dir/circular_buffer.cpp.o.provides.build: objs/common/CMakeFiles/common.dir/circular_buffer.cpp.o

objs/common/CMakeFiles/common.dir/JobDequeue.cpp.o: objs/common/CMakeFiles/common.dir/flags.make
objs/common/CMakeFiles/common.dir/JobDequeue.cpp.o: /home/gl/workspace/omgserver/common/JobDequeue.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/gl/workspace/omgserver/client/CMakeFiles $(CMAKE_PROGRESS_13)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object objs/common/CMakeFiles/common.dir/JobDequeue.cpp.o"
	cd /home/gl/workspace/omgserver/client/objs/common && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/common.dir/JobDequeue.cpp.o -c /home/gl/workspace/omgserver/common/JobDequeue.cpp

objs/common/CMakeFiles/common.dir/JobDequeue.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/common.dir/JobDequeue.cpp.i"
	cd /home/gl/workspace/omgserver/client/objs/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/gl/workspace/omgserver/common/JobDequeue.cpp > CMakeFiles/common.dir/JobDequeue.cpp.i

objs/common/CMakeFiles/common.dir/JobDequeue.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/common.dir/JobDequeue.cpp.s"
	cd /home/gl/workspace/omgserver/client/objs/common && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/gl/workspace/omgserver/common/JobDequeue.cpp -o CMakeFiles/common.dir/JobDequeue.cpp.s

objs/common/CMakeFiles/common.dir/JobDequeue.cpp.o.requires:
.PHONY : objs/common/CMakeFiles/common.dir/JobDequeue.cpp.o.requires

objs/common/CMakeFiles/common.dir/JobDequeue.cpp.o.provides: objs/common/CMakeFiles/common.dir/JobDequeue.cpp.o.requires
	$(MAKE) -f objs/common/CMakeFiles/common.dir/build.make objs/common/CMakeFiles/common.dir/JobDequeue.cpp.o.provides.build
.PHONY : objs/common/CMakeFiles/common.dir/JobDequeue.cpp.o.provides

objs/common/CMakeFiles/common.dir/JobDequeue.cpp.o.provides.build: objs/common/CMakeFiles/common.dir/JobDequeue.cpp.o

# Object files for target common
common_OBJECTS = \
"CMakeFiles/common.dir/CThreadManage.cpp.o" \
"CMakeFiles/common.dir/IJob.cpp.o" \
"CMakeFiles/common.dir/MD5.cpp.o" \
"CMakeFiles/common.dir/CPoolThread.cpp.o" \
"CMakeFiles/common.dir/CThread.cpp.o" \
"CMakeFiles/common.dir/timer_manager.cpp.o" \
"CMakeFiles/common.dir/CEventThread.cpp.o" \
"CMakeFiles/common.dir/server_application.cpp.o" \
"CMakeFiles/common.dir/system_util.cpp.o" \
"CMakeFiles/common.dir/mtrand.cpp.o" \
"CMakeFiles/common.dir/CTimerEventHandler.cpp.o" \
"CMakeFiles/common.dir/circular_buffer.cpp.o" \
"CMakeFiles/common.dir/JobDequeue.cpp.o"

# External object files for target common
common_EXTERNAL_OBJECTS =

objs/game_lib/libcommon.a: objs/common/CMakeFiles/common.dir/CThreadManage.cpp.o
objs/game_lib/libcommon.a: objs/common/CMakeFiles/common.dir/IJob.cpp.o
objs/game_lib/libcommon.a: objs/common/CMakeFiles/common.dir/MD5.cpp.o
objs/game_lib/libcommon.a: objs/common/CMakeFiles/common.dir/CPoolThread.cpp.o
objs/game_lib/libcommon.a: objs/common/CMakeFiles/common.dir/CThread.cpp.o
objs/game_lib/libcommon.a: objs/common/CMakeFiles/common.dir/timer_manager.cpp.o
objs/game_lib/libcommon.a: objs/common/CMakeFiles/common.dir/CEventThread.cpp.o
objs/game_lib/libcommon.a: objs/common/CMakeFiles/common.dir/server_application.cpp.o
objs/game_lib/libcommon.a: objs/common/CMakeFiles/common.dir/system_util.cpp.o
objs/game_lib/libcommon.a: objs/common/CMakeFiles/common.dir/mtrand.cpp.o
objs/game_lib/libcommon.a: objs/common/CMakeFiles/common.dir/CTimerEventHandler.cpp.o
objs/game_lib/libcommon.a: objs/common/CMakeFiles/common.dir/circular_buffer.cpp.o
objs/game_lib/libcommon.a: objs/common/CMakeFiles/common.dir/JobDequeue.cpp.o
objs/game_lib/libcommon.a: objs/common/CMakeFiles/common.dir/build.make
objs/game_lib/libcommon.a: objs/common/CMakeFiles/common.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library ../game_lib/libcommon.a"
	cd /home/gl/workspace/omgserver/client/objs/common && $(CMAKE_COMMAND) -P CMakeFiles/common.dir/cmake_clean_target.cmake
	cd /home/gl/workspace/omgserver/client/objs/common && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/common.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
objs/common/CMakeFiles/common.dir/build: objs/game_lib/libcommon.a
.PHONY : objs/common/CMakeFiles/common.dir/build

objs/common/CMakeFiles/common.dir/requires: objs/common/CMakeFiles/common.dir/CThreadManage.cpp.o.requires
objs/common/CMakeFiles/common.dir/requires: objs/common/CMakeFiles/common.dir/IJob.cpp.o.requires
objs/common/CMakeFiles/common.dir/requires: objs/common/CMakeFiles/common.dir/MD5.cpp.o.requires
objs/common/CMakeFiles/common.dir/requires: objs/common/CMakeFiles/common.dir/CPoolThread.cpp.o.requires
objs/common/CMakeFiles/common.dir/requires: objs/common/CMakeFiles/common.dir/CThread.cpp.o.requires
objs/common/CMakeFiles/common.dir/requires: objs/common/CMakeFiles/common.dir/timer_manager.cpp.o.requires
objs/common/CMakeFiles/common.dir/requires: objs/common/CMakeFiles/common.dir/CEventThread.cpp.o.requires
objs/common/CMakeFiles/common.dir/requires: objs/common/CMakeFiles/common.dir/server_application.cpp.o.requires
objs/common/CMakeFiles/common.dir/requires: objs/common/CMakeFiles/common.dir/system_util.cpp.o.requires
objs/common/CMakeFiles/common.dir/requires: objs/common/CMakeFiles/common.dir/mtrand.cpp.o.requires
objs/common/CMakeFiles/common.dir/requires: objs/common/CMakeFiles/common.dir/CTimerEventHandler.cpp.o.requires
objs/common/CMakeFiles/common.dir/requires: objs/common/CMakeFiles/common.dir/circular_buffer.cpp.o.requires
objs/common/CMakeFiles/common.dir/requires: objs/common/CMakeFiles/common.dir/JobDequeue.cpp.o.requires
.PHONY : objs/common/CMakeFiles/common.dir/requires

objs/common/CMakeFiles/common.dir/clean:
	cd /home/gl/workspace/omgserver/client/objs/common && $(CMAKE_COMMAND) -P CMakeFiles/common.dir/cmake_clean.cmake
.PHONY : objs/common/CMakeFiles/common.dir/clean

objs/common/CMakeFiles/common.dir/depend:
	cd /home/gl/workspace/omgserver/client && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gl/workspace/omgserver/client /home/gl/workspace/omgserver/common /home/gl/workspace/omgserver/client /home/gl/workspace/omgserver/client/objs/common /home/gl/workspace/omgserver/client/objs/common/CMakeFiles/common.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : objs/common/CMakeFiles/common.dir/depend

