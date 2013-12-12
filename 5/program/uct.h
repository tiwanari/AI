#pragma once

#include <math.h>
#include "board.h"

// #define PLAYOUT_MAX 20000
// #define EXPAND_THRESHOLD 10
// #define C 1.0

#define ucb(x, n, ni) ((x) + C * sqrt(2 * log(n)/(ni)))

#define INIFINITY 100000.0

// 盤面
typedef struct node {
	struct node* moth;				// 親
	struct node* children[AREA];	// 子供(最大AREA)
	int nchildren;					// 子供の数
	int pos;						// 置いた位置
	int playout;					// プレイアウト回数
	int win;						// 勝利数
}* node_t;

/**
 * UCTによって最善手を求める
 * @param stone_t turn 現在の手番
 * @param stone_t board[][] 盤面
 * @return int 最善手
 */
int uct(stone_t turn, const stone_t board[HIGHT][AREA]);