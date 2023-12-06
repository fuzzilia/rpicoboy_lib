#include "RPicoBoy.h"

/**
 * フルカラーLEDテストを行うクラス
 */

class LedTest {
  public:
    LedTest(RPicoBoy *obj);
    void setup0();
    void run0();
    void run1();

  private:
    static const int VAL_ARRAY_MAX = 12;

    RPicoBoy *_game_obj;
    int _r;
    int _g;
    int _b;
    int _val;
    bool _is_lighting;
    int _select_digits;
    int _val_array[VAL_ARRAY_MAX] = {0,0,0, 0,0,0, 0,0,0, 0,0,0};
    bool _push_btn_a;

    void initValArray();
    void updateDigits();
    void incrementDigit();
    void decrementDigit();
    void showLedDigits();
    void calcRgbv();
    void calcInputDigit();
    void callCursorSE();
};

// コンストラクタ
LedTest::LedTest(RPicoBoy *obj) {
  _game_obj = obj;
}

// セットアップ関数
void LedTest::setup0() {
  _game_obj->setFpsDelay(24);
  _game_obj->setOneSoundDelay(300);
  _game_obj->setTextSize(1);
  delay(100);

  initValArray();
  _r = 0;
  _g = 0;
  _b = 0;
  _val = 0;
  _is_lighting = false;
  _select_digits = 0;

  _game_obj->clearDisplay(); // 画面をクリア
  _game_obj->resetButton();  // ボタンの状態をクリア
  _push_btn_a = true;
}

void LedTest::run0() {
  _game_obj->startFps();     // fpsの待ち時間用
  _game_obj->clearDisplay(); // 画面クリア
  _game_obj->updateButton(); // ボタンの状態更新

  // メニューに戻る判定
  if (_game_obj->isCrossAllButton()) {
    _is_lighting = false;
    _game_obj->ledOff();  // LED消灯
    _game_obj->setMenuSelect(0);
    _game_obj->setTextSize(1);
    _game_obj->clearDisplay(); // 画面をクリア
    _game_obj->display(); // 表示
  }

  if (_game_obj->getButton(BTN_A) && !_push_btn_a) {
    // Aボタンの場合は点灯
    _is_lighting = true;
    _game_obj->ledOn(_r, _g, _b, _val);
    callCursorSE();
  } else if (_game_obj->getButton(BTN_B)) {
    // Bボタンの場合は消灯
    _is_lighting = false;
    _game_obj->ledOff();
    callCursorSE();
  } else if (_game_obj->getButton(BTN_STATE)) {
    // それ以外のボタンの場合は値を更新
    updateDigits();
    callCursorSE();
  }

  // 画面表示
  showLedDigits();

  // ボタンの状態を保存
  _push_btn_a = _game_obj->getButton(BTN_A);

  _game_obj->display(); // 表示
  _game_obj->fpsDelay();
}

void LedTest::run1() {
  // if (_is_lighting) {
  //   _game_obj->ledOn(_r, _g, _b, _val);
  // } else {
  //   _game_obj->ledOff();
  // }
}

// 内部配列を初期化する関数
void LedTest::initValArray() {
  for (int i = 0; i < VAL_ARRAY_MAX; i++) {
    _val_array[i] = 0;
  } 
}

// 桁数の部分を更新する関数
void LedTest::updateDigits() {
  if (_game_obj->getButton(BTN_UP)) {
    // UPの場合は値を増加
    incrementDigit();
  } else if (_game_obj->getButton(BTN_DOWN)) {
    // DOWNの場合は値を減少
    decrementDigit();
  } else if (_game_obj->getButton(BTN_RIGHT)) {
    // RIGHTの場合は次に移動
    if (_select_digits < VAL_ARRAY_MAX - 1) { _select_digits++; }
  } else if (_game_obj->getButton(BTN_LEFT)) {
    // LEFTの場合は前に移動
    if (_select_digits > 0) { _select_digits--; }
  }
}

// 対象桁数を増加させる関数
void LedTest::incrementDigit() {
  _val_array[_select_digits]++;

  if (_val_array[_select_digits] > 9) {
    _val_array[_select_digits] = 9;
  }

  calcRgbv();
}

// 対象桁数を減少させる関数
void LedTest::decrementDigit() {
  _val_array[_select_digits]--;

  if (_val_array[_select_digits] < 0) {
    _val_array[_select_digits] = 0;
  }

  calcRgbv();
}

// RGBとValの値を計算する関数
void LedTest::calcRgbv() {
  // r
  _r = _val_array[0] * 100 + _val_array[1] * 10 + _val_array[2];
  if (_r > LED_MAX) {
    _r = LED_MAX;
    _val_array[0] = String(LED_MAX).charAt(0) - '0';
    _val_array[1] = String(LED_MAX).charAt(1) - '0';
    _val_array[2] = String(LED_MAX).charAt(2) - '0';
  }
  // g
  _g = _val_array[3] * 100 + _val_array[4] * 10 + _val_array[5];
  if (_g > LED_MAX) {
    _g = LED_MAX;
    _val_array[3] = String(LED_MAX).charAt(0) - '0';
    _val_array[4] = String(LED_MAX).charAt(1) - '0';
    _val_array[5] = String(LED_MAX).charAt(2) - '0';
  }
  // b
  _b = _val_array[6] * 100 + _val_array[7] * 10 + _val_array[8];
  if (_b > LED_MAX) {
    _b = LED_MAX;
    _val_array[6] = String(LED_MAX).charAt(0) - '0';
    _val_array[7] = String(LED_MAX).charAt(1) - '0';
    _val_array[8] = String(LED_MAX).charAt(2) - '0';
  }
  // val
  _val = _val_array[9] * 100 + _val_array[10] * 10 + _val_array[11];
  if (_val > LUX_MAX) {
    _val = LUX_MAX;
    _val_array[9]  = String(LUX_MAX).charAt(0) - '0';
    _val_array[10] = String(LUX_MAX).charAt(1) - '0';
    _val_array[11] = String(LUX_MAX).charAt(2) - '0';
  }
}

// 画面に表示させる関数
void LedTest::showLedDigits() {
  _game_obj->setCursor(0, 0);
  _game_obj->print("  r: ");
  _game_obj->print(String(_val_array[0]));
  _game_obj->print(String(_val_array[1]));
  _game_obj->println(String(_val_array[2]));
  _game_obj->println("");

  _game_obj->print("  g: ");
  _game_obj->print(String(_val_array[3]));
  _game_obj->print(String(_val_array[4]));
  _game_obj->print(String(_val_array[5]));
  _game_obj->println("   LedOn:  A");
  _game_obj->println("");

  _game_obj->print("  b: ");
  _game_obj->print(String(_val_array[6]));
  _game_obj->print(String(_val_array[7]));
  _game_obj->print(String(_val_array[8]));
  _game_obj->println("   LedOff: B");
  _game_obj->println("");

  _game_obj->print("val: ");
  _game_obj->print(String(_val_array[9]));
  _game_obj->print(String(_val_array[10]));
  _game_obj->print(String(_val_array[11]));

  // 入力カーソル位置を計算
  calcInputDigit();
}

// 入力桁数部分を計算して表示させる関数
void LedTest::calcInputDigit() {
  int space_count = 0;
  int row_count   = -1;

  // 位置を計算
  for (int i = 0; i <= _select_digits; i++) {
    if (i % 3 == 0) {
      row_count++;
      space_count = 0;
    } else {
      space_count++;
    }
  }

  // 表示する文字列を計算
  String display_str = "     -";
  for (int j = 0; j < space_count; j++) {
    display_str = " " + display_str;
  }

  _game_obj->setCursor(0, row_count * 16 + 8);
  _game_obj->print(display_str);
}

// カーソル移動でのSEを鳴らす関数
void LedTest::callCursorSE() {
  _game_obj->buzzerCallDelay(3000, 100);
}