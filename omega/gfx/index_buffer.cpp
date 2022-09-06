#include "index_buffer.h"

#include <GL/gl.h>

namespace omega::gfx {

IndexBuffer::IndexBuffer(const u32 *data, u32 count) : count(count) {
    glGenBuffers(1, &id);
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(u32), data, GL_STATIC_DRAW);
}

IndexBuffer::IndexBuffer(u32 count) : count(count) {
    glGenBuffers(1, &id);
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(u32), nullptr, GL_DYNAMIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &id);
}

void IndexBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void IndexBuffer::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::sub_data(GLintptr offset, GLsizeiptr size, const GLvoid *data) {
    bind();
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
}

} // namespace omega::gfx
