cmake_minimum_required(VERSION 3.30)
project(archive)

set(CMAKE_CXX_STANDARD 23)

add_executable(archive main.cpp
        archiver.h
        archiver.cpp
)
