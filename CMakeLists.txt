cmake_minimum_required(VERSION 3.13)
project(tsi CXX)

set(CMAKE_CXX_STANDARD 17)

add_library(tsi INTERFACE)
target_include_directories(tsi INTERFACE include)
