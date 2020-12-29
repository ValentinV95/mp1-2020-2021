#include <iostream>
#include <stdio.h>
void insertion_sort(double arr[], int n)
{
	int a = 0; int b = 0;
	for (int i = 1; i < n; i++)
		for (int j = i; j > 0 && arr[j - 1] - arr[j] >= 0; j--)
		{
			double tmp = arr[j - 1];
			arr[j - 1] = arr[j];
			arr[j] = tmp;
			a = a + 3; b++;
		}
	printf("\n%d%s\n%d%s", a, "swaps", b, "comparisons");
}