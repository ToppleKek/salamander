#include "TheSalamander.h"
#include "engine/Logger.h"
#include "objects/Player.h"
#include "MainScene.h"
#include "TitleScene.h"
#include "ResultsScene.h"
#include <cassert>

void TheSalamander::start() {
    Logger::info("TheSalamander start()");
    m_scene_event = SDL_RegisterEvents(1);

    assert(m_scene_event != static_cast<std::uint32_t>(-1));

    auto scene = std::make_unique<TitleScene>();
    scene->set_scene_change_event(m_scene_event);
    m_current_scene = std::move(scene);

    // TODO: The game objects should have different layers that they can be rendering on
    // TODO: It is extremely inefficient to specfically render the player first then making sure
    // TODO: you do not render it again in the map. There should be different render layers to make sure
    // TODO: the player is always on top of every other object.
}

void TheSalamander::update(std::uint32_t delta_t) {
    m_camera.update();
    m_current_scene->update(delta_t);
    m_active_objects.clear();

    const Vector2D &camera_pos = m_camera.pos();
    std::map<std::string, std::shared_ptr<GameObject>> all_objects = get_all_objects();

    // Find on screen objects
    for (const auto &object : all_objects) {
        // TODO: this game will have basically no y scrolling but that is a dumb limitation for a later project
        int render_pos_x = object.second->pos().x() - camera_pos.x();
        if (object.second->is_persistent() || (render_pos_x >= 0 && render_pos_x <= 1080))
            m_active_objects[object.first] = object.second;
    }

    // Go ahead and do collision checks on active objects
    for (const auto &object : m_active_objects) {
        for (const auto &other_object : m_active_objects) {
            if (other_object == object)
                continue;

            if (SDL_HasIntersection(object.second->collider(), other_object.second->collider())) {
                object.second->on_collide(*other_object.second, other_object.first);
            }
        }
    }
}

void TheSalamander::render(SDL_Renderer *render_context) {
    const Vector2D &camera_pos = m_camera.pos();
    m_current_scene->render(render_context, camera_pos);

    for (const auto &object : m_active_objects)
        object.second->render(render_context, camera_pos);
}

void TheSalamander::handle_events(const SDL_Event &event) {
    if (event.type == m_scene_event) {
        // stupid
        auto *scene_id = reinterpret_cast<SceneId *>(event.user.data1);

        if (*scene_id == SceneId::TITLE) {
            auto title_scene = std::make_unique<TitleScene>();
            title_scene->set_scene_change_event(m_scene_event);
            m_current_scene = std::move(title_scene);
        } else if (*scene_id == SceneId::MAIN) {
            auto main_scene = std::make_unique<MainScene>();
            main_scene->set_scene_change_event(m_scene_event);
            m_camera.set_target(main_scene->object("player"));
            m_current_scene = std::move(main_scene);
        } else if (*scene_id == SceneId::RESULTS) {
            auto results = reinterpret_cast<MainScene::Results *>(event.user.data2);
            auto results_scene = std::make_unique<ResultsScene>(results->m_houses_burned, results->m_spikes_hit, results->m_score);
            results_scene->set_scene_change_event(m_scene_event);
            m_current_scene = std::move(results_scene);
            delete results;
        }

        delete scene_id;
    }

    m_current_scene->handle_events(event);
}

std::map<std::string, std::shared_ptr<GameObject>> TheSalamander::all_objects() {
    return get_all_objects();
}

void TheSalamander::destroy() {
    m_current_scene->destroy();
}

std::map<std::string, std::shared_ptr<GameObject>> TheSalamander::get_all_objects() {
    std::map<std::string, std::shared_ptr<GameObject>> all_objects;
    std::map<std::string, std::shared_ptr<GameObject>> children;

    all_objects.insert(m_objects.begin(), m_objects.end());
    all_objects.insert(m_current_scene->all_objects().begin(), m_current_scene->all_objects().end());

    for (const auto &object : all_objects) {
        if (!object.second->children().empty())
            children.insert(object.second->children().begin(), object.second->children().end());
    }

    all_objects.insert(children.begin(), children.end());

    return all_objects;
}
