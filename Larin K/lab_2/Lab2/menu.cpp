#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include "menu.h"
#include "linear_equations.h"
#include "matrix.h"
#include "vector.h"
#include "rational.h"
#include "BigInt.h"

using namespace std;
using namespace lab;

using rational = Rational<BigInt>;

namespace
{
	template <typename T>
	static void printEquationsSystem(const Matrix<T>& m)
	{
		const int limitDigit = 10;

		if (m.size().first == 0 || m.size().second == 0) {
			return;
		}

		for (size_t i = 0; i < m.size().first && i < limitDigit; i++)
		{
			for (size_t j = 0; j < m.size().second - 1 && j < limitDigit; j++)
			{
				if (j > 0) {
					cout << "+ ";
				}

				if (is_same_v<T, rational>) {
					cout << '(';
				}
				cout << m[i][j];
				if (is_same_v<T, rational>) {
					cout << ')';
				}
				cout << "*x" << j + 1 << ' ';
			}

			if (m.size().second > limitDigit + 1) {
				cout << "... ";
			}

			cout << "= " << m[i].back() << '\n';
		}

		if (m.size().first > limitDigit) {
			cout << "...........\n";
		}
	}

	template <typename T>
	void createMatrixMenu(Matrix<T>& matrix)
	{
		system("cls");

		size_t h, w;

		cout << "\tcreate matrix menu\n\n";
		cout << "enter a positive integer number of equations\n";
		cout << "number of equations: ";
		cin >> h;
		cout << "enter a positive integer number of variables\n";
		cout << "number of variables: ";
		cin >> w;

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		matrix.clear();
		matrix.resize(h, w + 1);
	}

	template <typename T>
	void createRandomMatrix(Matrix<T>& matrix)
	{
		double minValue, maxValue;
		cout << "enter minimum and maximum of random values\n";
		cout << "minimum value: ";
		cin >> minValue;
		cout << "maximum value: ";
		cin >> maxValue;

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		if (minValue > maxValue) {
			std::swap(minValue, maxValue);
		}

		static mt19937_64 _rand{ (random_device{})() };
		uniform_real_distribution<double> distr(minValue, maxValue);

		for (size_t i = 0; i < matrix.size().first; i++)
		{
			for (size_t j = 0; j < matrix.size().second; j++)
			{
				if constexpr (!is_same_v<T, rational>) {
					matrix[i][j] = T(distr(_rand));
				}
				else {
					matrix[i][j] = rational(int64_t(distr(_rand) * 1e+10), int64_t(1e+10));
				}
			}
		}
	}

	template <typename T>
	void inputMatrixMenu(Matrix<T>& matrix)
	{
		system("cls");

		cout << "\nchose the metod of input matrix\n";
		cout << "1) read from console\n";
		cout << "2) read from file\n";
		cout << "3) fill the matrix with nulls\n";
		cout << "4) fill the matrix with random values\n";
		cout << "5) cancel\n";

		while (true)
		{
			cout << ">> ";
			cout.flush();
			int comand;
			cin >> comand;

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			if (comand == 2) {
				cout << "enter name of file\n>> ";
				cout.flush();

				string fileName;
				getline(cin, fileName);

				ifstream fin(fileName);
				if (!fin.is_open()) {
					cout << "could not open file\n";
					continue;
				}

				for (size_t i = 0; i < matrix.size().first; i++)
				{
					for (size_t j = 0; j < matrix.size().second; j++)
					{
						fin >> matrix[i][j];
					}
				}

				fin.close();
				break;
			}
			else if (comand == 1) {
				cout << "enter the matrix corresponding to the system of equations\n";

				for (size_t i = 0; i < matrix.size().first; i++)
				{
					for (size_t j = 0; j < matrix.size().second; j++)
					{
						cin >> matrix[i][j];
					}
				}

				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				break;
			}
			else if (comand == 3) {
				matrix = Matrix<T>(matrix.size().first, matrix.size().second);
				break;
			}
			else if (comand == 4) {
				createRandomMatrix(matrix);
				break;
			}
			else if (comand == 5) {
				return;
			}
			else {
				cout << "incorrect input\n";
			}
		}
	}

	template <typename T>
	void printSolveResult(Matrix<T>& matrix)
	{
		lab::vector<T> ans;
		eqResults err;

		if constexpr (is_same_v<T, rational>) {
			solveEquationSystem(matrix, ans, err, [](const Matrix<T>& m, size_t colum) {
				for (size_t i = colum; i < m.size().first; i++)
				{
					if (m[i][colum] != 0) return i;
				}
				return colum;
			});
		}
		else {
			solveEquationSystem(matrix, ans, err);
		}

		if (err == eqResults::INCONSISTENT) {
			cout << "the system is inconsistent\n";
		}
		else if (err == eqResults::INF_SOLUTIONS) {
			cout << "infinite number of solutions\n";
		}
		else {
			cout << "solution of the system of equations:\n";
			for (size_t i = 0; i < ans.size(); i++)
			{
				cout << "x" << i + 1 << " = " << ans[i];
				if (i + 1 < ans.size()) {
					cout << ';';
				}
				cout << ' ';
			}
			cout << '\n';
		}

		system("pause");
	}

	template <typename T>
	void printFullMatrixMenu(Matrix<T>& matrix)
	{
		cout << "print menu\n";
		cout << "1) print to console\n";
		cout << "2) print to file\n";
		cout << "3) cancel\n";

		while (true)
		{
			cout << ">> ";
			int comand;
			cin >> comand;

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			if (comand == 1) {
				for (size_t i = 0; i < matrix.size().first; i++)
				{
					for (size_t j = 0; j < matrix.size().second; j++)
					{
						cout << matrix[i][j] << "  ";
					}
					cout << '\n';
				}

				system("pause");
				break;
			}
			else if (comand == 2) {
				cout << "enter name of file\n>> ";
				cout.flush();

				string fileName;
				cin.ignore();
				getline(cin, fileName);

				ofstream fout(fileName);
				if (!fout.is_open()) {
					cout << "could not open file\n";
					continue;
				}

				for (size_t i = 0; i < matrix.size().first; i++)
				{
					for (size_t j = 0; j < matrix.size().second; j++)
					{
						fout << matrix[i][j] << "  ";
					}
					fout << '\n';
				}

				fout.close();
				break;
			}
			else if (comand == 3) {
				break;
			}
			else {
				cout << "incorrect input\n";
			}
		}
	}



	template <typename T>
	void inputElementMenu(Matrix<T>& matrix)
	{
		cout << "enter indexes of modify element\n";
		while (true)
		{
			size_t i, j;
			cin >> i >> j;

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			if (i > matrix.size().first || j > matrix.size().second || i == 0 || j == 0) {
				cout << "incorrect indexes\n";
			}
			else {
				cout << "input new value of element (" << i << ", " << j << "):\n>> ";
				cin >> matrix[i - 1][j - 1];
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				break;
			}
		}
	}

	template <typename T>
	bool _menu()
	{
		bool printMatrixType = true;
		Matrix<T> matrix;
		createMatrixMenu(matrix);
		inputMatrixMenu(matrix);

		while (true)
		{
			system("cls");

			cout << "system of linear equations of ";
			if (is_same<T, double>::value) {
				cout << "real ";
			}
			else if (is_same<T, rational>::value) {
				cout << "rational ";
			}

			if (matrix.size().second == 0) {
				cout << "0 x 0\n";
			}
			else {
				cout << ' ' << matrix.size().first << " x " << matrix.size().second - 1 << '\n';
			}

			if (printMatrixType) {
				cout << '\n';
				printEquationsSystem(matrix);
			}

			cout << "\n\tMain menu\n";
			cout << "1) create new matrix\n";
			cout << "2) reset matrix\n";
			cout << "3) set matrix element\n";
			cout << "4) run Gauss algorithm\n";
			cout << "5) solve a system of linear equations\n";
			cout << "6) print full matrix\n";
			cout << "7) " << (printMatrixType ? "stop" : "start") << " print matrix\n";
			cout << "8) delete matrix\n";
			cout << "9) exit\n";
			cout << ">> ";
			cout.flush();

			int comand;
			cin >> comand;

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			switch (comand)
			{
			case 1:
				return true;
			case 2:
				inputMatrixMenu(matrix);
				break;
			case 3:
				inputElementMenu(matrix);
				break;
			case 4:
				matrix.gauss();
				break;
			case 5:
				printSolveResult(matrix);
				break;
			case 6:
				printFullMatrixMenu(matrix);
				break;
			case 7:
				printMatrixType = !printMatrixType;
				break;
			case 8:
				return false;
			case 9:
				exit(0);
			default:
				cout << "incorrect input\n";
				system("pause");
			}
		}
	}

	void switchType()
	{
		bool cycleFlag = true;
		while (cycleFlag)
		{
			system("cls");

			cout << "\tcreate matrix menu\n";
			cout << "choose matrix type:\n";
			cout << "1) real\n";
			cout << "2) rational\n";
			cout << "3) cancel\n";
			cout << ">> ";
			cout.flush();

			int comand;
			cin >> comand;

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			switch (comand)
			{
			case 1:
				cycleFlag = _menu<double>();
				break;
			case 2:
				cycleFlag = _menu<rational>();
				break;
			case 3:
				return;
			default:
				cout << "incorrect input\n";
				system("pause");
			}
		}
	}
}


void menu()
{
	while (true)
	{
		system("cls");
		cout << "matrix not created\n";

		cout << "\n\tMain menu\n";
		cout << "1) create new matrix\n";
		cout << "2) exit\n";
		cout << ">> ";
		cout.flush();

		int comand;
		cin >> comand;

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		switch (comand)
		{
		case 1:
			switchType();
			break;
		case 2:
			exit(0);
		default:
			cout << "incorrect input\n";
			system("pause");
		}
	}
}

