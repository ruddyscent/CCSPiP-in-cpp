cmake_minimum_required(VERSION 3.5)

project(chapter2)

set(CMAKE_CXX_STANDARD 2a)

add_executable(dna_search dna_search.cc)
add_executable(maze maze.cc)
add_executable(missionaries missionaries.cc)