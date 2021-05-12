

#include "sorts.h"
#include "stdlib.h"
#include "memory.h"

static void swap(float* a, float* b)
{
	float temp = *a;
	*a = *b;
	*b = temp;
}

static void ptrSwap(float** a, float** b)
{
	float* temp = *a;
	*a = *b;
	*b = temp;
}

testInfo bubbleSort(float* const arr, size_t len)
{
	int flag = 1;
	testInfo report;
	report.swapCount = report.compareCount = 0;

	for (size_t i = 0; i < len && flag; i++)
	{
		flag = 0;
		for (size_t j = len - 1; j > i; j--)
		{
			report.compareCount++;
			if (arr[j] < arr[j - 1]) {
				swap(&arr[j], &arr[j - 1]);
				report.swapCount++;

				flag = 1;
			}
		}
	}

	return report;
}

static int64_t _partition(float* arr, int64_t left, int64_t right, testInfo* report)
{
	// pos - псевдослучайное 32-х битное число на [left, right)
#if RAND_MAX <= (1 << 16)
	int64_t pos = (rand() | (rand() << 15)) % (right - left) + left;
#else
	int64_t pos = rand() % (right - left) + left;
#endif

	float pivot = arr[pos];

	while (left < right)
	{
		while (left <= right && arr[left] <= pivot)
		{
			report->compareCount++;
			left++;
		}
		while (left <= right && arr[right] >= pivot) 
		{
			report->compareCount++;
			right--;
		}

		if (left < right) {
			report->swapCount++;
			swap(&arr[left], &arr[right]);
		}
	}

	report->swapCount++;
	if (pos > left) {
		swap(&arr[pos], &arr[left]);
		return left;
	}

	swap(&arr[pos], &arr[left - 1]);
	return left - 1;
}

static void _quickSort(float* arr, int64_t first, int64_t last, testInfo* report)
{
	if (first < last) {
		int64_t p = _partition(arr, first, last, report);
		_quickSort(arr, first, p - 1, report);
		_quickSort(arr, p + 1, last, report);
	}
}

testInfo quickSort(float* const arr, size_t len)
{
	testInfo report;
	report.compareCount = report.swapCount = 0;

	_quickSort(arr, 0, (int64_t)len - 1, &report);

	return report;
}

static void _merge(float* arr, float* buffer, size_t l, size_t r, size_t mid, testInfo* report)
{
	size_t i = l, j = mid + 1, k = l;

	while (i <= mid || j <= r)
	{
		report->swapCount++;

		if (i <= mid && j <= r) {
			report->compareCount++;
		}
		if (j > r || (i <= mid && arr[i] < arr[j])) {
			buffer[k] = arr[i];
			i++;
		}
		else {
			buffer[k] = arr[j];
			j++;
		}

		k++;
	}
}

static void _mergeSort(float* arr, float* buffer, size_t l, size_t r, testInfo* report)
{
	if (l < r) {
		size_t mid = l + (r - l) / 2;

		// при рекурсивном вызове arr и buffer мен€ютс€ местами
		_mergeSort(buffer, arr, l, mid, report);
		_mergeSort(buffer, arr, mid + 1, r, report);
		_merge(buffer, arr, l, r, mid, report);
	}
}

#pragma warning(push)
#pragma warning(disable:6011)
#pragma warning(disable:6386)
testInfo mergeSort(float* const arr, size_t len)
{
	testInfo report;
	float* buffer = (float*)malloc(len * sizeof(float));
	report.compareCount = report.swapCount = 0;

	for (size_t i = 0; i < len; i++)
	{
		buffer[i] = arr[i];
	}

	_mergeSort(arr, buffer, 0, len - 1, &report);

	free(buffer);
	
	return report;
}
#pragma warning(pop)

static void _radixNormalizeInPlace(float* arr, size_t len, testInfo* report)
{
	if (arr[len - 1] > 0) return;

	report->swapCount += len / 2;
	for (size_t i = 0; i < len/2; i++)
	{
		swap(&arr[i], &arr[len - i - 1]);
	}
	
	size_t j = 0;
	while (j < len && arr[j] < 0) j++;

	report->swapCount += (len + j) / 2 - j;
	for (size_t i = j; i < (len + j) / 2; i++)
	{
		swap(&arr[i], &arr[len + j - i - 1]);
	}
}

static void _radixNormalize(float* arr, float* buffer, size_t len)
{
	size_t i = len - 1;
	size_t pos = 0;

	for (; i > 0 && buffer[i] < 0; i--, pos++)
	{
		arr[pos] = buffer[i];
	}

	for (size_t j = 0; j <= i; j++, pos++)
	{
		arr[pos] = buffer[j];
	}
}

testInfo radixSort(float* const arr, size_t len)
{
	const int countValues = (1 << 8);

	testInfo report;
	size_t counts[sizeof(float)][countValues];
	float* tempArr;
	float* buffer;

	memset(counts, 0, sizeof(float) * countValues * sizeof(size_t));

	report.compareCount = report.swapCount = 0;

	for (int byteNumber = 0; byteNumber < sizeof(float); byteNumber++)
	{
		for (size_t i = 0; i < len; i++)
		{
			int val = ((uint8_t*)&arr[i])[byteNumber];
			counts[byteNumber][val]++;
		}
	}

	for (int byteNumber = 0; byteNumber < sizeof(float); byteNumber++)
	{
		size_t sum = 0;
		for (int i = 0; i < countValues; i++)
		{
			sum += counts[byteNumber][i];
			counts[byteNumber][i] = sum - counts[byteNumber][i];
		}
	}

	tempArr = arr;
	buffer = (float*)malloc(sizeof(float) * len);
	if (buffer == NULL) exit(0);

	for (int byteNumber = 0; byteNumber < sizeof(float); byteNumber++)
	{
		for (size_t i = 0; i < len; i++)
		{
			int val = ((uint8_t*)&tempArr[i])[byteNumber];

			buffer[counts[byteNumber][val]] = tempArr[i];
			counts[byteNumber][val]++;

			report.swapCount++;
		}

		ptrSwap(&buffer, &tempArr);
	}

	if (arr == tempArr) {
		_radixNormalizeInPlace(arr, len, &report);
		
		free(buffer);
	}
	else {
		_radixNormalize(arr, tempArr, len);
		report.swapCount += len;

		free(tempArr);
	}

	return report;
}

static int compare(const void* a, const void* b)
{
	if (*(float*)a == *(float*)b) return 0;
	if (*(float*)a < *(float*)b) return -1;
	return 1;
}

#pragma warning(push)
#pragma warning(disable:6011)
#pragma warning(disable:6385)
#pragma warning(disable:6386)
#pragma warning(disable:6387)
testInfo checkSort(float* const arr, size_t len, testInfo(sortFunc)(float* const, size_t))
{
	float* arrCopy = (float*)malloc(sizeof(float) * len);
	for (int i = 0; i < len; i++)
	{
		arrCopy[i] = arr[i];
	}

	testInfo report = sortFunc(arr, len);
	qsort(arrCopy, len, sizeof(float), compare);

	report.isCorrect = 1;
	for (int i = 0; i < len; i++)
	{
		if (arr[i] != arrCopy[i]) {
			report.isCorrect = 0;
			break;
		}
	}

	free(arrCopy);

	return report;
}
#pragma warning(pop)