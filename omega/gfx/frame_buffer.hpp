#ifndef OMEGA_GFX_FRAMEBUFFER_HPP
#define OMEGA_GFX_FRAMEBUFFER_HPP

#include "omega/gfx/gl.hpp"

#include <cstdint>
#include <vector>

#include "omega/gfx/texture/texture.hpp"
#include "omega/util/util.hpp"
#include "omega/util/types.hpp"

namespace omega::gfx {

using namespace omega::util;

using namespace omega::gfx::texture;

/**
 * Wrapper for OpenGL frame buffers
 */
class FrameBuffer {
  public:
    FrameBuffer(u32 width,
                u32 height,
                macro min_filter = OMEGA_GL_NEAREST,
                macro mag_filter = OMEGA_GL_NEAREST);
    ~FrameBuffer();

    /**
     * binds the current frame buffer
     * and calls sets the whole frame buffer as the viewport
     */
    void bind() const;

    /**
     * unbinds the frame buffer (i.e. binds to the window frame buffer)
     */
    static void unbind() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    /**
     * Binds the texture and sets it to the "slot" active texture
     * @param slot to bind the texture to
     */
    void bind_texture(u32 slot = 0) const;

    /**
     * unbinds the texture
     */
    void unbind_texture() const;

    /**
     * Resizes the frame buffer with the current dimensions
     * @param width
     * @param height
     */
    void resize(u32 width,
                u32 height,
                macro min_filter = OMEGA_GL_NEAREST,
                macro mag_filter = OMEGA_GL_NEAREST);

    /**
     * @returns the width
     */
    u32 get_width() const { return width; }

    /**
     * @returns the height
     */
    u32 get_height() const { return height; }

    /**
     * @returns the render buffer id (depth and stencil buffers)
     */
    u32 get_render_buffer_id() const { return rbo_depth_stencil; }

    /**
     * @returns the color buffer
     */
    sptr<Texture> get_color_buffer() const { return color_buffer; }

  private:
    // dimensions
    u32 width;
    u32 height;

    // gl objects
    u32 id = 0;

    sptr<Texture> color_buffer = nullptr;
    u32 rbo_depth_stencil = 0;
};

} // namespace omega::gfx

#endif // OMEGA_GFX_FRAMEBUFFER_HPP
