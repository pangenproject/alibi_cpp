cmake_minimum_required(VERSION 3.25)

# Ustaw standard C++ na C++17
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

# Kolorowanie kompilacji w zależności od systemu operacyjnego
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    # Dla GNU lub Clang
    add_compile_options(-Wall -Wextra)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=always")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # Dla Microsoft Visual C++
    add_compile_options(/W4)
    add_definitions(-D_USE_MATH_DEFINES) # Opcjonalne definicje
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif ()
