#include <stdio.h>
#include <stdlib.h>
#include "functions_eigen.h"
#include <time.h>
#include <sys/time.h>

int main (int argc, char *argv[]) {
	clock_t end, begin;
	double *mas, *ans, *mas_new, mistake, eps, *x, *y;
	int n, m, k, n_tests;
	char *filename;
	//printf("%d\n", argc);
	if ((argc > 7) or (argc < 6)) {
		printf("Mistake\n");
		return 1;
	}
	
	n = atoi(argv[1]);
	m = atoi(argv[2]);
	eps = atof(argv[3]);
	k = atoi(argv[4]);
	mas = (double*)malloc(n*n*sizeof(double));
	mas_new = (double*)malloc(n*n*sizeof(double));
	if (mas == NULL) return -1;
	if (mas_new == NULL) return -1;
	//printf("In main2\n");
	int res = read_matr(n, mas, argv);
	if (res == 2) {
		printf("No such formula\n");
		return 1;
	}
	if (res == -1) {
		printf("Not enough!\n");
		return 1;
	}
	for (int i = 0; i < n*n; i ++) {
		mas_new[i] = mas[i]; 
	}
	write_matr(n, m, mas);
	ans = (double*)malloc(1*sizeof(double));
	x = (double*)malloc(n*sizeof(double));
	y = (double*)malloc(n*sizeof(double));
	
	if (ans == NULL) return -1;
	begin = clock();
	if (solve(mas, n, ans, eps, k, x, y) == -1) {
		printf("Mistake!\n");
		return -1;
	}
	end =  clock();
	printf("\n");
	printf("%d eigen value = %lf\n", k, ans[0]);
	printf("Time = %lf\n", (double)(end-begin)/CLOCKS_PER_SEC);
	free(x);
	free(y);
	free(mas);
	free(mas_new);
	free(ans);
}