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

void createCounters(double* array, long* counters, int N)
{
	int i;
	unsigned char* bp = (unsigned char*)array;
	unsigned char* Dataend = (unsigned char*)(array + N);

	memset(counters, 0, 256 * sizeof(double) * sizeof(int));
	while (bp != Dataend)
	{
		for (i = 0; i < sizeof(double); i++)
		{
			counters[256 * i + *(bp++)]++;
		}
	}
}
testInfo floatradixLastPass(short Offset, int size, double* array, double* dest, long* count)
{
	testInfo radix;
	radix.swapCount = radix.compareCount = 0;
	double* sp;
	long s, c, i, * cp;
	unsigned char* bp;
	long numNeg = 0;
	for (i = 128; i < 256; i++) numNeg += count[i];

	s = numNeg;
	cp = count;
	for (i = 0; i < 128; ++i, ++cp)
	{
		c = *cp;
		*cp = s;
		s += c;
	}

	cp = count + 255;
	s = 0;
	*cp = 0;
	for (i = 254; i >= 128; i--, cp--)
	{
		s += *cp;
		*cp = s;
	}
	bp = (unsigned char*)array + Offset;
	sp = array;
	for (i = size; i > 0; --i, bp += sizeof(double), ++sp)
	{
		cp = count + *bp;
		if (*bp < 128)
		{
			dest[*cp] = *sp;
			(*cp)++;
		}
		else
		{
			(*cp)--;
			dest[*cp] = *sp;
		}
		radix.swapCount++;
	}
	return radix;
}
testInfo radixPass(short Offset, int N, double* sourse, double* dest, long* count)
{
	testInfo radix;
	radix.swapCount = radix.compareCount = 0;
	double* sp;
	long s, c, i, * cp;
	unsigned char* bp;

	s = 0;
	cp = count;
	for (i = 256; i > 0; --i, ++cp)
	{
		c = *cp;
		*cp = s;
		s += c;
	}

	bp = (unsigned char*)sourse + Offset;
	sp = sourse;
	for (i = N; i > 0; --i, bp += sizeof(double), ++sp)
	{
		cp = count + *bp;
		dest[*cp] = *sp;
		(*cp)++;
		radix.swapCount++;
	}
	return radix;
}
testInfo FloatRadixSort(double* array, int size)
{
	testInfo radix;
	testInfo rad;
	radix.swapCount = radix.compareCount = 0;
	int i;
	double* temp;
	double* mas = (double*)malloc(sizeof(double) * size);
	long* counters = (long*)malloc(sizeof(double) * 256 * sizeof(int));
	long* count;

	createCounters((double*)array, counters, size);

	for (i = 0; i < sizeof(double) - 1; i++)
	{
		count = counters + 256 * i;
		rad = radixPass(i, size, array, mas, count);
		radix.swapCount += rad.swapCount;
		radix.compareCount += rad.compareCount;
		temp = array;
		array = mas;
		mas = temp;
	}
	count = counters + 256 * (sizeof(double) - 1);
	rad = floatradixLastPass(sizeof(double) - 1, size, array, mas, count);
	radix.swapCount += rad.swapCount;
	radix.compareCount += rad.compareCount;
	temp = array;
	array = mas;
	mas = temp;

	free(mas);
	free(counters);
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
	return array;
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
	merge.compareCount += mergeSort(a, l, mid).compareCount;
	merge.compareCount += mergeSort(a, mid + 1, r).compareCount;
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

	testInfo chet [100];
	testInfo sum;
	testInfo MIN;
	testInfo MAX;
	int64_t lol=0;
	sum.compareCount = sum.swapCount = 0;
	MIN.compareCount = MIN.swapCount = 1000000000;
	MAX.compareCount = MAX.swapCount = 0;
	int zero = 1;
	int N = 1000;
	double mass[SIZE_T];
	double* p;
	p = mass;
	int i;
	int cor = 0;
	int per = 0;
	testInfo flow;
	srand(time(NULL));
	while (zero != 0)
	{
		printf(" Âûáåðèòå îäèí èç ïóíêòîâ íèæå è ââåäèòå åãî öèôðó â êîíñîëü. \n \n ");
		printf(" Ìåíþ \n 1. Ââåñòè ìàññèâ âðó÷íóþ \n 2. Âûâåñòè ìàññèâ íà ýêðàí \n 3. Âûáðàòü êîëè÷åñòâî ýëëåìåíòîâ â ìàññèâå. Ñåé÷àñ n= %d", N);
		printf(" \n 4. Çàïîëíèòü ìàññèâ ðàíäîìíûìè ýëåìåíòàìè \n 5. Îòñîðòèðîâàòü ìàññèâ ñîðòèðîâêîé ïóçûðüêîì. \n 6. Îòñîðòèðîâàòü ìàññèâ ñîðòèðîâêîé ðàñ÷åñêîé \n ");
		printf("7. Îòñîðòèðîâàòü ìàññèâ ïîðàçðÿäíîé ñîðòèðîâêîé. \n 8. Îòñîðòèðîâàòü ìàññèâ ñîðòèðîâêîé ñëèÿíèåì \n 0. Âûõîä\n");
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
			massiv (p,N);
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
			flow = FloatRadixSort(mass, N);
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
		if (zero > 4 && cor == 1)
			printf("Correct");
		if (zero > 4 && cor == 0)
			printf("No correct");
	}
		
	

	return 0;
}
