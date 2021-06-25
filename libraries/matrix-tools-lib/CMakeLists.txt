cmake_minimum_required(VERSION 3.19)

project(matrix-tools-lib)

add_library(${PROJECT_NAME} STATIC
        src/MatrixFileParser.cpp
        )

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        )