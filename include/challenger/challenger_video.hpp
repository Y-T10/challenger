#pragma once

#include <optional>
#include <type_traits>
#include <utility>
#include <string>
#include <memory>

#include "SDL3/SDL_surface.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"

namespace challenger {
    /// 本来は ``decltype([](T*ptr){deleter(ptr)})`` としたかった．
    /// しかし2024/1/22時点では、g++がこれをうまく処理できない．
    /// そのためこの構造体を定義した
    template<class T, void(*deleter)(T*)>
    struct SDL_deleter {
        void operator()(T* ptr) {
            deleter(ptr);
        };
    };

    template<class T, auto deleter>
    using SDL_ptr = std::unique_ptr<T, SDL_deleter<T, deleter>>;

    using Window = SDL_ptr<SDL_Window, SDL_DestroyWindow>;
    using Renderer = SDL_ptr<SDL_Renderer, SDL_DestroyRenderer>;
    using Surface = SDL_ptr<SDL_Surface, SDL_DestroySurface>;
    using Texture = SDL_ptr<SDL_Texture, SDL_DestroyTexture>;

    template<class ptr_type, auto Func, class ...Args>
    const ptr_type Create(Args&& ...args) noexcept {
        constexpr bool chechFunc = std::is_invocable_r_v<typename ptr_type::pointer, decltype(Func), Args...>;
        static_assert(chechFunc, "Func or ptr_type is wrong.");
        if constexpr (chechFunc) {
            return ptr_type(Func(args...));
        }
        return nullptr;
    };

    inline const Window CreateWindow(const std::string& title, int w, int h, Uint32 flags) noexcept {
        return Window(SDL_CreateWindow(title.c_str(), w, h, flags));
    };

    inline const Renderer CreateDefaultRenderer(const Window& window, Uint32 flags) noexcept {
        return Renderer(SDL_CreateRenderer(window.get(), nullptr, flags));
    }; 

    inline const Surface CreateSurface(const int w, const int h, const SDL_PixelFormatEnum format) noexcept {
        return Surface(SDL_CreateSurface(w, h, format));
    }

    inline const Texture CreateTexture(const Renderer renderer, const SDL_PixelFormatEnum format, const SDL_TextureAccess access, const int w, const int h) noexcept {
        return Texture(SDL_CreateTexture(renderer.get(), format, access, w, h));
    }

    const std::optional<std::pair<float,float>> FitRenderOutput(const Renderer& renderer, const Window& window);
    void RenderSurface(const Renderer& renderer, const Surface& surface, const int x, const int y) noexcept;
}
