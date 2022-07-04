#ifndef LIBGL2D_PHYSICS_ENTITY_H
#define LIBGL2D_PHYSICS_ENTITY_H

#include "libGL2D/events/input_processor.h"
#include "libGL2D/gfx/sprite_batch.h"
#include "libGL2D/gfx/texture/texture.h"
#include "libGL2D/physics/math.h"

namespace libgl {

/**
 * Basic Entity abstraction for rendering, updating, and handling inputs
 */
class Entity {
   public:
	Entity();
	virtual ~Entity() {}

	/**
	 * Updates the entity data
	 * @param dt the timestep if necessary
	 */
	virtual void Update(float dt) {
		(void)dt;
	}

	/**
	 * Renders the entity
	 * @param sprite_batch for rendering
	 */
	virtual void Render(SpriteBatch &sprite_batch) {
		(void)sprite_batch;
	}

	/**
	 * Handles input and stores entity data
	 * @param input the input processor to get data from
	 */
	virtual void Input(InputProcessor &input) {
		(void)input;
	}
	virtual const glm::vec2 &GetVel() const { return vel_; }
	virtual void SetVel(const glm::vec2 &vel) { vel_ = vel; }
	virtual void SetVelX(float x) { vel_.x = x; }
	virtual void SetVelY(float y) { vel_.y = y; }

   protected:
	glm::vec2 vel_;
};

/**
 * Abstraction for entities if they are circles
 */
class CircleComponent {
   public:
	CircleComponent(float x, float y, float radius);
	virtual ~CircleComponent() {}
	const glm::vec2 &GetCenter() const { return center_; }
	float GetRadius() const { return radius_; }

   protected:
	glm::vec2 center_;
	float radius_;
};

/**
 * Abstraction for AABB rectangle entities
 */
class RectComponent {
   public:
	RectComponent(float x, float y, float w, float h);
	virtual ~RectComponent() {}
	const glm::rect &GetRect() const { return rect_; }
	void SetX(float x) { rect_.x = x; }
	void SetY(float y) { rect_.y = y; }
	void SetW(float w) { rect_.w = w; }
	void SetH(float h) { rect_.h = h; }
	void SetRect(const glm::rect &r) { rect_ = r; }

   protected:
	glm::rect rect_;
};

/**
 * Abstraction of a texture using / sprite rendering entity
 */
class SpriteComponent {
   public:
	SpriteComponent(Texture *texture);
	virtual ~SpriteComponent() {}

   protected:
	Texture *texture_;
};

}  // namespace libgl

#endif  // LIBGL2D_PHYSICS_ENTITY_H