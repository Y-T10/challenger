# プログラム名
add_executable(SDL_helloworld)

# プログラムファイルの出力場所を追加
set_target_properties(
    SDL_helloworld PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)

# ソースファイルを追加
target_sources(SDL_helloworld PRIVATE main.cpp)
# ヘッダファイルのディレクトリを追加
target_include_directories(SDL_helloworld PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# プログラムが利用するターゲットを追加
target_link_libraries(
    SDL_helloworld PRIVATE
    challenger::challenger
)
