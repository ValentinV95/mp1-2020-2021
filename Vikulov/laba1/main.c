#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include "InsertionSort.h"
#include "ShellSort.h"
#include "MergeSort.h"
#include "RadixSort.h"


int main() {
	srand(time(NULL));
	long int size, key; 
	bool flag = true;
	size_t count_per = 0, count_com = 0;
	printf("Enter the size of array: ");
	scanf("%d", &size);
	
	if (size <= 0 )
		printf("ERROR!!!\n");
	else {
		float* arr = (float*)malloc(size * sizeof(float));
		float* check = (float*)malloc(size * sizeof(float));
		
		printf("Input elements:\n");
		
		/*for (int i = 0; i < size; i++) {
			printf("arr[%d] = ", i);
			scanf("%f", &arr[i]);
		}
		*/
		  
		for (int i = 0; i < size; i++) {
			arr[i] = -5000 + rand() % 10000;
			arr[i] += 0.00002;
		}


		for (int i = 0; i < size; i++) {
			check[i] = arr[i];              //Копирование массива для дальнейшей проверки
		}

		printf("\nArray before Sorting:\n");
		for (int i = 0; i < size; i++)
			printf("arr[%d] = %f\n", i, arr[i]);



		printf("Insertion Sort --> 1\n");
		printf("Shell Sort --> 2\n");
		printf("Merge Sort --> 3\n");
		printf("Radix Sort --> otherwise\n");

		printf("Select the way: ");
		scanf("%d", &key);

		switch (key) {
		case 1:
			InsertionSort(arr, size, &count_per, &count_com);
			printf("\nArray after Insertion Sort:\n");
			for (int i = 0; i < size; i++)
				printf("arr[%d] = %f\n", i, arr[i]);
			printf("Number of comparisons = %d\nNumber of inversions = %d\n", count_com, count_per);
			break;
		case 2:
			ShellSort(arr, size, &count_per, &count_com);
			printf("\nArray after Shell Sort:\n");
			for (int i = 0; i < size; i++)
				printf("arr[%d] = %f\n", i, arr[i]);
			printf("Number of comparisons = %d\nNumber of inversions = %d\n", count_com, count_per);
			break;
		case 3:
			printf("\nArray after Merge Sort:\n");
			MergeSort(arr, 0, size - 1, &count_com, &size);
			for (int i = 0; i < size; i++)
				printf("arr[%d] = %f\n", i, arr[i]);
			printf("Number of comparisons = %d\nNumber of inversions = %d\n", count_com, size);
			break;
		default:
			printf("\nArray after Radix Sort:\n");
			radix_sort(arr, size, &count_com, &count_per);
			for (int i = 0; i < size; i++)
				printf("arr[%d] = %f\n", i, arr[i]);
			printf("Number of comparisons = %d\nNumber of inversions = %d\n", count_com, size);
			break;
		}

		//Сортируем проверяющий массив пузырьком

		for (int i = 0; i < size - 1; i++) {
			for (int j = i + 1; j < size; j++) {
				if (check[i] > check[j]) {
					float tmp = check[j];   
					check[j] = check[i];
					check[i] = tmp;
				}
			}
		}

		

		//Проверяем корректность
		for (int i = 0; i < size; i++) {
			if (arr[i] != check[i])
				flag = false;
		}
		

		if (flag == true)
			printf("Sorting is done correctly\n");
		else
			printf("Sorting is not done correctly\n");
		
	}

	
	return 0;
}