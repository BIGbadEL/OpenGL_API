//
// Created by grzegorz on 17.02.19.
//

#include "shader.h"

#include "glad/glad.h"

namespace SandBox{

    Shader::Shader(const char* vertPath, const char* fragPath) {
        std::string vertexSrc = read_file(vertPath);
        std::string fragmentSrc = read_file(fragPath);
        const char* vertCode = vertexSrc.c_str();
        const char* fragCode = fragmentSrc.c_str();

        unsigned vert, frag;
        int success;

        char infoLog[512];

        vert = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vert, 1, &vertCode, nullptr);
        glCompileShader(vert);

        glGetShaderiv(vert, GL_COMPILE_STATUS, &success);
        if(!success){
            glGetShaderInfoLog(vert, 512, nullptr, infoLog);
            std::cout << "Error:VertexShader:Compilation: " << infoLog << '\n';
        }

        frag = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(frag, 1, &fragCode, nullptr);
        glCompileShader(frag);


        glGetShaderiv(frag, GL_COMPILE_STATUS, &success);
        if(!success){
            glGetShaderInfoLog(frag, 512, nullptr, infoLog);
            std::cout << "Error:FragmentShader:Compilation: " << infoLog << '\n';
        }

        _id = glCreateProgram();
        glAttachShader(_id, vert);
        glAttachShader(_id, frag);

        glLinkProgram(_id);

        glGetProgramiv(_id, GL_LINK_STATUS, &success);
        if(!success){
            glGetProgramInfoLog(_id, 512, nullptr, infoLog);
            std::cout << "Error:ShaderProgram:Compilation: " << infoLog << '\n';
        }

        glDeleteShader(vert);
        glDeleteShader(frag);

    }

    void Shader::Bind() const {
        glUseProgram(_id);
    }

    void Shader::SetInt(const char* name, int value) {
        glUniform1i(glGetUniformLocation(_id, name), value);
    }

    void Shader::SetFloat(const char* name, float value) {
        glUniform1f(glGetUniformLocation(_id, name), value);
    }

    void Shader::SetBool(const char* name, bool value) {
        glUniform1i(glGetUniformLocation(_id, name), value);
    }

    void Shader::SetVec2(const char* name, float x, float y) {
        glUniform2f(glGetUniformLocation(_id, name), x, y);
    }

    void Shader::SetVec3(const char* name, float x, float y, float z) {
        glUniform3f(glGetUniformLocation(_id, name), x, y, z);
    }

    void Shader::SetVec4(const char* name, float x, float y, float z, float w) {
        glUniform4f(glGetUniformLocation(_id, name), x, y, z, w);
    }
}
