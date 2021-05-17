#include<stdio.h>
#include<stdlib.h>
#include <locale.h>
#include"rabotasmassivami.h"
#include"sortirovki.h"
#define scanf scanf_s
int f = 0;

void draw()
{
	printf("Выберете, что хотите сделать \n");
	printf("1. заполнить массив случайно \n");
	printf("2. заполнить массив вручную \n");
	printf("3. отсортировать массив сортировкой выбором \n");
	printf("4. отсортировать массив быстрой сортировкой \n");
	printf("5. отсортировать массив сортировкой слиянием \n");
	printf("6. отсортировать массив поразрядной сортировкой \n");
	printf("7. проверить массив на отсортированность \n");
	printf("8. вывести массив \n");
	printf("9. выйти из программы \n");
	printf("\n");
}

void scan(float* a,int N)
{
	int n;
	static float* c = NULL;
	scanf("%d", &n);
	switch (n)
	{
	case 1:
		sozdaniemassiva(a, N);
		if(c==NULL)
			c = (float*)malloc(N * 4);
		arraycopy(a, c,N);
		printf("Массив заполнен");
		break;
	case 2:
		zapolnenievrucnuu(a, N);
		if(c==NULL)
			c = (float*)malloc(N * 4);
		arraycopy(a, c, N);
		printf("Массив заполнен");
		break;
	case 3:
		sortvibor(a, N);
		printf("Массив отсортирован выбором \nКоличество перестановок: %llu\nКоличество сравнений: %llu",perestanovki,sravnenia);
		break;
	case 4:
		sortxoar(a, 0, N - 1);
		printf("Массив отсортирован алгоритмом быстрой сортировки\nКоличество перестановок: %llu\nКоличество сравнений: %llu", perestanovki, sravnenia);
		break;
	case 5:
		float* b;
		b = (float*)malloc(N * 4);
		mergesort(a, b, 0, N - 1);
		printf("Массив отсортирован слиянием\nКоличество перестановок: %llu\nКоличество сравнений: %llu", perestanovki, sravnenia);
		free(b);
		break;
	case 6:
		radixsort(a, N);
		printf("Массив отсортирован поразрядной сортировкой\nКоличество перестановок: %llu\nКоличество сравнений: %llu", perestanovki, sravnenia);
		break;
	case 7:
		if (proverkamassiva(a, c, N)) printf("Массив отсортирован"); else printf("Массив не отсортирован");
		break;
	case 8:
		    vivodmassiva2(a, N);
		break;
	case 9:
		free(c);
		f = 1;
		break;
	default:
		f = 1;
		break;
	}
	printf("\n");
}

int main()
{
	int N;
	setlocale(LC_ALL, "Rus");
	printf("Выберете размер массива \n");
	scanf("%d", &N);
	float* array = (float*)malloc(N * 4);
	draw();
	while (f == 0)
	{
		perestanovki = 0;
		sravnenia = 0;
		scan(array, N);
		
	}
	free(array);
}