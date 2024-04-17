#include "challenger/challenger_event.hpp"
#include <cassert>

std::vector<SDL_Event> challenger::FetchAllEvents() noexcept {
    // キューからイベントを移す．
    auto events = std::vector<SDL_Event>(0);

    for(SDL_Event e; SDL_PollEvent(&e);) {
        events.push_back(e);
    }

    return events;
}