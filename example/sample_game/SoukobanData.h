/**
* @file SoukobanData.h
* @brief 倉庫番のデータヘッダーファイル
*
* @details 倉庫番に必要な定数やデータを記述
* @note ゲームの処理はSoukoban.hを参照
*/

/** FPS */
#define SOUKOBAN_FPS 20

/** SE */
#define SE_NONE 0
#define SE_WALL 1

// ---------BGM関係の定数----------
/** BGMデータ */
const int BGM_MAX = 47;

unsigned int BGM_DATA[BGM_MAX][2] = {
  {831 , 150}, // ♯ソ
  {831 , 150}, // ♯ソ
  {831 , 150}, // ♯ソ
  {659 , 150}, // ミ
  {659 , 150}, // ミ
  {659 , 150}, // ミ
  {740 , 150}, // ♯ファ
  {740 , 150}, // ♯ファ
  {740 , 150}, // ♯ファ
  {523 , 150}, // ド
  {523 , 150}, // ド
  {523 , 150}, // ド
  {831 , 150}, // ♯ソ
  {831 , 150}, // ♯ソ
  {831 , 150}, // ♯ソ
  {659 , 150}, // ミ
  {659 , 150}, // ミ
  {659 , 150}, // ミ
  {740 , 150}, // ♯ファ
  {740 , 150}, // ♯ファ
  {740 , 150}, // ♯ファ
  {523 , 150}, // ド
  {523 , 150}, // ド
  {523 , 150}, // ド
  {831 , 150}, // ♯ソ
  {831 , 150}, // ♯ソ
  {831 , 150}, // ♯ソ
  {659 , 150}, // ミ
  {659 , 150}, // ミ
  {659 , 150}, // ミ
  {740 , 150}, // ♯ファ
  {740 , 150}, // ♯ファ
  {740 , 150}, // ♯ファ
  {523 , 150}, // ド
  {523 , 150}, // ド
  {523 , 150}, // ド

  {440 , 150}, // ラ
  {0 , 150},   // 無音
  {440 , 150}, // ラ
  {0 , 150},   // 無音
  {440 , 150}, // ラ
  {0 , 150},   // 無音
  {0 , 150},   // 無音
  {0 , 150},   // 無音
  {0 , 150},   // 無音
  {0 , 150},   // 無音
  {0 , 150},   // 無音
};

/** クリア時のSE */
const int CLEAR_SE_MAX = 5;

unsigned int CLEAR_SE[CLEAR_SE_MAX][2] = {
  {1397, 450},  // ファ
  {0 , 300},    // 無音
  {1175, 150},  // ファ
  {587, 150},   // レ
  {1397, 600},  // ファ
};

/** 全クリア時のSE */
const int ALL_CLEAR_SE_MAX = 13;

unsigned int ALL_CLEAR_SE[ALL_CLEAR_SE_MAX][2] = {
  {784, 150},   // ソ
  {1047, 150},  // ド
  {1175, 150},  // レ
  {1568, 150},  // ソ
  {988, 150},  // シ
  {1175, 150},  // レ

  {784, 150},   // ソ
  {1047, 150},  // ド
  {1175, 150},  // レ
  {1568, 150},  // ソ
  {988, 150},  // シ
  {1175, 150},  // レ

  {1568, 600},  // ソ
};

/** 全クリア時のLED */
const int ALL_CLEAR_LED_MAX = 13;

unsigned int ALL_CLEAR_LED[ALL_CLEAR_LED_MAX][4] = {
  // r, g, b, val
  {255, 0, 0, 100},
  {128, 128, 0, 100},
  {0, 255, 0, 100},
  {0, 128, 128, 100},
  {0, 0, 255, 100},
  {0, 128, 128, 100},

  {255, 0, 0, 100},
  {128, 128, 0, 100},
  {0, 255, 0, 100},
  {0, 128, 128, 100},
  {0, 0, 255, 100},
  {0, 128, 128, 100},

  {255, 200, 200, 120},
};

// ---------ゲーム関係の定数----------
/** 倉庫番タイトル */
long long unsigned int SOUKO_TITLE[20] = {0xffffffffffffffff,0xffffffffffffffff,0xfffcffff3ffff9ff,0xfff87fc000e000ff,0xfff31fc000f019ff,0xffc00fcf9ff999ff,0xff0fe1c000fd93ff,0xfe0001cf9fc0007f,0xffcfcfc801fe07ff,0xffc00fc999f891ff,0xffcfcfc801c3983f,0xffc00fc801e0017f,0xffcfffcb99f399ff,0xff8007c801f001ff,0xff80079f9ff001ff,0xff27e78000f399ff,0xff20073f9ff001ff,0xffe7e7bf9ff3f9ff,0xffffffffffffffff,0xffffffffffffffff};

/** キャラクターの上向きドット画像 */
long long unsigned int CHARA_U[16]   = {0x1ff8,0x2004,0x6006,0xa005,0xa005,0x6006,0x23c4,0x1c38,0x3c3c,0x4c32,0x7c3e,0x5ffa,0x3ffc,0x1ff8,0x2244,0x3e7c};
/** キャラクターの右向きドット画像 */
long long unsigned int CHARA_R[16]   = {0xff0,0x1008,0x24a4,0x2b58,0x2b28,0x2508,0x1118,0xd30,0x3ffc,0x4f92,0x7fbe,0x2f94,0x1fb8,0x1ff8,0x2244,0x7c3e};
/** キャラクターの左向きドット画像 */
long long unsigned int CHARA_L[16]   = {0xff0,0x1008,0x2524,0x1ad4,0x14d4,0x10a4,0x1888,0xcb0,0x3ffc,0x49f2,0x7bfe,0x29f4,0x1bf8,0x1ff8,0x2244,0x7c3e};
/** キャラクターの下向きドット画像 */
long long unsigned int CHARA_D[16]   = {0x1ff8,0x2814,0x766e,0xa995,0xaa55,0x6816,0x2994,0x1c38,0x3ffc,0x4e72,0x7efe,0x2e74,0x1ef8,0x1ff8,0x2244,0x3e7c};
/** キャラクターの上向きマスク */
long long unsigned int CHARA_U_M[16]   = {0xe007,0xc003,0x8001,0x0,0x0,0x8001,0xc003,0xe007,0xc003,0x8001,0x8001,0x8001,0xc003,0xe007,0xc183,0xc183};
/** キャラクターの右向きマスク*/
long long unsigned int CHARA_R_M[16]   = {0xf00f,0xe007,0xc003,0xc007,0xc007,0xc007,0xe007,0xf00f,0xc003,0x8001,0x8001,0xc003,0xe007,0xe007,0xc183,0x83c1};
/** キャラクターの左向きマスク */
long long unsigned int CHARA_L_M[16]   = {0xf00f,0xe007,0xc003,0xe003,0xe003,0xe003,0xe007,0xf00f,0xc003,0x8001,0x8001,0xc003,0xe007,0xe007,0xc183,0x83c1};
/** キャラクターの下向きマスク */
long long unsigned int CHARA_D_M[16]   = {0xe007,0xc003,0x8001,0x0,0x0,0x8001,0xc003,0xe007,0xc003,0x8001,0x8001,0xc003,0xe007,0xe007,0xc183,0xc183};

/** 全てのドットが立っていない何もないドット画像 */
long long unsigned int NOTHING[16] ={0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0};

/** 全てのドットが立っている壁ドット画像 */
long long unsigned int WALL[16] = {0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff};

/** 荷物のドット画像 */
long long unsigned int BAGGAGE[16] = {0x0,0x7ffe,0x4002,0x7ffe,0x4ff2,0x67e6,0x73ce,0x781e,0x781e,0x73ce,0x67e6,0x4ff2,0x7ffe,0x4002,0x7ffe,0x0};

/** ゴールのドット画像 */
long long unsigned int GOAL[16] = {0x0,0xfe0,0x1ff0,0x3ff8,0x7c7c,0x783c,0x703c,0x7000,0x70fc,0x70fc,0x783c,0x3c7c,0x3ffc,0x1fec,0xfcc,0x0};


/** ステージデータの構造体 */
typedef struct {
  int16_t goal_x;    /* ゴールx座標 */
  int16_t goal_y;    /* ゴールy座標 */

  int16_t baggage_x; /* 荷物x座標 */
  int16_t baggage_y; /* 荷物y座標 */

  int16_t current_x; /* キャラクター現在地x座標 */
  int16_t current_y; /* キャラクター現在地y座標 */

  int time;          /* 制限時間 */
  int16_t map_w;     /* マップ横幅 */
  int16_t map_h;     /* マップ縦幅 */
  int16_t map_s;     /* マップの横幅で必要な部分 */
  int16_t ratio;     /* ミニマップ表示倍率 */
  long long unsigned int *map; /* マップ情報配列 */
} StageData;

/** 全ステージ数 */
const int STAGE_MAX_SIZE = 10;

/** マップドット画像 */
long long unsigned int MAP_0[16] = {0xffff,0xffff,0xffff,0xffff,0xffff,0xf00f,0xf00f,0xf00f,0xf00f,0xf00f,0xf00f,0xffff,0xffff,0xffff,0xffff,0xffff};
long long unsigned int MAP_1[16] = {0xffff,0xffff,0xffff,0xffff,0xffff,0xf00f,0xf00f,0xf50f,0xf24f,0xf00f,0xf00f,0xffff,0xffff,0xffff,0xffff,0xffff};
long long unsigned int MAP_2[16] = {0xffff,0x9fff,0x9fff,0x800f,0x800f,0x800f,0x800f,0xfe0f,0xfe07,0xfe03,0xfe03,0xfe03,0xff03,0xffc3,0xffc3,0xffff};
long long unsigned int MAP_3[16] = {0xffff,0xc003,0x8003,0x8001,0x8021,0x8421,0x8001,0x8001,0x8001,0x8001,0x8c31,0x8c21,0x8001,0xe003,0xe007,0xffff};
long long unsigned int MAP_4[16] = {0xffff,0xffff,0xffff,0xffff,0xc003,0xc003,0xd803,0xdfe3,0x9fe3,0x9803,0x8803,0x883f,0xc7ff,0xffff,0xffff,0xffff};
long long unsigned int MAP_5[16] = {0xffff,0x831d,0x8211,0xa601,0xc7a1,0xce39,0x8e0d,0x827d,0x8005,0xce25,0xd021,0xd8f1,0xdec1,0xde09,0x80f9,0xffff};
long long unsigned int MAP_6[32] = {0xffffffff,0x80000001,0x80000001,0x80000001,0x80000001,0x80000001,0x80000001,0x80000001,0x80000001,0x80000001,0x80000001,0x80000001,0x80000001,0x80000001,0x80000001,0x80000001,0x80000001,0x80000001,0x80000001,0x80000001,0x80000001,0x80000001,0x80000001,0x80000001,0x80000001,0x80000001,0x80000001,0x80000001,0x80000001,0x80000001,0x80000001,0xffffffff};
long long unsigned int MAP_7[32] = {0xffffffff,0xffffffff,0xffffffff,0xe7ffffdf,0xc000000f,0xe3ffff8f,0xecfffedf,0xe800005f,0xec7ff85f,0xec9ff4df,0xed0002df,0xed9fe2df,0xedb3b6df,0xeda016df,0xedb396df,0xeda6b6df,0xeda0b6df,0xedb4b6df,0xed1fb6df,0xed0016df,0xecbf26df,0xe8ffc6df,0xe80002df,0xe5ffe6df,0xc7fffcdf,0xc000005f,0xeffffcdf,0xdfffff9f,0x8000000f,0x8fffff9f,0xdfffffff,0xffffffff};
long long unsigned int MAP_8[32] = {0xffffffff,0xffffffff,0xffffffff,0xffffbfff,0xffff1fff,0xfff35dff,0xf3004c1f,0xf060001f,0xf9fefe3f,0xfde6ff7f,0xfd80ff7f,0xfdc0ff7f,0xf9f61f7f,0xf90ff17f,0xf0300307,0xe5800027,0xec03f827,0xcc360e67,0xcc140c77,0xe9140817,0xec56191f,0xe513b81f,0xcc18027f,0xdc3f1b1f,0xc438221f,0xfc01203f,0xfe019e7f,0xfff87fff,0xffe07fff,0xffe9ffff,0xffffffff,0xffffffff};
long long unsigned int MAP_9[32] = {0xffffffff,0xffffffff,0xf000007f,0xf001f01f,0xe0f0f0df,0xe27801df,0xe33c7ddf,0xe3b9fcdf,0xe3bbfc1f,0xe3fbfc1f,0xe9db8607,0xe9d77607,0xeac7763f,0xeb00663f,0xe000ef3f,0xeb94ec3f,0xeb76dc5f,0xda769cdf,0xd87638ef,0xd8607cef,0xd97f7cef,0x9bbf7cef,0x98cf70ef,0x98f0f0ef,0x987fe32f,0x9803c3df,0x9982017f,0xc1f2001f,0xfffe201f,0xfffff80f,0xffffffff,0xffffffff};

/** マップデータ */
// {ゴールx座標, ゴールy座標, 荷物x座標,  荷物y座標, キャラクター現在地x座標, キャラクター現在地y座標, 制限時間, マップ横幅, マップ縦幅, マップの横幅で必要な部分, ミニマップ表示倍率, マップ情報配列}
// {goal_x,     goal_y,     baggage_x, baggage_y, current_x,             current_y,             time,     map_w,     map_h,     map_s,                  ratio,            *map}
StageData STAGE_0_DATA = { 8,  7,  6,  7,  5,  7,  60, 16, 16, 16, 2, MAP_0};
StageData STAGE_1_DATA = { 6,  7,  9,  7,  7,  8,  60, 16, 16, 16, 2, MAP_1};
StageData STAGE_2_DATA = { 1,  1, 11, 12, 12, 13,  60, 16, 16, 16, 2, MAP_2};
StageData STAGE_3_DATA = { 3,  2,  9,  8,  9,  9,  60, 16, 16, 16, 2, MAP_3};
StageData STAGE_4_DATA = { 4, 12,  6, 10,  7, 10,  60, 16, 16, 16, 2, MAP_4};
StageData STAGE_5_DATA = {14,  1,  2,  2,  1, 14, 100, 16, 16, 16, 2, MAP_5};
StageData STAGE_6_DATA = { 2, 29,  9,  7,  7,  8, 100, 32, 32, 32, 1, MAP_6};
StageData STAGE_7_DATA = {15, 15,  2, 28,  2, 29, 150, 32, 32, 32, 1, MAP_7};
StageData STAGE_8_DATA = {16, 18, 12, 10,  2, 24, 200, 32, 32, 32, 1, MAP_8}; 
StageData STAGE_9_DATA = {11, 19, 23, 27, 23, 28, 300, 32, 32, 32, 1, MAP_9};

/** 全ステージデータの配列 */
StageData ALL_STAGE_ARRAY[STAGE_MAX_SIZE] = {
  STAGE_0_DATA, STAGE_1_DATA, STAGE_2_DATA, STAGE_3_DATA, STAGE_4_DATA,
  STAGE_5_DATA, STAGE_6_DATA, STAGE_7_DATA, STAGE_8_DATA, STAGE_9_DATA
};

