#pragma once
#include <iostream>
#include <ctime>
#include <iomanip>
#include "vector.h"

//const double MIN = 1e-9;

using namespace std;




template <typename T>
class Matrix : public Vector <Vector<T>>
{
private:
	T s;
	bool compatable = 1;
	int rank = 0;

	int maxIndexInCol(int index)
	{
		int maxAbs = index;

		for (int i = index + 1; i < this->size; i++)
		{
			if (_abs(this->data[maxAbs][index]) < _abs(this->data[i][index]))
			{
				maxAbs = i;
			}
		}

		return maxAbs;
	}

	void swapRow(int i, int j)
	{
		if (i != j)
		{
			Vector<T> temp = this->data[i];
			this->data[i] = this->data[j];
			this->data[j] = temp;
		}
	}

	void showDecision()
	{
		for (int i = this->size - 1; i >= 0; i--)
		{
			for (int j = this->size; j > i - 1; j--) {
				if (this->data[i][j] != 0)
				{
					this->data[i][j] = this->data[i][j + 1] / this->data[i][j];
				}
			}
		}
	}

public:
	Matrix(size_t m_size) :

		Vector<Vector<T>>(m_size, Vector<T>(m_size))

	{

	}



	Matrix(size_t h, size_t w, const T& val) :
		Vector<Vector<T>>(h, Vector<T>(w, val))
	{
	}


	~Matrix()
	{}

	bool getCompatable() {
		return compatable;
	}

	double Module(double q)
	{
		if (q < 0)
		{
			q *= -1;
		}
		return q;
	}
	void Rank()
	{
		for (int i = 0; i < this->size; i++)
		{
			if (this->data[i][i] != 0)
			{
				rank++;
			}
		}
	}

	int getRank()
	{
		return rank;
	}

	void CheckComplect()
	{
		for (int i = this->size - 1; i >= 0; i--)
		{

			if (this->data[i][0] == 0) {
				int proverka = 0;
				for (int j = 1; j < this->size; j++)
				{
					if (this->data[i][j] != 0)
					{
						proverka++;
					}
				}
				if ((proverka == 0) && (this->data[i][this->size] != 0)) {
					this->compatable = 0;
				}
			}
		}
	}


	void RandomElements()
	{
		for (size_t i = 0; i < this->size; i++)
		{
			for (size_t j = 0; j < this->size + 1; j++)
			{
				this->data[i][j] = static_cast<T>(rand()) / 39 / 3;
			}
		}
	}

	void LinearSystem()
	{
		for (size_t i = 0; i < this->size; i++)
		{
			for (size_t j = 0; j < this->size; j++)
			{
				cout << scientific << setprecision(6) << this->data[i][j] << "* X" << j + 1 << "\t";
			}
			cout << scientific << setprecision(6) << "=\t" << this->data[i][this->size];

			cout << endl;
		}
	}

	void GaussMethod(Vector<T>& x)
	{
		CheckComplect();
		for (size_t i = 0; i < this->size; i++)
		{
			int max = maxIndexInCol(i);
			swapRow(max, i);

			for (int row = i + 1; row < this->size; row++)
			{
				if (row != i && this->data[row][i] != 0) {
					T mnozhitel = (this->data[row][i]) / (this->data[i][i]);

					for (int k = i; k < this->size + 1; k++)
					{
						
						this->data[row][k] -= (this->data[i][k]) * mnozhitel;
						if (Module(this->data[row][k]) < 0.000000001)
						{
							this->data[row][k] = 0;
						}
						
						
					}
					
				}

			}
			

		}

		for (int i = this->size - 1; i >= 0; i--)
		{
			double sum = this->data[i][this->size];
			for (size_t j = this->size - 1; j > i; j--)
			{
				sum -= this->data[i][j] * x[j];
			}

			if (this->data[i][i] == 0)
			{
				x[i] = 0;
			}
			else
			{
				x[i] = sum / this->data[i][i];
			}

		}

		CheckComplect();			
	
		Rank();
	}

	void Alignment()
	{
		int j;
		for (int i = 0; i < this->size; i++)
		{
			if (this->data[i][i] == 0) {
				j = i + 1;
				if (j < this->size)
				{
					while (this->data[j][i] == 0 && j < this->size - 1)
					{
						j++;
					}
					swapRow(i, j);
				}
			}
		}
	}


};