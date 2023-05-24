cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 17)


project(alibicpp)

# Dodaj plik main.cpp jako główny plik źródłowy
add_executable(alibicpp main.cpp)

# Dodaj moduły Block.h i Block.cpp
add_library(Block src/Block.cpp src/Block.h)
add_library(Graph src/Graph.cpp src/Graph.h)
add_library(linsort src/linsort.cpp src/linsort.h)
add_library(read src/read.cpp src/read.h)

# Podłącz moduły do głównego pliku źródłowego
target_link_libraries(alibicpp Block Graph linsort read)