#include <iostream>
#include "Vector.h"
#include "Matrix.h"
#include "MethodMan.h"
#include "ctime"
using namespace std;

int main()
{
	srand(time(NULL));
	int size;

	cout << "Input matrix size:" << endl;
	cin >> size;

	Method<double> SysOfLinEq(size);
	Vector<double> solution(size);
	double* element = new double[size];

	SysOfLinEq.InputMat();

	int x = 1;
	int choice;


	for (int i = 0; i < size; i++)
	{
		cout << "\nEnter the " << i + 1 << " element of the vector" << endl;
		cin >> element[i];
	}

	cout << endl << "Original matrix:" << endl;
	SysOfLinEq.s_print(element);

	solution = SysOfLinEq.gauss(element);

	cout << "Triangular matrix:" << endl;
	SysOfLinEq.s_print(element);

	cout << "Solution vector:" << endl;
	solution.print_vector();

	SysOfLinEq.Check(element);

	system("pause");
}