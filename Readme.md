# challenger
[独自拡張のSDL3](https://github.com/Y-T10/SDL)のC++20ラッパーライブラリ．
元のSDL3との互換性を保ちつつ、C++20のコード内で扱いやすくしている

## 概要
[独自拡張のSDL3](https://github.com/Y-T10/SDL)を元に、以下の機能を持つ．
- SDL_WindowやSDL_Renderer等のリソースを管理するクラス．
  - クラスのメンバ関数を使うことで、リソースをSDL3の関数に渡すことができる．
- 一度の呼び出しですべてのイベントを取り出す関数．
