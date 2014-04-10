CMAKE_MINIMUM_REQUIRED(VERSION 2.8)    

PROJECT(football_server)              

MESSAGE(STATUS "Project: SERVER")            

SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -std=c++11 -O0 -Wall -g -D_GNU_SOURCE -fPIC")

SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -std=c++11 -O3 -Wall -g -D_GNU_SOURCE -fPIC")

INCLUDE_DIRECTORIES(./include )

SET(CMAKE_BUILD_TYPE DEBUG)
ADD_SUBDIRECTORY(net build/net) 
ADD_SUBDIRECTORY(common build/common)
ADD_SUBDIRECTORY(orm build/orm)
ADD_SUBDIRECTORY(message build/message_lib)


ADD_SUBDIRECTORY(gate_server/build)                             
#ADD_SUBDIRECTORY(game_server/build)                             
ADD_SUBDIRECTORY(db_server/build)                             
