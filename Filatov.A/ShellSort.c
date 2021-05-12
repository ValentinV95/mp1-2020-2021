#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#endif
#include <stdio.h>

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
	double temp;
	for (int s = n / 2; s > 0; s /= 2)
	{
		for (int i = s; i < n; i++)
		{
			for (int j = i - s; (j >= 0) && (a[j] > a[j + s]); j -= s)
			{
				temp = a[j];
				a[j] = a[j + s];
				a[j + s] = temp;
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		printf("%lf\n", a[i]);
	}
	free(a);
	return 0;
}