cmake_minimum_required(VERSION 3.8)
project(test_graph)
find_package(GTest)

add_executable(test_graph test_graph.cpp graph.h graph.cpp)
target_link_libraries(test_graph gtest gtest_main pthread)
enable_testing()