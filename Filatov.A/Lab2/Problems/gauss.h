// Метод Гаусса с выбором ведущего элемента(наибольший)
#include <iostream>
#include <time.h>
#include <random>
#include <algorithm>
#include <iomanip>

using namespace std;

const double e = 1e-9;

template <typename Type>
class Vector
{
public:
	Vector<Type>()
	{
		size = 0;
		T = nullptr;
	}
	Vector<Type>(size_t size)
	{
		this->size = size;
		T = new Type[size];
	}
	Vector<Type>(Vector& B) : Vector<Type>(B.size)
	{
		size = B.size;
		for (size_t i = 0; i < size; i++)
		{
			T[i] = B[i];
		}
	}
	size_t get_size()
	{
		return size;
	}
	void Random()
	{
		srand(clock());
		for (size_t i = 0; i < size; i++)
		{
			T[i] = (double)rand() / (double)rand();
		}
	}
	Type& operator[](size_t i)
	{
		if (i > size)
		{
			cerr << "Index out of range";
			exit(0);
		}
		return T[i];
	}
	Vector<Type>& operator=(Vector<Type> B)
	{
		swap(T, B.T);
		swap(size, B.size);
		return *this;
	}
	Vector<Type> operator-(Vector<Type>& B)
	{
		if (size != B.size)
		{
			cerr << "Wrong size";
			exit(0);
		}
		Vector C(size);
		for (size_t i = 0; i < size; i++)
		{
			C[i] = T[i] - B[i];
		}
		return C;
	}
	Vector<Type> operator*(Type b)
	{
		Vector C(size);
		for (size_t i = 0; i < size; i++)
		{
			C[i] = T[i] * b;
		}
		return C;
	}
	template <typename Type> friend istream& operator>>(istream& in, Vector<Type>& A);
	template <typename Type> friend ostream& operator<<(ostream& out, Vector<Type>& A);
	~Vector()
	{
		delete[](T);
		size = 0;
	}
protected:
	size_t size;
	Type* T;
};

template <typename Type>
istream& operator>>(istream& in, Vector<Type>& A)
{
	for (size_t i = 0; i < A.size; i++)
	{
		in >> A[i];
	}
	return in;
};

template <typename Type>
ostream& operator<<(ostream& out, Vector<Type>& A)
{
	for (size_t i = 0; i < A.size; i++)
	{
		out << A[i] << " ";
	}
	return out;
};

template<typename Type>
class Matrix : public Vector<Vector<Type>>
{
public:
	Matrix<Type>()
	{

	}
	Matrix<Type>(size_t size) : Vector<Vector<Type>>(size)
	{
		for (size_t i = 0; i < size; i++)
		{
			T[i] = Vector<Type>(size);
		}
	}
	Matrix<Type>(Matrix& B) : Matrix(B.size)
	{
		for (size_t i = 0; i < size; i++)
		{
			T[i] = B[i];
		}
	}
	void Random()
	{
		srand(clock());
		for (size_t i = 0; i < size; i++)
		{
			for (size_t j = 0; j < size; j++)
			{
				T[i][j] = (double)(rand()) / (double)(rand());
			}
		}
	}
	Matrix<Type>& operator=(Matrix B)
	{
		swap(size, B.size);
		swap(T, B.T);
		return *this;
	}
	Matrix<Type> operator*(Type b)
	{
		Matrix<Type> C(size);
		for (size_t i = 0; i < size; i++)
		{
			C[i] = T[i] * b;
		}
		return C;
	}
	template <typename Type> friend istream& operator>>(istream& in, Matrix<Type>& A);
	template <typename Type> friend ostream& operator<<(ostream& out, Matrix<Type>& A);
	~Matrix()
	{
	}
};

template <typename Type>
istream& operator>>(istream& in, Matrix<Type>& A)
{
	for (size_t i = 0; i < A.size; i++)
	{
		in >> A[i];
	}
	return in;
};

template <typename Type>
ostream& operator<<(ostream& out, Matrix<Type>& A)
{
	for (size_t i = 0; i < A.size; i++)
	{
		out << A[i] << endl;
	}
	return out;
};

template <typename Type>
class Gauss
{
public:
	Gauss<Type>(Matrix<Type>& M)
	{
		this->M = M;
	}
	Vector<Type> Solve(Vector<Type>& V)
	{
		size_t size = V.get_size();
		for (size_t i = 0; i < size; i++)
		{
			size_t max = i;
			for (size_t j = i + 1; j < size; j++)
			{
				if (abs(M[j][i]) - abs(M[max][i]) > e)
				{
					max = j;
				}
			}
			if (max != i)
			{
				swap(M[i], M[max]);
				swap(V[i], V[max]);
			}
			if (abs(M[i][i]) < e)
			{
				cerr << "Invalid matrix";
				exit(0);
			}
			for (size_t j = i + 1; j < size; j++)
			{
				Type temp = M[j][i] / M[i][i];
				M[j] = M[j] - (M[i] * temp);
				V[j] -= V[i] * temp;
			}
		}
		Vector<Type> G(size);
		for (int i = size - 1; i >= 0; i--)
		{
			G[i] = V[i];
			for (size_t j = i + 1; j < size; j++)
			{
				G[i] -= G[j] * M[i][j];
			}
			G[i] /= M[i][i];
		}
		return G;
	}
private:
	Matrix<Type> M;
};