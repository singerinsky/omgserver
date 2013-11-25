CMAKE_MINIMUM_REQUIRED(VERSION 2.8)    

PROJECT(football_server)              

MESSAGE(STATUS "Project: SERVER")            
MESSAGE(STATUS "Project Directory: ${PROJECT_SOURCE_DIR}")

SET(CMAKE_BUILE_TYPE DEBUG)                 



INCLUDE_DIRECTORIES(./include )
ADD_SUBDIRECTORY(common)                             
ADD_SUBDIRECTORY(net)                             
ADD_SUBDIRECTORY(soccer_ai)                             
ADD_SUBDIRECTORY(gate_server/build)                             
ADD_SUBDIRECTORY(game_server/build)                             
ADD_SUBDIRECTORY(db_server/build)                             
