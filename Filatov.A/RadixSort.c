#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#endif
#include <stdio.h>
#include <conio.h>

struct bytes8
{
	long long a : 64;
};

typedef struct bytes8 bytes;

union doublebit
{
	bytes b;
	double d;
};

typedef union doublebit doublebit;

void radix(doublebit *a, int l, int r, int k)
{
	if ((l >= r) || (k < 0))
		return;
	int i = l, j = r;
	while (i < j)
	{
		if (!((a[i].b.a >> k) & 1))
		{
			i++;
			continue;
		}
		if ((a[j].b.a >> k) & 1)
		{
			j--;
			continue;
		}
		long long temp = a[i].b.a;
		a[i].b.a = a[j].b.a;
		a[j].b.a = temp;
	}
	if (!((a[i].b.a >> k) & 1))
	{
		i++;
	}
	radix(a, l, i - 1, k - 1);
	radix(a, i, r, k - 1);
}

void radixmn(doublebit *a, int l, int r, int k)
{
	if ((l >= r) || (k < 0))
		return;
	int i = l, j = r;
	while (i < j)
	{
		if ((a[i].b.a >> k) & 1)
		{
			i++;
			continue;
		}
		if (!((a[j].b.a >> k) & 1))
		{
			j--;
			continue;
		}
		long long temp = a[i].b.a;
		a[i].b.a = a[j].b.a;
		a[j].b.a = temp;
	}
	if ((a[i].b.a >> k) & 1)
	{
		i++;
	}
	radixmn(a, l, i - 1, k - 1);
	radixmn(a, i, r, k - 1);
}

int main(int argc, char **argv)
{
	int n = atoi(argv[1]);
	FILE *f;
	f = fopen("test.txt", "r");
	doublebit* a;
	a = malloc(n * sizeof(double));
	for (int i = 0; i < n; i++)
	{
		fscanf(f, "%lf", &a[i]);
	}
	fclose(f);
	int i = 0, j =  n - 1;
	while (i < j)
	{
		if ((a[i].b.a >> 63) & 1)
		{
			i++;
			continue;
		}
		if (!((a[j].b.a >> 63) & 1))
		{
			j--;
			continue;
		}
		long long temp = a[i].b.a;
		a[i].b.a = a[j].b.a;
		a[j].b.a = temp;
	}
	if ((a[i].b.a >> 63) & 1)
	{
		i++;
	}
	radixmn(a, 0, i - 1, 62);
	radix(a, i, n - 1, 62);
	for (int i = 0; i < n; i++)
	{
		printf("%lf ", a[i].d);
	}
	free(a);
	return 0;
}