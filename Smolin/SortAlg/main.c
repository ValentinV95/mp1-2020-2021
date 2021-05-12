#include "stdio.h"
#include "locale.h"
#include <stdlib.h>
#include "time.h"

extern int comp_merge;
extern int perm_merge;

int size;

void input_array(double[], int);
void random_array(double[], int);
void print_array(double[], int);

void correct_check(double[], int);

void insertion_sort(double[], const size_t);
void comb_sort(double[], const size_t);
void merge_sort(double[], int, int);
void radixSort(double*, double*, long);

int main()
{
	setlocale(LC_ALL, "Russian");
	//int size;
	int array_type;

	printf("Введите количество элементов массива: ");
	scanf_s("%d", &size);

	printf("\n-----------------------------------------------------");

	printf("\nВведите тип массива:\n\n 1 - Random\n\n 2 - Ручной ввод\n\n array id = ");
	scanf_s("%d", &array_type);

	printf("-----------------------------------------------------\n");

	double* a = (double*)malloc(size * sizeof(double));
	double* second_array = (double*)malloc(size * sizeof(double));

	printf("\nUnsorted array:\n\n");
	switch (array_type) {
	case 1:
		random_array(a, size);
		break;
	case 2:
		input_array(a, size);
		break;
	default:
		printf("Неправильное значение, введите ещё раз(1-2)\n\n");
		scanf_s("%d", &array_type);
	}

	printf("\n-----------------------------------------------------");

	int sort_id;
	printf("\nВведите id нужной сортировки:\n\n 1 - insertion sort\n\n 2 - comb sort\n\n 3 - merge sort\n\n 4 - radix sort\n\n sort id = ");
	scanf_s("%d", &sort_id);

	printf("-----------------------------------------------------\n");

	switch (sort_id) {
	case 1:
		insertion_sort(a, (size_t)size);
		break;
	case 2:
		comb_sort(a, (size_t)size);
		break;
	case 3:
		merge_sort(a, 0, size - 1);
		printf("\nКоличество сравнений: %d\n", comp_merge);
		printf("\nКоличество перестановок: %d\n", perm_merge);
		break;
	case 4:
		radixSort(a, second_array, size);
		break;
	default:
		printf("Неправильное значение, введите ещё раз(1-4)\n\n");
		scanf_s("%d", &sort_id);
	}

	correct_check(a, size);

	printf("\nArray after sorting algorithm: \n\n");
	print_array(a, size);

	free(a);
	free(second_array);
}

void input_array(double a[], int N) {
	for (int i = 0; i < N; i++)
	{
		printf("a[%d] = ", i);
		scanf_s("%lf", &a[i]);
	}
}

void random_array(double a[], int N) {
	srand(time(0));
	for (int i = 0; i < N; i++)
	{
		a[i] = ((double)rand() / rand());
		printf("a[%d] = %lf", i,a[i]);
		printf("\n");
	}
}

void print_array(double a[], int N) {
	for (int i = 0; i < N; i++) 
	{
		printf("a[%d] = %lf\n", i, a[i]);
	}
}

void correct_check(double a[], int N) {
	int success_id = 1 ;
	for (int i = 0; i < N - 1; i++) {
		if (a[i] < a[i + 1])
			success_id++;
	}
	if (success_id == N)
		printf("\n\nArray sorted successfull\n\n");
	else printf("\n\nArray hasn't been sorted\n\n");
}
