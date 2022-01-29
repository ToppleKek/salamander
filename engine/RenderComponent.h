#ifndef SALAMANDER_RENDERCOMPONENT_H
#define SALAMANDER_RENDERCOMPONENT_H

struct SDL_Renderer;

struct RenderComponent {
    virtual void render(SDL_Renderer *render_context, int x, int y) = 0;
};

#endif //SALAMANDER_RENDERCOMPONENT_H
