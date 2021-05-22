#include <iostream>
#include <ctime>
#include <iomanip>
#include "matrix.h"

using namespace std;

void Check()
{
	int u_size;

	cout << "    Enter the number of unknowns: ";
	cin >> u_size;
	cout << "\n\n\n";

	Matrix<double> b(u_size, u_size + 1, 1);
	Vector<double> X(u_size, 0);

	b.RandomElements();
	cout << "    The original system of linear equations\n\n";
	b.LinearSystem();

	cout << "\n\n\n";

	b.GaussMethod(X);
	cout << "    The system of linear equations in the reduced form\n\n";
	b.LinearSystem();

	cout << "\n\n\n      Linear equation system solution: \n\n";

	for (size_t i = 0; i < u_size; i++)
	{
		cout << "X" << i + 1 << "\t=\t" << X[i] << endl;
	}

	Vector<double> k(u_size, 0);

	cout << "\n\n    Substitute the resulting values into the original system\n\n";

	for (size_t i = 0; i < u_size; i++)
	{
		for (int j = 0; j < u_size; j++)
		{
			k[i] += b[i][j] * X[j];
		}
	}

	for (size_t i = 0; i < u_size; i++)
	{
		cout << k[i] << "  =  " << b[i][u_size] << endl;
	}
}

void RandomNumberGauss()
{
	int u_size;

	cout << "    Enter the number of unknowns: ";
	cin >> u_size;
	cout << "\n\n\n";

	Matrix<double> b(u_size, u_size + 1, 1);
	Vector<double> X(u_size, 0);

	b.RandomElements();
	cout << "    The original system of linear equations\n\n";
	b.LinearSystem();

	cout << "\n\n\n";

	b.GaussMethod(X);

	cout << "    The system of linear equations in the reduced form\n\n";
	b.LinearSystem();


	cout << "\n\n\n      Linear equation system solution: \n\n";

	for (size_t i = 0; i < u_size; i++)
	{
		cout << "X" << i + 1 << "\t=\t" << X[i] << endl;
	}
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

void userValues()
{
	size_t u_size;

	cout << "    Enter the number of unknowns: ";
	cin >> u_size;



	Matrix<double> b(u_size, u_size + 1, 1);
	Vector<double> X(u_size, 0);

	for (size_t i = 0; i < b.getSize(); i++)
	{
		cout << "\n    Enter the coefficients of the unknowns in the " << i + 1 << " line separated by a space \n";
		cout << "    After entering the items, press the Enter\n\n";

		for (int j = 0; j < b.getSize(); j++)
		{
			cin >> b[i][j];
		}

		cout << "\n    Enter the value of the intercept on line " << i + 1 << endl;
		cout << "    After entering the items, press the Enter\n\n";
		cin >> b[i][b.getSize()];
	}

	cout << endl;


	cout << "     The original system of linear equations\n\n";
	b.LinearSystem();

	cout << "\n\n\n";

	b.GaussMethod(X);
	b.Alignment();


	cout << "     The system of linear equations in the reduced form\n\n";
	b.LinearSystem();

	cout << "\n\n\n    Linear equation system solution: \n\n";

	for (size_t i = 0; i < u_size; i++)
	{
		cout << "X" << i + 1 << "\t=\t" << X[i] << endl;
	}
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}


void logic()
{
	int a;

	cout << " 1. Apply Gaussian method for a matrix with random numbers\n";
	cout << " 2. Apply Gaussian method for matrix with custom numbers\n";
	cout << " 3. Check if the Gaussian method is working correctly\n\n";


	cout << "    Select the appropriate option, enter the number and press enter... ";
	cin >> a;
	cout << "\n\n";

	switch (a)
	{
	case 1:
		RandomNumberGauss();
		break;

	case 2:
		userValues();
		break;

	case 3:
		Check();
		break;
	default:
		cout << "    Unfortunately this command does not exist!\n";
		cout << "    Please, choose another option from the list below:\n\n";
		logic();

	}

}
