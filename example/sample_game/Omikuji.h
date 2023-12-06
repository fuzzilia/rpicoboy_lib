#include "RPicoBoy.h"

/**
 * おみくじ用クラス
 */

// 吉
long long unsigned int KICHI_DOT[32] = {0x0,0x3c000,0x7e000,0x7e000,0x7e000,0x7e000,0x7e000,0x1ffffff8,0x3ffffffc,0x3ffffffc,0x1ffffff8,0x7e000,0x7e000,0xff000,0x7ffe00,0xffff00,0xffff00,0x7ffe00,0x0,0x7ffe00,0x1ffff80,0x3ffffc0,0x3ffffc0,0x3e007c0,0x3c003c0,0x3c003c0,0x3e007c0,0x3ffffc0,0x3ffffc0,0x1ffff80,0x7ffe00,0x0};
// 大
long long unsigned int DAI_DOT[32]   = {0x0,0x3c000,0x7e000,0x7e000,0x7e000,0x7e000,0x7e000,0x3ffffffc,0x7ffffffe,0x7ffffffe,0x7ffffffe,0x3ffffffc,0x7e000,0xff000,0xff000,0x1ff800,0x1ff800,0x3ffc00,0x3ffc00,0x7ffe00,0x7ffe00,0xfe7f00,0x1fc3f80,0x3fc3fc0,0x7f81fe0,0xff00ff0,0x1fe007f8,0x3fc003fc,0x7fc003fe,0x7f8001fe,0x3f0000fc,0x0};
// 中
long long unsigned int CHU_DOT[32]   = {0x0,0x3c000,0x7e000,0x7e000,0x7e000,0x7e000,0x7e000,0x3ffffffc,0x7ffffffe,0x7ffffffe,0x7ffffffe,0x7ffffffe,0x7c07e03e,0x7c07e03e,0x7c07e03e,0x7c07e03e,0x7c07e03e,0x7c07e03e,0x7c07e03e,0x7c07e03e,0x7ffffffe,0x7ffffffe,0x7ffffffe,0x7ffffffe,0x3ffffffc,0x7e000,0x7e000,0x7e000,0x7e000,0x7e000,0x3c000,0x0};
// 小
long long unsigned int SYO_DOT[32]   = {0x0,0x3c000,0x7e000,0x7e000,0x7e000,0x7e000,0x7e000,0x7e000,0x7e000,0xc7e300,0x1e7e780,0x1e7e780,0x3e7e7c0,0x3e7e7c0,0x7c7e3e0,0xfc7e3f0,0x1f87e1f8,0x3f87e1fc,0x7f07e0fe,0x7e07e07e,0x7c07e03e,0x7807e01e,0x3007e00c,0x7e000,0x7e000,0x7e000,0x7e000,0x7e000,0x7e000,0x7e000,0x3c000,0x0};
// 末
long long unsigned int SUE_DOT[32]   = {0x0,0x3c000,0x7e000,0x7e000,0x7e000,0x7e000,0x7e000,0x3ffffffc,0x7ffffffe,0x7ffffffe,0x3ffffffc,0x7e000,0x7e000,0xff000,0x3ffffc0,0x7ffffe0,0x7ffffe0,0x3ffffc0,0x1ff800,0x3ffc00,0x7ffe00,0xffff00,0x1ffff80,0x3f7efc0,0x7e7e7e0,0xfc7e3f0,0x1f87e1f8,0x3f07e0fc,0x7e07e07e,0x7c07e03e,0x3803c01c,0x0};
// 凶
long long unsigned int KYO_DOT[32]   = {0x0,0xc00,0x1e00,0x1f00,0x1f00,0x381f00,0x7c1f00,0x387e3f1c,0x7c7fff3e,0x7c3fff3e,0x7c1ffe3e,0x7c0ffe3e,0x7c07fc3e,0x7c03fc3e,0x7c07fc3e,0x7c07fe3e,0x7c0ffe3e,0x7c1fff3e,0x7c3fdf3e,0x7c7f8fbe,0x7cff07be,0x7dfc07be,0x7df803be,0x7df0033e,0x7c00003e,0x7c00003e,0x7ffffffe,0x7ffffffe,0x7ffffffe,0x7ffffffe,0x3ffffffc,0x0};


class Omikuji {
  public:
    Omikuji(RPicoBoy *obj);
    void setup0();
    void run0();
    void setup1();
    void run1();

  private:
    static const int DAIKICHI = 0;
    static const int CHUKICHI = 1;
    static const int SYOKICHI = 2;
    static const int KICHI    = 3;
    static const int SUEKICHI = 4;
    static const int KYO      = 5;
    static const int DAIKYO   = 6;

    RPicoBoy *_game_obj;
    bool _is_sound_playing;
    bool _is_push;
    long _show_number;
    bool _push_btn;

    void showFortune();
    void callDaikichi();
    void callSokosoko();
    void callHazure();
};

// コンストラクタ
Omikuji::Omikuji(RPicoBoy *obj) {
  _game_obj = obj;
  _is_sound_playing = false;
}

void Omikuji::setup0() {
  randomSeed(analogRead(0));
  _game_obj->setFpsDelay(60);
  _game_obj->setOneSoundDelay(150);
  delay(100);

  _show_number = 0;
  _is_push = false;
  _game_obj->clearDisplay(); // 画面をクリア
  _game_obj->resetButton(); // ボタンの状態をクリア
  _push_btn = true;
}

void Omikuji::setup1() {
  _is_sound_playing = false;
}

// メイン処理ループ
void Omikuji::run0() {
  _game_obj->startFps();     // fpsの待ち時間用
  // ボタンの状態更新
  _game_obj->updateButton();

  // メニューに戻る判定
  if (_game_obj->isCrossAllButton()) {
    _is_sound_playing = false;
    _game_obj->ledOff();  // LED消灯
    _game_obj->setMenuSelect(0);
    _game_obj->clearDisplay(); // 画面をクリア
    _game_obj->display(); // 表示
  }

  if (!_is_sound_playing) {
    _game_obj->clearDisplay(); // 画面をクリア

    _show_number = random(DAIKICHI, DAIKYO+1); // 0から7の乱数を生成

    // 画面に書き込み
    showFortune();

    _game_obj->display(); // 表示
  }

  // なんらかのボタンが押されていた場合
  if (_game_obj->getButton(BTN_STATE) && !_push_btn) {
    if (!_is_push) {
      _is_sound_playing = true;
    }
    _is_push = true;
  } else {
    _is_push = false;
  }

  // ボタンの状態を更新
  _push_btn = _game_obj->getButton(BTN_STATE);

  _game_obj->fpsDelay();
}

// 音関係
void Omikuji::run1() {
  _game_obj->ledOff();

  if (_is_sound_playing) {
    int r = random(0, LED_MAX+1); // 0から255の乱数を生成
    int g = random(0, LED_MAX+1); // 0から255の乱数を生成
    int b = random(0, LED_MAX+1); // 0から255の乱数を生成
    int val = 100;

    switch (_show_number) {
      case DAIKICHI:
        // 大吉
        _game_obj->ledOn(r, g, b, val);
        delay(10);
        callDaikichi();
        _is_sound_playing = false;        
        break;
      case CHUKICHI:
        // 中吉
        _game_obj->ledOn(r, g, b, val);
        delay(10);
        callSokosoko();
        _is_sound_playing = false;
        break;
      case SYOKICHI:
        // 小吉
        _game_obj->ledOn(r, g, b, val);
        delay(10);
        callSokosoko();
        _is_sound_playing = false;
        break;
      default:
        // 上記以外
        callHazure();
        _is_sound_playing = false;
        break;
    }
  }
}

// 運勢を表示する関数
void Omikuji::showFortune() {
  short rate = 2;
  switch (_show_number) {
    case DAIKICHI:
      // 大吉
      _game_obj->drawImage64bitBinExpansion(0, 0, 32, 32, 32, DAI_DOT, NULL, rate);
      _game_obj->drawImage64bitBinExpansion(65, 0, 32, 32, 32, KICHI_DOT, NULL, rate);
      break;
    case CHUKICHI:
      // 中吉
      _game_obj->drawImage64bitBinExpansion(0, 0, 32, 32, 32, CHU_DOT, NULL, rate);
      _game_obj->drawImage64bitBinExpansion(65, 0, 32, 32, 32, KICHI_DOT, NULL, rate);
      break;
    case SYOKICHI:
      // 小吉
      _game_obj->drawImage64bitBinExpansion(0, 0, 32, 32, 32, SYO_DOT, NULL, rate);
      _game_obj->drawImage64bitBinExpansion(65, 0, 32, 32, 32, KICHI_DOT, NULL, rate);
      break;
    case KICHI:
      // 吉
      _game_obj->drawImage64bitBinExpansion(32, 0, 32, 32, 32, KICHI_DOT, NULL, rate);
      break;
    case SUEKICHI:
      // 末吉
      _game_obj->drawImage64bitBinExpansion(0, 0, 32, 32, 32, SUE_DOT, NULL, rate);
      _game_obj->drawImage64bitBinExpansion(65, 0, 32, 32, 32, KICHI_DOT, NULL, rate);
      break;
    case KYO:
      // 凶
      _game_obj->drawImage64bitBinExpansion(32, 0, 32, 32, 32, KICHI_DOT, NULL, rate);
      break;
    case DAIKYO:
      // 大凶
      _game_obj->drawImage64bitBinExpansion(0, 0, 32, 32, 32, DAI_DOT, NULL, rate);
      _game_obj->drawImage64bitBinExpansion(65, 0, 32, 32, 32, KYO_DOT, NULL, rate);
      break;
    default:
      // 無
      break;
  }
}

/**
 * 大吉の音を鳴らす関数
 */
void Omikuji::callDaikichi() {
  _game_obj->buzzerCall(1661); // ♯ソ
  _game_obj->buzzerCall(1760); // ラ
  _game_obj->buzzerCall(2637); // ミ
  _game_obj->buzzerCall(3322); // ♯ソ
  _game_obj->buzzerCall(2489); // ♯レ
  _game_obj->buzzerCall(2960); // ♯ファ
  _game_obj->buzzerCall(4186); // ド
  _game_obj->buzzerCall(3136); // ソ
}

/**
 * そこそこの音を鳴らす関数
 */
void Omikuji::callSokosoko() {
  int sound_delay = 0;
  _game_obj->getSoundDelay(&sound_delay);
  _game_obj->buzzerCallDelay(1047, sound_delay*2); // ド
  _game_obj->buzzerCallDelay(1319, sound_delay);   // ミ
  _game_obj->buzzerCallDelay(1047, sound_delay);   // ド
  _game_obj->buzzerCallDelay(1760, sound_delay*2); // ラ
}

/**
 * はずれの音を鳴らす関数
 */
void Omikuji::callHazure() {
  _game_obj->buzzerCall(3136); // ソ
  _game_obj->buzzerCall(1109); // ド#
  _game_obj->buzzerCall(1047); // ド
}
