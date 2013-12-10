#include <stdio.h>
#include "board.h"

/**
 * 指定した位置におけるか
 * @param int pos
 * @param stone_t board[][]
 * @return int ture:1, false:0
 */
int is_movable(int pos, stone_t board[][])
{
	return board[3][pos] == NONE;
}

/**
 * 合法手を作る
 * @param stone_t board[][] 盤面
 * @param int moves[AREA] 合法手の格納先
 * @return int 合法手の数
 */
int get_legal_moves(stone_t board[][], int moves[AREA])
{
	int count = 0;
	int i;

	for (i = 0; i < AREA; i++) {
		if (board[3][i] == NONE)
			moves[count++] = i;
	}

	return count;
}

/**
 * 置かれた位置が平面の対角線上にあるか
 * @param int pos 置かれた位置
 * @return int true:1, false:0
 */
int is_on_diagonal_line(int pos)
{
	return pos % 5 == 0 || pos % 3 == 0;
}

/**
 * 盤面の対角線方向の面を返す
 * @param int layer 対象の位置(高さ)
 * @param int pos 対象の位置(平面)
 * @param stone_t board[][] 盤面
 * @param stone_t dest[] 結果の面
 */
void copy_board_diagonally(int layer, int pos, stone_t board[][], stone_t dest[])
{
	int i, j;

	if (pos % 5 == 0) {
		// 0, 5, 10, 15を見る
		for (i = 0; i < HIGHT; i++) {
			for (j = 0; j < 4; j++) {
				int index = 5 * j;
				dest[i * 4 + j] = board[i][index]; 
			}
		}
	}
	else if (pos % 3 == 0) {
		// 3, 6, 9, 12を見る
		for (i = 0; i < HIGHT; i++) {
			for (j = 1; j <= 4; j++) {
				int index = 3 * j;
				dest[i * 4 + j] = board[i][index]; 
			}
		}
	}
}

/**
 * 盤面の横方向の面を返す
 * @param int layer 対象の位置(高さ)
 * @param int pos 対象の位置(平面)
 * @param stone_t board[][] 盤面
 * @param stone_t dest[] 結果の面
 */
stone_t *copy_board_latitudinally(int layer, int pos, stone_t board[][], stone_t dest[])
{
	int i, j;
	for (i = 0; i < HIGHT; i++) {
		for (j = 0; j < WIDTH; j++) {
			int index = (pos / 4) * 4 + j;
			dest[i * 4 + j] = board[i][index];
		}
	}
}

/**
 * 盤面の縦方向の面を返す
 * @param int layer 対象の位置(高さ)
 * @param int pos 対象の位置(平面)
 * @param stone_t board[][] 盤面
 * @param stone_t dest[] 結果の面
 */
stone_t *copy_board_longitudinally(int layer, int pos, stone_t board[][], stone_t dest[])
{
	int i, j;
	for (i = 0; i < HIGHT; i++) {
		for (j = 0; j < DEPTH; j++) {
			int index = (pos / 4) * 4 + j;
			dest[i * 4 + j] = board[i][index];
		}
	}
}

/**
 * 平面に対して勝敗をチェックする
 * @param int pos 置かれた位置
 * @param stone_t color 判定する色
 * @param stone_t plane[] 平面
 * @return int win:1, other:0
 */
int check_win(int pos, stone_t color, stone_t plane[])
{
	int win;
	int i;


	// 斜めの処理
	if (pos % 5 == 0) {
		// 0, 5, 10, 15を見る
		win = 1;
		for (i = 0; i < 4; i++) {
			int index = 5 * i;
			if (plane[index] != color) {
				win = 0;
				break;
			}
		}
		if (win) return 1;
	}
	else if (pos % 3 == 0) {
		// 3, 6, 9, 12を見る
		win = 1;
		for (i = 1; i <= 4; i++) {
			int index = 3 * i;
			if (plane[index] != color) {
				win = 0;
				break;
			}
		}
		if (win) return 1;
	}

	// 横
	win = 1;
	for (i = 0; i < WIDTH; i++) {
		int index = (pos / 4) * 4 + i;
		if (plane[index] != color) {
			win = 0;
			break;
		}
	}
	if (win) return 1;

	// 縦
	win = 1;
	for (i = 0; i < DEPTH; i++) {
		int index = (pos % 4) + 4 * i;
		if (plane[index] != color) {
			win = 0;
			break;
		}
	}
	if (win) return 1;

	return 0;
}

/**
 * ボードを上から表示
 * @param stone_t board[][] 盤面
 */
void print_board(stone_t board[][])
{
	int i, j;

	for (i = HIGHT - 1; i >= 0; i--) {
		printf("-----%2d段目-----\n", i + 1);
		printf("|\n");
		for (j = 0; j < AREA; j++) {
			switch (board[i][j]) {
				case NONE:
					printf(" |");
					break;
				case BLACK:
					printf("0|");
					break;
				case WHITE:
					printf("O|\n");
					break;
			}
			if (j % 4 == 0)	printf("\n");
		}
		printf("\n");
	}
}



