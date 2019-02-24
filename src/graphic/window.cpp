//
// Created by grzegorz on 17.02.19.
//

#include <iostream>
#include "window.h"

#include "events/event.h"
#include "events/events.h"
#include "events/event_manager.h"

#include "input/input_manager.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace SandBox {
    Window::Window(int width, int height, const char* name): _width(width), _height(height), _name(name) {
        Init();
        InputManager::Init();
    }

    Window::~Window() {
        glfwDestroyWindow(_window);
        glfwTerminate();
        SandBox::EventManager::CleanUp();
    }

    void cursor_position_callback(GLFWwindow* window, double xPos, double yPos){
        auto temp = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));

        temp->_x = xPos;
        temp->_y = yPos;

        EventManager::Emit<CursorMove>();

    }

    void window_size_callback(GLFWwindow* window, int width, int height) {
        auto temp = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));

        temp->_width = width;
        temp->_height = height;

        glViewport(0, 0, width, height);

        EventManager::Emit<WindowResize>();

    }

    void Window::Init() {

        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        _window = glfwCreateWindow(_width, _height, _name, nullptr, nullptr);

        if(!_window){
            std::cout << "Failed to creat GLFW window" << '\n';
        }

        glfwMakeContextCurrent(_window);

        if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))){
            std::cout << "Failed to initialize GLAD" << std::endl;
            glfwTerminate();
            return;
        }

        glViewport(0, 0, _width, _height);

        glfwSetWindowUserPointer(_window, this);

        glfwSetWindowSizeCallback(_window, window_size_callback);
        glfwSetCursorPosCallback(_window, cursor_position_callback);
        glfwSetKeyCallback(_window, key_callback);
        glfwSetMouseButtonCallback(_window, mouse_button_callback);

        glfwSwapInterval(0);

        std::cout << "OpenGL: " << glGetString(GL_VERSION) << '\n';
        std::cout << "Vendor: " << glGetString(GL_VENDOR) << '\n';
        std::cout << "Renderer: " << glGetString(GL_RENDERER) << '\n';
        std::cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << '\n';

    }

    void Window::Update() const {
        SandBox::EventManager::Flush();
        glfwSwapBuffers(_window);
        glfwPollEvents();
        InputManager::Update();

        GLenum error = glGetError();
        if(error != GL_NO_ERROR){
            std::cout << "OpenGL ERROR:" << error << std::endl;
        }
    }

    bool Window::ShouldClose() const {
        return glfwWindowShouldClose(_window) != 0;
    }

    void Window::Clear() const {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Window::EnableDepthTest() {
        glEnable(GL_DEPTH_TEST);
    }

    void Window::Close() const {
        glfwSetWindowShouldClose(_window, true);
    }


}