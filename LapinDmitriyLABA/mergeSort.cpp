#include<stdlib.h>


int Com = 0;
int Per = 0;


void MergeExpert(double* array, double* second, int l, int q, int r) {


    double* a = array + l; int a_size = q - l + 1;
    double* b = array + q + 1; int b_size = r - q;


    int i = 0; int j = 0;
    while (i < a_size && j < b_size) {
        Com++;
        if (a[i] <= b[j]) {
            second[i + j] = a[i];
            Per++;
            ++i;
        }
        else {
            second[i + j] = b[j];
            Per++;
            ++j;
        }
    }

    if (i == a_size)
        for (; j < b_size; j++) {
            second[i + j] = b[j];
            Per++;
        }
    else if (j == b_size)
        for (; i < a_size; i++) {
            second[i + j] = a[i];
            Per++;
        }



    for (int step = 0; step < r - l + 1; step++) {
        array[l + step] = second[step];
        Per++;
    }

}


void MergeSortIn(double* array, double* second, int l, int r) {
    if (l < r) {
        int q = (l + r) / 2;
        MergeSortIn(array, second, l, q);
        MergeSortIn(array, second, q + 1, r);
        MergeExpert(array, second, l, q, r);
    }
}



void MergeSort(double* array, int size) {
    double* second = (double*)malloc(sizeof(double) * size);
    MergeSortIn(array, second, 0, size - 1);
    free(second);
}




int getMergeComparsion() {
    int temp = Com;
    Com = 0;
    return temp;
}
int getMergePermutation() {
    int temp = Per;
    Per = 0;
    return temp;
}
