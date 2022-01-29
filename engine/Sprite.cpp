#include "Sprite.h"
#include "ServiceLocator.h"
#include "Logger.h"

Sprite::Sprite(SDL_Texture *texture) : m_texture{texture} {
    SDL_QueryTexture(m_texture, nullptr, nullptr, &m_w, &m_h);
}

Sprite::Sprite(SDL_Texture *texture, int frames, int frame_width) :
    m_texture{texture},
    m_frames{frames},
    m_frame_width{frame_width} {
    SDL_QueryTexture(m_texture, nullptr, nullptr, &m_w, &m_h);
}

Sprite::Sprite(const Sprite &other) {
    m_texture = other.m_texture;
    m_w = other.m_w;
    m_h = other.m_h;
}

Sprite &Sprite::operator=(const Sprite &other) {
    if (this == &other)
        return *this;

    m_texture = other.m_texture;
    return *this;
}

bool Sprite::empty() const noexcept {
    return m_texture == nullptr;
}

void Sprite::next_frame() noexcept {
    if (m_current_frame >= m_frames)
        m_current_frame = 1;
    else
        ++m_current_frame;
}

void Sprite::render(SDL_Renderer *render_context, int x, int y) {
    if (m_frames > 0) {
        SDL_Rect src_rect {
                (m_current_frame - 1) * m_frame_width,
                0,
                m_frame_width,
                m_h
        };

        SDL_Rect draw_rect {
                x,
                y,
                m_frame_width,
                m_h
        };

        SDL_RenderCopy(render_context, m_texture, &src_rect, &draw_rect);
        return;
    }


    SDL_Rect draw_rect {
        x,
        y,
        m_w,
        m_h
    };

    SDL_RenderCopy(render_context, m_texture, nullptr, &draw_rect);
}

void Sprite::render(SDL_Renderer *render_context, int x, int y, SDL_RendererFlip flip) {
    SDL_Rect draw_rect {
            x,
            y,
            m_w,
            m_h
    };

    SDL_RenderCopyEx(render_context, m_texture, nullptr, &draw_rect, 0, nullptr, flip);
}

int Sprite::width() const noexcept {
    return m_w;
}

int Sprite::height() const noexcept {
    return m_h;
}

void Sprite::swap_texture(SDL_Texture *other) noexcept {
    m_texture = other;
    SDL_QueryTexture(m_texture, nullptr, nullptr, &m_w, &m_h);
}

void Sprite::destroy() noexcept {
    ServiceLocator::texture_cache().unload(m_texture);
    m_texture = nullptr;
}

