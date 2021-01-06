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
	printf(" Îòñîðòèðîâàííûé ìàññèâ äîëæåí èìåòü ñëåäóþùèé âèä : \n\n");
	for (int j = 0; j < M; j++)
		printf("   %lf ", arr[j]);
	printf("\n\n");
	printf("--------------------------------------------------------------------------------\n\n");

}

void CheckSortI(double* arr, int M) {
	for (int j = 0; j < M - 1; j++)
		for (int v = M - 2; v > j - 1; v--)
			if (arr[v] > arr[v + 1]) {
				double tmp = arr[v];
				arr[v] = arr[v + 1];
				arr[v + 1] = tmp;
			}
	printf("--------------------------------------------------------------------------------\n\n");
	printf(" Îòñîðòèðîâàííûé ìàññèâ äîëæåí èìåòü ñëåäóþùèé âèä : \n\n");
	for (int j = 0; j < M; j++)
		printf("   %lf  ", arr[j]);
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
	printf(" Îòñîðòèðîâàííàÿ ïîñëåäîâàòåëüíîñòü:\n\n");
	printf(" ");
	for (int i = 0; i < size; i++)
		printf(" %.6lf ", arr[i]);

	printf("\n\n\n\n");

	printf(" Êîëè÷åñòâî ïåðåñòàíîâîê : %d\n", per);
	printf(" Êîëè÷åñòâî ñðàâíåíèé : %d \n\n\n", srv);
	printf("--------------------------------------------------------------------------------\n\n");
	free(arr);
	printf(" Õîòèòå ïðîâåðèòü êîððåêòíîñòü âûïîëíåíèÿ ïðîãðàììû?\n\n");
	printf(" Äà - ââåäèòå 1 è íàæèòå Enter\n");
	printf(" Íåò - ââåäèòå 2  è íàæìèòå Enter\n\n");
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
	printf(" Îòñîðòèðîâàííàÿ ïîñëåäîâàòåëüíîñòü:\n\n");
	printf(" ");
	for (int i = 0; i < size; i++)
		printf(" %lf ",  arr[i]);

	printf("\n\n\n\n");

	printf(" Êîëè÷åñòâî ïåðåñòàíîâîê : %d\n", per);
	printf(" Êîëè÷åñòâî ñðàâíåíèé : %d \n\n\n", srv);
	printf("--------------------------------------------------------------------------------\n\n");

	free(arr);
	printf(" Õîòèòå ïðîâåðèòü êîððåêòíîñòü âûïîëíåíèÿ ïðîãðàììû?\n\n");
	printf(" Äà - ââåäèòå 1 è íàæèòå Enter\n");
	printf(" Íåò - ââåäèòå 2  è íàæìèòå Enter\n\n");
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
	printf(" Îòñîðòèðîâàííàÿ ïîñëåäîâàòåëüíîñòü:\n\n");
	printf(" ");
	for (int m = 0; m < n; m++)
		printf("%lf ", a[m]);

	printf("\n\n\n\n");

	printf(" Êîëè÷åñòâî ïåðåñòàíîâîê ìåæäó ìàññèâàìè  %d \n", pers[0]);
	printf(" Êîëè÷åñòâî ñðàâíåíèé ýëåìåíòîâ ìàññèâà %d \n\n\n", srvs[0]);
	printf("--------------------------------------------------------------------------------\n\n");

	free(t);
	printf(" Õîòèòå ïðîâåðèòü êîððåêòíîñòü âûïîëíåíèÿ ïðîãðàììû?\n\n");
	printf(" Äà - ââåäèòå 1 è íàæèòå Enter\n");
	printf(" Íåò - ââåäèòå 2  è íàæìèòå Enter\n\n");
	printf(" ");
	scanf(" %d", &vib);
	if (vib == 1) {
		printf("\n\n");
		CheckSortD(ch, n);
	}
	free(ch);
}

void create_counters(double* data, long* counters, long N)
{

	unsigned char* bp = (unsigned char*)data;

	unsigned char* dataEnd = (unsigned char*)(data + N);
	unsigned short i;
	for (int i = 0; i < 256 * sizeof(double); i++)
		counters[i] = 0;

	while (bp != dataEnd)
	{
		for (i = 0; i < sizeof(double); i++)
			counters[256 * i + *(bp++)]++;
	}

}

void radix_pass(short Offset, long N, double* source, double* dest, long* count, int *per)
{
	double* sp;
	long s = 0, d, i, * cp = count;
	unsigned char* bp;

	for (i = 256; i > 0; i--, ++cp)
    {
		d = *cp; *cp = s; s += d;
	}

	bp = (unsigned char*)source + Offset;
	sp = source;
	for (i = N; i > 0; --i, bp += sizeof(double), ++sp)
	{
		cp = count + *bp; dest[*cp] = *sp; (*cp)++;  per[0] = per[0] + 1;
	}
	cp += N;
}

void radix_sort(double* in, double* out, long* counters, long N, int *pe)
{

	long* count;
	unsigned short i;
	int k = 0;
	create_counters(in, counters, N);

	for (i = 0; i < sizeof(double); i++)
	{
		count = counters + 256 * i;
		radix_pass(i, N, in, out, count, pe);
		for (long j = 0; j < N; j++){
			in[j] = out[j];
			pe[0] = pe[0] + 1;
		}	
	}
	while (in[k] >= 0 && k < N)
		k++;
	for (int i = 0; i < N - k; i++)
	{
		in[i] = out[N - 1 - i];
	}
	for (int i = 0; i < k; i++)
	{
		in[N - k + i] = out[i];
	}
	free(out);
	//free(counters);
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

	printf(" Êîëè÷åñòâî ïåðåñòàíîâîê : %d\n", per);
	printf(" Êîëè÷åñòâî ñðàâíåíèé : %d \n\n\n", srv);
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

	printf(" Êîëè÷åñòâî ïåðåñòàíîâîê : %d\n", per);
	printf(" Êîëè÷åñòâî ñðàâíåíèé : %d \n\n\n", srv);

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

	printf(" Êîëè÷åñòâî ïåðåñòàíîâîê ìåæäó ìàññèâàìè  %d \n", pers[0]);
	printf(" Êîëè÷åñòâî ñðàâíåíèé ýëåìåíòîâ ìàññèâà %d \n\n\n", srvs[0]);

	free(t);
}


void create_countersExp(double* data, long* counters, long N)
{

	unsigned char* bp = (unsigned char*)data;

	unsigned char* dataEnd = (unsigned char*)(data + N);
	unsigned short i;
	for (int i = 0; i < 256 * sizeof(double); i++)
		counters[i] = 0;

	while (bp != dataEnd)
	{
		for (i = 0; i < sizeof(double); i++)
			counters[256 * i + *(bp++)]++;
	}

}

void radix_passExp(short Offset, long N, double* source, double* dest, long* count, int *per)
{
	double* sp;
	long s = 0, d, i, * cp = count;
	unsigned char* bp;

	for (i = 256; i > 0; i--, ++cp)
    {
		d = *cp; *cp = s; s += d;
	}

	bp = (unsigned char*)source + Offset;
	sp = source;
	for (i = N; i > 0; --i, bp += sizeof(double), ++sp)
	{
		cp = count + *bp; dest[*cp] = *sp; (*cp)++;  per[0] = per[0] + 1;
	}
	cp += N;
}

void radix_sortExp(double* in, double* out, long* counters, long N, int *pe)
{

	long* count;
	unsigned short i;
	int k = 0;
	create_countersExp(in, counters, N);

	for (i = 0; i < sizeof(double); i++)
	{
		count = counters + 256 * i;
		radix_passExp(i, N, in, out, count, pe);
		for (long j = 0; j < N; j++){
			in[j] = out[j];
			pe[0] = pe[0] + 1;
		}	
	}
	while (in[k] >= 0 && k < N)
		k++;
	for (int i = 0; i < N - k; i++)
	{
		in[i] = out[N - 1 - i];
	}
	for (int i = 0; i < k; i++)
	{
		in[N - k + i] = out[i];
	}
	
	printf("\n\n");

	printf(" Êîëè÷åñòâî ïåðåñòàíîâîê ìåæäó ìàññèâàìè  %d \n", pers[0]);
	
	free(out);
	//free(counters);
}


void Experiment() {
	int j;
	int kol;
	printf("\n");
	printf(" Ââåäèòå ÷èñëî, êîòîðîå ñîîòâåòñòâóåò äëèíå ñîçäàâàåìîãî ìàññèâà ");
	scanf("%d", &kol);
	printf("\n");

	printf(" Âûáåðèòå òèï ñîðòèðîâêè äëÿ Âàøåãî ýêñïåðèìåíòà :\n");
	printf("      Ñîðòèðîâêà <âñòàâêîé>           - íàæìèòå 1 \n");
	printf("      Ñîðòèðîâêà <ðàñ÷åñêîé>          - íàæìèòå êëàâèøó 2\n");
	printf("      Ñîðòèðîâêà <ñëèÿíèåì >          - íàæìèòå êëàâèøó 3\n");
	printf("      Ïîðàçðÿäíàÿ ñîðòèðîâêà          - íàæìèòå êëàâèøó 4\n\n ");
	printf("Òèï ñîðòèðîâêè: ");
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
		double* arrayk = (double*)malloc(kol * sizeof(double));

		for (int i = 0; i < kol; i++)
			array[i] = rand() % 10000 + 1;
		putchar('\n');

		int pers[1] = { 0 };
		radix_passExp(array, arrayk, kol, pers);

		printf("\n\n");
		printf(" Êîëè÷åñòâî ïåðåñòàíîâîê : %d\n\n\n", pers[0]);
	}
}






int main()
{
	setlocale(LC_ALL, "Rus");
	int  a;
	int kol;


	printf("\t\t|---------------------------------------| \n");
	printf("\t\t| Ïðîãðàììà äëÿ ñîðòèðîâêè íàáîðà ÷èñåë |\n");
	printf("\t\t|---------------------------------------| \n\n");

	printf(" Âûáåðèòå òèï ñîðòèðîâêè äëÿ Âàøåãî íàáîðà ÷èñåë :\n");
	printf("      Ñîðòèðîâêà <âñòàâêîé>           - íàæìèòå 1 \n");
	printf("      Ñîðòèðîâêà <ðàñ÷åêîé>           - íàæìèòå êëàâèøó 2\n");
	printf("      Ñîðòèðîâêà <ñëÿèíèåì >          - íàæìèòå êëàâèøó 3\n");
	printf("      <Ïîðàçðÿäíàÿ> ñîðòèðîâêà        - íàæìèòå êëàâèøó 4\n");
	printf("      Ýêñïåðèåíòàëüíàÿ ñîðòèðîâêà     - íàæìèòå êëàâèøó 6\n\n");
	printf(" Òèï ñîðòèðîâêè: ");
	scanf(" %d", &a);

	if (a == 1 || a == 2  ||  a == 3) {
		printf("\n");
		printf(" Ââåäèòå êîëè÷åñòâî ÷èñåë, êîòîðûå ñëåäóåò îòñîðòèðîâàòü è íàæìèòå Enter : \n ");
		printf("Êîëè÷åñòâî ÷èñåë: ");
		scanf("%d", &kol);
		double* array = (double*)malloc(kol * sizeof(double));
		double* check = (double*)malloc(kol * sizeof(double));

		printf("\n");

		printf(" Ââåäèòå ÷èñëà, êîòîðûå ñëåäóåò îòñîðòèðîâàòü , ÷åðåç ïðîáåë. Ïîñëå òîãî êàê ââåëè âñå ÷èñëà íàæìèòå Enter: ");
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
		printf(" Ââåäèòå êîëè÷åñòâî ÷èñåë, êîòîðûå ñëåäóåò îòñîðòèðîâàòü è íàæìèòå Enter : \n");
		printf(" Êîëè÷åñòâî ÷èñåë: ");
		scanf("%d", &kol);
		double* array = (double*)malloc(kol * sizeof(double));
		double* arrayk = (double*)malloc(kol * sizeof(double));
		double* check = (double*)malloc(kol * sizeof(double));
        long* counters = (long*)malloc(1024 * sizeof(double));

		printf("\n");

		printf(" Ââåäèòå öåëûå ÷èñëà, êîòîðûå ñëåäóåò îòñîðòèðîâàòü , ÷åðåç ïðîáåë\n");
		printf(" Ïîñëå òîãî êàê ââåëè âñå ÷èñëà íàæìèòå Enter: ");
		for (int i = 0; i < kol; i++)
			scanf("%lf", &array[i]);

		for (int i = 0; i < kol; i++)
		    check[i] = array[i];

		int pers[1] = { 0 };
		radix_sort(array, arrayk, counters,kol, pers);

		printf("--------------------------------------------------------------------------------\n");
		printf(" Îòñîðòèðîâàííàÿ ïîñëåäîâàòåëüíîñòü:\n\n");
		printf(" ");

		//for (int h = 0; h < kol; h++)
		//    printf(" %lf ", array[h]);
	
		//int j = 0;
		//while (j < kol && array[j] >= 0)
			//j++;

		//if (j != 0) {
			//int i = 0;
			//for (int l = kol - 1; l >= j; l--)
				//printf("%lf ", array[l]);
			//for (int i = 0; i < j; i++)
				//printf("%lf ", array[i]);
		//}
		//else {
		//	for (int i = 0; i < kol; i++)
		//		printf("%lf ", array[i]);
		//}

		printf("\n\n");
		printf(" Êîëè÷åñòâî ïåðåñòàíîâîê : %d\n", pers[0]);
		printf("--------------------------------------------------------------------------------\n\n");



		printf(" Õîòèòå ïðîâåðèòü êîððåêòíîñòü âûïîëíåíèÿ ïðîãðàììû?\n\n");
		printf(" Äà - ââåäèòå 1 è íàæèòå Enter\n");
		printf(" Íåò - ââåäèòå 2  è íàæìèòå Enter\n\n");
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



