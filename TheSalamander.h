#ifndef SALAMANDER_MAPPYGAME_H
#define SALAMANDER_MAPPYGAME_H

#include <map>
#include <string>
#include <memory>
#include "engine/Game.h"
#include "engine/GameObject.h"
#include "engine/FollowCamera.h"
#include "TitleScene.h"
#include "MainScene.h"

class TheSalamander : public Game {
public:
    TheSalamander() = default;
    void start() override;
    void update(std::uint32_t delta_t) override;
    void render(SDL_Renderer *render_context) override;
    void handle_events(const SDL_Event &event) override;
    std::map<std::string, std::shared_ptr<GameObject>> all_objects() override;
    void destroy() override;

    virtual ~TheSalamander() = default;

    enum class SceneId {
        TITLE,
        MAIN,
        RESULTS
    };

private:
    std::map<std::string, std::shared_ptr<GameObject>> m_objects;
    std::map<std::string, std::shared_ptr<GameObject>> m_active_objects;
    std::unique_ptr<Scene> m_current_scene;
    FollowCamera m_camera;
    std::uint32_t m_scene_event{};

    std::map<std::string, std::shared_ptr<GameObject>> get_all_objects();
};


#endif //SALAMANDER_MAPPYGAME_H
