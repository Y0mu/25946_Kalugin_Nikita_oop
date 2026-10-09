# Задание 5.IV. CMakeLists.txt для тестов.
# Полностью повторяет 5.III, но обрабатывается только при BUILD_TESTS = ON.

cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(my_tests_proj VERSION 0.4.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- Подключение GoogleTest через FetchContent (скачивание при конфигурации) ----
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.15.2
)

# Для Windows: не переопределять настройки CRT родительского проекта.
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

# Включаем тесты CTest.
enable_testing()

add_executable(my_tests my_tests.cpp)

target_link_libraries(my_tests PUBLIC mylib)
target_link_libraries(my_tests PUBLIC GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(my_tests)

message(STATUS "Тесты подключены: цель my_tests")
