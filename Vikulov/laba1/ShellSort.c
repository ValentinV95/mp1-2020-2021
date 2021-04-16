#include "ShellSort.h"
void ShellSort(float mas[], int size, size_t* c1, size_t* c2) {
	int step;
	for (step = size / 2; step > 0; step /= 2) {
		for (int i = step; i < size; i++) {
			(*c2)++;
			for (int j = i - step; j >= 0 && mas[j] > mas[j + step]; j -= step) {
				(*c2)++;
				double tmp = mas[j];
				mas[j] = mas[j + step];
				mas[j + step] = tmp;
				(*c1)++;
			}
		}
	}



}