cmake_minimum_required(VERSION 3.5)

project(chapter4)

set(CMAKE_CXX_STANDARD 17)

add_executable(edge edge.cpp)
add_executable(graph graph.cpp)
add_executable(weighted_edge weighted_edge.cpp)
add_executable(weighted_graph weighted_graph.cpp)
add_executable(mst mst.cpp)
add_executable(dijkstra dijkstra.cpp)
