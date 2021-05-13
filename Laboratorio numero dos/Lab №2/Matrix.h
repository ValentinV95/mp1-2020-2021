#pragma once
using namespace std;
template <typename T>
class Matrix : public Vector < Vector < T > >
{
public:

	Matrix(int n) : Vector < Vector < T > >(n, Vector < T >(n)) {}

	void matrix_print()
	{
		for (size_t i = 0; i < this->size; i++)
		{
			for (size_t j = 0; j < this->size; j++)
			{
				cout << this->arr[i][j] << "\n";
			}
			cout << endl;
		}
	}
};