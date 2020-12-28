#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>      
#include <time.h>
#include <conio.h>
#include <malloc.h>
#include <stdlib.h>
#include <math.h>
#define SIZE 10

void mergeSort(double* a, int l, int r)
{
    if (l == r) return;
    int mid = (l + r) / 2; 
    mergeSort(a, l, mid);
    mergeSort(a, mid + 1, r);
    int i = l;  
    int j = mid + 1; 
    float* tmp = (float*)malloc(r * sizeof(int)); 
    for (int step = 0; step < r - l + 1; step++) 
    {
        if ((j > r) || ((i <= mid) && (a[i] < a[j])))
        {
            tmp[step] = a[i];
            i++;
        }
        else
        {
            tmp[step] = a[j];
            j++;
        }
    }
    for (int step = 0; step < r - l + 1; step++)
        a[l + step] = tmp[step];
}



void main()
{
    const N = 10;
    double mass[10];
    double* p;
    p = mass;
    int i;
    srand(time(NULL));
    for (i = 0; i < N; i++)
    {
        //scanf("%lf", &mass[i]);
        mass[i] = rand();
        mass[i] = (mass[i] * 0.00001 + rand());
        if ((rand() % 2) == 1)
            mass[i] = 0 - mass[i];
    }
    mergeSort(p, 0, N-1);

    for (i = 0; i < N; i++)
    {
        printf("%lf", mass[i]);
        printf("  ");
    }
    return(0);
}