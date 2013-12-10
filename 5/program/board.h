#pragma once

#define WIDTH 4
#define DEPTH 4
#define HIGHT 4

#define AREA WIDTH * DEPTH

typedef enum {
	NONE,
	BLACK,
	WHITE,
}
stone_t;

typedef struct board {
	int move;			// 置いた位置
	stone_t board[4][16];	// 盤面
	int playout;		// プレイアウト回数
	int win;			// 勝利数
}
board_t;

/**
 * ボードを上から表示
 * @param stone_t board[][] 盤面
 **/
void print_board(stone_t board[][]);