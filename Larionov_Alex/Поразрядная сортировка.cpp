#include<iostream>
#include<stdio.h>
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
