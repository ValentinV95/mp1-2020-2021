// Метод Гауса с выбором ведущего элемента(наибольший)
#include <iostream>

using namespace std;

template <typename Type>
class Vector
{
public:
	Vector()
	{
		size = 0;
		T = nullptr;
	}
	Vector(size_t size)
	{
		this->size = size;
		T = new Type[size];
	}
	Vector(Vector& B) : Vector(B.size)
	{
		for (size_t i = 0; i < size; i++)
		{
			T[i] = B[i];
		}
	}
	Type& operator[](size_t i)
	{
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
private:
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

template <typename Type>
class Matrix
{
public:
	Matrix(size_t size)
	{
		this->size = size;
		V = new Vector<Type>[size];
		for (size_t i = 0; i < size; i++)
		{
			V[i] = Vector<Type>(size);
		}
	}
	Matrix(Matrix& B) : Matrix(B.size)
	{
		for (size_t i = 0; i < size; i++)
		{
			V[i] = B[i];
		}
	}
	Vector<Type>& operator[](size_t i)
	{
		return V[i];
	}
	template <typename Type> friend istream& operator>>(istream& in, Matrix<Type>& A);
	template <typename Type> friend ostream& operator<<(ostream& out, Matrix<Type>& A);
	~Matrix()
	{
		delete[](V);
		size = 0;
	}
private:
	size_t size;
	Vector<Type>* V;
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
void Gauss(Matrix<Type>& A, size_t i, size_t size)
{
	size_t max = i;
	for (size_t j = i + 1; j < size; j++)
	{
		if (A[j][i] > A[max][i])
		{
			max = j;
		}
	}
	if (max != i)
	{
		swap(A[max], A[i]);
	}
	for (size_t j = i + 1; j < size; j++)
	{
		Type temp = A[j][i] / A[i][i];
		A[j] = A[j] - A[i] * temp;
	}
	if (i < size - 2)
	{
		Gauss(A, i + 1, size);
	}
	return;
};

int main()
{
	int n;
	cin >> n;
	Matrix<double> A(n);
	cin >> A;
	Gauss(A, 0, n);
	cout << A;
	return 0;
}