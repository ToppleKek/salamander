#include "House.h"

#include "../engine/ServiceLocator.h"
#include "../engine/Logger.h"

House::House(int x, int y) :
    m_pos{x, y},
    m_sprite{ServiceLocator::texture_cache().get("house")},
    m_flame_sprite{ServiceLocator::texture_cache().get("flame"), 4, 130},
    m_collider{m_pos.x(), m_pos.y(), m_sprite.width(), m_sprite.height()} {}

void House::update(std::uint32_t delta_t) {
    if (m_on_fire) {
        --m_health;

        if (m_health == 0)
            m_dead = true;

        if (++m_ticks == 16) {
            m_flame_sprite.next_frame();
            m_ticks = 0;
        }
    }
}

Vector2D House::pos() {
    return m_pos;
}

void House::render(SDL_Renderer *render_context, const Vector2D &camera_offset) {
    m_sprite.render(render_context, m_pos.x() - camera_offset.x(), m_pos.y() - camera_offset.y());

    if (m_on_fire)
        m_flame_sprite.render(render_context, m_pos.x() - camera_offset.x(), m_pos.y() - camera_offset.y());
}

void House::destroy() {
    m_sprite.destroy();
    m_dead = true;
}

void House::handle_event(const SDL_Event &event) {

}

SDL_Rect *House::collider() {
    return &m_collider;
}

void House::on_collide(GameObject &other, const std::string &id) {
    if (m_dead || m_on_fire)
        return;

    if (id.starts_with("flame")) {
        Logger::info("House is burning! x={} y={}", m_pos.x(), m_pos.y());
        m_on_fire = true;
    }
}

bool House::is_dead() const noexcept {
    return m_dead;
}
