#include "RPicoBoy.h"
#include "MovieData.h"


/**
 * 動画テストを行うクラス
 */

class MovieTest {
  public:
    MovieTest(RPicoBoy *obj);
    void setup0();
    void run0();
    void run1();

  private:
    RPicoBoy *_game_obj;
    unsigned int _frame_count;
};

MovieTest::MovieTest(RPicoBoy *obj) {
  _game_obj = obj;
}

void MovieTest::setup0() {
  _game_obj->setFpsDelay(FRAME_RATE);
  _game_obj->setOneSoundDelay(150);

  _frame_count = MAX_FRAME;

  _game_obj->clearDisplay(); // 画面クリア

  delay(100);
  _game_obj->resetButton(); // ボタンの状態をクリア
}

void MovieTest::run0() {
  _game_obj->startFps();     // fpsの待ち時間用
  _game_obj->clearDisplay(); // 画面クリア
  _game_obj->updateButton(); // ボタンの状態更新

  // 画面表示
  if (_frame_count >= MAX_FRAME) {
    _frame_count = 0;
  }

  if (MOVIE_MODE == MODE_64BIT) {
    _game_obj->drawImage64bitBinExpansionConst(0, 0, MOVIE_WIDTH, MOVIE_HEIGHT, MOVIE_WIDTH, MOVIE_ARRAY[_frame_count], NULL, 2);
  } else {
    _game_obj->drawArrayImage90RotConst(MOVIE_X_POS, 0, MOVIE_WIDTH, MOVIE_HEIGHT, MOVIE_ARRAY[_frame_count]);
  }
  _frame_count++;

  // メニューに戻る判定
  if (_game_obj->isCrossAllButton()) {
    // _is_playing = false;
    _game_obj->setMenuSelect(0);
    _game_obj->setTextSize(1);
    _game_obj->clearDisplay(); // 画面をクリア
    _game_obj->display(); // 表示
  }

  _game_obj->display(); // 表示
  _game_obj->fpsDelay();
}

void MovieTest::run1() {

}