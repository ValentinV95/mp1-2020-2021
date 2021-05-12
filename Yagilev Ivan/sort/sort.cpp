
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <ctime>
#include <math.h>
#include <string.h>
int compare = 0;
int change = 0;
int point = 0;
void merge(float* array, float* secondsecond, int lev, int sred, int right)
{
    sred = (lev + right) / 2;
    int minleft = lev;
    int minright = sred + 1;
    int minsec = lev;
    while ((minleft <= sred) && (minright <= right)){
        if (array[minleft] <= array[minright]){
            secondsecond[minsec] = array[minleft];
            minleft++;
            change++;
        }
        else{
            secondsecond[minsec] = array[minright];
            minright++;
            change++;
        }
        minsec++;
        compare++;
    }
    if (minleft > sred){
        for (int i = minright; i <= right; i++){
            secondsecond[minsec] = array[i];
            minsec++;
            change++;
        }
    }
    else{
        for (int i = minleft; i <= sred; i++){
            secondsecond[minsec] = array[i];
            minsec++;
            change++;
        }
    }

    for (int i = lev; i <= right; i++){
        array[i] = secondsecond[i];
    }
}

void create_counters(float* data, int* counters, int size)
{
    unsigned char* bp = (unsigned char*)data;
    unsigned char* dataEnd = (unsigned char*)(data + size);
    unsigned short i;
    memset(counters, 0, 256 * sizeof(float) * sizeof(int));
    while (bp != dataEnd)
    {
        for (i = 0; i < sizeof(float); i++)
        {
            counters[256 * i + *(bp++)]++;
        }
    }
}

void radix_pass(short offset, int size, float* source, float* dest, int* count)
{
    float* sp;
    int s = 0, c, i, * cp = count;
    unsigned char* bp;
    for (i = 256; i > 0; --i, cp++)
    {
        c = *cp;		*cp = s;		s += c;
    }
    bp = (unsigned char*)source + offset;
    sp = source;
    for (i = size; i > 0; --i, bp += sizeof(float), ++sp)
    {
        cp = count + *bp;
        dest[*cp] = *sp;
        (*cp)++;
        change++;
    }
}

void radix_sort(float* array, int size)
{
    float* temporary_array = (float*)malloc(size * sizeof(float));
    int* counters = (int*)malloc(1024 * sizeof(int));
    int* count;
    int k = 0;
    create_counters(array, counters, size);
    for (unsigned short i = 0; i < sizeof(float); i++)
    {
        count = counters + 256 * i;
        radix_pass(i, size, array, temporary_array, count);
        for (int j = 0; j < size; j++)
        {
            array[j] = temporary_array[j];
        }
    }
    while (array[k] >= 0 && k < size && !(k > 0 && array[k] <= 0 && array[k - 1] > 0)) k++;
    for (int i = 0; i < size - k; i++)
    {
        array[i] = temporary_array[size - 1 - i];
    }
    for (int i = 0; i < k; i++)
    {
        array[size - k + i] = temporary_array[i];
    }
    change++;
    
    free(temporary_array);
    free(counters);
}

void merge_sort(float* array, float* secondsecond, int lev, int right)
{
    if (lev < right)
    {
        int middle = (lev + right) / 2;
        merge_sort(array, secondsecond, lev, middle);
        merge_sort(array, secondsecond, middle + 1, right);
        merge(array, secondsecond, lev, middle, right);
    }
}

void bubble_sort(float* array, int size) {
    for (int i = 0; i < size - 1; i++){
        for (int j = size - 2; j > i - 1; j--){
            if (array[j] > array[j + 1]){
                float tmp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = tmp;
                point = 1;
            }
        }
        if (point == 0)
            break;
    }
}

void select_sort(float* array, int size) {
    for (int i = 0; i < size; i++) {
        int min_position = i;
        for (int j = i + 1; j < size; j++) {
            if (array[min_position] > array[j]) {
                min_position = j;
                change++;
            }
            compare++;
        }
        float tmp = array[min_position];
        array[min_position] = array[i];
        array[i] = tmp;

    }
}

void comb_sort(float* array, int size)
{
    float factor = 1.24733;
    int step = size - 1;
    while (step >= 1){
        for (int i = 0; i + step < size; i++){
            if (array[i] > array[i + step]){
                float temp = array[i];
                array[i] = array[i + step];
                array[i + step] = temp;
                change++;

            }
            compare++;
        }
        step /= factor;
    }
}

int main(){
    float* a;
    int i, n;

    system("chcp 1251");
    system("cls");

    printf("|CREATING AND SORTING ARRAY (min-max)| (float)\n");
    printf("Enter the size of the array:\n(insert the number)\n");
    scanf ("%d", &n);
    
    a = (float*)malloc(n * sizeof(float));
    
    printf("How do you want to fill the array?\n(insert the number)\n");
    printf("1.Manually\n2.Random numbers\n");

    int answer;
    float second[sizeof a];
    scanf ("%d",&answer);
    
    if (answer == 1) {
        for (i = 0; i < n; i++) {
            printf("a[%d] = ", i);
            scanf ("%f", &a[i]);
        }
    }
    
    if (answer == 2) {
        srand(time(NULL));
        for (i = 0; i < n; i++) {
            a[i] = ((float)rand()) / ((float)RAND_MAX) + rand()%1500*pow(-1,i);
            printf("a[%d] = %f\n", i,a[i]);
        }
    }
    
    printf("Unsorted array:\n[");
    for (i = 0; i < n; i++)
        printf("|%f|", a[i]);
    printf("]\n");
    
    
    printf("Select sorting type:\n(insert the number)\n1.Selection sort o(N^2)\n2.Comb sort o(N*logN)\n3.Merge sort o(N*logN)\n4.Radix sort o(N)\n");
    scanf("%d",&answer);
    
    if (answer==1) {
        select_sort(a,n);
    }
    
    if (answer == 2) {
        comb_sort(a,n);
    }
    
    if (answer == 3) {
        merge_sort(a,second,0,n-1);
    }
    
    if (answer == 4) {
        radix_sort(a, n);
    }
    printf("Sorted array:\n(min-max)\n[");
    for (i = 0; i < n; i++)
        printf("|%f| ", a[i]);
    printf("]\n\n");

    bubble_sort(a, n);

    if (point==0) {
        printf("Array sorted correctly\n");
    }
    else {
        printf("Array is not sorted correctly\n");
    }

    printf("Number of changes - %d\n", change);
    printf("Number of compares - %d\n", compare);

    printf("\nNeed to reverse an array? (max-min)\n1.Yes\n2.No\n(insert the number)\n");
    scanf ("%d",&answer);

    if (answer==1) {
        float kb = a[0];
        for (int i = 0; i < (n/2); i++) {
            kb = a[i];
            a[i] = a[n - 1 - i];
            a[n - i - 1] = kb;
        }

        printf("Sorted array:\n(max-min)\n[");
        for (i = 0; i < n; i++)
            printf("|%f| ", a[i]);
    }

    free(a);
    getchar();   getchar();

    return 0;
}