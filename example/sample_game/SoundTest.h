#include "RPicoBoy.h"

/**
 * サウンドテストを行うクラス
 */

class SoundTest {
  public:
    SoundTest(RPicoBoy *obj);
    void setup0();
    void run0();
    void run1();

  private:
    static const int THOUSAND_DIGIT = 0;
    static const int HUNDRED_DIGIT  = 1;
    static const int TEN_DIGIT      = 2;
    static const int ONE_DIGIT      = 3;

    RPicoBoy *_game_obj;
    int _thousand_num;
    int _hundred_num;
    int _ten_num;
    int _one_num;
    int _select_digits;
    bool _is_playing;
    bool _push_btn_a;

    void updateDigits();
    void incrementDigit();
    void decrementDigit();

    void showSoundDigits();
    void calcInputDigit();
};

// コンストラクタ
SoundTest::SoundTest(RPicoBoy *obj) {
  _game_obj = obj;
}

void SoundTest::setup0() {
  _game_obj->setFpsDelay(24);
  _game_obj->setOneSoundDelay(300);
  _game_obj->setTextSize(2);
  delay(100);

  _thousand_num = 0;
  _hundred_num = 0;
  _ten_num = 0;
  _one_num = 0;
  _select_digits = THOUSAND_DIGIT;
  _is_playing = false;
  _game_obj->clearDisplay(); // 画面をクリア
  _game_obj->resetButton(); // ボタンの状態をクリア
  _push_btn_a = true;
}

void SoundTest::run0() {
  _game_obj->startFps();     // fpsの待ち時間用
  _game_obj->clearDisplay(); // 画面クリア
  _game_obj->updateButton(); // ボタンの状態更新

  // メニューに戻る判定
  if (_game_obj->isCrossAllButton()) {
    _is_playing = false;
    _game_obj->setMenuSelect(0);
    _game_obj->setTextSize(1);
    _game_obj->clearDisplay(); // 画面をクリア
    _game_obj->display(); // 表示
  }

  if (_game_obj->getButton(BTN_A) && !_push_btn_a) {
    // Aボタンの場合は再生
    _is_playing = true;
  } else if (_game_obj->getButton(BTN_B)) {
    // Bボタンの場合は停止
    _is_playing = false;
  } else if (_game_obj->getButton(BTN_STATE)) {
    // それ以外のボタンの場合は値を更新
    updateDigits();
  }

  // 画面表示
  showSoundDigits();

  // ボタンの状態を保存
  _push_btn_a = _game_obj->getButton(BTN_A);

  _game_obj->display(); // 表示
  _game_obj->fpsDelay();
}

void SoundTest::run1() {
  if (_is_playing) {
    // 音を作成し鳴らす
    int freq_num = _thousand_num * 1000 + _hundred_num * 100 + _ten_num * 10 + _one_num;
    _game_obj->buzzerCall(freq_num);
  }
}

// 桁数の部分を更新する関数
void SoundTest::updateDigits() {
  if (_game_obj->getButton(BTN_UP)) {
    // UPの場合は値を増加
    incrementDigit();
  } else if (_game_obj->getButton(BTN_DOWN)) {
    // DOWNの場合は値を減少
    decrementDigit();
  } else if (_game_obj->getButton(BTN_RIGHT)) {
    // RIGHTの場合は右に移動
    if (_select_digits < ONE_DIGIT) { _select_digits++; }
  } else if (_game_obj->getButton(BTN_LEFT)) {
    // LEFTの場合は左に移動
    if (_select_digits > THOUSAND_DIGIT) { _select_digits--; }
  }
}

// 対象桁数を増加させる関数
void SoundTest::incrementDigit() {
  if (_select_digits == THOUSAND_DIGIT && _thousand_num < 9) {
    // 千の桁の場合
    _thousand_num++;
  } else if (_select_digits == HUNDRED_DIGIT && _hundred_num < 9) {
    // 百の桁の場合
    _hundred_num++;
  } else if (_select_digits == TEN_DIGIT && _ten_num < 9) {
    // 十の桁の場合
    _ten_num++;
  } else if (_select_digits == ONE_DIGIT && _one_num < 9) {
    // 一の桁の場合
    _one_num++;
  }
}

// 対象桁数を減少させる関数
void SoundTest::decrementDigit() {
  if (_select_digits == THOUSAND_DIGIT && _thousand_num > 0) {
    // 千の桁の場合
    _thousand_num--;
  } else if (_select_digits == HUNDRED_DIGIT && _hundred_num > 0) {
    // 百の桁の場合
    _hundred_num--;
  } else if (_select_digits == TEN_DIGIT && _ten_num > 0) {
    // 十の桁の場合
    _ten_num--;
  } else if (_select_digits == ONE_DIGIT && _one_num > 0) {
    // 一の桁の場合
    _one_num--;
  }
}

// 画面表示をする関数
void SoundTest::showSoundDigits() {
  // 周波数部分の表示
  _game_obj->setCursor(0, SCREEN_HEIGHT / 2 - 32);
  _game_obj->print("freq: ");
  _game_obj->print(String(_thousand_num));
  _game_obj->print(String(_hundred_num));
  _game_obj->print(String(_ten_num));
  _game_obj->println(String(_one_num));

  // 入力桁数部分の表示
  calcInputDigit();

  // 操作方法部分の表示
  _game_obj->println("  Play: A");
  _game_obj->println("  Stop: B");
}

// 入力桁数部分を計算して表示させる関数
void SoundTest::calcInputDigit() {
  String display_str = "      -";

  // 現在の桁数位置分だけスペースを追加
  for (int i = 0; i < _select_digits; i++) {
    display_str = " " + display_str;
  }

  _game_obj->println(display_str);
}
