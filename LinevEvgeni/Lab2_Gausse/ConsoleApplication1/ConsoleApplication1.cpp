#include <iostream>
#include <cmath>
using namespace std;


template<typename T>
class Vector
{
private:
	int size;
	T* data;
public:
	Vector()
	{
		size = 0;
		data = NULL;
	}

	Vector(int size_)
	{
		size = size_;
		data = new T[size];
	}

	Vector(const Vector& second)
	{
		data = new T[second.size];
		size = second.size;
		for (int i = 0; i < size; i++)
			data[i] = second.data[i];
	}
	~Vector()
	{
		delete[] data;
		data = NULL;
		size = 0;
	}

	T& operator [] (int i)
	{
		return data[i];
	}
	
	Vector operator * (int c)
	{
		Vector v(*this);
		if (v.data == NULL)
			exit(1);
		else
		{
			for (int i = 0; i < v.size; i++)
				v[i] = v[i] * c;
			return v;
		}
	}

	T operator *( const Vector& second)
	{		
		T res = (T)0;
		if (this->size != second.size || this->data==NULL || second.data == NULL)
		{
			exit(1);
		}
		else
		{
			for (int i = 0; i < second.size; i++)
				res += this->data[i] * second.data[i];
			return res;
		}
	}

	Vector operator + (const Vector& second)
	{
		if (this->size != second.size || this->data == NULL || second.data == NULL)
			exit(1);
		else
		{
			for (int i = 0; i < size; i++)
				this->data[i] = this->data[i] + second.data[i];
			return *this;
		}
	}

	Vector operator - (const Vector& second)
	{
		if (this->size != second.size || this->data == NULL || second.data == NULL)
			exit(1);
		else
		{
			for (int i = 0; i < size; i++)
				this->data[i] = this->data[i] - second.data[i];
			return *this;
		}
	}

	Vector& operator = (const Vector& v)
	{
		size = v.size;
		data = v.data;
		return *this;
	}

	friend istream& operator >> (istream& ist, Vector& v)
	{
		for (int i = 0; i < v.size; i++)
			ist >> v.data[i];
		return ist;
	}

	friend ostream& operator << (ostream& ost, const Vector& v)
	{
		for (int i = 0; i < v.size; i++)
			ost << v.data[i] <<' ' ;
		cout << endl;
		return ost;
	}

	int getSize() const
	{
		return size;
	}

	void setSize(int s)
	{
		if (s == size)
			return;
		if (s == 0)
		{
			if (data != NULL)
			{
				delete[] data;
				size = 0;
				data = NULL;				
			}
			return;
		}
		if (s < size)
		{
			T* tmp;
			tmp = new T[s];
			for (int i = 0; i < s; i++)
				tmp[i] = data[i];
			delete[] data;
			data = tmp;
			size = s;
			return;
		}
		if (s > size)
		{
			T* tmp;
			tmp = new T[s];
			for (int i = 0; i < size; i++)
				if (data != NULL)
				 tmp[i] = data[i];
			for (int i = size; i < s; i++)
				tmp[i] = 0;
			if (data!=NULL)
			delete[] data;
			size = s;
			data = tmp;
			return;
		}
	}
};

template<template <typename> typename Vector, typename T>
class Matrix
{
protected:
	int size;
    Vector<Vector<T>> data;
public:
	Matrix()
	{
		size = 0;
	}
	Matrix(int size_) : size(size_), data(size_)
	{
		for (int i = 0; i < size; i++)
			data[i].setSize(size);
	}
	Matrix(const Matrix& second)
	{
		if (size != second.size)
		{
			data.setSize(second.size);
			for (int i = 0; i < size; i++)
				data[i].setSize(second.size);
			size = second.size;
		}
		for (int j = 0; j < size; j++)
		 for (int i = 0; i < size; i++)
			data[j][i] = second.data[j][i];
	}

	~Matrix()
	{}

	friend istream& operator >> (istream& ist, Matrix& m)
	{
		for (int j = 0; j < m.size; j++)
		{
			for (int i = 0; i < m.size; i++)
			{
				ist >> m.data[j][i];
				
			}
			
		}
		return ist;
	}

	friend ostream& operator << (ostream& ost, Matrix& m)
	{
		for (int j = 0; j < m.size; j++)
		{
			for (int i = 0; i < m.size; i++)
			{
				ost << m.data[j][i] << ' ';
			}
			cout << endl; 
		}
		return ost;
	}

	void Random()
	{
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				data[i][j] = rand()%10;
	}
};

template<template <typename> typename Vector, typename T>
class MatrixGausse : public Matrix <typename Vector, typename T>
{
public:	
	MatrixGausse():Matrix<Vector,T>()
	{};

	MatrixGausse(int size_) :Matrix<Vector,T>(size_)
	{
	};

	MatrixGausse(const MatrixGausse& second):Matrix<Vector,T>(second)
	{};

	~MatrixGausse()
	{};

	void Gauss(Vector<T> b)
	{
		T c;
		T d;
		for (int j = 0; j < this->size; j++)
		{
			T prov = this->data[j][j];
			for (int i = j; i < this->size; i++)
				if ((abs(this->data[i][j]) - abs(this->data[j][j])) > 1e-6)
				{
					for (int k = j; k < this->size; k++)
					{
						c = this->data[j][k];
						this->data[j][k] = this->data[i][k];
						this->data[i][k] = c;
					}
					c = b[j];
					b[j] = b[i];
					b[i] = c;
				}
			if (this->data[j][j] != 0)
			{
				T tmp = this->data[j][j];
				for (int i = 0; i < this->size; i++)
					this->data[j][i] = this->data[j][i] / (tmp);
				b[j] = b[j] / (tmp);
				for (int i = 0; i < this->size; i++)
				{
					if (i != j && this->data[i][j] != 0)
					{
						T tmp2 = this->data[i][j];
						for (int k = j; k < this->size; k++)
						{
							c = this->data[j][k];
							this->data[j][k] = this->data[j][k] * tmp2;
							if (abs(abs(this->data[i][k]) - abs(this->data[j][k])) > 1e-6)
								this->data[i][k] = this->data[i][k] - this->data[j][k];
							else
								this->data[i][k] = 0;
							this->data[j][k] = c;
						}
						d = b[j];
						b[j] = b[j] * tmp2;
						if (abs(abs(b[i]) - abs(b[j])) > 1e-6)
							b[i] = b[i] - b[j];
						else
							b[i] = 0;
						b[j] = d;
					}
				}
			}
		}

		int p = 0;
		int k = 0;
		for (int i = 0; i < this->size; i++)
			if (this->data[i][i] == 0)
			{
				for (int j = 0; j < this->size; j++)
					if (this->data[i][j] == 0)
						p = p + 1;
				if (p == this->size && b[i] != 0)
				{
					cout << " К сожалению, решений нет";
					exit(0);
				}
				if (p == this->size && b[i] == 0)
					k = 1;
			}
		if (k == 1)
		{
			cout << "К счастью, решений бесконечно много";
			exit(0);
		}
		cout << b;
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Введите размер матрицы"<< endl;
	int sizevec;
	int t;
	cin >> sizevec;
	MatrixGausse <Vector, double> a(sizevec);
	Vector <double> b(sizevec);	
	cout << "Выберите вариант"<< endl <<"1. Я хочу сгенерировать случайную матрицу"<<endl<<"2. Я хочу задать свою матрицу"<<endl;
	cin >> t;
	switch (t)
	{
	case 1:
		a.Random();
		cout <<"Это ваша матрица"<<endl<< a;
		break;
	case 2: 
		cin >> a;
		break;
	}
	cout << "Введите правую часть" << endl;
	cin >> b;
	cout << "Искомый вектор" << endl;
    a.Gauss(b);
	
}