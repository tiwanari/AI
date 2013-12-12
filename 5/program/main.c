#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "board.h"
#include "uct.h"

extern int PLAYOUT_MAX;
extern int EXPAND_THRESHOLD;
extern double C;

void show_guide()
{
	int i;
	printf("---guide---\n");
	for (i = 0; i < AREA; i++) {
		printf("%2d|", i);
		if ((i + 1) % 4 == 0)
			printf("\n");
	}
	printf("-----------\n");
}

int input_move(stone_t turn, const stone_t board[HIGHT][AREA])
{
	char pos[100];

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

int enemy(stone_t turn, const stone_t board[HIGHT][AREA])
{
	return uct(turn, board);
}

#define TRY 100

int main(void)
{
	stone_t turn;
	stone_t board[HIGHT][AREA];
	int pos, layer;
	int win[2] = {};	// 勝利数をカウント
	int i;

	// for (i = 0; i < TRY; i++) {
		turn = BLACK;
		init_board(board);	// 盤面の初期化
		// print_board(board);
		while (1) {
			if (turn == BLACK) {
				pos = input_move(turn, board);	// 入力
				// PLAYOUT_MAX = 50000;
				// EXPAND_THRESHOLD = 100;
				// C = 0.7;
				// pos = enemy(turn, board);
			}
			else {
				PLAYOUT_MAX = 50000;
				EXPAND_THRESHOLD = 1000;
				C = 0.7;
				pos = enemy(turn, board);
				printf("%d\n", pos);
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
			// printf("--- next turn ---\n");
			turn = REVERSE(turn);
		}
	// }

	printf("BLACK: %d, WHITE: %d\n", win[0], win[1]);
	
	return 0;
}