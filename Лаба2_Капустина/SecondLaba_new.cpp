/* Необходимо реализовать метод Гаусса для действительной квадратной матрицы с выбором ведущего элемента
Необходимо реализовать шаблонный класс вектор
Необходимо реализовать класс квадратная матрица, которая является шаблоном класса вектор от вектора
Необходимо реализовать класс СЛАУ, который является наследником(вместо наследования можно сделать включение)
квадратной матрицы и у него есть метод Гаусса.Метод Гаусса принимает правую часть в качестве аргумента и
возвращает ответ в виде вектора
Для удобства можно реализовать функцию swap, которая меняет строки и элементы местами
Срок выполнения до 8 мая.По итогам проверяется код программы через систему github и отчет
*/
#include <iostream>
#include "ClassVector.h"
#include "Matrix.h"
#include <stdio.h>      
#include <time.h>


int main() {
	int N;
	int k;
	cout << "Enter the number N, the dimension of a square matrix: ";
	cin >> N;
	cout << endl;
	Vector<double> stroka(N + 1);
	Matrix <double>(N, stroka);
	Gauss<double> systema(N, stroka);
	Vector<double> otvet(N);
	cout << "Press 1 if you want to enter the matrix manually." << endl;
	cout << "Press 2 if you want to fill the matrix with random numbers" << endl;
	cin >> k;
	if (k == 1)
	{
		cout << "Enter systems of linear equations: " << endl;
		cin >> systema;
	}
	if (k == 2)
	{
		systema.random();
		cout << systema;
	}
	int f = 0;
	otvet = systema.Otvet(f);
	cout << "Decision vector: " << endl;
	cout << otvet;
	cout << "Triangular system: " << endl;
	cout << systema;

	error(f);

	return (0);
}


