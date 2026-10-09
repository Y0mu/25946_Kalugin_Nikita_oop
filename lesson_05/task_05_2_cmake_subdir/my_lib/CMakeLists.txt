# Задание 5.II. CMakeLists.txt для библиотеки внутри поддиректории my_lib.
# Корневой CMakeLists.txt подключает эту директорию через add_subdirectory(my_lib).

cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(mylib_proj VERSION 0.2.0 LANGUAGES CXX)

# Статическая библиотека mylib.
add_library(mylib STATIC
    my_lib.cpp
    my_lib.h
    my_random.cpp
    my_random.h
)

# Заголовки библиотеки видны всем, кто с ней связан (main.cpp и тесты).
target_include_directories(mylib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
