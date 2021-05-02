#include <iostream>
#include <cmath>

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

	void set_data()
	{
		T a;
		for (size_t i = 0; i < size; i++)
		{
			cin >> a;
			data[i] = a;
		}
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

template <typename Type>

class Matrix : public MyVec<MyVec<Type>>
{
protected:
    size_t size_column;
public:
    Matrix(){}

    Matrix(size_t _size_line, size_t _size_column) : MyVec<MyVec<Type>> {_size_line}
    {
        this->size = _size_line;
        size_column = _size_column;
		MyVec<Type> A {size_column};
        for (size_t i = 0; i < this->size; i++)
        {
            this->data[i] = A;
        }
    }

	void rand_set_matrix_double()
    {
		MyVec<Type> A {size_column};
        for (size_t i = 0; i < this->size; i++)
        {
            this->data[i] = A;
            this->data[i].rand_set_data_double();
        }
    }

    void set_matrix()
    {
        for (size_t i = 0; i < this->size; i++)
        {
            this->data[i].set_data();
        }
    }
    
    //Accepts the column number and line number from which the maximum element is searched.
    //Returns the number of the line with the maximum element in this column.
	size_t max_in_column_i_line(size_t column, size_t start)
    {
        Type MaxN = this->data[start][column];
        size_t j = start;
        for (size_t i = (start + 1); i < this->size; i++)
        {
            if (abs(MaxN) < abs(this->data[i][column]))
            {
                MaxN = this->data[i][column];
                j = i;
            }
        }
        return(j);
    }

	MyVec<Type> Gauss(MyVec<Type> X) // For type double, With an accuracy of 10^-8.
    {
		Matrix<Type> Copy = *this;
        if ((this->size == size_column) && (this->size == X.get_size()))
        {
            size_t MaxValuei;
            for (size_t i = 0; i < size_column; i++)
            {
                MaxValuei = max_in_column_i_line(i, i);
                Type MaxV =  this->data[MaxValuei][i];
                if (MaxValuei > i)
                    {
                        this->swap(MaxValuei, i);
                        X.swap(MaxValuei, i);
                    }
                MaxValuei = i;
                if (abs(MaxV) != 0)
                {
                    this->data[MaxValuei] /= MaxV;
                    X[MaxValuei] /= MaxV;
                    for (size_t j = 0; j < this->size; j++)
                    {
                        if (j != MaxValuei)
                        {
                            X[j] -= (X[MaxValuei]*this->data[j][i]);
                            this->data[j] -= (this->data[MaxValuei]*this->data[j][i]);
                        }
                    }
                }
                else
                {
                    cout << "More than one answer" << endl;
                    system("pause");
                    exit(1);
                }
            }
            for (size_t i = 0; i < X.get_size(); i++)
            {
                
                Type a = X[i];
                if (abs(a) < 0.00000001)
                {
                    X[i] = 0;
                } 
            }
			*this = Copy;
            return X;
        }
        else
        {
            cout << "Error size" << endl;
            system("pause");
            exit(0);
        }
    }

	void test(MyVec<Type> & X, MyVec<Type> & _X)
    {
        MyVec<double> X0{X};
        size_t T = 0;
        for(size_t j = 0; j < size_column; j++)
        {
            X0[j] = 0;
        }
        for(size_t i = 0; i < this->size; i++)
        {
            for(size_t j = 0; j < size_column; j++)
            {
                X0[i] += ((X[j])*(this->data[i][j]));
            }
        }
        for(size_t j = 0; j < size_column; j++)
        {
            double Nule = (X0[j]) - (_X[j]); //The difference if it is an error, or the inaccuracy if it is true.
            if (abs(Nule) < 0.00000001)
            {
                Nule = 0;
            }
            if(Nule != 0)
            {
                cout << "Error in" << j << " " << X0[j] << " " << _X[j] << " " << Nule << endl;
                T += 1;
            }
        }
        if(T == 0)
        {
            cout << "ok" << endl;
        }
        else
        {
            cout << "Error" << endl;
        }
    }

	void print_matrix()
    {
        for (size_t i = 0; i < this->size; i++)
        {
            cout << this->data[i];
        }
    }
};

int main()
{
    cout << "Enter the size of the matrix (m rows and n columns)" << endl;
    size_t m, n, check;
    cin >> m >> n;
    srand(m*n);
    Matrix<double> M0{m, n};
    cout << "1: Create a random matrix\n2: Enter the matrix(double)" << endl;
    cin >> check;
	if (check == 1)
    {
        M0.rand_set_matrix_double();
    }
    if (check == 2)
    {
        M0.set_matrix();
    }
    cout << "1: Print your matrix\n2: Don't print your matrix" << endl;
    cin >> check;
    if (check == 1)
    {
        cout << "Your matrix" << endl;
		M0.print_matrix();
    }
    cout << "1: Create a random vector of values\n2: Enter a vector of values" << endl;
    cin >> check;
    MyVec<double> X{m};
    if (check == 1)
    {
        X.rand_set_data_double();
    }
    if (check == 2)
    {
        X.set_data();
    }
    cout << "1: Print your vector of values\n2: Don't print your vector of values" << endl;
    cin >> check;
    if (check == 1)
    {
        cout << "Your vector of values" << endl;
        cout << X;
    }
    cout << "Solving a system of linear equations by the Gauss method" << endl;
	MyVec<double> XV = M0.Gauss(X);
    cout << XV;
    cout << "1: Test Gause\n2: End" << endl;
    cin >> check;
    if (check == 1)
    {
        cout << "Test" << endl;
        M0.test(XV, X);   
    }

    system("pause");
}
