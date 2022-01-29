#include "Flame.h"

#include <utility>

#include "../engine/ServiceLocator.h"
#include "../engine/Logger.h"

#define FLAME_GRAVITY 1
#define FLAME_FRICTION 1

Flame::Flame(int x, int y, Vector2D velocity) :
    m_pos{x, y},
    m_velocity{velocity},
    m_sprite{ServiceLocator::texture_cache().get("flame"), 4, 130},
    m_collider{x, y, 130, m_sprite.height()} {}

void Flame::update(std::uint32_t delta_t) {
    if (m_dead)
        return;

    m_pos += m_velocity;

    if (m_pos.y() > 3000) {
        m_dead = true;
        return;
    }

    m_velocity.set_x(m_velocity.x() < 0 ? m_velocity.x() + FLAME_FRICTION : m_velocity.x() - FLAME_FRICTION);
    m_velocity.set_y(m_velocity.y() + FLAME_GRAVITY);

    if (++m_ticks == 16) {
        m_sprite.next_frame();
        m_ticks = 0;
    }

    if (--m_health <= 0)
        m_dead = true;

    m_collider.x = m_pos.x();
    m_collider.y = m_pos.y();
}

void Flame::render(SDL_Renderer *render_context, const Vector2D &camera_offset) {
    m_sprite.render(render_context, m_pos.x() - camera_offset.x(), m_pos.y() - camera_offset.y());
}

Vector2D Flame::pos() {
    return m_pos;
}

void Flame::destroy() {
    m_sprite.destroy();
    m_dead = true;
}

void Flame::handle_event(const SDL_Event &event) {}

SDL_Rect *Flame::collider() {
    return &m_collider;
}

void Flame::on_collide(GameObject &other, const std::string &id) {}

bool Flame::is_dead() const noexcept {
    return m_dead;
}
