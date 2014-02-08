#include <stdio.h>
#include <stdlib.h>
#include "aco.h"

int main(int argc, char **argv)
{
	int N;
	double RHO;
	double ALPHA;
	double BETA;
	int res;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s N [RHO] [ALPHA] [BETA]\n", argv[0]);
		exit(1);
	}
	N = atoi(argv[1]);
	RHO = argc > 2 ? atof(argv[2]) : 0.9;
	ALPHA = argc > 3 ? atof(argv[3]) : 1.0;
	BETA = argc > 4 ? atof(argv[4]) : 1.0;

	printf("N = %d, rho = %f, alpha = %f, beta = %f\n", N, RHO, ALPHA, BETA);

	if ((res = aco(N, RHO, ALPHA, BETA)) == -1)
		printf("unresolved\n");
	else
		printf("in %d steps\n", res);

	return 0;
}