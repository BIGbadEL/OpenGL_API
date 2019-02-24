//
// Created by grzegorz on 23.02.19.
//

#include <iostream>
#include <cmath>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "src/graphic/window.h"
#include "src/graphic/shader.h"
#include "src/graphic/texture.h"

#include "src/camera/camera.h"

#include "src/events/event_manager.h"
#include <events/events.h>

#include <input/input_manager.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

constexpr int width = 800;
constexpr int height = 600;

void onResize(SandBox::Window* win, SandBox::Shader& shader);

void onCursorMoveLater(SandBox::Window* window, float& lastx, float& lasty, SandBox::Camera& camera);

void onCursorMove(SandBox::Window* window, float& lastx, float& lasty, SandBox::Camera& camera);

void onKeyPressed(SandBox::Camera& camera, float& dT, SandBox::Window* win);


struct VertexData{
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

int main() {

    SandBox::Window window(width, height, "Hello");

    SandBox::Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));
    float deltaTime = 0.0f;
    float lastX = 0.0f;
    float lastY = 0.0f;


    window.EnableDepthTest();

    float vertices[] = {
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,

            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,

            -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,

            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,

            -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    };

//    unsigned index[] = {
//            0, 1, 2,
//            2, 3, 0,
//
//            4, 5, 6,
//            6, 7, 4,
//
//            8, 9, 10,
//            10, 11, 8,
//
//            12, 13, 14,
//            14, 15, 12,
//
//            16, 17, 18,
//            18, 19, 16,
//
//            20, 21, 22,
//            22, 23, 20
//
//    };

    unsigned *indeces = new unsigned[100000];

    unsigned int offset = 0;

    for(int i = 0; i < 100000 - 6; i += 6, offset += 4){

        indeces[i + 0] = offset + 0;
        indeces[i + 1] = offset + 1;
        indeces[i + 2] = offset + 2;
        indeces[i + 3] = offset + 2;
        indeces[i + 4] = offset + 3;
        indeces[i + 5] = offset + 0;

    }

    //index buffer

    unsigned IBO;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 1000000 * sizeof(unsigned), indeces, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //end index buffer


    unsigned VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 1000000 * sizeof(float), nullptr, GL_DYNAMIC_DRAW);


    unsigned cubeVAO;

    glGenVertexArrays(1, &cubeVAO);
    glBindVertexArray(cubeVAO);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);



//    unsigned lampVAO;
//
//    glGenVertexArrays(1, &lampVAO);
//    glBindVertexArray(lampVAO);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
//    glEnableVertexAttribArray(0);
//
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindVertexArray(0);


    SandBox::Shader cube_shader("shaders/cube.vert", "shaders/cube.frag");
  //  SandBox::Shader lamp_shader("shaders/lamp.vert", "shaders/lamp.frag");

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(width) / static_cast<float>(height),
                                            0.1f, 100.0f);

    cube_shader.Bind();
    cube_shader.SetMat4("projection", projection);
    cube_shader.SetVec3("lightColor", glm::vec3(1.0f));
    glm::mat4 model(1.0f);
    cube_shader.SetMat4("model", model);
//    cube_shader.SetVec3("objectColor", glm::vec3(1.0f, 0.1f, 0.1f));

    SandBox::Texture tex("textures/wood.jpg");

    cube_shader.SetInt("tex", 0);

//    lamp_shader.Bind();
//    lamp_shader.SetMat4("projection", projection);



    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    int frame_count = 0;
    float prev_time = 0;

    glm::vec3 lightPos = glm::vec3(2.0f, 3.0f, 4.0f);

    SandBox::EventManager::Subscribe<SandBox::WindowResize>(SandBox::handle::sync, onResize, &window,
                                                            std::reference_wrapper(cube_shader));

    SandBox::EventManager::Subscribe<SandBox::CursorMove>(
            SandBox::handle::sync,
            onCursorMove, &window,
            std::reference_wrapper(lastX),
            std::reference_wrapper(lastY),
            std::reference_wrapper(camera)
    );

    SandBox::EventManager::Subscribe<SandBox::KeyPressed>(
            SandBox::handle::sync,
            onKeyPressed,
            std::reference_wrapper(camera),
            std::reference_wrapper(deltaTime),
            &window
    );

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    auto map_buffer = reinterpret_cast<VertexData*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));

    auto data = reinterpret_cast<VertexData*>(vertices);
    unsigned indexcount = 0;

    for(int h = 0; h < 10; ++h) {

        for (int x = -5; x <= 5; ++x) {

            glm::vec3 trans = glm::vec3(x, h, 0.0f);

            for(int i = 0; i < 24; ++i){
                map_buffer->pos = (data + i)->pos + trans;
                map_buffer->normal = (data + i)->normal;
                map_buffer->texCoords = (data + i)->texCoords;
                map_buffer++;
                indexcount += 1;
            }

        }

        for(int y = 1; y <= 10; ++y){

            glm::vec3 trans = glm::vec3(5, h, -y);

            for(int i = 0; i < 24; ++i){
                map_buffer->pos = (data + i)->pos + trans;
                map_buffer->normal = (data + i)->normal;
                map_buffer->texCoords = (data + i)->texCoords;

                map_buffer++;
                indexcount += 1;
            }

        }

        for (int x = -5; x < 5; ++x) {

            glm::vec3 trans = glm::vec3(x, h, -10.0f);

            for(int i = 0; i < 24; ++i){
                map_buffer->pos = (data + i)->pos + trans;
                map_buffer->normal = (data + i)->normal;
                map_buffer->texCoords = (data + i)->texCoords;

                map_buffer++;
                indexcount += 1;
            }

        }

        for(int y = 1; y <= 9; ++y){
            glm::vec3 trans = glm::vec3(-5.0f, h, -y);

            for(int i = 0; i < 24; ++i){
                map_buffer->pos = (data + i)->pos + trans;
                map_buffer->normal = (data + i)->normal;
                map_buffer->texCoords = (data + i)->texCoords;

                map_buffer++;
                indexcount += 1;
            }
        }

    }

    while (!window.ShouldClose()) {
        double time = glfwGetTime();

        deltaTime = static_cast<float>(time) - prev_time;

        window.Clear();

        cube_shader.Bind();

        lightPos += glm::vec3(static_cast<float>(glm::sin(time) / 100), 0.0f, static_cast<float>(glm::cos(time) / 100));

        cube_shader.SetMat4("view", camera.GetViewMatrix());
        cube_shader.SetVec3("lightPos", lightPos);
        cube_shader.SetVec3("cameraPos", camera.GetPosition());



        glActiveTexture(GL_TEXTURE0);
        tex.Bind();



        glBindVertexArray(cubeVAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

        glDrawElements(GL_TRIANGLES, indexcount, GL_UNSIGNED_INT, nullptr);

        glBindVertexArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


        window.Update();

        if (static_cast<int>(prev_time) != static_cast<int>(time)) {
            std::cout << "FPS: " << frame_count << '\n';
            frame_count = 0;
        }

        prev_time = static_cast<int>(time);
        frame_count++;



    }

    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &cubeVAO);
    delete[] indeces;

    return 0;
}

void onResize(SandBox::Window* win, SandBox::Shader& shader) {
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), win->getAspectRatio(), 0.1f, 100.0f);

    shader.Bind();
    shader.SetMat4("projection", projection);
}

void onCursorMoveLater(SandBox::Window* window, float& lastx, float& lasty, SandBox::Camera& camera) {
    double localx, localy;
    window->getMousePos(localx, localy);

    camera.MouseMovement(static_cast<float>(localx) - lastx, static_cast<float>(localy) - lasty);

    lastx = static_cast<float>(localx);
    lasty = static_cast<float>(localy);
}

void onCursorMove(SandBox::Window* window, float& lastx, float& lasty, SandBox::Camera& camera) {
    double x, y;
    window->getMousePos(x, y);
    lastx = static_cast<float>(x);
    lasty = static_cast<float>(y);

    SandBox::EventManager::Unsubscibe<SandBox::CursorMove>(1);

    SandBox::EventManager::Subscribe<SandBox::CursorMove>(
            SandBox::handle::sync,
            onCursorMoveLater,
            window,
            std::reference_wrapper(lastx),
            std::reference_wrapper(lasty),
            std::reference_wrapper(camera)
    );

//    glClearColor(static_cast<float>(x / window->getWidth()), static_cast<float>(y / window->getHeight()), 0.0f, 1.0f);
}

void onKeyPressed(SandBox::Camera& camera, float& dT, SandBox::Window* win) {

    if (SandBox::InputManager::isKeyPressed(SB_KEY_W)) {
        camera.Move(SandBox::Camera::Movement::forward, dT);
    }

    if (SandBox::InputManager::isKeyPressed(SB_KEY_A)) {
        camera.Move(SandBox::Camera::Movement::left, dT);
    }

    if (SandBox::InputManager::isKeyPressed(SB_KEY_S)) {
        camera.Move(SandBox::Camera::Movement::backward, dT);
    }

    if (SandBox::InputManager::isKeyPressed(SB_KEY_D)) {
        camera.Move(SandBox::Camera::Movement::right, dT);
    }

    if (SandBox::InputManager::isKeyPressed(SB_KEY_Q)) {
        camera.Move(SandBox::Camera::Movement::up, dT);
    }

    if (SandBox::InputManager::isKeyPressed(SB_KEY_E)) {
        camera.Move(SandBox::Camera::Movement::down, dT);
    }

    if (SandBox::InputManager::isKeyPressed(SB_KEY_ESCAPE)) {
        win->Close();
    }

}


