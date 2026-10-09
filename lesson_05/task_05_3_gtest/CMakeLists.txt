# Задание 5.III. Корневой CMakeLists.txt: библиотека + тесты.

cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(oop_task_05_3 VERSION 0.3.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra)
endif()

# Сначала библиотека: цель mylib должна существовать, когда её будут
# подключать к тестам.
add_subdirectory(my_lib)

# Затем директория с тестами — здесь подключается GoogleTest
# и создаётся цель my_tests, связанная с mylib.
add_subdirectory(tests)

# Исполняемый файл программы.
add_executable(exec_trg main.cpp)

# Связываем программу с нашей библиотекой.
target_link_libraries(exec_trg PUBLIC mylib)
