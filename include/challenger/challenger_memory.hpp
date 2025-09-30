#pragma once

#include <type_traits>
#include <memory>
#include <utility>

namespace challenger {
    /**
     * @brief SDLオブジェクト用のスマートポインタ
     * @tparam T オブジェクトの型
     * @tparam real_deleter オブジェクトの廃棄関数
     */
    template<class T>
    using SDL_ptr = std::unique_ptr<T, void (*)(std::add_pointer_t<T>)>;

    /**
     * @brief SDLオブジェクトのスマートポインタを構築するヘルパー関数
     * @tparam Ctor  SDLオブジェクトのコンストラクタ
     * @tparam Dtr   SDLオブジェクトの廃棄関数
     * @tparam Args コンストラクタのパラメータ型
     * @param args コンストラクタの引数
     * @return 生成されたスマートポインタオブジェクト
     */
    template<auto Ctor, auto Dtr, class... Args>
    inline auto Create(Args&&... args) noexcept {
        static_assert(std::is_invocable_v<decltype(Ctor), Args...>);

        using result_type_ptr = std::invoke_result_t<decltype(Ctor), Args...>;
        using result_type = std::remove_pointer_t<result_type_ptr>;
        static_assert(std::is_pointer_v<result_type_ptr>);
        static_assert(!std::is_pointer_v<result_type>);

        static_assert(std::is_invocable_v<decltype(Dtr), result_type_ptr>);

        return SDL_ptr<result_type>(Ctor(std::forward<Args>(args)...), Dtr);
    }
}
