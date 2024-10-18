#pragma once

#include <functional>
#include <cstddef>
#include <vector>

#include "SDL3/SDL_dialog.h"
#include "challenger_video.hpp"

namespace challenger {
    using FilterList = std::vector<SDL_DialogFileFilter>;
    using DialogCallback = std::function<void(const char* const*, const int)>;

    /**
     * @brief ファイル保存ダイアログを表示する
     * @param window ダイアログの親ウィンドウ
     * @param filter ファイルのフィルターセット
     * @param callback ダイアログ終了後の処理
     */
    void ShowSaveFileDialog(
        const Window& window, const FilterList& filter,
        const DialogCallback& callback
    ) noexcept;

    /**
     * @brief ファイルオープンダイアログを表示する
     * @param window ダイアログの親ウィンドウ
     * @param filter ファイルのフィルターセット
     * @param callback ダイアログ終了後の処理
     * @param selectOne ファイルを1つのみ選択するか．デフォルトはtrue．
     */
    void ShowOpenFileDialog(
        const Window& window, const FilterList& filter,
        const DialogCallback& callback, const bool selectOne = true
    ) noexcept;

    /**
     * @brief フォルダオープンダイアログを表示する
     * @param window ダイアログの親ウィンドウ
     * @param callback ダイアログ終了後の処理
     * @param selectOne フォルダを1つのみ選択するか．デフォルトはtrue．
     */
    void ShowOpenFolderDialog(
        const Window& window, const DialogCallback& callback, const bool selectOne = true
    ) noexcept;
}