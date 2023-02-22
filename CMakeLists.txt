# cmake 最小版本要求
cmake_minimum_required(VERSION 3.0)

if(${CMAKE_VERSION} VERSION_LESS 3.0)

cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})

endif()

project(POKER_GAME VERSION 1.0
				  DESCRIPTION "POKER_GAME"
				  LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Debug)

include_directories(./include)

aux_source_directory(./src src)

add_executable(server.out ${src})

