cmake_minimum_required(VERSION 3.14)
project(src)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(src
        DPPDiversity.cpp
        DPPDiversity.h
        main.cpp)
