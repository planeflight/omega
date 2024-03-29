#ifndef OMEGA_GFX_VERTEXBUFFER_HPP
#define OMEGA_GFX_VERTEXBUFFER_HPP

#include <cstddef>

#include "omega/util/types.hpp"

namespace omega::gfx {

/**
 * A Vertex Buffer provides methods for adding / storing vertex data
 * such as position, normal, vector, color, etc to the GPU.
 * Holds a vertex attribute in the buffer
 */
class VertexBuffer {
  public:
    VertexBuffer(const void *data, u32 size);
    explicit VertexBuffer(size_t size);
    ~VertexBuffer();

    /**
     * Binds the Vertex Buffer in the OpenGL state machine
     */
    void bind() const;

    /**
     * Unbinds the Vertex Buffer in the OpenGL state machine
     */
    static void unbind();

    /**
     * Changes the buffer's data.
     * Range from offset to size must not overflow buffer
     * @param offset in bytes
     * @param size in bytes
     * @param data data
     */
    void sub_data(size_t offset, size_t size, const void *data);

  private:
    u32 id;
};
} // namespace omega::gfx

#endif // OMEGA_GFX_VERTEXBUFFER_HPP
