#ifndef _BILLIARDS_ENTITY_TABLE_H_
#define _BILLIARDS_ENTITY_TABLE_H_

#include <memory>

#include "billiards/entity/sprite.h"
#include "libGL2D/gfx/texture/texture.h"

class Table : public Sprite {
   public:
	Table(libGL2D::Sptr<libGL2D::Texture> texture, float win_width, float win_height);

	glm::rect GetCollisionRect() const {
		float border_size = 56.0f * rect_.w / texture_->GetWidth();
		return glm::rect(rect_.x + border_size, rect_.y + border_size, rect_.w - border_size * 2, rect_.h - border_size * 2);
	}
};

#endif  // _BILLIARDS_ENTITY_TABLE_H_