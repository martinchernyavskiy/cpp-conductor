cmake_minimum_required(VERSION 3.10)
project(Conductor)
set(CMAKE_CXX_STANDARD 11)

# Find GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Library
add_library(threadpool threadpool.cpp)

# Tests
add_executable(conductor_tests tests.cpp)
target_link_libraries(conductor_tests threadpool ${GTEST_LIBRARIES} pthread)