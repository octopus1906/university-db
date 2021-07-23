cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC utils.cpp test.cpp)

set(FLAGS -Wall -Werror -Wextra -Wpedantic -O3)

project(universityDB)

add_library(${PROJECT_NAME}-lib STATIC ${SRC})
target_compile_options(${PROJECT_NAME}-lib PRIVATE ${FLAGS})

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib)
target_compile_options(${PROJECT_NAME} PRIVATE ${FLAGS})
