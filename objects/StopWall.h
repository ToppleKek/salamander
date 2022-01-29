#ifndef SALAMANDER_STOPWALL_H
#define SALAMANDER_STOPWALL_H

#include "../engine/GameObject.h"
#include "../engine/SpriteRenderComponent.h"
#include "../engine/ServiceLocator.h"
#include <limits>

class StopWall : public GameObject {
public:
    StopWall(int x, int y) :
            m_pos{x, y},
            m_sprite{ServiceLocator::texture_cache().get("stop")} {}

    void update(std::uint32_t delta_t) override {
//        --m_x_scroll_offset;
//
//        if (m_x_scroll_offset < -m_sprite.width())
//            m_x_scroll_offset = 0;
    }

    [[nodiscard]] Vector2D pos() override { return m_pos; }

    void render(SDL_Renderer *render_context, const Vector2D &camera_offset) override {
        m_sprite.render(render_context, m_pos.x() - camera_offset.x(), m_pos.y() - camera_offset.y());

    }

    void destroy() override { m_sprite.destroy(); }
    void handle_event(const SDL_Event &event) override {}

    SDL_Rect *collider() override {
        return &m_collider;
    }

    void on_collide(GameObject &, const std::string &) override {}
    [[nodiscard]] bool is_persistent() const noexcept override { return true; }
    [[nodiscard]] bool is_dead() const noexcept override { return false; }
    [[nodiscard]] std::map<std::string, std::shared_ptr<GameObject>> &children() override {
        return m_children;
    }

private:
    Vector2D m_pos;
    Sprite m_sprite;
    SDL_Rect m_collider {
            m_pos.x(),
            m_pos.y() - 3000,
            m_sprite.width(),
            5000
            //m_sprite.height()
    };

    std::map<std::string, std::shared_ptr<GameObject>> m_children{};
};

#endif //SALAMANDER_STOPWALL_H
