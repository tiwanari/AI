/**
 * 盤面についての処理をまとめたもの
 * @author 03-123006 岩成達哉
 */

#include <stdio.h>
#include <string.h>
#include "board.h"

/**
 * 盤面を初期化する
 * @param stone_t board[][] 初期化する盤面
 */
void init_board(stone_t board[HIGHT][AREA])
{
	// int i, j;
	// for (i = 0; i < HIGHT; i++)
	// 	for (j = 0; j < AREA; j++)
	// 		board[i][j] = NONE;

	memset(board, NONE, sizeof(stone_t) * HIGHT * AREA);
}

/**
 * 平面を表示(debug用)
 * @param stone_t plane[] 平面
 */
void print_plane(const stone_t plane[AREA])
{
	int i;
	for (i = 0; i < AREA; i++) {
		printf("%s|", get_stone_image(plane[i]));
		if ((i+1) % WIDTH == 0)	printf("\n");
	}
}

/**
 * ボードを上から表示
 * @param stone_t board[][] 盤面
 */
void print_board(const stone_t board[HIGHT][AREA])
{
	int i;

	for (i = HIGHT - 1; i >= 0; i--) {
		printf("---%2d段目---\n", i + 1);
		print_plane(board[i]);
	}
}

/**
 * 指定した位置におけるか
 * @param int pos
 * @param stone_t board[][]
 * @return int ture:1, false:0
 */
int is_putable(int pos, const stone_t board[HIGHT][AREA])
{
	return board[3][pos] == NONE;
}

/**
 * 指定した位置に配置
 * @param int pos 置く位置
 * @param stone_t color 置く色
 * @param stone_t board[][]
 * @return int 置いた層
 */
int put_stone(int pos, stone_t color, stone_t board[HIGHT][AREA])
{
	int i;
	for (i = 0; i < HIGHT; i++) {
		if (board[i][pos] == NONE) {
			board[i][pos] = color;
			break;
		}
	}
	return i;
}

/**
 * 指定した位置の石を取り出す(Undo)
 * @param int pos 取り出す位置
 * @param stone_t board[][]
 * @return int 取り除いた層
 */
int pick_stone(int pos, stone_t board[HIGHT][AREA])
{
	int i;
	for (i = HIGHT - 1; i >= 0; i--) {
		if (board[i][pos] != NONE) {
			board[i][pos] = NONE;
			break;
		}
	}
	return i;
}

/**
 * 合法手を作る
 * @param stone_t board[][] 盤面
 * @param int hands[AREA] 合法手の格納先
 * @return int 合法手の数
 */
int get_legal_hands(const stone_t board[HIGHT][AREA], int hands[AREA])
{
	int count = 0;
	int i;

	for (i = 0; i < AREA; i++)
		if (board[3][i] == NONE)
			hands[count++] = i;

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
 * 全て埋まっているか
 * @param stone_t board[][] 盤面
 * @return int true:1, false:0
 */
int is_full(const stone_t board[HIGHT][AREA])
{
	int i;

	for (i = 0; i < AREA; i++)
		if (board[3][i] == NONE)
			return 0;

	return 1;
}

/**
 * 盤面のコピー
 * @param stone_t board[][] コピー元
 * @param stone_t dest[][] コピー先
 */
void copy_board(const stone_t board[HIGHT][AREA], stone_t dest[HIGHT][AREA])
{
	// int i, j;
	// for (i = 0; i < HIGHT; i++)
	// 	for (j = 0; j < AREA; j++)
	// 		dest[i][j] = board[i][j];

	memcpy(dest, board, sizeof(stone_t) * HIGHT * AREA);
}

/**
 * 盤面の対角線方向の面を返す
 * @param int pos 対象の位置(平面)
 * @param stone_t board[][] 盤面
 * @param stone_t dest[] 結果の面
 */
void copy_board_diagonally(int pos, const stone_t board[HIGHT][AREA], stone_t dest[AREA])
{
	int i, j;
	
	if (pos % 5 == 0) {
		// 0, 5, 10, 15をコピー
		for (i = 0; i < HIGHT; i++) {
			for (j = 0; j < 4; j++) {
				int index = 5 * j;
				dest[i * 4 + j] = board[i][index]; 
			}
		}
	}
	else if (pos % 3 == 0) {
		// 3, 6, 9, 12をコピー
		for (i = 0; i < HIGHT; i++) {
			for (j = 1; j <= 4; j++) {
				int index = 3 * j;
				dest[i * 4 + (j-1)] = board[i][index]; 
			}
		}
	}
}

/**
 * 盤面の横方向の面を返す
 * @param int pos 対象の位置(平面)
 * @param stone_t board[][] 盤面
 * @param stone_t dest[] 結果の面
 */
void copy_board_latitudinally(int pos, const stone_t board[HIGHT][AREA], stone_t dest[AREA])
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
 * @param int pos 対象の位置(平面)
 * @param stone_t board[][] 盤面
 * @param stone_t dest[] 結果の面
 */
void copy_board_longitudinally(int pos, const stone_t board[HIGHT][AREA], stone_t dest[AREA])
{
	int i, j;
	for (i = 0; i < HIGHT; i++) {
		for (j = 0; j < DEPTH; j++) {
			int index = (pos % 4) + 4 * j;
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
int check_win_plane(int pos, stone_t color, const stone_t plane[AREA])
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
 * ゲームが終了したかを調べる
 * @param int layer 置いたの位置(高さ)
 * @param int pos 置いたの位置(平面)
 * @param stone_t color 置いた色
 * @param stone_t board[][] 盤面
 * @return int true:1, false:0
 */
int check_win(int layer, int pos, stone_t color, const stone_t board[HIGHT][AREA])
{
	stone_t temp[AREA];
	int trans_pos;	// 平面に分けた時の位置
	
	// 平面のチェック
	if (check_win_plane(pos, color, board[layer]))
		return 1;

	// 斜めのチェック
	if (is_on_diagonal_line(pos)) {
		copy_board_diagonally(pos, board, temp);
		if (pos % 5 == 0)
			trans_pos = layer * 4 + pos / 5;
		else
			trans_pos = layer * 4 + pos / 3 - 1;
		if (check_win_plane(trans_pos, color, temp))
			return 1;
	}
	
	// 横のチェック
	copy_board_latitudinally(pos, board, temp);
	trans_pos = layer * 4 + pos % 4;
	if (check_win_plane(trans_pos, color, temp))
		return 1;

	// 縦のチェック
	copy_board_longitudinally(pos, board, temp);
	trans_pos = layer * 4 + pos / 4;
	if (check_win_plane(trans_pos, color, temp))
		return 1;

	return 0;
}

/**
 * ゲームオーバーの手か
 * @param int pos 手
 * @param stone_t turn 現在の手番
 * @param stone_t board[][] 盤面
 * @return int true:1, false:0
 */
int is_terminate_hand(int pos, stone_t turn, const stone_t board[HIGHT][AREA])
{
	stone_t copy[HIGHT][AREA];
	int layer;
	copy_board(board, copy);

	layer = put_stone(pos, turn, copy);	// 置いてみる

	return check_win(layer, pos, turn, copy) || is_full(copy);
}

/**
 * リーチの数を返す
 * @param stone_t color リーチを調べる色
 * @param stone_t board[][] 盤面
 * @return int リーチの数
 */
// int get_reach(stone_t color, const stone_t board[HIGHT][AREA])
// {
// 	return 0;
// }

/**
 * 石のイメージを返す
 * @param stone_t color 石の色
 * @return char* 文字列表現
 */
char* get_stone_image(stone_t color)
{
	switch (color) {
		case NONE:
			return "  ";
		case BLACK:
			return "0 ";
		case WHITE:
			return "O ";
	}
	return "  ";
}
