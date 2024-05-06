#pragma once

#include <memory>

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
}
