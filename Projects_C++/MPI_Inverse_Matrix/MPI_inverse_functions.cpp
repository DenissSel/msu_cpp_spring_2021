#include "MPI_inverse_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cstdlib>
#include <mpi.h>

int read_matr(int n, int width, int size, int rank, double *mas, char **args)
{
	FILE *f;
	int a, k;
	//printf("In read\n");
	k = atoi(args[3]);
	//printf ("filename = %s\n", args[4]);
	if (k == 0)
	{
		f = fopen(args[4], "r");
		if (f == NULL)
		{
			printf("Bad\n");
			fclose(f);
			return -1;
		}
		printf("FILE is OPENED\n");
		for (int i = 0; i < width * n; i++)
		{
			if (fscanf(f, "%lf", &mas[i]) != 1)
				return -1;
		}
		fclose(f);
		return 0;
	}
	else if (k < 5)
	{
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < n; j++)
			{
				mas[i * n + j] = func(k, n, rank + 1 + i * size, j + 1);
			}
		}
		return 0;
	}
	return 2;
}
int print_matr(int n, int k, int width, int size, int rank, double *mas, double *buf1)
{
	MPI_Status status;
	for (int i = 0; i < k; i++)
	{
		if (rank == 0)
		{
			//printf("\n");

			if (i % size == 0)
			{
				for (int j = 0; j < k; j++)
				{
					printf("%lf  ", mas[(i / size) * n + j]);
				}
			}
			else
			{
				MPI_Recv(buf1, n, MPI_DOUBLE, i % size, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
				for (int j = 0; j < k; j++)
				{
					printf("%lf  ", buf1[j]);
				}
			}
			printf("\n");
		}
		else if (rank == i % size)
		{
			// buf1 = (double *)malloc(n * sizeof(double));
			for (int j = 0; j < n; j++)
			{
				buf1[j] = mas[i * n + j];
			}
			MPI_Send(buf1, n, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
		}
	}

	return 0;
}
double func(int k, int n, int i, int j)
{
	if (k == 1)
	{
		return n - fmax(i, j) + 1;
	}
	else if (k == 2)
	{
		return fmax(i, j);
	}
	else if (k == 3)
	{
		return fabs(i - j);
	}
	else if (k == 4)
	{
		return 1 / ((double)i + (double)j - 1);
	}
	return -1;
}

int solve(int n, int k, int width, int size, int rank, double *mas, double *ans, double *buf1, double *buf2)
{
	MPI_Status status;
	int first_line, i = 0, tmp, tmp_out, dist;
	double lambda, buf_tmp;
	//FILE *fp;
	char filename[20];
	for (int j = 0; j < width; j++)
	{
		for (int i = 0; i < n; i++)
		{
			if (i == j * size + rank)
				ans[j * n + i] = 1;
			else
				ans[j * n + i] = 0;
		}
	}
	for (int i = 0; i < n; i++)
	{
		/*tmp = № строки с ненулевым элементом
		
		MPI_Allgather(&tmp, &tmp_out ,.., MPI_MIN)
		if (i != tmp_out) {
			if (i % size == tmp_out & size && i % size == rank) {
				поменять строки местами внутри одного процесса
			} else {
				if (i % size == rank) поменять строки между процессами
			}
		} */
		tmp = n + 1;

		if (rank >= i % size)
			dist = 0;
		else
			dist = 1;

		for (int j = i / size + dist; j < width; j++)
		{
			if (mas[j * n + i] != 0)
			{
				tmp = j * size + rank;
				break;
			}
		}

		MPI_Reduce(&tmp, &tmp_out, 1, MPI_INT, MPI_MIN, i % size, MPI_COMM_WORLD);
		MPI_Bcast(&tmp_out, 1, MPI_INT, i % size, MPI_COMM_WORLD);
		//printf("tmp_out = %d\n", tmp_out);
		if (i != tmp_out)
		{

			if (((i % size) == (tmp_out % size)) && ((i % size) == rank))
			{
				for (int j = 0; j < n; j++)
				{
					buf_tmp = mas[(i / size) * n + j];
					mas[(i / size) * n + j] = mas[(tmp_out / size) * n + j];
					mas[(tmp_out / size) * n + j] = buf_tmp;
				}
				for (int j = n; j < 2 * n; j++)
				{
					//mas[(i / size) * n + j]  = mas[(i / size) * n + j] / mas[(i / size) * n + i];
					buf_tmp = ans[(i / size) * n + j - n];
					ans[(i / size) * n + j - n] = ans[(tmp_out / size) * n + j - n];
					ans[(tmp_out / size) * n + j - n] = buf_tmp;
				}
			}
			else
			{
				if (rank == tmp_out % size)
				{
					for (int j = 0; j < n; j++)
					{
						buf1[j] = mas[(tmp_out / size) * n + j];
					}
					for (int j = n; j < 2 * n; j++)
					{
						//mas[(i / size) * n + j]  = mas[(i / size) * n + j] / mas[(i / size) * n + i];
						buf1[j] = ans[(tmp_out / size) * n + j - n];
					}
					MPI_Send(buf1, 2 * n, MPI_DOUBLE, i % size, 0, MPI_COMM_WORLD);
					MPI_Recv(buf2, 2 * n, MPI_DOUBLE, i % size, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
					for (int j = 0; j < n; j++)
					{
						mas[(tmp_out / size) * n + j] = buf2[j];
					}
					for (int j = n; j < 2 * n; j++)
					{
						//mas[(i / size) * n + j]  = mas[(i / size) * n + j] / mas[(i / size) * n + i];
						ans[(tmp_out / size) * n + j - n] = buf2[j];
					}
				}
				if (rank == i % size)
				{
					for (int j = 0; j < n; j++)
					{
						buf2[j] = mas[(i / size) * n + j];
					}
					for (int j = n; j < 2 * n; j++)
					{
						//mas[(i / size) * n + j]  = mas[(i / size) * n + j] / mas[(i / size) * n + i];
						buf2[j] = ans[(i / size) * n + j - n];
					}
					MPI_Recv(buf1, 2 * n, MPI_DOUBLE, tmp_out % size, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
					MPI_Send(buf2, 2 * n, MPI_DOUBLE, tmp_out % size, 0, MPI_COMM_WORLD);
					for (int j = 0; j < n; j++)
					{
						mas[(i / size) * n + j] = buf1[j];
					}
					for (int j = n; j < 2 * n; j++)
					{
						//mas[(i / size) * n + j]  = mas[(i / size) * n + j] / mas[(i / size) * n + i];
						ans[(i / size) * n + j - n] = buf1[j];
					}
				}
			}
		}

		//good
		if (rank == i % size)
		{
			lambda = mas[(i / size) * n + i];
			for (int j = 0; j < n; j++)
			{
				mas[(i / size) * n + j] = mas[(i / size) * n + j] / lambda;
				buf1[j] = mas[(i / size) * n + j];
			}
			for (int j = n; j < 2 * n; j++)
			{
				//mas[(i / size) * n + j]  = mas[(i / size) * n + j] / mas[(i / size) * n + i];
				ans[(i / size) * n + j - n] = ans[(i / size) * n + j - n] / lambda;
				buf1[j] = ans[(i / size) * n + j - n];
			}

			MPI_Bcast(buf1, 2 * n, MPI_DOUBLE, i % size, MPI_COMM_WORLD);
			//sprintf(filename, "file_%d.out", rank);
			//fp = fopen(filename, "a");
			//fprintf(fp, "buf1: ");
			/*for (int l = 0; l < 2 * n; l++)
			{
				fprintf(fp, "%lf ", buf1[l]);
			}
			fprintf(fp, "\n");*/
			for (int j = i / size + 1; j < width; j++)
			{
				lambda = mas[j * n + i] / buf1[i];
				//fprintf(fp, "lambda = %lf \n mas  ", lambda);
				for (int l = i; l < n; l++)
				{
					mas[j * n + l] -= lambda * buf1[l];
					//fprintf(fp, "%lf ", mas[j * n + l]);

					//fprintf(fp, "ans  %lf ", ans[j * n + l]);
				}
				//fprintf(fp, "\n ans  ");
				for (int l = 0; l < n; l++)
				{
					ans[j * n + l] -= lambda * buf1[l + n];
					//fprintf(fp, "%lf ", ans[j * n + l]);
				}
				//fprintf(fp, "\n");
			}
			//fprintf(fp, "\n");
			//fprintf(fp, "\n");
			//fclose(fp);
		}
		else
		{
			MPI_Bcast(buf1, 2 * n, MPI_DOUBLE, i % size, MPI_COMM_WORLD);
			/*sprintf(filename, "file_%d.out", rank);
			fp = fopen(filename, "a");
			fprintf(fp, "buf1: ");
			for (int l = 0; l < 2 * n; l++)
			{
				fprintf(fp, "%lf ", buf1[l]);
			}
			fprintf(fp, "\n");*/
			for (int j = i / size; j < width; j++)
			{
				lambda = mas[j * n + i] / buf1[i];
				//fprintf(fp, "lambda = %lf \nmas  ", lambda);
				for (int l = i; l < n; l++)
				{
					mas[j * n + l] -= lambda * buf1[l];
					//fprintf(fp, "%lf ", mas[j * n + l]);
				}
				//fprintf(fp, "\n ans  ");
				for (int l = 0; l < n; l++)
				{
					ans[j * n + l] -= lambda * buf1[l + n];
					//fprintf(fp, "%lf ", ans[j * n + l]);
				}
				//fprintf(fp, "\n");
			}
			//fprintf(fp, "\n");
			//fprintf(fp, "\n");
			//fclose(fp);
		}
	}
	//inverse steps of Gauss method
	for (int i = n - 1; i > -1; i--)
	{
		if (rank == i % size)
		{
			for (int j = 0; j < n; j++)
			{
				buf1[j] = ans[i / size * n + j];
			}
		}
		MPI_Bcast(buf1, 2 * n, MPI_DOUBLE, i % size, MPI_COMM_WORLD);
		for (int j = 0; j < i / size; j++)
		{
			for (int l = 0; l < n; l++)
			{
				ans[j * n + l] -= mas[j * n + i] * buf1[l];
			}
			mas[j * n + i] = 0;
		}
	}
	/*sprintf(filename, "file_%d.out", rank);
	fp = fopen(filename, "a");
	fprintf(fp, "ANS: \n");
	for (int l = 0; l < width; l++)
	{
		for (int j = 0; j < n; j ++)
		{
			fprintf(fp, "%lf ", ans[l*n + j]);
		}
		fprintf(fp, "\n");
	}
	fprintf(fp, "\n");
	fclose(fp);*/
	return 0;
}

int calculate_mistake(int n, int width, int size, int rank, double *mas, char **args)
{
	//FILE *fp;
	double sum = 0, element;
	int k = atoi(args[3]);
	double mistake;
	//char filename[20];
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < n; j++)
		{
			element = 0;
			for (int l = 0; l < n; l++)
			{
				element += mas[i * n + l] * func(k, n, 1 + l, j + 1);
			}
			if (j == i * size + rank)
				element -= 1;
			sum += element * element;
		}
	}
	/*sprintf(filename, "file_%d.out", rank);
	fp = fopen(filename, "a");
	fprintf(fp, "mistake = %lf\n", sum);
	fclose(fp);*/
	MPI_Reduce(&sum, &mistake, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	if (rank == 0)
		printf("MISTAKE = %e\n", mistake);
	return 0;
}
