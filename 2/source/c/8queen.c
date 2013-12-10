#include <stdio.h>
#include <stdlib.h>

#define B 8

int check(int i, int j, int k, int l, int m, int n, int o, int p)
{
    return (i != j) && (i != k) && (i != l) && (i != m) && (i != n) && (i != o) && (i != p)
        && (j != k) && (j != l) && (j != m) && (j != n) && (j != o) && (j != p)
        && (k != l) && (k != m) && (k != n) && (k != o) && (k != p)
        && (l != m) && (l != n) && (l != o) && (l != p)
        && (m != n) && (m != o) && (m != p)
        && (n != o) && (n != p)
        && (o != p)
        && (abs(i - j) != 1) && (abs(j - k) != 1) && (abs(k - l) != 1) && (abs(l - m) != 1) 
        && (abs(m - n) != 1) && (abs(n - o) != 1) && (abs(o - p) != 1)
        && (abs(i - k) != 2) && (abs(j - l) != 2) && (abs(k - m) != 2) && (abs(l - n) != 2) 
        && (abs(m - o) != 2) && (abs(n - p) != 2)
        && (abs(i - l) != 3) && (abs(j - m) != 3) && (abs(k - n) != 3) && (abs(l - o) != 3) 
        && (abs(m - p) != 3) 
        && (abs(i - m) != 4) && (abs(j - n) != 4) && (abs(k - o) != 4) && (abs(l - p) != 4) 
        && (abs(i - n) != 5) && (abs(j - o) != 5) && (abs(k - p) != 5)
        && (abs(i - o) != 6) && (abs(j - p) != 6) 
        && (abs(i - p) != 7);
}
        
        
int main(void)
{
    int i, j, k, l, m, n, o, p;
    
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            for (k = 0; k < 8; k++) {
                for (l = 0; l < 8; l++) {
                    for (m = 0; m < 8; m++) {
                        for (n = 0; n < 8; n++) {
                            for (o = 0; o < 8; o++) {
                                for (p = 0; p < 8; p++) {
                                    if (check(i, j, k, l, m, n, o, p)) {
                                        printf("%d %d %d %d %d %d %d %d\n", i, j, k, l, m, n, o, p);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}