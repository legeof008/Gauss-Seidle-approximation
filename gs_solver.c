#include "piv_gs_solver.h"
#include "matrix.h"
void solve(matrix_t *m, matrix_t *xold, matrix_t *xnew)
{
  write_matrix(m, stdout);
  initc_matrix(m);
  write_matrix(m, stdout);
  initfx(m, xold);
  write_matrix(xold, stdout);
  if (cond(m))
  {
    double err = 10.;
    for (int i = 0; err > 1; i++)
    {
      if (i % 2 == 0)
      {
        printf("Iteracja nr. %d\n", i);
        getiter(m, xold, xnew);
        write_matrix(xnew, stdout);
        err = errcounter(xold, xnew);
        printf("Blad maksymalny jest rowny: %lf\n", err);
      }
      else
      {
        printf("Iteracja nr. %d\n", i);
        getiter(m, xnew, xold);
        write_matrix(xold, stdout);
        err = errcounter(xold, xnew);
        printf("Blad maksymalny jest rowny: %lf\n", err);
      }
    }
    printf("Blad maksymalny jest rowny: %lf\n", err);
    write_matrix(xnew, stdout);
    put_ans(m, xnew);
  }
  else
  {
    printf("Macierz nie spelnia kryterium dominacji!\n");
    write_matrix(xold, stdout);
    put_ans(m, xold);
  }
  printf("Macierz z wynikami:\n");
  write_matrix(m, stdout);
}