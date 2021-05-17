#pragma once
#include<iostream>

using namespace std;

const double MIN = 1e-9;

template<typename T>

class vector
{
protected:
	T* data;
	int size;
public:
	vector(int nsize = 0, T* ndata = NULL)
		:size(nsize)
	{
		if (size < 0)
		{
			cout << "Size is negative\n";
			exit(1);
		}

		data = new T[size];

		if (ndata != NULL)
		{
			for (int i = 0; i < size; i++)
			{
				data[i] = ndata[i];
			}
		}
	}

	vector(const vector& a)
		:size(a.size)
	{
		data = new T[size];
		for (int i = 0; i < size; i++)
		{
			data[i] = a[i];
		}
	}

	int getsize() const { return size; }

	void resize(int newsize)
	{
		if (size != newsize)
		{
			delete[] data;
			data = new T[newsize];
			size = newsize;
		}
	}

	void swap(int a, int b)
	{
		if (a != b)
		{
			T tmp = this->data[a];
			this->data[a] = this->data[b];
			this->data[b] = tmp;
		}
	}

	void fillrandom()
	{
		for (int i = 0; i < size; i++)
		{
			this->data[i] = (T)(rand() % 20001) / 20.0 - 500;
		}
	}

	vector<T>& operator=(const vector& second)
	{
		if (size != second.size)
		{
			size = second.size;
			delete[] data;
			data = new T[size];
		}

		for (int i = 0; i < size; i++)
		{
			this[0][i] = second[i];
		}

		return *this;
	}

	bool operator!=(const vector& second)
	{
		if (size != second.size) { return true; }
		if (this == &second) { return false; }

		for (int i = 0; i < size; i++)
		{
			if (abs(data[i] - second.data[i])>MIN)
				return true;
		}

		return false;
	}

	friend vector operator*(const vector<T>& a, T b)
	{
		vector<T> result(a.size);
		for (int i = 0; i < a.size; i++)
		{
			result[i] = a[i] * b;
		}
		return result;
	}

	friend vector operator*(T b,const vector<T>& a)
	{
		vector<T> result(a.size);
		for (int i = 0; i < a.size; i++)
		{
			result[i] = a[i] * b;
		}
		return result;
	}

	vector<T>& operator/=(const T a)
	{
		for (int i = 0; i < size; i++)
		{
			data[i] /= a;
		}

		return *this;
	}

	vector<T>& operator+=(const vector<T> a)
	{
		for (int i = 0; i < size; i++)
		{
			data[i] += a[i];
		}

		return *this;
	}

	T& operator[](int i)
	{
		if (i < 0 || i >= size)
		{
			cout << "Access error in vector";
			exit(2);
		}

		return data[i];
	}

	const T& operator[](int i) const
	{
		if (i < 0 || i >= size)
		{
			cout << "Access error in vector";
			exit(2);
		}

		return data[i];
	}

	friend ostream& operator<<(ostream& str, const vector<T>& vec)
	{
		for (int i = 0; i < vec.size; i++)
		{
			str << vec[i] << ' ';
		}
		str << '\n';
		return str;
	}

	friend istream& operator>>(istream& str, vector<T>& vec)
	{
		for (int i = 0; i < vec.size; i++)
		{
			str >> vec[i];
		}

		return str;
	}

	template<typename T>
	friend double inaccuracy(vector<T> a, vector<T> b);

	~vector()
	{
		delete[] data;
	}
};

template<typename T>
double inaccuracy(vector<T> a,vector<T> b)
{
	double result = 100;
	for (int i = 0; i < a.size; i++)
	{
		if (abs(b[i] - a[i]) >= MIN && abs(b[i] - a[i]) < result)
		{
			result = abs(b[i] - a[i]);
		}
	}
	return result;
}