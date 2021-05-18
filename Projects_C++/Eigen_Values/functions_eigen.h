#pragma once

int read_matr(int n, double *mas, char **args);
double func (int k, int n, int i, int j); 
int write_matr (int n, int m, double *mas);
int solve(double *mas, int N, double *ans, double eps, int k, double *x, double *y);
int trio_diag(double *E, int n, double *x, double *y);
double scalar_product(double *X, double *Y, int n);
void reflexion(double *A, double *x, int n, int m, double xx, double *y);
int number_of_sign_changes(double *mas, int n, double lambda);
double calculate_norm (double *mas, int n);