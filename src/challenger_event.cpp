#include "challenger/challenger_event.hpp"
#include <cassert>

namespace {
    /**
     * @brief SDLのイベントキューを扱うイテレータ
     * @tparam does_remove インクリメント時に現在の要素を破棄するか
     */
    template <bool does_remove>
    struct event_queue_iterator {
        using value_type = SDL_Event;
        using pointer = SDL_EventQueueElement;
        using reference = std::add_lvalue_reference_t<value_type>;
        using iterator_category = std::input_iterator_tag;
        using difference_type = std::ptrdiff_t;

        SDL_EventQueueElement iter;

        event_queue_iterator(pointer p):
        iter(p){}
        event_queue_iterator():
        iter(nullptr){}
        event_queue_iterator(const event_queue_iterator& rval) = delete;
        event_queue_iterator(event_queue_iterator&& rval)
        :iter(rval.iter) {
            rval.iter = nullptr;
        }

        event_queue_iterator& operator=(const event_queue_iterator& rval) = delete;
        event_queue_iterator& operator=(event_queue_iterator&& rval) {
            if(this == &rval) {
                return *this;
            }
            iter = rval.iter;
            rval.iter = nullptr;
        };

        reference operator*() const noexcept {
            assert(!!iter);
            return *(SDL_GetEvent(iter));
        }

        event_queue_iterator& operator++() noexcept {
            assert(!!iter);
            iter = SDL_ForwardElement(iter, does_remove);
            return *this;
        }

        event_queue_iterator operator++(int) noexcept {
            event_queue_iterator ret(iter);
            ++*this;
            return ret;
        }

        bool operator==(const event_queue_iterator& rval) noexcept {
            return iter == rval.iter;
        }

        bool operator!=(const event_queue_iterator& rval) noexcept {
            return !(*this == rval);
        }
    };

    static_assert(std::input_iterator<event_queue_iterator<true>>);
    static_assert(std::input_iterator<event_queue_iterator<false>>);
}

std::vector<SDL_Event> challenger::FetchAllEvents() noexcept {
    SDL_PumpEvents();
    SDL_LockEventQueue();
    assert(SDL_IsEventQueueActive());
    /// インクリメント時に移動元の要素を破棄する．
    using EQ_pop_iter = event_queue_iterator<true>;
    
    // キューからイベントを移す．
    auto events = std::vector<SDL_Event>(0);
    for(auto element = EQ_pop_iter(SDL_EventQueueBegin()); element != EQ_pop_iter(SDL_EventQueueEnd()); element++) {
        events.push_back(*element);
    }
    SDL_UnlockEventQueue();
    return events;
}