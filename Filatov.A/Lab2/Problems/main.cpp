#include "gauss.h"

int main()
{
	size_t n;
	cin >> n;
	Matrix<double> A(n);
	cin >> A;
	Gauss<double> G(A);
	Vector<double> V(n);
	cin >> V;
	cout << G.Solve(V);
	return 0;
}