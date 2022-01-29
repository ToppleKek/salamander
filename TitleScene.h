#ifndef SALAMANDER_TITLESCENE_H
#define SALAMANDER_TITLESCENE_H

#include <memory>
#include <map>
#include "engine/Scene.h"
#include "engine/GameObject.h"
#include "engine/Sprite.h"

class TitleScene : public Scene {
public:
    TitleScene();

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
    Sprite m_title_sprite;
    Sprite m_title_text_sprite;
    int m_ticks{};
    int m_total_ticks{};
};

#endif //SALAMANDER_TITLESCENE_H
