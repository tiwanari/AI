#include <stdio.h>
#include "board.h"
#include "negamax.h"

int DEPTH_MAX;

// 評価値
int eval_board[HIGHT][AREA] =
{
	{
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
	},
	{
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
	},
	{
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
	},
	{
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
	},
};

/**
 * ゲーム終了局面の評価値を返す
 * @param int pos 置いた位置
 * @param stone_t mycolor 自分の色
 * @param stone_t board[][] 盤面
 * @return win:∞, draw:0, lose:−∞
 */
int get_terminal_value(int pos, stone_t mycolor, const stone_t board[HIGHT][AREA])
{
	return 0;
}


/**
 * 評価関数
 * @param stone_t mycolor 自分の色
 * @param stone_t board[][] 盤面
 * @return int 評価値
 */
int get_evaluation_value(stone_t mycolor, const stone_t board[HIGHT][AREA])
{
	int pos, value = 0, c;

	// 場所による得点計算
	for (pos = 0; pos < AREA; pos++)
	{
		// c = board[pos];
		// if (c == 0)
		// 	continue;
		// else if (c == TURNCOLOR(turn))
		// 	value += evalboard[pos];
		// else
		// 	value -= evalboard[pos];
	}
	return value;
}

/**
 * negamax + αβ枝刈りを実際に行う
 * @param int depth 探索の深さ
 * @param int al α
 * @param int be β
 * @param stone_t mycolor 自分の色
 * @param stone_t turn 現在の手番
 * @param stone_t board[][] 盤面
 * @param int* res 最善手
 * @return int α
 */
int negamax_t(int depth, int al, int be, stone_t mycolor, 
	stone_t turn, stone_t board[HIGHT][AREA], int* res)
{
	int hands[AREA];
	int nhands;
	int value;
	int i;
    
    // 一番下なら評価値を返す
	if (depth >= DEPTH_MAX)	return get_evaluation_value(mycolor, board);

	// 合法手を取得
	nhands = get_legal_hands(board, hands);
	// 置くところがないなら結果を返す
	if (nhands == 0) {
		// if (isTerminalNode())
		// 	return get_terminal_value();
	}

	for (i = 0; i < nhands; i++) {
		put_stone(hands[i], turn, board);	// 手を進める

		// 再帰
		value = -negamax_t(depth + 1, -be, -al, mycolor, REVERSE(turn), board, res);
		
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
 * @param stone_t mycolor 自分の色
 * @param stone_t turn 現在の手番
 * @param stone_t board[][] 盤面
 * @return int 最善手
 */
int negamax(stone_t mycolor, stone_t turn, stone_t board[HIGHT][AREA]) {
	int value;	// 評価値
	int res;	// 最善手の格納先

	// 探索を行う
	value = negamax_t(0, ALPHA, BETA, mycolor, turn, board, &res);

	return res;
} 

