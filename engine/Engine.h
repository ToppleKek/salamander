#ifndef SALAMANDER_ENGINE_H
#define SALAMANDER_ENGINE_H

#include <SDL2/SDL.h>
#include <memory>

#include "Game.h"
#include "RawFilesystem.h"
#include "Mt19937Rng.h"
#include "resource/MappedTextureCache.h"

class Engine {
public:
    explicit Engine(std::unique_ptr<Game> t_game);

    int start();
    void tick();
    void handle_events(const std::map<std::string, std::shared_ptr<GameObject>> &objects);

private:
    std::unique_ptr<Game> m_game;
    bool m_exit = false;
    SDL_Renderer *m_renderer{};
    SDL_Window *m_window{};
    std::uint32_t m_current_time{};
    std::int32_t m_accumulator{};
    RawFilesystem m_filesystem_service;
    MappedTextureCache m_texture_cache;
    Mt19937Rng m_rng_service;
    std::uint32_t fps_last_time{};
    std::uint32_t fps_frames{};
    std::uint32_t ticks{};
    std::uint32_t ticks_last_time{};

    void init();
};

#endif //SALAMANDER_ENGINE_H
