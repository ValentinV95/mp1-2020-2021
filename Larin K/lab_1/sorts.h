#pragma once

#include "inttypes.h"

struct testInfo
{
	int64_t compareCount, swapCount;
	int isCorrect;
};
typedef struct testInfo testInfo;


testInfo bubbleSort(float* const arr, size_t len);
testInfo quickSort(float* const arr, size_t len);
testInfo mergeSort(float* const arr, size_t len);
testInfo radixSort(float* const arr, size_t len);

testInfo checkSort(float* const arr, size_t len, testInfo(sortFunc)(float* const, size_t));
