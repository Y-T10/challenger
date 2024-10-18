#include "challenger/chDialog.hpp"
#include "SDL3/SDL_dialog.h"
#include "SDL3/SDL_stdinc.h"

namespace {
    static void SDLCALL callback_impl(void* user, const char* const* filelist, int filter) noexcept {
        auto functor = static_cast<challenger::DialogCallback*>(user);
        (*functor)(filelist, filter);
    }
}

namespace challenger {
    void ShowSaveFileDialog(
        const Window& window, const FilterList& filter,
        const DialogCallback& callback
    ) noexcept {
        SDL_ShowSaveFileDialog(
            callback_impl, (void*)(&callback), window.get(),
            filter.data(), filter.size(), nullptr
        );
    }

    void ShowOpenFileDialog(
        const Window& window, const FilterList& filter,
        const DialogCallback& callback, const bool selectOne
    ) noexcept {
        SDL_ShowOpenFileDialog(
            callback_impl, (void*)(&callback), window.get(),
            filter.data(), filter.size(), nullptr, !selectOne
        );
    }

    void ShowOpenFolderDialog(
        const Window& window, const DialogCallback& callback, const bool selectOne
    ) noexcept {
        SDL_ShowOpenFolderDialog(
            callback_impl, (void*)(&callback), window.get(),
            nullptr, !selectOne
        );
    }
}