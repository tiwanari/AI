
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "aco.h"
#include "util.h"

double** pheromone;	// フェロモン
int N;				// 問題サイズ
double RHO;			// ρ
double ALPHA;		// α
double BETA;		// β

/**
 * 初期化をする
 */
void init()
{
	int i, j;

	// フェロモンの配列を取得
	pheromone = (double**)safe_malloc(sizeof(double*) * N * N);
	for (i = 0; i < N * N; i++) {
		pheromone[i] = (double*)safe_malloc(sizeof(double) * N * N);
		for (j = 0; j < N * N; j++) {
			pheromone[i][j] = INIT_PHEROMONE;
		}
	}

	// 乱数列の初期化
	srand((unsigned)time(NULL));
}

/**
 * 終了処理を行う
 */
void finalize()
{
	int i;
	// フェロモンの配列を解放
	for (i = 0; i < N; i++) {
		free(pheromone[i]);
	}
	free(pheromone);
}

/**
 * 死んでいるクイーンの数を数える
 * @param route 置いた場所
 * @param n 置いた数
 * @return int 死んだ数
 */ 
int count_die(const int* route, const int n)
{
	int i, j;
	int* dies = (int*)safe_calloc(sizeof(int) * n);
	int count = 0;
	const int killed = 1;

	for (i = 0; i < n; i++) {
		int flag = 0;
		// すでに死んでいるなら飛ばす
		if (dies[i] == killed) {
			count++;
			continue;
		}

		for (j = i+1; j < n; j++) {
			int row0 = route[i] / N, col0 = route[i] % N;
			int row1 = route[j] / N, col1 = route[j] % N;

			// 縦，横，斜めにあるか
			if (row0 == row1 || col0 == col1 || abs(row0 - row1) == abs(col0 - col1)) {
				dies[i] = dies[j] = killed;	// 死んだとする
				if (!flag)
					count++;
				flag = 1;
			}
		}
	}

	free(dies);
	return count;
}

/**
 * すでに訪れたかを見る
 * @param route 道筋
 * @param n 置いた数
 * @param next 次に奥市
 */
int is_visited(const int* route, const int n, const int next)
{
	int i;
	for (i = 0; i < n; i++) {
		// きた道にあるか
		if (route[i] == next)
			return 1;
	}
	return 0;
}

/**
 * N回置く
 * @return int* 置いた位置
 */
int* try()
{
	int* route = (int*)safe_malloc(sizeof(int) * N);
	int pos = rand() % (N*N), count = 1;
	const int total = N * N;
	double* possiblity = (double*)safe_calloc(sizeof(double) * N * N);
	double pheromone_sum = 0.0;
	int i;

	route[0] = pos;	// 最初の位置

	while (count < N) {
		double sum = 0.0;
		double val = get_rand();
		double cumulation = 0.0;

		for (i = 0; i < total; i++) {
			if (is_visited(route, count, i))
				possiblity[i] = 0.0;	// すでに通った
			else {
				// huelisticな値を与える
				route[count] = i;
				possiblity[i] = pow(pheromone[pos][i], ALPHA) * pow(HUE / (count_die(route, count + 1) + 1), BETA);
			}
			pheromone_sum += pheromone[pos][i];
			sum += possiblity[i];
		}

		// 進む先を位置を選ぶ
		for (i = 0; i < total; i++) {
			if (is_visited(route, count, i)) {
				continue;
			}
			if ((cumulation += possiblity[i] / sum) > val) {
				route[count++] = pos = i;
				break;
			}
		}
		
	}
	// printf("all pheromone: %f\n", pheromone_sum);
	free(possiblity);
	return route;
}

/**
 * 結果の表示を行う
 * @param route 置いた位置
 */
void show_result(int* route)
{
	int i;
	printf("|-");
	for (i = 0; i < N-1; i++) printf("--");
	printf("|\n|");
	for (i = 0; i < N*N; i++) {
		if (is_visited(route, N, i))	printf("*|");
		else 							printf(" |");
		if ((i + 1) % N == 0) 			printf("\n|");
	}
	for (i = 0; i < N-1; i++) printf("--");
	printf("-|\n");
}

/**
 * フェロモンを更新する
 * @param route 置いた道筋
 * @param ndie 死んでいる数
 */
void update_pheromone(int* route, int ndie)
{
	int i;
	for (i = 0; i < N - 1; i++) {
		pheromone[route[i]][route[i+1]] = pheromone[route[i]][route[i+1]] + Q / ndie;
	}
}

/**
 * フェロモンを蒸発させる
 */
void normalize_pheromone()
{
	int i, j;
	const int total = N * N;
	for (i = 0; i < total; i++) {
		for (j = 0; j < total; j++) {
			pheromone[i][j] *= RHO;
		}
	}
}

/**
 * 解があるか調べフェロモンを更新する
 * @param list 置いた位置の集合
 */
int check_list(int** list)
{
	int i;

	for (i = 0; i < N_ANT; i++) {
		int ndie = count_die(list[i], N);
		if (ndie == 0) {
			show_result(list[i]);
			return 1;
		}
		update_pheromone(list[i], ndie);	// フェロモンの更新
		free(list[i]);
	}
	normalize_pheromone();

	return 0;
}

/**
 * アントコロニー最適化を行う
 * @param n 問題サイズ
 * @param rho 比率
 * @param alpha フェロモンの重み
 * @param beta ヒューリスティックの重み
 * @return int 解けたかどうか
 */
int aco(const int n, const double rho, const double alpha, const double beta)
{
	int** list = (int**)safe_malloc(sizeof(int*) * N_ANT);
	int i;
	int count = 0;
	int res = -1;

	N = n;
	RHO = rho;
	ALPHA = alpha;
	BETA = beta;

	init();
	while (1) {
		++count;
		// printf("%d step(s)\n", ++count);
		for (i = 0; i < N_ANT; i++)
			list[i] = try();

		if (check_list(list)) {
			res = count;
			break;
		}

		// 収束していないと見なす
		if (count >= STEP_THRESHOLD)
			break;
	}
	free(list);
	finalize();

	return res;
}