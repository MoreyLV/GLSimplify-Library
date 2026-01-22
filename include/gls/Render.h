//
// Created by Morey on 20/01/2026.
//

#ifndef GLSIMPLIFY_RENDER_H
#define GLSIMPLIFY_RENDER_H

#include "gls/Mesh.h"
#include "gls/Shader.h"


namespace gls {
    class Render {
    public:
        Render();
        void draw(const Mesh& mesh, Shader& shader) const;

    private:
        struct Impl;
        Impl* impl;
    };
}



#endif //GLSIMPLIFY_RENDER_H