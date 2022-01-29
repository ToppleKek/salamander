#ifndef SALAMANDER_PLAYER_H
#define SALAMANDER_PLAYER_H

#include <memory>
#include <map>
#include <vector>
#include "../engine/GameObject.h"
#include "../engine/SpriteRenderComponent.h"

class Player : public GameObject {
public:
    Player(int x, int y);
    void update(std::uint32_t delta_t) override;
    [[nodiscard]] Vector2D pos() override;
    void render(SDL_Renderer *render_context, const Vector2D &camera_offset) override;
    void destroy() override;
    void handle_event(const SDL_Event &event) override;
    [[nodiscard]] SDL_Rect *collider() override;
    void on_collide(GameObject &other, const std::string &id) override;
    [[nodiscard]] bool is_persistent() const noexcept override { return true; }
    [[nodiscard]] bool is_dead() const noexcept override { return false; }
    [[nodiscard]] std::map<std::string, std::shared_ptr<GameObject>> &children() override;

    [[nodiscard]] int penalty() const noexcept;
    void set_penalty(int penalty) noexcept;
    [[nodiscard]] int bonus() const noexcept;

private:
    enum class PlayerDirection {
        LEFT,
        RIGHT
    };

    Vector2D m_pos;
    Vector2D m_velocity{};
    Sprite m_sprite;
    SDL_Rect m_collider;
    bool m_is_jumping{false};
    bool m_on_ground{false};
    PlayerDirection m_direction{PlayerDirection::RIGHT};
    std::vector<std::shared_ptr<GameObject>> m_flames;
    std::map<std::string, std::shared_ptr<GameObject>> m_children;
    std::uint32_t m_flame_accumulator{};
    int m_flame_cooldown{};
    int m_penalty{};
    int m_bonus{};

};

#endif //SALAMANDER_PLAYER_H
