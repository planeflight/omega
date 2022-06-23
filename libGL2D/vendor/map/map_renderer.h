#ifndef _VENDOR_MAP_MAPRENDERER_H_
#define _VENDOR_MAP_MAPRENDERER_H_

#include <cstdint>
#include <string>
#include <vector>

#include "libGL2D/core/using.h"
#include "libGL2D/gfx/sprite_batch.h"
#include "libGL2D/gfx/texture/texture.h"
#include "libGL2D/vendor/map/tiled.h"

namespace libgl {
namespace tiled {

/**
 * Renders the tiled map by converting each layer into 1 texture for much faster
 * rendering
 */
class MapRenderer {
   public:
	explicit MapRenderer(Map* map, const std::string& tileset_path);
	virtual ~MapRenderer();

	/**
	 * Renders the tiled map
	 * @param batch for rendering
	 */
	virtual void Render(SpriteBatch& batch);

   protected:
	/**
	 * Loads a tile layer and creates a texture
	 * @param layer to set
	 */
	void LoadLayer(const Layer& layer);
	/**
	 * Sets the tiles pixels on the new texture
	 * @param tile_start the offset to start copying
	 * @param tile
	 * @param layer_width_pix width of the layer in pixels
	 * @param layer_height_pix height of the layer in pixels
	 */
	void SetTilePixels(uint32_t* tile_start, const Tile& tile, uint32_t layer_width_pix, uint32_t layer_height_pix) {
		(void)layer_height_pix;
		// get tileset image and pixels
		const Tileset& tileset = map_->tilesetCollection[tile.tilesetIndex];
		auto tileset_img = tex_manager_->Get(tile.tilesetIndex);
		const uint32_t* tileset_pixels = tileset_img->GetPixels();
		// get location of rect on tileset
		uint32_t src_x, src_y, src_w, src_h;
		src_w = tileset.tileWidth;
		src_h = tileset.tileHeight;
		src_x = (tile.tileFlatIndex % tileset.colCount) * src_w;
		src_y = (tile.tileFlatIndex / tileset.colCount) * src_h;
		// if no tile set all of the tiles to 0
		if (tile.gid == 0) {
			for (uint32_t y = 0; y < src_h; ++y) {
				for (uint32_t x = 0; x < src_w; ++x) {
					tile_start[x] = 0;
				}
				tile_start += layer_width_pix;
			}
			return;
		}
		// copy pixels from tileset to tile
		for (uint32_t y = 0; y < src_h; ++y) {
			const uint32_t* tileset_pixel_row = &tileset_pixels[(src_y + y) * tileset_img->GetWidth() + src_x];
			for (uint32_t x = 0; x < src_w; ++x) {
				uint32_t tileset_pix_data = tileset_pixel_row[x];
				// copy r, g, b, a
				tile_start[x] = tileset_pix_data;
			}
			// update location of pixel to next row
			tile_start += layer_width_pix;
		}
	}
	Map* map_;
	Uptr<TextureManager<uint32_t>> tex_manager_;
	std::vector<Uptr<Texture>> layer_texture_;
};
}  // namespace tiled
}  // namespace libgl

#endif  // _VENDOR_MAP_MAPRENDERER_H_