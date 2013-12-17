/**
 * ゲームの進行をするもの
 * @author 03-123006 岩成達哉
 */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
// #include <sys/time.h>
#include <math.h>
#include "board.h"
#include "uct.h"
#include "negamax.h"

extern int PLAYOUT_MAX;
extern int EXPAND_THRESHOLD;
extern double C;
extern int DEPTH_MAX;

/**
 * 現在の時刻を得る(unix系のみ)
 * sys/time.hをインクルードすること
 * @return double 時間[sec](精度:6桁)
 */
// double cur_time()
// {
// 	struct timeval tp[1];
// 	gettimeofday(tp, NULL);
// 	return tp->tv_sec + tp->tv_usec * 1.0e-6;
// }

/**
 * ブロックの置く位置のガイドを表示
 */
void show_guide()
{
	int i;
	printf("--- guide---\n");
	for (i = 0; i < AREA; i++) {
		printf("%2d|", i);
		if ((i + 1) % 4 == 0)
			printf("\n");
	}
	printf("-----------\n");
}

/**
 * ユーザからの入力を得る
 * @param stone_t turn 現在の手番
 * @param stone_t board[][] 盤面
 * @return int 置いた位置
 */
int input_move(stone_t turn, const stone_t board[HIGHT][AREA])
{
	char pos[100];	// buffer

	show_guide();
	while (1) {
		printf("input next pos(%s)[0-15]: ", get_stone_image(turn));
		fgets(pos, 100, stdin);

		if (!isdigit(pos[0])) {
			printf("Illegal input!\n");
			continue;
		} 

		if (atoi(pos) >= 0 && atoi(pos) < AREA && is_putable(atoi(pos), board)) break;

		printf("Illegal move!\n");
	}

	return atoi(pos);
}

int main(int argc, char **argv)
{
	stone_t turn;
	stone_t board[HIGHT][AREA];
	int pos, layer;
	int win[2] = {};	// 勝利数をカウント

	// 手番を選ぶ
	turn = (argc > 1 && argv[1][0] != '0') ? WHITE : BLACK;
	// プレイアウト回数
	// PLAYOUT_MAX = argc > 2 ? atoi(argv[1]) : 10000;	// ここが間違ってました
	PLAYOUT_MAX = argc > 2 ? atoi(argv[2]) : 10000;

	printf("PLAYOUT_MAX: %d\n", PLAYOUT_MAX);

	init_board(board);	// 盤面の初期化
	print_board(board);	// 初期盤面

	while (1) {
		if (turn == BLACK) {
			pos = input_move(turn, board);	// 入力
		}
		else {
			// DEPTH_MAX = argc > 2 ? atoi(argv[2]) : 5;
			// pos = negamax(turn, board);

			pos = uct(turn, board);
			printf("input next pos(%s)[0-15]: %d\n", get_stone_image(turn), pos);
		}
		layer = put_stone(pos, turn, board);	// 石を置く

		print_board(board);	// ボードの表示

		if (check_win(layer, pos, turn, board)) {
			win[turn - 1]++;
			printf("%s Win !!\n", get_stone_image(turn));
			break;
		}
			
		if (is_full(board)) {
			printf("Draw !!\n");
			break;
		}
		printf("--- next turn ---\n");
		turn = REVERSE(turn);
	}

	
	return 0;
}
