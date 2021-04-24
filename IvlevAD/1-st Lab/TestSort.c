#include "TestSort.h"
#include "Sort.h"
#include <stdio.h>

void TestSort(unsigned int n,float array[], float newnewarray[]) //Проверка отсортированного массива
//n - длина массива
//array[] - массив после сортировки
//newnewarray[] - копия исходного массива
{
    unsigned int count = 0;
    for (unsigned int i = 0; i<n-1; i++)
    {
        if (array[i]>array[i+1])
        {
            count = i;
        }
    }
    if (count != 0)
    {
        printf("Error\n", count);
    }
    else
    {
        BubbleSort(n, newnewarray);
        for (unsigned int j = 0; j < n; j++)
        {
            if (newnewarray[j] != array[j])
            {
                printf("Error %u\n", j);
                count = 1;
            }
        }
        if (count == 0)
        {
            printf("Ok\n");
        }
    }
}