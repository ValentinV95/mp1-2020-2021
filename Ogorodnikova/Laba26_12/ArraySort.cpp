#include <cstdlib>
#include <stdio.h>
#include "ArraySort.h"
#include <string.h>
#include "If_and_swap.h"



void insert_sort(float* arr, int n)
{
    int j = 0;
	float t = 0;
    for (int i = 1; i < n; ++i)
    {
        t = arr[i];
        for (j = i; j > 0; --j)
        {
            if (arr[j - 1] > t)
            {
                arr[j] = arr[j - 1];
                _if++;
                _swap++;
            }
            else
            {
                _if++;
                break;
            }
        }
        arr[j] = t;
    }
}

void shell_sort(float* arr, int n)
{
    int j = 0;
    float t;
    for (int step = n / 2; step > 0; step /= 2)
    {
        for (int i = step; i < n; i++)
        {
            t = arr[i];
            for (j = i; j >= step; j -= step)
            {
                if (t < arr[j - step])
                {
                    arr[j] = arr[j - step];
                    _if++;
                    _swap++;
                }
                else
                {
                    _if++;
                    break;
                }
            }
            arr[j] = t;
        }
    }
}

void merge(float* arr, float* left, float* right, int l, int r)
{
    int i = 0, j = 0, k = 0;
    while ((i < l) && (j < r))
    {
        _if++;
        _swap++;
        if (left[i] < right[j])
        {
            
            arr[k++] = left[i++];
        }
        else
        {
            arr[k++] = right[j++];
        }
    }
    while (i < l)
    {
        _swap++;
        arr[k++] = left[i++];
    }
    while (j < r)
    {
        _swap++;
        arr[k++] = right[j++];
    }
}

void merge_sort(float* array, int n)
{
    int pivot = n / 2;
    if (n < 2)
    {
        _if++;
    }
    else
    {
        float* left = (float*)malloc(pivot * sizeof(float));
        float* right = (float*)malloc((n - pivot) * sizeof(float));
        for (int i = 0; i < pivot; i++)
        {
            left[i] = array[i];
        }
        for (int i = pivot; i < n; i++)
        {
            right[i - pivot] = array[i];
        }
        merge_sort(left, pivot);
        merge_sort(right, n - pivot);
        merge(array, left, right, pivot, n - pivot);
        free(left);
        free(right);
    }
}

void hoar_sort(float* arr, int first, int n)
{
    int i = first, j = n;
	float c = 0;
    const float pivot = arr[(first + n) / 2];
    do
    {
        while (arr[i] < pivot)
        {
            _if++;
            ++i;
        }

        while (arr[j] > pivot)
        {
            _if++;
            --j;
        }

        if (i <= j)
        {
            if (i < j)
            {
                _if++;
                c = arr[i];
                arr[i] = arr[j];
                arr[j] = c;
            }
            i++;
            j--;
        }

    } while (i <= j);


    if (i < n)
    {
        _if++;
       hoar_sort(arr, i, n);
    }
    if (j > first)
    {
        _if++;
        hoar_sort(arr, first, j);
    }
}


// radix sort
void count_add(float* arr, long* counters, const int n)
{
    unsigned char* pr = (unsigned char*)arr;
    unsigned char* data = (unsigned char*)(arr + n);

    memset(counters, 0, 256 * sizeof(float) * sizeof(int));
    while (pr != data)
    {
        _if++;
        for (int i = 0; i < sizeof(float); i++)
        {
            counters[256 * i + *(pr++)]++;
        }
    }
}

inf _radix(const int set, const int size, float* arr, float* dest, long* count)
{
    inf radix{0, 0};
    long int s = 0, c = 0, * cp = NULL;
    unsigned char* pr = NULL;
    long int num = 0;

    for (int i = 128; i < 256; i++)
    {
        num += count[i];
    }

    s = num;
    cp = count;
    for (int i = 0; i < 128; ++i, ++cp)
    {
        c = *cp;
        *cp = s;
        s += c;
    }

    cp = count + 255;
    s = 0;
    *cp = 0;
	
    for (int i = 254; i >= 128; cp--, i--)
    {
        s += *cp;
        *cp = s;
    }
	
    pr = (unsigned char*)arr + set;
	
    float* sp = arr;
    for (int i = size; i > 0; --i, pr += sizeof(float), ++sp)
    {
        cp = count + *pr;
        if (*pr < 128)
        {
            _if++;
            dest[*cp] = *sp;
            (*cp)++;
        }
        else
        {
            _if++;
            (*cp)--;
            dest[*cp] = *sp;
        }
        radix.count_swap++;
        _swap++;
    }
    return radix;
}

inf pass_radix(int set, int n, float* source, float* dest, long* count)
{
    inf radix{ 0, 0 };
    float* sp = NULL;
    long s = 0, c = 0, * cp = NULL;
    unsigned char* pr = NULL;

    s = 0;
    cp = count;
    for (int i = 256; i > 0; --i, ++cp)
    {
        c = *cp;
        *cp = s;
        s += c;
    }

    pr = (unsigned char*)source + set;
    sp = source;
    for (int i = n; i > 0; --i, pr += sizeof(float), ++sp)
    {
        cp = count + *pr;
        dest[*cp] = *sp;
        (*cp)++;
        radix.count_swap++;
        _swap++;
    }
    return radix;
}

inf radix_sort(float* arr, int size)
{
    inf radix{ 0, 0 },
        rad{ 0, 0 };
    float* tmp = NULL,
        * pre_arr = (float*)malloc(sizeof(float) * size);
    long int* counters = (long int*)malloc(sizeof(float) * 256 * sizeof(int));
    long* count;

    count_add((float*)arr, counters, size);

    for (int i = 0; i < sizeof(float) - 1; i++)
    {
        count = counters + 256 * i;
        rad = pass_radix(i, size, arr, pre_arr, count);
        radix.count_swap += rad.count_swap;
        _swap++;
        radix.count_if += rad.count_if;
        _if++;
        tmp = arr;
        arr = pre_arr;
        pre_arr = tmp;
    }

    count = counters + 256 * (sizeof(float) - 1);
    rad = _radix(sizeof(float) - 1, size, arr, pre_arr, count);
    radix.count_swap += rad.count_swap;
    _swap++;
    radix.count_if += rad.count_if;
    _if++;
    tmp = arr;
    arr = pre_arr;
    pre_arr = tmp;

    free(pre_arr);
    free(counters);
    return radix;
}


void print_if_and_swap()
{
    printf("If: %d, Swap: %d \n", _if, _swap);
}
void obnull_if_swap()
{
    _if = 0;
    _swap = 0;
}