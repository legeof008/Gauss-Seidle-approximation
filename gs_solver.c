#include "piv_gs_solver.h"
#include "matrix.h"
void solve(matrix_t* m, matrix_t* xold, matrix_t* xnew)
{
    write_matrix(m, stdout);
    initc_matrix(m);
    write_matrix(m, stdout);
    initfx(m, xold);
    write_matrix(xold, stdout);
    double err = 10.;
    for(int i = 0; err > 1; i++)
    {
      if (i % 2 == 0)
      {
        printf("Iteracja nr. %d\n",i);
        getiter(m, xold, xnew);
        write_matrix(xnew, stdout);
        err = errcounter(xold, xnew);
        printf("Blad maksymalny jest rowny: %lf\n", err);
      }
      else
      {
        printf("Iteracja nr. %d\n",i);
        getiter(m, xnew, xold);
        write_matrix(xold, stdout);
        err = errcounter(xold, xnew);
        printf("Blad maksymalny jest rowny: %lf\n", err );
      }
      
    }
    
    write_matrix(xnew, stdout);
    printf("Blad maksymalny jest rowny: %lf\n", err);
}