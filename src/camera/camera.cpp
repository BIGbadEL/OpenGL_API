//
// Created by grzegorz on 20.02.19.
//

#include <iostream>
#include "camera.h"

namespace SandBox {

    void SandBox::Camera::Move(SandBox::Camera::Movement direction, float dt) {
        float velocity = dt * _speed;

        switch (direction) {
            case Movement::forward:
                _position += _front * velocity;
                break;
            case Movement::backward:
                _position -= _front * velocity;
                break;
            case Movement::right:
                _position += _right * velocity;
                break;
            case Movement::left:
                _position -= _right * velocity;
                break;
        }

    }

    void Camera::MouseMovement(float xoffset, float yoffset) {
        yaw += xoffset * _mouseSensitivity;
        pitch -= yoffset * _mouseSensitivity;

        if (pitch > 89.0f) {
            pitch = 89.0f;
        } else if (pitch < -89.0f) {
            pitch = -89.0f;
        }

        UpdateMembers();
    }

    void Camera::UpdateMembers() {
        glm::vec3 front;

        float p = glm::radians(pitch);
        float y = glm::radians(yaw);
        front.x = glm::cos(p) * glm::cos(y);
        front.y = glm::sin(p);
        front.z = glm::cos(p) * glm::sin(y);

        _front = glm::normalize(front);
        _right = glm::normalize(glm::cross(_front, _worldUp));
        _up = glm::normalize(glm::cross(_right, front));

    }

}