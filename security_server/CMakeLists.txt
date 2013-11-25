#cmake_minimum_required(VERSION 2.8)
#cmake_policy(SET CMP0015 OLD)
#if your os is ubuntu set libname as ubuntu ;if os is centos set libname as centos ;if os is qq's suse set libname as qq
set(libname "ubuntu")

PROJECT (flash_security_server)
MESSAGE(STATUS "building server...."${security_server_BINARY_DIR})
SET(CMAKE_BUILD_TYPE DEBUG)

SET(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -g")
#SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g")
#SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
INCLUDE_DIRECTORIES(../include)
AUX_SOURCE_DIRECTORY(./ DIR_SRCS)
ADD_SUBDIRECTORY(../net objs/net) 
ADD_SUBDIRECTORY(../common objs/common)
 
LINK_DIRECTORIES(/usr/local/lib)
LINK_DIRECTORIES(../libfor${libname})
MESSAGE("Linking libs ${libname}")
ADD_EXECUTABLE(serurity_server ${DIR_SRCS})
ADD_DEPENDENCIES(serurity_server net common)
TARGET_LINK_LIBRARIES(serurity_server net common  libgflags.so libglog.so libtinyxml.a xml2 libz.so)
