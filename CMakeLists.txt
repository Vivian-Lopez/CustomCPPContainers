cmake_minimum_required(VERSION 3.31)
project(CustomContainers)

set(CMAKE_CXX_STANDARD 26)

add_executable(CustomContainers
        UniquePtr.cpp
        UniquePtr.h
        Vector.cpp
        Vector.h
        Singleton.cpp
        Singleton.h)
