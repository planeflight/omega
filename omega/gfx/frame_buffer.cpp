#include "frame_buffer.hpp"

#include "omega/gfx/gl.hpp"

namespace omega::gfx {

FrameBuffer::FrameBuffer(u32 width, u32 height, macro min, macro mag)
 : width(width), height(height) {
    resize(width, height, min, mag);
}

FrameBuffer::~FrameBuffer() {
    glDeleteFramebuffers(1, &id);
    glDeleteRenderbuffers(1, &rbo_depth_stencil);
}

void FrameBuffer::resize(u32 width, u32 height,
                         macro min, macro mag) {
    if (id != 0) {
        glDeleteFramebuffers(1, &id);
        glDeleteRenderbuffers(1, &rbo_depth_stencil);
        id = 0;
        rbo_depth_stencil = 0;
    }
    this->width = width;
    this->height = height;
#ifdef EMSCRIPTEN
    glGenFramebuffers(1, &id);
#else
    glCreateFramebuffers(1, &id);
#endif
    glBindFramebuffer(GL_FRAMEBUFFER, id);
    check_error();
    // create color buffer
    color_buffer = Texture::create_empty(width, height, min, mag);
    // attach to frame buffer
    glFramebufferTexture2D(GL_FRAMEBUFFER,
                           GL_COLOR_ATTACHMENT0,
                           GL_TEXTURE_2D,
                           color_buffer->get_renderer_id(),
                           0);
    // create depth and stencil buffer in render buffer
#ifdef EMSCRIPTEN
    glGenRenderbuffers(1, &rbo_depth_stencil);
#else
    glCreateRenderbuffers(1, &rbo_depth_stencil);
#endif
    glBindRenderbuffer(GL_RENDERBUFFER, rbo_depth_stencil);

#ifdef EMSCRIPTEN
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                              GL_DEPTH_ATTACHMENT,
                              GL_RENDERBUFFER,
                              rbo_depth_stencil);
#else
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                              GL_DEPTH_STENCIL_ATTACHMENT,
                              GL_RENDERBUFFER,
                              rbo_depth_stencil);
#endif

    // check if it was successful
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        util::warn("Frame Buffer Error: Frame Buffer is not complete!");
    }

    // unbind everything
    color_buffer->unbind();
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    check_error();
}

void FrameBuffer::bind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, id);
    glViewport(0, 0, width, height);
}

void FrameBuffer::bind_texture(u32 slot) const {
    color_buffer->bind(slot);
}

void FrameBuffer::unbind_texture() const {
    color_buffer->unbind();
}

} // namespace omega
