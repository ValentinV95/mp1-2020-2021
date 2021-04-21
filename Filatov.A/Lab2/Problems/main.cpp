#include "gauss.h"

int main()
{
	size_t n;
	cin >> n;
	Matrix<double> A(n);
	/*cin >> A;*/
	A.Random();
	Gauss<double> G(A);
	Vector<double> V(n);
	/*cin >> V;*/
	V.Random();
	cout << G.Solve(V) << endl;
	return 0;
}