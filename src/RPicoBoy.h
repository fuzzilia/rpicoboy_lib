/**
* @file RPicoBoy.h
* @brief RPicoBoyを動かすためのライブラリヘッダーファイル
*
* @details RPicoBoyを動かすためのライブラリ
* @note githubのURLを貼り付けておこう
*/
#ifndef RPicoBoy_h

#define RPicoBoy_h

#include <stdio.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/** Raspberry Pi Pico本体のLEDピン */
#define PICO_LED_PIN 25
/** 電圧ブザーピン */
#define BUZZER_PIN   15

/** フルカラーLED REDピン */
#define LED_RED_PIN   26
/** フルカラーLED GREENピン */
#define LED_GREEN_PIN 22
/** フルカラーLED BLUEピン */
#define LED_BLUE_PIN  21
/** フルカラーLED ANODEピン */
#define LED_ANODE_PIN 20

/** BUTTON A INPUTピン */
#define BUTTON_A_PIN     28
/** BUTTON B INPUTピン */
#define BUTTON_B_PIN     27
/** BUTTON UP INPUTピン */
#define BUTTON_UP_PIN    17
/** BUTTON LEFT INPUTピン */
#define BUTTON_LEFT_PIN  16
/** BUTTON RIGHT INPUTピン */
#define BUTTON_RIGHT_PIN 19
/** BUTTON DOWN INPUTピン */
#define BUTTON_DOWN_PIN  18

/** EEPROM SDAピン */
#define EEPROM_SDA_PIN 2
/** EEPROM SCLピン */
#define EEPROM_SCL_PIN 3
/** EEPROM チップadress */
#define EEPROM_ADDRESS 0x50
/** EEPROM 番地の最大値 */
#define MAX_EEADDRESS 32766

/** OLED SDAピン */
#define SDA_PIN 4
/** OLED SCLピン */
#define SCL_PIN 5

/** OLED横幅ドット数 */
#define SCREEN_WIDTH 128
/** OLED縦幅ドット数 */
#define SCREEN_HEIGHT 64
/** OLEDリセット端子(未使用-1) */
#define OLED_RESET    -1

/** フルカラーLED PWM最大値 */
#define LED_MAX      255
/** フルカラーLED LUX最大値 */
#define LUX_MAX      155
/** フルカラーLED 赤色の電圧値 */
#define RED_VOLTAGE  2.1
/** Raspberry Pi Picoの電圧値 */
#define PICO_VOLTAGE 3.3

/** テキスト表示の白文字モード */
#define TEXT_W_MODE  0
/** テキスト表示の黒文字モード */
#define TEXT_BW_MODE 1

/** ボタンA */
#define BTN_A     0
/** ボタンB */
#define BTN_B     1
/** ボタン上 */
#define BTN_UP    2
/** ボタン右 */
#define BTN_RIGHT 3
/** ボタン左 */
#define BTN_LEFT  4
/** ボタン下 */
#define BTN_DOWN  5
/** いずれかのボタン */
#define BTN_STATE 6
/** ボタン最大値 */
#define BTN_MAX   7
/** 任意のデータを持ちまわれる数の最大値 */
#define VAL_DATA_MAX 50

/** OLED(SSD1306)画面オブジェクト*/
Adafruit_SSD1306 oled_obj(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/** 
 * RPicoBoyクラス。
 *
 * RPicoBoyで開発を行うための様々な機能を持つクラス。
 */
class RPicoBoy {
  public:
    RPicoBoy();
    void init(int fps, int one_sound_delay);
    void setFpsDelay(int fps);
    void setOneSoundDelay(int one_sound_delay);
    void startFps();
    void getFpsDelay(int *fps, unsigned int *delay_time);
    void getSoundDelay(int *sound_delay);
    void fpsDelay();
    void oneSoundDelay();
    void setMenuSelect(int number);
    int getMenuSelect();
    bool isChangedMenuSelect();
    // void setVariableData(unsigned int adress, byte data);
    // byte getVariableData(unsigned int adress);
    // void clearVariableData();

    // OLEDの関数
    void oledSetup();
    void setDrawColor(uint16_t color);
    void setTextSize(uint8_t size);
    void setTextColor(int mode);
    void setCursor(int16_t x, int16_t y);
    void drawPixel(int16_t x, int16_t y);
    void dotInversion(int16_t x, int16_t y);
    void drawImage64bitBin(int16_t x, int16_t y, int w, int h, int s, long long unsigned int *array, long long unsigned int *mArray);
    void drawImage64bitBinExpansion(int16_t x, int16_t y, int w, int h, int s, long long unsigned int *array, long long unsigned int *mArray, unsigned short exp_rate);
    void drawImage64bitBinExpansionConst(int16_t x, int16_t y, int w, int h, int s, const long long unsigned int *array, const long long unsigned int *mArray, unsigned short exp_rate);
    void drawPixelWithMask(int16_t x, int16_t y, char bin_c, char mask_c);
    // void drawArrayImage(int16_t x, int16_t y, int w, int h, bool *array);
    void drawArrayImage90Rot(int16_t x, int16_t y, int w, int h, long long unsigned int *array);
    void drawArrayImage90RotConst(int16_t x, int16_t y, int w, int h, const long long unsigned int *array);
    void drawLine(int16_t start_x, int16_t start_y, int16_t end_x, int16_t end_y);
    void fillRect(int16_t start_x, int16_t start_y, int16_t end_x, int16_t end_y);
    void print(String s);
    void println(String s);
    void clearDisplay();
    void display();

    // フルカラーLEDの関数
    void ledSetup();
    void ledOn(int r, int g, int b, int value);
    void ledOff();
  
    // ボタンの関数
    void buttonSetup();
    void getButtons(bool *buttonArray);
    void resetButton();
    void updateButton();
    bool getButton(int btn_number);
    bool isCrossAllButton();
  
    // ブザーの関数
    void buzzerSetup();
    void buzzerCall(int freq);
    void buzzerCallDelay(int freq, int delay_time);
  
    // EEPROMの関数
    void writeEEPROM(unsigned int eeaddress, byte data);
    byte readEEPROM(unsigned int eeaddress);
 
  private:
    Adafruit_SSD1306 *_oled;   /**< SSD1306画面オブジェクトのポインタ */
    int _menu_select;          /**< メニューで選択された値 */
    int _old_menu_select;      /**< ひとつ前のメニューで選択された値 */
    int _fps;                  /**< FPS */
    unsigned long _old_micros; /**< 測定開始時のUNIX時間 */
    unsigned int _delay_time;  /**< 待ち時間(microseconds) */
    int _one_sound_delay;      /**< 一音分の待ち時間(milliseconds) */
    uint16_t _draw_color;      /**< 描画色(WHITE or BLACKのどちらかの定数を設定) */
    uint8_t _text_size;        /**< テキストサイズ */
    int _r_pin;                /**< フルカラーLEDのRedピン */
    int _g_pin;                /**< フルカラーLEDのGreenピン */
    int _b_pin;                /**< フルカラーLEDのBlueピン */
    int _anode_pin;            /**< フルカラーLEDのアノードピン */
    int _buzzer_pin;           /**< ブザーピン */
    bool _buttons[BTN_MAX] = {false, false, false, false, false, false, false}; /**< ボタン状態配列([A, B, UP, RIGHT, LEFT, DOWN, state]) */
    bool _old_buttons[BTN_MAX] = {false, false, false, false, false, false, false}; /**< 1つ前のボタン状態配列([A, B, UP, RIGHT, LEFT, DOWN, state]) */
    // byte _variable_data[VAL_DATA_MAX] = {}; /**< 任意のデータ入力範囲 */
};

/**
 * コンストラクタ
 *
 * 各クラス内変数の初期化を行う。
 */
RPicoBoy::RPicoBoy() {
  _oled = &oled_obj;
  _menu_select = 0;
  _old_menu_select = 0;
  _old_micros = micros();
  _fps = 100;
  _delay_time = 10000;
  _one_sound_delay = 150;
  _draw_color = WHITE;
  _text_size = 1;
  _r_pin = 0;
  _g_pin = 0;
  _b_pin = 0;
  _anode_pin = 0;
  _buzzer_pin = 0;
}

/**
 * 初期化関数
 *
 * OLED、フルカラーLED、ボタン、ブザー、EEPROMを初期化して使用できるようにする。
 * また画面のFPSと1音分のディレイ時間を設定する。
 *
 * @param[in] int fps fps数(0だと待ち時間なし)
 * @param[in] int one_sound_delay 一音分の待ち時間(milliseconds)
 */
void RPicoBoy::init(int fps, int one_sound_delay) {
  oledSetup();
  ledSetup();
  buttonSetup();
  buzzerSetup();

  // EEPROMの準備
  Wire1.setSDA(EEPROM_SDA_PIN);
  Wire1.setSCL(EEPROM_SCL_PIN);
  Wire1.begin();

  setFpsDelay(fps);
  _one_sound_delay = one_sound_delay;
}

/**
 * FPSを設定する関数
 *
 * 引数から待ち時間を計算し設定する。
 *
 * @param[in] int fps fps数(0だと待ち時間なし)
 */
void RPicoBoy::setFpsDelay(int fps) {
  if (fps <= 0) {
    _fps = 0;
    _delay_time = 0;
  } else {
    _fps = fps;
    _delay_time = (unsigned int)1000000/fps; // microseconds
  }
}

/**
 * 一音分の待ち時間を設定する関数
 *
 * 引数の待ち時間を設定する。
 *
 * @param[in] int one_sound_delay 一音分の待ち時間(milliseconds)
 */
void RPicoBoy::setOneSoundDelay(int one_sound_delay) {
  _one_sound_delay = one_sound_delay;
}

/**
 * FPS用に時間の計測を開始する関数
 *
 * FPSを正確に計測するために処理loopの最初に記述する。
 */
void RPicoBoy::startFps() {
  _old_micros = micros();
}

/**
 * FPSと待ち時間を取得する関数
 *
 * 引数のポインタに値を渡す。
 *
 * @param[out] fps fpsのポインタ
 * @param[out] delay_time 待ち時間のポインタ
 */
void RPicoBoy::getFpsDelay(int *fps, unsigned int *delay_time) {
  *fps = _fps;
  *delay_time = _delay_time;
}

/**
 * 一音の待ち時間を取得する関数
 *
 * 引数のポインタに値を渡す。
 *
 * @param[out] sound_delay 一音の待ち時間のポインタ
 */
void RPicoBoy::getSoundDelay(int *sound_delay) {
  *sound_delay = _one_sound_delay;
}

/**
 * FPSの処理待ち関数
 *
 * FPS設定時に計算した分だけ処理待ちする。
 */
void RPicoBoy::fpsDelay() {
  unsigned int new_time = micros();
  if (new_time > _old_micros) {
    unsigned int diff_time = new_time - _old_micros;
    if (_delay_time > diff_time) {
      unsigned int wait_time = _delay_time - diff_time;
      delayMicroseconds(wait_time);
    }
  } else {
    // 計算上おかしい場合は単純に1フレーム分待つ
    delayMicroseconds(_delay_time);
  }
}

/**
 * 一音の処理待ち関数
 *
 * 一音分だけ処理待ちする。
 */
void RPicoBoy::oneSoundDelay() {
  delay(_one_sound_delay);
}

/**
 * メニュー番号を設定する関数
 *
 * 選択されているメニューの番号を設定する。
 * この際一つ前のメニュー番号も記録する。(メニューが切り替わったかを判定するため)
 *
 * @param[in] number メニュー番号
 */
void RPicoBoy::setMenuSelect(int number) {
  _old_menu_select = _menu_select;
  _menu_select = number;
}

/**
 * メニュー番号を取得する関数
 *
 * 選択されているメニューの番号を取得する。
 *
 * @return int メニュー番号
 */
int RPicoBoy::getMenuSelect() {
  return _menu_select;
}

/**
 * メニューが切り替わったかを判定する関数
 *
 * 切り替わった場合true、切り替わっていない場合falseを返す。
 *
 * @return bool true:切り替わった、false:切り替わっていない
 */
bool RPicoBoy::isChangedMenuSelect() {
  if (_old_menu_select != _menu_select) {
    return true;
  } else {
    return false;
  }
}

// /**
//  * 任意のデータを格納する関数
//  *
//  * RPicoBoyのオブジェクトが保持する任意のデータを持つ配列にデータを格納する。
//  *
//  * @param[in] adress 番号(0～VAL_DATA_MAX-1の値)
//  * @param[in] data 書き込むデータ
//  */
// void RPicoBoy::setVariableData(unsigned int adress, byte data) {
//   // 最大番地以上の場合は何もしない
//   if (adress >= VAL_DATA_MAX) { return; }
//   _variable_data[adress] = data;
// }

// /**
//  * 任意のデータを取得する関数
//  *
//  * RPicoBoyのオブジェクトが保持する任意のデータを持つ配列のデータを取得する
//  *
//  * @return byte データ（番地の範囲外の場合は0xFFを返す）
//  */
// byte RPicoBoy::getVariableData(unsigned int adress) {
//   byte rdata = 0xFF;

//   // 最大番地以上の場合はデフォルト値を返す
//   if (adress >= VAL_DATA_MAX) { return rdata; }
//   return _variable_data[adress];
// }

// /**
//  * 任意データの配列をクリアする関数
//  *
//  * RPicoBoyのオブジェクトが保持する任意のデータを持つ配列のデータをすべてクリアする
//  */
// void clearVariableData() {
//   _variable_data[VAL_DATA_MAX] = {};
// }

/**
 * OLEDのセットアップをする関数
 *
 * OLEDのセットアップを行い使用できるようにする。
 */
void RPicoBoy::oledSetup() {
  // OLEDの初期化処理
  Wire.setSDA(SDA_PIN);
  Wire.setSCL(SCL_PIN);
  Wire.begin();

  // OLED初期設定
  if (!_oled->begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    // エラーなら無限ループ
    while (true) {
      Serial.println("SSD1306:0 allocation failed");
      delay(3000);
    };
  }

  // 文字と色の設定
  setTextSize(1);
  setTextColor(TEXT_W_MODE);
  setDrawColor(WHITE);
}

/**
 * 描画色を設定する関数
 *
 * 引数の描画色を設定する。
 *
 * @param[in] color WHITE or BLACK
 */
void RPicoBoy::setDrawColor(uint16_t color) {
  _draw_color = color;
}

/**
 * テキストサイズを設定する関数
 *
 * OLEDに表示するテキストサイズを設定する。
 *
 * @param[in] size テキストサイズ
 */
void RPicoBoy::setTextSize(uint8_t size) {
  _text_size = size;
  _oled->setTextSize(size);
}

/**
 * 文字色を設定する関数
 *
 * OLEDに表示する文字色を設定する。
 *
 * @param[in] mode TEXT_W_MODE or TEXT_BW_MODE
 */
void RPicoBoy::setTextColor(int mode) {
  if (mode == TEXT_W_MODE) {
    _oled->setTextColor(WHITE);
  } else {
    _oled->setTextColor(BLACK, WHITE);
  }
}

/**
 * カーソル位置を設定する関数
 *
 * OLED上のカーソル位置を設定する。
 *
 * @param[in] x x座標
 * @param[in] y y座標
 */
void RPicoBoy::setCursor(int16_t x, int16_t y) {
  _oled->setCursor(x, y);
}

/**
 * 指定座標のピクセルにドットを描く関数
 *
 * OLED上の指定位置にドットを描く。
 * この時の色はsetDrawColor関数で設定した値を用いる。
 *
 * @param[in] x x座標
 * @param[in] y y座標
 */
void RPicoBoy::drawPixel(int16_t x, int16_t y) {
  _oled->drawPixel(x, y, _draw_color);
}

/**
 * 対象ピクセルのドットを反転させる関数
 *
 * OLED上の指定位置のドットの色を反転させる。
 *
 * @param[in] x x座標
 * @param[in] y y座標
 */
void RPicoBoy::dotInversion(int16_t x, int16_t y) {
  bool dot = _oled->getPixel(x, y);
  _oled->drawPixel(x, y, !dot);
}

/**
 * 64bitまでの配列イメージを表示する関数
 *
 * 64bitまでの配列ドット画像を表示させる。
 *
 * @param[in] x 開始位置のx座標
 * @param[in] y 開始位置のy座標
 * @param[in] w 横幅ドット数
 * @param[in] h 縦幅ドット数
 * @param[in] s 横幅ドット数の内の必要な分のドット数
 * @param[in] array 16進数のドットイメージ配列
 * @param[in] mArray 16進数のマスクドットイメージ配列
 */
void RPicoBoy::drawImage64bitBin(int16_t x, int16_t y, int w, int h, int s, long long unsigned int *array, long long unsigned int *mArray) {
  int result = 0;

  for (int i = 0; i < h; i++) {
    // 16進数の1行分を2進数で取得
    char bin_c[w];
    for (int j = (w-1); j >=0; j--) {
      result = (array[i] >> j) & 1;
      bin_c[(w-1)-j] = '0'+result;
    }
  
    // マスクがあればそっちも2進数で取得
    char bin_c_m[w];
    if (mArray != NULL) {
      for (int j = (w-1); j >=0; j--) {
        result = (mArray[i] >> j) & 1;
        bin_c_m[(w-1)-j] = '0'+result;
      }
    }

    // 必要な分だけ表示
    for (int k = 0; k < s; k++) {
      if (mArray != NULL) {
        // マスクがある場合
        drawPixelWithMask(x+k, y+i, bin_c[k], bin_c_m[k]);
      } else {
        // マスクがない場合
        drawPixelWithMask(x+k, y+i, bin_c[k], ' ');
      }
    }
  }
}

/**
 * 64bitまでの配列イメージを拡大倍率を設定して表示する関数
 *
 * 64bitまでの配列ドット画像を表示させる。
 *
 * @param[in] x 開始位置のx座標
 * @param[in] y 開始位置のy座標
 * @param[in] w 横幅ドット数
 * @param[in] h 縦幅ドット数
 * @param[in] s 横幅ドット数の内の必要な分のドット数
 * @param[in] array 16進数のドットイメージ配列
 * @param[in] mArray 16進数のマスクドットイメージ配列
 * @param[in] exp_rate 拡大倍率
 */
void RPicoBoy::drawImage64bitBinExpansion(int16_t x, int16_t y, int w, int h, int s, long long unsigned int *array, long long unsigned int *mArray, unsigned short exp_rate) {
  int result = 0;

  for (int i = 0; i < h; i++) {
    // 16進数の1行分を2進数で取得
    char bin_c[w];
    for (int j = (w-1); j >=0; j--) {
      result = (array[i] >> j) & 1;
      bin_c[(w-1)-j] = '0'+result;
    }
  
    // マスクがあればそっちも2進数で取得
    char bin_c_m[w];
    if (mArray != NULL) {
      for (int j = (w-1); j >=0; j--) {
        result = (mArray[i] >> j) & 1;
        bin_c_m[(w-1)-j] = '0'+result;
      }
    }

    // 必要な分だけ表示
    for (int k = 0; k < s; k++) {
      for (int l = 1; l <= exp_rate; l++) {
        for (int m = 1; m <= exp_rate; m++) {
          if (mArray != NULL) {            
            drawPixelWithMask(x+k*exp_rate+l, y+i*exp_rate+m, bin_c[k], bin_c_m[k]);
          } else {
            drawPixelWithMask(x+k*exp_rate+l, y+i*exp_rate+m, bin_c[k], ' ');
          }
        }
      }
    }
  
  }
}

/**
 * 64bitまでの配列イメージを拡大倍率を設定して表示する関数のConstバージョン
 *
 * 64bitまでの配列ドット画像を表示させる。
 *
 * @param[in] x 開始位置のx座標
 * @param[in] y 開始位置のy座標
 * @param[in] w 横幅ドット数
 * @param[in] h 縦幅ドット数
 * @param[in] s 横幅ドット数の内の必要な分のドット数
 * @param[in] array 16進数のドットイメージ配列(Const)
 * @param[in] mArray 16進数のマスクドットイメージ配列(Const)
 * @param[in] exp_rate 拡大倍率
 */
void RPicoBoy::drawImage64bitBinExpansionConst(int16_t x, int16_t y, int w, int h, int s, const long long unsigned int *array, const long long unsigned int *mArray, unsigned short exp_rate) {
  int result = 0;

  for (int i = 0; i < h; i++) {
    // 16進数の1行分を2進数で取得
    char bin_c[w];
    for (int j = (w-1); j >=0; j--) {
      result = (array[i] >> j) & 1;
      bin_c[(w-1)-j] = '0'+result;
    }
  
    // マスクがあればそっちも2進数で取得
    char bin_c_m[w];
    if (mArray != NULL) {
      for (int j = (w-1); j >=0; j--) {
        result = (mArray[i] >> j) & 1;
        bin_c_m[(w-1)-j] = '0'+result;
      }
    }

    // 必要な分だけ表示
    for (int k = 0; k < s; k++) {
      for (int l = 1; l <= exp_rate; l++) {
        for (int m = 1; m <= exp_rate; m++) {
          if (mArray != NULL) {            
            drawPixelWithMask(x+k*exp_rate+l, y+i*exp_rate+m, bin_c[k], bin_c_m[k]);
          } else {
            drawPixelWithMask(x+k*exp_rate+l, y+i*exp_rate+m, bin_c[k], ' ');
          }
        }
      }
    }
  
  }
}

/**
 * マスクの値を判定してドットを打つ関数
 *
 * マスクの部分かどうかを判定してドットを打つ。
 *
 * @param[in] x x座標
 * @param[in] y y座標
 * @param[in] bin_c 描画の値
 * @param[in] mask_c マスクの値
 */
void RPicoBoy::drawPixelWithMask(int16_t x, int16_t y, char bin_c, char mask_c) {
  bool pixel = _oled->getPixel(x, y);
  if (bin_c == '1') {
    // ドットが立っているものについては普通にドットを打つ
    drawPixel(x, y);
  } else if (pixel) {
    // マスクの範囲外であれば
    if (mask_c == '0') {
      _oled->drawPixel(x, y, BLACK);
    }
  }
}

// 配列のイメージを表示する関数
// x, yは開始座標、wは横幅、hは縦幅、*arrayは0または1を持つ配列
// void RPicoBoy::drawArrayImage(int16_t x, int16_t y, int w, int h, bool *array) {
//   int max_num = w * h;
//   int h_num = -1;

//   for (int i = 0; i < max_num; i++) {
//     int w_num = i % w;
//     if (w_num == 0) { h_num++; }
//     _oled->drawPixel(x+w_num, y+h_num, array[i]);
//   }
// }

/**
 * 90度右に傾けた配列のイメージを表示する関数
 *
 * 横幅が64を超える場合に使用する。
 *
 * @param[in] x 開始位置x座標
 * @param[in] y 開始位置y座標
 * @param[in] w 横幅ドット数
 * @param[in] h 縦幅ドット数
 * @param[in] array 16進数のドットイメージ配列
 */
void RPicoBoy::drawArrayImage90Rot(int16_t x, int16_t y, int w, int h, long long unsigned int *array) {
  int result = 0;
  int line_num = 0;

  for (int i = 0; i < w; i++) {
    // 16進数の1行分を2進数で取得
    char bin_c[h];
    for (int j = (h-1); j >=0; j--) {
      result = (array[i] >> j) & 1;
      bin_c[(h-1)-j] = '0'+result;
    }

    // Serial.println(bin_c);

    // 必要な分だけ表示
    for (int k = 0; k < h; k++) {
      if (bin_c[k] == '1') { drawPixel(x+line_num, y+k); };
    }

    line_num++;
  }
}

/**
 * 90度右に傾けた配列のイメージを表示する関数のConstバージョン
 *
 * 横幅が64を超える場合に使用する。
 *
 * @param[in] x 開始位置x座標
 * @param[in] y 開始位置y座標
 * @param[in] w 横幅ドット数
 * @param[in] h 縦幅ドット数
 * @param[in] array 16進数のドットイメージ配列(Const)
 */
void RPicoBoy::drawArrayImage90RotConst(int16_t x, int16_t y, int w, int h, const long long unsigned int *array) {
  int result = 0;
  int line_num = 0;

  for (int i = 0; i < w; i++) {
    // 16進数の1行分を2進数で取得
    char bin_c[h];
    for (int j = (h-1); j >=0; j--) {
      result = (array[i] >> j) & 1;
      bin_c[(h-1)-j] = '0'+result;
    }

    // Serial.println(bin_c);

    // 必要な分だけ表示
    for (int k = 0; k < h; k++) {
      if (bin_c[k] == '1') { drawPixel(x+line_num, y+k); };
    }

    line_num++;
  }
}

/**
 * 直線を引く関数
 *
 * OLEDの画面に直線を引く。
 *
 * @param[in] start_x 開始位置x座標
 * @param[in] start_y 開始位置y座標
 * @param[in] end_x 終了位置x座標
 * @param[in] end_y 終了位置y座標
 */
void RPicoBoy::drawLine(int16_t start_x, int16_t start_y, int16_t end_x, int16_t end_y) {
  _oled->drawLine(start_y, start_x, end_y, end_x, _draw_color);
}

/**
 * 塗りつぶしの四角を表示する関数
 *
 * OLEDの画面に塗りつぶしの四角を描く。（多分動かない）
 *
 * @param[in] start_x 開始位置x座標
 * @param[in] start_y 開始位置y座標
 * @param[in] end_x 終了位置x座標
 * @param[in] end_y 終了位置y座標
 */
void RPicoBoy::fillRect(int16_t start_x, int16_t start_y, int16_t end_x, int16_t end_y) {
  _oled->fillRect(start_y, start_x, end_y, end_x, WHITE);
}

/**
 * 文字を表示する関数
 *
 * OLEDの画面に文字を表示する。
 *
 * @param[in] s 表示文字列
 */
void RPicoBoy::print(String s) {
  _oled->print(s);
}

/**
 * 文字を表示する関数(改行つき)
 *
 * OLEDの画面に文字を改行つきで表示する。
 *
 * @param[in] s 表示文字列
 */
void RPicoBoy::println(String s) {
  _oled->println(s);
}

/**
 * 画面をクリアする関数
 *
 * OLEDの画面をクリア(何も描かれていない状態)にする。
 */
void RPicoBoy::clearDisplay() {
  _oled->clearDisplay();
}

/**
 * OLEDの画面に反映させる関数
 *
 * 描画した文字やドットをOLEDの画面に反映させる。
 * この関数を使用しないと文字やドットを変更してもOLEDの画面に表示されない。
 */
void RPicoBoy::display() {
  _oled->display();
}

/**
 * フルカラーLEDをセットアップする関数
 *
 * フルカラーLEDを使用できるようにする。
 * またPicoのLEDを点灯させる。
 */
void RPicoBoy::ledSetup() {
  // ピン番号取得
  _r_pin = LED_RED_PIN;
  _g_pin = LED_GREEN_PIN;
  _b_pin = LED_BLUE_PIN;
  _anode_pin = LED_ANODE_PIN;

  // ピンの設定
  pinMode(PICO_LED_PIN, OUTPUT);
  pinMode(_r_pin, OUTPUT);
  pinMode(_g_pin, OUTPUT);
  pinMode(_b_pin, OUTPUT);
  pinMode(_anode_pin, OUTPUT);

  // picoのLEDを点灯させてフルカラーLEDを消灯
  digitalWrite(PICO_LED_PIN, HIGH);
  ledOff();
}

/**
 * フルカラーLEDを光らせる関数
 *
 * 電圧の関係などもあり、RGBの値通りの色にはならないので注意が必要。
 *
 * @param[in] r Redの値
 * @param[in] g Greenの値
 * @param[in] b Blueの値
 * @param[in] value 光の強さ
 */
void RPicoBoy::ledOn(int r, int g, int b, int value) {
  int r_val = (r >= LED_MAX) ? LED_MAX : r;
  int g_val = (g >= LED_MAX) ? LED_MAX : g;
  int b_val = (b >= LED_MAX) ? LED_MAX : b;
  int val   = (value >= LUX_MAX) ? LUX_MAX : value;

  // rのみ電圧が低いので計算で調整
  r_val = r_val * RED_VOLTAGE / PICO_VOLTAGE;

  // 値が逆なのでMAXの値から引く
  r_val = LED_MAX - r_val;
  g_val = LED_MAX - g_val;
  b_val = LED_MAX - b_val;

  // 光量を調節して光らせる
  ledOff();
  analogWrite(_anode_pin, val);
  analogWrite(_r_pin, r_val);
  analogWrite(_g_pin, g_val);
  analogWrite(_b_pin, b_val);
}

/**
 * フルカラーLEDを消す関数
 *
 * フルカラーLEDを消灯する。
 */
void RPicoBoy::ledOff() {
  analogWrite(_anode_pin, 0);
  analogWrite(_r_pin, LED_MAX);
  analogWrite(_g_pin, LED_MAX);
  analogWrite(_b_pin, LED_MAX);
}

/**
 * ボタンのセットアップをする関数
 *
 * 各種ボタンを使用できるようにする。
 */
void RPicoBoy::buttonSetup() {
  pinMode(BUTTON_A_PIN, INPUT_PULLUP);
  pinMode(BUTTON_B_PIN, INPUT_PULLUP);
  pinMode(BUTTON_UP_PIN, INPUT_PULLUP);
  pinMode(BUTTON_LEFT_PIN, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT_PIN, INPUT_PULLUP);
  pinMode(BUTTON_DOWN_PIN, INPUT_PULLUP);
}

/**
 * ボタンが押されているかの状態を取得する関数
 *
 * 各種ボタンの状態を配列で取得する。
 *
 * @param[out] buttonArray [A, B, UP, RIGHT, LEFT, DOWN, state]の順番で押されていればtrue/押されていなければfalse
 */
void RPicoBoy::getButtons(bool *buttonArray) {
  bool button_state = false;
  // ボタン判定
  if (digitalRead(BUTTON_A_PIN) == 0) {
    buttonArray[BTN_A] = true;
    button_state = true;
  }
  if (digitalRead(BUTTON_B_PIN) == 0) {
    buttonArray[BTN_B] = true;
    button_state = true;
  }
  if (digitalRead(BUTTON_UP_PIN) == 0) {
    buttonArray[BTN_UP] = true;
    button_state = true;
  }
  if (digitalRead(BUTTON_RIGHT_PIN) == 0) {
    buttonArray[BTN_RIGHT] = true;
    button_state = true;
  }
  if (digitalRead(BUTTON_LEFT_PIN) == 0) {
    buttonArray[BTN_LEFT] = true;
    button_state = true;
  }
  if (digitalRead(BUTTON_DOWN_PIN) == 0) {
    buttonArray[BTN_DOWN] = true;
    button_state = true;
  }
  buttonArray[BTN_STATE] = button_state;
}

/**
 * ボタンの状態をリセットする関数
 *
 * ボタンの状態をすべて押されていない状態(false)にする。
 */
void RPicoBoy::resetButton() {
  for (int i = 0; i < BTN_MAX; i++) {
    _buttons[i] = false;
  }
}

/**
 * ボタンの状態を更新する関数
 *
 * ボタンの状態を更新する。
 */
void RPicoBoy::updateButton() {
  resetButton();
  getButtons(_buttons);
}

/**
 * ボタンの状態を取得する関数
 *
 * 引数の番号のボタンの状態を返す。
 * ボタンの範囲外の値が引数に設定されていた場合はNULLを返す。
 *
 * @param[in] btn_number BTN_A, BTN_B, BTN_UP, BTN_RIGHT, BTN_LEFT, BTN_DOWN, BTN_STATEのいずれかを設定
 */
bool RPicoBoy::getButton(int btn_number) {
  if (btn_number  < 0 || BTN_MAX <= btn_number) {
    return NULL;
  }
  return _buttons[btn_number];
}

/**
 * 上下左右のキーがすべて押されているか判定する関数
 *
 * BTN_UP, BTN_RIGHT, BTN_LEFT, BTN_DOWNのすべてのボタンが押されているかを判定する。
 *
 * @return bool 全て押されていた場合はtrue/そうでない場合はfalse
 */
bool RPicoBoy::isCrossAllButton() {
  if (_buttons[BTN_UP] && _buttons[BTN_DOWN] && _buttons[BTN_RIGHT] && _buttons[BTN_LEFT]) {
    return true;
  }
  return false;
}

/**
 * ブザーをセットアップする関数
 *
 * ブザーを使用できるようにする。
 */
void RPicoBoy::buzzerSetup() {
  _buzzer_pin = BUZZER_PIN;
  pinMode(_buzzer_pin, OUTPUT);
}

/**
 * ブザーを鳴らす関数
 *
 * 引数の周波数でブザーを鳴らす。
 * 音を鳴らす長さはsetOneSoundDelay関数で設定した値。
 *
 * @param[in] freq 周波数
 */
void RPicoBoy::buzzerCall(int freq) {
  tone(_buzzer_pin, freq);
  oneSoundDelay();
  noTone(_buzzer_pin);
}

/**
 * 任意の時間ブザーを鳴らす関数
 *
 * 引数の周波数と継続時間でブザーを鳴らす。
 *
 * @param[in] freq 周波数
 * @param[in] delay_time 継続時間(milliseconds)
 */
void RPicoBoy::buzzerCallDelay(int freq, int delay_time) {
  tone(_buzzer_pin, freq);
  delay(delay_time);
  noTone(_buzzer_pin);
}

/**
 * EEPROMに書き込みを行う関数
 *
 * EEPROMに書き込みを行う。
 *
 * @param[in] eeaddress アドレス番地(0から32766)
 * @param[in] data 書き込みデータ(1byte分のみ)
 */
void RPicoBoy::writeEEPROM(unsigned int eeaddress, byte data) {
  // 最大番地より大きい場合は何もしない
  if (eeaddress > MAX_EEADDRESS) { return; }

  // 番地を指定してデータ書き込み
  Wire1.beginTransmission(EEPROM_ADDRESS);
  Wire1.write((int)(eeaddress >> 8));   // 番地のHighByte
  Wire1.write((int)(eeaddress & 0xFF)); // 番地のLowByte
  Wire1.write(data);
  Wire1.endTransmission();
 
  delay(5);
}

/**
 * EEPROMの読み込みを行う関数
 *
 * EEPROMの読み込みを行う。
 *
 * @param[in] eeaddress アドレス番地(0から32766)
 * @return byte 引数の番地に記録されている1byteデータ。取得できなかった場合は0xFFを返す。
 */
byte RPicoBoy::readEEPROM(unsigned int eeaddress) {
  byte rdata = 0xFF;

  // 番地指定
  Wire1.beginTransmission(EEPROM_ADDRESS);
  Wire1.write((int)(eeaddress >> 8));   // 番地のHighByte
  Wire1.write((int)(eeaddress & 0xFF)); // 番地のLowByte
  Wire1.endTransmission();

  // データ取得
  Wire1.requestFrom(EEPROM_ADDRESS, 1); 
  if (Wire1.available()) { rdata = Wire1.read(); }
  return rdata;
}

#endif // RPicoBoy_h