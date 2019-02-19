#include <iostream>

#include "src/graphic/window.h"
#include "src/graphic/shader.h"
#include "src/Events/event_manager.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "src/graphic/texture.h"

#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Events/events.h>

constexpr int width = 800;
constexpr int height = 600;

void onResize(SandBox::Window* win){
    std::cout << win->getWidth() << " x " << win->getHeight() << '\n';
}

void onCursorMove(SandBox::Window* window){
    double x,y;
    window->getMousePos(x, y);
    glClearColor(static_cast<float>(x / window->getWidth()), static_cast<float>(y / window->getHeight()), 0.0f, 1.0f);
}

int main() {



    SandBox::Window window(width, height, "Hello");

    SandBox::EventManager::AddCallback<SandBox::WindowResize>(onResize, &window);
    SandBox::EventManager::AddCallback<SandBox::CursorMove>(onCursorMove, &window);

    glEnable(GL_DEPTH_TEST); //TODO: move to window

    float vertices[] = {
            /// position         texCoord
            /// Tył
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            /// Przód
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            /// Lewa strona
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            /// Prawa strona
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            /// Dół
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            /// Góra
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };




    unsigned VAO;
    unsigned VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(3*sizeof(float)));
    glEnableVertexAttribArray(1);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //texture

    SandBox::Texture texture("textures/wood.jpg");

    SandBox::Texture texture2("textures/krolik.png");

    //end texture

    SandBox::Shader shader("shaders/shader.vert", "shaders/shader.frag");

    shader.Bind();
    shader.SetInt("texture1", 0);
    shader.SetInt("texture2", 1);

    glm::mat4 view(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    shader.SetMat4("view", view);

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(width) / static_cast<float>(height), 0.1f, 100.0f);

    shader.SetMat4("projection", projection);

    glClearColor(0.4f, 0.4f, 0.6f, 1.0f);

    int frame_count = 0;
    int prev_time = 0;

    while(!window.ShouldClose()){
        double time = glfwGetTime();

        window.Clear();

        shader.Bind();

        glm::mat4 model(1.0f);

        model = rotate(model, static_cast<float>(glfwGetTime()), glm::vec3(1.0f, 0.5f, 0.0f));
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));

        shader.SetMat4("model", model);

        glActiveTexture(GL_TEXTURE0);
        texture.Bind();

        glActiveTexture(GL_TEXTURE1);
        texture2.Bind();

        glBindVertexArray(VAO);

        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        model = glm::mat4(1.0f);
         model = glm::translate(model, glm::vec3(0.0f,1.0f,0.0f)); // sześcian będzie na orbicie punktu (0,1,0).
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f,1.0f,0.0f));
        model = glm::translate(model, glm::vec3(1.0f, 0.0f,0.0f));
        model = glm::scale(model, glm::vec3(0.2f, 1.0f,1.0f));
        shader.SetMat4("model", model);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);


        window.Update();

        if(prev_time != static_cast<int>(time)){
            std::cout << "FPS: " << frame_count << '\n';
            frame_count = 0;
        }

        prev_time = static_cast<int>(time);
        frame_count++;

        SandBox::EventManager::Flush(2);
    }

    SandBox::EventManager::CleanUp();

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);

    return 0;
}




