# Win32APIで画面キャプチャ
## 概要
- 画面キャプチャの実装サンプルです
- 本アプリはデスクトップ画面をキャプチャしますがウィンドウハンドルを好きなウィンドウの物に変えたりすればそのウィンドウのキャプチャができます
- 本コードは複製・改造OKです
## アプリの仕様
- ウィンドウが最小化されていない限り自動(30fps)で画面キャプチャし続けます
- マウスでアプリの画面内をドラッグすると画面キャプチャ位置を移動できます
- アプリの画面内でマウスが指す座標は常にRGBを表示し続けます
## コードの仕様
- Captureクラスが画面キャプチャをします
- キャプチャしたい画面の数だけこのクラスをnewしてください
- このクラスの使い方はScreenCapture.cppのWndProc関数を参考してください
- 使い方のすべてはこの関数内に収まっています
## 動作確認環境
- Microsoft Visual Studio Community 2019 (Version 16.11.3)
- C++
- Windows 10 Home (21H1)
## 参考サイト
- http://eternalwindows.jp/graphics/bitmap/bitmap10.html
- https://docs.microsoft.com/ja-jp/windows/win32/winmsg/wm-size
