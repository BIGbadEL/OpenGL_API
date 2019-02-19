//
// Created by grzegorz on 17.02.19.
//

#pragma once

#include <cstring>
#include <string>
#include <iostream>

namespace SandBox{
    std::string read_file(const char* path);

    unsigned char* load_img(const char* path, int* width, int* height, int* nrChannels);

    void free_img(unsigned char* data);
}

 //SANDBOX_TESTS_READ_FILE_H
