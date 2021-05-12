#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#endif
#include <stdio.h>
#include <malloc.h>

int main(int argc, char **argv)
{
	int n = atoi(argv[1]);
	FILE *f;
	f = fopen("test.txt", "r");
	double* a;
	a = malloc(n * sizeof(double));
	for (int i = 0; i < n; i++)
	{
		fscanf(f, "%lf", &a[i]);
	}
	fclose(f);
	int m;
	double temp;
	for (int i = 0; i < n; i++)
	{
		m = i;
		for (int j = i + 1; j < n; j++)
		{
			if (a[j] < a[m])
				m = j;
		}
		temp = a[i];
		a[i] = a[m];
		a[m] = temp;
	}
	for (int i = 0; i < n; i++)
	{
		printf("%lf\n", a[i]);
	}
	free(a);
	return 0;
}