CMAKE_MINIMUM_REQUIRED(VERSION 2.8)    

PROJECT(football_server)              

MESSAGE(STATUS "Project: SERVER")            

SET(CMAKE_BUILE_TYPE DEBUG)                 
SET(CMAKE_CXX_FLAGS_DEBUG "g++ -O0 -Wall -g")
SET(CMAKE_CXX_FLAGS_RELEASE "g++ -O3 -Wall")

INCLUDE_DIRECTORIES(./include )
ADD_SUBDIRECTORY(soccer_ai)                             
ADD_SUBDIRECTORY(gate_server/build)                             
ADD_SUBDIRECTORY(game_server/build)                             
ADD_SUBDIRECTORY(db_server/build)                             
