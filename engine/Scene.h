#ifndef ENGLISH_GAME_SCENE_H
#define ENGLISH_GAME_SCENE_H

#include <SDL2/SDL.h>
#include "GameObject.h"
#include "Vector2D.h"

struct Scene {
    virtual void render(SDL_Renderer *render_context, const Vector2D &camera_offset) = 0;
    virtual void destroy() = 0;
    virtual void handle_events(const SDL_Event &event) = 0;
    virtual void update(std::uint32_t delta_t) = 0;
    virtual void set_scene_change_event(std::uint32_t event) = 0;
    virtual std::shared_ptr<GameObject> object(const std::string &id) = 0;
    virtual std::map<std::string, std::shared_ptr<GameObject>> &all_objects() = 0;
};

#endif //ENGLISH_GAME_SCENE_H
