cmake_minimum_required(VERSION 3.26)
project(lut)

set(CMAKE_CXX_STANDARD 20)

add_library(lut INTERFACE)
include_directories(lut include)
find_package(Microsoft.GSL CONFIG REQUIRED)

add_subdirectory(tests)