#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <malloc.h>
#include <time.h>

int col_switch, col_compare;
void select_sort(int n, float* array, int col_switch, int col_compare) {
    int c, d, position;
    float swap;
    for (c = 0; c < (n - 1); c++)
    {
        position = c;

        for (d = c + 1; d < n; d++)
        {

            if (array[position] > array[d])
                position = d;
            col_compare++;

        }

        if (position != c)
        {

            swap = array[c];
            array[c] = array[position];
            array[position] = swap;
            col_switch++;

        }
    }
    printf("Sorted array:\n");
    for (c = 0; c < n; c++)
        printf("%f\t", array[c]);
    printf(" \n");
    printf("number of comparisons:%d\n", col_compare);
    printf("number of permutations:%d\n", col_switch);



}

void swap(float* a, float* b) {
    float t;

    t = *a, * a = *b, * b = t;
}

void qs(float* numbers, int left, int right)
{
    int pivot;
    int l_hold = left;
    int r_hold = right;
    pivot = numbers[left];
    while (left < right)
    {
        while ((numbers[right] >= pivot) && (left < right))
            right--;
        if (left != right)
        {
            numbers[left] = numbers[right];
            left++;
        }
        while ((numbers[left] <= pivot) && (left < right))
            left++;
        if (left != right)
        {
            numbers[right] = numbers[left];
            right--;
        }
    }
    numbers[left] = pivot;
    pivot = left;
    left = l_hold;
    right = r_hold;
    if (left < pivot)
        qs(numbers, left, pivot - 1);
    if (right > pivot)
        qs(numbers, pivot + 1, right);
}


void mergesort(float* a, int num) {
    int rght, rend;
    int i, j, m;
    float* b = (float*)malloc(num * sizeof(float));

    for (int f = 0; f < num; f++) {
        b[f] = a[f];
        col_switch++;
    }


    for (int k = 1; k < num; k *= 2)
    {
        for (int left = 0; left + k < num; left += k * 2)
        {
            rght = left + k;
            rend = rght + k;
            if (rend > num) rend = num; col_compare++;
            m = left; i = left; j = rght;
            while (i < rght && j < rend)
            {
                if (a[i] <= a[j])
                {
                    b[m] = a[i]; i++;
                    col_compare++;
                    col_switch++;
                }
                else
                {
                    b[m] = a[j]; j++;
                    col_compare++;
                    col_switch++;
                }
                m++;
            }
            while (i < rght)
            {
                b[m] = a[i];
                i++; m++;
                col_switch++;
            }
            while (j < rend)
            {
                b[m] = a[j];
                j++; m++;
                col_switch++;
            }
            for (m = left; m < rend; m++)
            {
                a[m] = b[m];
                col_switch++;
            }
        }
    }
}

void swap_mass(float* a, float* b, size_t n) {
    for (size_t i = 0; i < n; i++)
    {
        float tmp = a[i];
        a[i] = b[i];
        b[i] = tmp;

    }
}
void radix_sort(float array[], size_t count)
{
    int zeroes = 0;

    // float temp_array[count]; // c99 only
    float* temp_array = (float*)malloc(count * sizeof(float));
    float* warray = temp_array;

    for (uint32_t radix = 1; radix; radix <<= 1)
    {
        uint32_t* iarray = (uint32_t*)array;

        int count0 = 0;
        int count1 = 0;

        zeroes = 0;
        for (int j = 0; j < count; ++j)
            zeroes += !(iarray[j] & radix);

        count1 = zeroes;

        for (int j = 0; j < count; ++j)
            if (iarray[j] & radix)
            {

                warray[count1] = array[j];
                ++count1;
            }
            else
            {

                warray[count0] = array[j];
                ++count0;
            }
        col_compare++;


        swap_mass((float*)warray, array, count);
    }

    if (zeroes < count)
    {


        memcpy(warray + (count - zeroes), array, zeroes * sizeof(float));

        for (int d = 0, j = count - 1; j >= zeroes; j--, d++) {
            warray[d] = array[j];

        }
        memcpy(array, warray, count * sizeof(float));
        col_switch++;
    }
}

void bubbleSort(float* a, int size) {
    int i, j;
    float tmp;
    for (i = 1; i < size; i++) {
        for (j = 1; j < size; j++) {
            if (a[j] < a[j - 1]) {
                tmp = a[j];
                a[j] = a[j - 1];
                a[j - 1] = tmp;
            }
        }
    }
}


void main()
{

    int  n, c, sort_var;
    float temp;
    printf("enter the number of array values\n");
    scanf("%d", &n);
    float* arr = (float*)malloc(n * sizeof(float));
    float* checking_arr = (float*)malloc(n * sizeof(float));
    printf("Enter %d values\n", n);

    for (c = 0; c < n; c++)
        scanf("%f", &arr[c]);

    memcpy(checking_arr, arr, sizeof(float) * n);

    printf("Select a sorting method:\n");
    printf("selection sort 1\n");
    printf("quick sort 2\n");
    printf("merge sort 3\n");
    printf("radix sort 4\n");

    scanf("%d", &sort_var);

    if (sort_var == 1) {
        select_sort(n, arr, col_switch, col_compare);
    }
    if (sort_var == 2) {
        qs(arr, 0, n - 1);
        printf("Sorted array:\n");
        for (c = 0; c < n; c++)
            printf("%f\t", arr[c]);
        printf(" \n");
        printf("number of comparisons:%d\n", col_compare);
        printf("number of permutations:%d\n", col_switch);


    }
    if (sort_var == 3) {
        mergesort(arr, n);
        printf("Sorted array:\n");
        for (c = 0; c < n; c++)
            printf("%f\t", arr[c]);
        printf(" \n");
        printf("number of comparisons:%d\n", col_compare);
        printf("number of permutations:%d\n", col_switch);

    }
    if (sort_var == 4) {
        radix_sort(arr, n);
        printf("Sorted array:\n");
        for (c = 0; c < n; c++)
            printf("%f\t", arr[c]);
        printf(" \n");
        printf("number of comparisons:%d\n", col_compare);
        printf("number of permutations:%d\n", col_switch);
    }

    bubbleSort(checking_arr, n);
    printf("Checking for correct execution by bubble sorting:\n");
    printf("\n");
    int check = 0;

    for (int i = 0;i < n; i++) {
        if (arr[i] == checking_arr[i]) {
            check++;
        }
    }
    if (check == n) {
        printf("sorted correctly!");
    }
    else {
        printf("sorted uncorrectly!");
    }


}

