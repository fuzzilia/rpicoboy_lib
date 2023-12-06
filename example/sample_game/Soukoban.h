#include "RPicoBoy.h"
#include "SoukobanData.h"

/**
* 倉庫番のクラス
*/
class Soukoban {
  public:
    Soukoban(RPicoBoy *obj);
    void setup0();
    void run0();
    void run1();

  private:
    RPicoBoy *_game_obj;

    // 以下倉庫番メニューに関わる部分
    int _menu_cursor;
    int _old_cursor;
    int _dicision;
    int _menu_min;
    int _menu_x;
    int _menu_y;
    int _low_diff;
    int _menu_max;
    int _save_stage_num;
    bool _push_btn_a;

    void soukoMenu();
    void calcCursorPosition();
    void callCursorSE();

    // 以下倉庫番ゲームにかかわる部分
    long long unsigned int *_chara_i;
    long long unsigned int *_chara_m;
    StageData _current_stage;
    int _load_stage_num;
    bool _is_map_clear;
    int _time_count;
    int _call_se_num;
    bool _push_cross_btn;
    bool _is_play_bgm;
    unsigned int _bgm_count;

    void soukoGame();
    void setupStage();
    void loadStageData(StageData map_data);
    void beforeStartStage();
    void moveChara();
    void inMapRange(int16_t *x, int16_t *y);
    bool isWall(int16_t x, int16_t y);
    void showNearbyMap();
    void showMiniMap();
    void judgeGoal();
    void clearStage();
    void judgeTimeUp();
    void timeUpStage();
    void allStageClear();
    void playClearSe();
    void playAllClear();
};

/**
 * コンストラクタ
 */
Soukoban::Soukoban(RPicoBoy *obj) {
  _game_obj = obj;

  _menu_x = 42;
  _menu_y = 32;
  _low_diff = 10;
}

/**
* メインのsetup関数
*/
void Soukoban::setup0() {
  // 準備
  _game_obj->setFpsDelay(SOUKOBAN_FPS);
  _game_obj->setOneSoundDelay(150);
  _game_obj->setTextSize(1);
  delay(100);

  _menu_cursor = 1;
  _old_cursor  = 1;
  _dicision = 0;

  // ステージのセーブデータを取得
  _save_stage_num = (int) _game_obj->readEEPROM(0);
  // セーブデータが違う値(ない)場合はセーブデータはないものとする
  if (0 < _save_stage_num && _save_stage_num < 10) {
    _menu_max = 2;
  } else {
    _menu_max = 1;
  }
  _menu_min = 1;

  // 初期値を設定
  _chara_i = CHARA_D;
  _chara_m = CHARA_D_M;
  _load_stage_num = 0;
  _is_map_clear = true;
  _time_count = 1;
  _call_se_num = SE_NONE;

  _game_obj->clearDisplay(); // 画面をクリア
  _game_obj->resetButton(); // ボタンの状態をクリア
  _push_btn_a = true;
  _push_cross_btn = true;
  _is_play_bgm = false;
  _bgm_count = 0;
}

/**
* メインループ関数
*/
void Soukoban::run0() {
  _game_obj->startFps();     // fpsの待ち時間用
  _game_obj->clearDisplay(); // 画面をクリア

  // ボタンの状態更新
  _game_obj->updateButton();

  // メニューに戻る判定
  if (_game_obj->isCrossAllButton()) {
    _is_play_bgm = false;
    _game_obj->setMenuSelect(0);
    _game_obj->clearDisplay(); // 画面をクリア
  }

  if (_dicision == 0) {
    /* メニューの場合の処理 */
    soukoMenu();
  } else {
    /* ゲームの場合の処理 */
    soukoGame();
  }

  _game_obj->display(); // 表示
  _game_obj->fpsDelay();
}

void Soukoban::run1() {
  if (_call_se_num == SE_WALL) {
    // 壁の場合のSE
    _game_obj->buzzerCallDelay(100, 150);
    _game_obj->buzzerCallDelay(0, 150);
    _call_se_num = SE_NONE;
    _bgm_count++;
  } else if (_is_play_bgm) {
    // BGMを鳴らす
    _game_obj->buzzerCallDelay(BGM_DATA[_bgm_count][0], BGM_DATA[_bgm_count][1]);
    _bgm_count++;
    if (_bgm_count >= BGM_MAX) _bgm_count = 0;
  }
}

/**
* 倉庫番のメニュー画面を表示する関数
*/
void Soukoban::soukoMenu() {
    // タイトルロゴを表示
  _game_obj->drawImage64bitBinExpansionConst(32, 0, 64, 20, 64, SOUKO_TITLE, NULL, 1);

  // メニュー表示
  _game_obj->setCursor(_menu_x, _menu_y);
  _game_obj->print("New Game");

  // セーブデータがない場合はLoadは表示しない
  if (_menu_max > 1) {
    _game_obj->setCursor(_menu_x, _menu_y + _low_diff);
    _game_obj->print("  Load");
  }

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

  // 選択しているものが変更されていればSEを鳴らす
  if (_old_cursor != _menu_cursor) {
    callCursorSE();
  }
  _old_cursor = _menu_cursor;
}

/**
* カーソル位置を計算する関数
*/
void Soukoban::calcCursorPosition() {
  if (_game_obj->getButton(BTN_A) && !_push_btn_a) {
    // A
    if (_menu_cursor > 1) {
      // 決定した時に「Load」なら保存されたステージ番号を設定
      _load_stage_num = _save_stage_num;
    } else {
      // 「New Game」を選んだ場合はすでにセーブデータがあっても消す
      _game_obj->writeEEPROM(0, 0);
    }
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

/**
* カーソル移動でのSEを鳴らす関数
*/
void Soukoban::callCursorSE() {
  _game_obj->buzzerCallDelay(3000, 100);
}

/**
* 倉庫番のゲームを行う関数
*/
void Soukoban::soukoGame() {
  // クリア判定(クリアならステージ読み込み)
  if (_is_map_clear) { setupStage(); }

  // リトライ判定(リトライなら再度ステージ読み込み)
  if (_game_obj->getButton(BTN_B)) {
    _is_play_bgm = false;
    _bgm_count = 0;
    setupStage();
  }

  // ボタンによるキャラ移動
  moveChara();
  // キャラの周囲のマップを表示
  showNearbyMap();
  // キャラの向きを取得してキャラを表示
  _game_obj->drawImage64bitBin(16*5-8, 16*2-8, 16, 16, 16, _chara_i, _chara_m);

  // 左側マップ情報を表示
  showMiniMap();
  // ゴール判定
  judgeGoal();
  // タイムアップ判定
  judgeTimeUp();

  // 全ステージクリア判定
  if (_load_stage_num >= STAGE_MAX_SIZE) {
    // 全ステージクリア演出
    allStageClear();
    _game_obj->setMenuSelect(0);
    _game_obj->clearDisplay(); // 画面をクリア
  }

  // 時間カウントアップ
  _time_count++;
}

/**
* ゲームのステージの準備を行う関数
*/
void Soukoban::setupStage() {
  loadStageData(ALL_STAGE_ARRAY[_load_stage_num]);
  _is_map_clear = false;
  // ステージ開始前の表示演出
  beforeStartStage();
  // BGM開始
  _is_play_bgm = true;
  _bgm_count = 0;
  // カウント初期化
  _time_count = 1;
}

/**
* ステージデータを読み込む関数
*/ 
void Soukoban::loadStageData(StageData stage_data) {
  _current_stage.goal_x    = stage_data.goal_x;
  _current_stage.goal_y    = stage_data.goal_y;
  _current_stage.baggage_x = stage_data.baggage_x;
  _current_stage.baggage_y = stage_data.baggage_y;
  _current_stage.current_x = stage_data.current_x;
  _current_stage.current_y = stage_data.current_y;
  _current_stage.time      = stage_data.time;
  _current_stage.map_w     = stage_data.map_w;
  _current_stage.map_h     = stage_data.map_h;
  _current_stage.map_s     = stage_data.map_s;
  _current_stage.ratio     = stage_data.ratio;
  _current_stage.map       = stage_data.map;

  // キャラの向きも一定に読み込み
  _chara_i = CHARA_D;
  _chara_m = CHARA_D_M;
}

/**
* ステージ開始前の演出を行う関数
*/
void Soukoban::beforeStartStage() {
  _game_obj->clearDisplay(); // 画面をクリア

  // ステージ番号計算
  String num_str = String(_load_stage_num + 1);
  if (num_str.length() == 1) {
    num_str = " " + num_str;
  }

  // ステージを表示
  _game_obj->setCursor(SCREEN_WIDTH / 2 - 8 * 3, SCREEN_HEIGHT / 2 - 4);
  _game_obj->print("stage:");
  _game_obj->print(num_str);

  _game_obj->display(); // 表示
  delay(2000);
  _game_obj->clearDisplay(); // 画面をクリア
}

/**
* キャラを動かす関数
*/
void Soukoban::moveChara() {
  // キャラと荷物の現在地を取得
  int16_t x  = _current_stage.current_x;
  int16_t y  = _current_stage.current_y;
  int16_t bx = _current_stage.baggage_x;
  int16_t by = _current_stage.baggage_y;

  // ボタン入力による移動
  if (!_push_cross_btn) {
      if (_game_obj->getButton(BTN_UP)) {
      y--;
      by--;
      _chara_i = CHARA_U;
      _chara_m = CHARA_U_M;
      _push_cross_btn = true;
    } else if (_game_obj->getButton(BTN_DOWN)) {
      y++;
      by++;
      _chara_i = CHARA_D;
      _chara_m = CHARA_D_M;
      _push_cross_btn = true;
    } else if (_game_obj->getButton(BTN_RIGHT)) {
      x++;
      bx++;
      _chara_i = CHARA_R;
      _chara_m = CHARA_R_M;
      _push_cross_btn = true;
    } else if (_game_obj->getButton(BTN_LEFT)) {
      x--;
      bx--;
      _chara_i = CHARA_L;
      _chara_m = CHARA_L_M;
      _push_cross_btn = true;
    } 
  } else {
    _push_cross_btn = false;
  }

  // マップ内の座標に限定
  inMapRange(&x, &y);

  // 壁判定
  if (!isWall(x, y)) {
    // 壁でなければ移動後座標の荷物判定
    if (x == _current_stage.baggage_x && y == _current_stage.baggage_y) {
      // 荷物をマップ内座標に限定
      inMapRange(&bx, &by);
      if (!isWall(bx, by)) {
        // 荷物も壁でなければ移動後のキャラと荷物座標を設定
        _current_stage.current_x = x;
        _current_stage.current_y = y;
        _current_stage.baggage_x = bx;
        _current_stage.baggage_y = by;
      } else {
        _call_se_num = SE_WALL;
      }
    } else {
      // 移動後のキャラ座標を設定
      _current_stage.current_x = x;
      _current_stage.current_y = y;
    }
  } else {
    _call_se_num = SE_WALL;
  }
}

/**
* マップ内範囲に座標を制限する関数
*/
void Soukoban::inMapRange(int16_t *x, int16_t *y) {
  // 移動範囲判定(x方向)
  if (*x < 0) {
    // 一番左
    *x = 0;
  } else if (*x > _current_stage.map_s-1) {
    // 一番右
    *x = _current_stage.map_s - 1;
  }

  // 移動範囲判定(y方向)
  if (*y < 0) {
    // 一番上
    *y = 0;
  } else if (*y > _current_stage.map_h-1) {
    // 一番下
    *y = _current_stage.map_h - 1;
  }
}

/**
* 対象座標が壁がどうかを判定する関数
*
*/
bool Soukoban::isWall(int16_t x, int16_t y) {
  bool result = false;

  // 引数座標のマップ上の値を取得
  int shift_digits = _current_stage.map_s - 1 - x;
  int is_wall = (_current_stage.map[y] >> shift_digits) & 1;

  // ビットが立っていた場合は壁とみなす
  if (is_wall == 1) {
    result = true;
  }

  return result;
}

/**
* キャラの周囲のマップを表示させる関数
*/
void Soukoban::showNearbyMap() {
  int16_t start_x = _current_stage.current_x - 2;
  int16_t start_y = _current_stage.current_y - 2;
  int16_t end_x   = _current_stage.current_x + 3;
  int16_t end_y   = _current_stage.current_y + 2;

  int x_num = 3;
  int y_num = 0;

  for (int16_t y = start_y; y <= end_y; y++) {
    for (int16_t x = start_x; x <= end_x; x++) {
      if (x < 0 || y < 0 || x >=  _current_stage.map_s || y >=  _current_stage.map_h || isWall(x, y)) {
        // 範囲外、または壁の場合は壁を表示
        _game_obj->drawImage64bitBin(16*x_num-8, 16*y_num-8, 16, 16, 16, WALL, NULL);
      } else if (x == _current_stage.goal_x && y == _current_stage.goal_y) {
        // ゴール座標の場合はゴールを表示
        _game_obj->drawImage64bitBin(16*x_num-8, 16*y_num-8, 16, 16, 16, GOAL, NULL);
      } else if (x == _current_stage.baggage_x && y == _current_stage.baggage_y) {
        // 荷物座標の場合は荷物を表示
        _game_obj->drawImage64bitBin(16*x_num-8, 16*y_num-8, 16, 16, 16, BAGGAGE, NULL);
      }
      x_num++;
    }
    y_num++;
    x_num = 3;
  }
}

/**
* ミニマップを表示させる関数
*/
void Soukoban::showMiniMap() {
  // ステージ番号表示
  _game_obj->setCursor(0, 0);
  _game_obj->print("[");
  _game_obj->print(String(_load_stage_num + 1));
  _game_obj->println("]");

  // 残り時間表示
  if (_time_count % (SOUKOBAN_FPS / 2) == 0) {
    _current_stage.time--;
    _time_count = 1;
  }
  _game_obj->print("t:");
  String time_str = String(_current_stage.time);
  while (time_str.length() < 3) {
    time_str = " " + time_str;
  }
  _game_obj->println(time_str);
  _game_obj->println("re: B");

  // マップ情報を表示
  int diff_x = 0;
  int diff_y = 30;
  int ratio  = _current_stage.ratio;
  _game_obj->drawImage64bitBinExpansion(diff_x, diff_y, _current_stage.map_w, _current_stage.map_h, _current_stage.map_h, _current_stage.map, NULL, ratio);

  // キャラを表示
  int16_t new_x = _current_stage.current_x * ratio +1;
  int16_t new_y = _current_stage.current_y * ratio +1;
  _game_obj->drawPixel(new_x + diff_x, new_y + diff_y);
  _game_obj->drawPixel(new_x + diff_x + 1, new_y + diff_y);
  _game_obj->drawPixel(new_x + diff_x, new_y + diff_y + 1);
  _game_obj->drawPixel(new_x + diff_x + 1, new_y + diff_y + 1);

  // 縦線を表示
  _game_obj->drawLine(0, 16*2+4, SCREEN_HEIGHT-1, 16*2+4);
}

/**
* ゴールかどうかを判定する関数
*/
void Soukoban::judgeGoal() {
  if (_current_stage.goal_x == _current_stage.baggage_x && _current_stage.goal_y == _current_stage.baggage_y) {
    // 荷物をゴールに運べていた場合はクリア
    // BGM止める
    _is_play_bgm = false;
    // クリア演出
    clearStage();
    // 次のマップ番号にする
    _load_stage_num++;
    // 自動セーブ
    _game_obj->writeEEPROM(0, byte(_load_stage_num));
    _is_map_clear = true;
  }
}

/**
* クリア後の処理を行う関数
*/
void Soukoban::clearStage() {
  // ステージ番号計算
  String num_str = String(_load_stage_num + 1);
  if (num_str.length() == 1) {
    num_str = " " + num_str;
  }

  // 文字表示部分の範囲を空白にする
  for (int i = 0; i <= SCREEN_WIDTH / 16; i++) {
    _game_obj->drawImage64bitBin(i*16, SCREEN_HEIGHT / 2 - 8, 16, 16, 16, NOTHING, NOTHING);
  }

  // ステージクリア表示
  _game_obj->setCursor(0, SCREEN_HEIGHT / 2 - 4);
  _game_obj->print("    stage:");
  _game_obj->print(num_str);
  _game_obj->print(" clear!");
  _game_obj->display(); // 表示

  // LEDを光らせる
  _game_obj->ledOn(0, 100, 0, 20);

  // クリアSEを鳴らす
  delay(300);
  playClearSe();
  delay(1000);

  // LED OFF
  _game_obj->ledOff();
  _game_obj->clearDisplay(); // 画面をクリア
}

/**
* 時間切れかどうかを判定する関数
*/
void Soukoban::judgeTimeUp() {
  if (_current_stage.time <= 0) {
    // BGM止める
    _is_play_bgm = false;
    // タイムアップ演出
    timeUpStage();
    _is_map_clear = true;
  }
}

/**
* タイムアップ演出を行う関数
*/
void Soukoban::timeUpStage() {
  // 文字表示部分の範囲を空白にする
  for (int i = 0; i <= SCREEN_WIDTH / 16; i++) {
    _game_obj->drawImage64bitBin(i*16, SCREEN_HEIGHT / 2 - 16, 16, 16, 16, NOTHING, NOTHING);
    _game_obj->drawImage64bitBin(i*16, SCREEN_HEIGHT / 2, 16, 16, 16, NOTHING, NOTHING);
  }

  // タイムアップ表示
  _game_obj->setCursor(0, SCREEN_HEIGHT / 2 - 8);
  _game_obj->println("      Time Up!");
  _game_obj->print("   Not cleared...");

  _game_obj->display(); // 表示
  delay(2000);
  _game_obj->clearDisplay(); // 画面をクリア
}

/**
* すべてのステージをクリアした時の関数
*/
void Soukoban::allStageClear() {
  _game_obj->clearDisplay(); // 画面をクリア

  // 表示
  _game_obj->setCursor(0, SCREEN_HEIGHT / 2 - 8);
  _game_obj->println("  All Stage Cleared!");
  _game_obj->print("   Congratulations!");

  _game_obj->display(); // 表示

  // 全ステージclearのSEを鳴らす
  playAllClear();
  delay(1000);
  _game_obj->ledOff();
  _game_obj->clearDisplay(); // 画面をクリア
}

/**
* ステージクリアした時のSEを鳴らす関数
*/
void Soukoban::playClearSe() {
  for (int i = 0; i < CLEAR_SE_MAX; i++) {
    _game_obj->buzzerCallDelay(CLEAR_SE[i][0], CLEAR_SE[i][1]);
  }
}

/**
* 全ステージクリアした時のLEDを光らせてSEを鳴らす関数
*/
void Soukoban::playAllClear() {
  _game_obj->ledOff();
  for (int i = 0; i < ALL_CLEAR_SE_MAX; i++) {
    _game_obj->ledOn(ALL_CLEAR_LED[i][0], ALL_CLEAR_LED[i][1], ALL_CLEAR_LED[i][2], ALL_CLEAR_LED[i][3]);
    _game_obj->buzzerCallDelay(ALL_CLEAR_SE[i][0], ALL_CLEAR_SE[i][1]); 
  }
}