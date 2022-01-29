#ifndef SALAMANDER_GAME_H
#define SALAMANDER_GAME_H

#include <cstdint>
#include <map>
#include <memory>
#include <iterator>
#include "GameObject.h"
#include "Scene.h"

struct SDL_Renderer;

struct Game {
    virtual void start() = 0;
    virtual void update(std::uint32_t delta_t) = 0;
    virtual void render(SDL_Renderer *render_context) = 0;
    virtual void handle_events(const SDL_Event &event) = 0;
    virtual std::map<std::string, std::shared_ptr<GameObject>> all_objects() = 0;
    virtual void destroy() = 0;
};

#endif //SALAMANDER_GAME_H
