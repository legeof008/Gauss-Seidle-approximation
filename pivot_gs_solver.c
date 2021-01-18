#include "piv_gs_solver.h"
#include "matrix.h"
#include <float.h>
#include <math.h>
double errcount(matrix_t *xold, matrix_t* xnew)
{
    double max = DBL_MIN;
    for(int i = 0; i < xold->rn; i++)
    {  
        if(max < (*(xnew->e + i) - *(xold->e + i))/(*(xnew->e + i))* 100 && *(xnew->e + i) != 0)
            max = fabs((*(xnew->e + i) - *(xold->e + i))/(*(xnew->e +i))) * 100;
    }
    return max;
}

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
void initfx(matrix_t* m, matrix_t* x)
{
    for(int i = 0; i < m->rn; i++)
        put_entry_matrix(x,i,0,*(m->e + i * m->cn + m->rn)/ *(m->e + i * m->cn + i));
}
