#include "stdio.h"
#include "stdlib.h"
#include "locale.h"
#include "malloc.h"
#include "time.h"
#include "string.h"
int comp = 0; /*Number of comparisons*/
int perm = 0; /*Number of permutations*/

void swap(float* a, float* b) /*Swap variables*/
{
	float tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

int compare(const void* x1, const void* x2)
{
	return (*(float*)x1 - *(float*)x2);
}

void insertsort(float* array, int size) /*Insertion sort*/
{
	int k = 0;
	for (int i = 1; i < size; i++)
	{
		k = i;
		for (int j = i; (j > 0) && (array[j - 1] > array[j]); j--)
		{
			if (array[j - 1] > array[j])
			{
				float tmp = array[j - 1];
				array[j - 1] = array[j];
				array[j] = tmp;
				perm++;
				k = j - 1;
			}
		}
		if (k != 0) comp++;
	}
	comp += perm;
}

int partition(float* a, int l, int r) /*Permutation of elements (quicksort)*/
{
	float v = a[(l + r) / 2];
	int i = l;
	int j = r;
	while (i <= j)
	{
		while (a[i] < v) { i++; comp++; }
		while (a[j] > v) { j--; comp++; }
		if (i >= j) break;
		swap(&a[i++], &a[j--]);
		perm++;
		comp++;
	}
	return j;
}

void quicksort(float* array, int l, int r) /*Quicksort (main part)*/
{
	if (l < r)
	{
		int q = partition(array, l, r);
		quicksort(array, l, q);
		quicksort(array, q + 1, r);
	}
}

void merge(float* arr, float* l, float* r, int lcount, int rcount) /*Merge of two ordered arrays (merge sort)*/
{	
	int i = 0, j = 0, k = 0;
	while ((i < lcount) && (j < rcount))
	{
		comp++;
		perm++;
		if (l[i] < r[j]) arr[k++] = l[i++];
		else arr[k++] = r[j++];
	}
	while (i < lcount) {arr[k++] = l[i++]; perm++;}
	while (j < rcount) {arr[k++] = r[j++]; perm++;}
}

void mergesort(float* array, int n) /*Merge sort (main part)*/
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

void createCounters(float* data, long* counters, long N) /*Counting values of bytes (radix sort)*/
{
	unsigned char* bp = (unsigned char*)data;
	unsigned char* dataEnd = (unsigned char*)(data + N);
	unsigned short i;
	memset(counters, 0, 256 * sizeof(float) * sizeof(long));
	while (bp != dataEnd) {
		for (i = 0; i < sizeof(float); i++)
			counters[256 * i + *(bp++)]++;
	}
}

void radixPass(short offset, long N, float* source, float* dest, long* count) /*Sorting by the radix with counting sort (radix sort)*/
{
	float* sp;
	long s = 0, c, i, * cp = count;
	unsigned char* bp;
	for (i = 256; i > 0; --i, cp++) {
		c = *cp;		*cp = s;		s += c;
	}
	bp = (unsigned char*)source + offset;
	sp = source;
	for (i = N; i > 0; --i, bp += sizeof(float), ++sp) 
	{
		cp = count + *bp;	
		dest[*cp] = *sp;		
		(*cp)++;
		perm++;
	}
}

void radixSort(float* in, float* out, long N) /*Radix sort (main part)*/
{
	long* count;
	long* counters = (long*)malloc(1024 * sizeof(long));
	long k = 0;
	createCounters(in, counters, N);
	for (unsigned short i = 0; i < sizeof(float); i++) {
		count = counters + 256 * i;
		radixPass(i, N, in, out, count);
		for (long j = 0; j < N; j++)
			in[j] = out[j];
	}
	while (in[k] >= 0 && k < N && !(k > 0 && in[k] <= 0 && in[k - 1] > 0)) k++;
	for (int i = 0; i < N-k; i++)
		in[i] = out[N-1-i];
	for (int i = 0; i < k; i++)
		in[N - k + i] = out[i];
	perm += N;
	free(counters);
}

void CreateArray(float* arr, float* check, int n) /*Filling the original array and check-array*/
{
	srand(time(NULL));
	for (int i = 0; i < n; i++)
	{
		int s = rand();
		if (s % 2 == 0) s = 1;
		else s = -1;
		arr[i] = (float)rand() / RAND_MAX * 50000 * s;
		check[i] = arr[i];
	}

}
void CheckArray(float* arr, float* check, int n) /*Checking the sort*/
{
	int count = 0;
	qsort(check, n, sizeof(float), compare);
	for (int i = 0; i < n; i++)
		if (check[i]>arr[i] || check[i]<arr[i]) count++;
	if (count == 0) printf("Array has been sorted successfully!\n");
	else printf("Array hasn't been sorted successfully :/\n");
}

int main()
{
	int length; /*Array length*/
	int a = 0;
	int exitcode = 0;
	printf("Enter the length of array: ");
	scanf_s("%d", &length);
	float* arr = (float*)malloc(length * sizeof(float)); /*Original array*/
	float* add = (float*)malloc(length * sizeof(float)); /*Additional array (radix sort)*/
	float* check = (float*)malloc(length * sizeof(float)); /*Check-array*/
	CreateArray(arr, check, length);
	printf("1 - insertion sort\n");
	printf("2 - quicksort\n");
	printf("3 - merge sort\n");
	printf("4 - radix sort\n");
	printf("Enter the number of sort: ");
	scanf_s("%d", &a);
	/*Sort selection*/
	do
	{
		switch (a)
		{
		case 1:
			insertsort(arr, length);
			exitcode = 1;
			break;
		case 2:
			quicksort(arr, 0, length - 1);
			exitcode = 1;
			break;
		case 3:
			mergesort(arr, length);
			exitcode = 1;
			break;
		case 4:
			radixSort(arr, add, length);
			exitcode = 1;
			break;
		default:
			printf("Wrong value, try again\n\n");
			printf("Enter the number of sort: ");
			scanf_s("%d", &a);
		}
	} while (exitcode != 1);
	printf("Length of array: %d\n", length);
	printf("Number of sort: %d\n", a);
	printf("Number of comparisons: %d\n", comp);
	printf("Number of permutations: %d\n", perm);
	CheckArray(arr, check, length);
	free(arr);
	free(add);
	free(check);
}