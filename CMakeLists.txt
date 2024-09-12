cmake_minimum_required(VERSION 3.29)
project(program1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(program1
    database.cpp
    database.h
    personal.cpp
    personal.h
    student.cpp
    student.h)
