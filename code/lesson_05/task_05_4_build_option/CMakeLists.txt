# Задание 5.IV. Корневой CMakeLists.txt с опцией BUILD_TESTS.
#
# Опция задаётся так:
#   cmake -S . -B build                  -> тесты собираются (BUILD_TESTS = ON по умолчанию)
#   cmake -S . -B build -DBUILD_TESTS=OFF -> тесты не собираются вообще

cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(oop_task_05_4 VERSION 0.4.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra)
endif()

# Главная опция проекта: включать или выключать тесты.
# ON — значение по умолчанию, OFF можно передать при конфигурации.
option(BUILD_TESTS "Собирать тесты вместе с библиотекой" ON)

# Библиотека нужна всегда.
add_subdirectory(my_lib)

# Директорию с тестами обрабатываем только если опция включена.
if(BUILD_TESTS)
    message(STATUS "BUILD_TESTS = ON: тесты будут собраны")
    add_subdirectory(tests)
else()
    message(STATUS "BUILD_TESTS = OFF: собираем без тестов")
endif()

# Исполняемый файл программы.
add_executable(exec_trg main.cpp)
target_link_libraries(exec_trg PUBLIC mylib)
