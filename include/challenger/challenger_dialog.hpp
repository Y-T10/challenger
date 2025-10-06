#pragma once

#include <vector>

#include "boost/compat/move_only_function.hpp"
#include "challenger_video.hpp"
#include "SDL3/SDL_dialog.h"

namespace challenger {
    using FilterList = std::vector<SDL_DialogFileFilter>;
    using PathList = std::vector<std::string>;
    using CallbackFolder = boost::compat::move_only_function<void(const PathList&)>;
    using CallbackFile = boost::compat::move_only_function<void(const PathList&, const int)>;

    /**
     * @brief ファイル保存ダイアログを表示する
     * @param window ダイアログの親ウィンドウ
     * @param func ファイルのフィルターセット
     * @param filter ファイルのフィルター
     * @param default_location 最初に開かれるフォルダ．デフォルトは空．
     */
    void ShowSaveFileDialog(const Window& window, CallbackFile&& func, const FilterList& filter, const std::string& default_location = "") noexcept;
    
    /**
     * @brief ファイルオープンダイアログを表示する
     * @param window ダイアログの親ウィンドウ
     * @param func ファイルのフィルターセット
     * @param filter ファイルのフィルター
     * @param default_location 最初に開かれるフォルダ．デフォルトは空．
     * @param allow_many ファイルを1つのみ選択するか．デフォルトはfalse．
     */
    void ShowOpenFileDialog(const Window& window, CallbackFile&& func, const FilterList& filter, const std::string& default_location = "", const bool allow_many = true) noexcept;

    /**
     * @brief フォルダオープンダイアログを表示する
     * @param window ダイアログの親ウィンドウ
     * @param func ダイアログ終了後の処理
     * @param default_location 最初に開かれるフォルダ．デフォルトは空．
     * @param allow_many フォルダを1つのみ選択するか．デフォルトはfalse．
     */
    void ShowOpenFolderDialog(const Window& window, CallbackFolder&& func, const std::string& default_location = "", const bool allow_many = true) noexcept;
}