# challenger
[SDL3](https://github.com/libsdl-org/SDL)のC++20ラッパーライブラリ．
元のSDL3との互換性を保ちつつ、C++20のコード内で扱いやすくしている．

## 概要
[SDL3](https://github.com/libsdl-org/SDL)を元に、以下の機能を持つ．
- SDL_WindowやSDL_Renderer等のリソースを管理するクラス．
  - クラスのメンバ関数を使うことで、リソースをSDL3の関数に渡すことができる．
- 一度の呼び出しですべてのイベントを取り出す関数．
