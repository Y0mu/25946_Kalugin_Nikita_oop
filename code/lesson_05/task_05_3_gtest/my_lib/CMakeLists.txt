# Задание 5.III. CMakeLists.txt библиотеки (без изменений по сравнению с 5.II).

cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(mylib_proj VERSION 0.3.0 LANGUAGES CXX)

add_library(mylib STATIC
    my_lib.cpp
    my_lib.h
)

target_include_directories(mylib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
