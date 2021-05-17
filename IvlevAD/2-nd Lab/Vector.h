#pragma once

#include <iostream>

using namespace std;

template <typename T>

class MyVec
{
protected:
	size_t size;
	T* data;
public:
	size_t get_size()
	{
		return(size);
	}

	void rand_set_data_double()
	{
		for (size_t i = 0; i < size; i++)
		{
			data[i] = (T) ((rand() / 10.0) - (rand() / 20.0));
		}
	}

	MyVec(size_t _size = 0)
	{
		size = _size;
		if (size == 0)
		{
			data = nullptr;
		}
		else
		{
			data = new T[size];
		}
	}
	MyVec(const MyVec& sec)
	{
		size = sec.size;
		data = new T[size];
		for (size_t i = 0; i < size; i++)
		{
			data[i] = sec[i];
		}
	}

	T& operator [](size_t i) const
	{
		return(data[i]);
	}

	MyVec& operator = (const MyVec& sec)
	{
		if (sec.size > size)
		{
			re_size(sec.size);
		}
		for (size_t i = 0; i < sec.size; i++)
		{
			data[i] = sec[i];
		}
		return (*this);
	}

	MyVec operator * (T sec)
	{
		MyVec <T> A{ size };
		for (size_t i = 0; i < size; i++)
		{
			A[i] = data[i] * sec;
		}
		return(A);
	}

	MyVec& operator -= (const MyVec& sec)
	{
		if (sec.size > size)
		{
			re_size(sec.size);
		}
		for (size_t i = 0; i < sec.size; i++)
		{
			data[i] -= sec[i];
		}
		return (*this);
	}

	MyVec& operator /= (T sec)
	{
		for (size_t i = 0; i < size; i++)
		{
			data[i] /= sec;
		}
		return (*this);
	}

	bool check_size(const MyVec& sec)
	{
		if (size == sec.size)
		{
			return true;
		}
		else
		{
			cout << "Error size" << endl;
			return false;
		}
	}

	void re_size(size_t sec_size)
	{
		if (sec_size > size)
		{
			T* secdata;
			secdata = new T[sec_size];
			for (size_t i = 0; i < size; i++)
			{
				secdata[i] = data[i];
			}
			for (size_t i = size; i < sec_size; i++)
			{
				secdata[i] = 0;
			}
			delete[] data;
			data = secdata;
		}
		size = sec_size;
	}

	void swap(size_t i, size_t j)
    {
        T C;
        C = data[i];
        data[i] = data[j];
        data[j] = C;
    }

	~MyVec()
    {
        delete [] data;
    }
};

template <typename U>

istream& operator >> (istream& ist, MyVec<U> & sec)
{
	for (size_t i = 0; i < sec.get_size(); i++)
	{
		ist >> sec[i];
	}
    return ist;
}

template <typename U>

ostream& operator << (ostream& ost, MyVec<U> & sec)
{
    for (size_t i = 0; i < (sec.get_size() - 1); i++)
    {
        ost << sec[i] << " ";
    }
	ost << sec[sec.get_size() - 1];
	ost << "\n";
    return ost;
}
