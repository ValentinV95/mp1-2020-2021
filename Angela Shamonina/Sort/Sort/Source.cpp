#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h> 
#include <malloc.h>
#include <math.h>
#include <string.h>
#include<time.h>
int count1 = 0;
int count2 = 0;
int flag = 0;
int checkflag = 0;
int K, n, k;
float* a, * check;
int compare(const void* x1, const void* x2)
{
    return (*(float*)x1 - *(float*)x2);
}
void bubble_sort(float* array, const size_t size)
{
    for (int i = 0; i < size - 1; i++)
    {
        flag = 0;
        for (int j = size - 2; j > i - 1; j--)

        {

            count1++;
            if (array[j] > array[j + 1])
            {
                count2++;
                float tmp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = tmp;
                flag = 1;
            }
        }
        if (flag == 0)
            break;
    }
}
void checking(float* array, float* check, int n)
{
    qsort(check, n, sizeof(float), compare);
    for (int i = 0; i < n; i++) {
        if (array[i] != check[i])
        {
            checkflag = 1;
            break;
        }
        else {
            checkflag = 0;
        }
    }
    if (flag == 1)
    {
        printf("Sorting was performed incorrectly\n");
    }
    else {
        printf("Sorting was performed correctly\n");
    }


}
void quicksort(float* a, int L, int R)
{
    int i = L, j = R;
    float q = a[(L + R) / 2];
    do {
        while (a[i] < q) { i++; count1++; }
        while (a[j] > q) { j--; count1++; }
        if (i <= j)
        {
            float w = a[i];
            a[i] = a[j];
            a[j] = w;
            i++; j--; count1++; count2++;
        }
    } while (i <= j);
    if (L < j)
        quicksort(a, L, j);
    if (i < R)
        quicksort(a, i, R);
}

void merge(float* array, float* second, int l, int q, int r)
{
    int h, i, j, k;
    q = (l + r) / 2; h = l; i = l; j = q + 1;
    while ((h <= q) && (j <= r))
    {
        count1++;
        if (array[h] <= array[j])
        {
            count2++;
            second[i] = array[h];
            h++;
        }
        else
        {
            count2++;
            second[i] = array[j];
            j++;
        }
        i++;
    }  if (h > q)
    {
        for (k = j; k <= r; k++)
        {
            count2++;
            second[i] = array[k];
            i++;
        }
    }
    else
    {
        for (k = h; k <= q; k++)
        {
            count2++;
            second[i] = array[k];
            i++;
        }
    } for (k = l; k <= r; k++)
    {
        array[k] = second[k];
    }
}
void mergesort(float* array, float* second, int l, int r) {
    if (l < r) {
        int q = (l + r) / 2;
        mergesort(array, second, l, q);
        mergesort(array, second, q + 1, r);
        merge(array, second, l, q, r);
    }
}

void createCounters(float* in, long* counters, long N) {
    unsigned char* bp = (unsigned char*)in;
    unsigned char* end = (unsigned char*)(in + N);
    memset(counters, 0, 256 * sizeof(float) * sizeof(long));
    while (bp != end) {
        for (int i = 0; i < sizeof(float); i++) {
            counters[256 * i + *(bp++)]++;

        }
    }

}
void radixPass(short Offset, long N, float* in, float* out, long* count) {
    float* sp;
    long s, c, * cp;
    unsigned char* bp;
    s = 0;
    cp = count;
    for (int i = 256; i > 0; --i, ++cp) {
        c = *cp;
        *cp = s;
        s += c;
    }
    bp = (unsigned char*)in + Offset;
    sp = in;
    for (int i = N; i > 0; --i, bp += sizeof(float), ++sp) {
        cp = count + *bp;
        out[*cp] = *sp;
        (*cp)++;
        count2++;
    }

}
void signedradixLastPass(short Offset, long N, float* in, float* out, long* count) {
    float* sp;
    long s, c, * cp, numNeg = 0;
    unsigned char* bp;
    for (int i = 128; i < 256; i++) numNeg += count[i];
    s = numNeg;
    cp = count;
    for (int i = 0; i < 128; ++i, ++cp) {
        c = *cp;
        *cp = s;
        s += c;
    }
    cp = count + 255;
    s = 0; *cp = 0;
    for (int i = 255; i >= 128; i--, cp--) {
        s += *cp;
        *cp = s;
    }
    bp = (unsigned char*)in + Offset;
    sp = in;
    for (int i = N; i > 0; i--, bp += sizeof(float), sp++) {
        cp = count + *bp;
        if (*bp < 128) {
            out[*cp] = *sp;
            (*cp)++;
        }
        else {
            (*cp)--;
            out[*cp] = *sp;
        }
        count2++;
    }

}
void radixSort(float* in, float* out, int N) {
    int i;
    long* counters = (long*)malloc(sizeof(float) * 256 * sizeof(long));
    long* count;
    createCounters((float*)in, counters, N);
    for (i = 0; i < sizeof(float) - 1; i++) {
        count = counters + 256 * i;
        radixPass(i, N, in, out, count);
        float* tmp = in;
        in = out;
        out = tmp;
    }
    count = counters + 256 * (i);
    signedradixLastPass(i, N, in, out, count);

}


int main()
{

    printf("Enter the length of the array: ");
    scanf_s("%d", &n);
    printf("Method of filling the array:\n ");
    printf("1. The random array\n ");
    printf("2. Keyboard input\n ");
    printf("Enter the method number:\n ");
    scanf_s("%d", &k);
    if (k == 1) {
        a = (float*)malloc(n * sizeof(float));
        check = (float*)malloc(n * sizeof(float));
        for (int i = 0; i < n; i++) {
            a[i] = rand() * 0.0001 * pow(-1, i);
            check[i] = a[i];
        }
    }
    if (k == 2) {
        a = (float*)malloc(n * sizeof(float));
        check = (float*)malloc(n * sizeof(float));
        for (int i = 0; i < n; i++) {
            printf("a[%d]= ", i);
            scanf("%f", &a[i]);
            check[i] = a[i];
        }
    }
    printf("Available sorting options:\n ");
    printf("1. Bubble sort\n ");
    printf("2. Quicksort\n ");
    printf("3. Mergesort\n ");
    printf("4. Radixsort\n ");
    printf("Enter the sorting number:\n ");
    scanf_s("%d", &K);
    srand(time(0));

    if (K == 1) {

        bubble_sort(a, n);
        checking(a, check, n);
        printf("Number of comparisons: ");
        printf("%d\n ", count1);
        printf("Number of permutations: ");
        printf("%d\n ", count2);
    }
    if (K == 2) {
        quicksort(a, 0, n - 1);
        checking(a, check, n);
        printf("Number of comparisons: ");
        printf("%d\n ", count1);
        printf("Number of permutations: ");
        printf("%d\n ", count2);
    }
    if (K == 3) {
        float* b;

        b = (float*)malloc(n * sizeof(float));

        mergesort(a, b, 0, n - 1);
        checking(a, check, n);
        printf("Number of comparisons: ");
        printf("%d\n ", count1);
        printf("Number of permutations: ");
        printf("%d\n ", count2);
    }
    if (K == 4) {
        float* out;
        out = (float*)malloc(n * sizeof(float));
        radixSort(a, out, n);
        checking(a, check, n);

        printf("Number of permutations:");
        printf("%d\n ", count2);
    }

    for (int i = 0; i < n; i++) {
        printf("a[%d]= ", i);
        printf("%f\n", a[i]);

    }



    return 0;
}