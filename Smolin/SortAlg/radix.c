#include "stdio.h"
#include "malloc.h"

int perm_radix = 0;
int comp_radix = 0;

void createCounters(double* data, long* counters, long N)
{
	unsigned char* bp = (unsigned char*)data;
	unsigned char* dataEnd = (unsigned char*)(data + N);
	unsigned short i;
	memset(counters, 0, 256 * sizeof(double) * sizeof(long));
	while (bp != dataEnd) {
		for (i = 0; i < sizeof(double); i++)
			counters[256 * i + *(bp++)]++;
	}
}

void radixPass(short offset, long N, double* source, double* dest, long* count)
{
	double* sp;
	long s = 0, c, i, * cp = count;
	unsigned char* bp;
	for (i = 256; i > 0; --i, cp++) {
		c = *cp;		*cp = s;		s += c;
	}
	bp = (unsigned char*)source + offset;
	sp = source;
	for (i = N; i > 0; --i, bp += sizeof(double), ++sp)
	{
		cp = count + *bp;
		dest[*cp] = *sp;
		(*cp)++;
		perm_radix++;
	}
}

void radixSort(double* in, double* out, long N)
{
	long* count;
	long* counters = (long*)malloc(sizeof(double) * 256 * sizeof(long));
	double* temp;
	long k = 0;
	createCounters(in, counters, N);
	for (unsigned short i = 0; i < sizeof(double); i++) {
		count = counters + 256 * i;
		radixPass(i, N, in, out, count);
		for (long j = 0; j < N; j++)
			in[j] = out[j];
	}

	while (in[k] >= 0 && k < N && !(k > 0 && in[k] <= 0 && in[k - 1] > 0)) k++;
	for (int i = 0; i < N - k; i++)
		in[i] = out[N - 1 - i];
	for (int i = 0; i < k; i++)
		in[N - k + i] = out[i];

	perm_radix += N;

	printf("\nКоличество сравнений: %d\n", comp_radix);
	printf("\nКоличество перестановок: %d\n", perm_radix);

	free(counters);
}