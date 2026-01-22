//
// Created by Morey on 20/01/2026.
//

#include "../include/gls/Render.h"
#include <glad/glad.h>
#include <iostream>

#include "gls/Debug.h"

namespace gls{
    struct Render::Impl {
        GLuint VAO, EBO;
        int vertexCount, indexCount;
    };

    Render::Render() : impl(new Impl) {}
    void Render::draw(const Mesh& mesh, Shader& shader) const{
        shader.use();

        mesh.bind();

        if (mesh.isIndexed()) {
             GL_CHECK(glDrawElements(GL_TRIANGLES, impl->indexCount, GL_UNSIGNED_INT, nullptr));
        }else {
                 GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, impl->vertexCount));
        }
        mesh.unbind();
    };
}
