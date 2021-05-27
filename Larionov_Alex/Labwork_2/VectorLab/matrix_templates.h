#pragma once
#include <iostream>
using namespace std;
template <class T>
class vector
{
public:
	T** link, input; size_t size_1, size_2;
	vector()
	{
		link = nullptr;
	};
	vector<T>(size_t size1)
	{
		size_1 = 1;
		size_2 = size1;
		input = 0;
		link = new T * [size_1];
		for (size_t i = 0; i < this->size_1; i++)
		{
			link[i] = new T[size_2];
		}
		for (size_t i = 0; i < (this->size_1); i++)
		{
			for (size_t j = 0; j < this->size_2; j++)
			{
				link[i][j] = 0;
			}
		}
	}
	vector<T>(size_t size1, size_t size2)
	{
		size_1 = size1;
		size_2 = size2;
		input = 0;
		link = new T * [size_1];
		for (size_t i = 0; i < this->size_1; i++)
		{
			link[i] = new T[size_2];
		}
		for (size_t i = 0; i < (this->size_1); i++)
		{
			for (size_t j = 0; j < this->size_2; j++)
			{
				link[i][j] = 0;
			}
		}
	}
	void fill_manually(vector A)
	{
		for (size_t i = 0; i < (this->size_1); i++)
		{
			for (size_t j = 0; j < this->size_2; j++)
			{
				cin >> input;
				A.link[i][j] = input;
			}
		}
	}
	void fill_randomly(vector A)
	{
		srand(time(NULL));
		for (size_t i = 0; i < (this->size_1); i++)
		{
			for (size_t j = 0; j < this->size_2; j++)
			{
				A.link[i][j] = rand();
			}
		}
	}
	size_t getsize() { return(size_1); }
	T** getlink() { return(link); }
	friend vector<T> operator + (vector& left, vector& right)
	{
		vector<T> temp(left.size_1, left.size_2);
		for (size_t i = 0; i < temp.size_1; i++)
		{
			for (size_t j = 0; j < temp.size_2; j++)
			{
				temp.link[i][j] = left.link[i][j] + right.link[i][j];
			}
		}
		return(temp);
	}
	friend vector<T> operator - (vector& left, vector& right)
	{
		vector<T> temp(left.size_1, left.size_2);
		for (size_t i = 0; i < temp.size_1; i++)
		{
			for (size_t j = 0; j < temp.size_2; j++)
			{
				temp.link[i][j] = left.link[i][j] - right.link[i][j];
			}
		}
		return(temp);
	}
	friend vector<T> operator * (T left, vector<T> right)
	{
		vector temp(right.size_1, right.size_2);
		for (size_t i = 0; i < temp.size_1; i++)
		{
			for (size_t j = 0; j < temp.size_2; j++)
			{
				temp.link[i][j] = left * right.link[i][j];
			}
		}
		return(temp);
	}
	friend vector<T> operator / (vector left, T right)
	{
		vector temp(left.size_1, left.size_2);
		for (size_t i = 0; i < temp.size_1; i++)
		{
			for (size_t j = 0; j < temp.size_2; j++)
			{
				temp.link[i][j] = (left.link[i][j]) / right;
			}
		}
		return(temp);
	}
	vector<T>& operator = (vector right)
	{
		this->size_1 = right.size_1;
		this->size_2 = right.size_2;
		for (size_t i = 0; i < this->size_1; i++)
		{
			for (size_t j = 0; j < this->size_2; j++)
			{
				this->link[i][j] = right.link[i][j];
			}
		}
		return(*this);
	}
	void print()
	{
		for (int i = 0; i < (this->size_1); i++)
		{
			for (size_t j = 0; j < this->size_2; j++)
			{
				cout << this->link[i][j] << "		";
			}
			cout << "" << endl;
		}
	}
	
};
template <class T>
class matrix :public vector<T>
{
public:
	//T** linkM, inputM; size_t size_1M, size_2M;
	matrix<T>(size_t size1M, size_t size2M)
	{
		this->size_1 = size1M;
		this->size_2 = size2M;
		this->input = 0;
		this->link = new T * [this->size_1];
		for (size_t i = 0; i < this->size_1; i++)
		{
			this->link[i] = new T[this->size_2];
		}
		for (size_t i = 0; i < (this->size_1); i++)
		{
			for (size_t j = 0; j < this->size_2; j++)
			{
				this->link[i][j] = 0;
			}
		}
	}
	matrix<T>(size_t size1M)
	{
		this->size_1 = size1M;
		this->size_2 = size1M + 1;
		this->input = 0;
		this->link = new T * [this->size_1];
		for (size_t i = 0; i < this->size_1; i++)
		{
			this->link[i] = new T[this->size_2];
		}
		for (size_t i = 0; i < (this->size_1); i++)
		{
			for (size_t j = 0; j < this->size_2; j++)
			{
				this->link[i][j] = 0;
			}
		}
	}
	void fill_manually()
	{
		for (size_t i = 0; i < (this->size_1); i++)
		{
			for (size_t j = 0; j < this->size_2; j++)
			{
				cin >> this->input;
				this->link[i][j] = this->input;
			}
		}
	}
	void printm()
	{
		for (int i = 0; i < (this->size_1); i++)
		{
			for (size_t j = 0; j < this->size_2; j++)
			{
				cout << this->link[i][j] << "		";
			}
			cout << "" << endl;
		}
	}
	void fill_randomly()
	{
		srand(time(NULL));
		for (size_t i = 0; i < (this->size_1); i++)
		{
			for (size_t j = 0; j < this->size_2; j++)
			{
				this->link[i][j] = rand();
			}
		}
	}
	void swap(size_t initial, size_t swappable)
	{
		if (initial != swappable)
		{
			T* temp;
			temp = new T[this->size_2];
			for (size_t j = 0; j < this->size_2; j++)
			{
				temp[j] = this->link[initial][j];
				this->link[initial][j] = this->link[swappable][j];
				this->link[swappable][j] = temp[j];
			}
		}
	}
	void nullify_row(size_t i)
	{
		T temp;
		if (this->link[i][i] != 0)
		{
			if (this->link[i][i] < 0)
			{
				for (size_t j = 0; j < this->size_2; j++)
				{
					this->link[i][j] = (-1) * this->link[i][j];
				}
			}
			for (size_t i1 = i; i1 < this->size_1 - 1; i1++)// занулить ниже диагонали
			{
				if (this->link[i1 + 1][i] != 0)
				{
					if (this->link[i1 + 1][i] < 0)
					{
						for (size_t j = 0; j < this->size_2; j++)
						{
							this->link[i1 + 1][j] = (-1) * this->link[i1 + 1][j];
						}
					}
					temp = this->link[i1 + 1][i] / this->link[i][i];
					for (size_t J = 0; J < this->size_2; J++)
					{
						this->link[i1 + 1][J] = this->link[i1 + 1][J] - this->link[i][J] * temp;
					}
				}
			}
			for (size_t i1 = i; i1 > 0; i1--)//занулить выше диагонали
			{
				if (this->link[i1 - 1][i] != 0)
				{
					if (this->link[i1 - 1][i] < 0)
					{
						for (size_t j = 0; j < this->size_2; j++)
						{
							this->link[i1 - 1][j] = (-1) * this->link[i1 - 1][j];
						}
					}
					temp = this->link[i1 - 1][i] / this->link[i][i];
					for (size_t J = 0; J < this->size_2; J++)
					{
						this->link[i1 - 1][J] = this->link[i1 - 1][J] - this->link[i][J] * temp;
					}
				}
			}

		}
		//this->printm();
	}
	void J_G()
	{
		for (size_t i = 0; i < this->size_1; i++)
		{
			for (size_t j = 0; j < this->size_1; j++)
			{
				if (this->link[j][i] < 0)
				{
					for (size_t H = 0; H < this->size_2; H++)
					{
						this->link[j][H] = (-1) * this->link[j][H];
					}
				}
			}
			for (size_t j = i; j < this->size_1; j++)
			{
				if (this->link[i][i] < this->link[j][i])
				{
					this->swap(i, j);
				}
			}
			cout << " " << endl;
			this->nullify_row(i);
		}
		T temp;
		for (size_t K = 0; K < this->size_1; K++)\
		{
			if (this->link[K][K] != 0)
			{
				temp = this->link[K][K];
				for (size_t N = 0; N < this->size_2; N++)
				{
					this->link[K][N] = this->link[K][N] / temp;
				}
			}
		}
		for (size_t K = 0; K < this->size_1; K++) //занулить погрешности от операций с double
		{
			for (size_t N = 0; N < this->size_2; N++)
			{
				if (abs(this->link[K][N]) < 0.1e-14)
				{
					this->link[K][N] = 0;
				}
			}
		}
		this->printm();
	}
	size_t checkM()
	{ 
	// ѕроверка на совместность и бесконечные решени€
		size_t count1 = 0, count2=0, count3=0;
		for (size_t i = 0; i < this->size_1; i++)
		{
			for (size_t j = 0; j < this->size_1; j++)
			{
				if (abs(this->link[i][j]) > 0.1e-14 ) { count1++; };
				if (abs(this->link[i][this->size_2-1]) > 0.1e-14) { count2++; };
			}
			if (count1 == 0)
			{
				if (count2 == 0)
				{
					cout << "Ѕесконечно много решений." << endl;
					count3++;
					break;
				}
				else
				{
					cout << "—истема не совместна." << endl;
					count3++;
					break;
				}
			}
			count1 = 0; count2 = 0;
		}
		return(count3);
	}
	void printAnswer()
	{
		T A=0;
		for (size_t i = 0; i < this->size_1; i++)
		{
			cout << "X" << i << "=" << 	this->link[i][this->size_2 - 1] << endl;
		}
	}
};