#ifndef SALAMANDER_SPRITERENDERCOMPONENT_H
#define SALAMANDER_SPRITERENDERCOMPONENT_H

#include <string>

#include "Sprite.h"
#include "RenderComponent.h"


class SpriteRenderComponent : public RenderComponent {
public:
    explicit SpriteRenderComponent(const std::string &texture_key);
    void render(SDL_Renderer *render_context, int x, int y) override;

private:
    Sprite m_sprite;
};

#endif //SALAMANDER_SPRITERENDERCOMPONENT_H
