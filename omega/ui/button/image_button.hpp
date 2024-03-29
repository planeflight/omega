#ifndef OMEGA_UI_BUTTON_IMAGEBUTTON_HPP
#define OMEGA_UI_BUTTON_IMAGEBUTTON_HPP

#include "omega/gfx/texture/texture.hpp"
#include "omega/ui/button/button.hpp"
#include "omega/util/util.hpp"

namespace omega::ui::button {

class ImageButton : public Button {
  public:
    ImageButton(f32 x, f32 y, f32 w, f32 h,
                std::function<void()> on_click);
    virtual ~ImageButton() override;

    virtual void render() override;
    virtual void set_focus_texture(gfx::texture::Texture *focus) {
        this->focus = focus;
    }

    virtual void set_unfocus_texture(gfx::texture::Texture *un_focus) {
        this->un_focus = un_focus;
    }

  protected:
    gfx::texture::Texture *focus;
    gfx::texture::Texture *un_focus;
};

} // namespace omega::ui::button

#endif // OMEGA_UI_BUTTON_IMAGEBUTTON_HPP
