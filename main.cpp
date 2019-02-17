#include <iostream>

#include "src/graphic/window.h"
#include "src/graphic/shader.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>


#include <cmath>

constexpr int width = 800;
constexpr int height = 600;

int main() {

    SandBox::Window window(width, height, "Hello");

    /// Wierzchołki dla standardowego trójkąta
    /*float vertices[] = {
            0.0f, 0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f
    };*/
    /// Wierzchołki dla 2 trójkątów
    float vertices[] = {
            /// Position          Color
             0.0f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
             0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f
    };


    unsigned VAO;
    unsigned VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(3*sizeof(float)));

    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

//    unsigned shader = LoadShader("shaders/shader.vert", "shaders/shader.frag");
    SandBox::Shader shader("shaders/shader.vert", "shaders/shader.frag");

    glClearColor(0.4f, 0.4f, 0.6f, 1.0f);

    while(!window.ShouldClose()){
        double x,y;
        window.getMousePos(x, y);

        float timeX, timeY;
        timeX = static_cast<float>(sin(glfwGetTime() / 2.0));
        timeY = static_cast<float>(cos(glfwGetTime() / 2.0));


        window.Clear();

        glClearColor(static_cast<float>(x / window.getWidth()), static_cast<float>(y / window.getHeight()), 0.0f, 1.0f);

        shader.Bind();

//        glUniform2f(glGetUniformLocation(shader, "PositionOffset"), timeX, timeY);
        shader.SetVec2("PositionOffset", timeX, timeY);

        glBindVertexArray(VAO);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        window.Update();
    }

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);

    return 0;
}




