//
// Created by grzegorz on 20.02.19.
//

#pragma once

#include <array>

#include "key_codes.h"
#include "button_codes.h"

class GLFWwindow;
#define GLFW_RELEASE                0

namespace SandBox {
    class InputManager {

        friend void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

        friend void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);


    public:
        InputManager() = delete;

        static void Init();
        static void Update();

        static inline bool isKeyPressed(int keycode){ return _KeyStatus.at(keycode); }
        static inline bool isButtonPressed(int buttoncode){ return _ButtonStatus.at(buttoncode); }

    private:
        static std::array<bool, SB_KEY_LAST>  _KeyStatus;
        static std::array<bool, SB_MOUSE_BUTTON_LAST> _ButtonStatus;
    };

    inline void key_callback([[maybe_unused]] GLFWwindow *window, int key, [[maybe_unused]] int scancode, int action,
                             [[maybe_unused]] int mods) {
        SandBox::InputManager::_KeyStatus[key] = action != GLFW_RELEASE;
    }

    inline void mouse_button_callback([[maybe_unused]] GLFWwindow *window, int button, int action, [[maybe_unused]] int mods) {
        SandBox::InputManager::_ButtonStatus[button] = action != GLFW_RELEASE;
    }
}

 //SANDBOX_TESTS_INPUT_MANAGER_H
