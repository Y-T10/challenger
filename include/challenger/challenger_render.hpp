#pragma once

#include "challenger_video.hpp"

#include "SDL3/SDL_render.h"

namespace challenger {
    /// レンダラのスマートポインタ
    using Renderer = SDL_ptr<SDL_Renderer, SDL_DestroyRenderer>;
    /// テクスチャのスマートポインタ
    using Texture = SDL_ptr<SDL_Texture, SDL_DestroyTexture>;

    /**
     * @brief 既定のレンダラを生成する
     * @param window ウィンドウ
     * @param flags 生成フラグ
     * @return レンダラオブジェクト
     */
    inline const Renderer CreateDefaultRenderer(const Window& window, Uint32 flags) noexcept {
        return Renderer(SDL_CreateRenderer(window.get(), nullptr, flags));
    };

    /**
     * @brief テクスチャを生成する
     * @param renderer レンダラ
     * @param format テクスチャのフォーマット
     * @param access テクスチャへのアクセス設定
     * @param w テクスチャの幅
     * @param h テクスチャの高さ
     * @return const Texture 
     */
    inline const Texture CreateTexture(const Renderer renderer, const SDL_PixelFormatEnum format, const SDL_TextureAccess access, const int w, const int h) noexcept {
        return Texture(SDL_CreateTexture(renderer.get(), format, access, w, h));
    }

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
