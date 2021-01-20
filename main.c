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
    solve(m);
  }
  return 0;
}
