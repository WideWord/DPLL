cmake_minimum_required(VERSION 3.0)
project(DPLL)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES source/main.cpp source/DPLLTester.cpp source/DPLLTester.hpp source/CNFExpression.cpp source/CNFExpression.hpp)
add_executable(DPLL ${SOURCE_FILES})
