cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0015 OLD)
#set the lib in this os 
#if your os is ubuntu set libname as ubuntu ;if os is centos set libname as centos ;if os is qq's suse set libname as qq

SET(LIBRARY_OUTPUT_PATH ../../game_lib)
SET(EXECUTABLE_OUTPUT_PATH ../../game_exe)

PROJECT (db_server)
MESSAGE(STATUS "building db_server"${db_server_BINARY_DIR})
SET(CMAKE_BUILD_TYPE DEBUG)
#SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -std=c++11 -O0 -Wall -g -D_GNU_SOURCE -fPIC")
#SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall  ")
INCLUDE_DIRECTORIES(../../include)
AUX_SOURCE_DIRECTORY(../ DIR_SRCS)
 
LINK_DIRECTORIES(/usr/local/lib)
LINK_DIRECTORIES(../../game_lib)

ADD_EXECUTABLE(db_server ${DIR_SRCS})
#ADD_DEPENDENCIES(db_server net common mysqlpp)
TARGET_LINK_LIBRARIES(db_server net common orm message_lib libgflags.so libglog.so libtinyxml.a mysqlclient mysqlpp pthread libprotobuf.a)
