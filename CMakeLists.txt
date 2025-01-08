
cmake_minimum_required(VERSION 3.10)

project(LabyrinthProject VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_COMPILER clang++)

include_directories(${CMAKE_SOURCE_DIR}/header)

set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/labyrinth/gen_labyrinth.cpp
    ${CMAKE_SOURCE_DIR}/src/labyrinth/labyrinth.cpp
    ${CMAKE_SOURCE_DIR}/src/items/item.cpp
    ${CMAKE_SOURCE_DIR}/src/items/hammer.cpp
    ${CMAKE_SOURCE_DIR}/src/items/shield.cpp
    ${CMAKE_SOURCE_DIR}/src/items/sword.cpp
    ${CMAKE_SOURCE_DIR}/src/items/war_mist.cpp
    ${CMAKE_SOURCE_DIR}/src/utils.cpp
)

add_executable(labyrinth ${SOURCES})
