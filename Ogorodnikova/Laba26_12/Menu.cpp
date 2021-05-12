#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctime>
#include "Menus.h"
#include "ArrayF.h"
#include "ArraySort.h"

void menu(float** arr, int* n)
{
	char c;
	char men[4][50] = { {"Information about array"}, {"Sorts"}, {"Print array"}, {"Exit"} };
	const int max_op = 4;
	int op = 0;
	while (true)
	{
		system("cls");
		for (int i = 0; i < max_op; i++)
		{
			if (i == op)
			{
				printf("* ");
			}
			else
				printf("  ");
			printf("%s\n", men[i]);
		}
		c = _getch();

		if (c == 72)
		{
			op = (op - 1 + max_op) % max_op;
		}
		if (c == 80)
		{
			op = (op + 1) % max_op;
		}
		if(c == 13)
		{
			switch (op)
			{
			case 0:
				menu_array(arr, n);
				break;
			case 1:
				menu_sort(*arr, *n);
				break;
			case 2:
				print_arr(*arr, *n);
				break;
			case 3:
				c = 27;
				break;
				default:
					break;
			}
		}
		if (c == 27)
		{
			break;
		}
	}
}
void menu_sort(float* arr, int n)
{
	double start = clock();
	char c;
	char men[6][50] = { {"Insertion sort"}, {"Shell sort"}, {"merge sort"}, {"Quicksort"}, {"Radix sort"}, {"Exit"} };
	const int max_op = 6;
	int op = 0;
	while (true)
	{
		system("cls");
		for (int i = 0; i < max_op; i++)
		{
			if (i == op)
			{
				printf("* ");
			}
			else
				printf("  ");
			printf("%s\n", men[i]);
		}
		c = _getch();

		if (c == 72)
		{
			op = (op - 1 + max_op) % max_op;
		}
		if (c == 80)
		{
			op = (op + 1) % max_op;
		}
		if (c == 13)
		{
			switch (op)
			{
			case 0:
				start = clock();
				obnull_if_swap();
				insert_sort(arr, n);
				printf("%.4lf sec.\n", (clock() - start) / CLOCKS_PER_SEC);
				print_if_and_swap();
				system("pause");
				break;
			case 1:
				start = clock();
				obnull_if_swap();
				shell_sort(arr, n);
				printf("%.4lf sec.\n", (clock() - start) / CLOCKS_PER_SEC);
				print_if_and_swap();
				system("pause");
				break;
			case 2:
				start = clock();
				obnull_if_swap();
				merge_sort(arr, n);
				printf("%.4lf sec.\n", (clock() - start) / CLOCKS_PER_SEC);
				print_if_and_swap();
				system("pause");
				break;
			case 3:
				start = clock();
				obnull_if_swap();
				hoar_sort(arr, 0, n - 1);
				printf("%.4lf sec.\n", (clock() - start) / CLOCKS_PER_SEC);
				print_if_and_swap();
				system("pause");
				break;
			case 4:
				start = clock();
				obnull_if_swap();
				radix_sort(arr, n);
				printf("%.4lf sec.\n", (clock() - start) / CLOCKS_PER_SEC);
				print_if_and_swap();
				system("pause");
				break;
			case 5:
				c = 27;
				break;
			default:
				break;
			}
		}
		if (c == 27)
		{
			break;
		}
	}
}
void menu_array(float** arr, int* n)
{
	char c;
	char men[4][50] = { {"Enter size array"}, {"Random elements of array"}, {"Keyboard enter"}, {"Exit"} };
	const int max_op = 4;
	int op = 0;
	while (true)
	{
		system("cls");
		for (int i = 0; i < max_op; i++)
		{
			if (i == op)
			{
				printf("* ");
			}
			else
				printf("  ");
			printf("%s\n", men[i]);
		}
		c = _getch();

		if (c == 72)
		{
			op = (op - 1 + max_op) % max_op;
		}
		if (c == 80)
		{
			op = (op + 1) % max_op;
		}
		if (c == 13)
		{
			switch (op)
			{
			case 0:
				size_arr(arr, n);
				break;
			case 1:
				arr_rand(*arr, *n);
				break;
			case 2:
				keyboard_in(*arr, *n);
				break;
			case 3:
				c = 27;
				break;
			default:
				break;
			}
		}
		if (c == 27)
		{
			break;
		}
	}
}