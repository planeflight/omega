#include "window.hpp"

#include <iostream>

#include "omega/core/sdl2.hpp"
#include "omega/util/log.hpp"

namespace omega::core {

Window::~Window() {
    if (context != nullptr) {
        SDL_GL_DeleteContext(context);
    }
    context = nullptr;
    if (window != nullptr) {
        SDL_DestroyWindow(window);
    }
    window = nullptr;
    SDL_Quit();
    util::info("Successfully quit application.");
}

bool Window::init(u32 width, u32 height, bool resizable, const std::string &title) {
    this->width = width;
    this->height = height;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) != 0) {
        util::error("Failed to initialize SDL: '{}'", SDL_GetError());
        return false;
    }

#ifdef EMSCRIPTEN
    // use the ES OpenGL profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    // specify version 3.0
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
 

#else
    // use the core OpenGL profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    // specify version 4.5
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
 
#endif
   // request a color buffer with 8-bits per RGBA channel
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    // enable double buffering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // force hardware acceleration
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    auto window_flags = resizable ?
        (WindowFlags::opengl | WindowFlags::resizable) : WindowFlags::opengl;
    window = SDL_CreateWindow(title.c_str(),
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              width,
                              height,
                              window_flags);
    if (window == nullptr) {
        util::error("Failed to create window: '{}'", SDL_GetError()); 
        return false;
    }
    util::info("Window created successfully.");

    context = SDL_GL_CreateContext(window);
    if (context == nullptr) {
        util::error("Failed to create GL Context: '{}'", SDL_GetError());
        return false;
    }
    util::info("OpenGL Context successfully created.");
    if (SDL_GL_SetSwapInterval(0) == -1) {
        util::error("Failed to disable Vsync: '{}'", SDL_GetError());
        return false;
    }
    util::info("Disabled Vsync.");

#ifndef EMSCRIPTEN
    // initialize glad
    if (gladLoadGLLoader(SDL_GL_GetProcAddress) == 0) {
        util::error("Failed to initialize Glad");
        return false;
    }
#endif
    util::info("OpenGL API successfully loaded.");
    return true;
}

void Window::clear(GLbitfield mask) {
    glClear(mask);
}

void Window::swap_buffers() {
    SDL_GL_SwapWindow(window);
}

void Window::on_resize(u32 new_width, u32 new_height) {
    width = new_width;
    height = new_height;
}

} // namespace omega::core
