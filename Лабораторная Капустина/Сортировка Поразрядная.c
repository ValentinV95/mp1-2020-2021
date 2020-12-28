#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>      
#include <time.h>
#include <conio.h>
#include <malloc.h>
#include <stdlib.h>
#include <math.h>
#include "inttypes.h"
#include "memory.h"
#define SIZE_T 100000

struct testInfo
{
	int64_t compareCount, swapCount;
	int isCorrect;
};
typedef struct testInfo testInfo;

static void _radix_(double* array, double* uol, size_t cp)
{
	size_t i = cp - 1;
	size_t num = 0;

	for (size_t j = 0; j <= i; j++, num++)
	{
		array[num] = uol[j];
	}

	for (; i > 0 && uol[i] < 0; i--, num++)
	{
		array[num] = uol[i];
	}
}

testInfo radixSort(double* const array, size_t cp)
{
	const int countValues = (1 << 8);

	testInfo report;
	size_t counts[sizeof(double)][(1 << 8)];
	double* tempArray;
	double* buf;
	int k=0;

	memset(counts, 0, sizeof(double) * countValues * sizeof(size_t));

	report.compareCount = report.swapCount = 0;

	for (size_t i = 0; i < sizeof(double); i++)
	{
		for (size_t j = 0; j < cp; j++)
		{
			int val = *((uint8_t*)&array[j] + i);
			counts[i][val]++;
		}
	}

	for (size_t i = 0; i < sizeof(double); i++)
	{
		size_t sum = 0;
		for (int j = 0; j < countValues; j++)
		{
			size_t temp = counts[i][j];
			counts[i][j] = sum;
			sum += temp;
		}
	}

	tempArray = (double*)malloc(sizeof(double) * cp);
	buf = (double*)malloc(sizeof(double) * cp);

	memcpy(tempArray, array, sizeof(double) * cp);
	for (size_t i = 0; i < sizeof(double); i++)
	{
		double* temp;

		for (size_t j = 0; j < cp; j++)
		{
			int val = *((uint8_t*)&tempArray[j] + i);
			buf[counts[i][val]] = tempArray[j];
			counts[i][val]++;
			k++;
			report.swapCount++;
		}

		temp = tempArray;
		tempArray = buf;
		buf = temp;
	}

	_radix_(array, tempArray, cp);
	report.swapCount += cp;
	k = k + cp;
	free(tempArray);
	free(buf);
	printf("%d", k);
	return report;
}

void main()
{
	const N = 100;
	double mass[SIZE_T];
	double* p;
	p = mass;
	int i;
	testInfo flow;
	srand(time(NULL));
	for (i = 0; i < N; i++)
	{
		//scanf("%lf", &mass[i]);
		mass[i] = rand();
		mass[i] = (mass[i] * 0.00001 + rand());
		if ((rand() % 2) == 1)
			mass[i] = 0 - mass[i];
	}
	radixSort(mass, N);
	//printf("%" PRIu64 "\n", flow.compareCount);

	for (i = 0; i < 100; i++)
	{
		printf("%lf", mass[i]);
		printf("  ");
	}
	return(0);
}
