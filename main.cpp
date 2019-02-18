#include <iostream>

#include "src/graphic/window.h"
#include "src/graphic/shader.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include <cmath>

constexpr int width = 800;
constexpr int height = 600;

int main() {

    SandBox::Window window(width, height, "Hello");

    float vertices[] = {
            ///Pierwszy trójkąt.
            /// Position          Color              TexCoords
            -0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  0.0f, 1.0f,    /// lewy górny wierzchołek - wsp : (0, 1)
            -0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  0.0f, 0.0f,    /// lewy dolny wierzchołek - wsp : (0, 0)
            0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,  1.0f, 0.0f,    ///prawy dolny wierzchołek - wsp : (1, 0)

            ///Drugi trójkąt.
            /// Position          Color              TexCoords
            -0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  0.0f, 1.0f,    /// lewy górny wierzchołek - wsp : (0, 1)
            0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,  1.0f, 0.0f,    ///prawy dolny wierzchołek - wsp : (1, 0)
            0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,  1.0f, 1.0f     ///prawy górny wierzchołek - wsp : (1, 1)
    };



    unsigned VAO;
    unsigned VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(6*sizeof(float)));
    glEnableVertexAttribArray(2);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //texture

    stbi_set_flip_vertically_on_load(true);

    int t_width, t_height, t_nrChannels;

    unsigned char* data = stbi_load("textures/wood.jpg", &t_width, &t_height, &t_nrChannels, 0);

    unsigned texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if(data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, t_width, t_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else std::cerr << "Failed to load image" << std::endl;

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(data);

    data = stbi_load("textures/lena.jpg", &t_width, &t_height, &t_nrChannels, 0);
    unsigned texture2;
    glGenTextures(1, &texture2);

    std::cout << t_width << "x" << t_height << " " << texture2 <<'\n';

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if(data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, t_width, t_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else std::cerr << "Failed to load image" << std::endl;

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(data);

    //end texture

    SandBox::Shader shader("shaders/shader.vert", "shaders/shader.frag");

    shader.SetInt("texture1", 0);
    shader.SetInt("texture2", 1);

    glClearColor(0.4f, 0.4f, 0.6f, 1.0f);

    int frame_count = 0;
    int prev_time = 0;

    while(!window.ShouldClose()){
        double x,y;
        window.getMousePos(x, y);

        double time = glfwGetTime();

        window.Clear();

        glClearColor(static_cast<float>(x / window.getWidth()), static_cast<float>(y / window.getHeight()), 0.0f, 1.0f);

        shader.Bind();

        glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE0);


        glBindTexture(GL_TEXTURE_2D, texture2);
        glActiveTexture(GL_TEXTURE1);

        glBindVertexArray(VAO);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        window.Update();

        if(prev_time != static_cast<int>(time)){
            std::cout << "FPS: " << frame_count << '\n';
            frame_count = 0;
        }

        prev_time = static_cast<int>(time);
        frame_count++;
    }

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);

    return 0;
}




