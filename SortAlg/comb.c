#include "stdio.h"

int perm_comb = 0;
int comp_comb = 0;

void comb_sort(double array[], const size_t size) {
    double factor = 1.2473309; int step = size - 1;
    while (step >= 1) {
        for (int i = 0; i + step < size; i++) {
            if (array[i] > array[i + step]) {
                double tmp = array[i];
                array[i] = array[i + step];
                array[i + step] = tmp;
                perm_comb++;
                comp_comb++;
            }
        }
        step /= factor;
    }
    printf("\nКоличество сравнений: %d\n", comp_comb);
    printf("\nКоличество перестановок: %d\n", perm_comb);
}
