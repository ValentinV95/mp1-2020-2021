// ConsoleApplication5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <stdio.h>
#include <stdlib.h>

void swap(double arr[], int i, int j)
{
    double c;
    c = arr[i];
    arr[i] = arr[j];
    arr[j] = c;
}

int part(double arr[], int l, int r)
{
    double v = arr[(l + r) / 2];
    int i = l;
    int j = r;
    while (i <= j)
    {
        while (arr[i] < v)
            i++;
        while (arr[j] > v)
            j--;
        if (i >= j)
            break;
        swap(arr, i, j);
        i++;
        j--;

    }
    return j;
}

void quicksort(double arr[], int l, int r)
{
    if (l < r)
    {
        int q = part(arr, l, r);
        quicksort(arr, l, q);
        quicksort(arr, q + 1, r);
    }
}

int main()
{
    srand(60);
    double mas[100]{ 0 };
    int n;
    scanf_s("%d", &n);
    for (int i = 0; i < n; i++)
    {
        mas[i] = (double)(rand() % 5100)/100;
    }
    for (int i = 0; i < n; i++)
    {
        printf("%lf ", mas[i]);
    }
    printf("\n");

    quicksort(mas, 0, n - 1);

    for (int i = 0; i < n; i++)
    {
        printf(" %lf\n", mas[i]);
    }
    int end;
    scanf_s("%d", &end);
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
