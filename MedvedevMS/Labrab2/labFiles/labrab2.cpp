#include "vector.h"
#include "Matrix.h"
#include "gauss.h"
#include <iostream>


int main()
{
    size_t m, n;
	int cond;
	
	srand(time(0));
	
	cout << "Enter the positive number of rows(m) and columns(n)" << endl 
		<< "Note that the last column of the matrix is a vector of values!" << endl;
	cout << "Number of rows:";
	cin >> m;
	cout << "Number of columns:";
	cin >> n;

	Matrix<double> a(m, n);

	cout << "Enter 1 for random filling of the matrix, or 2 for manual filling." << endl;
	cin >> cond;
	switch (cond)
	{
	case 1: 
		cout << "Random matrix:" << endl;
		a.rand_matr();
		cout << a << endl;
		break;
	case 2:
		cout << "Input matrix:" << endl;
		cin >> a;
		cout << "Your matrix:" << endl;
		cout << a;
		break;

	default:
		cout << "incorrect input" << endl;
		break;
	}
    
	equationsSystem<double> equal(a);
	Vector<double> G = equal();
	eqResults ans = equal.getErr();
	
	switch (ans)
	{
	case eqResults::OK:
		cout << "Solution vector:" << endl;
		cout << G;
        break;

	case eqResults::INCONSISTENT:
		cout << "System of linear equations is inconsistent";
		break;

	case eqResults::INF_SOLUTIONS:
		cout << "Infinite number of solutions";
		break;

	case eqResults::NOT_SQUARE:
		cout << "Not square matrix";
		break;

	case eqResults::UNKNOWN:
		break;
	}
	
	
}

