#include<stdlib.h>
#include<string.h>
#define uchar unsigned char
#define ushort unsigned short



int RadPer = 0;


void radixPass(short Offset, long N, double* source, double* dest, long* count) {
	double* sp;
	long s = 0, c, i, * cp = count;
	uchar* bp;

	for (i = 256; i > 0; --i, ++cp) {
		c = *cp;		*cp = s;		s += c;
	}
	bp = (uchar*)source + Offset;
	sp = source;
	for (i = N; i > 0; --i, bp += sizeof(double), ++sp) {
		cp = count + *bp;	dest[*cp] = *sp;		(*cp)++;
	}
}



void createCounters(double* data, long* counters, long N) {

	uchar* bp = (uchar*)data;             
	uchar* dataEnd = (uchar*)(data + N);
	ushort i;

	memset(counters, 0, 256 * sizeof(double) * sizeof(long));

	while (bp != dataEnd) {
		for (i = 0; i < sizeof(double); i++)
			counters[256 * i + *(bp++)]++;
	}
}



void doubleRadixLastPass(short Offset, long N, double* source, double* dest, long* count) {
	double* sp;
	long s, c, i, * cp;
	uchar* bp;

	long numNeg = 0;
	for (i = 128; i < 256; i++) numNeg += count[i];

	s = numNeg;
	cp = count;
	for (i = 0; i < 128; ++i, ++cp) {
		c = *cp;
		*cp = s;
		s += c;
	}

	
	s = count[255] = 0;                 
	cp = count + 254;                     
	for (i = 254; i >= 128; --i, --cp) {
		*cp += s;                       
		s = *cp;                        
	}

	bp = (uchar*)source + Offset;
	sp = source;
	for (i = N; i > 0; --i, bp += sizeof(double), ++sp) {
		cp = count + *bp;
		if (*bp < 128) dest[(*cp)++] = *sp;
		else dest[--(*cp)] = *sp;
	}
}







void radixSortIn(double* in, double* out, long* counters, long N) {
	
	long* count;
	ushort i;
	createCounters(in, counters, N);

	for (i = 0; i < sizeof(double) - 1; i++) {
		count = counters + 256 * i;
		radixPass(i, N, in, out, count);
		for (long j = 0; j < N; j++) {
			in[j] = out[j];
			RadPer++;
		}
	}

	count = counters + 256 * i;
	doubleRadixLastPass(i, N, in, out, count);
	for (long j = 0; j < N; j++) {
		RadPer++;
		in[j] = out[j];
	}
}



void radixSort(double* in, long N) {
	double* out = (double*)malloc(N * sizeof(double));
	long* counters = (long*)malloc(sizeof(double) * 256 * sizeof(long));
	radixSortIn(in, out, counters, N);
	free(out);
	free(counters);
}



int getRadixComparsion() { return 0; }
int getRadixPermutation() {
	int temp = RadPer;
	RadPer = 0;
	return temp;
}

