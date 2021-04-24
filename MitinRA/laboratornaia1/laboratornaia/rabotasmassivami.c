#define scanf scanf_s
#include"sortirovki.h"
#include<vcruntime.h>

void sozdaniemassiva(float* a,int N)
{
	srand(1);
	for (int i = 0; i < N; i++)
		a[i] = rand() / 100.0-32767/200.0;
	
}

void vivodmassiva(float* a,int N)
{
	for (int i = 0; i < N; i++)
	{
		printf("%7d \t", i);
	}
	printf("\n");
	for (int i = 0; i < N; i++)
	{
		printf("%5.2f \t", a[i]);
	}
	printf("\n \n");
}

void vivodmassiva2(float* a,int N)
{
	for (int i = 0; i < N; i++)
	{
		printf("%d\t%g\n", i, a[i]);
	}
	printf("\n");
}

void zapolnenievrucnuu(float* a, int N)
{
	for (int i = 0; i < N; i++)
	{
		scanf("%f", &a[i]);
	}
}

int proverkamassiva(float *a,float* c,int N)
{
	if (c == NULL)
		return 0;
	sortbubble(c, N);
	for (int i = 0; i < N; i++)
	{
		if (a[i] != c[i])
			return 0;
	}
	return 1;
}

void arraycopy(float* a, float* b,int N)
{
	for (int i = 0; i < N; i++)
	{
		b[i] = a[i];
	}
}