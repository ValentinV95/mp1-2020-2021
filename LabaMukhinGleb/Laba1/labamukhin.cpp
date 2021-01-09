#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <malloc.h>
int swp = 0; int cmp = 0;
void insrt_sort(float arr[], int t)
{
	for (int i = 1; i < t; i++)
	{
		for (int j = i; i > 0 && arr[j - 1] - arr[j] >= 0; j--)
		{
			float d = arr[j];
			arr[j] = arr[j - 1];
			arr[j - 1] = d;
			swp += 3; cmp++;
		}
	}

}
void comb_sort(float* arr, int t)
{
	float f = 1.2473309;
	int stp = t - 1;
	while (stp >= 1)
	{
		for (int i = 0; i + stp < t; i++)
		{   cmp++;
			if (arr[i] > arr[i + stp])
			{
				float d = arr[i];
				arr[i] = arr[i + stp];
				arr[i + stp] = d;
				swp++;
			}
		} 
		stp /= f;
	} 
	
}
void merge(float* arr, float* arr2, int lt, int mid, int rt)
{
	mid = (lt + rt) / 2;
	

	int minlt = lt;
	int minrt = mid + 1;
	int minarr2 = lt;
	while ((minlt <= mid) && (minrt <= rt))
	{
		if (arr[minlt] <= arr[minrt])
		{
			arr2[minarr2] = arr[minlt];
			minlt++;
			swp++;
		}
		else
		{
			arr2[minarr2] = arr[minrt];
			minrt++;
			swp++;
		}
		minarr2++;
		cmp++;
	}
	if (minlt > mid)
	{
		for (int i = minrt; i <= rt; i++)
		{
			arr2[minarr2] = arr[i];
			minarr2++;
			swp++;
		}
	}
	else
	{
		for (int i = minlt; i <= mid; i++)
		{
			arr2[minarr2] = arr[i];
			minarr2++;
			swp++;
		}
	}
	for (int i = lt; i <= rt; i++)
	{
		arr[i] = arr2[i];
	}
}
void merge_sort(float* arr, float* arr2, int lt, int rt)
{
	if (lt < rt)
	{
		int mid = (lt + rt) / 2;
		merge_sort(arr, arr2, lt, mid);
		merge_sort(arr, arr2, mid + 1, rt);
		merge(arr, arr2, lt, mid, rt);
	}
}
void createCounters(float* arr, int* counters, int t)
{
    int i;
    unsigned char* bp = (unsigned char*)arr;
    unsigned char* arrend = (unsigned char*)(arr + t);

	memset(counters, 0, 256 * sizeof(float) * sizeof(int));
	while (bp != arrend)
	{
		for (i = 0; i < sizeof(float); i++){
			counters[256 * i + *(bp++)]++;
		}
	}
}
void radix_pass(short Offset, int t, float* arr, float* dest, int* count)
{
	float* sp;
	int q, c, i, * cp;
	unsigned char* bp;
	
	q = 0;
	cp = count;
	     for (i = 256; i > 0; --i, ++cp){
	     c = *cp;
		 *cp = q;
		 q += c;
	      }

	bp = (unsigned char*)arr + Offset;
	sp = arr;
	     for (i = t; i > 0; --i, bp += sizeof(float), ++sp){
		cp = count + *bp;
		dest[*cp] = *sp;
		(*cp)++;
		swp++;
	     }
}
void radix_Lpass(short Offset, int t, float* arr, float* dest, int* count)
{
	float* sp;
	int s, c, i, * cp;
	unsigned char* bp;

	int un = 0;
	for (i = 128; i < 256; i++) un += count[i];

	s = un;
	cp = count;
	for (i = 0; i < 128; ++i, ++cp)
	{
		c = *cp;
		*cp = s;
		s += c;
	}

	cp = count + 255;
	s = 0; *cp = 0;
	for (i = 255; i >= 128; i--, cp--)
	{
		s += *cp;
		*cp = s;
	}
	bp = (unsigned char*)arr + Offset;
	sp = arr;
	for (i = t; i > 0; i--, bp += sizeof(float), sp++)
	{
		cp = count + *bp;
		if (*bp < 128)
		{
			dest[*cp] = *sp;
			(*cp)++;
		}
		else
		{
			(*cp)--;
			dest[*cp] = *sp;
		}
		swp++;
	}
}
void radix_sort(float* arr, int t)
{
	int i;
	float* tp;
	float* dest = (float*)malloc(sizeof(float) * t);
	int* counters = (int*)malloc(sizeof(float) * 256 * sizeof(int));
	int* count;

	createCounters((float*)arr, counters, t);

	for (i = 0; i < sizeof(float) - 1; i++)
	{
		count = counters + 256 * i;
		radix_pass(i, t, arr, dest, count);
		tp = arr;
		arr = dest;
		dest = tp;
	}
	count = counters + 256 * (sizeof(float) - 1);
	radix_Lpass(sizeof(float) - 1, t, arr, dest, count);

	tp = arr;
	arr = dest;
	dest = tp;

	free(dest);
	free(counters);
}


int main()
{
	srand(time(0));
	float arr[1000];
	float arr2[sizeof arr];
	int sort;
	int t;
	int i;
	int a;
	printf(" \n");
	printf(" \n");
	printf("THE SORTING ALGORITHM \n");
	printf(" \n");
	printf("Welcome dear user!\n ");
	printf(" \n");
	printf("In this program you can sort the array.\n");
	printf(" \n");
	printf("Choose size of array: ");
	scanf("%d", &t);
	printf("Avalible sorts:\n");
	printf("1)Insert sort \n");
	printf("2) Comb sort\n");
	printf("3) Merge sort\n");
	printf("4) Radix sort\n");
	printf("Choose type of sort: ");
	scanf("%d", &sort);
	printf(" \n");
	for (i = 0; i < t; i++)
		arr[i] = rand() * 0.001 * pow(-1, i);
	cmp = 0;
	swp = 0;
	printf("Default array: \n");
	for (i = 0; i < t; i++)
	{
		printf("array[");
		printf("%d", i);
		printf("]=");
		printf("%f ", arr[i]);
		printf(" \n");
	}
	printf(" \n");
	if (sort == 1)
		insrt_sort(arr, t);
	
	
	if (sort == 2)
		comb_sort(arr, t);
		
		
    if (sort == 3)
		merge_sort(arr, arr2, 0, t - 1);
			
			
	if (sort == 4)
		radix_sort(arr, t);
			
		
	
	printf("Sorted array: \n");
	for (i = 0; i < t; i++)
	{
		printf("array[");
		printf("%d", i);
		printf("]=");
		printf("%f ", arr[i]);
		printf(" \n");
	}


	if (arr[i] <= arr[i + 1])
		printf("Correctly");
	else
		printf("Uncorrectly");


	printf(" \n");
	printf(" \n");
	printf("Sum of comparisons: ");
	printf("%d", cmp);
	printf("\n");
	printf("Sum of swaps: ");
	printf("%d", swp);
	printf(" \n");
	printf(" \n");

	printf("You're great!\n");
	printf(" \n");
	printf("See you soon!\n");
	printf(" \n");
