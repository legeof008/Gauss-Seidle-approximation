#include "matrix.h"
#include "piv_gs_solver.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  FILE *in;
  if (argc > 1 && (in = fopen(argv[1], "r")) != NULL)
  {
    matrix_t *m = read_matrix(in);
    // wszystko ponizej tego komentarza do nastepnego komentarza do bzdury do testowania
    matrix_t *xold = make_matrix(m->rn, 1);
    matrix_t *xnew = make_matrix(m->rn, 1);
    solve(m,xold,xnew);
    /*write_matrix(m, stdout);
    initc_matrix(m);
    write_matrix(m, stdout);
    initfx(m, xold);
    initfx(m, xnew);
    write_matrix(xold, stdout);
    double err;
    for (int i = 0; i <= 11; i++)
    {
      if (i % 2 == 0)
      {
        printf("Iteracja nr. %d\n",i);
        getiter(m, xold, xnew);
        write_matrix(xnew, stdout);
        err = errcount(xold, xnew);
        printf("Blad maksymalny jest rowny: %lf\n", err);
      }
      else
      {
        printf("Iteracja nr. %d\n",i);
        getiter(m, xnew, xold);
        write_matrix(xold, stdout);
        err = errcount(xold, xnew);
        printf("Blad maksymalny jest rowny: %lf\n", err);
      }
    }
    write_matrix(xnew, stdout);
    err = errcount(xold, xnew);
    printf("Blad maksymalny jest rowny: %lf\n", err);*/
    /*int sym = 0;
    if (m != NULL)
    {
      matrix_t *c = NULL;
      int *row_per = malloc(m->rn * sizeof *row_per);
      printf("\nMacierz:\n");
      write_matrix(m, stdout);
      if (argc > 2 && strcmp(argv[2], "-s") == 0)
      {
        c = symm_pivot_ge_matrix(m, row_per);
        sym = 1;
      }
      else
        c = pivot_ge_matrix(m, row_per);
      if (c != NULL)
      {
        int i;
        printf("\nPo elim. Gaussa:\n");
        write_matrix(c, stdout);
        printf("Permutacja:");
        for (i = 0; i < c->rn; i++)
          printf(" %d", row_per[i]);
        printf("\n");
        if (bs_matrix(c) == 0)
        {
          int j;
          int *iper = pivot_get_inv_per(c, row_per);
          printf("Permutacja odwrotna:");
          for (i = 0; i < c->rn; i++)
            printf(" %d", iper[i]);
          printf("\n");
          printf("\nPo podstawieniu wstecz:\n");
          write_matrix(c, stdout);
          printf("Rozwiązania: \n");
          for (j = 0; j < c->cn - c->rn; j++)
          {
            printf("Nr %d:\n", j + 1);
            for (i = 0; i < c->rn; i++)
            {
              int oi = sym ? iper[i] : i;
              printf("\t%g", *(c->e + oi * c->cn + j + c->rn));
            }
            printf("\n");
          }
        }
      }
      else
        printf("nie lula!\n");
    }
    return 0;
  }
  else
    return 1;*/
  }
  return 0;
}
