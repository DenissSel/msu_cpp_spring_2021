#include <stdio.h>
#include <stdlib.h>
#include "MPI_inverse_functions.h"
#include <time.h>
#include <sys/time.h>
#include <mpi.h>

int main (int argc, char *argv[]) {
	struct timeval time_begin, time_end;
	double *mas, *ans, *mas_new, *buf1, *buf2, mistake, t1, t2;
	int n, m, k, n_tests, rank, size, width, first_line;
	char *filename;
	clock_t end, begin;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	//printf("%d\n", argc);
	if ((argc > 5) or (argc < 4)) {
		printf("Mistake\n");
		return 1;
	}
	
	n = atoi(argv[1]);
	m = atoi(argv[2]);
	if (n % size >= rank + 1) {
		width = n / size + 1;
		// first_line = rank * width;
	}
	else {
		width = n / size;
		// first_line = (n % size) * (width + 1) + (rank - n % size) * width;
	}
	mas = (double*)malloc(width*n*sizeof(double));
	mas_new = (double*)malloc(width*n*sizeof(double));
	ans = (double*)malloc(width*n*sizeof(double));
	buf1 = (double *)malloc(2 * n * sizeof(double));
	buf2 = (double *)malloc(2 * n * sizeof(double));
	if (mas == NULL) return -1;
	if (mas_new == NULL) return -1;
	if (ans == NULL) return -1;
	//printf("In main2\n");
	int res = read_matr(n, width, size, rank, mas, argv);
	if (res == 2) {
		printf("No such formula\n");
		return 1;
	}
	if (res == -1) {
		printf("Not enough!\n");
		return 1;
	}
	for (int i = 0; i < width * n; i ++) 
	{
		mas_new[i] = mas[i];
	}
	/*printf("%d\n", rank);
	for (int i = 0; i < width; i ++) {
		for (int j = 0; j < n; j ++) {
			printf("%lf ", mas[i*n + j]);
		}
		printf("\n");
	}*/
	
	print_matr(n, m, width, size, rank, mas, buf1);
	MPI_Barrier(MPI_COMM_WORLD);
	if (rank == 0) t1 = MPI_Wtime();
	solve(n, m, width, size, rank, mas, ans, buf1, buf2);
	MPI_Barrier(MPI_COMM_WORLD);
	if (rank == 0) 
	{
		t2 = MPI_Wtime();
		printf("Time: %f\n", t2 - t1);
	}
	//printf("\n");
	
	print_matr(n, m, width, size, rank, ans, buf1);
	//printf("\n");
	calculate_mistake(n, width, size, rank, ans, argv);
	MPI_Finalize();
	return 0;
}