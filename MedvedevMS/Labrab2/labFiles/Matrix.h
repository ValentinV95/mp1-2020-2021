#pragma once
#include "vector.h"
#include "cassert"
using namespace std;

template <class T>
class Matrix : public Vector<Vector<T>>
{
public:
	Matrix() {}


	Matrix<T>(size_t row, size_t colum) : Vector<Vector<T>>(row, Vector<T>(colum, T()))
	{}

	Matrix<T>(const Matrix& Matr) : Vector<Vector<T>>(Matr) {}

	int MaxIndexInCol(int ind)
	{
		int MaxAbs = ind;
		for (int i = ind + 1; i < this->size; i++)
		{
			if (abs(this->data[MaxAbs][ind]) < abs(this->data[i][ind]))
			{
				MaxAbs = i;
			}
		}
		return MaxAbs;
	}
	void rand_matr()
	{
		for (int i = 0; i < this->size; i++)
		{
				this->data[i].random_fill_in();
		}
	}

	size_t geth()
	{
		return this->size;
	}
	size_t getw()
	{
		if (this->size != 0) {
			return this->data[0].getsize();
		}
		return 0;
	}

	~Matrix()
	{}

	Vector<T> operator* (const Vector<T>& V)
	{
		assert(this->size == V.getsize());
		Vector<T> res(this->size);
		for (int i = 0; i < this->size; i++)
		{
			res[i] = 0;
			for (int j = 0; j < this->getw(); j++)
			{
				res[i] += this->data[i][j] * V[j];
			}
		}
	}

	template <typename T>
	friend ostream& operator<< (ostream& out, const Matrix<T>& Matr)
	{
		for (int i = 0; i < Matr.size; i++)
		{
			out << Matr[i] << endl;
		}
		return out;
	}

	template <typename T>
	friend istream& operator>> (istream& in, Matrix<T>& Matr)
	{
		for (int i = 0; i < Matr.size; i++)
		{
			in >> Matr[i];
		}
		return in;
	}
};





	
	


