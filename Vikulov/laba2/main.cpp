#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <locale.h>
#include <cstdlib>
#include <ctime>
#include "VectorsMatrixGauss.h"


typedef unsigned int uint;
using namespace std;


template<typename T>
bool checking(Vector<T>& correct_y, Vector<T>& our_answer) {
	double eps = 10e-9;
	for (int i = 0; i < correct_y.Get_size(); i++)
		if (abs(correct_y.coords[i] - our_answer.coords[i]) > eps)
			return false;
	return true;
}

int main() {
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	uint dim;
	short int key;
	const double eps = 10e-9;
	cout << "Введите кол-во переменных = кол-ву уравнений: ";
	cin >> dim;
	Vector <double> b(dim);

	// Создал копию вектора-столбца свободных членов для проверки на корректность в дальнейшем
	Vector <double> copy(dim);
	Matrix <double> A(dim);
	cout << "Ввод матрицы коэффициентов матрицы А" << endl;
	cout << "1 - заполнение с клавиатуры" << endl;
	cout << "2 - матрица из случайных чисел" << endl;
	cout << "Введите опцию: " << endl;
	cin >> key;

	if (key == 1)
		cin >> A;
	else if (key == 2)
		A.generate_random_matrix();
	else {
		cout << "Неопределенная опция!" << endl;
		exit(-10);
	}

	cout << "Ввод столбца свободных членов b" << endl;
	cout << "1 - заполнение с клавиатуры" << endl;
	cout << "2 - столбец из случайных чисел" << endl;
	cin >> key;
	if (key == 1)
		cin >> b;
	else if (key == 2)
		b.generate_random_vector();
	else {
		cout << "Неопределенная опция!" << endl;
		exit(-11);
	}

	copy = b;
	cout << endl;
	GaussMethod<double> system(A);
	cout << "Система уравнений: " << endl;
	system.display_system(b);
	cout << endl;

	cout << "Столбец решения системы уравнений:" << endl;
	system.Solve(b);
	cout << b << endl;
	b = A * b;
	
	// Первый вариант проверки на корректность
	/*if (copy.Is_equal(b))
		cout << "Система уравнений решена верно!" << endl;
	else
		cout << "Система решена неверно!" << endl;
		*/


	// Обновлённая проверка на корректность
	if (checking(copy, b))
		cout << "Система уравнений решена верно!" << endl;
	else
		cout << "Система решена неверно!" << endl;
		
	cout << "Погрешность = " << eps << endl;
	return 0;
}