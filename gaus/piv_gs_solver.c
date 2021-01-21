#include "piv_gs_solver.h"
#include "matrix.h"
#include <float.h>
#include <math.h>
#define MAX_ERR 10000000.
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
double errcounter(matrix_t *xold, matrix_t *xnew)
{
    double max = DBL_MIN;
    for (int i = 0; i < xold->rn; i++)
    {
        if (max < fabs(*(xnew->e + i) - *(xold->e + i)))
        {
            max = fabs((*(xnew->e + i) - *(xold->e + i)));
        }
    }
    return max * MAX_ERR;
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

double rowsum(matrix_t *m, int rn, int diag)
{
    double sum = 0;

    for (int j = 0; j < m->cn - 1; j++)
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
    for (int i = 0; i < m->rn; i++)
    {
        sum = 0;
        for (int j = 0; j < m->cn - 1; j++)
        {
            if (j != diag)
            {
                sum += get_entry_matrix(m, i, j) * get_entry_matrix(xold, j, 0);
            }
        }

        *(xnew->e + diag) = (*(m->e + i * m->cn + m->cn - 1) - sum) / (*(m->e + i * m->cn + diag));
        diag++;
    }
}
int cond(matrix_t *m)
{
    double sum;
    int strong_dom = 0;
    for (int i = 0; i < m->rn; i++)
    {
        sum = 0;
        for (int j = 0; j < m->cn - 1; j++)
        {
            if (j != i)
                sum += fabs(*(m->e + i * m->cn + j));
        }
        if (sum > fabs(*(m->e + i * m->cn + i)))
            return 0; // suma elementow wieksza od diagonali

        if (fabs(*(m->e + i * m->cn + i)) > sum)
            strong_dom = 1;
    }
    if (strong_dom)
        return 1; // kryt. silnej dominacji spelnione dla conajmniej jednego wiersza
                  // a kryt. slabej dominacji spelnione dla reszty wierszy
    return 0;
}
// zamiana ostatniej kolumny macierzy na odpowiedzi
void put_ans(matrix_t *m, matrix_t *x)
{
    for (int i = 0; i < m->rn; i++)
        *(m->e + (i + 1) * m->cn - 1) = *(x->e + i);
}