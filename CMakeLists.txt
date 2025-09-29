cmake_minimum_required(VERSION 3.31)

# このプロジェクトの概要を設定する
project(challenger
    VERSION 0.0.1
    LANGUAGES CXX
    DESCRIPTION "SDL3向けのC++ラッパ."
)

# C++コンパイラに渡すオプションを設定する
add_compile_options(-Wall $<$<CONFIG:Debug>:-g3>)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 20)

# システム内のパッケージを読み込む
find_package(Threads REQUIRED)
find_package(Boost REQUIRED CONFIG)

# SDLライブラリがあるかを確認する
if (NOT TARGET SDL3::Headers OR NOT TARGET SDL3::SDL3)
    ## SDLをダウンロードする
    include(FetchContent)
    FetchContent_Declare(
        sdl
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-3.2.22
    )
    FetchContent_MakeAvailable(sdl)
endif()

# ライブラリの宣言
add_library(${PROJECT_NAME})
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

# ライブラリの設定
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/challenger_render.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/challenger_event.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/chDialog.cpp
)
target_link_libraries(
    ${PROJECT_NAME} PUBLIC
    SDL3::SDL3 Threads::Threads Boost::boost
)

# サンプルプログラムのビルド
if(${BUILD_EXAMPLE})
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/example)
endif()
