#define _CRT_SECURE_NO_WARNINGS // для корректной работы scanf()
#include <malloc.h>
#include <time.h>
#include <iostream>
#include "stdio.h"
#include "stdlib.h"
#include "locale.h"
#include "string.h"
int crav = 0; /*Количество сравнений*/
int per = 0; /*Количество перестановок*/


void swap(float* a, float* b) //Меняет местами
{
	float tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void buble_sort(float* array, int size) //Сортировка пузырьком для проверки сортировки расческой
{
	for (int i = 0; i < size - 1; i++)
	{
		int f = 0;
		for (int j = size - 2 ; j > i - 1; j--)
		{
			if (array[j] > array[j+1])
			{
				swap(&array[j], &array[j + 1]);
				per++;
				f = 1;
			}
			crav++;
			if (f == 1)
				break;
		}
	}
}

void selection_sort(float* array, int size) //Сортировка выбором
{
	for (int i = 0; i < size - 1; i++)
	{
		int min = i;
		for (int j = i + 1; j < size; j++)
		{
			crav++;
			if (array[j] < array[min])
			{
				min = j;

			}
		}
		if (min != i)
		{
			swap(&array[i], &array[min]);
			per++;
		}
	}

}

void comb_sort(float* array, int size) //Сортировка расческой
{
	double factor = 1.2473309;
	int step = size - 1;
	while (step >= 1)
	{
		for (int i = 0; i + step < size; i++)
		{
			if (array[i] > array[i + step])
			{
				swap(&array[i], &array[i + step]);
				per++;
			}
			crav++;
		}
		step /= factor;
	}
}

void merge(float* array,  int left, int right, int n )
{
	int mid = (left + right) / 2;
	float* dopmas;
	dopmas = (float*)malloc(n * sizeof(float));
	int start1 = left;
	int start2 = mid + 1;
	for (int i = left; i <= right; i++)
	{
		if ((start1 <= mid) && ((start2 > right) || (array[start1] < array[start2])))
		{
			dopmas[i] = array[start1];
			start1++;
			if (start2 <= right) crav++;
		}
		else
		{
			dopmas[i] = array[start2];
			start2++;
		}
	}
		for (int i = left; i <= right; i++)
		{
			crav++;
			if (array[i] != dopmas[i])
			{
				array[i] = dopmas[i];
				per++; //В данном случае перестановка - просто изменение исходного массива
			}
		}	
		free(dopmas);
}
	


void mergesort(float* array,  int left, int right, int n) // Сортировка слиянием
{
	int mid = (left + right) / 2;
	if (left < right)
	{
		mergesort(array,  left, mid, n);
		mergesort(array, mid + 1,right, n);
		merge(array,  left, right, n);
	}
}

void createCounters(float* data, long* counters, long N) // Считаем значения байт для radixSort
{
	unsigned char* bp = (unsigned char*)data;
	unsigned char* dataEnd = (unsigned char*)(data + N);
	unsigned short i;
	memset(counters, 0, 256 * sizeof(float) * sizeof(long));
	while (bp != dataEnd) {
		for (i = 0; i < sizeof(float); i++)
			counters[256 * i + *(bp++)]++;
	}
}

void radixPass(short offset, long N, float* source, float* dest, long* count) //Сортировка подсчетом для radixSort
{
	float* sp;
	long s = 0, c, i, * cp = count;
	unsigned char* bp;
	for (i = 256; i > 0; --i, cp++) {
		c = *cp;		
		*cp = s;		
		s += c;
	}
	bp = (unsigned char*)source + offset;
	sp = source;
	for (i = N; i > 0; --i, bp += sizeof(float), ++sp)
	{
		cp = count + *bp;
		dest[*cp] = *sp;
		(*cp)++;
		per++;
	}
}

void radixSort(float* in, float* out, long* counters, long N) // Поразрядная сортировка
{
	long* count;
	long help = 0;
	createCounters(in, counters, N);
	for (unsigned short i = 0; i < sizeof(float); i++) {
		count = counters + 256 * i;
		radixPass(i, N, in, out, count);
		for (long j = 0; j < N; j++)
			in[j] = out[j];
	}
	while (help < N && in[help] >= 0)
		help++;
	for (int i = 0; i < N - help; i++)
		in[i] = out[N - 1 - i];
	for (int i = 0; i < help; i++)
		in[N - help + i] = out[i];
	per += N;
	free(counters);
	free(out);
}

int main() // Главная часть
{
	float* array;
	int i, n, ind;
	system("chcp 1251");
	system("cls");
	printf("Введите длину массива: ");
	scanf_s("%d", &n);
	array = (float*)malloc(n * sizeof(float));

	srand(time(NULL));

	printf("1 - Сгенерировать случайный массив;\n");
	printf("2 - Ввести массив вручную.\n         ");
	scanf_s("%d", &ind);

	if (ind == 1)
		for (i = 0; i < n; i++)
		{
			array[i] = (float)rand() - 10000;
		}
	else 
		for (i = 0; i < n; i++)
		{
			scanf_s("%f", &array[i]);
		}

	printf("1 - сортировка вставками;\n");
	printf("2 - сортировка расческой;\n");
	printf("3 - сортировка слиянием;\n");
	printf("4 - поразрядная сортировка.\n");
	printf("Введите требуемый метод сортировки: ");
	scanf_s("%d", &ind);

	switch (ind)
	{
	case 1:
		selection_sort(array, n);
		break;
	case 2:
		comb_sort(array, n);
		buble_sort(array, n); 
		break;
	case 3:
		mergesort(array, 0, n - 1, n);
		break;
	case 4:
		float* add;
		add = (float*)malloc(n * sizeof(float));
		long* counters;
		counters = (long*)malloc(256 * sizeof(float) * sizeof(long));
		radixSort(array, add, counters, n); 
		break;
	}
	
	ind = 0;
	printf("%f\n", array[0]);
	for (i = 1; i < n; i++)
	{
		printf("%f\n", array[i]);
		if (array[i - 1] > array[i])
			ind = 1;
	}
	printf("\nsrav=%d per=%d " , crav, per);
	printf("\nЕсли 0, то верно. Если 1, то неверно: ");
	printf("%d", ind);
	free(array);
	return 0;
}