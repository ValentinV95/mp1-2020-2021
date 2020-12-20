#include "stdio.h"

int perm_insertion = 0;
int comp_insertion = 0;

void insertion_sort(double array[], size_t size) 
{
	int k = 0;
	for (int i = 1; i < size; i++)
	{
		k = i;
		for (int j = i; (j > 0) && (array[j - 1] > array[j]); j--)
		{
			if (array[j - 1] > array[j])
			{
				double tmp = array[j - 1];
				array[j - 1] = array[j];
				array[j] = tmp;
				perm_insertion++;
				comp_insertion++;
				k = j - 1;
			}
		}
		if (k != 0) comp_insertion++;
	}
	printf("\nКоличество сравнений: %d\n", comp_insertion);
	printf("\nКоличество перестановок: %d\n", perm_insertion);
}