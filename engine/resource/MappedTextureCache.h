#ifndef SALAMANDER_MAPPEDTEXTURECACHE_H
#define SALAMANDER_MAPPEDTEXTURECACHE_H

#include <SDL2/SDL_image.h>
#include <map>
#include "../Services.h"
#include "TextureLoader.h"
#include "../Logger.h"

class MappedTextureCache : public TextureCacheService {
public:
    MappedTextureCache() = default;
    explicit MappedTextureCache(SDL_Renderer *render_context): m_texture_loader(render_context) {}

    SDL_Texture *get(const std::string &texture_key) override {
        Logger::info("MappedTextureCache: getting: {}", texture_key);
        if (m_cache.contains(texture_key))
            return m_cache[texture_key];

        SDL_Texture *texture = m_texture_loader.load(texture_key);
        m_cache[texture_key] = texture;
        return texture;
    }

    SDL_Texture *new_from_string(const std::string &texture_key, const std::string &str) override {
        if (m_cache.contains(texture_key))
            unload(texture_key);

        SDL_Texture *texture = m_texture_loader.load_from_string(str);
        m_cache[texture_key] = texture;
        return texture;
    }

    SDL_Texture *replace_from_string(const std::string &texture_key, const std::string &str) override {
        if (m_cache.contains(texture_key)) {
            unload(texture_key);
            return new_from_string(texture_key, str);
        } else {
            return nullptr;
        }
    }

    void unload(const std::string &texture_key) override {
        //Logger::info("MappedTextureCache: destroying: {}", texture_key);
        if (m_cache.contains(texture_key)) {
            SDL_DestroyTexture(m_cache[texture_key]);
            m_cache.erase(texture_key);
        }
    }

    void unload(SDL_Texture *texture) override {
        for (auto &it : m_cache) {
            if (it.second == texture) {
                unload(it.first);
                break;
            }
        }
    }

private:
    TextureLoader m_texture_loader;
    std::map<std::string, SDL_Texture *> m_cache;
};

#endif //SALAMANDER_MAPPEDTEXTURECACHE_H
