//
// Created by grzegorz on 20.02.19.
//

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace SandBox {

    class Camera {
    public:
        explicit Camera(glm::vec3 pos)
        :_position(pos), _worldUp(0.0f, 1.0f, 0.0f), _speed(0.025f), _mouseSensitivity(0.1f), pitch(0.0f), yaw(-90.0f) { UpdateMembers(); }

        inline glm::mat4 GetViewMatrix() const { return glm::lookAt(_position, _position + _front, _up); }

        enum class Movement{
            forward, backward, left, right
        };

        void Move(Movement direction, float dt);

        void MouseMovement( float xoffset, float yoffset);

    private:
        void UpdateMembers();

    private:
        glm::vec3 _position;
        glm::vec3 _worldUp;
        glm::vec3 _front;
        glm::vec3 _right;
        glm::vec3 _up;

        float _speed;
        float _mouseSensitivity;

        float pitch;
        float yaw;

    };

}
//SANDBOX_TESTS_CAMERA_H
