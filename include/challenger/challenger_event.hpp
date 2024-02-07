#pragma once

#include "SDL3/SDL_events.h"
#include <forward_list>
#include <type_traits>
#include <algorithm>
#include <concepts>
#include <iterator>
#include <cassert>
#include <cstddef>
#include <vector>

namespace challenger {    
    /**
     * @brief イベントをすべて取り出す
     * @return std::vector<SDL_Event> 取り出したイベントの配列
     */
    std::vector<SDL_Event> FetchAllEvents() noexcept;

    template <SDL_EventType event_type, class event_functor>
    struct EventFunctor {
        constexpr static auto type = event_type;
        using functor = event_functor;
    };

    template<class context_type>
    void DispatchEvent(const SDL_Event& event, context_type& ctx) {
        return;
    }

    template<class context_type, class handler, class ...rests>
    void DispatchEvent(SDL_Event&& event, context_type&& ctx) {
        static_assert(std::is_invocable_v<typename handler::functor, SDL_Event&&, context_type&&>);
        if(event.type == handler::type){
            typename handler::functor{}(std::forward<SDL_Event>(event), std::forward<context_type>(ctx));
            return;
        }
        if constexpr (sizeof...(rests) > 0) {
            DispatchEvent<context_type, rests...>(std::forward<SDL_Event>(event), std::forward<context_type>(ctx));
            return;
        }
        return;
    }

}