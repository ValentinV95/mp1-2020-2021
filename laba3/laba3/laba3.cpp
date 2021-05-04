#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "ctime"
#include "string.h"
int a = 0;
int b = 0;
float tmp = 0;
void QuickSort(float* arr, int first, int last)
{
	int mid = (first + last) / 2;
	int i = first, j = last;
	float x = arr[mid];
	do {
		while (arr[i] < x)
		{
			i++;
			a++;
		}
		while (arr[j] > x)
		{
			j--;
			a++;
		}
		if (i <= j)
		{
			if (i < j)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
				a++;
				b++;
			}
			i++;
			j--;
		}
	} while (i <= j);

	if (i < last)
	{
		QuickSort(arr, i, last);
		a++;
	}
	if (first < j)
	{
		QuickSort(arr, first, j);
		a++;
	}
}
void InsertionSort(float arr[], const int size)
{
	for (int i = 1; i < size; i++)
		for (int j = i; j > 0; j--)
		{
			if (arr[j - 1] > arr[j])
			{
				tmp = arr[j];
				arr[j] = arr[j - 1];
				arr[j - 1] = tmp;
				b++;
			}
			a++;
		}
}
void Merge(float arr[], int begin, int end)
{
	int mid = begin + (end - begin) / 2;
	int i = begin;
	int j = mid + 1;
	int k = 0;
	int SortArr[1000];
	while (i <= mid && j <= end)
	{
		if (arr[i] <= arr[j])
		{
			SortArr[k] = arr[i];
			i++;
			b++;
		}
		else
		{
			SortArr[k] = arr[j];
			j++;
			b++;
		}
		k++;
		a++;
	}
	while (i <= mid)
	{
		SortArr[k] = arr[i];
		i++;
		k++;
		b++;
	}
	while (j <= end)
	{
		SortArr[k] = arr[j];
		j++;
		k++;
		b++;
	}
	for (int i = 0; i < k; i++)
	{
		arr[begin + i] = SortArr[i];

	}
}
void MergeSort(float arr[], int left, int right)
{
	int tmp = 0;
	if (left < right)
		if (left - right == 1)
		{
			if (arr[left] > arr[right])
			{
				tmp = arr[left];
				arr[left] = arr[right];
				arr[right] = tmp;
			}
		}
		else
		{
			MergeSort(arr, left, left + (right - left) / 2);
			MergeSort(arr, left + (right - left) / 2 + 1, right);
			Merge(arr, left, right);
		}
}
void createCounters(float* data, long* counters, long N) 
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
void radixPass(short offset, long N, float* source, float* dest, long* count) 
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
		b++;
	}
}
void radixSort(float* in, float* out, long* counters, long N) 
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
	b += N;
	free(counters);
	free(out);
}
void Correct(float arr[], int size)
{
	int a = 0;
	for (int i = 0; i < size - 1; i++)
	{
		if (arr[i] <= arr[i + 1])
			a++;
	}
	if (a == size - 1)
		printf("\nSorting is correct!\n");
	else
		printf("Sorting is incorrect!\n");
}
int main()
{
	float arr[1000];
	float* add;
	int size;
	int number = 0;
	int number2 = 0;
	srand(time(NULL));
	printf("Imput size: ");
	scanf("%d", &size);
	add = (float*)malloc(size * sizeof(float));
	long* counters;
	counters = (long*)malloc(256 * sizeof(float) * sizeof(long));
	printf("1)manually \n2)randomized\n");
	printf("How to enter an array?\n");
	
	scanf("%d", &number2);
	switch (number2)
	{
	case 1:
	{
		printf("Imput araay: ");
		for (int i = 0; i < size; i++)
			scanf("%f", &arr[i]);
		break;
	}
	case 2:
	{
		for (int i = 0; i < size; i++)
			arr[i] = rand() % 1000;
		break;
	}
	}
	printf("Injected array: \n");
	for (int i = 0; i < size; i++)
		printf("%f ", arr[i]);
	printf(" \n 1)Insertion Sort \n 2)Quick Sort \n 3)Merge Sort \n 4)Radix Sort \n");
	printf("Select sort: ");
	scanf("%d", &number);
	switch (number)
	{
	case 1:
		InsertionSort(arr, size);
		break;
	case 2:
		QuickSort(arr, 0, size - 1);
		break;
	case 3:
		MergeSort(arr, 0, size - 1);
	case 4:
		radixSort(arr, add, counters, size);
		break;
	default:
		printf("error");
		return 0;
		break;
	}
	printf("Sorted array: \n");
	for (int i = 0; i < size; i++)
		printf("%f ", arr[i]);
	Correct(arr, size);
	printf("\nNumber of comparisons: %d ", a);
	printf("\nNumber of permutations: %d", b);

}