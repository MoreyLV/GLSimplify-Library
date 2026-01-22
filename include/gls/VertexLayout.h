//
// Created by Morey on 18/01/2026.
//

#ifndef GLSIMPLIFY_VERTEXLAYOUT_H
#define GLSIMPLIFY_VERTEXLAYOUT_H

#include <vector>
#include <cstdint>

namespace gls {
    enum AttrType {
        Int,
        Float,
        Uint
    };
    struct AttributeLayout {
        int index;
        int size;
        AttrType type;
        bool normalized;
        int offset;
    };
    const std::vector<AttributeLayout> DefaultAttributes = {
        {0,3,gls::AttrType::Float, false, 3}
    };
    class VertexLayout {

    public:
        VertexLayout();
        void add(int size, AttrType type, bool normalized);
        uint32_t getStride() const;
        const std::vector<AttributeLayout>& getAttributes() const { return attributes; }
    private:
        uint32_t stride = 0;
        std::vector<AttributeLayout> attributes;
    };
}

#endif //GLSIMPLIFY_VERTEXLAYOUT_H