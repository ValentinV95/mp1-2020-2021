
#include <malloc.h>
void Merge(float* mas, int begin, int end, size_t* c2, int* size);

void MergeSort(float* mas, int left, int right, size_t* c2, int* size) {
	float tmp;
	if (left < right) {
		MergeSort(mas, left, (left + right) / 2, c2, size);
		MergeSort(mas, (left + right) / 2 + 1, right, c2, size);
		Merge(mas, left, right, c2, size);
	}
	
}


void Merge(float* mas, int begin, int end, size_t* c2, int* size) {
	int i = begin, mid = (begin + end) / 2;
	int j = mid + 1;
	int k = 0;
	float* arr = (float*)malloc((*size) * sizeof(float));

	while (i <= mid && j <= end) {
		if (mas[i] <= mas[j]) {
			(*c2)++;
			arr[k] = mas[i];
			i++;
		}
		else {
			arr[k] = mas[j];
			j++;
			(*c2)++;
		}
		k++;
	}

	while (i <= mid) {
		arr[k] = mas[i];
		i++;
		k++;
	}
	while (j <= end) {
		arr[k] = mas[j];
		j++;
		k++;
	}

	for (int i = 0; i < k; i++)
		mas[begin + i] = arr[i];

}