# Задание 5.III. CMakeLists.txt для тестов.
# Здесь подключается GoogleTest и создаётся исполняемый файл с тестами.

cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(my_tests_proj VERSION 0.3.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---------------------------------------------------------------------------
# Подключение GoogleTest.
# Способ 1 (основной): скачать googletest на этапе конфигурации через FetchContent.
# ---------------------------------------------------------------------------
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.15.2
)

# Для Windows: не переопределять настройки компилятора/линкера родительского проекта.
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Если рядом лежит заранее скачанная копия googletest, можно указать её так:
#   cmake -S . -B build -DFETCHCONTENT_SOURCE_DIR_GOOGLETEST=path/to/googletest

FetchContent_MakeAvailable(googletest)

# ---------------------------------------------------------------------------
# Способ 2: использовать уже установленный GoogleTest.
# Тогда вместо блока выше достаточно:
#   find_package(GTest CONFIG REQUIRED)
# и цель называется GTest::gtest_main (так же, как при FetchContent).
# ---------------------------------------------------------------------------

# Включаем механизм тестов CTest.
enable_testing()

# Исполняемый файл с тестами.
add_executable(my_tests my_tests.cpp)

# Подключаем библиотеку с функциями и саму библиотеку GoogleTest.
target_link_libraries(my_tests PUBLIC mylib)
target_link_libraries(my_tests PUBLIC GTest::gtest_main)

# Подключаем GoogleTest, чтобы тесты автоматически находились для CTest.
include(GoogleTest)
gtest_discover_tests(my_tests)
