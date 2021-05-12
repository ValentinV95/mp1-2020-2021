#include "stdio.h"
#include "stdlib.h"
#include "locale.h"
// #include "malloc.h"
#include "time.h"
#include "string.h"
int comp = 0; //Количество сравнений
int perm = 0; //Количество перестановок

void swap(double* a, double* b) //Смена мест переменных
{
	double tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

int compare(const void* x1, const void* x2)
{
	return (*(double*)x1 - *(double*)x2);
}

void insert_sort(double* array, int size) // Функция сортировки вставками
{
	int k = 0;
	for(int i = 1; i < size ; i++)
        {
            k = i;
		    for(int j = i; (j > 0) && (array[j-1] > array[j]);j--)
		    {
                if (array[j-1] > array[j])
                {
                comp++;
                double tmp=array[j-1];
                array[j-1]=array[j];
                array[j]=tmp;
                perm++;
                k = j -1;
                }
            }
            if (k != 0) comp++;
	}
	comp += perm;
}

int partition(double* a, int l, int r) //Перестановка элементов (быстрая сортировка)
{
	double v = a[(l + r) / 2];
	int i = l;
	int j = r;
	while (i <= j)
	{
		while (a[i] < v) { ++i; ++comp; }
		while (a[j] > v) { --j; ++comp; }
		if (i >= j) break;
		swap(&a[++i], &a[--j]);
		++perm;
		++comp;
	}
	return j;
}

void quickSort(double* num, int l, int r) //Быстрая сортировка
{
	if (l < r)
	{
		int q = partition(num, l, r);
		quickSort(num, l, q);
		quickSort(num, q + 1, r);
	}
}

void merge(double* a, double* l, double* r, int lcount, int rcount) // Слияние двух упорядоченных массивов (Сортировка слиянием)
{
	int i = 0, j = 0, k = 0;
	while ((i < lcount) && (j < rcount))
	{
		++comp;
		++perm;
		if (l[i] < r[j]) a[++k] = l[++i];
		else a[++k] = r[++j];
	}
	while (i < lcount) {a[++k] = l[++i]; ++perm;}
	while (j < rcount) {a[++k] = r[++j]; ++perm;}
}

void mergeSort(double* num, int n) //Сортировка слиянием
{
	int mid;
        if (n < 2) return;
            mid = n / 2;
	double* l = (double*)malloc(mid * sizeof(double));
	double* r = (double*)malloc((n - mid) * sizeof(double));
        for (int i = 0; i < mid; i++) l[i] = num[i];
        for (int i = mid; i < n; i++) r[i - mid] = num[i];
            mergeSort(l, mid);
            mergeSort(r, n - mid);
        merge(num, l, r, mid, n - mid);
	free(l);
	free(r);
}

void createCounters(double* data, long* counters, long N) //Подсчёт значений байтов (Поразрядная сортировка)
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

void radixPass(short offset, long N, double* source, double* dest, long* count) //Сортировка по основанию с отсчетом сортировки (Поразрядная сортировка)
{
	double* sp;
	long s = 0, c, i, * cp = count;
	unsigned char* bp;
	for (i = 256; i > 0; --i, ++cp) {
		c = *cp;
        *cp = s;
        s += c;
	}
	bp = (unsigned char*)source + offset;
	sp = source;
	for (i = N; i > 0; --i, bp += sizeof(double), ++sp)
	{
		cp = count + *bp;
		dest[*cp] = *sp;
		++(*cp);
		++perm;
	}
}

void radixSort(double* in, double* out, long N) //Поразрядная сортировка
{
	long* count;
	long* counters = (long*)malloc(1024 * sizeof(long));
	long k = 0;
	createCounters(in, counters, N);
	for (unsigned short i = 0; i < sizeof(double); ++i) {
		count = counters + 256 * i;
		radixPass(i, N, in, out, count);
		for (long j = 0; j < N; ++j)
			in[j] = out[j];
	}
	while (in[k] >= 0 && k < N && !(k > 0 && in[k] <= 0 && in[k - 1] > 0)) ++k;
	for (int i = 0; i < N-k; ++i)
		in[i] = out[N-1-i];
	for (int i = 0; i < k; ++i)
		in[N - k + i] = out[i];
	perm += N;
	free(counters);
}

void CreateArray(double* arr, double* check, int n) //Заполнение исходного массива и check-array
{
	srand(time(NULL));
	for (int i = 0; i < n; ++i)
	{
		int s = rand();
		if (s % 2 == 0) s = 1;
		else s = -1;
		arr[i] = (double)rand() / RAND_MAX * 50000 * s;
		check[i] = arr[i];
	}

}
void CheckArray(double* a, double* check, int n) //Проверка сортировки
{
	int count = 0;
	qsort(check, n, sizeof(double), compare);
	for (int i = 0; i < n; ++i)
		if (check[i]>a[i] || check[i]<a[i]) ++count;
	if (count == 0) printf("Sorting is correct!\n");
	else printf("Sorting is not correct! :/\n");
}

int main()
{
	int length; /*Array length*/
	int a = 0;
	int exitcode = 0;
        printf("Input size: ");
            scanf_s("%d", &length);
	double* arr = (double *)malloc(length * sizeof(double)); /*Original array*/
	double* add = (double*)malloc(length * sizeof(double)); /*Additional array (radix sort)*/
	double* check = (double*)malloc(length * sizeof(double)); /*Check-array*/

	CreateArray(arr, check, length);
	printf("Input array: ");
	for (int i=0; i < length; i++) printf("%f    ", arr[i]); printf("\n");
        printf(" 1) Insertion sort\n");
        printf(" 2) Quicksort\n");
        printf(" 3) Merge sort\n");
        printf(" 4) Radix sort\n");
        printf("Select sort: ");
        scanf_s("%d", &a);
        //Выбор сортировки
	do
	{
		switch (a)
		{
		case 1:
			insert_sort(arr, length);
			exitcode = 1;
			break;
		case 2:
			quickSort(arr, 0, length - 1);
			exitcode = 1;
			break;
		case 3:
			mergeSort(arr, length);
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
            CheckArray(arr, check, length);
            printf("\n");
            printf("Number of comparisons: %d\n", comp);
            printf("Number of permutations: %d\n", perm);
			printf("Output array: ");
			for (int i=0; i < length; i++) printf("%f    ", arr[i]); printf("\n");
        free(arr);
        free(add);
        free(check);
}








