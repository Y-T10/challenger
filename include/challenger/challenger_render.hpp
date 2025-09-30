#pragma once

#include "challenger_video.hpp"

#include "SDL3/SDL_render.h"

namespace challenger {
    /// レンダラのスマートポインタ
    using Renderer = SDL_ptr<SDL_Renderer>;
    /// テクスチャのスマートポインタ
    using Texture = SDL_ptr<SDL_Texture>;

    /**
     * @brief ウィンドウを元にレンダラの出力を調整する
     * 
     * @param renderer レンダラ
     * @param window ウィンドウ
     * @return true 出力調整成功
     * @return false 出力調整失敗
     */
    const bool FitRenderOutput(const Renderer& renderer, const Window& window);
}
