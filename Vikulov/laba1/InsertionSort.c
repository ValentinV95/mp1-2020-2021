// c1 - ���-�� ������������   �2 - ���-�� ���������
#include "InsertionSort.h"

void InsertionSort(float* mas, int size, size_t* c1, size_t* c2) {
	for (int i = 1; i < size; i++) {
		int j = i;
		//(*c2)++;
		while ((j > 0) && (mas[j - 1] > mas[j])){
			(*c2)++;
			double tmp = mas[j - 1];
			mas[j - 1] = mas[j];
			mas[j] = tmp;
			j--;
			(*c1)++;
			
		}
		(*c2)++;
	}



}