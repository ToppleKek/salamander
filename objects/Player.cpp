#include "Player.h"
#include "../engine/ServiceLocator.h"
#include "../engine/Logger.h"
#include "Flame.h"
#include <cinttypes>

#define PLAYER_SPEED 2
#define FRICTION 1
#define MAX_VELOCITY 30
#define MAX_Y_VELOCITY 64
#define GRAVITY 1
#define MAX_FLAMES 7

Player::Player(int x, int y) :
        m_pos(x, y),
        m_sprite{ServiceLocator::texture_cache().get("firetruck")},
        m_collider {m_pos.x(), m_pos.y(), m_sprite.width(), m_sprite.height()} {}

void Player::update(std::uint32_t delta_t) {
    m_pos += m_velocity;

    if (m_velocity.x() < 0)
        m_velocity.set_x(m_velocity.x() + FRICTION > 0 ? 0 : m_velocity.x() + FRICTION);
    else if (m_velocity.x() > 0)
        m_velocity.set_x(m_velocity.x() - FRICTION < 0 ? 0 : m_velocity.x() - FRICTION);

    if (!m_on_ground)
        m_velocity.set_y(m_velocity.y() + GRAVITY);
        //m_velocity.set_y(m_velocity.y() + GRAVITY > MAX_Y_VELOCITY ? MAX_Y_VELOCITY : m_velocity.y() + GRAVITY);

    const std::uint8_t *keystates = SDL_GetKeyboardState(nullptr);

    if (keystates[SDL_SCANCODE_LEFT]) {
        m_velocity.set_x(m_velocity.x() - PLAYER_SPEED < -MAX_VELOCITY ? -MAX_VELOCITY : m_velocity.x() - PLAYER_SPEED);
        m_direction = PlayerDirection::LEFT;
    }

    if (keystates[SDL_SCANCODE_RIGHT]) {
        m_velocity.set_x(m_velocity.x() + PLAYER_SPEED > MAX_VELOCITY ? MAX_VELOCITY : m_velocity.x() + PLAYER_SPEED);
        m_direction = PlayerDirection::RIGHT;
    }

    if (keystates[SDL_SCANCODE_UP] && !m_is_jumping) {
        m_velocity.set_y(-32);
        m_is_jumping = true;
        m_on_ground = false;
    }

    if (keystates[SDL_SCANCODE_SPACE] && m_flames.size() < MAX_FLAMES && m_flame_cooldown == 0) {
        if (m_flame_accumulator >= 200) {
            Vector2D velocity = Vector2D{m_direction == PlayerDirection::LEFT ? -70 : 70, -20};
            int x = m_direction == PlayerDirection::LEFT ? m_pos.x() : m_pos.x() + m_sprite.width();
            m_flames.push_back(std::make_shared<Flame>(x, m_pos.y(), velocity));
            m_flame_accumulator = 0;
        }

        m_flame_accumulator += delta_t;
    } else if (m_flames.size() == MAX_FLAMES) {
        m_flame_cooldown = 60;
    }

    m_flame_cooldown > 0 ? --m_flame_cooldown : m_flame_cooldown = 0;
    m_collider.x = m_pos.x();
    m_collider.y = m_pos.y();
}

Vector2D Player::pos() {
    return m_pos;
}

void Player::render(SDL_Renderer *render_context, const Vector2D &camera_offset) {
    //m_sprite.render(render_context, m_pos.x() - camera_offset.x(), m_pos.y() - camera_offset.y());

    if (m_direction == PlayerDirection::LEFT)
        m_sprite.render(render_context, m_pos.x() - camera_offset.x(), m_pos.y() - camera_offset.y());
    else
        m_sprite.render(render_context, m_pos.x() - camera_offset.x(), m_pos.y() - camera_offset.y(), SDL_FLIP_HORIZONTAL);
}

void Player::destroy() {
    m_sprite.destroy();
}

void Player::handle_event(const SDL_Event &event) {
//    if (event.type == SDL_KEYDOWN) {
//        switch (event.key.keysym.sym) {
//            case SDLK_LEFT:
//                m_velocity.set_x(m_velocity.x() - PLAYER_SPEED);
//                break;
//
//            case SDLK_RIGHT:
//                m_velocity.set_x(m_velocity.x() + PLAYER_SPEED);
//                break;
//        }
//    }
}

SDL_Rect *Player::collider() {
    return &m_collider;
}

void Player::on_collide(GameObject &other, const std::string &id) {
    Logger::info("Player collided with object: x={} y={} other collider: other.x={} other.y={} ({})", m_pos.x(), m_pos.y(), other.collider()->x, other.collider()->y, id);

    if (id == "ground") {
        int dy = (m_collider.y + m_sprite.height()) - other.collider()->y;
        m_pos.set_y(m_pos.y() - dy);
        //m_pos.set_y(other.pos().y());
        m_velocity.set_y(0);
        m_is_jumping = false;
        m_on_ground = true;
    } else if (id == "stop_wall_l") {
        m_velocity.set_x(100);
        m_velocity.set_y(-30);
        m_on_ground = false;
        m_is_jumping = true;
    } else if (id == "stop_wall_r") {
        m_velocity.set_x(-100);
        m_velocity.set_y(-30);
        m_on_ground = false;
        m_is_jumping = true;
    } else if (id.starts_with("spike")) {
        m_velocity.set_y(-25);
        m_velocity.set_x(m_direction == PlayerDirection::LEFT ? 40 : -40);
        m_on_ground = false;
        m_is_jumping = true;
        ++m_penalty;
    }
}

std::map<std::string, std::shared_ptr<GameObject>> &Player::children() {
    m_children.clear();
    std::vector<int> to_delete{};

    for (int i = 0; i < m_flames.size(); ++i) {
        if (m_flames.at(i)->is_dead()) {
            //m_flames.at(i)->destroy();
            to_delete.push_back(i);
        }

        else
            m_children["flame" + std::to_string(i)] = m_flames.at(i);
    }

    for (const auto d : to_delete)
        m_flames.erase(m_flames.begin() + d);

    return m_children;
}

int Player::penalty() const noexcept {
    return m_penalty;
}

void Player::set_penalty(int penalty) noexcept {
    m_penalty = penalty;
}

int Player::bonus() const noexcept {
    return m_bonus;
}
