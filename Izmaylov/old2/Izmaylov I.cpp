#include<stdio.h>
#include <locale.h>
#include <stdlib.h>



void CheckSortD(double* arr, int M) {
	for (int j = 0; j < M - 1; j++)
		for (int v = M - 2; v > j - 1; v--)
			if (arr[v] > arr[v + 1]) {
				double tmp = arr[v];
				arr[v] = arr[v + 1];
				arr[v + 1] = tmp;
			}
	printf("--------------------------------------------------------------------------------\n\n");
	printf(" Отсортированный массив должен иметь следующий вид : \n\n");
	for (int j = 0; j < M; j++)
		printf("   %lf ", arr[j]);
	printf("\n\n");
	printf("--------------------------------------------------------------------------------\n\n");
	
}

void CheckSortI(int* arr, int M) {
	for (int j = 0; j < M - 1; j++)
		for (int v = M - 2; v > j - 1; v--)
			if (arr[v] > arr[v + 1]) {
				int tmp = arr[v];
				arr[v] = arr[v + 1];
				arr[v + 1] = tmp;
			}
	printf("--------------------------------------------------------------------------------\n\n");
	printf(" Отсортированный массив должен иметь следующий вид : \n\n");
	for (int j = 0; j < M; j++)
		printf("   %d ", arr[j]);
	printf("\n\n");
	printf("--------------------------------------------------------------------------------\n\n");

}





void insertionSort( double* arr, int size, double* ch)
{
	int vib = 0;
	int per = 0, srv = 0; 
	for (int i = 1; i < size; i++) {
		int j;
		for (j = i; i > 0 && arr[j - 1] > arr[j]; j--) {
			double tmp = arr[j];
			arr[j] = arr[j - 1];
			arr[j - 1] = tmp;
			per++;
			srv++;
		}
		if (j != 0)
			srv++;
	}
		
	printf("--------------------------------------------------------------------------------\n");
	printf(" Отсортированная последовательность:\n\n");
	printf(" ");
	for (int i = 0; i < size; i++)
		printf(" %.6lf ", arr[i]);
	
	printf("\n\n\n\n");

	printf(" Количество перестановок : %d\n", per);
	printf(" Количество сравнений : %d \n\n\n", srv);
	printf("--------------------------------------------------------------------------------\n\n");
	free(arr);
	printf(" Хотите проверить корректность выполнения программы?\n\n");
	printf(" Да - введите 1 и нажите Enter\n");
	printf(" Нет - введите 2  и нажмите Enter\n\n");
	printf(" ");
	scanf(" %d", &vib);
	if (vib == 1) {
		printf("\n\n");
		CheckSortD(ch, size);
	}
	free(ch);

}

void comb_sort(double* arr, int size, double *ch)
{
	int vib = 0;
	int per = 0, srv = 0;

	double factor = 1.2473309;
	int step = size - 1;
	while (step >= 1){
		for (int i = 0; i + step < size; i++) {
			if (arr[i] > arr[i + step]) {
				double tmp = arr[i];
				arr[i] = arr[i + step];
				arr[i + step] = tmp;
				per++;
				srv++;
			}
			else
				srv++;
		}
		step = step / factor;
	}
	
	
	printf("--------------------------------------------------------------------------------\n");
	printf(" Отсортированная последовательность:\n\n");
	printf(" ");
	for (int i = 0; i < size; i++)
		printf(" %lf ",  arr[i]);

	printf("\n\n\n\n");
	
	printf(" Количество перестановок : %d\n", per);
	printf(" Количество сравнений : %d \n\n\n", srv);
	printf("--------------------------------------------------------------------------------\n\n");

	free(arr);
	printf(" Хотите проверить корректность выполнения программы?\n\n");
	printf(" Да - введите 1 и нажите Enter\n");
	printf(" Нет - введите 2  и нажмите Enter\n\n");
	printf(" ");
	scanf(" %d", &vib);
	if (vib == 1) {
		printf("\n\n");
		CheckSortD(ch, size);
	}
	free(ch);
 }



void merge(double a[], double t[], int i, int l, int n, int *per, int *srv)
{
	//int j = i + l, n1 = min(j, n), n2 = min(j + l, n), k = i;
	int j = i + l, k = i;
	int n1, n2;

	if (j > n)
		n1 = n;
	else
		n1 = j;

	if (j + l > n)
		n2 = n;
	else
		n2 = j + l;


	while (i < n1 && j < n2)
		//t[k++] = a[i] <= a[j] ? a[i++] : a[j++];
		if (a[i] <= a[j]) {
			t[k++] = a[i++];
			per[0] = per[0] + 1 ;
			srv[0] = srv[0] + 1;
		}
		else {
			t[k++] = a[j++];
			per[0] = per[0] + 1;
			srv[0] = srv[0] + 1;
		}

	while (i < n1) {
		t[k++] = a[i++];
		per[0] = per[0] + 1;
	 }
	while (j < n2) {
		t[k++] = a[j++];
		per[0] = per[0] + 1;
	 }
}

void umsort(double *a, int n, double *ch)
{
	int vib = 0;
	int pers[1] = { 0 };
	int srvs[1] = { 0 };

	//int* srvs = (int*)malloc(1 * sizeof(int));
	//srvs[0] = 0;
	
	double* t = (double*)malloc(n * sizeof(double));
	int l = 1, i;

	while (l < n) {
		for (i = 0; i < n; i += 2 * l)
			merge(a, t, i, l, n, pers,srvs);
		l *= 2;
		for (i = 0; i < n; i += 2 * l)
			merge(t, a, i, l, n, pers, srvs);
		l *= 2;
	}
	
	
	printf("--------------------------------------------------------------------------------\n");
	printf(" Отсортированная последовательность:\n\n");
	printf(" ");
	for (int m = 0; m < n; m++)
		printf("%lf ", a[m]);
	
	printf("\n\n\n\n");
	
	printf(" Количество перестановок между массивами  %d \n", pers[0]);
	printf(" Количество сравнений элементов массива %d \n\n\n", srvs[0]);
	printf("--------------------------------------------------------------------------------\n\n");
	
	free(t);
	printf(" Хотите проверить корректность выполнения программы?\n\n");
	printf(" Да - введите 1 и нажите Enter\n");
	printf(" Нет - введите 2  и нажмите Enter\n\n");
	printf(" ");
	scanf(" %d", &vib);
	if (vib == 1) {
		printf("\n\n");
		CheckSortD(ch, n);
	}
	free(ch);
}



void Counters(int* data, long int* counters, long int  N) {

	//int *data -  массив разрядный, который считает количествво различных элементов в массиве
	unsigned char* bp = (unsigned char*)data;

	//data[1],   bp[1*sizeof(uint)]
 // указатели дают возможность приведить к другому виду, если мы будем обращаться к bp
// то будем воспринимать информацию хранящуюся в области памяти как char

	unsigned char* dataEnd = (unsigned char*)(data + N);
	unsigned short i;
	/////////////////long int memset(*counters, 0, 256 * sizeof(unsigned int) * sizeof(long));
	//couners - масси который будет обозначать количество необходимых разрядов, при этом
	// здесь будут храниться все разряды вряд 

	for (int jer = 0; jer < sizeof(long int) * 256; jer++)
		counters[jer] = 0;


	while (bp != dataEnd) {                                     //идет по всем данным, что у нас есть 
		for (i = 0; i < sizeof(unsigned int); i++)     // идет по разряду данного числа
			counters[256 * i + *(bp++)]++;               // идет по этому адресу   сначала произойдет разыменование и будет увеличиваться будет указатель а не значение 

	}
}

void radixPass(short Offset, long N, int* source, int* dest, long* count,int* pers, int*srvs) { // сортивровка одного разряда 
	// *count - общее количество элементов 
	int* sp;
	long s = 0, c, i, * cp = count;
	unsigned char* bp;

	for (i = 256; i > 0; --i, ++cp) {
		c = *cp;		*cp = s;		s += c;
	}
	bp = (unsigned char*)source + Offset;
	sp = source;
	for (i = N; i > 0; --i, bp += sizeof(unsigned int), ++sp) {
		cp = count + *bp;	dest[*cp] = *sp;		(*cp)++;
		pers[0] = pers[0] + 1;
	}
}

void signedRadixLastPass(short Offset, long N, int* source, int* dest, long* count, int*pers, int*srvs) {
	int* sp;
	long s, c, i, * cp, numNeg = 0;
	unsigned char* bp;

	// подсчет количества отрицательных чисел
	for (i = 128; i < 256; i++) {
		numNeg += count[i];
	}
	// первые 128 элементов count относятся к положительным числам.
	// отсчитываем номер первого числа, начиная от numNeg 
	s = numNeg;	cp = count;
	for (i = 0; i < 128; ++i, ++cp) {
		c = *cp;		*cp = s;		s += c;

	}
	s = 0;	cp = count + 128;
	for (i = 0; i < 128; ++i, ++cp) {
		c = *cp;		*cp = s;		s += c;
	}

	bp = (unsigned char*)source + Offset;
	sp = source;
	for (i = N; i > 0; --i, bp += sizeof(int), ++sp) {
		cp = count + *bp;	dest[*cp] = *sp;		(*cp)++;
		pers[0] = pers[0] + 1;
	}

}

void signedRadixSort(int* in, int* out, long N, int *per, int *srv) {
	//Размеры in, out – N, размер counters - sizeof(uint)*256

	long counters[sizeof(unsigned int) * 256];

	long* count; unsigned short i;
	Counters(in, counters, N);

	for (i = 0; i < sizeof(int) - 1; i++) {
		count = counters + 256 * i;
		radixPass(i, N, in, out, count, per ,srv);
		for (long j = 0; j < N; j++) {
			in[j] = out[j];
			per[0] = per[0] + 1;
		}
	}
	count = counters + 256 * i;
	signedRadixLastPass(i, N, in, out, count,per,srv);
}





void insertionSortExp(double* arr, int size)
{
	int per = 0, srv = 0;
	for (int i = 1; i < size; i++) {
		int j;
		for (j = i; i > 0 && arr[j - 1] > arr[j]; j--) {
			double tmp = arr[j];
			arr[j] = arr[j - 1];
			arr[j - 1] = tmp;
			per++;
			srv++;
		}
		if (j != 0)
			srv++;
	}

	printf("\n\n");

	printf(" Количество перестановок : %d\n", per);
	printf(" Количество сравнений : %d \n\n\n", srv);
	free(arr);

}


void comb_sortExp(double* arr, int size)
{
	int per = 0, srv = 0;

	double factor = 1.2473309;
	int step = size - 1;
	while (step >= 1) {
		for (int i = 0; i + step < size; i++) {
			if (arr[i] > arr[i + step]) {
				double tmp = arr[i];
				arr[i] = arr[i + step];
				arr[i + step] = tmp;
				per++;
				srv++;
			}
			else
				srv++;
		}
		step = step / factor;
	}



	printf("\n\n");

	printf(" Количество перестановок : %d\n", per);
	printf(" Количество сравнений : %d \n\n\n", srv);

	free(arr);
}


void mergeExp(double a[], double t[], int i, int l, int n, int* per, int* srv)
{
	//int j = i + l, n1 = min(j, n), n2 = min(j + l, n), k = i;
	int j = i + l, k = i;
	int n1, n2;

	if (j > n)
		n1 = n;
	else
		n1 = j;

	if (j + l > n)
		n2 = n;
	else
		n2 = j + l;


	while (i < n1 && j < n2)
		//t[k++] = a[i] <= a[j] ? a[i++] : a[j++];
		if (a[i] <= a[j]) {
			t[k++] = a[i++];
			per[0] = per[0] + 1;
			srv[0] = srv[0] + 1;
		}
		else {
			t[k++] = a[j++];
			per[0] = per[0] + 1;
			srv[0] = srv[0] + 1;
		}

	while (i < n1) {
		t[k++] = a[i++];
		per[0] = per[0] + 1;
	}
	while (j < n2) {
		t[k++] = a[j++];
		per[0] = per[0] + 1;
	}
}

void umsortExp(double* a, int n)
{
	int pers[1] = { 0 };
	int srvs[1] = { 0 };

	//int* srvs = (int*)malloc(1 * sizeof(int));
	//srvs[0] = 0;

	double* t = (double*)malloc(n * sizeof(double));
	int l = 1, i;

	while (l < n) {
		for (i = 0; i < n; i += 2 * l)
			merge(a, t, i, l, n, pers, srvs);
		l *= 2;
		for (i = 0; i < n; i += 2 * l)
			merge(t, a, i, l, n, pers, srvs);
		l *= 2;
	}

	printf("\n\n");

	printf(" Количество перестановок между массивами  %d \n", pers[0]);
	printf(" Количество сравнений элементов массива %d \n\n\n", srvs[0]);

	free(t);
}


void CountersExp(int* data, long int* counters, long int  N) {

	//int *data -  массив разрядный, который считает количествво различных элементов в массиве
	unsigned char* bp = (unsigned char*)data;

	//data[1],   bp[1*sizeof(uint)]
 // указатели дают возможность приведить к другому виду, если мы будем обращаться к bp
// то будем воспринимать информацию хранящуюся в области памяти как char

	unsigned char* dataEnd = (unsigned char*)(data + N);
	unsigned short i;
	/////////////////long int memset(*counters, 0, 256 * sizeof(unsigned int) * sizeof(long));
	//couners - масси который будет обозначать количество необходимых разрядов, при этом
	// здесь будут храниться все разряды вряд 

	for (int jer = 0; jer < sizeof(long int) * 256; jer++)
		counters[jer] = 0;


	while (bp != dataEnd) {                                     //идет по всем данным, что у нас есть 
		for (i = 0; i < sizeof(unsigned int); i++)     // идет по разряду данного числа
			counters[256 * i + *(bp++)]++;               // идет по этому адресу   сначала произойдет разыменование и будет увеличиваться будет указатель а не значение 

	}
}

void radixPassExp(short Offset, long N, int* source, int* dest, long* count, int* pers, int* srvs) { // сортивровка одного разряда 
	// *count - общее количество элементов 
	int* sp;
	long s = 0, c, i, * cp = count;
	unsigned char* bp;

	for (i = 256; i > 0; --i, ++cp) {
		c = *cp;		*cp = s;		s += c;
	}
	bp = (unsigned char*)source + Offset;
	sp = source;
	for (i = N; i > 0; --i, bp += sizeof(unsigned int), ++sp) {
		cp = count + *bp;	dest[*cp] = *sp;		(*cp)++;
		pers[0] = pers[0] + 1;
	}
}

void signedRadixLastPassExp(short Offset, long N, int* source, int* dest, long* count, int* pers, int* srvs) {
	int* sp;
	long s, c, i, * cp, numNeg = 0;
	unsigned char* bp;

	// подсчет количества отрицательных чисел
	for (i = 128; i < 256; i++) {
		numNeg += count[i];
	}
	// первые 128 элементов count относятся к положительным числам.
	// отсчитываем номер первого числа, начиная от numNeg 
	s = numNeg;	cp = count;
	for (i = 0; i < 128; ++i, ++cp) {
		c = *cp;		*cp = s;		s += c;

	}
	s = 0;	cp = count + 128;
	for (i = 0; i < 128; ++i, ++cp) {
		c = *cp;		*cp = s;		s += c;
	}

	bp = (unsigned char*)source + Offset;
	sp = source;
	for (i = N; i > 0; --i, bp += sizeof(int), ++sp) {
		cp = count + *bp;	dest[*cp] = *sp;		(*cp)++;
		pers[0] = pers[0] + 1;
	}

}

void signedRadixSortExp(int* in, int* out, long N, int* per, int* srv) {
	//Размеры in, out – N, размер counters - sizeof(uint)*256

	long counters[sizeof(unsigned int) * 256];

	long* count; unsigned short i;
	CountersExp(in, counters, N);

	for (i = 0; i < sizeof(int) - 1; i++) {
		count = counters + 256 * i;
		radixPassExp(i, N, in, out, count, per, srv);
		for (long j = 0; j < N; j++) {
			in[j] = out[j];
			per[0] = per[0] + 1;
		}
	}
	count = counters + 256 * i;
	signedRadixLastPassExp(i, N, in, out, count, per, srv);
}



void Experiment() {
	int j;
	int kol;
	printf("\n");
	printf(" Введите число, которое соответствует длине создаваемого массива ");
	scanf("%d", &kol);
	printf("\n");

	printf(" Выберите тип сортировки для Вашего эксперимента :\n");
	printf("      Сортировка <вставкой>           - нажмите 1 \n");
	printf("      Сортировка <расческой>          - нажмите клавишу 2\n");
	printf("      Сортировка <слиянием >          - нажмите клавишу 3\n");
	printf("      Поразрядная сортировка          - нажмите клавишу 4\n\n ");
	printf("Тип сортировки: ");
	scanf(" %d", &j);
	if (j == 1 || j == 2 || j == 3) {
		double* array = (double*)malloc(kol * sizeof(double));
		for (int i = 0; i < kol; i++)
			array[i] = rand() % 10000 + 1; 
		putchar('\n');


		printf("\n");
		if (j == 1)
			insertionSortExp(array, kol);

		if (j == 2)
			comb_sortExp(array, kol);


		if (j == 3)
			umsortExp(array, kol);
    }
	if (j == 4){
		int* array = (int*)malloc(kol * sizeof(int));
		int* arrayk = (int*)malloc(kol * sizeof(int));
		
		for (int i = 0; i < kol; i++)
			array[i] = rand() % 10000 + 1;
		putchar('\n');

		int pers[1] = { 0 };
		int srvs[1] = { 0 };
		signedRadixSortExp(array, arrayk, kol, pers, srvs);

		printf("\n\n");
		printf(" Количество перестановок : %d\n\n\n", pers[0]);
	}
}






int main()
{
	setlocale(LC_ALL, "Rus");
	int  a;
	int kol;

	
	printf("\t\t|---------------------------------------| \n");
	printf("\t\t| Программа для сортировки набора чисел |\n");
	printf("\t\t|---------------------------------------| \n\n");

	printf(" Выберите тип сортировки для Вашего набора чисел :\n");
	printf("      Сортировка <вставкой>           - нажмите 1 \n");
	printf("      Сортировка <расчекой>           - нажмите клавишу 2\n");
	printf("      Сортировка <сляинием >          - нажмите клавишу 3\n");
	printf("      <Поразрядная> сортировка        - нажмите клавишу 4\n");
	printf("      Экспериентальная сортировка     - нажмите клавишу 6\n\n");
	printf(" Тип сортировки: ");
	scanf(" %d", &a);

	if (a == 1 || a == 2  ||  a == 3) {
		printf("\n");
		printf(" Введите количество чисел, которые следует отсортировать и нажмите Enter : \n ");
		printf("Количество чисел: ");
		scanf("%d", &kol);
		double* array = (double*)malloc(kol * sizeof(double));
		double* check = (double*)malloc(kol * sizeof(double));

		printf("\n");

		printf(" Введите числа, которые следует отсортировать , через пробел. После того как ввели все числа нажмите Enter: ");
		for (int i = 0; i < kol; i++)
			scanf("%lf", &array[i]);
		
		for (int i = 0; i < kol; i++)
			check[i] = array[i];

		if (a == 1) 
			insertionSort(array, kol, check);

		if (a == 2) 
			comb_sort(array, kol, check);
		

		if (a == 3) 
			umsort(array, kol, check);
		

	}

	if(a==4) {
		int vib = 0;
		printf("\n");
		printf(" Введите количество чисел, которые следует отсортировать и нажмите Enter : \n");
		printf(" Количество чисел: ");
		scanf("%d", &kol);
		int* array = (int*)malloc(kol * sizeof(int));
		int* arrayk = (int*)malloc(kol * sizeof(int));
		int* check = (int*)malloc(kol * sizeof(int));

		printf("\n");

		printf(" Введите целые числа, которые следует отсортировать , через пробел\n");
		printf(" После того как ввели все числа нажмите Enter: ");
		for (int i = 0; i < kol; i++)
			scanf("%d", &array[i]);

		for (int i = 0; i < kol; i++)
			check[i] = array[i];

		int pers[1] = { 0 };
		int srvs[1] = { 0 };
		signedRadixSort(array, arrayk, kol, pers, srvs);

		printf("--------------------------------------------------------------------------------\n");
		printf(" Отсортированная последовательность:\n\n");
		printf(" ");

		int j = 0;
		while (array[j] >= 0 && j < kol)
			j++;

		if (j != 0) {
			int i = 0;
			for (int l = kol - 1; l >= j; l--)
				printf("%d ", array[l]);
			for (int i = 0; i < j; i++)
				printf("%d ", array[i]);
		}
		else {
			for (int i = 0; i < kol; i++)
				printf("%d", array[i]);
		}

		printf("\n\n");
		printf(" Количество перестановок : %d\n", pers[0]);
		printf("--------------------------------------------------------------------------------\n\n");


		
		printf(" Хотите проверить корректность выполнения программы?\n\n");
		printf(" Да - введите 1 и нажите Enter\n");
		printf(" Нет - введите 2  и нажмите Enter\n\n");
		printf(" ");
		scanf(" %d", &vib);
		if (vib == 1) {
			printf("\n\n");
			CheckSortI(check, kol);
		}
		free(check);
	}
	if (a == 6) {
		Experiment();
	}
}
