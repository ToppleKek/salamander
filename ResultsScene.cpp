#include "ResultsScene.h"
#include "engine/ServiceLocator.h"
#include "TheSalamander.h"
#include "engine/Logger.h"

ResultsScene::ResultsScene(int houses, int spikes, int total) : m_houses{houses}, m_spikes{spikes}, m_total{total} {}

void ResultsScene::render(SDL_Renderer *render_context, const Vector2D &camera_offset) {
    if (!m_house_score_text_sprite.empty())
        m_house_score_text_sprite.render(render_context, 600, 200);
    if (!m_spike_score_text_sprite.empty())
        m_spike_score_text_sprite.render(render_context, 600, 300);
    if (!m_total_score_text_sprite.empty())
        m_total_score_text_sprite.render(render_context, 600, 400);
    if (!m_press_key_text_sprite.empty())
        m_press_key_text_sprite.render(render_context, 600, 700);
}

void ResultsScene::destroy() {
    m_spike_score_text_sprite.destroy();
    m_house_score_text_sprite.destroy();
    m_total_score_text_sprite.destroy();
    m_press_key_text_sprite.destroy();
}

void ResultsScene::handle_events(const SDL_Event &event) {
    if (event.type == SDL_KEYDOWN && m_can_press)
        send_goto_title();
}

void ResultsScene::update(std::uint32_t) {
    if (m_ticks > 120)
        return;

    ++m_ticks;

    if (m_ticks == 30) {
        std::string s = "Houses burned: " + std::to_string(m_houses) + " * 100 = " + std::to_string(m_houses * 100);
        auto t = ServiceLocator::texture_cache().new_from_string("house_score", s);
        m_house_score_text_sprite.swap_texture(t);
    }

    if (m_ticks == 60) {
        std::string s = "Spikes hit: " + std::to_string(m_spikes) + " * -50 = -" + std::to_string(m_spikes * 50);
        auto t = ServiceLocator::texture_cache().new_from_string("spike_score", s);
        m_spike_score_text_sprite.swap_texture(t);
    }

    if (m_ticks == 90) {
        std::string s = "Total score: " + std::to_string(m_total);
        auto t = ServiceLocator::texture_cache().new_from_string("total_score", s);
        m_total_score_text_sprite.swap_texture(t);
    }
    
    if (m_ticks == 120) {
        auto t = ServiceLocator::texture_cache().new_from_string("press_any_key", "Press any key to return to the main menu");
        m_press_key_text_sprite.swap_texture(t);
        m_can_press = true;
    }
}

void ResultsScene::set_scene_change_event(std::uint32_t event) {
    m_scene_change_event = event;
}

std::shared_ptr<GameObject> ResultsScene::object(const std::string &id) {
    return m_objects[id];
}

std::map<std::string, std::shared_ptr<GameObject>> &ResultsScene::all_objects() {
    return m_objects;
}

void ResultsScene::send_goto_title() const {
    SDL_Event user_event;
    // stupid
    auto scene_id = new TheSalamander::SceneId(TheSalamander::SceneId::TITLE);
    SDL_memset(reinterpret_cast<void *>(&user_event), 0, sizeof(user_event));
    user_event.type = m_scene_change_event;
    user_event.user.code = 1;
    user_event.user.data1 = reinterpret_cast<void *>(scene_id);
    SDL_PushEvent(&user_event);
}
