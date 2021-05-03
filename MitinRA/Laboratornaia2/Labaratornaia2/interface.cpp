#pragma once
#include<iostream>
#include"Vector.cpp"
#include"Matrix.cpp"
#include"interface.h"

using namespace std;

void menu()
{
	static bool flag = false;
	srand((unsigned)time(NULL));

	if (!flag)
	{
		cout << "Laboratory work No. 2: the Gauss method\n";
		flag = true;
	}
	
	cout << "Choose what you want to do:\n";
	cout << "1. Solve the system using the Gauss method\n";
	cout << "2. Check the correctness of the program\n";
	cout << "3. Multiply matrix by vector\n";
	cout << "4. Exit\n";

	logic();
}

void menu2()
{
	int size;
	char a;
	cout << "Enter number of variables\n";
	cin >> size;
	cout << "Choose how you want to fill the matrix and vector:\n";
	cout << "a. Randomly\n";
	cout << "b. Manually\n";
	cin >> a;
	logic2(size, a);
}

void logic()
{
	int k;
	cin >> k;
	switch (k)
	{
	case 1:
		menu2();
		break;
	case 2:
		check();
		break;
	case 3:
		multiply();
		break;
	case 4:
		exit(0);
	default:
		cout << "Wrong simbol\n";
		menu();
		break;
	}
}

void logic2(int size,char _case)
{
	{
		Matrix<double> mat(size);
		vector<double> ans(size);
		switch (_case)
		{
		case 'a':
			mat.fillrandom();
			ans.fillrandom();
			cout << "Matrix:\n" << mat << "Vector:\n" << ans << '\n';
			break;
		case 'b':
			cout << "Enter matrix\n";
			cin >> mat;
			cout << "Enter vector\n";
			cin >> ans;
			break;
		default:
			cout << "Wrong simbol\n";
			menu2();
		}
		ans = mat(ans);
		if (ans != vector<double>(0))
		{
			cout << "Answer:\n" << ans << '\n';
		}
	}

	menu();
}

void check()
{
	int size,n;
	cout << "Enter the size of the matrix to check\n";
	cin >> size;
	cout << "Enter number of iteration\n";
	cin >> n;

	{
		Matrix<double> mat(size);
		vector<double> vec(size), ans(size);
		bool flag = false;
		for (int i = 0; i < n; i++)
		{
			mat.fillrandom();
			vec.fillrandom();

			ans = mat * vec;
			Matrix<double> mat1 = mat;
			ans = mat(ans);
			if (ans != vec&&ans!=vector<double>(0))
			{
				cout << "Is not correct:\n" << inaccuracy(vec, ans) << '\n';
				flag = true;
			}

			if (i == n - 1&&flag==false)
			{
				cout << "All correct!\n";
			}
		}
	}

	menu();
}

void multiply()
{
	int size;
	char _case;
	cout << "Enter size of vector and matrix\n";
	cin >> size;
	cout << "Choose how you want to fill the matrix and vector:\n";
	cout << "a. Randomly\n";
	cout << "b. Manually\n";
	cin >> _case;
	{
		Matrix<double> mat(size);
		vector<double> vec(size);
		switch (_case)
		{
		case 'a':
			mat.fillrandom();
			vec.fillrandom();
			cout << "Matrix:\n" << mat << "Vector:\n" << vec << '\n';
			break;
		case 'b':
			cout << "Enter matrix\n";
			cin >> mat;
			cout << "Enter vector\n";
			cin >> vec;
			break;
		default:
			cout << "Wrong simbol\n";
			menu2();
		}
		cout << "Anser:\n" << mat * vec << '\n';
	}

	menu();
}