CMAKE_MINIMUM_REQUIRED(VERSION 2.8)    

PROJECT(football_server)              

MESSAGE(STATUS "Project: SERVER")            

SET(CMAKE_BUILE_TYPE DEBUG)                 
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -D_GNU_SOURCE -fPIC")

INCLUDE_DIRECTORIES(./include )
ADD_SUBDIRECTORY(gate_server/build)                             
#ADD_SUBDIRECTORY(game_server/build)                             
ADD_SUBDIRECTORY(db_server/build)                             
