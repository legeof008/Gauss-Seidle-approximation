#include "piv_gs_solver.h"
#include "matrix.h"
#include <float.h>
#include <math.h>

void initc_matrix(matrix_t *m)
{
    double max = DBL_MIN;
    int col = m->cn;
    int tr = -1;
    int tc = -1;
    // i to kolumny, j to wiersze 
    for(int i = 0; i < m->cn  ;i++)
    {
        for(int j = i; j< m->rn; j++)
        {
            if (fabs(*(m->e + i *col +j)) > max)
            {
                max = *(m->e + j *col +i);
                tr = j;
                tc = i;
            }
        }
        
        xchg_rows(m,tr,tc);
        max = DBL_MIN;
    }
}