#include<iostream>
#include<stdio.h>
void countingSort(int* array, int* dest, int n, int m)
{
	int count[m+1] = { 0 };
	int tmp1 = 0, tmp2 = 0;
	for (int i = 0; i < n; i++)
		count[array[i]]++;
	tmp1 = count[0]; count[0] = 0;
	for (int i = 1; i <= m; i++) {
		tmp2 = count[i];       count[i] = count[i - 1] + tmp1;       tmp1 = tmp2;
	}
	for (i = 0; i < n; i++) {
		c = array[i];
		dest[count[c]] = c;
		count[c]++;
	}
