#include "TitleScene.h"
#include "engine/ServiceLocator.h"
#include "TheSalamander.h"

TitleScene::TitleScene() :
    m_title_sprite{ServiceLocator::texture_cache().get("title"), 3, 800},
    m_title_text_sprite{ServiceLocator::texture_cache().new_from_string("title_text", "Press Any Key to Start")} {
}

void TitleScene::render(SDL_Renderer *render_context, const Vector2D &camera_offset) {
    m_title_sprite.render(render_context, 500, 0);
    m_title_text_sprite.render(render_context, 750, 800);
}

void TitleScene::destroy() {
    m_title_sprite.destroy();

    for (auto &object : m_objects)
        object.second->destroy();
}

void TitleScene::handle_events(const SDL_Event &event) {
    if (event.type == SDL_KEYDOWN && m_total_ticks >= 50) {
        SDL_Event user_event;
        // stupid
        auto scene_id = new TheSalamander::SceneId(TheSalamander::SceneId::MAIN);
        SDL_memset(reinterpret_cast<void *>(&user_event), 0, sizeof(user_event));
        user_event.type = m_scene_change_event;
        user_event.user.code = 1;
        user_event.user.data1 = reinterpret_cast<void *>(scene_id);
        SDL_PushEvent(&user_event);
    }
}

void TitleScene::update(std::uint32_t) {
    if (++m_ticks == 16) {
        m_title_sprite.next_frame();
        m_ticks = 0;
    }

    ++m_total_ticks;
}

void TitleScene::set_scene_change_event(std::uint32_t event) {
    m_scene_change_event = event;
}

std::shared_ptr<GameObject> TitleScene::object(const std::string &id) {
    return m_objects[id];
}

std::map<std::string, std::shared_ptr<GameObject>> &TitleScene::all_objects() {
    return m_objects;
}
