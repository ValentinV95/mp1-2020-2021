#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <stdlib.h>
#include <malloc.h>

int comp_merge = 0;
int perm_merge = 0;
int comp_radix = 0;
int perm_radix = 0;
int comp_quick = 0;
int perm_quick = 0;
int comp_selection = 0;
int perm_selection = 0;

void mergesort(float* array, int n);
void merge(float* arr, float* l, float* r, int lcount, int rcount) 
{
	int i = 0, j = 0, k = 0;
	while ((i < lcount) && (j < rcount))
	{
		comp_merge++;
		perm_merge++;
		if (l[i] < r[j]) arr[k++] = l[i++];
		else arr[k++] = r[j++];
	}
	while (i < lcount) 
	{
		arr[k++] = l[i++];perm_merge++;
	}
	while (j < rcount) 
	{
		arr[k++] = r[j++];perm_merge++;
	}
}

void mergesort(float* array, int n) 
{
	int mid;
	if (n < 2) return;
	mid = n / 2;
	float* l = (float*)malloc(mid * sizeof(float));
	float* r = (float*)malloc((n - mid) * sizeof(float));
	for (int i = 0; i < mid; i++) l[i] = array[i];
	for (int i = mid; i < n; i++) r[i - mid] = array[i];
	mergesort(l, mid);
	mergesort(r, n - mid);
	merge(array, l, r, mid, n - mid);
	free(l);
	free(r);
}

void createCounters(float* array, long* counters, int N)
{
	int i;
	unsigned char* bp = (unsigned char*)array;
	unsigned char* end = (unsigned char*)(array + N);

	memset(counters, 0, 256 * sizeof(float) * sizeof(long));
	while (bp != end)
	{
		for (i = 0; i < sizeof(float); i++)
		{
			counters[256 * i + *(bp++)]++;
		}
	}
}
void radixPass(short Offset, int size, float* array, float* dest, long* count)
{
	float* sp;
	long s, c, i, * cp;
	unsigned char* bp;

	s = 0;
	cp = count;
	for (i = 256; i > 0; --i, ++cp)
	{
		c = *cp;
		*cp = s;
		s += c;
	}

	bp = (unsigned char*)array + Offset;
	sp = array;
	for (i = size; i > 0; --i, bp += sizeof(float), ++sp)
	{
		cp = count + *bp;
		dest[*cp] = *sp;
		(*cp)++;
		perm_radix++;
	}
}
void radixLastPass(short Offset, int size, float* array, float* dest, long* count)
{
	float* sp;
	long sum, c, i, * cp;
	unsigned char* bp;

	long numNeg = 0;
	for (i = 128; i < 256; i++) numNeg += count[i];

	sum = numNeg;
	cp = count;
	for (i = 0; i < 128; ++i, ++cp)
	{
		c = *cp;
		*cp = sum;
		sum += c;
		perm_radix++;
	}

	cp = count + 255;
	sum = 0; *cp = 0;
	for (i = 255; i >= 128; i--, cp--)
	{
		sum += *cp;
		*cp = sum;
	}
	bp = (unsigned char*)array + Offset;
	sp = array;
	for (i = size; i > 0; i--, bp += sizeof(float), sp++)
	{
		cp = count + *bp;
		if (*bp < 128)
		{
			dest[*cp] = *sp;
			(*cp)++;
			perm_radix++;
			comp_radix++;
		}
		else
		{
			(*cp)--;
			dest[*cp] = *sp;
			perm_radix++;
			comp_radix++;
		}
	}
}
void radixSort(float* array, int size)
{
	int i;
	float* temp;
	float* dest = (float*)malloc(sizeof(float) * size);
	long* counters = (long*)malloc(sizeof(float) * 256 * sizeof(long));
	long* count;

	createCounters((float*)array, counters, size);

	for (i = 0; i < sizeof(float) - 1; i++)
	{
		count = counters + 256 * i;
		radixPass(i, size, array, dest, count);
		temp = array;
		array = dest;
		dest = temp;
	}
	count = counters + 256 * (sizeof(float) - 1);
	radixLastPass(sizeof(float) - 1, size, array, dest, count);

	temp = array;
	array = dest;
	dest = temp;

	perm_radix += size;
	free(dest);
	free(counters);
}
void swap(float* a, float* b) 
{
	float tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}
int partition(float* a, int l, int r)
{
	float v = a[(l + r) / 2];
	int i = l;
	int j = r;
	while (i <= j)
	{
		while (a[i] < v) { i++; }
		while (a[j] > v) { j--; }
		if (i >= j) break;
		swap(&a[i++], &a[j--]);
		perm_quick++;
		comp_quick++;
	}
	return j;
}

void quicksort(float* array, int l, int r) 
{
	if (l < r)
	{
		int q = partition(array, l, r);
		quicksort(array, l, q);
		quicksort(array, q + 1, r);
	}
}

void selectionSort(float* num, int size)
{
	float temp;
	int min;
	for (int i = 0; i < size - 1; i++)
	{
		min = i; 
		for (int j = i + 1; j < size; j++) 
		{
			if (num[j] < num[min]) 
				min = j;
			comp_selection++;
		}
		temp = num[i];      
		num[i] = num[min];
		num[min] = temp;
		perm_selection++;
	}
}