#include <iostream>
#include <ctime>
#include <iomanip>

const double MIN = 1e-9;

using namespace std;

template<typename T>
T _abs(T element)
{
	if (element < 0) { element *= -1; }

	return element;

}

template<typename T>
T Evklid(T a, T b) {

	if (a == b) {
		return a;
	}

	if (a > b) {
		T tmp = a;
		a = b;
		b = tmp;
	}

	Evklid(a, b - a);
}


template <typename T>
class Vector
{
protected:
	T* data;
	size_t size;
public:
	Vector() { this->size = 0; data = nullptr; }

	Vector(size_t _size)
	{
		

		size = _size;
		data = new T[size];
	}

	Vector(const Vector& second)
		: size(second.size)
		, data(new T[second.size])
	{
		for (int i = 0; i < second.size; i++)
		{
			data[i] = second.data[i];
		}
	}

	

	Vector(size_t _size, const T& elems) :
		size(_size)
	{
		
	
		this->data = new T[_size];
	
		for (size_t i = 0; i < size; i++)
		{
			data[i] = elems;
		}
	}
	
	~Vector() { delete[] data; }


	T& operator[](size_t index)
	{
		
		return data[index];
	}

	const T& operator[](size_t index) const
	{
		return data[index];
	}

	int getSize() const { return size; }

	T* getData(size_t index)
	{
		return data[index];
	}

	Vector& operator=(const Vector& Val)
	{
		if (size != Val.size)
		{
			
			delete[] data;
			data = nullptr;
			size = 0;
			data = new T[Val.size];
			size = Val.size;

			
		}

		for (size_t i = 0; i < size; i++)
		{
			this->data[i] = Val.data[i];
		}
		return *this;

	}

	bool operator != (const Vector& second)
	{
		

		if (size == second.size)
		{
			for (size_t i = 0; i < size; i++)
			{
				if (_abs(data[i] - second.data[i]) > MIN)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
		else
		{
			return false;
		}
	}

	void swap(int& a, int& b)
	{
		if (a != b)
		{
			T tmp = this->data[a];
			this->data[a] = this->data[b];
			this->data[b] = tmp;
		}

	}

	void resize(size_t _size)
	{
		if (size != _size)
		{
			delete[] this->data;
			this->data = new T[_size];
			this->size = _size;
		}
	}

	


	Vector<T>& operator+=(const Vector<T> a)
	{
		if (this->size == a.size)
		{
			for (int i = 0; i < this->size; i++)
			{
				this->data[i] += a[i];
			}
		}

		return *this;
	}

	Vector<T>& operator/= (const T a)
	{
		for (int i = 0; i < size; i++)
		{
			data[i] /= a;
		}

		return *this;
	}

	friend Vector<T> operator*(const Vector<T>& A, T B)
	{
		Vector<T> result(A.size);
		for (int i = 0; i < A.getSize; i++)
		{
			result[i] = A[i] * B;
		}

		return result;
	}

	friend Vector operator*(T B, const Vector& A)
	{
		Vector<T> result(A.size);
		for (int i = 0; i < A.size; i++)
		{
			result[i] = A[i] * B;
		}

		return result;
	}

	template <typename T>
	friend ostream& operator<< (ostream& out,const Vector<T>& V);


	template <typename T>
	friend istream& operator>> (istream& in, Vector<T>& V);

};


template <typename T>
ostream& operator<< (ostream& out, const Vector<T>& V)
{
	for (size_t i = 0; i < V.size; i++)
	{
		out << V[i] << ' ';
	}
	cout << endl;
	return out;
}



template <typename T>
istream& operator>> (istream& in, Vector<T>& V)
{
	

	for (size_t i = 0; i < V.size; i++)
	{
		in >> V[i];
	}

	return in;
}




template <typename T>
class Matrix : public Vector <Vector<T>>
{
private:
	T s;

	int maxIndexInCol(int index)
	{
		int maxAbs = index;

		for (int i = index+1; i < this->size; i++)
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
					this->data[i][j] = this->data[i][j+1] / this->data[i][j];
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
		Vector<Vector<T>> (h, Vector<T>(w, val))
	{
	}

	
	~Matrix()
	{}


	void RandomElements()
	{
		for (size_t i = 0; i < this->size; i++)
		{
			for (size_t j = 0; j < this->size+1; j++)
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

		for (size_t i = 0; i < this->size; i++)
		{
			int max = maxIndexInCol(i);
			swapRow(max, i);

			for (int row = i + 1; row < this->size; row++)
			{
				if (row != i && this->data[row][i] != 0) {
					T mnozhitel = (this->data[row][i]) / (this->data[i][i]);

					for (int k = i; k < this->size+1; k++)
					{

						this->data[row][k] -= (this->data[i][k]) * mnozhitel;
						if (this->data[row][k] < MIN)
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
			for (size_t j = this->size-1; j > i; j--)
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

void Check()
{
	int u_size;

	cout << "    Enter the number of unknowns: ";
	cin >> u_size;
	cout << "\n\n\n";

	Matrix<double> b(u_size, u_size + 1, 1);
	Vector<double> X(u_size, 0);

	b.RandomElements();
	cout << "    The original system of linear equations\n\n";
	b.LinearSystem();

	cout << "\n\n\n";

	b.GaussMethod(X);
	cout << "    The system of linear equations in the reduced form\n\n";
	b.LinearSystem();

	cout << "\n\n\n      Linear equation system solution: \n\n";

	for (size_t i = 0; i < u_size; i++)
	{
		cout << "X" << i + 1 << "\t=\t" << X[i] << endl;
	}

	Vector<double> k(u_size, 0);

	cout << "\n\n    Substitute the resulting values into the original system\n\n";

	for (size_t i = 0; i < u_size; i++)
	{
		for (int j = 0; j < u_size; j++)
		{
			k[i] += b[i][j] * X[j];
		}
	}

	for (size_t i = 0; i < u_size; i++)
	{
		cout << k[i] << "  =  " << b[i][u_size] << endl;
	}
}

void RandomNumberGauss()
{
	int u_size;

	cout << "    Enter the number of unknowns: ";
	cin >> u_size;
	cout << "\n\n\n";

	Matrix<double> b(u_size, u_size+1, 1);
	Vector<double> X(u_size, 0);

	b.RandomElements();
	cout << "    The original system of linear equations\n\n";
	b.LinearSystem();

	cout << "\n\n\n";

	b.GaussMethod(X);
	
	cout << "    The system of linear equations in the reduced form\n\n";
	b.LinearSystem();

	
	cout << "\n\n\n      Linear equation system solution: \n\n";

	for (size_t i = 0; i < u_size; i++)
	{
		cout << "X" << i+1 << "\t=\t" << X[i] << endl;
	}
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

void userValues()
{
	size_t u_size;

	cout << "    Enter the number of unknowns: ";
	cin >> u_size;

	

	Matrix<double> b(u_size, u_size + 1, 1); 
	Vector<double> X(u_size, 0);

	for (size_t i = 0; i < b.getSize(); i++)
	{
		cout << "\n    Enter the coefficients of the unknowns in the " << i + 1 << " line separated by a space \n";
		cout << "    After entering the items, press the Enter\n\n";

		for (int j = 0; j < b.getSize(); j++)
		{
			cin >> b[i][j];
		}

		cout << "\n    Enter the value of the intercept on line " << i + 1 << endl;
		cout << "    After entering the items, press the Enter\n\n";
		cin >> b[i][b.getSize()];
	}

	cout << endl;
	

	cout << "     The original system of linear equations\n\n";
	b.LinearSystem();

	cout << "\n\n\n";

	b.GaussMethod(X);
	b.Alignment();


	cout << "     The system of linear equations in the reduced form\n\n";
	b.LinearSystem();

	cout << "\n\n\n    Linear equation system solution: \n\n";

	for (size_t i = 0; i < u_size; i++)
	{
		cout << "X" << i+1 << "\t=\t" << X[i] << endl;
	}
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}


void logic()
{
	int a;
	
	cout << " 1. Apply Gaussian method for a matrix with random numbers\n";
	cout << " 2. Apply Gaussian method for matrix with custom numbers\n";
	cout << " 3. Check if the Gaussian method is working correctly\n\n";

	cout << "    Select the appropriate option, enter the number and press enter... ";
	cin >> a;
	cout << "\n\n";

	switch (a)
	{
	case 1:
		RandomNumberGauss();
		break;

	case 2:
		userValues();
		break;

	case 3:
		Check();
		break;
	default:
		cout << "    Unfortunately this command does not exist!\n";
		cout << "    Please, choose another option from the list below:\n\n";
		logic();

	}

}



int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(0));
	cout << "\t\t----------------------------------------------------------------------------\n";
	cout << "\t\t|A program for solving a system of linear equations by the Gaussian method |\n";
	cout << "\t\t----------------------------------------------------------------------------\n\n";
	cout << "    What do you want to do? \n\n";
	
	logic();

	return 0;
}
