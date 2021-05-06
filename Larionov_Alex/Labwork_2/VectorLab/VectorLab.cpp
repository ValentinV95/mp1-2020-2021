#include <iostream>
using namespace std;
template <class T>
class vector
{
public:
	T** link, input; size_t size_1, size_2; size_t v = 1;
	vector()
	{ 
		 link = nullptr; 
	};
	vector<T>(size_t size1, size_t size2)
	{
		size_1 = size1;
		size_2 = size2;
		input = 0;
		link = new T*[size_1];
		for (size_t i = 0; i < this->size_1; i++)
		{
			link[i] = new T[size_2];
		}
		for (size_t i = 0; i < (this->size_1); i++)
		{
			for (size_t j = 0; j < this->size_2; j++)
			{
				link[i][j] =0;
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
	/*void setlink_manual()
	{
		for(size_t i=0; i<this->size;i++)
		cin >> this->link[i];
	}*/
	//~vector(){ delete[] link;}
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
	vector<T> A{};
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
	}
};
int main()
{
	/*
	vector<int> A(2, 2), B(2, 2), C(2, 2);
	A.fill_manually(A); B.fill_manually(B);
	A.print(); B.print();
	cout << "Сложение А+В" << endl;
	C = A + B;
	C.print();	A.print(); B.print();
	cout << "Разность B-C" << endl;
	A = B - C;
	C.print();	A.print(); B.print();
	cout << "Произведение 2*B" << endl;
	A = 2 * B; 
	C.print();	A.print(); B.print();
	cout << "Деление 2B/2" << endl;
	B=A/2;
	C.print();	A.print(); B.print();*/
	matrix<int> M(5);
	M.fill_manually();
	//M.printm();
};