#include "TextureLoader.h"

#include <cassert>
#include "../Logger.h"

TextureLoader::TextureLoader(SDL_Renderer *render_context) : m_render_context(render_context) {
    m_font_data = ServiceLocator::filesystem().get_file("fonts/font.ttf");
    SDL_RWops *rwop = SDL_RWFromMem(m_font_data.data(), static_cast<int>(m_font_data.size()));
    m_font = TTF_OpenFontRW(rwop, 1, 24);

    if (!m_font) {
        Logger::error("Failed to open font: {}", TTF_GetError());
        std::exit(1);
    }
}

SDL_Texture *TextureLoader::load(const std::string &texture_key) {
    assert(m_render_context && "TextureLoader not properly initialized!");

    std::string filename = "texture/" + texture_key + ".png";
    std::vector<char> sprite_data = ServiceLocator::filesystem().get_file(filename);

    SDL_RWops *rwop = SDL_RWFromMem(sprite_data.data(), static_cast<int>(sprite_data.size()));
    SDL_Surface *image = IMG_LoadPNG_RW(rwop);
    SDL_FreeRW(rwop);

    assert(image);

    Logger::info("Loading image: {}", filename);

    SDL_Texture *t = SDL_CreateTextureFromSurface(m_render_context, image);

    if (!t)
        Logger::error(SDL_GetError());

    return t;
}

SDL_Texture *TextureLoader::load_from_string(const std::string &str) {
    SDL_Surface *surface = TTF_RenderText_Solid(m_font, str.c_str(), SDL_Color{255, 255, 255, 255});
    //SDL_Surface *surface = TTF_RenderText_Solid(m_font, str.c_str(), SDL_Color{255, 255, 255, 255});

    if (!surface)
        Logger::error("Failed to create surface from string: {}", TTF_GetError());

    SDL_Texture *t = SDL_CreateTextureFromSurface(m_render_context, surface);

    SDL_FreeSurface(surface);

    if (!t)
        Logger::error("Failed to load texture from string: {}", SDL_GetError());

    return t;
}
