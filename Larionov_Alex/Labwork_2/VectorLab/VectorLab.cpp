#include <iostream>
using namespace std;
template <class T>
class vector
{
public:
	T* link, input; size_t size;
	vector<T>() { size = 0; link = 0; input = 0; };
	vector<T>(size_t size1)
	{
		size = size1;
		input = 0;
		link = new T[size];
	}
	void fill_manually(vector A)
	{
		for (size_t i = 0; i < (this->size); i++)
		{
			cin >> input;
			A.link[i] = input;
		}
	}
	void fill_randomly(vector A)
	{
		srand(time(NULL));
		for (size_t i = 0; i < (this->size); i++)
		{
			A.link[i] = rand();
		}
	}
	size_t getsize() { return(size); }
	T& getlink(size_t i) { return(link[i]); }
	void setlink_manual(size_t i)
	{
		cin >> this->link[i];
	}
	//~vector(){ delete[] link;}
	friend vector<T> operator + (vector& left, vector& right)
	{
		vector<T> temp(left.size);
		for (size_t i = 0; i < temp.size; i++)
		{
			temp.link[i] = 0;
			temp.link[i] = left.link[i] + right.link[i];
		}
		return(temp);
	}
	friend vector<T> operator - (vector& left, vector& right)
	{
		vector<T> temp(left.size);
		for (size_t i = 0; i < temp.size; i++)
		{
			temp.link[i] = 0;
			temp.link[i] = left.link[i] - right.link[i];
		}
		return(temp);
	}
	friend vector<T> operator * (T& left, vector& right)
	{
		vector temp(right.size);
		for (size_t i = 0; i < temp.size; i++)
		{
			temp.link[i] = 0;
			temp.link[i] = left * right.link[i];
		}
		return(temp);
	}
	friend vector<T> operator / (vector& left, T& right)
	{
		vector temp(left.size);
		for (size_t i = 0; i < temp.size; i++)
		{
			temp.link[i] = 0;
			temp.link[i] = (left.link[i]) / right;
		}
		return(temp);
	}
	vector<T>& operator = (vector right)
	{
		vector<T> temp(right.size);
		for (size_t i = 0; i < temp.size; i++)
		{
			temp.link[i] = right.link[i];
		}
		return(temp);
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
	matrix<T>(size_t size1)
	{
		this->size = size1;
		vector<T> A(this->size);
		for(size_t i=0; i<this->size; i++)
		{
			this->link[i] = A;
		}
	}
	void printm()
	{
		for (size_t i = 0; i < this->size; i++)
		{
			this->link[i].print();
		}
	}
	void fillm_manuall()
	{
		for(size_t i=0; i< this->size; i++)
		{
			this->link[i].setlink_manuall(i);
		}
	}
};
int main()
{
	matrix<int> A(5);
	A.fillm_manuall();
	A.printm();
};