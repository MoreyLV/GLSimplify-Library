//
// Created by Morey on 21/01/2026.
//

#ifndef GLSIMPLIFY_DEBUG_H
#define GLSIMPLIFY_DEBUG_H

#ifdef GLS_DEBUG
    #include <iostream>
    #include <glad/glad.h>

    namespace gls {
        void checkGLError(const char* where);
    }

#define GL_CHECK(x) \
do { \
x; \
gls::checkGLError(#x); \
} while(0)

#define GL_CHECK_RET(x) \
([&]() { \
auto _res = (x); \
gls::checkGLError(#x); \
return _res; \
})()

#else

#define GL_CHECK(x) x
#define GL_CHECK_RET(x) x

#endif

#endif //GLSIMPLIFY_DEBUG_H