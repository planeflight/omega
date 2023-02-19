#ifndef OMEGA_GFX_TEXTURE_MESH_HPP
#define OMEGA_GFX_TEXTURE_MESH_HPP

#include <GL/gl.h>

#include <string>
#include <vector>
#include <cstdint>

#include "omega/gfx/index_buffer.hpp"
#include "omega/gfx/shader.hpp"
#include "omega/gfx/vertex_array.hpp"
#include "omega/gfx/vertex_buffer.hpp"
#include "omega/gfx/vertex_buffer_layout.hpp"
#include "omega/util/std.hpp"

namespace omega::gfx::texture {

struct MeshVertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 tex_coords;
    glm::vec3 tangent;
    glm::vec3 bitangent;
};

struct MeshTexture {
    uint32_t id;
    std::string type;
    std::string path;
};

class Mesh {
  public:
    Mesh(std::vector<MeshVertex> vertices, std::vector<uint32_t> indices, std::vector<MeshTexture> textures);

    void render(Shader &shader);

  private:
    void setup_mesh();

    std::vector<MeshVertex> vertices;
    std::vector<uint32_t> indices;
    std::vector<MeshTexture> textures;

    util::uptr<VertexArray> vao;
    util::uptr<VertexBuffer> vbo;
    util::uptr<IndexBuffer> ibo;
};

} // namespace omega::gfx::texture

#endif // OMEGA_GFX_TEXTURE_MESH_HPP