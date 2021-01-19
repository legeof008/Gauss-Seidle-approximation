#include "piv_gs_solver.h"
#include "matrix.h"
#include <float.h>
#include <math.h>
double errcount(matrix_t *xold, matrix_t *xnew) // zwraca masymalny blad niepewnosci z niewiadomych
{
    double max = DBL_MIN;
    for (int i = 0; i < xold->rn; i++)
    {
        if (max < (*(xnew->e + i) - *(xold->e + i)) / (*(xnew->e + i)) * 100 && *(xnew->e + i) != 0)
            max = fabs((*(xnew->e + i) - *(xold->e + i)) / (*(xnew->e + i))) * 100;
    }
    return max;
}

void initc_matrix(matrix_t *m) // ustawianie najwiekszych wartosci na diagonalnej co do modulu
{
    double max = DBL_MIN;
    int col = m->cn;
    int tr = -1;
    int tc = -1;
    // i to kolumny, j to wiersze
    for (int i = 0; i < m->cn; i++)
    {
        for (int j = i; j < m->rn; j++)
        {
            if (fabs(*(m->e + i * col + j)) > max)
            {
                max = *(m->e + j * col + i);
                tr = j;
                tc = i;
            }
        }

        xchg_rows(m, tr, tc);
        max = DBL_MIN;
    }
}
void initfx(matrix_t *m, matrix_t *x) // inicjalizacja pierwszej w procesie macierzy niewiadomych
{
    for (int i = 0; i < m->rn; i++)
        put_entry_matrix(x, i, 0, *(m->e + i * m->cn + m->rn) / *(m->e + i * m->cn + i));
}
int cond1(matrix_t *m) // diagonalna w wierszu wieksza >= suma wspolczynnikow w wierszu (dla wszystkich wierszow)
{
    double sum;
    int diag = 0;
    for (int i = 0; i < m->rn; i++)
    {
        sum = 0;
        for (int j = 0; j < m->cn - 1; j++)
        {
            if (j != diag)
            {
                sum += *(m->e + i * m->cn + j);
            }
        }
        if (sum > *(m->e + i * m->cn + diag))
        {
            printf("Niespelniony warunek !\n");
            return 0;
        }
        printf("Suma, wiersz %d = %f\n", i, sum);
        diag++;
    }
    return 1;
}
int cond2(matrix_t *m) // diagonalna w wierszu wieksza > suma wspolczynnikow w wierszu (dla conajmniej jednego wiersza)
{
    double sum;
    int diag = 0;
    for (int i = 0; i < m->rn; i++)
    {
        sum = 0;
        for (int j = 0; j < m->cn - 1; j++)
        {
            if (j != diag)
            {
                sum += *(m->e + i * m->cn + j);
            }
        }
        if (sum < *(m->e + i * m->cn + diag))
        {
            printf("Spelniony warunek dla wiersza %d!\n", i);
            return 1;
        }
        printf("Suma, wiersz %d = %f\n", i, sum);
        diag++;
    }
    printf("Niespelniony warunek !\n");
    return 0;
}
double rowsum(matrix_t *m, int rn, int diag)
{
    double sum = 0;
   
    for (int j = 0; j < m->cn -1 ; j++)
    {
        if (j != diag)
        {
            sum += *(m->e + rn * m->cn + j);
        }
    }

    return sum;
}
void getiter(matrix_t *m, matrix_t *xold, matrix_t *xnew)
{
    double sum;
    int diag = 0;
    for(int i = 0; i < m->rn; i++)
    {
        sum = 0;
        for(int j = 0; j < m->cn - 1; j++)
        {
            if(j!=diag)
            {
                sum += *(m->e + i * m->cn + j) * (*(xold->e + j));
            }
        }
        *(xnew->e + diag) = (*(m->e + i * m->cn  + diag) - sum)/ (*(m->e + i * m->cn));
        diag++;
    }
}
