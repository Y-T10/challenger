#pragma once

#include <memory>
#include <utility>

namespace challenger {
    /**
     * @brief SDLオブジェクト用のスマートポインタ
     * @tparam T オブジェクトの型
     * @tparam real_deleter オブジェクトの廃棄関数
     */
    template<class T, auto real_deleter>
    using SDL_ptr = std::unique_ptr<T, decltype([](T* ptr){
        real_deleter(ptr);
    })>;

    /**
     * @brief SDLオブジェクトのスマートポインタを構築するヘルパー関数
     * @tparam smart_ptr SDLオブジェクトのスマートポインタ
     * @tparam Ctor  SDLオブジェクトのコンストラクタ
     * @tparam Args コンストラクタのパラメータ型
     * @param args コンストラクタの引数
     * @return 生成されたスマートポインタオブジェクト
     */
    template<class smart_ptr, auto Ctor, class... Args>
    smart_ptr Create(Args&&... args) noexcept {
        return smart_ptr(Ctor(std::forward<Args>(args)...));
    }
}
