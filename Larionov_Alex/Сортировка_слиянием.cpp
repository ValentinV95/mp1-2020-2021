#include<iostream>
#include<stdio.h>
void merge(double array[], double spare[], int l, int r)
{
	int i = l, q = (l + r) / 2, j = q + 1, k = 0;
	while (i <= q && j <= r)
	{
		if (array[i] <= array[j])
		{
			spare[k] = array[i];
			i++;
		}
		else
		{
			spare[k] = array[j];
			j++;
		}
		k++;
	}
	while (i <= q)
	{
		spare[k] = array[i];
		i++; k++;
	}
	while (j <= r)
	{
		spare[k] = array[j];
		j++;
		k++;
	}
	for (i = 0; i < k; i++)
		array[l + i] = spare[i];
}
int merge_sort(double array[], double spare[], int l, int r)
{
	if (l < r)
	{
		int q = (l + r) / 2;
		merge_sort(array, spare, l, q);
		merge_sort(array, spare, q + 1, r);
		merge(array, spare, l, r);
	}
	return(0);
}
