#ifndef SALAMANDER_SERVICES_H
#define SALAMANDER_SERVICES_H

#include <vector>
#include <string>

struct SDL_Renderer;
struct Sprite;
struct SDL_Texture;

struct FilesystemService {
//    virtual std::vector<char> get_file(const std::string &filename) {
//        return std::vector<char>();
//    }

    virtual std::vector<char> get_file(const std::string &filename) = 0;
};

struct TextureCacheService {
    virtual SDL_Texture *get(const std::string &texture_key) = 0;
    virtual SDL_Texture *new_from_string(const std::string &texture_key, const std::string &str) = 0;
    virtual SDL_Texture *replace_from_string(const std::string &texture_key, const std::string &str) = 0;
    virtual void unload(const std::string &texture_key) = 0;
    virtual void unload(SDL_Texture *texture) = 0;
//    virtual SDL_Texture *get(const std::string &texture_key) {
//        return nullptr;
//    }
//
//    virtual void unload(const std::string &texture_key) {}
};

struct RngService {
    virtual std::uint32_t random_int() = 0;
    virtual std::uint32_t int_between(uint32_t x, uint32_t y) = 0;
};

#endif //SALAMANDER_SERVICES_H
