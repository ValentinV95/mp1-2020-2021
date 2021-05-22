#include <iostream>
using namespace std;
#include"matrix_templates.h"
	void main()
{
	setlocale(LC_ALL, "Russian");
	size_t n=0, v=0;
	cout << "Введите размерность квадратной матрицы" << endl; cin >> n;
	cout << "Для того тчобы вручную заполнить матрицу нажмите 1" << endl << "Для того чтобы заполнить мтарицу случайными числами типа double нажмите 2 " << endl << "Для того чтобы заполнить мтарицу случайными числами типа int нажмите 3" << endl;
	cin >> v;
	switch (v)
	{
	case(1): {matrix<double> test(n); test.fill_manually(); cout << "Ваша матрица:" << endl; test.printm(); test.J_G(); test.printAnswer(); break; }
	case(2): {matrix<double> test(n); test.fill_randomly(); cout << "Ваша матрица:" << endl; test.printm(); test.J_G(); test.printAnswer(); break; }
	case(3): {matrix<int> test(n); test.fill_randomly(); cout << "Ваша матрица:" << endl; test.printm(); test.J_G(); test.printAnswer(); break; }
	}
}
