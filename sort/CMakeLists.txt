cmake_minimum_required(VERSION 3.8)
project(test_sort)
find_package(GTest)

add_executable(test_sort test_sort.cpp sort.h)
target_link_libraries(test_sort gtest gtest_main pthread)
enable_testing()