# Задание 5.I. Минимальный проект CMake со статической библиотекой.
# Библиотека и main.cpp лежат в одной директории, поэтому путей поиска не задаём.

# Минимальная версия CMake.
cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

# Название проекта, версия и язык.
project(oop_task_05_1 VERSION 0.1.0 LANGUAGES CXX)

# Стандарт языка C++17 и обязательное соответствие ему.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем предупреждения компилятора (для MSVC свои флаги).
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra)
endif()

# Собираем библиотеку mylib из двух пар файлов.
# STATIC — статическая библиотека; для динамической было бы SHARED.
add_library(mylib STATIC
    my_lib.cpp
    my_lib.h
    my_random.cpp
    my_random.h
)

# Чтобы заголовки библиотеки были видны и main.cpp, и (позже) тестам.
target_include_directories(mylib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Исполняемый файл программы.
add_executable(exec_trg main.cpp)

# Связываем программу с библиотекой.
target_link_libraries(exec_trg PUBLIC mylib)
