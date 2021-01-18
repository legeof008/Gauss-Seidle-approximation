#ifndef PIV_GS_SOLVER_H
#define PIV_GS_SOLVER_H

#include "matrix.h"
void initc_matrix(matrix_t *m);
void initfx(matrix_t* m, matrix_t* x);
double errcount(matrix_t *xold, matrix_t* xnew);
#endif