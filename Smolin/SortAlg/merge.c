#include "stdio.h"
#include "malloc.h"

int perm_merge = 0;
int comp_merge = 0;

extern int size;

void merge(double[], int, int);

void merge_sort(double array[], int first, int last) {
	int middle = (first + last) / 2;
	if (first < last) {
		merge_sort(array, first, middle);
		merge_sort(array, middle+1, last);
		merge(array, first, last);
		comp_merge++;
	}
}

void merge(double array[], int first, int last) {
	int middle, start, final, j;
	double* second;
	second = (double*)malloc((size) * sizeof(double));
	middle = (first + last) / 2;
	start = first; 
	final = middle + 1;
	for (j = first; j <= last; j++) {
		if (start <= middle) {
			if ((final > last) || (array[start] < array[final]))
			{
				second[j] = array[start];
				start++;
				comp_merge++;
				perm_merge++;
			}
			else
			{
				second[j] = array[final];
				final++;
				comp_merge++;
				perm_merge++;
			}
			comp_merge++;
		}
		else {
			second[j] = array[final];
			final++;
			comp_merge++;
			perm_merge++;
		}
	}
	for (j = first; j <= last; j++) {
		array[j] = second[j];
		perm_merge++;
	}
	free(second);
}