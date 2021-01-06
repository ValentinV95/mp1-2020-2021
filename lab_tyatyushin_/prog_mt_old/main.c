#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <locale.h>
#include <math.h>

void bubble_sort();

void comb_sort();

void merge();

void mergeSort();

int get_max ();

void radix_sort ();

int compare ();

double main()
{
    int pr[1] = {0};
    int sr[1] = {0};
    int E;
    int g,n;
    int *mas, mas1[10];
    double *arr, arr1[10];
    int i=0,j=0;

    setlocale(0,"");
    printf("Введите число соответсвующее алгоритму сортировки\n1 - сортировка пузырьком\n2 - сортировка расчёской\n3 - сортировка слиянием\n4 - поразрядная сортировка\n5 - проверка\n");
    scanf("%d", &E);
    printf("Введите кол-во чисел массива: ");
    scanf("%d", &g);
    arr = (double*)malloc(g*sizeof(double));


    if (E==4)
    {
        printf("Введите элементы массива: ");
        for(i=0;i<g;i++){
        scanf("%lf", &arr1[i]);
        }
    }
    else
    {
        printf("Введите элементы массива: ");
        for(i=0;i<g;i++){
        scanf("%lf", &arr[i]);
        }
    }

    if (E==4)
    {

        printf ("Введите точность: ");
        scanf ("%d", &n);
    }

    if (E==1)
    bubble_sort(arr, g);
    if (E==2)
    comb_sort(arr, g);
    if (E==3)
    {
        mergeSort(arr, 0, g - 1, sr, pr);
        printf("\n");
        printf("Количество перестановок: %d\n", pr[0]);
        printf("Количество сравнений : %d\n", sr[0]);
    }
    if (E==4)
    {
        for(i=0; i<g; i++){
            mas1[i]=(int)(arr1[i]*pow(10,n));

        }
        radix_sort (mas1, g, pr);
        for(i=0; i<g; i++){
            arr1[i]=(double)(mas1[i]*pow(10,-n));

        }
        printf("\n");
        printf("Количество перестановок: %d\n", pr[0]);
    }
    if(E==5) qsort(arr, g, sizeof(double), compare);

    if (E==4)
    {
        for(i=0 ; i<g ;  i++)
        printf("%lf ",arr1[i]);
    }
    else
    {
        for(i=0 ; i<g ;  i++)
        printf("%lf ",arr[i]);
    }

    if(E==5){
        printf("\nAfter sorting the list is: ");
        for( i = 0 ; i < g; i++ )
        {
            printf("%lf ", arr[i]);
        }

    }

    printf("\n");

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




int get_max (int arr[], int g, int *p){
   int max = arr[0];
   for (int i = 1; i < g; i++)
      if (arr[i] > max){
         max = arr[i];
         p[0]++;
      }
   return max;
}
void radix_sort (int arr[], int g, int *p){
   int yas[10][10], yas_cnt[10];
   int i, j, k, r, ne = 0, divisor = 1, l, pss;
   l = get_max (arr, g, p);
   while (l > 0){
      ne++;
      l /= 10;
   }
   for (pss = 0; pss < ne; pss++){
      for (i = 0; i < 10; i++){
         yas_cnt[i] = 0;
         p[0]++;

      }
      for (i = 0; i < g; i++){
         r = (arr[i] / divisor) % 10;
         yas[r][yas_cnt[r]] = arr[i];
         yas_cnt[r] += 1;
         p[0]++;

      }
      i = 0;
      for (k = 0; k < 10; k++){
         for (j = 0; j < yas_cnt[k]; j++){
            arr[i] = yas[k][j];
            i++;
            p[0]++;
         }
      }
      divisor *= 10;
   }
}
int compare (const void * a, const void * b)
{
    if (*(double*)a > *(double*)b) return 1;
    else if (*(double*)a < *(double*)b) return -1;
    else return 0;
}
