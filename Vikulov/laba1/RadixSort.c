#include <string.h>
#include <stdint.h>
#include <malloc.h>

void swap(float* a, float* b, size_t n) {
    for (size_t i = 0; i < n; i++)
    {
        float tmp = a[i];
        a[i] = b[i];
        b[i] = tmp;

    }
}
void radix_sort(float array[], size_t count, size_t* count_com, size_t* count_inv)
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


        swap((float**)warray, array, count, count_com, count_inv);
    }

    if (zeroes < count)
    {


        memcpy(warray + (count - zeroes), array, zeroes * sizeof(float));

        for (int d = 0, j = count - 1; j >= zeroes; j--, d++) {
            warray[d] = array[j];
            (*count_inv)++;
        }
        memcpy(array, warray, count * sizeof(float));
    }
    (*count_inv) += count;
}
