#include <stdio.h>
#include <malloc.h>
#include "Sort.h" //Функции сортировок
#include "TestSort.h" //Проверка отсортированного массива

void main() //Главная программа
{
    //На вход кол-во эл-тов массива и сам массив
    unsigned int n, j, k;
    float *dparray;
    float *newarray; //Массив для сортировки
    float *newnewarray;
    long *counters;
    printf("Enter the length of the array\n");
    scanf("%u", &n);
    newarray = (float*)malloc(n * sizeof(float));
    printf("Enter an array\n");
    for(unsigned int i = 0; i < n; ++i)
    {
        scanf("%f", &newarray[i]);
    }
    printf("Enter 1 if TestSort, else enter 0\n");//Проверка сортировки
    scanf("%u", &k);
    if (k == 1)
    {
        newnewarray = (float*)malloc(n * sizeof(float));
        for (unsigned int i = 0; i<n; i++)
        {
            newnewarray[i] = newarray[i];
        }
    }
    printf("Enter the sort number\n1-BubbleSort\n2-ShellSort\n3-MergeSort\n4-RadixSort\n");
    scanf("%u", &j);
    if (j==1)//Выбор сортировки
    {
        BubbleSort(n, newarray);
    }
    if (j==2)
    {
        ShellSort(n, newarray);
    }
    if (j==3)
    {
        dparray = (float*)malloc(n * sizeof(float));
        MergeSort(0, n-1, newarray, dparray);
    }
    if (j==4)
    {
        dparray = (float*)malloc(n * sizeof(float));
        counters = (long*)malloc(1024 * sizeof(long));
        SRadixSort(newarray, dparray, counters,n);
    }
    printf("permutation=%u\ncomparison=%u\n", permutation, comparison);
    if (k==1)
    {
            TestSort(n, newarray, newnewarray);
    }
    for (int k = 0; k < n; k++)//вывод отсортированного массива
    {
        printf("%f ", newarray[k]);
    }
    free(dparray);
    free(counters);
    free(newnewarray);
    system("pause");
}