#include "functions_eigen.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cstdlib>

int read_matr(int n, double *mas, char **args) {
	FILE *f;
	int a, k;
	//printf("In read\n");
	k = atoi(args[5]);
	//printf ("filename = %s\n", args[4]);
	if (k == 0) {
		f = fopen(args[6], "r");
		if ( f == NULL){
			printf("Bad\n");
			fclose(f);
			return - 1;
		}
		printf ("FILE is OPENED\n");
		for (int i = 0; i < n*n; i ++){
			if (fscanf(f, "%lf", &mas[i]) != 1) return -1;
		}
		fclose(f);
		free(f);
		return 0;
	} else if (k < 5) {
		for (int i = 0; i < n; i ++) {
			for (int j = 0; j < n; j ++) {
				mas[i*n+j] = func(k, n, i+1, j+1);
			}
		}
		return 0;
	}
	return 2;
}
double func (int k, int n, int i, int j) {
	if (k == 1) {
		return n-fmax(i,j)+1;
	} else if (k == 2) {
		if (i == j) return 2;
		else if (abs(i-j) == 1) return -1;
		return 0;
	} else if (k == 3) {
		if (i == j) if (i < n) return 1;
		if (i == n) return j;
		if (j == n) return i;
		return 0;
			
	} else if (k == 4) {
		return 1/((double)i+(double)j-1);
	}
	return -1;
}
int find_nenul(int num_stolb, double* mas, int N, int num_str){
	double eps = 1e-27;
	for (int i = num_str; i < N; i ++){
		if (fabs(mas[i*N + num_stolb]) > eps){
			return i;
		}
	}
	return -1;
}
int write_matr (int n, int m, double *mas) {
	if (n < m) return -1;
	for (int i = 0; i < m; i ++){
		for (int j = 0; j < m; j ++){
			printf("%lf  ", mas[i * n + j]);
		}
		printf("\n");
	}
	return 0;
}

double scalar_product(double *X, double *Y, int n)
{
    int i;
    double s = 0;
    for (int i=0; i<n; i++)
        s += X[i]*Y[i];
    return s;
}

int trio_diag(double *E, int n, double *x, double *y)
{
    for (int step = 0; step < n - 2; step ++)
    {
        int len = n - step - 1; int i; int j;
        for (i = 0; i < step + 1; i ++) 
            x[i] = 0;

        for (i = step + 1; i < n; i ++) 
            x[i] = E[i*n + step];

        double xx = sqrt(scalar_product(x, x, n)); 
        x[step + 1] -= xx;
        double xx1 = sqrt(scalar_product(x, x, n)); 
        if (xx1 == 0) continue;
        for (i = 0; i < n; i ++)
            x[i] = x[i] / xx1;

        reflexion(E, x, n, step, xx, y);
        }
        
    return 0;
}

void reflexion(double *A, double *x, int n, int m, double xx, double *y)
{
    
    int i, j;
    for (i = 0; i < n; i ++)
    {
        y[i] = 0;
        for (j = 0; j < n; j ++)
            y[i] += A[i*n + j]*x[j];
    }
    double xy = (scalar_product(x, y, n));
    for (i = 0; i < n; i ++) 
    {
        y[i] = 2*y[i] - 2*xy*x[i];
    }
    for (i = m; i < n; i ++)
        for (j = m; j < n; j ++)
        {
            if (i != m && j != m) 
                A[i*n + j] = A[i*n + j] - y[i]*x[j] - x[i]*y[j];
            if (i == m && j == m + 1) 
                A[i*n + j] = xx;
            if (i == m+1 && j == m) 
                A[i*n + j] = xx;
            if (i == m && j != m && j != m + 1)
                A[i*n + j] = 0;
            if (j == m && i != m && i != m + 1)
                A[i*n + j] = 0;
        }
}
int number_of_sign_changes(double *mas, int n, double lambda) {
	double l_prev, l_now, d, u;
	int Num = 0;
	l_prev = mas[0] - lambda;
	//printf("mas[0] = %lf  lambda = %lf  l = %lf ", mas[0], lambda, l_prev);
	if (fabs(l_prev) < 1e-27) return -1;
	//printf("Hello\n");
	if (l_prev < 0) Num ++;
	for (int i = 1; i < n; i ++) {
		d = mas[i - 1 + i*n];
		u = mas[i + (i-1)*n] / l_prev;
		l_now = mas[i + n*i] - lambda - u*d;
		l_prev = l_now;
		
		if (l_now < 0) {
			Num ++;
			
		}
		//printf("Num = %d  ", Num);
		if (fabs(l_now) < 1e-27) return -1;
	}
	//printf("\n");
	return Num;
}
double calculate_norm (double *mas, int n) {
	double sum, max = 0;
	for (int i = 0; i < n; i ++) {
		sum = 0;
		for (int j = 0; j < n; j ++) {
			sum += fabs(mas[i*n + j]);
		}
		if (max < sum) max = sum;
	}
	return max;
}

int solve(double *mas, int N, double *ans, double eps, int k, double *x, double *y) {
	int num_sign;
	double norm, a, b, c;
	if (trio_diag(mas, N, x, y) != 0) return -1;
	//printf ("\n");
	//write_matr(N, N, mas);
	num_sign = number_of_sign_changes(mas, N, 1);
	//printf ("\n");
	//printf("Num = %d\n", num_sign);
	norm = calculate_norm(mas, N);
	//printf("Norm = %lf\n", norm);
	a = -norm;
	b = norm;
	while (fabs(b-a) > eps) {
		c = (a + b) / 2;
		num_sign = number_of_sign_changes(mas, N, c);
		while (num_sign == -1) {
			c = (b + c) / 2;
			num_sign = number_of_sign_changes(mas, N, c);
		}
		if (num_sign < k) a = c;
		else b = c;
		//printf ("a = %lf   b = %lf c = %lf num = %d\n", a, b, c, num_sign);
	}
	ans[0] = (a + b) / 2.0;
	
	return 0;
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	