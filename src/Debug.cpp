//
// Created by Morey on 21/01/2026.
//

#include "../include/gls/Debug.h"
#include <glad/glad.h>
#include <iostream>

namespace gls {

    void checkGLError(const char* where) {
        GLenum err;
        while ((err = glGetError()) != GL_NO_ERROR) {
            std::cerr
                << "[OpenGL ERROR] "
                << err
                << " at "
                << where
                << std::endl;
        }
    }

}
