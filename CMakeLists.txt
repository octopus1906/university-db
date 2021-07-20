cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC utils.cpp test.cpp)

set(DIR_TEST test)
set(SRC_TEST ${DIR_TEST}/test_catch2.cpp ${DIR_TEST}/catch_main.cpp ${DIR_TEST}/catch_amalgamated.cpp)

set(FLAGS -Wall -Werror -Wextra -Wpedantic -O3)

project(universityDB)

add_library(${PROJECT_NAME}-lib STATIC ${SRC})
target_compile_options(${PROJECT_NAME}-lib PRIVATE ${FLAGS})

find_package(Catch2 REQUIRED)
add_executable(${PROJECT_NAME}-test ${SRC_TEST} ${SRC})
target_link_libraries(${PROJECT_NAME}-test PRIVATE Catch2::Catch2)
target_compile_options(${PROJECT_NAME}-test PRIVATE ${FLAGS})
include(CTest)
include(Catch)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib)
target_compile_options(${PROJECT_NAME} PRIVATE ${FLAGS})

catch_discover_tests(${PROJECT_NAME}-test)
