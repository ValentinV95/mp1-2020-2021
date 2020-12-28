#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>      
#include <time.h>
#include <conio.h>
#include <malloc.h>
#include <stdlib.h>


int bubble_sort(double* a, const size)
{
	int k = 0;
	for (int i = 0; i < size - 1; i++)
	{
		int flag = 0;
		for (int j = size - 2; j > i - 1; j--)
			if (a[j] > a[j + 1])
			{
				double tmp;
				tmp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tmp;
				k++;
				flag = 1;
			}
		if (flag == 0)
		{
			return k;
			break;
		}
	}
}


void main()
{
    const N = 10;
    double mass[10];
    double* p;
    p = mass;
    int i;
	int ch[1000];
	int sredn, min, max, sum=0;
	srand(time(NULL));
	for (int j = 0; j < 100; j++) {
		
		for (i = 0; i < N; i++)
		{
			mass[i] = rand();
		}
		ch[j] = bubble_sort(p, N);
		sum += ch[j];
	}
	bubble_sort(ch, 100);

	printf("%d", sum/100 );
	printf("  ");
	printf("%d", ch[1]);
	printf("  ");
	printf("%d", ch[2]);
	printf("  ");

	/* for (i = 0; i < N; i++)
    {
        printf("%lf", mass[i]);
        printf("  ");
    }*/
    return(0);
}