//
// Created by Morey on 16/01/2026.
//

#include <glad/glad.h>
#include <iostream>
#include "../include/gls/Mesh.h"

#include "gls/Debug.h"

namespace gls {
    struct Mesh::Impl {
        GLuint VAO, VBO, EBO;
        int vertexCount, indexCount;
        bool indexed;
    };

    GLenum ToGLType(AttrType type) {
        switch (type) {
            case AttrType::Float: return GL_FLOAT;
            case AttrType::Int: return GL_INT;
            case AttrType::Uint: return GL_UNSIGNED_INT;
                default: {
                 std::cout << "Unknown attribute type: " << type << std::endl;
                }return GL_FLOAT;
        }
    }

    Mesh::Mesh() : impl(new Impl) {}
    Mesh::~Mesh() {
        glDeleteBuffers(1, &impl->VBO);
        glDeleteBuffers(1, &impl->EBO);
        glDeleteVertexArrays(1, &impl->VAO);
        delete impl;
    }
    void Mesh::upload(const std::vector<float> &vertices, const VertexLayout &layout) {
        upload(vertices, {0}, layout);
    }

    void Mesh::upload(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const VertexLayout& layout) {

        if (indices.size() == 0) {
            impl->indexed = false;
        } else impl->indexed = true;

        GL_CHECK(glGenVertexArrays(1, &impl->VAO));
        if (!impl->VAO) {
            std::cerr << "Failed to initialize VAO\n"; return;
        }
        GL_CHECK(glGenBuffers(1, &impl->VBO));
        if (!impl->VBO) {
            std::cerr << "Failed to initialize VBO\n"; return;
        }

        GL_CHECK(glBindVertexArray(impl->VAO));

        GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, impl->VBO));
        GL_CHECK(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW));

        int index = 0;

        for (const auto& attr : layout.getAttributes()) {
            GL_CHECK(glEnableVertexAttribArray(index));
            GL_CHECK(glVertexAttribPointer(
                index,
                attr.size,
                ToGLType(attr.type),
                attr.normalized ? GL_TRUE : GL_FALSE,
                layout.getStride(),
                (void*)(uintptr_t)attr.offset
            ));
            index ++;
        }

        GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
        GL_CHECK(glBindVertexArray(0));

        impl->vertexCount = vertices.size() * sizeof(float) / layout.getStride();

        if (isIndexed()) {
            setIndices(indices);
        }

    }
    void Mesh::setIndices(const std::vector<unsigned int>& indices) {
        impl->indexCount = indices.size();
        GL_CHECK(glBindVertexArray(impl->VAO));

        GL_CHECK(glGenBuffers(1, &impl->EBO));
        if (!impl->EBO) {
            std::cerr << "Failed to initialize EBO\n"; return;
        }

        GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, impl->EBO));
        GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW));

        GL_CHECK(glBindVertexArray(0));
    }
    bool Mesh::isIndexed() const {
        return impl->indexed;
    }

    uint32_t Mesh::getVertexCount() const {
        return impl->vertexCount;
    }

    uint32_t Mesh::getIndexCount() const {
        return impl->indexCount;
    }

    void Mesh::bind() const {
        GL_CHECK(glBindVertexArray(impl->VAO));
    }

    void Mesh::unbind() const {
        GL_CHECK(glBindVertexArray(0));
    }
}
