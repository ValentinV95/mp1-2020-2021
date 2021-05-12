#include <clocale>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include "Menus.h"


int main()
{
	srand(time(NULL));
	int n = 15;
	float* arr = (float*)malloc(n * sizeof(float));

	menu(&arr, &n);

	free(arr);
	return 0;
}
