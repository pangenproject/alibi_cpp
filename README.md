# ALIBI - Algorithm for Linearization by Incremental graph BuIlding in C++

## Requirements

The minimum required CMake version for compilation is 3.25.

## Configuration

The project uses C++17 standard.

## Project Structure

```
alibicpp/
    ├── CMakeLists.txt
    ├── main.cpp
    ├── src/
    │   ├── Block.cpp
    │   ├── Block.h
    │   ├── Graph.cpp
    │   ├── Graph.h
    │   ├── linsort.cpp
    │   ├── linsort.h
    │   ├── read.cpp
    │   └── read.h
    └── build/
```

## Compilation

To compile the project, follow these steps:

1. Create the "build" directory:

```
mkdir build
cd build
```

2. Run CMake:

```
cmake ..
```

3. Compile the project (e.g., using Make on Linux):

```
make
```

## Executable File

After successful compilation, an executable file named "alibicpp" will be created in the "build" directory.

## Modules

The project consists of the following modules:

1. `Block` - implements functions for blocks in the project.

2. `Graph` - contains the implementation of the graph.

3. `linsort` - module for linear sorting.

4. `read` - contains functions for data reading.

## Notes

Make sure that the source files are placed in the appropriate project directories before compilation.

This documentation aims to facilitate the use of the "alibicpp" project and may be supplemented as needed.
