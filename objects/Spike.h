#ifndef SALAMANDER_SPIKE_H
#define SALAMANDER_SPIKE_H

#include <map>
#include <memory>
#include "../engine/GameObject.h"
#include "../engine/Sprite.h"

class Spike : public GameObject {
public:
    Spike(int x, int y);
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
    Sprite m_sprite;
    bool m_dead{false};
    int m_health{600};
    SDL_Rect m_collider;
    std::map<std::string, std::shared_ptr<GameObject>> m_children{};
};

#endif //SALAMANDER_SPIKE_H
