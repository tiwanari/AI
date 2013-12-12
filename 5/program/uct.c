#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "uct.h"
#include "board.h"

int PLAYOUT_MAX;
int EXPAND_THRESHOLD;
double C;

/**
 * ノードを作成して返す
 * @return node_t 作成したノード
 */
node_t init_node()
{
	node_t node;

	if ((node = (node_t)malloc(sizeof(struct node))) == NULL) {
		fprintf(stderr, "Error: memory allocation\n");
		exit(1);
	}
	node->moth = NULL;
	node->nchildren = 0;
	node->playout = 0;
	node->win = 0;

	return node;
}

/**
 * ノードを解法する
 * @param node_t mother 親
 */
void free_nodes(node_t mother)
{
	int i;
	for (i = 0; i < mother->nchildren; i++) {
		free_nodes(mother->children[i]);
	}
	free(mother);
}

/**
 * プレイアウトを行うシミュレーション関数
 * @param stone_t mycolor 自分の色
 * @param stone_t turn 現在の手番
 * @param stone_t board[][] 盤面
 * @return win:1, other:0
 */
int playout(stone_t mycolor, stone_t turn, stone_t board[HIGHT][AREA])
{
	stone_t t = turn;

	for (; ; t = REVERSE(t)) {
		int hands[AREA];
		int nhands = get_legal_hands(board, hands);
		int index = rand() % nhands;
		int layer = put_stone(hands[index], t, board);
		
		if (check_win(layer, hands[index], t, board)) {
			if (t == mycolor)
				return 1;
			else
				return 0;	// 勝ったときだけカウント
		}
		if (is_full(board))
			return 0;
	}
}

/**
 * 結果を親に伝播する
 * @param node_t node 変更を行ったノード
 * @param int playout プレイアウトの増分
 * @param int win 勝利数の増分
 */
void propagate_result(node_t node, int playout, int win)
{
	node_t temp;
	for (temp = node; temp != NULL; temp = temp->moth) {
		temp->playout += playout;
		temp->win += win;
	}
}

/**
 * プレイアウトの合計を返す
 * @param node_t node いずれかの子
 * @return int プレイアウトの合計
 */
int get_total_playout(node_t node)
{
	node_t temp;
	for (temp = node; temp->moth != NULL; temp = temp->moth) {}

	return temp->playout;
}

/**
 * ノードを展開する
 * @param node_t mother 上位のノード
 * @param stone_t mycolor 自分の色
 * @param stone_t turn 現在の手番
 * @param stone_t board 現在の盤面
 */
void expand_child(node_t mother, stone_t mycolor, stone_t turn, const stone_t board[HIGHT][AREA])
{
	int hands[AREA];
	int total_playout = 0;
	int total_win = 0;
	int layer;
	int i;
	
	// 展開済みなら終了
	if (mother->nchildren != 0) return ;

	mother->nchildren = get_legal_hands(board, hands);

	for (i = 0; i < mother->nchildren; i++) {
		stone_t copy[HIGHT][AREA];
		copy_board(board, copy);	// 盤面をコピーして使う
		
		mother->children[i] = init_node();
		mother->children[i]->moth = mother;
		mother->children[i]->pos = hands[i];
		total_playout += ++(mother->children[i]->playout);
		
		// 置く
		layer = put_stone(hands[i], turn, copy);

		// この時点で勝利か
		if (check_win(layer, hands[i], turn, copy)) {
			total_win += ++(mother->children[i]->win);
		}
		// 引き分け
		else if(is_full(copy)) {
			continue;
		}

		total_win += mother->children[i]->win = playout(mycolor, REVERSE(turn), copy);
	}
	propagate_result(mother, total_playout, total_win);	// 上位にも反映
}

/**
 * プレイアウトを行う子供を選択する
 * @param node_t mother 上位のノード
 * @param stone_t board[][] 現在の盤面
 * @return node_t プレイアウト行う子供
 */
node_t select_child(node_t mother, const stone_t board[HIGHT][AREA])
{
	double temp_ucb;
	double max_ucb = -INIFINITY;
	double winning_rate;
	int max_ucb_index;
	int i;

	// ucbが最も大きい子供を探す
	for (i = 0; i < mother->nchildren; i++) {
		// 勝率の計算
		winning_rate 
		= (double)mother->children[i]->win / mother->children[i]->playout;

		temp_ucb = ucb(winning_rate, get_total_playout(mother), mother->children[i]->playout);
		if (max_ucb < temp_ucb) {
			max_ucb = temp_ucb;
			max_ucb_index = i;
		}
	}

	return mother->children[max_ucb_index];
}

/**
 * UCTによって最善手を求める
 * @param stone_t turn 現在の手番
 * @param stone_t board[][] 盤面
 * @return int 最善手
 */
int uct(stone_t turn, const stone_t board[HIGHT][AREA])
{
	node_t root = init_node();	// 現在のノード
	double best_rate = -INIFINITY;
	int best_hand;
	int i;

	// 乱数列の初期化
	srand((unsigned int)time(NULL));

	// 子供を作る
	expand_child(root, turn, turn, board);

	// UCB値の計算と選択
	while (root->playout < PLAYOUT_MAX) {
		node_t candidate = select_child(root, board); // 最善手を選ぶ
		stone_t next[HIGHT][AREA];
		int win;
		int layer;
		stone_t cur_turn = turn;

		// ボードをコピー
		copy_board(board, next);
		layer = put_stone(candidate->pos, cur_turn, next);
		
		// 勝利判定
		if (check_win(layer, candidate->pos, cur_turn, next)) {
			propagate_result(candidate, 1, 1);
			continue;
		}
		// 終了判定
		else if (is_full(next)) {
			propagate_result(candidate, 1, 0);
			continue;
		}
		// 終端でなく一定回数のプレイアウトを行っているなら展開
		else if (candidate->playout >= EXPAND_THRESHOLD) {
			cur_turn = REVERSE(cur_turn);	// 手番を入れ替える

			// 展開
			expand_child(candidate, cur_turn, cur_turn, next);
			candidate = select_child(candidate, next);	// その中で手を選ぶ

			// 手を進める
			put_stone(candidate->pos, cur_turn, next);
		}
		// プレイアウトを行う
		win = playout(turn, REVERSE(cur_turn), next);
		propagate_result(candidate, 1, win);	// 上位にも反映
	}

	for (i = 0; i < root->nchildren; i++) {
		double winning_rate
			= (double)root->children[i]->win / root->children[i]->playout;

		printf("pos(%2d):%f\n", i, winning_rate);
		if (best_rate < winning_rate) {
			best_rate = winning_rate;
			best_hand = root->children[i]->pos;
		}
	}

	// ノードを解放する
	free_nodes(root);

	// 最善手を返す
	return best_hand;
}