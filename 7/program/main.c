#include <stdio.h>
#include <stdlib.h>
#include "aco.h"

#define NTRY 100

int main(int argc, char **argv)
{
	int N;
	double RHO;
	double ALPHA;
	double BETA;
	int unresolved = 0;
	int i;
	int sum = 0;


	if (argc < 2) {
		fprintf(stderr, "Usage: %s N\n", argv[0]);
		exit(1);
	}
	N = atoi(argv[1]);
	RHO = argc > 2 ? atof(argv[2]) : 0.9;
	ALPHA = argc > 3 ? atof(argv[3]) : 1.0;
	BETA = argc > 4 ? atof(argv[4]) : 1.0;

	for (i = 0; i < 100; i++) {
		int res;
		if ((res = aco(N, RHO, ALPHA, BETA)) == -1)
			unresolved++;
		else
			sum += res;
	}

	printf("%f %f\n", RHO, (double)sum / NTRY);
	fprintf(stderr, "%d %d\n", N, unresolved);
	return 0;
}