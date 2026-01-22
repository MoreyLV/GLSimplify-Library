//
// Created by Morey on 05/01/2026.
//

#ifndef GLSIMPLIFY_CONTEXTSETTINGS_H
#define GLSIMPLIFY_CONTEXTSETTINGS_H
#include "../../src/backends/sfml/ContextFlags.h"

namespace gls {
    struct ContextSettings {
        int depthBits = 24;
        int stencilBits = 8;
        int antialiasingLevel = 0;
        int majorVersion = 3;
        int minorVersion = 3;
        ContextFlags flag = Core;
    };
};




#endif //GLSIMPLIFY_CONTEXTSETTINGS_H