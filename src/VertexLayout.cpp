//
// Created by Morey on 18/01/2026.
//

#include "../include/gls/VertexLayout.h"

namespace gls {
    uint32_t sizeOfType(AttrType type) {
        switch (type) {
            case AttrType::Float: return sizeof(float);
            case AttrType::Int: return sizeof(int);
            case AttrType::Uint: return sizeof(unsigned int);
        }
    }

    VertexLayout::VertexLayout() {}
    void VertexLayout::add(int size, AttrType type, bool normalized) {
        AttributeLayout attr;
        attr.size = size;
        attr.type = type;
        attr.normalized = normalized;
        attr.offset = stride;

        stride += size * sizeOfType(type);
        attributes.push_back(attr);
    }

    uint32_t VertexLayout::getStride() const{
        return stride;
    }



}
