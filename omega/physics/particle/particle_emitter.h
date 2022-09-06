#ifndef OMEGA_PHYSICS_PARTICLE_PARTICLEEMITTER_H
#define OMEGA_PHYSICS_PARTICLE_PARTICLEEMITTER_H

#include <string>
#include <vector>

#include "omega/gfx/index_buffer.h"
#include "omega/gfx/shader.h"
#include "omega/gfx/sprite_batch.h"
#include "omega/gfx/texture/texture.h"
#include "omega/gfx/vertex_array.h"
#include "omega/gfx/vertex_buffer.h"
#include "omega/gfx/vertex_buffer_layout.h"
#include "omega/physics/particle/particle.h"
#include "omega/util/util.h"

namespace omega::physics::particle {

using namespace omega::gfx;
using namespace omega::util;

/**
 * Represents a min and max value for varius Emitter properties
 */
using range = std::pair<f32, f32>;

/**
 * Represents a particle vertex on the CPU with:
 * position,
 * center, (of the particle for the fragment shader)
 * radius,
 * color,
 */
struct ParticleVertex {
    f32 pos[2];
    f32 center[2];
    f32 radius;
    f32 color[4];
};

/**
 * Handles setting the settings of the particle emitters
 * including lifespan, starting and ending size, emittion frequency, rotations, accelerations, randomness, etc
 */
struct EmitterBuilder {
    f32 lifespan;
    f32 particle_lifespan;
    glm::vec4 begin_color; // color that particles are to be at the beginning
    glm::vec4 end_color;   // color that particles are to be at the end
    u32 max_particles;     // max particles at a given instance
    f32 emit_freq;         // time to emit particles
    glm::vec2 pos;         // pos in world coordinates
    range radius;          // radius
    range rot_range;       // range in degrees where particles spawn
    range speed;           // scalar range of different speeds
    glm::vec2 accel;       // acceleration
    glm::rectf emit_rect;  // random point in rect to spawn particle
};

/**
 * Abstracts all particles and renders and updates them
 */
class ParticleEmitter {
  public:
    explicit ParticleEmitter(EmitterBuilder &builder);
    virtual ~ParticleEmitter();

    virtual bool is_dead() const {
        return timer > data.lifespan;
    }

    /**
     * Resets the particle data if the life is over
     * @param del_particles if the remaining particles should be kept or all deleted
     */
    virtual void reset(bool del_particles = false) {
        timer = 0.0f;
        emit_timer = 0.0f;
        if (del_particles) {
            num_particles = 0;
        }
    }
    virtual void set_pos(const glm::vec2 &pos) {
        data.pos = pos;
    }

    /**
     * Updates every particle's size, color, etc
     * @param dt the timestep
     */
    virtual void update(f32 dt);

    /**
     * Renders the particle using a specially built shader
     * @param view_proj_matrx to convert to screen coords
     */
    virtual void render(const glm::mat4 &view_proj_matrix);

    EmitterBuilder &get_builder() {
        return data;
    }

  protected:
    /**
     * @return the number of particles that must be emitted
     */
    u32 can_emit() {
        u_int32_t to_add = 0;
        while (emit_timer >= data.emit_freq) {
            emit_timer -= data.emit_freq;
            if (num_particles + to_add < data.max_particles) {
                to_add++;
            }
        }
        return to_add;
    }

    /**
     * Emit's a new particle.
     * Called by ParticleEmitter::update(f32 dt);
     */
    void emit();

    Particle *particles;
    u32 num_particles;

    EmitterBuilder data;
    f32 timer;
    f32 emit_timer;

    uptr<VertexArray> vao;
    uptr<VertexBuffer> vbo;
    uptr<IndexBuffer> ibo;
    static uptr<Shader> shader;
};

} // namespace omega::physics::particle

#endif // OMEGA_PHYSICS_PARTICLE_PARTICLEEMITTER_H