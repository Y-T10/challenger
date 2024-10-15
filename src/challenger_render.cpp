#include "challenger/challenger_render.hpp"
#include <tuple>

namespace {
    using namespace challenger;
    
    const std::tuple<int, int> WindowSize(const Window& window) {
        int window_w = 0, window_h = 0;
        SDL_GetWindowSize(window.get(), &window_w, &window_h);
        return {window_w, window_h};
    }
}

const bool challenger::FitRenderOutput(const Renderer& renderer, const Window& window) {
    // レンダラの出力サイズを得る
    int render_w = 0, render_h = 0;
    if(!SDL_GetRenderOutputSize(renderer.get(), &render_w, &render_h)) {
        return false;
    }

    // ウィンドウのサイズを得る
    const auto [window_w, window_h] = WindowSize(window);

    // スケールを設定する
    const float scale_x = (double)(render_w) / (double)(window_w);
    const float scale_y = (double)(render_h) / (double)(window_h);
    return SDL_SetRenderScale(renderer.get(), scale_x, scale_y) == 0;
}
