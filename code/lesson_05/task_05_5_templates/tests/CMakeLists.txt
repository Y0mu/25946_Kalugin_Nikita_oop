# Задание 5.V. CMakeLists.txt для тестов шаблонной библиотеки.
# По сравнению с 5.IV почти ничего не изменилось: шаблоны видны тестам
# через тот же target_include_directories(mylib PUBLIC include).

cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(my_tests_proj VERSION 0.5.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.15.2
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(my_tests my_tests.cpp)

# mylib отдаёт свои заголовки наружу (PUBLIC include), поэтому отдельно
# прописывать target_include_directories для тестов не нужно.
target_link_libraries(my_tests PUBLIC mylib)
target_link_libraries(my_tests PUBLIC GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(my_tests)

message(STATUS "Тесты шаблонной библиотеки подключены")
