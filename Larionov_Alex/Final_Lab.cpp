#include <iostream>
#include"Lab_sorts.h"
#include<stdio.h>
#include <math.h>
int main()
{
	srand(time(NULL));
	int a, b, i, c, g, last = 0;
	double* massive, d = 0, l = 0;
	printf("Choose massive's length -");
	scanf("%d", &a);
	massive = (double*)malloc(a * sizeof(double));
	if (massive == NULL)
	{
		printf("Произошла ошибка. Запросили слишком много памяти??\n");
		return -1;
	}
	printf("For massive of random floating point numbers press - 1\n For massive of ordered floating point numbers press - 2\n For massive of reverse ordered floating point numbers press - 3\n To insert your own massive press - 4\n");
	scanf("%d", &b);
	switch (b)
	{
	case 1:
	{printf("Massive of random floating point numbers.\n");
	for (i = 0; i < a; i++)
	{
		massive[i] = pow(-1,i)*rand()+((double)rand() / (double)((RAND_MAX) + 1));
		printf("%lf\n", massive[i]);
	}
	break;
	}
	case 2:
	{
		printf("Massive of ordered floating point numbers.\n");
		for (i = 0; i < a; i++)
		{
			d++;
			massive[i] = d + ((double)rand() / (double)(RAND_MAX + 1));
			printf("%f\n", massive[i]);
		}
		break;
	}
	case 3:
	{
		printf("Massive of reverse ordered floating point numbers.\n");
		for (i = 0; i < a; i++)
		{
			d++;
			massive[i] = -1 * d + (double)(rand() / (double)(RAND_MAX + 1));
			printf("%f\n", massive[i]);
		}
		break;
	}
	case 4: {for (i = 0; i < a; i++) { printf("Massive element number %d = ",i); scanf("%lf", &l); massive[i] = l; }}
	}
	printf("For insertion sort press - 1\n For Shell's sort press - 2\n For radix sort press - 3\n For merge sort press - 4\n");
	scanf("%d", &c);
	switch (c)
	{
	case 1: {insertion_sort(massive, a); break; }
	case 2: {Shell_sort(massive, a); break; }
	case 3: {radixSort(massive, a); break; }
	case 4:
	{
		double* spare = (double*)malloc(a * sizeof(double));
		mergeSort(massive, spare, 0, a - 1);
	}
	break;
	}
	for (i = 0; i < a; i++)
	{
		printf("%f\n", massive[i]);
	}
	printf("\nPress 1 to check for sort outcome errors\n");
	scanf("%d", &g);
	if (g == 1)
	{
		for (i = 0; i < a - 1; i++)
		{
			if (massive[i] > massive[i + 1])
			{
				printf("sort went wrong\n", "%d%f%d%f", "massive element ", i, " = ", massive[i], "massive element ", i + 1, " = ", massive[i + 1]);
			}
			else
			{
				last = last + 1;
			}
		}
	}
	if (last != 0) { printf("Sort is Ok"); }
	return(0);
}