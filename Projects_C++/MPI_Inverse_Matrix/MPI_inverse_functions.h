#pragma once

int read_matr(int n, int width, int size, int rank, double *mas, char **args);
double func (int k, int n, int i, int j); 
int print_matr(int n, int k, int width, int size, int rank, double *mas, double *buf1);
int solve(int n, int k, int size, int width, int rank, double *mas, double *ans, double *buf1, double *buf2);
int calculate_mistake(int n, int width, int size, int rank, double *mas, char **args);

