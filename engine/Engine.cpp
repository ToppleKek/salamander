#include "Engine.h"

#include "Sprite.h"

#define DELTA_T 17

Engine::Engine(std::unique_ptr<Game> t_game) : m_game(std::move(t_game)), m_filesystem_service("./assets/") {}

int Engine::start() {
    Logger::info("Engine starting");

    init();
    m_game->start();

    Sprite fps_text{ServiceLocator::texture_cache().new_from_string("fps_text", "FPS:")};

    while (!m_exit) {
        std::uint32_t new_time = SDL_GetTicks();
        std::uint32_t frame_time = new_time - m_current_time;
        m_current_time = new_time;
        m_accumulator += frame_time;
        fps_frames++;

        if (fps_last_time < SDL_GetTicks() - 1000) {
            fps_last_time = SDL_GetTicks();
            fps_text.swap_texture(ServiceLocator::texture_cache().replace_from_string("fps_text", "FPS: " + std::to_string(fps_frames)));
            //Logger::info("FPS: {}", fps_frames);
            fps_frames = 0;
        }

        while (m_accumulator - DELTA_T >= 0) {
            // update
            tick();
            ticks++;

            if (ticks_last_time < SDL_GetTicks() - 1000) {
                ticks_last_time = SDL_GetTicks();
                //Logger::info("TPS: {}", ticks);
                ticks = 0;
            }

            if (m_exit)
                break;

            m_accumulator -= DELTA_T;
        }

        std::map<std::string, std::shared_ptr<GameObject>> objects = m_game->all_objects();
        SDL_RenderClear(m_renderer);

        m_game->render(m_renderer);
        fps_text.render(m_renderer, 0, 0);
//        for (auto &object : objects)
//            object.second->render(m_renderer);

        SDL_RenderPresent(m_renderer);
    }

    Logger::info("Cleaning up");
    std::map<std::string, std::shared_ptr<GameObject>> objects = m_game->all_objects();

    for (auto &object : objects)
        object.second->destroy();

    m_game->destroy();

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    Logger::info("Done cleanup");
    return 0;
}

void Engine::tick() {
    std::map<std::string, std::shared_ptr<GameObject>> objects = m_game->all_objects();
    handle_events(objects);

    for (auto &object : objects)
        object.second->update(m_accumulator);

    m_game->update(m_accumulator);
}

void Engine::handle_events(const std::map<std::string, std::shared_ptr<GameObject>> &objects) {
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            m_exit = true;
            return;
        }

        m_game->handle_events(e);
        for (auto &object : objects)
            object.second->handle_event(e);
    }
}

void Engine::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        Logger::error("SDL_Init failed: {}", SDL_GetError());
        std::exit(1);
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        Logger::error("IMG_Init failed: {}", IMG_GetError());
        SDL_Quit();
        std::exit(1);
    }

    if (TTF_Init() < 0) {
        Logger::error("TTF_Init failed: {}", TTF_GetError());
        IMG_Quit();
        SDL_Quit();
    }

    if ((m_window = SDL_CreateWindow("The Salamander", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1600, 900,
                                     SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI)) == nullptr) {
        Logger::error("SDL_CreateWindow failed: {}", SDL_GetError());
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        std::exit(1);
    }

    if ((m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)) == nullptr) {
        Logger::error("SDL_CreateRenderer failed: {}", SDL_GetError());
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        std::exit(1);
    }

    SDL_RenderSetLogicalSize(m_renderer, 1920, 1080);

    ServiceLocator::provide(&m_filesystem_service);
    m_texture_cache = MappedTextureCache(m_renderer);
    ServiceLocator::provide(&m_texture_cache);
    ServiceLocator::provide(&m_rng_service);
}
