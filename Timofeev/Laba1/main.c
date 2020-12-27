#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <stdlib.h>

extern int comp_merge, perm_merge;
extern int comp_radix, perm_radix;
extern int comp_quick, perm_quick;
extern int comp_selection, perm_selection;

void input_a(float[], int);
void random_a(float[], int);
void print_a(float[], int);
void mergesort(float* array, int n);
void radixSort(float* array, int size);
void quicksort(float* array, int l, int r);
void selectionSort(float* num, int size);

void main()
{
	int n, type, sort_type;
	setlocale(LC_ALL, "Russian");
	printf("Введите размер массива\t");
	scanf_s("%d", &n);
	float* array = (float*)malloc(n * sizeof(float));
    float* array2 = (float*)malloc(n * sizeof(float));
    printf("\nВведите тип массива:\n\n 1 - Random\n\n 2 - Ручной ввод\n\n array id = ");
    scanf_s("%d", &type);

    printf("\nНеотсортированный массив:\n\n");
    switch (type) 
    {
    case 1:
        random_a(array, n);
        break;
    case 2:
        input_a(array, n);
        break;
    default:
        printf("Неправильное значение, введите ещё раз(1-2)\n\n");
        scanf_s("%d", &type);
    }
    printf("\n\nВведите тип сортировки:\n\n1-mergeSort\n\n2-radixSort\n\n3-quicksort\n\n4-selectionSort\n\nsort id = ");
    scanf_s("%d", &sort_type);
    printf("\n\n");
    printf("Отсортированный массив");
    printf("\n\n");
    switch (sort_type)
    {
    case 1:
        mergesort(array, n);
        printf("\n%d-сравнения\n\n", comp_merge);
        printf("\n%d-перестановки\n\n", perm_merge);
        break;
    case 2:
        radixSort(array, n);
        printf("\n%d-сравнения\n\n", comp_radix);
        printf("\n%d-перестановки\n\n", perm_radix);
        break;  
    case 3:
        quicksort(array, 0, n-1);
        printf("\n%d-сравнения\n\n", comp_quick);
        printf("\n%d-перестановки\n\n", perm_quick);
        break;
    case 4:
        selectionSort(array, n);
        printf("\n%d-сравнения\n\n", comp_selection);
        printf("\n%d-перестановки\n\n", perm_selection);
        break;
    }
    print_a(array, n);
}

void input_a(float a[], int N) 
{
    for (int i = 0; i < N; i++)
    {
        printf("a[%d] = ", i);
        scanf_s("%f", &a[i]);
    }
}

void random_a(float a[], int N) {
    srand(time(0));
    for (int i = 0; i < N; i++)
    {
        a[i] = ((float)rand() / rand());
        printf("a[%d] = %f\n", i, a[i]);
    }
}

void print_a(float a[], int N) {
    for (int i = 0; i < N; i++)
    {
        printf("a[%d] = %f\n", i, a[i]);
    }
}