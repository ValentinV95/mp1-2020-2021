#include <iostream>
#include"Lab_sorts.h"
#include <math.h>
int main()
{
	srand(15);
	int a, b, i, c;
	double *massive;
	printf("Choose massive's length -");
	scanf("%d", &a);
	massive=(double *)malloc(a * sizeof(double));
	if (massive == NULL) 
	{
		printf("Произошла ошибка. Запросили слишком много памяти??\n");
		return -1;
	}
	printf("For massive of random floating point numbers press - 1\n For massive of ordered floating point numbers press - 2\n For massive of reverse ordered floating point numbers press - 3\n");
	scanf("%d", &b);
	switch (b)
	{
	case'1':
	{printf("Massive of random floating point numbers.");
	for (i = 0; i < a; i++)
	{
		massive[i] = (rand() / RAND_MAX);
		printf("%f\n", massive[i]);
	}
	}
	case'2':
	{
		printf("Massive of ordered floating point numbers.");
		for (i = 0; i < a; i++)
		{
			massive[i] = i + (rand() / (RAND_MAX + 1));
			printf("%f\n", massive[i]);
		}
	}
	case'3':
	{
		printf("Massive of reverse ordered floating point numbers.");
		for (i = 0; i < a; i++)
		{
			massive[i] = -10 * i + (rand() / (RAND_MAX + 1));
			printf("%f\n", massive[i]);
		}
	}
	}
	printf("For insertion sort press - 1\n For Shell's sort press - 2\n For radix sort press - 3\n For merge sort press - 4\n");
	scanf("%d", &c);
	switch (c)
	{
	case'1': insertion_sort(massive, a);
	case'2': Shell_sort(massive, a);
	case'3': radixSort(massive, a);
	case'4':
	{
		double *spare = (double *)malloc(a * sizeof(double));
		merge_sort(massive,spare, 0, a);
	}
	}
	for (i = 0; i < a; i++)
	{
		printf("%f\n", massive[i]);
	}
	return(0);
}