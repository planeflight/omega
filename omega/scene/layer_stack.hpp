#ifndef OMEGA_SCENE_LAYERSTACK_HPP
#define OMEGA_SCENE_LAYERSTACK_HPP

#include <vector>

#include "omega/scene/layer.hpp"

namespace omega::scene {

class LayerStack {
  public:
    LayerStack();
    ~LayerStack();

    void render(f32 dt);
    void update(f32 dt);
    void input(f32 dt);

    void push_layer(Layer *layer);
    void pop_layer();

  private:
    std::vector<Layer *> layers;
};

} // namespace omega::scene

#endif // OMEGA_SCENE_LAYERSTACK_HPP
