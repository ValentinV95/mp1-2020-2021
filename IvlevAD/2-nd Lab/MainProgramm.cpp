#include <iostream>
#include <cmath>
#include "Vector.h"
#include "Matrix.h"

using namespace std;

int main()
{
    cout << "Enter the size of the matrix (m rows and n columns)" << endl;
    size_t m, n, check;
    cin >> m >> n;
    srand(m*n);
    Matrix<double> M0{m, n};
    cout << "1: Create a random matrix\n2: Enter the matrix(double)" << endl;
    cin >> check;
	if (check == 1)
    {
        M0.rand_set_matrix_double();
    }
    if (check == 2)
    {
        cin >> M0;
    }
    cout << "1: Print your matrix\n2: Don't print your matrix" << endl;
    cin >> check;
    if (check == 1)
    {
        cout << "Your matrix" << endl;
		cout << M0;
    }
    cout << "1: Create a random vector of values\n2: Enter a vector of values" << endl;
    cin >> check;
    MyVec<double> X{m};
    if (check == 1)
    {
        X.rand_set_data_double();
    }
    if (check == 2)
    {
        cin >> X;
    }
    cout << "1: Print your vector of values\n2: Don't print your vector of values" << endl;
    cin >> check;
    if (check == 1)
    {
        cout << "Your vector of values" << endl;
        cout << X;
    }
    cout << "1: Step-by-step solution\n2: Only solution" << endl;
    cin >> check;
	MyVec<double> XV = M0.Gauss(X, check);
    cout << "Solving a system of linear equations by the Gauss method" << endl;
    cout << XV;
    cout << "1: Test Gause\n2: End" << endl;
    cin >> check;
    if (check == 1)
    {
        cout << "Test" << endl;
        M0.test(XV, X);   
    }

    system("pause");

}
