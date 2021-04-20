#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <time.h>
#include "bubblesort.h"
#include "shellsort.h"
#include "radix.h"
int count_comp1 = 0, count_perm1 = 0;

void sorting_check(double* mas, long size)
{
	int flag = 0;
	
	for (int i = 1; i < size; i++) 
	{
		if (mas[i] < mas[i - 1])
		{
			flag = 1;
			break;
		}
	}

	if (flag == 1)
	{
		std::cout << "Sorting is not correctly \n";
	}
	else
	{
		std::cout << "Sorting is correctly \n";
	}
}

//для наихудшего случая
void invert_mas(double* mas, int size)
{
	for (int i = 0, j = size - 1; i < size / 2; i++, j--)
	{

		double temp = mas[j];
		mas[j] = mas[i];
		mas[i] = temp;
	}
}



void bubblesort(double* mas, int size);
void shellsort(double* mas, int size);






//из-за трудностей со счетчиками, пришлось перенести mergesort в основную программу.
void mergeSort(double* mas, int left_half, int right_half)
{
	if (left_half == right_half) return;
	int mid = (left_half + right_half) / 2;
	mergeSort(mas, left_half, mid);
	mergeSort(mas, mid + 1, right_half);
	int i = left_half;
	int j = mid + 1;
	double* tmp = (double*)malloc((right_half - left_half + 1) * sizeof(double));

	for (int step = 0; step < right_half - left_half + 1; step++)
	{
		count_comp1++;
		if ((j > right_half) || ((i <= mid) && (mas[i] < mas[j]) ))
		{
			count_perm1++;
			tmp[step] = mas[i];
			i++;
		}
		else
		{
			count_perm1++;
			tmp[step] = mas[j];
			j++;
		}
	}

	for (int step = 0; step < right_half - left_half + 1; step++)
	{
		mas[left_half + step] = tmp[step];
	}
	free(tmp);
}



void create_counters(double* mas, long* counters, long size);
void radix_pass(short Offset, long size, double* mas, double* dest, long* count);
void radix_last_pass(short Offset, long size, double* mas, double* dest, long* count);
void radix_sort(double*& source_mas, long size);


int main()
{
	srand(time(NULL));
	int f, size;
	double* mas, * not_sorted_mas;
	std::cout << "Program ''Sort array''\n \n";
	std::cout << "Create and sort array - 1" << std::endl << "Out - 2" << std::endl;
	std::cin >> f;
	switch (f)
	{
	case 1: 
	{
		std::cout << "Enter array size" << std::endl;
		std::cin >> size;
		mas = (double*)malloc(size * sizeof(double));
		not_sorted_mas = (double*)malloc(size * sizeof(double));
		std::cout << "Enter array manually - 1" << std::endl << "Fill array with random values - 2" << std::endl;
		std::cin >> f;
		switch (f)
		{
		case 1:
		{
			for (int i = 0; i < size; i++)
			{
				std::cin >> mas[i];
				not_sorted_mas[i] = mas[i];
			}
			break;
		}
		case 2:
		{
			for (int i = 0; i < size; i++)
			{
				mas[i] = (double)(rand() % 10000 - 5000) / 100;
				not_sorted_mas[i] = mas[i];
			}
			break;
		}

		}

		std::cout << "Bubble sort - 1" << std::endl << "Shell sort - 2" << std::endl << "Merge sort - 3" << std::endl
			<< "Radix sort - 4" << std::endl;
		std::cin >> f;
		switch (f)
		{
		case 1:
		{
			
			bubblesort(mas, size);
			sorting_check(mas, size);
			break;
		}
		case 2:
		{
			
			shellsort(mas, size);
			sorting_check(mas, size);
			break;
		}
		case 3:
		{
			int left_half = 0;
			int right_half = size;
			mergeSort(mas, left_half, right_half - 1);
			std::cout << "number of comparisons " << count_comp1 << std::endl;
			std::cout << "number of permutations " << count_perm1 << std::endl;
			sorting_check(mas, size);
			break;
		}
		case 4:
		{
			radix_sort(mas, size);
			sorting_check(mas, size);
			break;
		}
		}

		std::cout << "display source array and sorted array on screen? \n 1 - yes \n 2 - no \n";
		std::cin >> f;
		switch (f)
		{
		case 1:
		{
			std::cout << "source array: \n";
			for (int i = 0; i < size; i++)
			{
				std::cout << "array[" << i << "] = " << not_sorted_mas[i] << std::endl;
			}

			std::cout << "sorted array: \n";
			for (int i = 0; i < size; i++)
			{
				std::cout << "array[" << i << "] = " << mas[i] << std::endl;
			}
			break;
		}
		case 2:
		{
			break;
		}
		
		}
		free(not_sorted_mas);
		free(mas);
	case 2: {
		return 0;
	}
	}
	}
}
