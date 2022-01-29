#ifndef SALAMANDER_GAMEOBJECT_H
#define SALAMANDER_GAMEOBJECT_H

#include <cinttypes>
#include <utility>
#include <SDL2/SDL.h>
#include <string>
#include <map>
#include <memory>
#include "Vector2D.h"

struct GameObject {
    virtual void update(std::uint32_t delta_t) = 0;
    [[nodiscard]] virtual Vector2D pos() = 0;
    virtual void render(SDL_Renderer *render_context, const Vector2D &camera_offset) = 0;
    virtual void destroy() = 0;
    virtual void handle_event(const SDL_Event &event) = 0;
    [[nodiscard]] virtual SDL_Rect *collider() = 0;
    virtual void on_collide(GameObject &other, const std::string &id) = 0;
    [[nodiscard]] virtual bool is_persistent() const noexcept = 0;
    [[nodiscard]] virtual bool is_dead() const noexcept = 0;
    [[nodiscard]] virtual std::map<std::string, std::shared_ptr<GameObject>> &children() = 0;
};

#endif //SALAMANDER_GAMEOBJECT_H
