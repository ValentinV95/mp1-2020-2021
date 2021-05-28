#include <iostream>
#include "clocale"
#include "Vector.h"
#include "reloadedMatrix.h"
#include "Gauss.h"

using namespace std;

int main()
{
	while (true) {
		setlocale(LC_ALL, "Russian");
		int size;
		cout << "Введите размер матрицы:" << endl;
		cin >> size;

		Gauss<double>mainMatrix(size);
		Vector<double>resultMatrix(size);
		
		cout << "Расширенная матрица:" << endl;
		mainMatrix.showSystem();

		//вызов метода Гаусса
		resultMatrix = mainMatrix.gaussMethod();

		//проверка решения с помощью встроенной функции класса Gauss
		mainMatrix.check();
		cout << endl;

		//вывод решения на экран
		cout << "Решение:" << endl;
		resultMatrix.print();

		//Возможность повтора
		int repeatCheck;
		cout << "Если хотите решить еще одну систему то введите 1, если нет, введите 0" << endl;
		cin >> repeatCheck;
		if (repeatCheck == 0){
			delete &mainMatrix;
			delete &resultMatrix;
			break;
		}
		else if (repeatCheck != 1) {
			cout << "Не корректный ввод";
		}
	}
}