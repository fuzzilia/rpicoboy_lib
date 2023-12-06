#include "RPicoBoy.h"

/**
 * スタートメニューのクラス
 */

long long unsigned int LOGO[15] = {0x40000000,0xa0000000,0x5ffffff8,0x50000008,0x56002a08,0x54005d08,0x3eadaac8,0x14a4aa68,0x14a92aa8,0x144daae8,0x10000018,0x1ffffffe,0x2,0x5,0x2};


class StartMenu {
  public:
    StartMenu(RPicoBoy *obj, int x, int y, int low_diff, int menu_max, String *menu_array);
    void setup0();
    void setup1();
    int getDecision();
    void showLogo();
    void run0();
    void run1();
    void calcCursorPosition();

  private:
    RPicoBoy *_game_obj;
    int _menu_cursor;
    int _old_cursor;
    int _dicision;
    int _menu_min;
    int _menu_x = 32;
    int _menu_y = 6;
    int _low_diff;
    int _menu_max;
    String *_menu_array;
    bool _push_btn_a = true;

    void callStartSE();
    void callCursorSE();
};

// コンストラクタ
StartMenu::StartMenu(RPicoBoy *obj, int x, int y, int low_diff, int menu_max, String *menu_array) {
  _game_obj = obj;
  _menu_x = x;
  _menu_y = y;
  _low_diff = low_diff;
  _menu_min = 1;
  _menu_max = menu_max;
  _menu_array = menu_array;
}

void StartMenu::setup0() {
  _game_obj->setFpsDelay(24);
  _game_obj->setOneSoundDelay(150);
  _menu_cursor = 1;
  _old_cursor  = 1;
  _dicision = 0;

  delay(100);
  _game_obj->resetButton(); // ボタンの状態をクリア
}

void StartMenu::setup1() {
  // 何もしない
}

// 決定したメニューの番号を取得する関数
int StartMenu::getDecision() {
  return _dicision;
}

// 上から降ってくるロゴを表示する関数
void StartMenu::showLogo() {
  int x = 32;
  int y = -30;

  // 表示
  for (int i = 0; i < 48; i++) {
    _game_obj->clearDisplay();
    _game_obj->drawImage64bitBinExpansion(x, y+i, 32, 15, 32, LOGO, NULL, 2);
    _game_obj->display();
    delay(50);
  }

  // 止まったらSEを鳴らす
  callStartSE();

  _game_obj->clearDisplay(); // 画面をクリア
  _game_obj->display(); // 表示

  delay(100);
}

// スタートSEを鳴らす関数
void StartMenu::callStartSE() {
  int sound_delay = 0;
  _game_obj->getSoundDelay(&sound_delay);
  _game_obj->buzzerCall(1047); // ド
  _game_obj->buzzerCallDelay(4186, sound_delay*3); // ド
}

// メニューを表示させるメイン関数
void StartMenu::run0() {
  _game_obj->ledOff();       // LED消灯
  _game_obj->startFps();     // fpsの待ち時間用
  _game_obj->clearDisplay(); // 画面をクリア

  // ボタンの状態更新
  _game_obj->updateButton();
  // カーソル位置を計算
  calcCursorPosition();

  // カーソル表示
  if (_menu_cursor == _menu_min) {
    _game_obj->setCursor(_menu_x-20, _menu_y);
    _game_obj->print("->");
  } else if (_menu_cursor == _menu_max) {
    _game_obj->setCursor(_menu_x-20, _menu_y+_low_diff*(_menu_max-1));
    _game_obj->print("->");
  } else {
    _game_obj->setCursor(_menu_x-20, _menu_y+_low_diff*(_menu_cursor-1));
    _game_obj->print("->");
  }

  // メニュー表示
  for (int i = 0; i < _menu_max; i++) {
    _game_obj->setCursor(_menu_x, _menu_y + _low_diff*i);
    _game_obj->print(_menu_array[i]);
  }
  _game_obj->display(); // 表示

  // 選択しているものが変更されていればSEを鳴らす
  if (_old_cursor != _menu_cursor) {
    callCursorSE();
  }
  _old_cursor = _menu_cursor;

  _game_obj->fpsDelay();
}

void StartMenu::run1() {
  // 何もしない
}

// カーソル位置を計算する関数
void StartMenu::calcCursorPosition() {
  if (_game_obj->getButton(BTN_A) && !_push_btn_a) {
    // A
    _dicision = _menu_cursor;
  } else if (_game_obj->getButton(BTN_UP)) {
    // UP
    _menu_cursor--;
    _menu_cursor = (_menu_cursor < _menu_min) ? _menu_min : _menu_cursor;
  } else if (_game_obj->getButton(BTN_DOWN)) {
    // DOWN
    _menu_cursor++;
    _menu_cursor = (_menu_cursor > _menu_max) ? _menu_max : _menu_cursor;
  }

  // ボタンの状態を保存
  _push_btn_a = _game_obj->getButton(BTN_A);
}

// カーソル移動でのSEを鳴らす関数
void StartMenu::callCursorSE() {
  _game_obj->buzzerCallDelay(3000, 100);
}