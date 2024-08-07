cmake_minimum_required(VERSION 3.20)

# このプロジェクトの概要を設定する
project(challenger
    VERSION 0.0.1
    LANGUAGES CXX
    DESCRIPTION "SDL3向けのC++ラッパ."
)

# ビルド周りの設定
option(BUILD_SHARED_LIBS "Build shared libraries." OFF)
option(CMAKE_BUILD_TYPE "Build type." Release)
option(BUILD_EXAMPLE "Build example programs" OFF)

# CMAKE_EXPORT_COMPILE_COMMANDSの既定値を設定する
if ((NOT (DEFINED $ENV{CMAKE_EXPORT_COMPILE_COMMANDS})) AND (DEFINED CMAKE_EXPORT_COMPILE_COMMANDS))
  set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
endif()

# C++コンパイラに渡すオプションを設定する
add_compile_options(-Wall $<$<CONFIG:Debug>:-g3>)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 20)

# ネットワーク上で公開されているライブラリを取り込む
include(FetchContent)

FetchContent_Declare(
    SDL
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG a1a82780298df6b966b8bbb5519126c80b286237
)
FetchContent_MakeAvailable(SDL)

# システム内のパッケージを読み込む
find_package(Threads REQUIRED)
find_package(Boost REQUIRED)

# ライブラリの宣言
add_library(${PROJECT_NAME})
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

# ライブラリの設定
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/challenger_render.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/challenger_event.cpp
)
target_link_libraries(
    ${PROJECT_NAME} PUBLIC
    SDL3::SDL3 Threads::Threads Boost::boost
)

# サンプルプログラムのビルド
if(${BUILD_EXAMPLE})
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/example)
endif()
