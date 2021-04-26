#include <iostream>
using namespace std;
template <class T>
class vector
{
public:
	T* link, input; int size;
	vector<T>(int size1)
	{
		size = size1;
		input = 0;
		link = new T[size];
		for (int i = 0; i < (this->size); i++)
		{
			link[i] = 0;
		}
	}
	void fill_manually(vector A)
	{
		T* link1 = A.getlink();
		for (int i = 0; i < (this->size); i++)
		{
			cin >> input;
			link1[i] = input;
		}
	}
	void fill_randomly(vector A)
	{
		srand(time(NULL));
		T* link1 = A.getlink();
		for (int i = 0; i < (this->size); i++)
		{
			link1[i] = rand();
		}
	}
	int getsize() { return(size); }
	T* getlink() { return(link); }
	//~vector(){ delete[] link;}
	friend vector<T> operator + (vector& left, vector& right)
	{
		vector<T> temp(left.getsize());
		for (int i = 0; i < temp.size; i++)
		{
			temp.link[i] = 0;
			temp.link[i] = left.link[i] + right.link[i];
		}
		return(temp);
	}
	friend vector<T> operator - (vector& left, vector& right)
	{
		vector<T> temp(left.getsize());
		for (int i = 0; i < temp.size; i++)
		{
			temp.link[i] = 0;
			temp.link[i] = left.link[i] - right.link[i];
		}
		return(temp);
	}
	friend vector<T> operator * (T& left, vector& right)
	{
		vector temp(right.getsize());
		for (int i = 0; i < temp.size; i++)
		{
			temp.link[i] = 0;
			temp.link[i] = left * right.link[i];
		}
		return(temp);
	}
	friend vector<T> operator / (vector& left, T& right)
	{
		vector temp(left.getsize());
		for (int i = 0; i < temp.size; i++)
		{
			temp.link[i] = 0;
			temp.link[i] = (left.link[i]) / right;
		}
		return(temp);
	}
	//vector<T>& operator[](int i)	{if (i > size){			cerr << "Index out of range";			exit(0);		}		return link[i];}
	vector operator = (vector<T>* left)
	{
		this->size = left.size;	
		for (int i = 0; i < size; i++) 
		{ 
			this->link[i] = left.link[i]; 
		}
	}
	void print()
	{
		for (int i = 0; i < (this->size); i++) cout << this->link[i] << "		";
	}
};
template <class T>
class matrix :public vector<vector<T>>
{
public:
	matrix<T>(int size2):vector<vector<T>>(size2)
	{
		this->size = size2;
		this->link = new vector<vector<T>>(this->size);
		for (int i = 0; i < this->size; i++)
		{
			this->link[i] = new vector<T>(this->size);
		}
	}
	void printM(matrix a)
	{
		T b;
		for (int i = 0; i < a.getsize(); i++)
		{
			for (int j = 0; j < a.getsize(); j++)
			{
				b = this->link[i][j];
				cout << "link[" << i << "][" << j << "]=" << b << endl;
			}
		}
	}
};
int main()
{
	//vector<double> C(10), B(10), A(10);	vector<double> D(5);A.fill_manually(A);	B.fill_manually(B);	int a = 5;	double b = 4.5;	C = b * A;	cout << "C=";	C.print();	cout << "b=" << b << endl;	C = C / b;	//A = B - C;	cout << "C=";	C.print();	cout << endl; cout << "A=";	A.print();
	vector<int> B(2);
	matrix<int> A(10);
	//A.printM(A);

};