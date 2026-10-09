# Задание 5.V. Корневой CMakeLists.txt: шаблонная библиотека + тесты + опция.

cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(oop_task_05_5 VERSION 0.5.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra)
endif()

# Опция из задания 5.IV осталась: тесты можно включать и выключать.
option(BUILD_TESTS "Собирать тесты вместе с библиотекой" ON)

# Библиотека (теперь шаблонная, заголовки в include/my_lib).
add_subdirectory(my_lib)

# Тесты — только если опция включена.
if(BUILD_TESTS)
    message(STATUS "BUILD_TESTS = ON: тесты будут собраны")
    add_subdirectory(tests)
else()
    message(STATUS "BUILD_TESTS = OFF: собираем без тестов")
endif()

# Исполняемый файл программы.
add_executable(exec_trg main.cpp)
target_link_libraries(exec_trg PUBLIC mylib)
