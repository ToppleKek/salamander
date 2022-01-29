#ifndef SALAMANDER_RESULTSSCENE_H
#define SALAMANDER_RESULTSSCENE_H

#include <memory>
#include <map>
#include "engine/Scene.h"
#include "engine/GameObject.h"
#include "engine/Sprite.h"

class ResultsScene : public Scene {
public:
    ResultsScene(int houses, int spikes, int total);

    void render(SDL_Renderer *render_context, const Vector2D &camera_offset) override;
    void destroy() override;
    void handle_events(const SDL_Event &event) override;
    void update(std::uint32_t delta_t) override;
    void set_scene_change_event(std::uint32_t event) override;
    std::shared_ptr<GameObject> object(const std::string &id) override;
    std::map<std::string, std::shared_ptr<GameObject>> &all_objects() override;

private:
    std::uint32_t m_scene_change_event{};
    std::map<std::string, std::shared_ptr<GameObject>> m_objects;
    Sprite m_house_score_text_sprite{};
    Sprite m_spike_score_text_sprite{};
    Sprite m_total_score_text_sprite{};
    Sprite m_press_key_text_sprite{};
    int m_ticks{};
    int m_houses;
    int m_spikes;
    int m_total;
    bool m_can_press{false};

    void send_goto_title() const;
};

#endif //SALAMANDER_RESULTSSCENE_H
