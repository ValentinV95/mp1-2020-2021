#include <stdio.h>
#include <time.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int comparisons, transpositions;

/*
 *
 *   
 *
 */

int inputArray(double arr[], int size) {
	printf("Input %d numbers\n", size);
	for (int i = 0; i < size; i++){
		printf("array[%d] = ", i);
		scanf("%lf", &arr[i]);
	}
	printf("Array is full!\n");
	return 0;
}

void fillArrayRandomNumber(double array[], int size){
	for (int i = 0; i < size; i++)
	{
		srand(time(0)*i);
		array[i] = rand() * 0.001 * pow(-1, i);
	}
}

void fillArrayInvert(double array[], int size){
	array[0] = size;
	for (int i = 1; i < size; i++)
	{
		array[i] = array[i-1]-1;
	}
}

void fillArrayEasy(double array[], int size){
	array[0] = 0;
	for (int i = 1; i < size; i++)
	{
		array[i] = array[i-1]+1;
	}
}

void showArray(double array[], int size) {
	for (int i = 0; i < size; ++i)
	{
		printf("%lf ", array[i]);
		//printf("%d", (0b10000000 & (char)array[i]) ? 1 : 0);
	}
	printf("\n\n");
}

void swap(double* a, double* b) {
	double tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

int compare(const void * x1, const void * x2){
  	return ( *(int*)x1 - *(int*)x2 );
}

void checkSort(double array[], int size){
	double* second_array = (double*)malloc(size * sizeof(double));
	for (int i = 0; i < size; i++)
	{
		second_array[i] = array[i];
	}
	qsort(second_array, size, sizeof(double), compare);
	bool check = true;
	for (int i = 0; i < size; i++)
	{
		if (second_array[i] != array[i]) {
			check = false;
			break;
		}
	}
	if (check == false) {
		printf("No matching");
	}
	else{
		printf("Nice, arrays matching");
	}
}

//***

/*
 *
 *   Functions for Bubble Sort sorting an array
 *
 */


void bubbleSort(unsigned int n, double array[]){
	for (int i = n - 1; i >= 0; i--){
		bool noSwap = true;
		for (int j = 0; j < i; j++){
			if (array[j] > array[j + 1]){
				swap(&array[j], &array[j+1]);
				transpositions++;
				noSwap = false;
			}
			comparisons++;
		}
		if (noSwap == true){
			break;
		}
	}
}

//***

/*
 *
 *   Functions for Quick Sort sorting an array
 *
 */

int partition(double* a, int l, int r){
	double v = a[(l + r) / 2];
	int i = l;
	int j = r;
	while (i <= j){
		while (a[i] < v) {
			i++;
			comparisons++;
		}
		while (a[j] > v) {
			j--;
			comparisons++; 
		}
		if (j <= i){
		 	break;
		}
		swap(&a[i++], &a[j--]);
		transpositions++;
		comparisons++;
	}
	return j;
}

void quickSort(double* array, int l, int r) 
{
	if (r > l)
	{
		int q = partition(array, l, r);
		quickSort(array, l, q);
		quickSort(array, q + 1, r);
	}
}

//***

/*
 *
 *   Functions for Merge Sort sorting an array
 *
 */

void merge(double* arr, double* l, double* r, int lcount, int rcount){	
	int i = 0, j = 0, k = 0;
	while ((i < lcount) && (j < rcount)){
		comparisons++;
		transpositions++;
		if (l[i] < r[j]){
		 	arr[k++] = l[i++];
		}
		else {arr[k++] = r[j++];}
	}
	while (i < lcount) {
		arr[k++] = l[i++]; 
		transpositions++;
	}
	while (j < rcount) {
		arr[k++] = r[j++];
		transpositions++;
	}
}

void mergeSort(double* array, int n){
	int mid;
	if (n < 2) return;
	mid = n / 2;
	double* l = (double*)malloc(mid * sizeof(double));
	double* r = (double*)malloc((n - mid) * sizeof(double));
	for (int i = 0; i < mid; i++){
	 	l[i] = array[i];
	}
	for (int i = mid; i < n; i++){
		r[i - mid] = array[i];
	}	
	mergeSort(l, mid);
	mergeSort(r, n - mid);
	merge(array, l, r, mid, n - mid);
	free(l);
	free(r);
}

//***

/*
 *
 *   Functions for Radix Sort sorting an array
 *
 */


void create_counters(double* array, int* counters, int size){
	unsigned char* bp = (unsigned char*)array;
	unsigned char* dataEnd = (unsigned char*)(array + size);
	unsigned short i;
	memset(counters, 0, 256 * sizeof(double) * sizeof(int));
	while (bp != dataEnd){
		for (i = 0; i < sizeof(double); i++){
			counters[256 * i + *(bp++)]++;
		}
		
	}
}

void radix_pass(short offset, int size, double* source, double* dest, int* count){
	double* sp;
	int s = 0, c, i, * cp = count;
	unsigned char* bp;
	for (i = 256; i > 0; --i, cp++)
	{
		c = *cp;		*cp = s;		s += c;
	}
	bp = (unsigned char*)source + offset;
	sp = source;
	for (i = size; i > 0; --i, bp += sizeof(double), ++sp)

	{
		cp = count + *bp;
		dest[*cp] = *sp;
		(*cp)++;
		transpositions++;

	}
}

void radixSort(double* array, int size){
	double* additional_array = (double*)malloc(size * sizeof(double));
	int* counters = (int*)malloc(2048 * sizeof(int));
	int* count;
	int k = 0;
	create_counters(array, counters, size);
	for (unsigned short i = 0; i < sizeof(double); i++)
	{
		count = counters + 256 * i;
		radix_pass(i, size, array, additional_array, count);
		for (int j = 0; j < size; j++)
		{
			array[j] = additional_array[j];
		}
	}
	while (array[k] >= 0 && k < size && !(k > 0 && array[k] <= 0 && array[k - 1] > 0)) k++;
	for (int i = 0; i < size - k; i++)
	{
		array[i] = additional_array[size - 1 - i];
	}
	for (int i = 0; i < k; i++)
	{
		array[size - k + i] = additional_array[i];
	}
	transpositions++;
	memcpy(array, additional_array, size * sizeof(double));
	free(additional_array);
	free(counters);
}

//***

int main()
{
	int size;
	int menuChoice = 0;
	int exitcode = 0;
	bool arrayExist = false;


	printf("Menu:\n");
	printf("1 - Fill Array\n");
	printf("2 - Bubble Sort\n");
	printf("3 - Quick sort\n");
	printf("4 - Merge sort\n");
	printf("5 - Radix sort\n");


	printf("Select menu item: ");
	scanf("%d", &menuChoice);

	do
	{
		switch (menuChoice)
		{
		case 0:
			printf("Enter the number of sort: ");
			scanf("%d", &menuChoice);
			break;
		case 1:
			printf("How many elements are in the array?: ");
			scanf("%d", &size);
			double* array = (double*)malloc(size * sizeof(double));
			inputArray(array, size);
			//fillArrayInvert(array, size);
			//fillArrayEasy(array, size);
			showArray(array, size);
			arrayExist = true;
			menuChoice = 0;
			break;
		case 2:
			if (arrayExist){
				bubbleSort(size, array);
				showArray(array, size);
				free(array);
			}
			exitcode = 1;
			break;
		case 3:
			if (arrayExist){
				quickSort(array, 0, size - 1);
				showArray(array, size);
				free(array);
			}	
			exitcode = 1;
			break;
		case 4:
			if (arrayExist){
				mergeSort(array, size);
				showArray(array, size);
				free(array);
			}	
			exitcode = 1;
			break;
		case 5:
			if (arrayExist){
				radixSort(array, size);
				showArray(array, size);
				free(array);
			}
			exitcode = 1;
			break;
		
		default:
			printf("Wrong value, try again\n\n");
			printf("Select menu item: ");
			scanf("%d", &menuChoice);
		}
	} while (exitcode != 1);
	printf("Sort number: %d\n", menuChoice);
	printf("Number of comparisons: %d\n", comparisons);
	printf("Number of transpositions: %d\n", transpositions);
	
}