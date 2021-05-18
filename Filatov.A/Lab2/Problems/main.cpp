#include "gauss.h"

int main()
{
	size_t n;
	cout << "Input matrix size" << endl;
	cin >> n;
	Matrix<double> A(n);
	cout << "Enter 1 for random matrix or 0 for input it manually" << endl;
	bool b;
	cin >> b;
	if (b)
	{
		A.Random();
		cout << A;
	}
	else
	{
		cin >> A;
	}
	Gauss<double> G(A);
	Vector<double> V(n);
	cout << "Enter 1 for random solution vector or 0 for input it manually" << endl;
	cin >> b;
	if (b)
	{
		V.Random();
		cout << V << endl;
	}
	else
	{
		cin >> V;
	}
	cout << "The result" << endl << G.Solve(V) << endl;
	return 0;
}