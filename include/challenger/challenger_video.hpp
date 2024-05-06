#pragma once

#include <type_traits>
#include <string>

#include "challenger_memory.hpp"

#include "SDL3/SDL_surface.h"
#include "SDL3/SDL_video.h"

namespace challenger {
    using Window = SDL_ptr<SDL_Window, SDL_DestroyWindow>;
    using Surface = SDL_ptr<SDL_Surface, SDL_DestroySurface>;

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

}
