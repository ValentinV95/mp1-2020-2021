#pragma once
#include<iostream>
#include"Vector.cpp"
#include<cmath>

using namespace std;

template<typename T>
class Matrix :public vector<vector<T>>
{
private:
	void swaprow(int i, int j)
	{
		if (i != j)
		{
			vector<T> tmp = this->data[i];
			this->data[i] = this->data[j];
			this->data[j] = tmp;
		}
	}

	int maxincol(int col)
	{
		T max = this->data[col][col];
		int num = col;

		for (int i = col + 1; i < this->size; i++)
		{
			if (abs(max) < abs(this->data[i][col]))
			{
				max = this->data[i][col];
				num = i;
			}
		}

		return num;
	}

public:
	Matrix(int nsize)
		:vector<vector<T> >(nsize)
	{
		for (int i = 0; i < this->size; i++)
		{
			this->data[i].resize(this->size);
		}
	}


	vector<T> operator*(const vector<T>& b)
	{
		if (this->size != b.getsize())
		{
			cout << "Size is different\n";
			exit(0);
		}
		vector<T> result(this->size);

		for (int i = 0; i < this->size; i++)
		{
			result[i] = 0;
			for (int j = 0; j < this->size; j++)
			{
				result[i] += this->data[i][j] * b[j];
			}
		}

		return result;
	}

	vector<T> operator()(const vector<T>& a)
	{
		vector<T> b = a;

		for (int i = 0; i < this->size; i++)
		{
			int imax = maxincol(i);
			swaprow(imax, i);
			b.swap(imax, i);
			
			if (abs(this->data[i][i]) < MIN)
			{
				cout << "System is linearly dependent\n\n";
				return vector<T>(0);
			}
			b[i] /= this->data[i][i];
			this->data[i] /= this->data[i][i];
			

			for (int j = i+1; j < this->size; j++)
			{
				b[j] += b[i] * this->data[j][i] * (-1);
				this->data[j] += this->data[i]*this->data[j][i]*(-1);
			}
		}

		for (int i = this->size - 1; i >= 0; i--)
		{
			for (int j = i + 1; j < this->size; j++)
			{
				b[i] += b[j] * (this->data[i][j]) * (-1);
			}
			if (abs(b[i]) < MIN)
			{
				b[i] = 0;
			}
		}

		return b;
	}

	void fillrandom()
	{
		for (int i = 0; i < this->size; i++)
		{
			for (int j = 0; j < this->size; j++)
			{
				this->data[i][j] = (T)(rand() % 20001)/20.0 - 500;
			}
		}
	}
};
