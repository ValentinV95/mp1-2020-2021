#include<stdlib.h>

unsigned long long perestanovki;
unsigned long long sravnenia;

int partition(float* a, int l, int r)
{
	float o = a[r];
	int position = r;
	while (l < r)
	{
		while (a[l] < o)
		{
			l++;
			sravnenia++;
		}
		while (a[r] >= o)
		{
			r--;
			sravnenia++;
		}
		sravnenia+=2;
		if (l >= r)
			break;
		float tmb = a[l];
		a[l] = a[r];
		a[r] = tmb;
		perestanovki += 2;
		
	}
	float t = a[l];
	a[l] = o;
	a[position] = t;
	perestanovki+=2;
	return l;
}

void sortxoar(float* a, int l, int r)
{
	if (l < r)
	{
		sravnenia++;
		int p = partition(a, l, r);
		sortxoar(a, l, p - 1);
		sortxoar(a, p + 1, r);
	}
}

void mergesort(float* a, float* b, int l, int r)
{
	if (l < r)
	{
		int mid = (l + r) / 2;
		mergesort(a, b, l, mid);
		mergesort(a, b, mid + 1, r);
		int leftindex = l;
		int rightindex = mid + 1;
		int i = l;
		while (leftindex <= mid && rightindex <= r)
		{
			if (a[leftindex] <= a[rightindex])
			{
				b[i] = a[leftindex];
				leftindex++;
			}
			else
			{
				b[i] = a[rightindex];
				rightindex++;
			}
			i++;
			sravnenia+=2;
			perestanovki++;
		}
		for (int j = leftindex; j <= mid; j++)
		{
			b[i] = a[j];
			i++;
			perestanovki++;
			sravnenia++;
		}
		for (int j = rightindex; j <= r; j++)
		{
			sravnenia++;
			b[i] = a[j];
			i++;
			perestanovki++;
		}
		for (int j = l; j <= r; j++)
		{
			sravnenia++;
			a[j] = b[j];
			perestanovki++;
		}
	}
}

void sortvibor(float* a,int N)
{

	for (int i = 0; i < N-1; i++)
	{
		float min = a[i];
		int position = i;
		for (int j = i; j < N; j++)
		{
			if (a[j] < min)
			{
				min = a[j];
				position = j;
			}
			sravnenia+=2;
		}
		float t = a[i];
		a[i] = min;
		a[position] = t;
		perestanovki+=2;
		sravnenia++;
	}

}

void radixsort(float* a, int N)
{
	int sizeofbyte = 256;
	int counts[sizeof(float)][256];
	float* temp;
	float* b;

	for (int i = 0; i < sizeof(float); i++)
	{
		for (int j = 0; j < 256; j++)
		{
			counts[i][j] = 0;
			
		}
	}
	sravnenia = 256 * sizeof(float);

	for (int byte = 0; byte < sizeof(float); byte++)
	{
		for (int i = 0; i < N; i++)
		{
			int value = ((unsigned char*)(a+i))[byte];
			counts[byte][value]++;
			sravnenia++;
		}
		sravnenia++;
	}

	for (int byte = 0; byte < sizeof(float); byte++)
	{
		int sum = 0;
		for (int i = 0; i < sizeofbyte; i++)
		{
			sum += counts[byte][i];
			counts[byte][i] = sum - counts[byte][i];
			sravnenia++;
		}
		sravnenia++;
	}

	temp = a;
	if (NULL == (b = (float*)malloc(sizeof(float) * N)))
	{
		exit(-1);
	}

	for (int byte = 0; byte < sizeof(float); byte++)
	{
		for (int i = 0; i < N; i++)
		{
			int value = ((unsigned char*)(temp+i))[byte];

			b[counts[byte][value]] = temp[i];
			counts[byte][value]++;

			perestanovki++;
			sravnenia++;
		}
		sravnenia++;
		float* t = b;
		b = temp;
		temp = t;
		
	}

	int amountofpositive = 0;
	while (a[amountofpositive] > 0 && amountofpositive < N)
	{
		amountofpositive++;
		sravnenia++;
	}
	int i, j;

	for (i = 0; i < (amountofpositive / 2); i++)
	{
		j = amountofpositive - i - 1;
		float t = a[i];
		a[i] = a[j];
		a[j] = t;
		perestanovki += 2;
		sravnenia++;
	}

	i = j = 0;
	for (i = 0; i < (N / 2); i++)
	{
		j = N - i - 1;
		float t = a[i];
		a[i] = a[j];
		a[j] = t;
		perestanovki += 2;
		sravnenia++;
	}

	free(b);
}

void sortbubble(float *a,int N)
{
	for (int i = 0; i < N; i++)
	{
		int flag = 1;
		for (int j = 0; j < N - i - 1; j++)
		{
			if (a[j + 1] < a[j])
			{
				float t = a[j + 1];
				a[j + 1]=a[j];
				a[j] = t;
				flag = 0;
			}
		}
		if (flag)
			break;
	}
}

/*struct cell
{
	float valueue;
	cell* next;
}base;

void addcell(cell* spisok, float value)
{
	while (spisok->next != NULL)
		spisok = spisok->next;
	spisok->next = (cell*)malloc(sizeof(cell));
	cell newcell=*spisok->next;
	newcell.valueue = value;
}

void fromcelltoarray(float* a, cell* count, int N)
{
	cell* spisok;
	int i = 0;
	for (int j = 0; j < N && i < N; j++)
	{
		int f = 0;
		spisok = count[j].next;
		while (spisok->next != NULL)
		{
			spisok = spisok->next;
			a[i] = spisok->valueue;
			i++;
		}

	}
}

void countingsort(float* array, char byte, int N)
{
	cell count[256];
	base.valueue = 1;
	for (int i = 0; i < 256; i++)
	{
		count[i].next = &base;
		count[i].valueue = 0;
	}
	unsigned char* a = (unsigned char*)array;
	for (int i = 0; i < N; i++)
	{
		addcell(count[a[4 * i + byte]].next,array[i]);
	}
	fromcelltoarray(a, count,N);
}*/

