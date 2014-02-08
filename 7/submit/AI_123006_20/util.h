#pragma once


/**
 * malloc + 成功確認
 * @param sz 確保するバイト数
 */
void * safe_malloc(size_t sz);

/**
 * calloc + 成功確認
 * @param sz 確保するバイト数
 */
void * safe_calloc(size_t sz);

/**
 * 時間を取得する
 * @return double 時間
 */
double get_time();

/**
 * 乱数値を得る
 * @return double 0 ~ 1
 */
double get_rand();
