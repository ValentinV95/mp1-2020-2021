#include<stdio.h>
#include<stdlib.h>
#include <locale.h>
#include"rabotasmassivami.h"
#include"sortirovki.h"
#define scanf scanf_s
int f = 0;

void draw()
{
	printf("��������, ��� ������ ������� \n");
	printf("1. ��������� ������ �������� \n");
	printf("2. ��������� ������ ������� \n");
	printf("3. ������������� ������ ����������� ������� \n");
	printf("4. ������������� ������ ������� ����������� \n");
	printf("5. ������������� ������ ����������� �������� \n");
	printf("6. ������������� ������ ����������� ����������� \n");
	printf("7. ��������� ������ �� ����������������� \n");
	printf("8. ������� ������ \n");
	printf("9. ����� �� ��������� \n");
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
		printf("������ ��������");
		break;
	case 2:
		zapolnenievrucnuu(a, N);
		if(c==NULL)
			c = (float*)malloc(N * 4);
		arraycopy(a, c, N);
		printf("������ ��������");
		break;
	case 3:
		sortvibor(a, N);
		printf("������ ������������ ������� \n���������� ������������: %llu\n���������� ���������: %llu",perestanovki,sravnenia);
		break;
	case 4:
		sortxoar(a, 0, N - 1);
		printf("������ ������������ ���������� ������� ����������\n���������� ������������: %llu\n���������� ���������: %llu", perestanovki, sravnenia);
		break;
	case 5:
		float* b;
		b = (float*)malloc(N * 4);
		mergesort(a, b, 0, N - 1);
		printf("������ ������������ ��������\n���������� ������������: %llu\n���������� ���������: %llu", perestanovki, sravnenia);
		free(b);
		break;
	case 6:
		radixsort(a, N);
		printf("������ ������������ ����������� �����������\n���������� ������������: %llu\n���������� ���������: %llu", perestanovki, sravnenia);
		break;
	case 7:
		if (proverkamassiva(a, c, N)) printf("������ ������������"); else printf("������ �� ������������");
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
	printf("�������� ������ ������� \n");
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