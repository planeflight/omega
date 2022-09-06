#include "vertex_array.h"

#include <GL/gl.h>

namespace omega::gfx {

VertexArray::VertexArray() {
    glGenVertexArrays(1, &id);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &id);
}

void VertexArray::add_buffer(const VertexBuffer &vb, const VertexBufferLayout &layout) {
    bind();
    vb.bind();
    const auto &elements = layout.get_attributes();
    uintptr_t offset = 0;
    for (u32 i = 0; i < elements.size(); ++i) {
        const auto &element = elements[i];
        // initialize attribute
        glEnableVertexAttribArray(i);
        // set pointer to data
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.get_stride(), (const void *)offset);
        // increase offset for pointer value
        offset += element.count * VertexBufferAttrib::get_size_of_type(element.type);
    }
}

void VertexArray::bind() const {
    glBindVertexArray(id);
}

void VertexArray::unbind() const {
    glBindVertexArray(0);
}

} // namespace omega