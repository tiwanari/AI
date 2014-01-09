#pragma once

#define Q 1.0
#define N_ANT 1000
#define INIT_PHEROMONE N_ANT
#define HUE 1.0
#define STEP_THRESHOLD 200

/**
 * アントコロニー最適化を行う
 * @param n 問題サイズ
 * @param rho 比率
 * @param alpha フェロモンの重み
 * @param beta ヒューリスティックの重み
 * @return int 解けたかどうか
 */
int aco(const int n, const double rho, const double alpha, const double beta);