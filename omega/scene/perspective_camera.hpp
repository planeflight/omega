#ifndef OMEGA_CORE_PERSPECTIVECAMERA_HPP
#define OMEGA_CORE_PERSPECTIVECAMERA_HPP

#include "omega/scene/camera.hpp"
#include "omega/util/math.hpp"
#include "omega/util/types.hpp"

namespace omega::scene {

/**
 * Perspective Camera represents a 3D projection of a scene,
 * as well as its position, forward, and up vectors
 */
class PerspectiveCamera : public Camera {
  public:
    PerspectiveCamera(const glm::vec3 &position = glm::vec3(0.0f),
                      f32 yaw = -90.0f,
                      f32 pitch = 0.0f);
    ~PerspectiveCamera() = default;

    /**
     * Set the projection matrix
     * @param fov field of view
     * @param aspect camera aspect ratio
     * @param near the near clip plane / distance
     * @param far the far clip plane / distance
     */
    void set_projection(f32 fov = 45.0f,
                        f32 aspect = 16.0f / 9.0f,
                        f32 near = 0.1f, f32 far = 100.0f);

    /**
     * @return the camera front vector
     */
    const glm::vec3 &get_front() const { return front; }
    /**
     * @return the camera right vector
     */
    const glm::vec3 &get_right() const { return right; }

    f32 get_pitch() const { return pitch; }
    void set_pitch(f32 pitch) { this->pitch = pitch; }
    f32 get_yaw() const { return yaw; }
    void set_yaw(f32 yaw) { this->yaw = yaw; }

    /**
     * Updates the view projection matrix if position, fov, near,
     * or far plane have changed
     *
     * IMPORTANT: must be called before rendering if the camera has changed
     */
    void recalculate_view_matrix() override;
    void mouse_movement(f32 dx, f32 dy, f32 mouse_sensitivity = 0.1f);

  private:
    void update_view_vectors();
    // view fields
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 world_up;
    // euler angles
    f32 yaw;   // rotating left and right
    f32 pitch; // rotating up and down
};

} // namespace omega::scene

#endif // OMEGA_CORE_PERSPECTIVECAMERA_HPP
