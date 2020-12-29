#include<iostream>
#include<stdio.h>
void Shell_sort(double array[],const int n)
{
	int step, i, j;
	double tmp;
	for(step=n/2;step>0;step/=2)
		for(i=step;i<n;i++)
			for (j = i - step; j >= 0 && array[j] > array[j + step]; j -= step)
			{
				tmp = array[j];
				array[j] = array[j + step];
				array[j + step] = tmp;
			}
}