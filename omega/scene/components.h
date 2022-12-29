#ifndef OMEGA_SCENE_COMPONENTS_H
#define OMEGA_SCENE_COMPONENTS_H

#include <array>
#include <string>

#include "omega/gfx/texture/texture.h"
#include "omega/scene/orthographic_camera.h"
#include "omega/scene/perspective_camera.h"
#include "omega/util/math.h"
#include "omega/util/std.h"

namespace omega::scene {

struct TagComponent {
    std::string tag;
};

struct TransformComponent {
    glm::vec3 position{0.0f, 0.0f, 0.0f};
    glm::vec3 rotation{0.0f, 0.0f, 0.0f};
    glm::vec3 scale{0.0f, 0.0f, 0.0f};
};

struct SpriteComponent {
    glm::vec4 color{1.0f, 1.0f, 1.0f, 1.0f};
    util::sptr<gfx::texture::Texture> texture = nullptr;
};

struct CameraComponent {
    enum class ProjectionType {
        perspective,
        orthographic
    };
    CameraComponent(ProjectionType type) : ortho(0.0f, 1600.0f, 0.0f, 900.0f),
                                           perspective(),
                                           camera_type(type) {
    }
    ~CameraComponent() = default;

    void set_projection_type(ProjectionType type) { camera_type = type; };
    ProjectionType get_projection_type() const { return camera_type; }

    scene::OrthographicCamera ortho;
    scene::PerspectiveCamera perspective;
    ProjectionType camera_type = ProjectionType::orthographic;
    bool primary = true;
};

} // namespace omega::scene

#endif // OMEGA_SCENE_COMPONENTS_H