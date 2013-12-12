#pragma once

#define WIDTH 4
#define DEPTH 4
#define HIGHT 4

#define AREA WIDTH * DEPTH

typedef enum {
	NONE,
	BLACK,
	WHITE,
} stone_t;

#define REVERSE(STONE) STONE == BLACK ? WHITE : BLACK

extern int PLAYOUT_MAX;
extern int EXPAND_THRESHOLD;
extern double C;

/**
 * 盤面を初期化する
 * @param stone_t board[][] 初期化する盤面
 */
void init_board(stone_t board[HIGHT][AREA]);

/**
 * 指定した位置におけるか
 * @param int pos
 * @param stone_t board[][]
 * @return int ture:1, false:0
 */
int is_putable(int pos, const stone_t board[HIGHT][AREA]);

/**
 * 指定した位置に配置
 * @param int pos
 * @param stone_t board[][]
 * @return int 置いた層
 */
int put_stone(int pos, stone_t color, stone_t board[HIGHT][AREA]);

/**
 * 合法手を作る
 * @param stone_t board[][] 盤面
 * @param int hands[AREA] 合法手の格納先
 * @return int 合法手の数
 */
int get_legal_hands(const stone_t board[HIGHT][AREA], int hands[AREA]);

/**
 * 全て埋まっているか
 * @param stone_t board[][] 盤面
 * @return int true:1, false:0
 */
int is_full(const stone_t board[HIGHT][AREA]);

/**
 * 盤面のコピー
 * @param stone_t board[][] コピー元
 * @param stone_t dest[][] コピー先
 */
void copy_board(const stone_t board[HIGHT][AREA], stone_t dest[HIGHT][AREA]);

/**
 * ゲームが終了したかを調べる
 * @param int layer 置いたの位置(高さ)
 * @param int pos 置いたの位置(平面)
 * @param stone_t color 置いた色
 * @param stone_t board[][] 盤面
 * @return int true:1, false:0
 */
int check_win(int layer, int pos, stone_t color, const stone_t board[HIGHT][AREA]);

/**
 * 石のイメージを返す
 * @param stone_t color 石の色
 * @return char* 文字列表現
 */
char* get_stone_image(stone_t color);

/**
 * ボードを上から表示
 * @param stone_t board[][] 盤面
 **/
void print_board(const stone_t board[HIGHT][AREA]);







