//
// Created by grzegorz on 17.02.19.
//

#pragma once

#include "read_file.h"

namespace SandBox {

    class Shader {
    public:
        Shader(const char* vertPath, const char* fragPath);

        void Bind() const;

        void SetInt(const char* name, int value);
        void SetFloat(const char* name, float value);
        void SetBool(const char* name, bool value);
        void SetVec2(const char* name, float x, float y);
        void SetVec3(const char* name, float x, float y, float z);
        void SetVec4(const char* name, float x, float y, float z, float w);

    private:
        unsigned _id;
    };

}
//SANDBOX_TESTS_SHADER_H
