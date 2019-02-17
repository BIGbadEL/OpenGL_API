#include <iostream>

#include "src/graphic/window.h"
#include "glad/glad.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


unsigned int LoadShader(const char* vertPath, const char* fragPath);

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
            0.0f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f,
            0.0f, 0.5f, 0.0f,
            0.5f, 0.5f, 0.0f,
            0.5f, -0.5f, 0.0f
    };

    unsigned VAO;
    unsigned VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    unsigned shader = LoadShader("shaders/shader.vert", "shaders/shader.frag");


    while(!window.ShouldClose()){
        double x,y;
        window.getMousePos(x, y);

        window.Clear();

        glClearColor(static_cast<float>(x / window.getWidth()), static_cast<float>(y / window.getHeight()), 0.0f, 1.0f);

        glUseProgram(shader);

        glBindVertexArray(VAO);

        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        window.Update();
    }

    return 0;
}

unsigned int LoadShader(const char* vertexShaderPath, const char* fragmentShaderPath){

    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    ///mówimy że chcemy łapać wyjątki - w sumie to nie część openGLa ale komentuję bo mniej znana strona c++sa
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        /// otwieramy pliki
        vShaderFile.open(vertexShaderPath);
        fShaderFile.open(fragmentShaderPath);
        std::stringstream vShaderStream, fShaderStream;

        /// czytamy z plików do stringstreamów
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        /// zamykamy pliki
        vShaderFile.close();
        fShaderFile.close();

        /// wyciągamy dane z stringstreama do zwykłego stringa
        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    /// Kod z plików powinien być podany jako string w stylu C
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    /// Tworzymy podprogramy używane w shaderze
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    /// kompilujemy
    glCompileShader(vertex);

    /// wyłapujemy błędy kompilacji
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    };

    /// teraz to samo dla fragment shadera
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);

    /// ---------------------------------------------------------------------------------------------------------
    /// -----------------------TEN FRAGMENT MAGICZNIE SIE NIE SKOPIOWAŁ------------------------------------------
    /// -----------------------ale jak się okazuje czasami działa bez tego i tak---------------------------------
    /// -----------------------Nie zakładajcie że zawsze bo to nie jest standardowe zachowanie-------------------
    /// ---------------------------------------------------------------------------------------------------------
    /// fragment shader też trzeba skompilować
    glCompileShader(fragment);

    /// i sprawdzić błędy
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    };
    ///----------------------------------------------------------------------------------------------------------

    /// teraz łączymy podprogramy w jeden porządny shader program
    unsigned int ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    /// i wyłapujemy błędy linkowania
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    /// składowe można bezpiecznie usunąć, żeby nie śmiecić
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    /// zwracamy identyfikator shadera
    return ID;
}


