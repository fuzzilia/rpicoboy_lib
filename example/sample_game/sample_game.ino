#include "RPicoBoy.h"
#include "StartMenu.h"
#include "Soukoban.h"
#include "Omikuji.h"
#include "SoundTest.h"
#include "LedTest.h"
#include "MovieTest.h"
#include "QRTest.h"

/**
 * RPicoBoyのサンプルゲーム
 */
const int MENU_MAX = 6;
String MENU_ARRAY[MENU_MAX] = {"Soukoban", "Furtune", "Sound Test", "Led Test", "Movie Test", "Help"};

const int SELECT_START_MENU = 0;
const int SELECT_SOUKOBAN   = 1;
const int SELECT_FORTUNE    = 2;
const int SELECT_SOUND_TEST = 3;
const int SELECT_LED_TEST   = 4;
const int SELECT_MOVIE_TEST = 5;
const int SELECT_QR_TEST    = 6;

// ゲーム共通のオブジェクト
RPicoBoy rb = RPicoBoy();

// 各ゲームのオブジェクト
StartMenu menu_obj  = StartMenu(&rb, 32, 3, 10, MENU_MAX, MENU_ARRAY);
Soukoban souko_obj  = Soukoban(&rb);
Omikuji omikuji_obj = Omikuji(&rb);
SoundTest sound_obj = SoundTest(&rb);
LedTest led_obj     = LedTest(&rb);
MovieTest movie_obj = MovieTest(&rb);
QRTest qr_obj       = QRTest(&rb);

/* ---- Core 0の処理 ---- */
void setup() {
  Serial.begin(115200);
  rb.init(24, 150);

  menu_obj.setup0();
  menu_obj.showLogo(); // ロゴを表示

  Serial.println("core0:start....");
}


// メインのループ関数
void loop() {
  switch (rb.getMenuSelect()) {
    case SELECT_START_MENU:
      // スタートメニューを実行
      runStartMenu();
      break;
    case SELECT_SOUKOBAN:
      // 倉庫番を実行
      runSoukoban();
      break;
    case SELECT_FORTUNE:
      // おみくじを実行
      runFurtune();
      break;
    case SELECT_SOUND_TEST:
      // サウンドテストを実行
      runSoundTest();
      break;
    case SELECT_LED_TEST:
      // Ledテストを実行
      runLedTest();
      break;
    case SELECT_MOVIE_TEST:
      // Movieテストを実行
      runMovieTest();
      break;
    case SELECT_QR_TEST:
      // QRテストを実行
      runQRTest();
      break;
  }
}


/* ---- Core 1の処理 ---- */
void setup1() {
  Serial.println("core1:start....");
}

void loop1() {
  switch (rb.getMenuSelect()) {
    case SELECT_START_MENU:
      // スタートメニューの場合はスタートメニューのrun1を実行
      menu_obj.run1();
      break;
    case SELECT_SOUKOBAN:
      // 倉庫番の場合は倉庫番のrun1を実行
      souko_obj.run1();
      break;
    case SELECT_FORTUNE:
      // おみくじの場合はおみくじのrun1を実行
      omikuji_obj.run1();
      break;
    case SELECT_SOUND_TEST:
      // サウンドテストの場合はサウンドテストのrun1を実行
      sound_obj.run1();
      break;
    case SELECT_LED_TEST:
      // LEDテストの場合はLEDテストのrun1を実行
      led_obj.run1();
      break;
    case SELECT_MOVIE_TEST:
      // MOVIEテストの場合はMOVIEテストのrun1を実行
      movie_obj.run1();
      break;
    case SELECT_QR_TEST:
      // QRテストの場合はQRテストのrun1を実行
      qr_obj.run1();
      break;
  }
}

// スタートメニューを実行する関数
void runStartMenu() {
  if (rb.isChangedMenuSelect()) {
    menu_obj.setup0();
    rb.setMenuSelect(SELECT_START_MENU); // 初期化
  }

  int menu_num = menu_obj.getDecision();
  if (menu_num == SELECT_START_MENU) {
    // スタートメニューを実行
    menu_obj.run0();
  } else {
    rb.setMenuSelect(menu_num);
  }
}

// 倉庫番を実行する関数
void runSoukoban() {
  if (rb.isChangedMenuSelect()) {
    souko_obj.setup0();
    rb.setMenuSelect(SELECT_SOUKOBAN); // 初期化
  }
  // 倉庫番を実行
  souko_obj.run0();
}

// おみくじを実行する関数
void runFurtune() {
  if (rb.isChangedMenuSelect()) {
    omikuji_obj.setup0();
    rb.setMenuSelect(SELECT_FORTUNE); // 初期化
  }
  // おみくじを実行
  omikuji_obj.run0();
}

// サウンドテストを実行する関数
void runSoundTest() {
  if (rb.isChangedMenuSelect()) {
    sound_obj.setup0();
    rb.setMenuSelect(SELECT_SOUND_TEST); // 初期化
  }
  // サウンドテストを実行
  sound_obj.run0();
}

// LEDテストを実行する関数
void runLedTest() {
  if (rb.isChangedMenuSelect()) {
    led_obj.setup0();
    rb.setMenuSelect(SELECT_LED_TEST); // 初期化
  }
  // LEDテストを実行
  led_obj.run0();
}

// Movieテストを実行する関数
void runMovieTest() {
  if (rb.isChangedMenuSelect()) {
    movie_obj.setup0();
    rb.setMenuSelect(SELECT_MOVIE_TEST); // 初期化
  }
  // Movieテストを実行
  movie_obj.run0();
}

// QRテストを実行する関数
void runQRTest() {
  if (rb.isChangedMenuSelect()) {
    qr_obj.setup0();
    rb.setMenuSelect(SELECT_QR_TEST); // 初期化
  }
  // QRテストを実行
  qr_obj.run0();
}