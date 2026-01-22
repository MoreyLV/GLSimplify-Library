//
// Created by Morey on 16/01/2026.
//

#ifndef GLSIMPLIFY_MESH_H
#define GLSIMPLIFY_MESH_H
#include <string>
#include "VertexLayout.h"
#include <vector>

namespace gls {
    class Mesh {
    public:
        Mesh();
        ~Mesh();

        void upload(const std::vector<float>& vertices, const VertexLayout& layout);
        void upload(const std::vector<float> &vertices, const std::vector<unsigned int> &indices, const VertexLayout &layout);
        bool isIndexed() const;
        uint32_t getVertexCount() const;
        uint32_t getIndexCount() const;
        void bind() const;
        void unbind() const;

    private:
        struct Impl;
        Impl* impl;
        void setIndices(const std::vector<unsigned int>& indices);
    };

}


#endif //GLSIMPLIFY_MESH_H