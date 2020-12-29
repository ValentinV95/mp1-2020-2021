#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>      
#include <time.h>
#include <conio.h>
#include <malloc.h>
#include <stdlib.h>
#include <math.h>
#include "inttypes.h"
#include "memory.h"
#include <locale.h>
#define SIZE_T 100000

struct testInfo
{
	int64_t compareCount, swapCount;
	int isCorrect;
};
typedef struct testInfo testInfo;

static void _radix_(double* array, double* buf, int64_t size)
{
	size_t i = size - 1;
	size_t pos = 0;

	for (; i > 0 && buf[i] < 0; i--, pos++)
	{
		array[pos] = buf[i];
	}

	for (size_t j = 0; j <= i; j++, pos++)
	{
		array[pos] = buf[j];
	}
}

testInfo radixSort(double* const array, size_t cp)
{
	const int countValues = (1 << 8);

	testInfo radix;
	size_t counts[sizeof(double)][(1 << 8)];
	double* tempArray;
	double* buf;

	memset(counts, 0, sizeof(double) * countValues * sizeof(size_t));

	radix.compareCount = radix.swapCount = 0;

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

			radix.swapCount++;
		}

		temp = tempArray;
		tempArray = buf;
		buf = temp;
	}

	_radix_(array, tempArray, cp);
	radix.swapCount += cp;
	free(tempArray);
	free(buf);
	return radix;
}

double massiv(double* array, int l)
{
	for (int i = 0; i < l; i++)
	{
		array[i] = rand();
		array[i] = (array[i] * 0.00001 + rand());
		if ((rand() % 2) == 1)
			array[i] = 0 - array[i];
	}
}

testInfo bubble_sort(double* a, const size)
{
	testInfo bubble;
	bubble.compareCount = bubble.swapCount = 0;
	for (int i = 0; i < size - 1; i++)
	{
		int flag = 0;
		for (int j = size - 2; j > i - 1; j--)
		{
			if (a[j] > a[j + 1])
			{
				double tmp;
				tmp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tmp;
				bubble.swapCount++;
				flag = 1;
			}
			bubble.compareCount++;
		}
		if (flag == 0)
		{
			return bubble;
			break;
		}
	}
}

testInfo comb_sort(double* a, const size)
{
	testInfo comb;
	comb.compareCount = comb.swapCount = 0;
	double factor = 1.2473309;
	int step = size - 1;
	while (step >= 1) {
		for (int i = 0; i + step < size; i++)
		{
			if (a[i] > a[i + 1])
			{
				double tmp;
				tmp = a[i];
				a[i] = a[i + 1];
				a[i + 1] = tmp;
				comb.swapCount++;
			}
			comb.compareCount++;
		}
		step /= factor;
	}

	int b = 1;
	while (b == 1) {
		b = 0;
		for (int j = 0; j + 1 < size; j++)
		{
			if (a[j] > a[j + 1])
			{
				double tmp;
				tmp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tmp;
				b = 1;
				comb.swapCount++;
			}
			comb.compareCount++;
		}

	}
	return comb;
}

testInfo mergeSort(double* a, int l, int r)
{
	testInfo merge;
	merge.compareCount = merge.swapCount = 0;
	if (l == r) return merge;
	int mid = (l + r) / 2;
	merge.swapCount += mergeSort(a, l, mid).swapCount;
	merge.swapCount += mergeSort(a, mid + 1, r).swapCount;
	int i = l;
	int j = mid + 1;
	float* tmp = (float*)malloc(r * sizeof(int));
	for (int step = 0; step < r - l + 1; step++)
	{
		if ((a[i] > a[j]))
			merge.swapCount++;
		if ((j > r) || ((i <= mid) && (a[i] <= a[j])))
		{
			tmp[step] = a[i];
			i++;
		}
		else
		{
			tmp[step] = a[j];
			j++;
		}
		merge.compareCount++;
	}
	for (int step = 0; step < r - l + 1; step++)
	{
		a[l + step] = tmp[step]; 
		merge.compareCount++;
	} 
	for (int step = 0; step < r - l + 1; step++)
	return merge;
}
int correct(double* array, int l)
{
	int flag = 1;
	for (int i = 0; i < l-1; i++)
	{
		if (array[i] > array[i + 1])
			flag = 0;
	}
	return flag;
};


void main()
{
	setlocale(LC_ALL, "Rus");
	int zero = 1;
	int N = SIZE_T;
	double mass[SIZE_T];
	double* p;
	p = mass;
	int i;
	int cor=0;
	int per = 0;
	testInfo flow;
	srand(time(NULL));
	while (zero != 0)
	{
		/*printf(" Âûáåðèòå îäèí èç ïóíêòîâ íèæå è ââåäèòå åãî öèôðó â êîíñîëü. \n \n ");
		printf(" Ìåíþ \n 1. Ââåñòè ìàññèâ âðó÷íóþ \n 2. Âûâåñòè ìàññèâ íà ýêðàí \n 3. Âûáðàòü êîëè÷åñòâî ýëëåìåíòîâ â ìàññèâå. Ñåé÷àñ n= %d", N);
		printf(" \n 4. Çàïîëíèòü ìàññèâ ðàíäîìíûìè ýëåìåíòàìè \n 5. Îòñîðòèðîâàòü ìàññèâ ñîðòèðîâêîé ïóçûðüêîì. \n 6. Îòñîðòèðîâàòü ìàññèâ ñîðòèðîâêîé ðàñ÷åñêîé \n ");
		printf("7. Îòñîðòèðîâàòü ìàññèâ ïîðàçðÿäíîé ñîðòèðîâêîé. \n 8. Îòñîðòèðîâàòü ìàññèâ ñîðòèðîâêîé ñëèÿíèåì \n 0. Âûõîä\n");*/
		scanf("%d", &zero);
		if (zero == 1)
		{
			for (i = 0; i < N; i++)
			{
				scanf("%lf", &mass[i]);
			}
		}
		if (zero == 2)
		{
			for (i = 0; i < N; i++)
			{
				printf("%lf", mass[i]);
				printf("  ");
			}
		}
		if (zero == 3)
		{
			scanf("%d", &N);
		}
		if (zero == 4)
		{
			for (i = 0; i < N; i++)
			{
				mass[i] = rand();
				mass[i] = (mass[i] * 0.00001 + rand());
				if ((rand() % 2) == 1)
					mass[i] = 0 - mass[i];
			}
		}
		if (zero == 5)
		{
			flow = bubble_sort(p, N);
			printf("×èñëî ïåðåñòàíîâîê %" PRId64 "\n", flow.swapCount);
			printf("×èñëî ñðàâíåíèé %" PRId64 "\n", flow.compareCount);
		}
		if (zero == 6)
		{
			flow = comb_sort(p, N);
			printf("×èñëî ïåðåñòàíîâîê %" PRId64 "\n", flow.swapCount);
			printf("×èñëî ñðàâíåíèé %" PRId64 "\n", flow.compareCount);
		}
		if (zero == 7)
		{
			flow = radixSort(mass, N);
			printf("×èñëî ïåðåñòàíîâîê %" PRId64 "\n", flow.swapCount);
			printf("×èñëî ñðàâíåíèé %" PRId64 "\n", flow.compareCount);
		}

		if (zero == 8)
		{
			flow = mergeSort(p, 0, N - 1);
			printf("×èñëî ïåðåñòàíîâîê %" PRId64 "\n", flow.swapCount);
			printf("×èñëî ñðàâíåíèé %" PRId64 "\n", flow.compareCount);
		}
		cor = correct(mass, N);
		if( zero>4 && cor ==1)
			printf("Correct");
		f( zero>4 && cor == 0)
			printf("No correct");
		{
	}
	return 0;
}
