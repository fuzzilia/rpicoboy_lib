#include "RPicoBoy.h"

/**
 * QRコードを表示するクラス
 */
const int QR_WIDTH  = 31;
const int QR_HETGHT = 31;
long long unsigned int QRCODE[QR_WIDTH] = {0x0,0x3f9dccfe,0x20b76682,0x2e9e48ba,0x2e9a86ba,0x2eaffcba,0x209cec82,0x3faaaafe,0x1f5400,0x2a855624,0x1b1b2392,0x25ca0a0e,0x1c6b3e64,0x3ff371d6,0x15132392,0x7ec3116,0x1b299d74,0x36bb3fd6,0x1620a39a,0x24b49066,0x1a6f3a14,0x2ce0f3e0,0x283e2e,0x3f991eb6,0x208c1230,0x2eb633e0,0x2e843e2e,0x2eba0c72,0x208f5764,0x3facf3e6,0x0};

class QRTest {
  public:
    QRTest(RPicoBoy *obj);
    void setup0();
    void run0();
    void run1();

  private:
    RPicoBoy *_game_obj;
    unsigned int _frame_count;
};

QRTest::QRTest(RPicoBoy *obj) {
  _game_obj = obj;
}

void QRTest::setup0() {
  _game_obj->setFpsDelay(12);
  _game_obj->setOneSoundDelay(150);
  delay(100);

  _game_obj->clearDisplay(); // 画面クリア

  // QR Code表示
  _game_obj->drawImage64bitBinExpansion(32, 1, QR_WIDTH, QR_HETGHT, QR_WIDTH, QRCODE, NULL, 2);

  // ドット反転
  for (int i = 0; i < SCREEN_WIDTH; i++) {
    for (int j = 0; j < SCREEN_HEIGHT; j++) {
      _game_obj->dotInversion(i, j);
    }
  }

  _game_obj->display(); // 表示
  _game_obj->resetButton(); // ボタンの状態をクリア
}

void QRTest::run0() {
  _game_obj->startFps();     // fpsの待ち時間用
  _game_obj->updateButton(); // ボタンの状態更新

  // メニューに戻る判定
  if (_game_obj->isCrossAllButton()) {
    _game_obj->setMenuSelect(0);
    _game_obj->setTextSize(1);
    _game_obj->clearDisplay(); // 画面をクリア
    _game_obj->display(); // 表示
  }

  _game_obj->fpsDelay();
}

void QRTest::run1() {

}