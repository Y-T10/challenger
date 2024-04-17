#include "challenger/challenger_video.hpp"

#include <optional>
#include <memory>

#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"

void challenger::RenderSurface(const Renderer& renderer, const Surface& surface, const int x, const int y) noexcept {
    if(surface.get() == nullptr) {
        return;
    }
    const auto texture = Texture(SDL_CreateTextureFromSurface(renderer.get(), surface.get()));
    if(texture.get() == nullptr) {
        return;
    }
    const SDL_FRect src_area = {.x = 0, .y = 0, .w = (float)surface->w, .h = (float)surface->h};
    const SDL_FRect dst_area = {.x = (float)x, .y = (float)y, .w = (float)surface->w, .h = (float)surface->h};
    SDL_RenderTexture(renderer.get(), texture.get(), &src_area, &dst_area);
}

const std::optional<std::pair<float,float>> challenger::FitRenderOutput(const Renderer& renderer, const Window& window) {
    int render_w = 0, render_h = 0;
    int window_w = 0, window_h = 0;
    SDL_GetWindowSize(window.get(), &window_w, &window_h);
    if(SDL_GetRenderOutputSize(renderer.get(), &render_w, &render_h) < 0) {
        return std::nullopt;
    }
    const float scale_x = (double)(render_w) / (double)(window_w);
    const float scale_y = (double)(render_h) / (double)(window_h);
    return
        SDL_SetRenderScale(renderer.get(), scale_x, scale_y) == 0?
        std::make_optional(std::pair<float, float>{scale_x, scale_y}):
        std::nullopt;
}
