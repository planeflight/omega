#include "app.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "omega/math/math.hpp"
#include "omega/util/log.hpp"
#include "omega/util/time.hpp"
#include "lib/imgui/imgui.h"
#include "lib/imgui/implot.h"
#include "lib/imgui/imgui_impl_sdl.h"
#include "lib/imgui/imgui_impl_opengl3.h"

static void setup_imgui(omega::core::Window *window) {
    // setup imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();


    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    /* ImGui::StyleColorsDark(); */

    ImGui_ImplSDL2_InitForOpenGL(window->get_native_window(),
                                 window->get_gl_context());
#ifdef EMSCRIPTEN
    const char version[] = "#version 100";
#else
    const char version[] = "#version 450";
#endif
    ImGui_ImplOpenGL3_Init(version);
}

static void quit_imgui() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    ImPlot::DestroyContext();
}

static void begin_imgui_frame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

static void end_imgui_frame(omega::core::Window *window) {
    ImGuiIO &io = ImGui::GetIO();
    io.DisplaySize = ImVec2(
        (f32)window->get_width(),
        (f32)window->get_height()
    );

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

namespace omega::core {

App *App::current_instance = nullptr;

App::App(const AppConfig &config) {
    current_instance = this;
    window = Window::instance();
    running = window->init(
        config.width,
        config.height,
        config.resizable,
        config.title
    );

    // init TTF_Font
    if (TTF_Init() != 0) {
        util::error("Unable to initialize SDL_ttf: '{}'", SDL_GetError());
        running = false;
    }
    util::Time::init();
    last_time = util::Time::get_time<f32>();
    fps = config.fps;
    globals = util::create_uptr<Globals>(Viewport(
        config.viewport_type,
        config.viewport_width,
        config.viewport_height
    ), "Main Scene");

    // init imgui
    imgui = config.imgui;
    setup_imgui(window);
    if (imgui) {
        util::info("Dear Imgui successfully initialized.");
    }
}

App::~App() {
    if (imgui) {
        quit_imgui();
        util::info("Successfully quit ImGui.");
    }
    SDL_Quit();
    TTF_Quit();
    util::info("Successfully closed libraries.");
}

f32 App::tick() {
    f32 to_sleep = math::max(
        1.0f / fps - (util::Time::get_time<f32>() - last_time),
        0.0f);
    util::Time::sleep(to_sleep);
    f32 current_time = util::Time::get_time<f32>();
    f32 dt = (current_time - last_time); // get delta time
    last_time = current_time;
    return dt;
}

void App::frame() {
    f32 dt = tick();

    auto &input = globals->input;
    input.prepare_for_update();

    events::Event event;
    while (input.poll_events(event)) {
        if (imgui) {
            ImGui_ImplSDL2_ProcessEvent(&event);
        }
        switch ((events::EventType)event.type) {
            case events::EventType::quit:
                running = false;
                break;
            case events::EventType::window_event:
                if (event.window.event == 
                    (u32)events::WindowEvents::window_resized) {
                    // change window width, height data
                    Window::instance()->on_resize(event.window.data1,
                                                  event.window.data2);
                    on_resize(event.window.data1, event.window.data2); 
                }
                break;
            case events::EventType::mouse_wheel:
                input.scroll_wheel = math::vec2((f32)event.wheel.x,
                                               (f32)event.wheel.y);
            default:
                break;
        }
    }
    input.update();
    // perform the input, update, and render
    this->input(dt);
    this->update(dt);

    begin_imgui_frame();
    this->render(dt);
    end_imgui_frame(window);

    window->swap_buffers();
}

static void update_loop() {
    auto &app = App::instance();
    app.frame();
}

void App::run() {
    setup();

#ifdef EMSCRIPTEN
    emscripten_set_main_loop(update_loop, 0, 1);
#else
    while (running) { update_loop(); }
#endif
}

} // namespace omega::core
