cmake_minimum_required(VERSION 3.8)
project(test_union_find)
find_package(GTest)

add_executable(test_union_find test_union_find.cpp union_find.h)
target_link_libraries(test_union_find gtest gtest_main pthread)
enable_testing()