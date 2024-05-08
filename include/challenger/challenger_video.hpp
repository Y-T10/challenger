#pragma once

#include <string>

#include "challenger_memory.hpp"

#include "SDL3/SDL_video.h"

namespace challenger {
    using Window = SDL_ptr<SDL_Window, SDL_DestroyWindow>;

    inline const Window CreateWindow(const std::string& title, int w, int h, Uint32 flags) noexcept {
        return Window(SDL_CreateWindow(title.c_str(), w, h, flags));
    };

}
