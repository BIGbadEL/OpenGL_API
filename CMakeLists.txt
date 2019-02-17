cmake_minimum_required(VERSION 3.12)

add_subdirectory(${CMAKE_SOURCE_DIR}/vendor/glad/)

project(Sandbox_tests)

include_directories(${CMAKE_SOURCE_DIR}/vendor/glad/include/)
include_directories(${CMAKE_SOURCE_DIR}/src/utils/)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(
        -pedantic -Wall -g -Wextra -Wshadow
        -Wnon-virtual-dtor -Wold-style-cast -Wcast-align
        -Wunused -Woverloaded-virtual -Wpedantic -Wconversion
        -Wsign-conversion -Wnull-dereference -Wdouble-promotion
        -Wformat=2 -Wduplicated-cond -Wduplicated-branches -Wlogical-op
        -Wuseless-cast -fsanitize=leak -fsanitize=undefined
        #-fsanitize=kernel-address -fsanitize=pointer-compare -fsanitize=pointer-subtract
        )

add_executable(Sandbox_tests main.cpp src/graphic/window.cpp src/graphic/window.h src/graphic/shader.cpp src/graphic/shader.h src/utils/read_file.h src/utils/read_file.cpp)

target_link_libraries(Sandbox_tests glad glfw3 GL X11 Xi Xrandr Xxf86vm Xinerama Xcursor rt m pthread dl ubsan )

configure_file(shaders/shader.frag shaders/shader.frag COPYONLY)
configure_file(shaders/shader.vert shaders/shader.vert COPYONLY)
