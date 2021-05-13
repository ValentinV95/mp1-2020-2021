#pragma once
using namespace std;
template <typename T>
class Vector
{
public:
	Vector()
	{
		size = 1;
		arr = new T[size];
	}

	Vector(int _size, T _value = T())
	{
		size = _size;
		arr = new T[_size];
		for (size_t i = 0; i < _size; i++)
		{
			arr[i] = _value;
		}
	}

	Vector(int _size, T* _values)
	{
		size = _size;
		arr = new T[size];
		for (size_t i = 0; i < size; i++)
		{
			arr[i] = _values[i];
		}
	}

	Vector(const Vector& other)
	{
		this->size = other.size;
		this->arr = new T[other.size];
		for (size_t i = 0; i < other.size; i++)
		{
			this->arr[i] = other.arr[i];
		}
	}

	~Vector()
	{
		delete[]arr;
	}

	void print_vector()
	{
		cout << "\n" << "{ ";
		for (size_t i = 0; i < size - 1; i++)
		{
			cout << arr[i] << " | ";
		}
		cout << arr[size - 1] << " }" << "\n\n";
	}

	T& operator[](int i)
	{
		return arr[i];
	}

	Vector<T> operator - (const Vector<T>& tmp)
	{
		Vector<T> temp(tmp.size);
		for (size_t i = 0; i < size; i++)
		{
			temp[i] = this->arr[i] - tmp.arr[i];
		}
		return temp;
	}

	Vector<T> operator + (const Vector<T>& tmp)
	{
		Vector<T> temp(tmp.size);
		for (size_t i = 0; i < size; i++)
		{
			temp[i] = this->arr[i] + tmp.arr[i];
		}
		return temp;
	}

	Vector& operator = (const Vector& tmpVector)
	{
		if (this->arr != tmpVector.arr)
		{
			delete[]this->arr;
			this->size = tmpVector.size;
			this->arr = new T[tmpVector.size];
			for (size_t i = 0; i < tmpVector.size; i++)
			{
				this->arr[i] = tmpVector.arr[i];
			}
		}
		return *this;
	}

protected:
	T* arr;
	int size;
};