#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

/**
 * malloc + 成功確認
 * @param sz 確保するバイト数
 */
void * safe_malloc(size_t sz)
{
	void * a = malloc(sz);
	if (a == NULL) {
		perror("malloc");
		exit(1);
	}
	return a;
}

/**
 * calloc + 成功確認
 * @param sz 確保するバイト数
 */
void * safe_calloc(size_t sz)
{
	void * a = calloc(1, sz);
	if (a == NULL) {
		perror("calloc");
		exit(1);
	}
	return a;
}

/**
 * 時間を取得する
 * @return double 時間
 */
double get_time()
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return tv.tv_sec + tv.tv_usec * 1e-6;
}

/**
 * 乱数値を得る
 * @return double 0 ~ 1
 */
double get_rand()
{
	return rand() / (double) RAND_MAX;
}

/**
 * 累乗を返す
 * @param num 掛ける値
 * @param times 掛ける回数
 * @return double 結果
 */
double ipow(double num, int times)
{
	double res = 1.0;
	int i;

	for (i = 0; i < times; i++)
		res *= num;
	return res;
}