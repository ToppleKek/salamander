#include "MainScene.h"

#include "objects/Ground.h"
#include "objects/Player.h"
#include "TheSalamander.h"
#include "engine/Logger.h"
#include "objects/StopWall.h"

#define MAX_HOUSES 10
#define HOUSE_SPAWN_INTERVAL 4000
#define MAX_SPIKES 14
#define SPIKE_SPAWN_INTERVAL 3000

MainScene::MainScene() :
    m_timer_sprite{ServiceLocator::texture_cache().new_from_string("timer_text", "30")},
    m_score_sprite{ServiceLocator::texture_cache().new_from_string("score_text", "Score: 0")},
    m_bg_sprite{ServiceLocator::texture_cache().get("city_bg")} {
    m_objects["ground"] = std::make_shared<Ground>(0, 900);
    m_objects["stop_wall_l"] = std::make_shared<StopWall>(0, 700);
    m_objects["stop_wall_r"] = std::make_shared<StopWall>(30000, 700);
    m_objects["player"] = std::make_shared<Player>(1000, 100);
}

void MainScene::render(SDL_Renderer *render_context, const Vector2D &camera_offset) {
    m_x_scroll_offset += (camera_offset.x() - m_last_camera_x) / 2;
    m_last_camera_x = camera_offset.x();

    if (m_x_scroll_offset > m_bg_sprite.width())
        m_x_scroll_offset = 0;
    else if (m_x_scroll_offset < 0)
        m_x_scroll_offset = m_bg_sprite.width();

    m_bg_sprite.render(render_context, -m_x_scroll_offset, 400 - camera_offset.y());
    m_bg_sprite.render(render_context, -m_x_scroll_offset + m_bg_sprite.width(), 400 - camera_offset.y());

    for (auto &object : m_objects)
        object.second->render(render_context, camera_offset);

    m_timer_sprite.render(render_context, 940, 100);
    m_score_sprite.render(render_context, 1720, 0);
}

void MainScene::destroy() {
    m_bg_sprite.destroy();

    for (auto &object : m_objects)
        object.second->destroy();
}

void MainScene::handle_events(const SDL_Event &event) {
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
        send_goto_title();
}

void MainScene::update(std::uint32_t delta_t) {
    if (m_accumulator >= 1200) {
        m_accumulator = 0;
        update_timer();
    }

    if (m_time_left <= 0)
        send_goto_results();

    m_accumulator += delta_t;

    auto player = std::dynamic_pointer_cast<Player>(m_objects["player"]);

    if (player->penalty()) {
        Logger::info("Player penalty: {}" , player->penalty());
        m_spikes_hit += player->penalty();
        m_time_left -= player->penalty() * 3;
        m_score -= player->penalty() * 50;
        player->set_penalty(0);
        update_score();
        update_timer();
    }

    if (m_last_house_spawn_time >= HOUSE_SPAWN_INTERVAL && m_houses.size() < MAX_HOUSES) {
        std::uint32_t x = ServiceLocator::rng().int_between(100, 29000);
        Logger::info("Spawning house at x={}", x);
        auto house = std::make_shared<House>(x, 660);
        m_objects["house" + std::to_string(x)] = house;
        m_houses.push_back(house);
        m_last_house_spawn_time = 0;
    }

    if (m_last_spike_spawn_time >= SPIKE_SPAWN_INTERVAL && m_spikes.size() < MAX_SPIKES) {
        std::uint32_t x = ServiceLocator::rng().int_between(1100, 29000);
        Logger::info("Spawning spikes at x={}", x);
        auto spike = std::make_shared<Spike>(x, 750);
        m_objects["spike" + std::to_string(x)] = spike;
        m_spikes.push_back(spike);
        m_last_spike_spawn_time = 0;
    }

    std::vector<int> houses_to_delete{};
    std::vector<int> spikes_to_delete{};

    for (int i = 0; i < m_houses.size(); ++i) {
        if (m_houses.at(i)->is_dead()) {
            //it->get()->destroy();
            m_objects.erase("house" + std::to_string(m_houses.at(i)->pos().x()));
            m_time_left += 6; // Gain time for destroying a house
            m_score += 100;
            ++m_houses_burned;
            update_timer();
            update_score();
            houses_to_delete.push_back(i);
        }
    }

    for (const auto i : houses_to_delete)
        m_houses.erase(m_houses.begin() + i);

    m_last_house_spawn_time += delta_t;

    for (int i = 0; i < m_spikes.size(); ++i) {
        if (m_spikes.at(i)->is_dead()) {
            m_objects.erase("spike" + std::to_string(m_spikes.at(i)->pos().x()));
            spikes_to_delete.push_back(i);
        }
    }

    for (const auto i : spikes_to_delete)
        m_spikes.erase(m_spikes.begin() + i);

    m_last_spike_spawn_time += delta_t;
}

void MainScene::set_scene_change_event(std::uint32_t event) {
    m_scene_change_event = event;
}

std::shared_ptr<GameObject> MainScene::object(const std::string &id) {
    return m_objects[id];
}

std::map<std::string, std::shared_ptr<GameObject>> &MainScene::all_objects() {
    return m_objects;
}

void MainScene::send_goto_title() const {
    SDL_Event user_event;
    // stupid
    auto scene_id = new TheSalamander::SceneId(TheSalamander::SceneId::TITLE);
    SDL_memset(reinterpret_cast<void *>(&user_event), 0, sizeof(user_event));
    user_event.type = m_scene_change_event;
    user_event.user.code = 1;
    user_event.user.data1 = reinterpret_cast<void *>(scene_id);
    SDL_PushEvent(&user_event);
}

void MainScene::send_goto_results() const {
    SDL_Event user_event;
    // stupid
    auto scene_id = new TheSalamander::SceneId(TheSalamander::SceneId::RESULTS);
    auto results = new Results{
        m_houses_burned,
        m_spikes_hit,
        m_score
    };

    SDL_memset(reinterpret_cast<void *>(&user_event), 0, sizeof(user_event));
    user_event.type = m_scene_change_event;
    user_event.user.code = 1;
    user_event.user.data1 = reinterpret_cast<void *>(scene_id);
    user_event.user.data2 = reinterpret_cast<void *>(results);
    SDL_PushEvent(&user_event);
}

void MainScene::update_timer() noexcept {
    m_timer_sprite.swap_texture(ServiceLocator::texture_cache().replace_from_string("timer_text", std::to_string(--m_time_left)));
}

void MainScene::update_score() noexcept {
    m_score_sprite.swap_texture(ServiceLocator::texture_cache().replace_from_string("score_text", "Score: " + std::to_string(m_score)));
}
