#ifndef _LIBGL2D_GFX_TEXTURE_TEXTUREREGION_H_
#define _LIBGL2D_GFX_TEXTURE_TEXTUREREGION_H_

#include <string>

#include "libGL2D/gfx/texture/texture.h"
#include "libGL2D/physics/math.h"

namespace libgl {

class TextureRegion {
   public:
	TextureRegion(Texture *tex, uint32_t x, uint32_t y, uint32_t w, uint32_t h);
	uint32_t get_x() const { return x_; }
	uint32_t get_y() const { return y_; }
	uint32_t get_w() const { return w_; }
	uint32_t get_h() const { return h_; }
	glm::rect get_rect() const { return glm::rect(x_, y_, w_, h_); }
	/**
	 * Returns the source rectangle used for rendering on a y-up axis
	 * @return source rectangle
	 */
	glm::rect get_gl_rect() const { return glm::rect(x_, texture_->get_height() - y_ - h_, w_, h_); }

   private:
	Texture *texture_;
	uint32_t x_;
	uint32_t y_;
	uint32_t w_;
	uint32_t h_;
	std::string region_name_;
};
}  // namespace libgl

#endif  // _LIBGL2D_GFX_TEXTURE_TEXTUREREGION_H_