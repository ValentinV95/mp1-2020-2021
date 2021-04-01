#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#endif
#include <stdio.h>
#include <malloc.h>
#include <string.h>

void merge(double* a, double* b, int l, int r)
{
	if (l >= r)
	{
		return;
	}
	int m = (l + r) / 2;
	merge(b, a, l, m);
	merge(b, a, m + 1, r);
	int i = l, j = m + 1;
	while ((i <= m) || (j <= r))
	{
		if ((j <= r) && ((i > m) || (b[i] > b[j])))
		{
			a[i + j - m - 1] = b[j];
			j++;
		}
		else
		{
			a[i + j - m - 1] = b[i];
			i++;
		}
	}
	return;
}

int main(int argc, char **argv)
{
	int n = atoi(argv[1]);
	FILE *f;
	f = fopen("test.txt", "r");
	double *a, *b;
	a = malloc(n * sizeof(double));
	b = malloc(n * sizeof(double));
	for (int i = 0; i < n; i++)
	{
		fscanf(f, "%lf", &a[i]);
		b[i] = a[i];
	}
	fclose(f);
	merge(a, b, 0, n - 1);
	for (int i = 0; i < n; i++)
	{
		printf("%f\n", a[i]);
	}
	free(a);
	free(b);
	return 0;
}