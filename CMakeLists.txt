cmake_minimum_required(VERSION 3.25)
project(alibi_cpp)

set(CMAKE_CXX_STANDARD 17)

add_executable(alibi_cpp main.cpp Graph.cpp Graph.h Block.cpp Block.h sort.cpp sort.h)
