#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include "Algorithm.h"
using namespace std;

double* arr;
int Exit = 0;
int N = 0;
int limit = 0;

int input_size() {
	int i;
	free(arr);

	do {
		printf("Введите новый размер массива:\n");
		printf(">");
		scanf_s("%d", &N);
	} while (N < 0);

	arr = (double*)malloc(sizeof(double) * N);
	for (i = 0;i < N;i++) {
		arr[i] = i;
	}

	return 0;
}

int generating_progression() {
	double a, q;
	int i;
	printf("Примечание: для ввода вещественных чисел используйте запятую\n");
	printf("Введите a0:\n");
	printf(">");
	scanf_s("%lf", &a);
	printf("Введите q:\n");
	printf(">");
	scanf_s("%lf", &q);
	arr[0] = a;
	for (i = 1;i < N;i++) {
		arr[i] = arr[i - 1] + q;
	}
	printf("Массив заполнен\n");
	return 0;
}

int random_array() {
	int i;
	srand(time(0));
	for (i = 0;i < N;i++) {
		arr[i] = ((double)rand() / rand()) * (i % 2 == 0 ? -1 : 1);
	}
	printf("Массив заполнен случайными элементами\n");
	return 0;
}

int input_array() {
	int flag = 1;
	if (N > limit) {
		flag = 0;
		printf("Массив включает более %d элементов\n", limit);
		printf("Хотите продолжить?\n");
		printf(" НЕТ->0 / ДА->1 \n");
		printf(">");
		scanf_s("%d", &flag);
	}
	if (flag) {
		printf("Введите %d значений\n", N);
		printf("Примечание: для ввода вещественных чисел используйте запятую\n");
		for (int i = 0;i < N;i++) {
			printf("array[%d] = ", i);
			scanf_s("%lf", &arr[i]);
		}
		printf("Массив заполнен\n");
	}
	return 0;
}

int show_array() {
	int flag = 1;
	if (N > limit) {
		flag = 0;
		printf("Массив включает более %d элементов\n", limit);
		printf("Хотите продолжить?\n");
		printf(" НЕТ->0 / ДА->1 \n");
		printf(">");
		scanf_s("%d", &flag);
	}
	if (flag) {
		printf("Состав массива:\n");
		for (int i = 0;i < N;i++) {
			printf(" array[%d] = %lf\n", i, arr[i]);
		}
	}
	return 0;
}

int MenuInitialize() {
	int i;
	system("chcp 1251");
	Exit = 10;
	N = 10;
	limit = 10;

	arr = (double*)malloc(sizeof(double) * N);
	for (i = 0;i < N;i++) {
		arr[i] = i;
	}
	return 0;
}

int UpdateMenu() {
	int input = 0;
	unsigned long count = 0;

	while (input != Exit) {

		system("cls");
		printf("+--------------------------------------------------+\n");
		printf("| Программа по созданию и сортировке массивов чисел|\n");
		printf("+--------------------------------------------------+\n");
		printf("Выберите действие:\n");
		printf("\n");
		printf("[Работа с массивом]\n");
		printf("1. Ввод размера массива (N = %d)\n", N);
		printf("2. Cлучайный ввод\n");
		printf("3. Генерация массива по арифм. прогр.\n");
		printf("4. Ручной ввод (N <= %d)\n", limit);
		printf("5. Вывести массив\n");
		printf("\n");
		printf("[Алгоритмы сортировки]\n");
		printf("6. Сортировка вставками    O(N^2)\n");
		printf("7. Сортировка Шелла        O(N * log(N))\n");
		printf("8. Сортировка слиянием     O(N * log(N))\n");
		printf("9. Поразрядная сортировка  O(N)\n");
		printf("\n");
		printf("10. Выход\n");

		printf(">");
		scanf_s("%d", &input);

		switch (input) {
		case 1: {
			input_size();
			break;
		}
		case 2: {
			random_array();
			break;
		}
		case 3: {
			generating_progression();
			break;
		}
		case 4: {
			input_array();
			break;
		}
		case 5: {
			show_array();
			break;
		}
		case 6: {
			printf("Сортировка началась...\n");
			count = insertion_sort(arr, N);
			printf("Массив отсортирован\n");
			printf("Кол-во операций: %d\n", count);
			break;
		}
		case 7: {
			printf("Сортировка началась...\n");
			count = Shell_sort(arr, N);
			printf("Массив отсортирован\n");
			printf("Кол-во операций: %d\n", count);
			break;
		}
		case 8: {
			printf("Сортировка началась...\n");
			count = _mergesort(arr, N);
			printf("Массив отсортирован\n");
			printf("Кол-во операций: %d\n", count);
			break;
		}
		case 9: {
			printf("Сортировка началась...\n");
			count = radixSort(arr, N);
			printf("Массив отсортирован\n");
			printf("Кол-во операций: %d\n", count);
			break;
		}
		case 10: {
			printf("GoodBye!\n");
			break;
		}
		default: {
			printf("Команда не найдена\n");
		}
		}
		system("pause");
	}
	return 0;
}
