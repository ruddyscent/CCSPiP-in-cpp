cmake_minimum_required(VERSION 3.5)

project(chapter4)

set(CMAKE_CXX_STANDARD 17)

add_executable(edge edge.cc)
add_executable(graph graph.cc)
add_executable(weighted_edge weighted_edge.cc)
add_executable(weighted_graph weighted_graph.cc)
add_executable(mst mst.cc)
add_executable(dijkstra dijkstra.cc)
