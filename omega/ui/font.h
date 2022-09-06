#ifndef OMEGA_GFX_FONT_H
#define OMEGA_GFX_FONT_H

#include <SDL2/SDL_ttf.h>

#include <memory>
#include <string>
#include <unordered_map>

#include "omega/gfx/texture/texture.h"
#include "omega/util/util.h"

namespace omega::ui {

using namespace omega::util;
using namespace omega::gfx::texture;

/**
 * Represents a ttf / SDL_ttf font at a given size
 */
class Font {
  public:
    Font(const std::string &path, u32 size);
    ~Font();
    /**
     * Creates a Textre to draw
     * @param text to render
     * @param color to draw it
     * @return a Texture
     */
    sptr<Texture> render_text(const std::string &text, const glm::vec4 &color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

  private:
    TTF_Font *font;
};

/**
 * Stores multiple fonts to avoid memory leaks and for easier-to-read / cleaner code
 */
class FontManager {
  public:
    /**
     * @param font_name the key to represent the font
     * @param filepath the path to the font
     * @param ptsize the size in pixels of the font
     */
    void load(const std::string &font_name, const std::string &filepath, u32 ptsize);

    /**
     * @param font_name the key representing the font
     * @return a sptr<Font> containing the font
     * IMPORTANT: the font name must be loaded, since the other case is not handled
     */
    sptr<Font> get(const std::string &font_name);

    /**
     * @param font_name
     * @return if the font is already loaded
     */
    bool contains(const std::string &font_name);

    /**
     * Another easy access method to get the font
     * Same as sptr<Font> Font::Get(const std::string &font_name);
     */
    sptr<Font> operator[](const std::string &font_name);

  private:
    std::unordered_map<std::string, sptr<Font>> fonts;
};

} // namespace omega::ui

#endif // OMEGA_GFX_FONT_H