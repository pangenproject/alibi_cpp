cmake_minimum_required(VERSION 3.25)
project(alibi_cpp)

set(CMAKE_CXX_STANDARD 17)


add_executable(alibi_cpp src/read.cpp src/read.h src/linsort.cpp src/linsort.h src/Graph.cpp src/Graph.h src/Block.cpp src/Block.h )
