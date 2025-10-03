#pragma once

#include <algorithm>
#include <functional>
#include <cstddef>
#include <type_traits>
#include <vector>

#include "boost/compat/move_only_function.hpp"
#include "challenger_video.hpp"
#include "SDL3/SDL_dialog.h"

namespace challenger {
    /// @brief ダイアログ関数のコールバック関数が返すファイルリストのイテレータ
    struct filelist_iterator final {
        using c_string_type = const char* const;

        using iterator_category = std::input_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = c_string_type;
        using const_value_type  = std::add_const_t<value_type>;
        using pointer           = std::add_pointer_t<value_type>;
        using reference         = std::add_lvalue_reference_t<value_type>;

        filelist_iterator(const pointer list):
            m_cur(list){};

        filelist_iterator():
            m_cur(nullptr){};

        filelist_iterator(const filelist_iterator& rval):
            m_cur(rval.m_cur){};

        filelist_iterator(filelist_iterator&& rval):
            m_cur(std::move(rval.m_cur)){};

        filelist_iterator& operator=(const filelist_iterator& rval) noexcept {
            if (this == &rval) { return *this; }
            m_cur = rval.m_cur;
            return *this;
        };

        filelist_iterator& operator=(filelist_iterator&& rval) noexcept {
            if (this == &rval) { return *this; }
            m_cur = std::move(rval.m_cur);
            return *this;
        };

        reference operator*() const { return *m_cur; };
        
        filelist_iterator& operator++() { m_cur++; return *this; }
        filelist_iterator operator++(int) { filelist_iterator tmp = *this; ++(*this); return tmp; }
        
        friend bool operator== (const filelist_iterator& lval, const filelist_iterator& rval) { return lval.m_cur == rval.m_cur; }
        friend bool operator!= (const filelist_iterator& lval, const filelist_iterator& rval) { return lval.m_cur != rval.m_cur; }
        
        pointer m_cur;
    };

    /// filelist_iteratorの先頭を返す
    filelist_iterator begin(const filelist_iterator::pointer ptr) noexcept;
    /// filelist_iteratorの末端を返す
    filelist_iterator end(const filelist_iterator::pointer ptr) noexcept;
}

namespace challenger {
    using FilterList = std::vector<SDL_DialogFileFilter>;
    using PathList = std::vector<std::string>;

    /**
     * @brief ファイル保存ダイアログを表示する
     * @tparam F functor
     * @param window ダイアログの親ウィンドウ
     * @param func ファイルのフィルターセット
     * @param filter ファイルのフィルター
     * @param default_location 最初に開かれるフォルダ．デフォルトは空．
     * @param allow_many ファイルを1つのみ選択するか．デフォルトはfalse．
     */
    template<class F>
    void ShowSaveFileDialog(const Window& window, F&& func, const FilterList& filter, const std::string& default_location = "", const bool allow_many = true) noexcept {
        static_assert(std::is_invocable_v<F, const PathList&, int>);

        static boost::compat::move_only_function<void(const PathList&, int)> _cpp_callback = nullptr;
        if (!!_cpp_callback) { return; }
        _cpp_callback = std::move(func);

        constexpr auto c_callback = [](void* user, const char* const* filelist, int filter_id){
            if (!_cpp_callback) { return; }
            std::invoke(_cpp_callback, PathList(challenger::begin(filelist), challenger::end(filelist)), filter_id);
            _cpp_callback = nullptr;
        };
        const char * def_location = default_location.empty() ? nullptr: default_location.c_str();
        
        SDL_ShowSaveFileDialog(c_callback, nullptr, window.get(), filter.data(), filter.size(), def_location, allow_many);
    }
    
    /**
     * @brief ファイルオープンダイアログを表示する
     * @tparam F functor
     * @param window ダイアログの親ウィンドウ
     * @param func ファイルのフィルターセット
     * @param filter ファイルのフィルター
     * @param default_location 最初に開かれるフォルダ．デフォルトは空．
     * @param allow_many ファイルを1つのみ選択するか．デフォルトはfalse．
     */
    template<class F>
    void ShowOpenFileDialog(const Window& window, F&& func, const FilterList& filter, const std::string& default_location = "", const bool allow_many = true) noexcept {
        static_assert(std::is_invocable_v<F, const PathList&, int>);

        static boost::compat::move_only_function<void(const PathList&, int)> _cpp_callback = nullptr;
        if (!!_cpp_callback) { return; }
        _cpp_callback = std::move(func);

        constexpr auto c_callback = [](void* user, const char* const* filelist, int filter_id){
            if (!_cpp_callback) { return; }
            std::invoke(_cpp_callback, PathList(challenger::begin(filelist), challenger::end(filelist)), filter_id);
            _cpp_callback = nullptr;
        };
        const char * def_location = default_location.empty() ? nullptr: default_location.c_str();
        
        SDL_ShowOpenFileDialog(c_callback, nullptr, window.get(), filter.data(), filter.size(), def_location, allow_many);
    }

    /**
     * @brief フォルダオープンダイアログを表示する
     * @tparam F functor
     * @param window ダイアログの親ウィンドウ
     * @param func ダイアログ終了後の処理
     * @param default_location 最初に開かれるフォルダ．デフォルトは空．
     * @param allow_many フォルダを1つのみ選択するか．デフォルトはfalse．
     */
    template<class F>
    void ShowOpenFolderDialog(const Window& window, F&& func, const std::string& default_location = "", const bool allow_many = true) noexcept {
        static boost::compat::move_only_function<void(const PathList&)> _cpp_callback = nullptr;
        if (!!_cpp_callback) { return; }
        _cpp_callback = std::move(func);

        constexpr auto c_callback = [](void* user, const char* const* filelist, int filter){
            if (!_cpp_callback) { return; }
            std::invoke(_cpp_callback, PathList(challenger::begin(filelist), challenger::end(filelist)));
            _cpp_callback = nullptr;
        };
        const char * def_location = default_location.empty() ? nullptr: default_location.c_str();

        SDL_ShowOpenFolderDialog(c_callback, nullptr, window.get(), def_location, allow_many);
    }
}