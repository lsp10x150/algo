cmake_minimum_required(VERSION 3.8)
project(test_symbol_tables)
find_package(GTest)

add_executable(test_symbol_tables test_symbol_tables.cpp symbol_tables.cpp symbol_tables.h)
target_link_libraries(test_symbol_tables gtest gtest_main pthread)
enable_testing()