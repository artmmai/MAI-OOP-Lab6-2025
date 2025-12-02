cmake_minimum_required(VERSION 3.10)
project(MAI-OOP-LABS)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Подключение Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY false
)
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE LAB_SOURCES "src/*.cpp")
add_library(lab6_lib STATIC ${LAB_SOURCES})
target_include_directories(lab6_lib PUBLIC include)

# Исполняемый файл
add_executable(lab6_exe main.cpp)
target_link_libraries(lab6_exe lab6_lib)

# Тесты
file(GLOB_RECURSE TEST_SOURCES "test/*.cpp")
add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests lab6_lib gtest_main)

enable_testing()
add_test(NAME Lab06-Tests COMMAND tests)
