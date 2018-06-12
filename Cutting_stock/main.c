/* Short script to calculate efficient way to cut stock material into required lengths */
/* V1 2018-06-12 */
/* Author: Audrius Stankus */

#include <stdio.h>
#include <stdlib.h>
#define CUT_THICKNESS 5
#define L_length 2400

/* Greedy algorithm / Cutting stock problem */

void one_stock(double L);

int length = 30;
double l[30] = {1476, 1476, 1476, 1476, 1362, 1362, 1362, 1362, 1362, 1000, 943, 900, 900, 900, 900, 700, 700, 700, 700, 700, 700, 548.7, 548.7, 548.7, 548.7, 488.6, 488.6, 488.6, 488.6, 150};

//double l[12] = {1476, 2, 1362, 100, 700, 700, 7, 548.7, 546, 488.6, 488.6, 150};

int no_raw = 0;
double total_leftover;
double wasted_pct;
int main()
{

    my_qsort(l, 0, length-1);

    while (length > 0)
    {
        one_stock(L_length);
    }
    wasted_pct = total_leftover / (no_raw*L_length) * 100;
    printf("Wasted length %.1f mm\n", total_leftover);
    printf("Wasted length pct %.3f pct\n", wasted_pct);
    return 0;
}


void one_stock(double L)
{
    no_raw++;
    printf("%d. ", no_raw);
    double L_leftover = L;
    for (int i = length-1; i >= 0; i-- )
    {
        if (l[i] < L_leftover)
        {
            printf("%.1f ", l[i]);
            L_leftover = L_leftover - l[i] - CUT_THICKNESS;
            for (int j = i; j < length-1; j++)
            {
                l[j] = l[j+1];
            }
            l[--length] = 0;
        }
    }
    printf(", left %.1f\n", L_leftover);
    total_leftover = total_leftover + L_leftover;
}

void my_qsort(double v[], int left, int right)
{
    int i, last;
    void swap(double v[], int i, int j);

    if (left >= right)
        return; /* Do nothing if array is less than 2 */

    swap(v, left, (left+right)/2);
    last = left;
    for (i = left + 1; i <= right; i++)
    {
        if (v[i] < v[left])
        {
            swap(v, ++last, i);
        }
    }
    swap(v, left, last);
    my_qsort(v, left, last-1);
    my_qsort(v, last+1, right);
}

void swap(double v[], int i, int j)
{
    double temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
