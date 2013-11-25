#cmake_minimum_required(VERSION 2.8)
#cmake_policy(SET CMP0015 OLD)

#set the lib in this os 
#if your os is ubuntu set libname as ubuntu ;if os is centos set libname as centos ;if os is qq's suse set libname as qq
set(libname "qq")

#set out put path

SET(LIBRARY_OUTPUT_PATH ../../game_lib)
SET(EXECUTABLE_OUTPUT_PATH ../../game_exe)


PROJECT (gate_server)
MESSAGE(STATUS "building gate_server"${gate_server_BINARY_DIR})
SET(CMAKE_BUILD_TYPE DEBUG)
ADD_DEFINITIONS(-D_QQ_PLATM_)
#本地才有
ADD_DEFINITIONS(-D_MY_DEBUG_)
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g")

SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

INCLUDE_DIRECTORIES(../../include)
AUX_SOURCE_DIRECTORY(../ DIR_SRCS)
#ADD_SUBDIRECTORY(../../net ../../objs/net) 
#ADD_SUBDIRECTORY(../../common ../../objs/common)  
LINK_DIRECTORIES(/usr/local/lib)

LINK_DIRECTORIES(../../libfor${libname})
MESSAGE("Linking libs ${libname}")

ADD_EXECUTABLE(gate_server ${DIR_SRCS})
ADD_DEPENDENCIES(gate_server net common)
TARGET_LINK_LIBRARIES(gate_server net common libgflags.so libglog.so libtinyxml.a libz.so boost_system)

