// LapinDmitriyLaba.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <float.h>
#include "radixSort.h"
#include "mergeSort.h"
#include "SelectShellSort.h"












double random()
{
	double min = -100000;
	double max = 100000;

	return (double)(rand()) / RAND_MAX * (max - min) + min;
}

double* createArray(int size) {
	double* array = (double*)malloc(size * sizeof(double));
	for (int i = 0; i < size; i++) {
		array[i] = random();
	}
	return array;
}

void printArray(double* array, int size) {
	for (int i = 0; i < size; i++) {
		printf("%lf  ", array[i]);
	}
	printf("\n");
}

void checkArray(double* array, int size) {

	int a = 1;
	for (int i = 1; i < size; i++) {
		if (array[i] < array[i - 1]) {
			a = 0;
		}
	}

	if (a == 1)
		printf("\narray sorted true\n");
	else
		printf("\narray sorted false\n");

}

void reverseArray(double* array, int size) {
	for (int i = 0; i < size/2; i++) {
		double temp = array[i];
		array[i] = array[size - 1 - i];
		array[size - 1 - i] = temp;
	}
	printf("\nArray reversed\n");
}

void SortArray(double* array, int size, int check) {
	int input;
	printf("1.Selection sort\n");
	printf("2.Shell sort \n");
	printf("3.Merge sort \n");
	printf("4.Radix sort \n");

	printf(">> ");
	scanf("%d", &input);
	switch (input) {
	case 1:
		SelectSort(array, size);
		printf("Permutations: %d \n Comparsions: %d \n", getSelectPermutation(), getSelectComparsion());
		break;
	case 2:
		ShellSort(array, size);
		printf("Permutations: %d \n Comparsions: %d \n", getShellPermutation(), getShellComparsion());
		break;
	case 3:
		MergeSort(array, size);
		printf("Permutations: %d \n Comparsions: %d \n", getMergePermutation(), getMergeComparsion());
		break;
	case 4:
		radixSort(array, size);
		printf("Permutations: %d \n Comparsions: %d \n", getRadixPermutation(), getRadixComparsion());
		break;
	}

	if (check == 1) {
		checkArray(array, size);
	}



}



void printMenu() {
	printf("\n1.Create new array\n");
	printf("2.Sort array\n");
	printf("3.Sort array with check\n");
	printf("4.Print array\n");
	printf("5.Reverse array\n");
	printf("6.EXIT\n");
}





int main()
{
	double* array = NULL; int size = 0; int input;
	srand(time(NULL));
	printf("array free      size = 0\n\n");



	printMenu();

	printf(">> ");
	scanf("%d", &input);
	while (input != 6) {
		switch (input) {
		case 1:
			printf("Input Size:\n>> ");
			scanf("%d", &size);
			free(array);
			array = createArray(size);
			printf("Array created, array size: %d\n", size);

			break;
		case 2:
			SortArray(array, size, 0);
			break;
		case 3:
			SortArray(array, size, 1);
			break;
		case 4:
			printArray(array, size);
			break;
		case 5:
			reverseArray(array, size);
			break;

		}

		printMenu();
		printf("\n>> ");
		scanf("%d", &input);

	}
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
