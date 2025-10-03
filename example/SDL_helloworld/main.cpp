#include "challenger/challenger_memory.hpp"
#include "challenger/challenger_render.hpp"
#include "challenger/challenger_event.hpp"
#include "challenger/challenger_video.hpp"
#include "challenger/chDialog.hpp"
#include "SDL3/SDL_timer.h"
#include "SDL3/SDL_init.h"
#include <future>

#define BOOST_SCOPE_EXIT_CONFIG_USE_LAMBDAS
#include "boost/scope_exit.hpp"

namespace challe = challenger;
using namespace challenger;

int main() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        return __LINE__;
    }

    BOOST_SCOPE_EXIT(){
        SDL_Quit();
    };

    challenger::Window window = Create<SDL_CreateWindow, SDL_DestroyWindow>("Hello SDL", 640, 480, 0);

    if(!window) {
        return __LINE__;
    }

    challenger::Renderer renderer = Create<SDL_CreateRenderer, SDL_DestroyRenderer>(window.get(), nullptr);

    if(!renderer) {
        return __LINE__;
    }

    SDL_FRect mouseposrect;
    mouseposrect.x = mouseposrect.y = -1000;  /* -1000 so it's offscreen at start */
    mouseposrect.w = mouseposrect.h = 50;

    const FilterList ExampleFilters = {
        {.name="PNG images", .pattern="png" },
        { "JPEG images", "jpg;jpeg" },
        { "GIF images", "gif" },
        { "All images", "png;jpg;jpeg;gif" },
        { "All files", "*" }
    };

    std::promise<std::vector<std::string>> selected_list;
    auto result = selected_list.get_future();
        
    challe::ShowOpenFileDialog(window, [&selected_list](const PathList& list, const int n) mutable { selected_list.set_value(list);}, ExampleFilters);

    for(bool isRunning = true; isRunning;) {
        /* run through all pending events until we run out. */
        for (const auto& event: challe::FetchAllEvents()) {
            switch (event.type) {
                case SDL_EVENT_QUIT:  /* triggers on last window close and other things. End the program. */
                    isRunning = false;
                    break;

                case SDL_EVENT_KEY_DOWN:  /* quit if user hits ESC key */
                    if (event.key.key == SDLK_ESCAPE) {
                        isRunning = false;
                    }
                    break;

                case SDL_EVENT_MOUSE_MOTION:  /* keep track of the latest mouse position */
                    /* center the square where the mouse is */
                    mouseposrect.x = event.motion.x - (mouseposrect.w / 2);
                    mouseposrect.y = event.motion.y - (mouseposrect.h / 2);
                    break;
            }
        }

        if (result.valid()) {
            if (std::future_status::ready == result.wait_for(std::chrono::milliseconds(1))) {
                const auto tmp = result.get();
                for(const auto &path: tmp) {
                    std::printf("selected: %s\n", path.c_str());
                }
            }
        }

        /* fade between shades of red every 3 seconds, from 0 to 255. */
        const Uint8 r = (Uint8) ((((float) (SDL_GetTicks() % 3000)) / 3000.0f) * 255.0f);
        SDL_SetRenderDrawColor(renderer.get(), r, 0, 0, 255);
        /* you have to draw the whole window every frame. Clearing it makes sure the whole thing is sane. */
        SDL_RenderClear(renderer.get());  /* clear whole window to that fade color. */
        /* set the color to white */
        SDL_SetRenderDrawColor(renderer.get(), 255, 255, 255, 255);
        /* draw a square where the mouse cursor currently is. */
        SDL_RenderFillRect(renderer.get(), &mouseposrect);
        /* put everything we drew to the screen. */
        SDL_RenderPresent(renderer.get());
        SDL_Delay(1);
    }
    return 0;
}