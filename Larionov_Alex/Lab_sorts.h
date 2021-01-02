#pragma once
#include <iostream>
#include <stdio.h>
void insertion_sort(double arr[], int n)
{
	int a = 0; int b = 0;
	for (int i = 1; i < n; i++)
		for (int j = i; j > 0 && arr[j - 1] - arr[j] >= 0; j--)
		{
			double tmp = arr[j - 1];
			arr[j - 1] = arr[j];
			arr[j] = tmp;
			a = a + 3; b++;
		}
	printf("\n%d%s\n%d%s", a, "swaps", b, "comparisons");
}
void Shell_sort(double array[], const int n)
{
	int step, i, j;
	double tmp;
	for (step = n / 2; step > 0; step /= 2)
		for (i = step; i < n; i++)
			for (j = i - step; j >= 0 && array[j] > array[j + step]; j -= step)
			{
				tmp = array[j];
				array[j] = array[j + step];
				array[j + step] = tmp;
			}

}
void createCounters(double* data, int* counters, long N)
{

	unsigned char* bp = (unsigned char*)data;
	unsigned char* dataEnd = (unsigned char*)(data + N);
	unsigned short i;

	memset(counters, 0, 256 * sizeof(double) * sizeof(long));

	while (bp != dataEnd)
	{
		for (i = 0; i < sizeof(double); i++)
			counters[256 * i + *(bp++)]++;
	}
}
void radixPass(short Offset, long N, double* source, double* dest, int* count)
{
	double* sp;
	int s = 0, c, i, * cp = count;
	unsigned char* bp;

	for (i = 256; i > 0; --i, ++cp)
	{
		c = *cp;		*cp = s;		s += c;
	}
	bp = (unsigned char*)source + Offset;
	sp = source;
	for (i = N; i > 0; --i, bp += sizeof(double), ++sp)
	{
		cp = count + *bp;	dest[*cp] = *sp;		(*cp)++;
	}
}
void radixSort(double* array, long N)
{
	double* additional_array = (double*)malloc(N * sizeof(double));
	int* counters = (int*)malloc(2048 * sizeof(int));
	int* count;
	int k = 0;
	createCounters(array, counters, N);
	for (unsigned short i = 0; i < sizeof(double); i++)
	{
		count = counters + 256 * i;
		radixPass(i, N, array, additional_array, count);
		for (int j = 0; j < N; j++)
		{
			array[j] = additional_array[j];
		}
	}
	while (array[k] >= 0 && k < N && !(k > 0 && array[k] <= 0 && array[k - 1] > 0)) k++;
	for (int i = 0; i < N - k; i++)
	{
		array[i] = additional_array[N - 1 - i];
	}
	for (int i = 0; i < k; i++)
	{
		array[N - k + i] = additional_array[i];
	}
	memcpy(array, additional_array, N * sizeof(double));
	free(additional_array);
	free(counters);
}
void merge(double array[], double spare[], int l, int r)
{
	int i = l, q = (l + r) / 2, j = q + 1, k = 0;
	while (i <= q && j <= r)
	{
		if (array[i] <= array[j])
		{
			spare[k] = array[i];
			i++;
		}
		else
		{
			spare[k] = array[j];
			j++;
		}
		k++;
	}
	while (i <= q)
	{
		spare[k] = array[i];
		i++; k++;
	}
	while (j <= r)
	{
		spare[k] = array[j];
		j++;
		k++;
	}
	for (i = 0; i < k; i++)
		array[l + i] = spare[i];
}
int merge_sort(double array[], double spare[], int l, int r)
{
	if (l < r)
	{
		int q = (l + r) / 2;
		merge_sort(array, spare, l, q);
		merge_sort(array, spare, q + 1, r);
		merge(array, spare, l, r);
	}
	return(0);
}