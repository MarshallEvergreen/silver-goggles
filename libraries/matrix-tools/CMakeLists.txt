cmake_minimum_required(VERSION 3.19)

project(matrix-tools)

add_subdirectory(test)

add_library(${PROJECT_NAME} STATIC
        src/Matrix.cpp src
        src/MatrixExceptions.cpp
        )

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        )