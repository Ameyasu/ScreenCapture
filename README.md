# Win32Apiで画面キャプチャ
## 概要
- 画面キャプチャの実装サンプルです
- 本アプリはデスクトップ画面をキャプチャしますがウィンドウハンドルを好きなウィンドウの物に変えたりすればそのウィンドウのキャプチャができます
- 本コードは複製・改造OKです
## 使い方
- ウィンドウが最小化されていない限り自動(30fps)で画面キャプチャし続けます
- マウスでアプリの画面内をドラッグすると画面キャプチャ位置を移動できます
- アプリの画面内のマウス位置の色を常に表示し続けます
## 参考サイト
- http://eternalwindows.jp/index.html
  - http://eternalwindows.jp/graphics/bitmap/bitmap10.html
- https://docs.microsoft.com/ja-jp/windows/win32/
  - https://docs.microsoft.com/ja-jp/windows/win32/winmsg/wm-size
