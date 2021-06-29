cmake_minimum_required(VERSION 3.19)

get_filename_component(Path "${CMAKE_CURRENT_SOURCE_DIR}/../" ABSOLUTE)
get_filename_component(Library ${Path} NAME)

project("${Library}-test")


add_executable(${PROJECT_NAME}
        NoZeroElementsMatrix2x2Tests.cpp
        NonSquareMatrixTests.cpp
        DeterminantZeroSquareMatrixTests.cpp NoZeroElementsMatrix3x3Tests.cpp)

target_link_libraries(${PROJECT_NAME}
        gtest_main
        gmock_main
        ${Library})
