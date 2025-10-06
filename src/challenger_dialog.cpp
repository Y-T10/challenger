#include "challenger/challenger_dialog.hpp"
#include <cassert>

namespace {
    using c_string_type = const char* const;

    const challenger::PathList generate_path_list(const c_string_type* list) noexcept {
        challenger::PathList output = {};
        for (c_string_type* iter = list; *iter != nullptr; iter++) {
            output.emplace_back(*iter);
        }
        return output;
    };
}

namespace challenger {
    void ShowSaveFileDialog(const Window& window, CallbackFile&& func, const FilterList& filter, const std::string& default_location) noexcept {
        static CallbackFile _cpp_callback = nullptr;
        if (!!_cpp_callback) { return; }
        _cpp_callback = std::move(func);

        constexpr auto c_callback = [](void* user, const char* const* filelist, int filter_id){
            if (!_cpp_callback) { return; }
            std::invoke(_cpp_callback, generate_path_list(filelist), filter_id);
            _cpp_callback = nullptr;
        };
        const char * def_location = default_location.empty() ? nullptr: default_location.c_str();
        
        SDL_ShowSaveFileDialog(c_callback, nullptr, window.get(), filter.data(), filter.size(), def_location);
    }

    void ShowOpenFileDialog(const Window& window, CallbackFile&& func, const FilterList& filter, const std::string& default_location, const bool allow_many) noexcept {
        static CallbackFile _cpp_callback = nullptr;
        if (!!_cpp_callback) { return; }
        _cpp_callback = std::move(func);

        constexpr auto c_callback = [](void* user, const char* const* filelist, int filter_id){
            if (!_cpp_callback) { return; }
            std::invoke(_cpp_callback, generate_path_list(filelist), filter_id);
            _cpp_callback = nullptr;
        };
        const char * def_location = default_location.empty() ? nullptr: default_location.c_str();
        
        SDL_ShowOpenFileDialog(c_callback, nullptr, window.get(), filter.data(), filter.size(), def_location, allow_many);
    }

    void ShowOpenFolderDialog(const Window& window, CallbackFolder&& func, const std::string& default_location, const bool allow_many) noexcept {
        static CallbackFolder _cpp_callback = nullptr;
        if (!!_cpp_callback) { return; }
        _cpp_callback = std::move(func);

        constexpr auto c_callback = [](void* user, const char* const* filelist, int filter){
            if (!_cpp_callback) { return; }
            std::invoke(_cpp_callback, generate_path_list(filelist));
            _cpp_callback = nullptr;
        };
        const char * def_location = default_location.empty() ? nullptr: default_location.c_str();

        SDL_ShowOpenFolderDialog(c_callback, nullptr, window.get(), def_location, allow_many);
    }
}
