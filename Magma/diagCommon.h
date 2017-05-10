#ifndef DIAG_COMMON_H
#define DIAG_COMMON_H

#include "Random64.h"

#define MATRIX(n, p, a) double (*a)[n] = (double(*)[n]) p

double *dmalloc(int n);
int *imalloc(int n);
void mfree(void *p);

void initE(Random64& rnd, int n, double *e);
double getEV(int dir, int n, int i);
void initA(int dir, int n, double *e, double *a, double *w);

void printMatrix(int n, double *a);
void printNorm(int n, double *a);

double wall_seconds();

#endif /* DIAG_COMMON_H */
