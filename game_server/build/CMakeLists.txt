cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0015 OLD)
#set the lib in this os 
#if your os is ubuntu set libname as ubuntu ;if os is centos set libname as centos ;if os is qq's suse set libname as qq
set(libname "ubuntu")

SET(EXECUTABLE_OUTPUT_PATH ../../game_exe)

PROJECT (game_server)
MESSAGE(STATUS "building game_server" ${game_server_BINARY_DIR})
SET(CMAKE_BUILD_TYPE DEBUG)

SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g ")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall ")
INCLUDE_DIRECTORIES(../../include)
AUX_SOURCE_DIRECTORY(../ DIR_SRCS)
LINK_DIRECTORIES(/usr/local/lib)
LINK_DIRECTORIES(../../game_lib)

LINK_DIRECTORIES(../../libfor${libname})
MESSAGE("Linking libs ${libname}")

ADD_EXECUTABLE(game_server ${DIR_SRCS})
ADD_DEPENDENCIES(game_server net common soccer_ai)
#TARGET_LINK_LIBRARIES(game_server net common soccer_ai libgflags.so libglog.so libtinyxml.a xml2 libz.so libprofiler.so)
TARGET_LINK_LIBRARIES(game_server net common soccer_ai libgflags.so libglog.so libtinyxml.a xml2 libz.so pthread)
