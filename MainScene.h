#ifndef SALAMANDER_MAINSCENE_H
#define SALAMANDER_MAINSCENE_H

#include <memory>
#include <map>
#include <vector>
#include "engine/Scene.h"
#include "engine/GameObject.h"
#include "engine/Sprite.h"
#include "objects/House.h"
#include "objects/Spike.h"

class MainScene : public Scene {
public:
    MainScene();

    void render(SDL_Renderer *render_context, const Vector2D &camera_offset) override;
    void destroy() override;
    void handle_events(const SDL_Event &event) override;
    void update(std::uint32_t delta_t) override;
    void set_scene_change_event(std::uint32_t event) override;
    std::shared_ptr<GameObject> object(const std::string &id) override;
    std::map<std::string, std::shared_ptr<GameObject>> &all_objects() override;

    struct Results {
        std::uint32_t m_houses_burned{};
        std::uint32_t m_spikes_hit{};
        int m_score{};
    };

private:
    std::uint32_t m_scene_change_event{};
    std::map<std::string, std::shared_ptr<GameObject>> m_objects;
    std::vector<std::shared_ptr<House>> m_houses;
    std::vector<std::shared_ptr<Spike>> m_spikes;
    Sprite m_timer_sprite;
    Sprite m_score_sprite;
    Sprite m_bg_sprite;
    int m_x_scroll_offset{};
    int m_last_camera_x{};
    std::uint32_t m_accumulator{};
    int m_time_left{30};
    std::uint32_t m_last_house_spawn_time{5000};
    std::uint32_t m_last_spike_spawn_time{2000};
    int m_score{};
    std::uint32_t m_houses_burned{};
    std::uint32_t m_spikes_hit{};

    void send_goto_title() const;
    void send_goto_results() const;
    void update_timer() noexcept;
    void update_score() noexcept;
};

#endif //SALAMANDER_MAINSCENE_H
