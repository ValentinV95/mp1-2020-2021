#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>      
#include <time.h>
#include <conio.h>
#include <malloc.h>
#include <stdlib.h>
#include <math.h>


void comb_sort(double* a, const size)
{
    double factor = 1.2473309;
    int step = size - 1;
    while (step >= 1) {
        for (int i = 0; i+step < size ; i++)
        {
            if (a[i] > a[i + 1])
            {
                double tmp;
                tmp = a[i];
                a[i] = a[i + 1];
                a[i + 1] = tmp;
            }
        }
        step /= factor;
    }

    int b = 1;
    while (b == 1) {
        b = 0;
        for (int j = 0; j+1 <size; j++)
            if (a[j] > a[j + 1])
            {
                double tmp;
                tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
                b = 1;
            }
    }
   // return (a);
}


void main()
{
    const N = 10000;
    double mass[10000];
    double* p;
    p = mass;
    int i;
    srand(time(NULL));
    for (i = 0; i < N; i++)
    {
        //scanf("%lf", &mass[i]);
        mass[i] = rand();
        mass[i] = (mass[i] * 0.00001 + rand());
        if ((rand()%2 )== 1)
            mass[i] = 0-mass[i] ;
    }
    comb_sort(p, N);

    for (i = 0; i < N; i++)
    {
        printf("%lf", mass[i]);
        printf("  ");
    }
    return(0);
}