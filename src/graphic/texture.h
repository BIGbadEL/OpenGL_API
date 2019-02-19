//
// Created by grzegorz on 18.02.19.
//

#pragma once

namespace SandBox {
    class Texture {
    public:
        explicit Texture(const char* path);
        ~Texture();

        void Bind() const;

        inline int GetWidth() const { return _width; }
        inline int GetHeight() const { return _height; }
        inline int GetNumberOfChannels() const { return _nrChannels; }

    private:

        unsigned _id;
        int _width;
        int _height;
        int _nrChannels;
    };
}
//SANDBOX_TESTS_TEXTURE_H
