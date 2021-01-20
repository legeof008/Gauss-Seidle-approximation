#ifndef PIV_GS_SOLVER_H
#define PIV_GS_SOLVER_H

#include "matrix.h"
void initc_matrix(matrix_t *m);
void initfx(matrix_t* m, matrix_t* x);
double errcount(matrix_t *xold, matrix_t* xnew);
void iter(matrix_t* m, matrix_t* xold, matrix_t* xnew);
int cond2(matrix_t* m);
int cond1(matrix_t* m);
double rowsum(matrix_t *m, int rn, int diag);
void getiter(matrix_t *m, matrix_t *xold, matrix_t *xnew);
double errcounter(matrix_t *xold, matrix_t *xnew);
void solve(matrix_t* m, matrix_t* xold, matrix_t* xnew);
#endif