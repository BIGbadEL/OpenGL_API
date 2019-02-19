cmake_minimum_required(VERSION 3.12)

project(utils)

include_directories(${CMAKE_SOURCE_DIR}/vendor/)

add_compile_options( -O3 )

add_library(utils utils_file.h utils_file.cpp)


install(
        TARGETS utils
        LIBRARY DESTINATION bin
        ARCHIVE DESTINATION bin
)