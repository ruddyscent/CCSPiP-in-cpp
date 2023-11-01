cmake_minimum_required(VERSION 3.5)

project(chapter2)

set(CMAKE_CXX_STANDARD 20)

add_executable(dna_search dna_search.cpp)
add_executable(maze maze.cpp)
add_executable(missionaries missionaries.cpp)