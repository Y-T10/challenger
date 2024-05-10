#pragma once

#include "SDL3/SDL_events.h"
#include <cassert>
#include <cstddef>
#include <vector>

namespace challenger {    
    /**
     * @brief イベントをすべて取り出す
     * @return std::vector<SDL_Event> 取り出したイベントの配列
     */
    std::vector<SDL_Event> FetchAllEvents() noexcept;
}