/**
 * Negamax法+αβカットを実装したもの
 * @author 03-123006 岩成達哉
 */

#pragma once

#include "board.h"

#define ALPHA -200000.0
#define BETA  200000.0

#define WIN_VAL 100000.0

/**
 * negamax + αβ枝刈りで最善手を返す
 * @param stone_t turn 現在の手番
 * @param stone_t board[][] 盤面
 * @return int 最善手
 */
int negamax(stone_t turn, const stone_t board[HIGHT][AREA]);
