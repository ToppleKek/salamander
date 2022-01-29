#ifndef SALAMANDER_TEXTURELOADER_H
#define SALAMANDER_TEXTURELOADER_H

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "../ServiceLocator.h"

class TextureLoader {
public:
    TextureLoader() = default;
    explicit TextureLoader(SDL_Renderer *render_context);
    SDL_Texture *load(const std::string &texture_key);
    SDL_Texture *load_from_string(const std::string &str);

private:
    SDL_Renderer *m_render_context{nullptr};
    TTF_Font *m_font{nullptr};
    std::vector<char> m_font_data;
};

#endif //SALAMANDER_TEXTURELOADER_H
