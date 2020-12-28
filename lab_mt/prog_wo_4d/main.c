#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <locale.h>

void bubble_sort();

void comb_sort();

void merge();

void mergeSort();

void printArray();

int get_max ();

void radix_sort ();

double main()
{
    int pr[1] = {0};
    int sr[1] = {0};
    int E;
    int g;
    int *mas;
    double *arr;
    int i=0,j=0;

    setlocale(0,"");
    printf("¬ведите число соответсвующее алгоритму сортировки\n1 - сортировка пузырьком\n2 - сортировка расчЄской\n3 - сортировка сли€нием\n4 - поразр€дна€ сортировка\n");
    scanf("%d", &E);
    printf("¬ведите кол-во чисел массива: ");
    scanf("%d", &g);


    arr = (double*)malloc(g*sizeof(double));
    mas = (int*)malloc(g*sizeof(int));


    if(E==4)
    {
        for(i=0; i<g; i++) {
        printf("mas[%d]=",i);
        scanf("%d", &mas[i]);
        }
    }
    else
    {
        for(i=0; i<g; i++) {
        printf("arr[%d]=",i);
        scanf("%lf", &arr[i]);
        }
    }

    if (E==1)
    bubble_sort(arr, g);
    if (E==2)
    comb_sort(arr, g);
    if (E==3){
        mergeSort(arr, 0, g - 1, sr, pr);
        printf("\n");
        printf(" оличество перестановок: %d\n", pr[0]);
        printf(" оличество сравнений : %d\n", sr[0]);
    }
    if (E==4)
    {
    radix_sort (mas, g, sr, pr);
    printf("\n");
        printf(" оличество перестановок: %d\n", pr[0]);
        printf(" оличество сравнений : %d\n", sr[0]);
    }


    if(E==4)
    {
        for(i=0 ; i<g ;  i++)
        {
        printf("%d ",mas[i]);
        }
    }
    else
    {
        for(i=0 ; i<g ;  i++)
        printf("%lf ",arr[i]);
    }

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

    double L[n1], R[n2];

    for (i = 0; i < n1; i++){
        L[i] = arr[l + i];
        p[0]++;
        s[0]++;
    }
    for (j = 0; j < n2; j++){
        R[j] = arr[m + 1 + j];
        p[0]++;
        s[0]++;
    }

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
            p[0]++;
            s[0]++;
        }
        else {
            arr[k] = R[j];
            j++;
            p[0]++;
            s[0]++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
        p[0]++;
    }

    while (j < n2) {
        arr[k] = R[j];
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


void printArray(double A[], int size)
{

    for (int i = 0; i < size; i++)
        printf("%lf ", A[i]);
    printf("\n");
}

int get_max (int arr[], int g, int *s, int *p){
   int max = arr[0];
   for (int i = 1; i < g; i++)
      if (arr[i] > max){
         max = arr[i];
         p[0]++;
         s[0]++;
      }
      s[0]++;
   return max;
}
void radix_sort (int arr[], int g, int *s, int *p){
   int bucket[10][10], bucket_cnt[10];
   int i, j, k, r, NOP = 0, divisor = 1, lar, pass;
   lar = get_max (arr, g, s, p);
   while (lar > 0){
      NOP++;
      lar /= 10;
      s[0]++;
   }
   for (pass = 0; pass < NOP; pass++){
      for (i = 0; i < 10; i++){
         bucket_cnt[i] = 0;
         p[0]++;
         s[0]++;
      }
      for (i = 0; i < g; i++){
         r = (arr[i] / divisor) % 10;
         bucket[r][bucket_cnt[r]] = arr[i];
         bucket_cnt[r] += 1;
         p[0]++;
         s[0]++;
      }
      i = 0;
      for (k = 0; k < 10; k++){
         for (j = 0; j < bucket_cnt[k]; j++){
            arr[i] = bucket[k][j];
            i++;
            p[0]++;
            s[0]++;
         }
      }
      divisor *= 10;
   }
}

