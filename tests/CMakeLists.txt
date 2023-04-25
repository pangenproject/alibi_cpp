set (Boost_USE_STATIC_LIBS OFF)
project("tests")
find_package(Boost REQUIRED COMPONENTS unit_test_framework)
find_package(Boost COMPONENTS filesystem thread system REQUIRED)

set(CMAKE_CXX_STANDARD 17)

set (TEST_SOURCE_FILES "${TEST_SOURCE_PATH}/test_block.cpp"
                       "${TEST_SOURCE_PATH}/test_graph.cpp")
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
cmake_minimum_required(VERSION 3.25)

if(Boost_FOUND)
    message(${Boost_INCLUDE_DIRS})
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable (Boost_Tests_run main.cpp test_read.cpp test_graph.cpp test_block.cpp test_sort.cpp)
    target_compile_definitions(Boost_Tests_run PRIVATE "BOOST_TEST_DYN_LINK=1")

    target_link_libraries(Boost_Tests_run ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
endif()

# 'Boost_Tests_run' is the target name
# 'test1.cpp tests2.cpp' are source files with tests
target_link_libraries (Boost_Tests_run ${Boost_LIBRARIES})