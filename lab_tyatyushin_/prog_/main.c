#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <locale.h>
#include <math.h>

void bubble_sort();

void comb_sort();

void merge();

void mergeSort();

void ed_cnts(double* sv, long* cnts, long N)
{
    unsigned short i;
	unsigned char* bp = (unsigned char*)sv;
	unsigned char* svEnd = (unsigned char*)(sv + N);

	for (int i = 0; i < 256 * sizeof(double); i++)
	cnts[i] = 0;

	while (bp != svEnd)
	{
	    for (i = 0; i < sizeof(double); i++)
		cnts[256 * i + *(bp++)]++;
	}

}

void Radix_Pass(short Offset, long N, double* source, double* dl, long* cnt, int *per)
{
    unsigned char* bp;
	double* as;
	long s = 0, d, i, * dc = cnt;


	for (i = 256; i > 0; i--, ++dc)
    {
        d = *dc;
		*dc = s;
		s += d;
	}
	bp = (unsigned char*)source + Offset;
	as = source;
	for (i = N; i > 0; --i, bp += sizeof(double), ++as)
	{
		dc = cnt + *bp; dl[*dc] = *as; (*dc)++;  per[0] = per[0] + 1;
	}
}

void Radix_Sort(double* vh, double* iz, long* cnts, long N, int *zx)
{
    long* cnt;
	unsigned short i;
	int k = 0;
	ed_cnts(vh, cnts, N);

	for (i = 0; i < sizeof(double); i++)
	{
		cnt = cnts + 256 * i;
		Radix_Pass(i, N, vh, iz, cnt, zx);
		for (long j = 0; j < N; j++){
			vh[j] = iz[j];
			zx[0] = zx[0] + 1;
		}
	}
	while (vh[k] >= 0 && k < N)
		k++;
	for (int i = 0; i < N - k; i++)
	{
		vh[i] = iz[N - 1 - i];
	}
	for (int i = 0; i < k; i++)
	{
		vh[N - k + i] = iz[i];
	}
}

int compare ();

int main()
{
    int pr[1] = {0};
    int sr[1] = {0};
    int E;
    long int g;
    int i=0;

    setlocale(0,"");
    printf("Введите число соответсвующее алгоритму сортировки\n1 - сортировка пузырьком\n2 - сортировка расчёской\n3 - сортировка слиянием\n4 - поразрядная сортировка\n5 - проверка\n");
    scanf("%d", &E);
    printf("Введите кол-во чисел массива: ");
    scanf("%ld", &g);



    if (E==1){
            double *arr;
       arr = (double*)malloc(g*sizeof(double));
       printf("Введите элементы массива: ");
       for(i=0;i<g;i++)
       scanf("%lf", &arr[i]);
       bubble_sort(arr, g);
       printf("Отсортированный массив: ");
       for(i=0 ; i<g ;  i++)
       printf("%lf ",arr[i]);
    }

    if (E==2){
            double *arr;
       arr = (double*)malloc(g*sizeof(double));
       printf("Введите элементы массива: ");
       for(i=0;i<g;i++)
       scanf("%lf", &arr[i]);
       comb_sort(arr, g);
       printf("Отсортированный массив: ");
       for(i=0 ; i<g ;  i++)
        printf("%lf ",arr[i]);
    }

    if (E==3)
    {
        double *arr;
       arr = (double*)malloc(g*sizeof(double));
       printf("Введите элементы массива: ");
       for(i=0;i<g;i++)
       scanf("%lf", &arr[i]);
       mergeSort(arr, 0, g - 1, sr, pr);
       printf("Отсортированный массив: ");
       for(i=0 ; i<g ;  i++)
       printf("%lf ",arr[i]);
       printf("\n");
       printf("Количество перестановок: %d\n", pr[0]);
       printf("Количество сравнений : %d\n", sr[0]);
    }
    if (E==4)
    {
		double* arr = (double*)malloc(g * sizeof(double));
		double* arr1 = (double*)malloc(g * sizeof(double));
        long* cnts = (long*)malloc(1024 * sizeof(double));

		printf("\n");

		printf("Введите элементы массива: ");
       for(i=0;i<g;i++)
       scanf("%lf", &arr[i]);

		Radix_Sort(arr, arr1, cnts,g, pr);

		printf("Отсортированный массив: ");
		for(i=0 ; i<g ;  i++)
        printf("%lf ",arr[i]);

		printf("\nКоличество перестановок : %d\n", pr[0]);

    }
    if(E==5) {
        double arr[g];
        printf("Введите элементы массива: ");
       for(i=0;i<g;i++)
       scanf("%lf", &arr[i]);
       qsort(arr, g, sizeof(double), compare);
       printf("\nОтсортированный массив: ");
        for( i = 0 ; i < g; i++ )
            printf("%lf ", arr[i]);
    }
    return(0);
}




void bubble_sort(double *arr, int g)
{
    double q;
    int i=0,j=0;
    int s,p;
    s=0;
    p=0;

    for(i=0 ; i<g-1 ; i++) {
        for(j=0 ; j<g-i-1 ; j++){
            if(arr[j]>arr[j+1]) {

                q=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=q;
                s++;
                p++;
            }
            else
            s++;
        }
    }
    printf("%d - кол-во сравнений\n%d - кол-во перестановок\n", s, p);
}

void comb_sort(double *arr, int size)
{
    int s,p;
    double factor = 1.2473309;
    int step=size-1;
    while (step >=1 )
    {
        for(int i=0; i+step<size;i++)
        {
            if (arr[i]>arr[i+step])
            {
                double tmp=arr[i];
                arr[i]=arr[i+step];
                arr[i+step]=tmp;
                s++;
                p++;
            }
            else
            s++;
        }
        step=step/factor;
    }
    printf("%d - кол-во сравнений\n%d - кол-во перестановок\n", s,p);
}

void merge(double arr[], int l, int m, int r, int *s, int *p)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    double Left[n1], Right[n2];

    for (i = 0; i < n1; i++){
        Left[i] = arr[l + i];
    }
    for (j = 0; j < n2; j++){
        Right[j] = arr[m + 1 + j];
    }

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (Left[i] <= Right[j]) {
            arr[k] = Left[i];
            i++;
            p[0]++;
            s[0]++;
        }
        else {
            arr[k] = Right[j];
            j++;
            p[0]++;
            s[0]++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = Left[i];
        i++;
        k++;
        p[0]++;
    }

    while (j < n2) {
        arr[k] = Right[j];
        j++;
        k++;
        p[0]++;
    }
}


void mergeSort(double arr[], int l, int r, int *s, int *p)
{
    if (l < r) {

        int m = l + (r - l) / 2;

        mergeSort(arr, l, m, s, p);
        mergeSort(arr, m + 1, r, s, p);

        merge(arr, l, m, r, s, p);
    }
}

int compare (const void * a, const void * b)
{
    if (*(double*)a > *(double*)b) return 1;
    else if (*(double*)a < *(double*)b) return -1;
    else return 0;
}
