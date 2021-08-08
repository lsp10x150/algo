cmake_minimum_required(VERSION 3.8)
project(test_priority_queue)
find_package(GTest)

add_executable(test_priority_queue test_priority_queue.cpp priority_queue.h)
target_link_libraries(test_priority_queue gtest gtest_main pthread)
enable_testing()