#pragma once

#include <string>

#include "challenger_memory.hpp"

#include "SDL3/SDL_video.h"

namespace challenger {
    using Window = SDL_ptr<SDL_Window, SDL_DestroyWindow>;
}
