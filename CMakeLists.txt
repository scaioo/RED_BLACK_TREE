cmake_minimum_required(VERSION 3.10)

# Name of the project
project(RedBlackTreeProject VERSION 1.0 LANGUAGES CXX)

# Specify the c++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add 'include' directory for .h files
include_directories(include)

# find source files in the src directory
file(GLOB SOURCES "src/*.cpp")

# Create final executable from source files
add_executable(rbt_tree ${SOURCES})

# Test Base: 
add_executable(test_basic tests/test_basic.cpp src/RedBlackTree.cpp)

# Test Stress: 
add_executable(test_stress tests/test_stress.cpp src/RedBlackTree.cpp)

# Test performance
add_executable(test_performance tests/test_performance.cpp src/RedBlackTree.cpp)