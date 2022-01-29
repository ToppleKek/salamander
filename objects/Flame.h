#ifndef SALAMANDER_FLAME_H
#define SALAMANDER_FLAME_H

#include "../engine/GameObject.h"
#include "../engine/Sprite.h"

class Flame : public GameObject {
public:
    Flame(int x, int y, Vector2D velocity);
    void update(std::uint32_t delta_t) override;
    [[nodiscard]] Vector2D pos() override;
    void render(SDL_Renderer *render_context, const Vector2D &camera_offset) override;
    void destroy() override;
    void handle_event(const SDL_Event &event) override;
    [[nodiscard]] SDL_Rect *collider() override;
    void on_collide(GameObject &other, const std::string &id) override;
    [[nodiscard]] bool is_persistent() const noexcept override { return true; }
    [[nodiscard]] bool is_dead() const noexcept override;
    [[nodiscard]] std::map<std::string, std::shared_ptr<GameObject>> &children() override {
        return m_children;
    }

private:
    Vector2D m_pos;
    Vector2D m_velocity;
    Sprite m_sprite;
    SDL_Rect m_collider;
    int m_health{250};
    int m_ticks{};
    bool m_dead{false};
    std::map<std::string, std::shared_ptr<GameObject>> m_children{};
};

#endif //SALAMANDER_FLAME_H
