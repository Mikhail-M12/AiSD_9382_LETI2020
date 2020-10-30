cmake_minimum_required(VERSION 3.17)
project(lr3)

set(CMAKE_CXX_STANDARD 20)

add_executable(lr3 main.cpp api.cpp api.h bintree.cpp bintree.h)