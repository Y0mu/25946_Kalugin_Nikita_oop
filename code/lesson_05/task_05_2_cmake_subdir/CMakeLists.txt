# Задание 5.II. Корневой CMakeLists.txt проекта.
# Отличие от 5.I: библиотека лежит в отдельной поддиректории my_lib,
# поэтому её подключаем через add_subdirectory.

cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(oop_task_05_2 VERSION 0.2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra)
endif()

# Обрабатываем директорию с библиотекой: там свой CMakeLists.txt,
# который создаёт цель mylib.
add_subdirectory(my_lib)

# Исполняемый файл программы.
add_executable(exec_trg main.cpp)

# Связываем программу с библиотекой. Благодаря PUBLIC в target_include_directories
# заголовки my_lib.h и my_random.h находятся автоматически.
target_link_libraries(exec_trg PUBLIC mylib)
