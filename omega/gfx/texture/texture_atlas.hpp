#ifndef OMEGA_GFX_TEXTURE_TEXTUREATLAS_HPP
#define OMEGA_GFX_TEXTURE_TEXTUREATLAS_HPP

#include <string>
#include <unordered_map>

#include "omega/gfx/texture/texture.hpp"
#include "omega/gfx/texture/texture_region.hpp"
#include "omega/util/std.hpp"

namespace omega::gfx::texture {

/**
 * Represents every "sub-texture" or TextureRegion of a larger texture
 * for faster rendering both on CPU and GPU side.
 * A TextureAtlas can only be created from a libgl atlas file
 * made with the tools/texture_packer package.
 */
class TextureAtlas {
  public:
    explicit TextureAtlas(const std::string &atlas_file_path, GLenum min_filter = GL_NEAREST, GLenum mag_filter = GL_NEAREST);
    ~TextureAtlas();

    /**
     * Returns the texture with the given look-up string
     * @param texture_name name of the texture region as defined by the atlas file
     * @return shared pointer to the TextureRegion
     */
    util::sptr<TextureRegion> get(const std::string &texture_name);

    /**
     * @returns the texture that the atlas is a wrapper of
     */
    util::sptr<Texture> get_texture() const { return tex; };

  private:
    std::unordered_map<std::string, util::sptr<TextureRegion>> tex_regions;
    util::sptr<Texture> tex = nullptr;
};
} // namespace omega::gfx::texture

#endif // OMEGA_GFX_TEXTURE_TEXTUREATLAS_HPP