#pragma once

#include <iostream>
#include <ctime>
#include <iomanip>

const double MIN = 1e-9;

using namespace std;

template<typename T>
T _abs(T element)
{
	if (element < 0) { element *= -1; }

	return element;

}

template<typename T>
T Evklid(T a, T b) {

	if (a == b) {
		return a;
	}

	if (a > b) {
		T tmp = a;
		a = b;
		b = tmp;
	}

	Evklid(a, b - a);
}


template <typename T>
class Vector
{
protected:
	T* data;
	size_t size;
public:
	Vector() { this->size = 0; data = nullptr; }

	Vector(size_t _size)
	{


		size = _size;
		data = new T[size];
	}

	Vector(const Vector& second)
		: size(second.size)
		, data(new T[second.size])
	{
		for (int i = 0; i < second.size; i++)
		{
			data[i] = second.data[i];
		}
	}



	Vector(size_t _size, const T& elems) :
		size(_size)
	{


		this->data = new T[_size];

		for (size_t i = 0; i < size; i++)
		{
			data[i] = elems;
		}
	}

	~Vector() { delete[] data; }


	T& operator[](size_t index)
	{

		return data[index];
	}

	const T& operator[](size_t index) const
	{
		return data[index];
	}

	int getSize() const { return size; }

	T* getData(size_t index)
	{
		return data[index];
	}

	Vector& operator=(const Vector& Val)
	{
		if (size != Val.size)
		{

			delete[] data;
			data = nullptr;
			size = 0;
			data = new T[Val.size];
			size = Val.size;


		}

		for (size_t i = 0; i < size; i++)
		{
			this->data[i] = Val.data[i];
		}
		return *this;

	}

	bool operator != (const Vector& second)
	{


		if (size == second.size)
		{
			for (size_t i = 0; i < size; i++)
			{
				if (_abs(data[i] - second.data[i]) > MIN)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
		else
		{
			return false;
		}
	}

	void swap(int& a, int& b)
	{
		if (a != b)
		{
			T tmp = this->data[a];
			this->data[a] = this->data[b];
			this->data[b] = tmp;
		}

	}

	void resize(size_t _size)
	{
		if (size != _size)
		{
			delete[] this->data;
			this->data = new T[_size];
			this->size = _size;
		}
	}




	Vector<T>& operator+=(const Vector<T> a)
	{
		if (this->size == a.size)
		{
			for (int i = 0; i < this->size; i++)
			{
				this->data[i] += a[i];
			}
		}

		return *this;
	}

	Vector<T>& operator/= (const T a)
	{
		for (int i = 0; i < size; i++)
		{
			data[i] /= a;
		}

		return *this;
	}

	friend Vector<T> operator*(const Vector<T>& A, T B)
	{
		Vector<T> result(A.size);
		for (int i = 0; i < A.getSize; i++)
		{
			result[i] = A[i] * B;
		}

		return result;
	}

	friend Vector operator*(T B, const Vector& A)
	{
		Vector<T> result(A.size);
		for (int i = 0; i < A.size; i++)
		{
			result[i] = A[i] * B;
		}

		return result;
	}

	template <typename T>
	friend ostream& operator<< (ostream& out, const Vector<T>& V);


	template <typename T>
	friend istream& operator>> (istream& in, Vector<T>& V);

};


template <typename T>
ostream& operator<< (ostream& out, const Vector<T>& V)
{
	for (size_t i = 0; i < V.size; i++)
	{
		out << V[i] << ' ';
	}
	cout << endl;
	return out;
}



template <typename T>
istream& operator>> (istream& in, Vector<T>& V)
{


	for (size_t i = 0; i < V.size; i++)
	{
		in >> V[i];
	}

	return in;
}


