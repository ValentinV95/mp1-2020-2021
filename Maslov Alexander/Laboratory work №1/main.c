#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <vcruntime_string.h>


int comparisons = 0;
int permutations = 0;


void fill_array_randomly(float array[], int size)
{
	for (int i = 0; i < size; i++)
	{
		srand(time(NULL) ^ i);
		array[i] = (rand() / 3.14) * pow(-1, rand());
	}
}

void show_array(float array[], int size) {
	for (int i = 0; i < size; ++i)
	{
		printf("%f ", array[i]);
	}
	printf("\n\n");
}

void check_array_for_sorting(float array[], int size)
{
	int counter = 0;
	for (int i = 1; i < size; ++i)
	{
		if (array[i] < array[i - 1])
		{
			counter++;
		}
	}
	if (counter == 0)
	{
		printf("Array is sorted\n");
	}
	else {
		printf("Array isn't sorted\n");
	}
}

int find_max_index(float array[], int size)
{
	int max_elem_index = 0;
	for (int j = 1; j <= size; j++)
	{
		comparisons++;
		if (array[j] >= array[max_elem_index])
		{
			max_elem_index = j;
		};
	};
	return max_elem_index;
}

void swap(float* a, float* b)
{
	float tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
	permutations++;
}

void merge(float array[], int size)
{
	float* third_arrray = (float*)malloc(size * sizeof(float));
	float* left_array_part = array;
	float* right_array_part = &array[size / 2];
	int left_array_part_size = size / 2;
	int right_array_part_size = size - (size / 2);
	int left_array_counter = 0, right_array_counter = 0, third_array_counter = 0;
	while (1)
	{
		comparisons +=3;
		permutations++;
		if (array[left_array_counter] < right_array_part[right_array_counter])
		{
			third_arrray[third_array_counter] = array[left_array_counter];
			left_array_counter++;
			third_array_counter++;
		}
		else
		{
			third_arrray[third_array_counter] = right_array_part[right_array_counter];
			right_array_counter++;
			third_array_counter++;
		}
		if (left_array_counter == left_array_part_size)
		{
			while (right_array_counter != right_array_part_size)
			{
				third_arrray[third_array_counter] = right_array_part[right_array_counter];
				right_array_counter++;
				third_array_counter++;
			}
			break;
		}
		if (right_array_counter == right_array_part_size)
		{
			while (left_array_counter != left_array_part_size)
			{
				third_arrray[third_array_counter] = array[left_array_counter];
				left_array_counter++;
				third_array_counter++;
			}
			break;
		}
	}
	memcpy(array, third_arrray, size * sizeof(float));
	permutations += size;
	free(third_arrray);

}

void create_counters(float* data, int* counters, int size)
{
	unsigned char* bp = (unsigned char*)data;
	unsigned char* dataEnd = (unsigned char*)(data + size);
	unsigned short i;
	memset(counters, 0, 256 * sizeof(float) * sizeof(int));
	while (bp != dataEnd)
	{
		for (i = 0; i < sizeof(float); i++)
		{
			counters[256 * i + *(bp++)]++;
		}
	}
}

void radix_pass(short offset, int size, float* source, float* dest, int* count)
{
	float* sp;
	int s = 0, c, i, * cp = count;
	unsigned char* bp;
	for (i = 256; i > 0; --i, cp++)
	{
		c = *cp;		*cp = s;		s += c;
	}
	bp = (unsigned char*)source + offset;
	sp = source;
	for (i = size; i > 0; --i, bp += sizeof(float), ++sp)
	{
		cp = count + *bp;
		dest[*cp] = *sp;
		(*cp)++;
		permutations++;
	}
}

int input_array(float arr[], int size) 
	{
	printf("Input %d numbers\n", size);
	for (int i = 0; i < size; i++) 
		{
		printf("array[%d] = ", i);
		scanf_s("%f", &arr[i]);
		}
	printf("Array was filled\n");
	return 0;
	}




void selection_sort(float array[], int size)
{
	for (int last_unsorted_index = size - 1; last_unsorted_index > 0; last_unsorted_index--)
	{
		int max_elem_index = find_max_index(array, last_unsorted_index);
		swap(&array[max_elem_index], &array[last_unsorted_index]);
	};
};

void shell_sort(float array[], int size)
{
	int i, j, step;
	float temporary;
	for (step = size / 2; step > 0; step = step / 2)
	{
		for (i = step; i < size; i++)
		{
			temporary = array[i];
			permutations++;
			for (j = i; j >= step; j = j - step)
			{
				comparisons++;
				if (temporary < array[j - step])
				{
					array[j] = array[j - step];
				}
				else
				{
					break;
				}

			}
			array[j] = temporary;
			permutations++;
		}
	}
}

void merge_sort(float array[], int size)
{

	float* left_array_part = array;
	float* right_array_part = &array[size / 2];
	int left_array_part_size = size / 2;
	int right_array_part_size = size - (size / 2);
	if (size < 2)
	{
		return;
	}
	merge_sort(left_array_part, left_array_part_size);
	merge_sort(right_array_part, right_array_part_size);
	merge(left_array_part, size);
}

void radix_sort(float* array, int size)
{
	float* temporary_array = (float*)malloc(size * sizeof(float));
	int* counters = (int*)malloc(1024 * sizeof(int));
	int* count;
	int k = 0;
	create_counters(array, counters, size);
	for (unsigned short i = 0; i < sizeof(float); i++)
	{
		count = counters + 256 * i;
		radix_pass(i, size, array, temporary_array, count);
		for (int j = 0; j < size; j++)
		{
			array[j] = temporary_array[j];
		}
	}
	while (array[k] >= 0 && k < size && !(k > 0 && array[k] <= 0 && array[k - 1] > 0)) k++;
	for (int i = 0; i < size - k; i++)
	{
		array[i] = temporary_array[size - 1 - i];
	}
	for (int i = 0; i < k; i++)
	{
		array[size - k + i] = temporary_array[i];
	}
	permutations++;
	memcpy(array, temporary_array, size * sizeof(float));
	free(temporary_array);
	free(counters);
}



int main()
{

	int size;
	int option = 0;
	int exitcode = 0;
	printf("Enter the length of array: ");
	scanf_s("%d", &size);
	float* array = (float*)malloc(size * sizeof(float));
	input_array(array, size);
	show_array(array, size);
	printf("1 - selection sort\n");
	printf("2 - shell sort\n");
	printf("3 - merge sort\n");
	printf("4 - radix sort\n");
	printf("Enter the number of sort: ");
	scanf_s("%d", &option);

	do
	{
		switch (option)
		{
		case 1:
			selection_sort(array, size);
			exitcode = 1;
			break;
		case 2:
			shell_sort(array, size);
			exitcode = 1;
			break;
		case 3:
			merge_sort(array, size);
			exitcode = 1;
			break;
		case 4:
			radix_sort(array, size);
			exitcode = 1;
			break;
		default:
			printf("Wrong value, try again\n\n");
			printf("Enter the number of sort: ");
			scanf_s("%d", &option);
		}
	} while (exitcode != 1);
	show_array(array, size);
	printf("Number of sort: %d\n", option);
	printf("Number of comparisons: %d\n", comparisons);
	printf("Number of permutations: %d\n", permutations);
	free(array);
}