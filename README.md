# RPicoBoyライブラリ

## 概要
Arduino IDEでfuzziliaが制作したハード「RPicoBoy」のスケッチ開発を行うためのライブラリです。

本ライブラリがなくても後述する外部ライブラリを用いて一から実装することも可能です。

## RPicoBoyで使用しているボードと外部ライブラリ

本ライブラリを使用する前に以下のボードと外部ライブラリをArduino IDEにインストールしておく必要があります。

|ボード名|
|---|
|Raspberry Pi Pico/RP2040|


|外部ライブラリ名|
|---|
|Adafruit GFX Library|
|Adafruit SSD1306|

## ピン定義

RPicoBoyにおけるピン定義は以下の通りです。

|定義名|ピン番号|説明|
|---|---|---|
|PICO_LED_PIN|25|Raspberry Pi Pico本体のLEDピン|
|BUZZER_PIN|15|電圧ブザーピン|
|LED_RED_PIN|26|フルカラーLED REDピン|
|LED_GREEN_PIN|22|フルカラーLED GREENピン|
|LED_BLUE_PIN|21|フルカラーLED BLUEピン|
|LED_ANODE_PIN|20|フルカラーLED ANODEピン|
|BUTTON_A_PIN|28|BUTTON A INPUTピン|
|BUTTON_B_PIN|27|BUTTON B INPUTピン|
|BUTTON_UP_PIN|17|BUTTON UP INPUTピン|
|BUTTON_LEFT_PIN|16|BUTTON LEFT INPUTピン|
|BUTTON_RIGHT_PIN|19|BUTTON RIGHT INPUTピン|
|BUTTON_DOWN_PIN|18|BUTTON DOWN INPUTピン|
|SDA_PIN|4|OLED SDAピン|
|SCL_PIN|5|OLED SCLピン|

## RPicoBoyの環境構築

### Arduino IDEのインストール

PCにArduino IDEをインストールしてください。

### ボードと外部ライブラリのインストール

以下のボードとライブラリをArduino IDEにインストールしてください。

|項目|名称|
|---|---|
|ボード|Raspberry Pi Pico/RP2040|
|外部ライブラリ|Adafruit GFX Library|
|外部ライブラリ|Adafruit SSD1306|

### Arduino IDEへのRPicoBoyライブラリのインストール

1. Releaseページから最新バージョンのzipファイルをダウンロードします。
2. Arduino IDEを起動させて上部メニューから「スケッチ」→「ライブラリをインクルード」→「.ZIP形式のライブラリをインストール」を選択します。
3. zipファイルが選択できるので、1でダウンロードしたzipファイルを指定します(すでにライブラリが存在する場合は上書きを選択します)。
4. RPicoBoyのライブラリがArduino IDEに追加されます。

## RPicoBoyライブラリに含まれるサンプルスケッチの書き込み方法

1. Arduino IDEを起動させ、ボード選択から「Raspbery Pi Pico - Raspbery Pi Pico/RP2040」を指定します。
2. 上部メニューの「ファイル」→「スケッチ例」→「RPicoBoy」→「sample_game」を選択します。
3. サンプルゲームのスケッチが立ち上がるので、RPicoBoyとPCを付属のUSBケーブルで接続します。
4. スケッチを書き込みます。
5. エクスプローラーが立ち上がり、しばらく待つと書き込みが終了してエクスプローラーが自動的に閉じます。
6. RPicoBoyにサンプルスケッチが書き込まれているので遊ぶことができます。

## ドキュメント

ライブラリ内の関数や定数などは以下のドキュメントを参照してください。

※ここにdoxygenで作ったドキュメントURLを貼る。
