//
// Created by grzegorz on 20.02.19.
//

#include <memory>
#include <cstring>

#include "input_manager.h"
#include "events/event_manager.h"
#include "events/events.h"



namespace SandBox {

    std::array<bool, SB_KEY_LAST>  InputManager::_KeyStatus;
    std::array<bool, SB_MOUSE_BUTTON_LAST> InputManager::_ButtonStatus;

    void InputManager::Init() {
        std::memset(_KeyStatus.begin(), false, SB_KEY_LAST);
        std::memset(_ButtonStatus.begin(), false, SB_MOUSE_BUTTON_LAST);
    }

    void InputManager::Update() {
        for(auto i : _KeyStatus){
            if(i){
                EventManager::Emit<KeyPressed>();
                break;
            }
        }

        for(auto i : _ButtonStatus){
            if(i){
                EventManager::Emit<ButtonPressed>();
                break;
            }
        }
    }

}