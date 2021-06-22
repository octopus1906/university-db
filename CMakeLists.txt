cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(universityDB)
set(sources 
    main.cpp 
    student.cpp 
    test.cpp
    )

add_executable(${PROJECT_NAME} ${sources})

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Wconversion)