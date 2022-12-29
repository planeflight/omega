#ifndef OMEGA_GFX_VERTEXARRAY_H
#define OMEGA_GFX_VERTEXARRAY_H

#include <cstdint>
#include <vector>

#include "omega/gfx/vertex_buffer.h"
#include "omega/gfx/vertex_buffer_layout.h"

namespace omega::gfx {

/**
 * A Vertex Array stores all of the data to supply a vertex. This implementation holds Vertex Buffers as a wrapper for the vertex attributes
 */
class VertexArray {
  public:
    VertexArray();
    ~VertexArray();

    /**
     * Sets the vertex attributes in the OpenGL vertexArray
     * @param vb Buffer to bind vertex attributes to
     * @param layout information about attributes
     */
    void add_buffer(const VertexBuffer &vb, const VertexBufferLayout &layout);

    /**
     * Binds the Vertex Array in the OpenGL state machine
     */
    void bind() const;

    /**
     * Unbinds the Vertex Array in the OpenGL state machine
     */
    static void unbind() {
        glBindVertexArray(0);
    }

  private:
    uint32_t id;
};

} // namespace omega::gfx

#endif // OMEGA_GFX_VERTEXARRAY_H