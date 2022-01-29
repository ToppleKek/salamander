#ifndef SALAMANDER_SPRITE_H
#define SALAMANDER_SPRITE_H

#include <string>
#include <SDL2/SDL_image.h>

class Sprite {
public:
    Sprite() = default;
    explicit Sprite(SDL_Texture *texture);
    Sprite(SDL_Texture *texture, int frames, int frame_width);
    ~Sprite() = default;
    Sprite(const Sprite &other);
    Sprite &operator=(const Sprite &other);

    [[nodiscard]] bool empty() const noexcept;
    void next_frame() noexcept;
    void render(SDL_Renderer *render_context, int x, int y);
    void render(SDL_Renderer *render_context, int x, int y, SDL_RendererFlip flip);
    [[nodiscard]] int width() const noexcept;
    [[nodiscard]] int height() const noexcept;
    void swap_texture(SDL_Texture *other) noexcept;
    void destroy() noexcept;

private:
    SDL_Texture *m_texture{nullptr};
    int m_w{};
    int m_h{};
    int m_frames{};
    int m_frame_width{};
    int m_current_frame{1};
};

#endif //SALAMANDER_SPRITE_H
