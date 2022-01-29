#include "Spike.h"

#include "../engine/ServiceLocator.h"

Spike::Spike(int x, int y) :
    m_pos{x, y},
    m_sprite{ServiceLocator::texture_cache().get("spike")},
    m_collider{m_pos.x(), m_pos.y(), m_sprite.width(), m_sprite.height()} {}

void Spike::update(std::uint32_t delta_t) {
    --m_health;

    if (m_health == 0)
        m_dead = true;
}

Vector2D Spike::pos() {
    return m_pos;
}

void Spike::render(SDL_Renderer *render_context, const Vector2D &camera_offset) {
    m_sprite.render(render_context, m_pos.x() - camera_offset.x(), m_pos.y() - camera_offset.y());
}

void Spike::destroy() {
    m_sprite.destroy();
    m_dead = true;
}

void Spike::handle_event(const SDL_Event &event) {}

SDL_Rect *Spike::collider() {
    return &m_collider;
}

void Spike::on_collide(GameObject &other, const std::string &id) {
    if (id.starts_with("spike") || id.starts_with("house"))
        m_dead = true;
}

bool Spike::is_dead() const noexcept {
    return m_dead;
}
