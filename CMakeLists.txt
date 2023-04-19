cmake_minimum_required(VERSION 3.25)
project(alibi_cpp)

set(CMAKE_CXX_STANDARD 17)


add_executable(alibi_cpp src/Graph.cpp src/Graph.h src/Block.cpp src/Block.h src/sort.cpp src/sort.h)
