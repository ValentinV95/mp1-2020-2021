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
class matrix :public vector<vector<T>>
{
public:
	/*vector<T> A{};
	matrix<T>(size_t size1)
	{
	vector<T> matrix(size1, size1);
	A = matrix;
	}
	void fill_manually()
	{
		vector<T> temp(A.size_1, A.size_1);
		temp.fill_manually(temp);
		A = temp;
	}
	void printm()
	{
		vector<T> temp(A.size1, A.size1);
		temp = A;
		temp.print();
	}*/
	T** linkM, inputM; size_t size_1M, size_2M;
	matrix<T>(size_t size1, size_t size2)
	{
		size_1M = size1;
		size_2M = size2;
		inputM = 0;
		linkM = new T * [size_1M];
		for (size_t i = 0; i < this->size_1M; i++)
		{
			linkM[i] = new T[size_2M];
		}
		for (size_t i = 0; i < (this->size_1M); i++)
		{
			for (size_t j = 0; j < this->size_2M; j++)
			{
				linkM[i][j] = 0;
			}
		}
	}
	matrix<T>(size_t size1)
	{
		size_1M = size1;
		size_2M = size1 + 1;
		inputM = 0;
		linkM = new T * [size_1M];
		for (size_t i = 0; i < this->size_1M; i++)
		{
			linkM[i] = new T[size_2M];
		}
		for (size_t i = 0; i < (this->size_1M); i++)
		{
			for (size_t j = 0; j < this->size_2M; j++)
			{
				linkM[i][j] = 0;
			}
		}
	}
	void fill_manually()
	{
		for (size_t i = 0; i < (this->size_1M); i++)
		{
			for (size_t j = 0; j < this->size_2M; j++)
			{
				cin >> inputM;
				this->linkM[i][j] = inputM;
			}
		}
	}
	void printm()
	{
		for (int i = 0; i < (this->size_1M); i++)
		{
			for (size_t j = 0; j < this->size_2M; j++)
			{
				cout << this->linkM[i][j] << "		";
			}
			cout << "" << endl;
		}
	}
	void fill_randomly()
	{
		srand(time(NULL));
		for (size_t i = 0; i < (this->size_1M); i++)
		{
			for (size_t j = 0; j < this->size_2M; j++)
			{
				this->linkM[i][j] = rand();
			}
		}
	}
	void swap(size_t initial, size_t swappable)
	{
		if (initial != swappable)
		{
			T* temp;
			temp = new T[this->size_2M];
			for (size_t j = 0; j < size_2M; j++)
			{
				temp[j] = linkM[initial][j];
				linkM[initial][j] = linkM[swappable][j];
				linkM[swappable][j] = temp[j];
			}
		}
	}
	void nullify_row(size_t i)
	{
		T temp;
		if (linkM[i][i] != 0)
		{
			if (linkM[i][i] < 0)
			{
				for (size_t j = 0; j < this->size_2M; j++)
				{
					linkM[i][j] = (-1) * linkM[i][j];
				}
			}
			for (size_t i1 = i; i1 < this->size_1M - 1; i1++)// занулить ниже диагонали
			{
				if (linkM[i1 + 1][i] != 0)
				{
					if (linkM[i1 + 1][i] < 0)
					{
						for (size_t j = 0; j < this->size_2M; j++)
						{
							linkM[i1 + 1][j] = (-1) * linkM[i1 + 1][j];
						}
					}
					temp = linkM[i1 + 1][i] / linkM[i][i];
					for (size_t J = 0; J < this->size_2M; J++)
					{
						linkM[i1 + 1][J] = linkM[i1 + 1][J] - linkM[i][J] * temp;
					}
				}
			}
			for (size_t i1 = i; i1 > 0; i1--)//занулить выше диагонали
			{
				if (linkM[i1 - 1][i] != 0)
				{
					if (linkM[i1 - 1][i] < 0)
					{
						for (size_t j = 0; j < this->size_2M; j++)
						{
							linkM[i1 - 1][j] = (-1) * linkM[i1 - 1][j];
						}
					}
					temp = linkM[i1 - 1][i] / linkM[i][i];
					for (size_t J = 0; J < this->size_2M; J++)
					{
						linkM[i1 - 1][J] = linkM[i1 - 1][J] - linkM[i][J] * temp;
					}
				}
			}

		}
		//this->printm();
	}
	void J_G()
	{
		for (size_t i = 0; i < this->size_1M; i++)
		{
			for (size_t j = 0; j < this->size_1M; j++)
			{
				if (linkM[j][i] < 0)
				{
					for (size_t H = 0; H < size_2M; H++)
					{
						linkM[j][H] = (-1) * linkM[j][H];
					}
				}
			}
			for (size_t j = i; j < this->size_1M; j++)
			{
				if (linkM[i][i] < linkM[j][i])
				{
					this->swap(i, j);
				}
			}
			cout << " " << endl;
			this->nullify_row(i);
		}
		T temp;
		for (size_t K = 0; K < size_1M; K++)\
		{
			if (linkM[K][K] != 0)
			{
				temp = linkM[K][K];
				for (size_t N = 0; N < size_2M; N++)
				{
					linkM[K][N] = linkM[K][N] / temp;
				}
			}
		}
		for (size_t K = 0; K < size_1M; K++)\
		{
			for (size_t N = 0; N < size_2M; N++)
			{
				if (abs(linkM[K][N]) < 0.1e-14)
				{
					linkM[K][N] = 0;
				}
			}
		}
		this->printm();
	}
	void printAnswer()
	{
		for (size_t i = 0; i < this->size_1M; i++)
		{
			cout << "X" << i << "=" << this->linkM[i][this->size_2M-1] << endl;
		}
	}
};