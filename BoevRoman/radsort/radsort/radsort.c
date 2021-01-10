// radsort.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define uchar unsigned char
#define ushort unsigned short
int perm = 0;

void rpass(short Offset, long N, double* source, double* dest, long* count) {
	double* sp;
	long s = 0, c, i, * cp = count;
	uchar* bp;

	for (i = 256; i > 0; --i, ++cp) {
		c = *cp; *cp = s; s += c;
	}
	bp = (uchar*)source + Offset;
	sp = source;
	for (i = N; i > 0; --i, bp += sizeof(double), ++sp) {
		cp = count + *bp; dest[*cp] = *sp; (*cp)++;
	}
}

void create_count(double* data, long* counters, long N) {

	uchar* bp = (uchar*)data;
	uchar* dataEnd = (uchar*)(data + N);
	ushort i;

	memset(counters, 0, 256 * sizeof(double) * sizeof(long));

	while (bp != dataEnd) {
		for (i = 0; i < sizeof(double); i++)
			counters[256 * i + *(bp++)]++;
	}
}

void double_rlastpass(short Offset, long N, double* source, double* dest, long* count) {
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

void rsort_in(double* in, double* out, long* counters, long N) {

	long* count;
	ushort i;
	create_count(in, counters, N);

	for (i = 0; i < sizeof(double) - 1; i++) {
		count = counters + 256 * i;
		rpass(i, N, in, out, count);
		for (long j = 0; j < N; j++) {
			in[j] = out[j];
			perm++;
		}
	}

	count = counters + 256 * i;
	double_rlastpass(i, N, in, out, count);
	for (long j = 0; j < N; j++) {
		perm++;
		in[j] = out[j];
	}
}



void radsort(double* in, long N) {
	double* out = (double*)malloc(N * sizeof(double));
	long* counters = (long*)malloc(sizeof(double) * 256 * sizeof(long));
	rsort_in(in, out, counters, N);
	free(out);
	free(counters);
}

void main()
{
	double a[8];
	int r;
	scanf_s("%d", &r);
	srand(r);
	for (int i = 0; i < 8; i++)
		a[i] = (double)(rand() % 5200) / 100;
	for (int i = 0; i < 8; i++)
		printf("%lf ", a[i]);
	printf("\n");
	radsort(a, 8);
	for (int i = 0; i < 8; i++)
		printf("%lf ", a[i]);
	printf("\n perm = %d\n", perm);
	int end;
	scanf_s("%d",&end);
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
