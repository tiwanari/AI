#include <stdio.h>
#include <string.h>

#define N 10

void printQueen(int queen[N])
{
    int i;
    
    printf("%d queen : ", N);
    for (i = 0; i < N; i++) {
        printf("%d ", queen[i]);
    }
    printf("\n");
}

/* (i,j)の位置から縦横斜めの方向にある board のすべての要素の値に dを加える */
void changeBoard(int board[N][N], int i, int j, int d)
{
    int k;
    
    for (k = 0; k < N; k++) { 
        board[i][k] += d;             /* 横方向 */
        board[k][j] += d;             /* 縦方向 */
    }
    if (i > j) {
        for (k = 0; k < N-(i-j); k++) {
            board[k+(i-j)][k] += d;   /* 右下がり斜め方向 (i > jのとき） */
        }
    } else {
        for (k = 0; k < N-(j-i); k++) {
            board[k][k+(j-i)] += d;   /* 右下がり斜め方向 (i <= jのとき） */
        }
    }
    if (i+j < N) {
        for (k = 0; k <= i+j; k++) {
            board[i+j-k][k] += d;     /* 左下がり斜め方向（i +j < Nのとき） */
        }
    } else {
        for (k = i+j-N+1; k < N; k++) {
            board[i+j-k][k] += d;     /* 左下がり斜め方向（i+j >= Nのとき） */
        }
    }
}

/* i 行目のクイーンの位置を設定して， setQueen(queen, board, i+1) を呼び出す
　ただし， i == N のときは，一つの解が queen に入っているのでそれを表示するだけである */
void setQueen(int queen[N], int board[N][N], int i)
{
    int j;
    
    if (i == N) {                              /* 解が見つかった */
        printQueen(queen);
        return;
    }
    
    for (j = 0; j < N; j++) {
        if (board[i][j] == 0) {                /* (i,j) の位置に置けるならば */
            queen[i] = j;                      /* (i,j) の位置にクイーンを置く */
            changeBoard(board, i, j, +1);      /* (i,j) から縦横斜めの方向のboard値を+1する */
            setQueen(queen, board, i+1);       /* i+1 行目のクイーンの位置を決める */
            changeBoard(board, i, j, -1);      /* (i,j) から縦横斜めの方向のboard値を元に戻す */
        }
    }
}

void findSolution()
{
    int queen[N];
    int board[N][N];
    
    memset(board, 0, sizeof(board));
    setQueen(queen, board, 0);
}

main()
{
    findSolution();
}