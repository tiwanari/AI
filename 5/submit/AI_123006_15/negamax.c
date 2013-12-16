/**
 * Negamax法+αβカットを実装したもの
 * @author 03-123006 岩成達哉
 */

#include <stdio.h>
#include "board.h"
#include "negamax.h"

int DEPTH_MAX = 5;

// 評価値
int eval_board[HIGHT][AREA] =
{
	{
		 50, -10, -10,  50,
		-10,   0,   0, -10,
		-10,   0,   0, -10,
		 50, -10, -10,  50,
	},
	{
		-10,   0,   0, -10,
		  0,  30,  30,   0,
		  0,  30,  30,   0,
		-10,   0,   0, -10,
	},
	{
		-10,   0,   0, -10,
		  0,  30,  30,   0,
		  0,  30,  30,   0,
		-10,   0,   0, -10,
	},
	{
		 50, -10, -10,  50,
		-10,   0,   0, -10,
		-10,   0,   0, -10,
		 50, -10, -10,  50,
	},
};

/**
 * 評価関数
 * @param stone_t mycolor 自分の色
 * @param stone_t board[][] 盤面
 * @return int 評価値
 */
int get_evaluation_value(stone_t mycolor, const stone_t board[HIGHT][AREA])
{
	int i, j;
	int value = 0;
	// static int RATE = 10;

	// リーチの数を評価値とする
	// value += RATE * get_reach(mycolor, board);
	// value -= RATE * get_reach(REVERSE(mycolor), board);

	// 場所による得点計算
	for (i = 0; i < HIGHT; i++) {
		for (j = 0; j < AREA; j++) {
			stone_t temp = board[i][j];
			if (temp == mycolor)
				value += eval_board[i][j];
			else if (temp == REVERSE(mycolor))
				value -= eval_board[i][j];
		}
	}

	return value;
}

/**
 * negamax + αβ枝刈りを実際に行う
 * @param int depth 探索の深さ
 * @param int al α
 * @param int be β
 * @param stone_t turn 現在の手番
 * @param stone_t board[][] 盤面
 * @param int* res 最善手
 * @return int α
 */
int negamax_t(int depth, int al, int be, 
	stone_t turn, stone_t board[HIGHT][AREA], int* res)
{
	int hands[AREA];
	int nhands;
	int value;
	int layer;
	int i;
    
    // 一番下なら評価値を返す
	if (depth >= DEPTH_MAX)	return get_evaluation_value(turn, board);

	// 合法手を取得
	nhands = get_legal_hands(board, hands);

	for (i = 0; i < nhands; i++) {
		layer = put_stone(hands[i], turn, board);	// 手を進める
		
		// 勝利判定
		if (check_win(layer, hands[i], turn, board))
			value = WIN_VAL;
		else if (is_full(board))
			value = 0;
		else
			value = -negamax_t(depth + 1, -be, -al, REVERSE(turn), board, res);
	
		pick_stone(hands[i], board);	// 手を戻す
		
		// 最善手の更新
		if (value > al) {
			al = value;
			if (depth == 0)	*res = hands[i];
		}

		// αβ枝刈り
		if (value >= be) break;
	}
	return al;
}

/**
 * negamax + αβ枝刈りで最善手を返す
 * @param stone_t turn 現在の手番
 * @param stone_t board[][] 盤面
 * @return int 最善手
 */
int negamax(stone_t turn, const stone_t board[HIGHT][AREA])
{
	int value;	// 評価値
	int res;	// 最善手の格納先
	stone_t copy[HIGHT][AREA];

	copy_board(board, copy);

	// 探索を行う
	value = negamax_t(0, ALPHA, BETA, turn, copy, &res);
	// if (value == WIN_VAL)
	// 	printf("CP find wins!\n");
	// else if (value == -WIN_VAL)
	// 	printf("CP find lose...\n");
	return res;
} 

