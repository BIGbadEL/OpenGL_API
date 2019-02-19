cmake_minimum_required(VERSION 3.12)

add_subdirectory(${CMAKE_SOURCE_DIR}/vendor/glad/)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/utils/)

project(Sandbox_tests)

include_directories(${CMAKE_SOURCE_DIR}/vendor/glad/include/)
include_directories(${CMAKE_SOURCE_DIR}/vendor/)
include_directories(${CMAKE_SOURCE_DIR}/src/utils/)
include_directories(${CMAKE_SOURCE_DIR}/src/)

set(CMAKE_CXX_STANDARD 17)

add_executable(Sandbox_tests main.cpp
        src/graphic/window.cpp src/graphic/window.h
        src/graphic/shader.cpp src/graphic/shader.h
        src/graphic/texture.cpp src/graphic/texture.h
        src/Events/event.h src/strong_type/strong_type.h src/Events/event_manager.cpp src/Events/event_manager.h src/Events/events.h)

target_link_libraries(Sandbox_tests utils glad glfw3 GL X11 Xi Xrandr Xxf86vm Xinerama Xcursor rt m pthread dl ubsan )

configure_file(shaders/shader.frag shaders/shader.frag COPYONLY)
configure_file(shaders/shader.vert shaders/shader.vert COPYONLY)
configure_file(textures/lena.jpg textures/lena.jpg COPYONLY)
configure_file(textures/wood.jpg textures/wood.jpg COPYONLY)
configure_file("textures/krolik.png" "textures/krolik.png" COPYONLY)
