cmake_minimum_required(VERSION 3.12)

project(stb_image)



add_library(stb_image STATIC stb_image.h)

install(
        TARGETS stb_image
        LIBRARY DESTINATION bin
        ARCHIVE DESTINATION bin
)

SET_TARGET_PROPERTIES(stb_image PROPERTIES LINKER_LANGUAGE C)
