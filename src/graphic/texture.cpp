//
// Created by grzegorz on 18.02.19.
//

#include "texture.h"
#include "utils_file.h"

#include "glad/glad.h"

namespace SandBox {

    Texture::Texture(const char* path) {
        unsigned char* data = load_img(path, &_width, &_height, &_nrChannels);
        glGenTextures(1, &_id);

        Bind();

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        if(data != nullptr){

            switch(_nrChannels) {
                case 0: std::cout << data << std::endl; break;
                case 1: glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, _width, _height, 0, GL_RED, GL_UNSIGNED_BYTE, data); break;
                case 2: glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, _width, _height, 0, GL_RG, GL_UNSIGNED_BYTE, data); break;
                case 3: glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, data); break;
                case 4: glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); break;
                default: std::cout << "Channel: " << _nrChannels << "not supported\n"; break;
            }

            glGenerateMipmap(GL_TEXTURE_2D);

        } else {
            std::cout << "Could not load texture \n";
        }

        glBindTexture(GL_TEXTURE_2D, 0);

        free_img(data);
    }

    Texture::~Texture() {
        glDeleteTextures(1, &_id);
    }

    void Texture::Bind() const {
        glBindTexture(GL_TEXTURE_2D, _id);
    }



}