#pragma once

#include <iostream>
#include <cassert>
using namespace std;

template <class T>
class Vector
{
protected:
	int size;
	T* data;
public:

	~Vector()
	{
		delete[] data;
		data = nullptr;
	}

	Vector(int size = 0, const T& elem = T())
	{
		this->size = size;
		this->data = new T[size];

		for (int i = 0; i < size; i++)
		{
			data[i] = elem;
		}
	}

	Vector(int _size, T* _data)
	{
		assert(size >= 0);
		this->size = _size;
		data = new T[size];
		if (_data != NULL)
		{
			for (int i = 0; i < size; i++)
			{
				data[i] = _data[i];
			}
		}
	}

	size_t const getsize()
	{
		return size;
	}

	Vector(const Vector& Vec)
	{
		data = new T[Vec.size];
		size = Vec.size;
		for (int i = 0; i < size; i++)
		{
			this->data[i] = Vec.data[i];
		}
	}

	void resize(int newsize)
	{
		if (size != newsize)
		{
			delete[] data;
			data = new T[newsize];
			size = newsize;
		}
	}


	void random_fill_in()
	{
		for (int i = 0; i < size; i++)
		{
			this->data[i] = (T)(rand() % 20001) / 20.0 - 500;
		}
	}

	T& operator[](unsigned int i)
	{
		assert(i >= 0 && i < size);
		return data[i];
	}

	const T& operator[](unsigned int i) const
	{
		assert(i >= 0 && i < size);
			return data[i];
	}

	Vector<T>& operator= (const Vector& Vec)
	{
		if (size != Vec.size)
		{
			size = Vec.size;
			delete[] data;
			data = new T[size];
		}
		for (int i = 0; i < size; i++)
		{
			this->data[i] = Vec.data[i];
		}
		return *this;
	}

	Vector<T> operator+ (const Vector& Vec) const
	{
		assert(size == Vec.size);
		Vector res = Vector(*this);
		for (int i = 0; i < size; i++)
		{
			res.data[i] += Vec.data[i];
		}
		return res;
	}

	Vector<T>& operator+= (const Vector& Vec)
	{
		assert(size == Vec.size);
		for (int i = 0; i < size; i++)
		{
			data[i] += Vec.data[i];
		}

		return (*this);
	}

	Vector<T> operator- (const Vector& Vec) const
	{
		assert(size == Vec.size);
		Vector res = Vector(*this);
		for (int i = 0; i < size; i++)
		{
			res.data[i] -= Vec.data[i];
		}
		return res;
	}

	Vector<T>& operator-= (const Vector& Vec)
	{
		return ((*this) += (Vec * (-1)));
	}

	Vector<T> operator* (T d) const
	{
		Vector res = Vector(*this);
		for (int i = 0; i < size; i++)
		{
			res.data[i] *= d;
		}
		return res;
	}

	Vector<T>& operator*= (T d)
	{
		for (int i = 0; i < size; i++)
		{
			data[i] *= d;
		}

		return (*this);
	}

	Vector<T> operator/ (T d)
	{
		Vector res = Vector(*this);
		for (int i = 0; i < size; i++)
		{
			res.data[i] /= d;
		}
		return res;
	}

	Vector<T>& operator/= (T d)
	{
		for (int i = 0; i < size; i++)
		{
			data[i] /= d;
		}
		return (*this);
	}

	template <typename T> friend ostream& operator<< (ostream& out, const Vector<T>& Vec);
	template <typename T> friend istream& operator>> (istream& in, Vector<T>& Vec);

	friend void swap(Vector<T>& l, Vector<T>& r)
	{
		std::swap(l.data, r.data);
		std::swap(l.size, r.size);
	}
};

template <typename T>
ostream& operator<< (ostream& out, const Vector<T>& Vec)
{
	out << "| ";
	for (int i = 0; i < Vec.size - 1; i++) {
		out << Vec.data[i] << "     ";
	}
	out << Vec.data[Vec.size - 1] << " |";
	return out;
};

	template <typename T>
	istream& operator>> (istream& in, Vector<T>& Vec)
	{
		for (int i = 0; i < Vec.size; i++)
		{
			in >> Vec.data[i];
		}
		return in;
	};
