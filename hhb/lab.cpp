#define _CRT_SECURE_NO_WARNINGS // для корректной работы scanf()
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include <iostream>
#include <string.h>

int srav = 0;
int per = 0;

void SWAP(float* a, float* b)  // меняет местами значения двух переменных
{
	float c = *a;
	*a = *b;
	*b = c;
}

void BUBBLESORT(float* m, int n)  // сортировка пузырьком
{
	for (int i = 0; i < n - 1; i++)
	{
		int f = 0;
		for (int j = (n - 1); j > i; j--) //
		{
			if (m[j - 1] > m[j]) //
			{
				SWAP(&m[j - 1], &m[j]);
				f = 1;
				per++;
			}
			srav++;
		}
		if (f == 0) break;
	}
}

void SHELLSORT(float* m, int n)  // сортировка Шелла
{
	int step, i, j;
	for (step = n / 2; step > 0; step /= 2)
	{
		for (i = step; i < n; i++)
		{
			for (j = i - step; j >= 0; j = j - step)
			{
				srav++;
				if (m[j] > m[j + step])
				{
					SWAP(&m[j], &m[j + step]);
					per++;
				}
			}
		}
	}
}

void MERGE(float* m, int n, int l, int r)  // сортировка слиянием (объединение двух массивов в один)
{
	int mid = (l + r) / 2;
	float* m2;
	m2 = (float*)malloc(sizeof(float) * n);
	int a = l;
	int b = mid + 1;
	for (int i = l; i <= r; i++)
	{
		if ((a <= mid) && ((b > r) || (m[a] < m[b])))
		{
			m2[i] = m[a];
			a++;
			if (b <= r) srav++;
		}
		else
		{
			m2[i] = m[b];
			b++;
		}
	}
	for (int i = l; i <= r; i++)
	{
		srav++;
		if (m[i] != m2[i])
		{
			m[i] = m2[i];
			per++;
		}
	}
}

void MERGESORT(float* m, int n, int l, int r)  // сортировка слиянием (основная рекурсивная часть)
{
	int mid = (l + r) / 2;
	if (l < r)
	{
		MERGESORT(m, n, l, mid);
		MERGESORT(m, n, mid + 1, r);
		MERGE(m, n, l, r);
	}
}

void CREATE_COUNTERS(float* data, long* counters, long N)  // пораздрядная сортировка (подсчет значений байтов)
{
	unsigned char* bp = (unsigned char*)data;
	unsigned char* data_end = (unsigned char*)(data + N);
	unsigned short i;
	memset(counters, 0, 256 * sizeof(float) * sizeof(long));
	while (bp != data_end)
	{
		for (i = 0; i < sizeof(float); i++)
			counters[256 * i + *(bp++)]++;
	}
}

void RADIX_PASS(short offset, long N, float* source, float* dest, long* count)  // пораздрядная сортировка (сортировка по основанию системы счисления)
{
	float* sp;
	long s = 0, c, i, * cp = count;
	unsigned char* bp;
	for (i = 256; i > 0; --i, cp++)
	{
		c = *cp; *cp = s; s += c;
	}
	bp = (unsigned char*)source + offset;
	sp = source;
	for (i = N; i > 0; --i, bp += sizeof(float), ++sp)
	{
		cp = count + *bp;
		dest[*cp] = *sp;
		++(*cp);
		per++;
	}
}

void RADIXSORT(float* in, float* out, long N)  // пораздрядная сортировка (основная часть)
{
	long* count;
	long* counters = (long*)malloc(1024 * sizeof(long));
	long k = 0;
	CREATE_COUNTERS(in, counters, N);
	for (unsigned short i = 0; i < sizeof(float); i++)
	{
		count = counters + i * 256;
		RADIX_PASS(i, N, in, out, count);
		for (long j = 0; j < N; j++)
			in[j] = out[j];
	}
	while (in[k] >= 0 && k < N && !(k > 0 && in[k] <= 0 && in[k - 1] > 0)) k++;
	for (int i = 0; i < N - k; i++)
		in[i] = out[N - 1 - i];
	for (int i = 0; i < k; i++)
		in[N - k + i] = out[i];
	per += N;
	free(counters);
}

int main()
{
	float* array;
	int i, n, chm, chs, f = 0;
	system("chcp 1251");
	system("cls");
	srand(time(NULL));
	printf("Enter the size of the array: ");
	scanf_s("%d", &n);  // ввод пользователем длины массива
	array = (float*)malloc(n * sizeof(float));
	float* add = (float*)malloc(n * sizeof(float));
	printf("Press 1 to create a random array \nPress 2 for manual input array\n");
	scanf_s("%d", &chm);  // выбор пользователем самостоятельного ввода массива или создание рандомного
	switch (chm)
	{
	case 1:
		for (i = 0; i < n; i++)
			array[i] = ((float)rand() / (float)1.12345678) - 10000;  // создание рандомного массива
		break;
	case 2:
		for (i = 0; i < n; i++)
			scanf_s("%f", &array[i]);  // ввод пользователем каждого элемента массива
	}

	printf(" 1. Bubble Sort\n 2. Shell Sort\n 3. Merge sort\n 4. Radix sort\n");
	printf("Select sort: ");
	scanf_s("%d", &chs);  // выбор пользователем одной из представленных сортировок
	switch (chs)
	{
	case 1:
		BUBBLESORT(array, n);
		break;
	case 2:
		SHELLSORT(array, n);
		break;
	case 3:
		MERGESORT(array, n, 0, n - 1);
		break;
	case 4:
		RADIXSORT(array, add, n);
		break;
	}
	printf("Sorted array:\n");  // вывод отсортированного массива
	for (int i = 0; i < n; i++)
		printf("%f\n", array[i]);

	for (int i = 0; i < n - 1; i++)  // проверка на корректность сортировки
		if (array[i] > array[i + 1]) f = 1;
	switch (f)
	{
	case 0:

		printf("\nSorting is correct\n");
		break;
	case 1:
		printf("\nSomething went wrong\n");
		break;
	}

	printf("\nNumber of comparisons = %d \nNumber of permutations = %d", srav, per);
	// вывод количества перестановок и сравнений, выполненных при сортировке
	free(array);
	return 0;
}