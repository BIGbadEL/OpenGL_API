//
// Created by grzegorz on 17.02.19.
//
#include "read_file.h"

namespace SandBox{
    std::string read_file(const char* path){
        FILE* file = fopen(path, "rt");

        if(file == nullptr){
            std::cout << "[read_file] Could not open file\n";
            return nullptr;
        }

        fseek(file, 0, SEEK_END);
        auto length = static_cast<unsigned long>(ftell(file));

        auto data = new char[length + 1];
        memset(data, 0, length + 1);

        fseek(file, 0, SEEK_SET);

        if(!fread(data, 1, length, file)){
            std::cout << "[read_file] Could not read file\n";
            fclose(file);
            delete[] data;
            return nullptr;
        }

        fclose(file);

        const std::string result(data);
        delete[] data;

        return result;
    }
}