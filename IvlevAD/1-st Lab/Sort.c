#include <math.h>
#include <string.h>
#include "Sort.h"

unsigned int permutation = 0;//Число перестановок
unsigned int comparison = 0;//Число сравнений

void BubbleSort(unsigned int n, float array[]) //Сортировка Пузырьком, n - кол-во эл-тов массива, array[] - массив для сортировки
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = n - 2; j > i - 1; j--)
        {
            comparison++;
            if (array[j] > array[j+1])
            {
                float tmp = array[j];
                array[j] = array[j+1];
                array[j+1] = tmp;
                permutation++;
            }
        }
    }
}

void ShellSort(unsigned int n, float array[]) //Сортировка Шелла, n - кол-во эл-тов массива, array[] - массив для сортировки
//Шаг сортировки 2^k - 1 (послед-ть Хиббарда)
{
    unsigned int step, i, j;
    float tmp;
    unsigned int k = 1;
    //for (k; pow(2, k) - 1 <= n; k++){} если без логарифма
    k = round(log2f(n));
    if (pow(2,k) -1 > n)
    {
        k--;
    }
    for (step = pow(2,k) - 1; step > 0; k--, step = pow(2,k) - 1)
    {
        for (i = step; i < n; i++)
        {
            comparison++;
            for (j = i; j >= step && array[j] < array[j-step]; j-=step)
            {
                tmp = array[j];
                array[j] = array[j-step];
                array[j-step] = tmp;
                permutation++;
            }
        }
    }
}

void Merge(unsigned int f, unsigned int l, float array[], float dparray[]) //Подпрограмма сортировки слиянием
//Сортирует и возвращает под массивы
//f - элемент начала сортировки (0 по умолчанию, сортирует с начала)
//l - элемент конца сортировки (n-1 по умолчанию, сортирует до конца)
//array[] - массив для сортировки, dparray[] - дополнительный массив размером n
{
    unsigned int mid = (f + l)/2;
    unsigned int st = f;
    unsigned int fin = mid + 1;
    for (unsigned int j = f; j<=l; j++)
    {
        comparison++;
        if ((st<=mid) && ((fin>l) || (array[st]<array[fin])))
        {
                dparray[j] = array[st];
                st++;
                permutation++;
        }
        else
        {
                dparray[j] = array[fin];
                fin++;
        }
    }
    for (unsigned int i = f; i <= l; i++)
    {
        array[i] = dparray[i];
    }
}

void MergeSort(unsigned int f, unsigned int l, float array[], float dparray[]) //Сортировка слиянием
//f - элемент начала сортировки (0 по умолчанию, сортирует с начала)
//l - элемент конца сортировки (n-1 по умолчанию, сортирует до конца)
//array[] - массив для сортировки, dparray[] - дополнительный массив размером n
//n - длина массива для сортировки
{
    if (f<l)
    {
        unsigned int mid = (f + l)/2;
        MergeSort(f, mid, array, dparray);
        MergeSort(mid+1, l, array, dparray);
        Merge(f, l, array, dparray);
    }
}

void CreateCounters(float *data, long *counters, long n) //Подпрограмма поразрядной сортировки
//Создаёт массив значений байтов у элементов исходного массива
//data - исходный массив для сортировки
//counters - массив для записи
//n - длина исходного массива
{
    unsigned char *bp = (unsigned char*)data;
    unsigned char *dataEnd = (unsigned char*)(data+n);
    unsigned short i;
    memset(counters, 0, 256*sizeof(float)*sizeof(long));
    while (bp != dataEnd)
    {
        for (i = 0; i < sizeof(float); i++)
        {
            counters[256*i + *(bp++)]++;
        }
    }
}

void RadixP(short offset, long n, float *source, float *dest, long *count) //Подпрограмма поразрядной сортировки
//Шаг поразрядной сортировки
//offset - номер байта
//n - длинна исходного массива для сортировки
//source - исходный массив для сортировки
//dest - дополнительны массив длины n
//count - дополнительный массив с разрядами
{
    float *sp;
    long s = 0, c, i, *cp = count;
    unsigned char *bp;
    for (i = 256; i>0; --i, cp++)
    {
        c = *cp;
        *cp = s;
        s += c;
    }
    bp = (unsigned char*)source + offset;
    sp = source;
    for (i = n; i>0; --i, bp += sizeof(float), ++sp)
    {
        cp = count + *bp;
        dest[*cp] = *sp;
        (*cp)++;
        permutation++;
    }
}

void SRadixSort(float *in, float *out, long *counters, long n) //Поразрядная сортировка
//in = массив для сортировки
//out - дополнительный массив длины n
//counters - дополнительный массив длины n
//n - длина массива для сортировки
{
	long *count; 
    short i;
    long k = 0; 
	CreateCounters(in, counters, n);

	for (i=0; i<sizeof(float); i++) 
    {
		count = counters + 256*i;
		RadixP (i, n, in, out, count); 
		for (long j = 0; j<n; j++)
        {
			in[j] = out[j];
        }
    }
	while ((in[k] >= 0) && (k < n) && ((k <= 0) || (in[k] > 0) || (in[k-1] <= 0))) 
    {
        k++;
    }
	for (int i = 0; i < n-k; i++)
    {
        in[i] = out[n-1-i];
    }
	for (int j = 0; j < k; j++)
    {
        in[n-k+j] = out[j];
    }
}

//Если эл-т массива имеет значимый знак на 6-й позиции после запятой, то иногда может округлить на 0.000001 в меньшую сторону
//(причина не известна)