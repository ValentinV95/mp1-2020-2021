#include <stdlib.h>
#include <string.h>

typedef unsigned char uchar;
typedef unsigned long ulong;
using namespace std;

ulong insertion_sort(double arr[], const int size) {
	ulong amount = 0;
	int i;
	double temp;
	for (i = 1;i < size;i++) {
		//по возрастанию
		for (int j = i; j > 0 && arr[j - 1] > arr[j];j--, amount++) {
			temp = arr[j];
			arr[j] = arr[j - 1];
			arr[j - 1] = temp;
			amount++;
		}
	}
	return amount;
}

ulong Shell_sort(double arr[], const int size) {
	ulong amount = 0;
	int step, i, j;
	double temp;

	for (step = size / 2; step > 0;step /= 2) {
		for (i = step; i < size;i++) {
			//по возрастанию
			for (j = i;j - step >= 0 && arr[j - step] > arr[j];j -= step, amount++) {
				temp = arr[j];
				arr[j] = arr[j - step];
				arr[j - step] = temp;
				amount++;
			}
		}
	}
	return amount;
}
ulong merge(double arr[], double second[], int left, int middle, int right) {
	int i;
	ulong amount = 0;
	int l_cur = left, r_cur = middle + 1;
	if (left == right) {
		second[left] = arr[left];
		amount++;
		return amount;
	}
	for (i = left;i <= right;i++, amount++) {
		if ((l_cur <= middle) && (r_cur <= right)) {
			//по возрастанию
			if (arr[l_cur] <= arr[r_cur]) {
				second[i] = arr[l_cur];
				l_cur++;
			}
			else {
				second[i] = arr[r_cur];
				r_cur++;
			}
			amount++;
		}
		else if (l_cur <= middle) {
			second[i] = arr[l_cur];
			l_cur++;
			amount++;
		}
		else {
			second[i] = arr[r_cur];
			r_cur++;
			amount++;
		}
		amount++;
	}
	return amount;
}
ulong mergesort(double arr[], double second[], int l, int r) {
	int i, q;
	ulong amount = 0;
	if (l < r) {
		q = (l + r) / 2;
		amount += mergesort(arr, second, l, q);
		amount += mergesort(arr, second, q + 1, r);
		amount += merge(arr, second, l, q, r);
		for (i = l;i <= r;i++) {
			arr[i] = second[i];
			amount++;
		}
		amount++;
	}
	return amount;
}
ulong _mergesort(double arr[], const int size) {
	ulong amount = 0;
	double* second = (double*)malloc(sizeof(double) * size);

	amount += mergesort(arr, second, 0, size - 1);

	free(second);
	return amount;
}

ulong createCounters(double* arr, long* counters, long N) {
	
	int i;
	ulong amount = 0;
	uchar* bp = (uchar*)arr;
	uchar* end = (uchar*)(arr + N);

	//количество возможных вариантов*кол-во разрядов(по 256)*тип данных массива counters
	memset(counters, 0, 256 * sizeof(double) * sizeof(long));
	while (bp != end) {
		for (i = 0;i < sizeof(double);i++) {
			counters[256 * i + *(bp++)]++;
			amount++;
		}
		amount++;
	}
	return amount;
}
ulong radixPass(short Offset, long size, double* arr, double* dest, long* count) {
	ulong amount = 0;
	double* sp;
	long s, c, i, * cp;
	uchar* bp;

	s = 0;
	cp = count;
	for (i = 256; i > 0; --i, ++cp) {
		c = *cp;
		*cp = s;
		s += c;
		amount++;
	}

	bp = (uchar*)arr + Offset;
	sp = arr;
	for (i = size; i > 0; --i, bp += sizeof(double), ++sp) {
		cp = count + *bp;
		dest[*cp] = *sp;
		(*cp)++;
		amount++;
	}
	return amount;
}
ulong radixLastPass(short Offset, long size, double* arr, double* dest, long* count) {
	ulong amount = 0;
	double* sp;
	long sum, c, i, * cp;
	uchar* bp;

	long numNeg = 0;
	for (i = 128;i < 256;i++) numNeg += count[i];

	sum = numNeg;
	cp = count;
	for (i = 0; i < 128; ++i, ++cp) {
		c = *cp;
		*cp = sum;
		sum += c;
		amount++;
	}
	
	cp = count + 255;
	sum = 0; *cp = 0;
	for (i = 255;i >= 128;i--,cp--) {
		sum += *cp;
		*cp = sum;
		amount++;
	}
	bp = (uchar*)arr + Offset;
	sp = arr;
	for (i = size; i > 0; i--, bp += sizeof(double), sp++) {
		cp = count + *bp;
		if (*bp < 128) {
			dest[*cp] = *sp;
			(*cp)++;
		}
		else {
			(*cp)--;
			dest[*cp] = *sp;
		}
		amount++;
	}
	return amount;
}

ulong radixSort(double arr[], const long size) {
	ulong amount = 0;
	int i;
	double* temp;
	double* dest = (double*)malloc(sizeof(double) * size);
	long* counters = (long*)malloc(sizeof(double) * 256 * sizeof(long));
	long* count;

	amount += createCounters((double*)arr, counters, size);

	for (i = 0; i < sizeof(double) - 1; i++) {
		count = counters + 256 * i;
		amount += radixPass(i, size, arr, dest, count);
		temp = arr;
		arr = dest;
		dest = temp;
	}
	count = counters + 256 * (sizeof(double) - 1);
	amount += radixLastPass(sizeof(double) - 1, size, arr, dest, count);

	temp = arr;
	arr = dest;
	dest = temp;

	free(dest);
	free(counters);
	return amount;
}