#include "menu.h"

#define _CRT_SECURE_NO_WARNINGS

#include "sorts.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "memory.h"
#include "time.h"

static void reverce(float* arr, size_t len)
{
	for (size_t i = 0; i < len / 2; i++)
	{
		float temp = arr[len - i - 1];
		arr[len - i - 1] = arr[i];
		arr[i] = temp;
	}
}

static void randomShuffle(float* arr, size_t len)
{
	for (size_t i = 0; i < len; i++)
	{
#if RAND_MAX <= (1 << 16)
		size_t pos = (((size_t)rand() << 15) + rand()) % (len - i) + i;
#else 
		size_t pos = rand() % (len - i);
#endif
		
		float temp = arr[i];
		arr[i] = arr[pos];
		arr[pos] = temp;
	}
}

#pragma warning(push)
#pragma warning(disable:6031)
static void createRandomArray(float* arr, size_t len)
{
	double min, max;
	
	printf("enter the minimum of an array element: ");
	scanf("%lf", &min);
	printf("enter the maximum of an array element: ");
	scanf("%lf", &max);

	for (size_t i = 0; i < len; i++)
	{
		arr[i] = (float)((double)rand() / RAND_MAX * (max - min) + min);
	}
}

static void createOrderArray(float* arr, size_t len)
{
	double min, max, step;
	
	printf("enter the minimum of an array element: ");
	scanf("%lf", &min);
	printf("enter the maximum of an array element: ");
	scanf("%lf", &max);

	step = (max - min) / len;
	for (size_t i = 0; i < len; i++)
	{
		arr[i] = (float)(min + step * i);
	}
}

static void readArray(float* arr, size_t len)
{
	printf("enter array: ");

	for (size_t i = 0; i < len; i++)
	{
		scanf("%f", &arr[i]);
	}
}

static void readArrayFromFile(float* arr, size_t len)
{
	char fileName[256];

	printf("enter file name: ");

	getchar();
	fgets(fileName, 255, stdin);

	fileName[strlen(fileName) - 1] = '\0';

	FILE* file = fopen(fileName, "r");
	if (file == NULL) {
		memset(arr, 0, len * sizeof(float));
		printf("unable to open file");
		system("pause");
		return;
	}

	for (size_t i = 0; i < len; i++)
	{
		fscanf(file, "%f", &arr[i]);
	}

	fclose(file);
}


static size_t arrayMenu(float** arr)
{
	void (* const createFunc[])(float*, size_t) = { createRandomArray, createOrderArray, readArray, readArrayFromFile };
	const char ARRAY_MENU_TEXT[] =
		"\n\tARRAY CREATION MENU\n"
		"1) array of random numbers\n"
		"2) numbers in the interval\n"
		"3) enter an array\n"
		"4) read array from file\n"
		">> ";
	int comand;
	size_t len;

	if (*arr != NULL) {
		free(*arr);
		*arr = NULL;
	}

	printf("enter new array length: ");
	scanf("%zu", &len);

	printf(ARRAY_MENU_TEXT);
	scanf("%d", &comand);

	if (comand <= 4 && len > 0) {
		*arr = (float*)malloc(sizeof(float) * len);
		createFunc[comand-1](*arr, len);
	}
	else {
		printf("incorrect input");
		system("pause");
		return 0;
	}

	return len;
}

static void sortMenu(float* arr, size_t len, int checkMode)
{
	testInfo(* const sortFuncs[])(float*, size_t) = { bubbleSort, quickSort, mergeSort, radixSort };
	const char SORT_MENU_TEXT[] =
		"\n\tSORT MENU\n"
		"1) bubble sort\n"
		"2) quick sort\n"
		"3) merge sort\n"
		"4) radix sort\n"
		">> ";

	testInfo report;
	int comand;

	printf(SORT_MENU_TEXT);
	scanf("%d", &comand);

	if (comand <= 4) {
		if (checkMode == 0) {
			report = sortFuncs[comand - 1](arr, len);
		}
		else {
			report = checkSort(arr, len, sortFuncs[comand - 1]);
		}
	}
	else {
		printf("incorrect input\n");
		system("pause");
		return;
	}

	printf("sort report: \n");
	printf("number of permutations: %lld\n", report.swapCount);
	printf("number of comparisons:  %lld\n", report.compareCount);
	if (checkMode) {
		printf("sort is correct: %s\n", (report.isCorrect ? "YES" : "NO"));
	}

	system("pause");
}

void changeArr(float* arr)
{
	int index;
	float value;

	printf("index: ");
	scanf("%d", &index);
	printf("new value: ");
	scanf("%f", &value);

	arr[index] = value;
}

void printArray(float* arr, size_t len)
{
	const char PRINT_ARRAY_MENU_TEXT[] = "\n\n"
		"1) print to console\n"
		"2) print to file\n"
		">> ";
	int comand;

	printf(PRINT_ARRAY_MENU_TEXT);
	scanf("%d", &comand);

	if (comand == 1) {
		for (size_t i = 0; i < len; i++)
		{
			printf("%f ", arr[i]);
		}
		printf("\n\n");

		system("pause");
	}
	else if (comand == 2) {
		char fileName[256];
		FILE* file;

		printf("enter file name: ");
		getchar();
		fgets(fileName, 255, stdin);
		fileName[strlen(fileName) - 1] = '\0';

		file = fopen(fileName, "w");
		if (file == NULL) {
			printf("unable to open file");
			system("pause");
			return;
		}

		for (size_t i = 0; i < len; i++)
		{
			fprintf(file, "%f ", arr[i]);
		}

		fclose(file);
	}

}

void mainMenu()
{
	const char MAIN_MENU_TEXT[] =
		"\n\n\tMENU\n"
		"1) create new array\n"
		"2) change array element\n"
		"3) sort array\n"
		"4) sort array with check\n"
		"5) reverse array\n"
		"6) random shuffle\n"
		"7) print array\n"
		"8) exit\n"
		">> ";

	float* arr = NULL;
	size_t arrLen = 0;

	srand((unsigned int)time(0));

	while (true)
	{
		int comand;

		system("cls");
		if (arrLen > 50) {
			printf("first 50 elements of array:\n");

			for (int i = 0; i < 50; i++)
			{
				printf("%f ", arr[i]);
			}
		}
		else if (arrLen > 0) {
			printf("array is:\n");

			for (int i = 0; i < arrLen; i++)
			{
				printf("%f ", arr[i]);
			}
		}
		else {
			printf("array is empty");
		}
		printf("\n\narray size: %zu", arrLen);
		printf(MAIN_MENU_TEXT);
		fflush(stdout);
		
		scanf("%d", &comand);

		switch (comand)
		{
		case 1:
			arrLen = arrayMenu(&arr);
			break;
		case 2:
			changeArr(arr);
			break;
		case 3:
			sortMenu(arr, arrLen, 0);
			break;
		case 4:
			sortMenu(arr, arrLen, 1);
			break;
		case 5:
			reverce(arr, arrLen);
			break;
		case 6:
			randomShuffle(arr, arrLen);
			break;
		case 7:
			printArray(arr, arrLen);
			break;
		case 8:
			return;
		}
	}
}
#pragma warning(pop)