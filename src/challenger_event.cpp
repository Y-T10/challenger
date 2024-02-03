#include "challenger/challenger_event.hpp"


inline std::vector<SDL_Event> challenger::FetchAllEvents() noexcept {
    SDL_LockEventQueue();
    assert(SDL_IsEventQueueActive());
    /// インクリメント時に移動元の要素を破棄する．
    using EQ_pop_iter = event_queue_iterator<true>;
    
    // キューからイベントを移す．
    auto events = std::vector<SDL_Event>(SDL_NumOfEvent());
    std::move(EQ_pop_iter(SDL_EventQueueBegin()), EQ_pop_iter(SDL_EventQueueEnd()), events.begin());
    SDL_UnlockEventQueue();
    return events;
}