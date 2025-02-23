cmake_minimum_required(VERSION 3.30)
project(archivate)

set(CMAKE_CXX_STANDARD 20)

add_executable(archivate main.cpp
        archiver.h
        archiver.cpp)
