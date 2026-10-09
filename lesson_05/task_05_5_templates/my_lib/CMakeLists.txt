# Задание 5.V. CMakeLists.txt библиотеки.
# Появилась отдельная директория include/my_lib, поэтому путь к заголовкам
# отдаём наружу через target_include_directories(... PUBLIC include).

cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(mylib_proj VERSION 0.5.0 LANGUAGES CXX)

# Библиотека состоит из заголовков с шаблонами и одного cpp-файла.
add_library(mylib STATIC
    src/my_lib.cpp
)

# Директория include/my_lib становится доступной всем, кто связан с mylib:
# и main.cpp, и тестам. Поэтому подключаем заголовки как "my_lib/my_lib.h".
target_include_directories(mylib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Шаблоны должны инстанцироваться в том, кто их использует, поэтому
# никаких хитростей с явным инстанцированием не нужно.
