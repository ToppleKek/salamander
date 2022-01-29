#include "SpriteRenderComponent.h"

#include "../engine/ServiceLocator.h"

SpriteRenderComponent::SpriteRenderComponent(const std::string &texture_key)
    : m_sprite(ServiceLocator::texture_cache().get(texture_key)) {}

void SpriteRenderComponent::render(SDL_Renderer *render_context, int x, int y) {
    m_sprite.render(render_context, x, y);
}
