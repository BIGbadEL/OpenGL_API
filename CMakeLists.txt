cmake_minimum_required(VERSION 3.12)

add_subdirectory(${CMAKE_SOURCE_DIR}/vendor/glad/)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/utils/)

project(Sandbox_tests)

include_directories(${CMAKE_SOURCE_DIR}/vendor/glad/include/)
include_directories(${CMAKE_SOURCE_DIR}/vendor/)
include_directories(${CMAKE_SOURCE_DIR}/src/utils/)
include_directories(${CMAKE_SOURCE_DIR}/src/)

set(CMAKE_CXX_STANDARD 17)

#only for profiler
#add_compile_options( -g )

add_executable(Sandbox_tests main.cpp
        src/graphic/window.cpp           src/graphic/window.h
        src/graphic/shader.cpp           src/graphic/shader.h
        src/graphic/texture.cpp          src/graphic/texture.h
        src/events/event.h               src/events/events.h
        src/events/event_manager.cpp     src/events/event_manager.h
        src/input/key_codes.h            src/input/button_codes.h
        src/input/input_manager.cpp      src/input/input_manager.h
        src/camera/camera.cpp            src/camera/camera.h
        src/events/callback/callback.cpp src/events/callback/callback.h
        src/events/callback/function_handler.h
        src/events/callback/async_function_handler.h
        )

target_link_libraries(Sandbox_tests utils glad glfw3 GL X11 Xi Xrandr Xxf86vm Xinerama Xcursor rt m pthread dl ubsan )

configure_file(shaders/cube.frag    shaders/cube.frag COPYONLY)
configure_file(shaders/cube.vert    shaders/cube.vert COPYONLY)
configure_file(shaders/lamp.frag    shaders/lamp.frag COPYONLY)
configure_file(shaders/lamp.vert    shaders/lamp.vert COPYONLY)
configure_file(textures/lena.jpg      textures/lena.jpg COPYONLY)
configure_file(textures/wood.jpg      textures/wood.jpg COPYONLY)
configure_file("textures/krolik.png" "textures/krolik.png" COPYONLY)
