#ifndef SALAMANDER_GROUND_H
#define SALAMANDER_GROUND_H
#include "../engine/GameObject.h"
#include "../engine/SpriteRenderComponent.h"
#include "../engine/ServiceLocator.h"
#include <limits>

class Ground : public GameObject {
public:
    Ground(int x, int y) :
        m_pos{x, y},
        m_sprite{ServiceLocator::texture_cache().get("ground")} {}

    void update(std::uint32_t delta_t) override {
//        --m_x_scroll_offset;
//
//        if (m_x_scroll_offset < -m_sprite.width())
//            m_x_scroll_offset = 0;
    }

    [[nodiscard]] Vector2D pos() override { return m_pos; }

    void render(SDL_Renderer *render_context, const Vector2D &camera_offset) override {
        m_x_scroll_offset += camera_offset.x() - m_last_camera_x;
        m_last_camera_x = camera_offset.x();

        if (m_x_scroll_offset > m_sprite.width())
            m_x_scroll_offset = 0;
        else if (m_x_scroll_offset < 0)
            m_x_scroll_offset = m_sprite.width();

        m_sprite.render(render_context, m_pos.x() - m_x_scroll_offset, m_pos.y() - camera_offset.y());
        m_sprite.render(render_context, m_pos.x() - m_x_scroll_offset + m_sprite.width(), m_pos.y() - camera_offset.y());

        m_collider.x = camera_offset.x();
    }

    void destroy() override { m_sprite.destroy(); }
    void handle_event(const SDL_Event &event) override {}

    SDL_Rect *collider() override {
        return &m_collider;
    }

    void on_collide(GameObject &other, const std::string &id) override {}
    [[nodiscard]] bool is_persistent() const noexcept override { return true; }
    [[nodiscard]] bool is_dead() const noexcept override { return false; }
    [[nodiscard]] std::map<std::string, std::shared_ptr<GameObject>> &children() override {
        return m_children;
    }

private:
    Vector2D m_pos;
    Sprite m_sprite;
    SDL_Rect m_collider {
            0,
            //std::numeric_limits<int>::min(),
            m_pos.y(),
            //m_pos.y(),
            m_sprite.width(),
            //std::numeric_limits<int>::max(),
            m_sprite.height()
            //m_sprite.height()
    };

    int m_x_scroll_offset{};
    int m_last_camera_x{};
    std::map<std::string, std::shared_ptr<GameObject>> m_children{};
};
#endif //SALAMANDER_GROUND_H
