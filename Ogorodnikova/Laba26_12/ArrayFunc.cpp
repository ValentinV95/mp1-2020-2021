#include <cstdlib>
#include <stdio.h>
#include "ArrayF.h"
void size_arr(float** arr, int* n)
{
	printf("Enter size array: ");
	scanf("%d", n);
	free(*arr);
	*arr = (float*)malloc(*n * sizeof(float));
	printf("Done \n");
	system("pause");
}

void print_arr(float* arr, int n)
{
	for(int i = 0; i < n; i++)
	{
		printf("%f ", arr[i]);
	}
	printf("\n");
	system("pause");
}

void keyboard_in(float* arr, int n)
{
	printf("Enter %d elements: ", n);
	for(int i = 0; i < n; i++)
	{
		scanf("%f", &arr[i]);
	}
}

void arr_rand(float* arr, int n)
{
	int max = 100, min = -100;
	for(int i = 0; i < n; i++)
	{
		arr[i] = (float)(rand()) / RAND_MAX * (max - min) + min;
	}
	printf("Done\n");
	system("pause");
}