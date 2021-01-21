#include "piv_gs_solver.h"
#include "matrix.h"
int solve(matrix_t *m)
{
  if (m == NULL)
    return 1;
  matrix_t *xold = make_matrix(m->rn, 1);
  matrix_t *xnew = make_matrix(m->rn, 1);
  initc_matrix(m);
  initfx(m, xold);

  if (cond(m))
  {
    double err = 10.;
    int i;
    for (i = 0; err > 1; i++)
    {
      if (i % 2 == 0)
      {
        getiter(m, xold, xnew);
        err = errcounter(xold, xnew);
      }
      else
      {
        getiter(m, xnew, xold);
        err = errcounter(xold, xnew);
      }
    }
    put_ans(m, (i / 2) ? xold : xnew);
  }
  else
  {
    put_ans(m, xold);
  }
  free_matrix(xold);
  free_matrix(xnew);
  return 0;
}