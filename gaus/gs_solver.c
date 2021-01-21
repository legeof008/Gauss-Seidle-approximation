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
  write_matrix(m, stdout);
  if (cond(m))
  {
    double err = 10.;
    int i;
    for (i = 0; err > 1; i++)
    {

      getiter(m, xold, xnew);
      err = errcounter(xold, xnew);
      xold = copy_matrix(xnew);
    }

    put_ans(m, xnew);
  }
  else
  {
    printf("------------------------------------------\n");
    printf("Kryteria zbieznosci nie zostaly spelnione!\n");
    printf("------------------------------------------\n");
    put_ans(m, xold);
  }
  free_matrix(xold);
  free_matrix(xnew);
  return 0;
}
/*
int main(int argc, char **argv)
{
  FILE *in = fopen(argv[1], "r");
  matrix_t *m;
  m = read_matrix(in);
  write_matrix(m, stdout);
  solve(m);
  write_matrix(m, stdout);
  return 0;
}*/