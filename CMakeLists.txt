cmake_minimum_required(VERSION 3.20)

# このプロジェクトの概要を設定する
project(challenger
    VERSION 0.0.1
    LANGUAGES CXX
    DESCRIPTION "Personal cpp template repository."
)

# ビルド周りの設定
option(BUILD_SHARED_LIBS "Build shared libraries." OFF)
option(CMAKE_BUILD_TYPE "Build type." Release)
option(BUILD_EXAMPLE "Build example programs" OFF)

# CMAKE_EXPORT_COMPILE_COMMANDSの既定値を設定する
if ((NOT (DEFINED $ENV{CMAKE_EXPORT_COMPILE_COMMANDS})) AND (DEFINED CMAKE_EXPORT_COMPILE_COMMANDS))
  set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
endif()

# CMakeのポリシーを設定する
cmake_policy(SET CMP0076 NEW)
cmake_policy(SET CMP0128 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0128 NEW)
cmake_policy(SET CMP0074 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0074 NEW)
cmake_policy(SET CMP0077 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

# C++コンパイラに渡すオプションを設定する
add_compile_options(-Wall $<$<CONFIG:Debug>:-g3>)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 20)

# CPMを有効にする
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/CPM.cmake)

# CPMを用いてネット上のパッケージを取り込む
CPMAddPackage(
    NAME fmt
    GITHUB_REPOSITORY fmtlib/fmt
    GIT_TAG 10.2.1
)

CPMAddPackage(
    NAME SDL3
    GITHUB_REPOSITORY "Y-T10/SDL"
    GIT_TAG main
)

# システム内のパッケージを読み込む
find_package(Threads REQUIRED)
find_package(Boost REQUIRED)

# ライブラリの宣言
add_library(${PROJECT_NAME})
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

# ライブラリの設定
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/challenger_video.cpp
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
