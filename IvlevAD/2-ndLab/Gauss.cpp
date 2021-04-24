#include <iostream>
#include <cmath>

using namespace std;

template <typename T>

class MyVector
{
protected:
    size_t size;
    T *data;
public:
    size_t get_size()
    {
        return size;
    }

    T& get_data_i(size_t i)
    {
        return(data[i]);
    }

    void set_data_i(size_t i, T a)
    {
        data[i] = a; 
    }

    void set_data()
    {
        for (size_t i = 0; i < size; i++)
        {
            T a;
            cin >> a;
            data[i] = a;
        }
    }

    void random_set_data()
    {
        for (size_t i = 0; i < size; i++)
        {
            T a = (T) ((rand() / 10.0) - (rand() / 20.0));
            data[i] = a;
        }
    }

    MyVector()
    {
        size = 0;
        data = nullptr;
    }

    MyVector(size_t _size)
    {
        size = _size;
        data = new T [size];
    }

    MyVector(MyVector & second)
    {
        size = second.get_size();
        data = new T [size];
        for (size_t i = 0; i < size; i++)
        {
            data[i] = second.get_data_i(i);
        }
    }

    void print_vector()
    {
        for (size_t i = 0; i < size; i++)
        {
            cout << data[i] << " ";
        }
        cout << endl;
    }

    MyVector & operator=(MyVector second)
    {
        if (size == 0)
        {
            size = second.get_size();
            data = new T [size];
            for (size_t i = 0; i < size; i++)
            {
                data[i] = second.get_data_i(i);
            }
        }
        else
        {
            if (size == second.get_size())
            {
                size = second.get_size();
                for (size_t i = 0; i < size; i++)
                {
                    data[i] = second.get_data_i(i);
                }
            }
            else
            {
                cout << "Error size" << endl;
            }
        }
        return *this;
    }

    MyVector<T>& operator /=(T M)
    {
        for (size_t i = 0; i < size; i++)
        {
            data[i] /= M;
        }
        return *this;
    }

    MyVector & operator -=(MyVector second)
    {
        for (size_t i = 0; i < size; i++)
        {
            data[i] -= second.get_data_i(i);
        }
        return *this;
    }

    MyVector<T> operator *(T M)
    {
        MyVector C{size};
        for (size_t i = 0; i < size; i++)
        {
            C.data[i] = this->data[i] * M;
        }
        return C;
    }

    MyVector<T>& operator *=(T M)
    {
        for (size_t i = 0; i < size; i++)
        {
            data[i] *= M;
        }
        return *this;
    }

    void swap(size_t i, size_t j)
    {
        T C;
        C = data[i];
        data[i] = data[j];
        data[j] = C;
    }

    ~MyVector()
    {
        delete [] data;
    }
};

template <typename U>

ostream& operator << (ostream& ost, MyVector<U> & second)
{
    for (size_t i = 0; i < second.get_size(); i++)
    {
        ost << second.get_data_i(i) << endl;
    }
    return ost;
}

template <typename Type>

class Matrix : public MyVector<MyVector<Type>>
{
protected:
    size_t size_column;
public:
    Matrix(){}

    Matrix(size_t _size_line, size_t _size_column) : MyVector<MyVector<Type>> {_size_line}
    {
        this->size = _size_line;
        size_column = _size_column;
        MyVector<Type> A {size_column};
        for (size_t i = 0; i < this->size; i++)
        {
            this->data[i] = A;
            this->data[i].random_set_data();
        }
    }

    size_t get_size_column()
    {
        return(size_column);
    }

    void set_matrix()
    {
        for (size_t i = 0; i < this->size; i++)
        {
            this->data[i].set_data();
        }
    }

    size_t max_in_column_i_line(size_t column, size_t start)
    {
        Type MaxN = this->data[start].get_data_i(column);
        size_t j = start;
        for (size_t i = (start + 1); i < this->size; i++)
        {
            if (abs(MaxN) < abs(this->data[i].get_data_i(column)))
            {
                MaxN = this->data[i].get_data_i(column);
                j = i;
            }
        }
        return(j);
    }

    void test(MyVector<Type> & X, MyVector<Type> & _X)
    {
        MyVector<double> X0{X};
        size_t T = 0;
        for(size_t j = 0; j < size_column; j++)
        {
            X0.get_data_i(j) = 0;
        }
        for(size_t i = 0; i < this->size; i++)
        {
            for(size_t j = 0; j < size_column; j++)
            {
                X0.get_data_i(i) += ((X.get_data_i(j))*(this->data[i].get_data_i(j)));
            }
        }
        for(size_t j = 0; j < size_column; j++)
        {
            double Nule = (X0.get_data_i(j)) - (_X.get_data_i(j));
            if (abs(Nule) < 0.00000001)
            {
                Nule = 0;
            }
            if(Nule != 0)
            {
                cout << "Error in" << j << " " << X0.get_data_i(j) << " " << _X.get_data_i(j) << " " << Nule << endl;
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
            this->data[i].print_vector();
        }
    }

    MyVector<Type> Gauss(MyVector<Type> & X) // For type double, With an accuracy of 10^-8.
    {
        if ((this->size == size_column) && (this->size == X.get_size()))
        {
            size_t MaxValuei;
            MyVector<Type> Copy;
            for (size_t i = 0; i < get_size_column(); i++)
            {
                MaxValuei = max_in_column_i_line(i, i);
                Type MaxV =  this->data[MaxValuei].get_data_i(i);
                if (MaxValuei > i)
                    {
                        this->swap(MaxValuei, i);
                        X.swap(MaxValuei, i);
                    }
                MaxValuei = i;
                if (abs(MaxV) != 0)
                {

                    this->data[MaxValuei] /= MaxV;
                    X.get_data_i(MaxValuei) /= MaxV;
                    for (size_t j = 0; j < this->size; j++)
                    {
                        if (j != MaxValuei)
                        {
                            Copy = this->data[MaxValuei];
                            Type C = X.get_data_i(MaxValuei);
                            C *= this->data[j].get_data_i(i);
                            X.get_data_i(j) -= C;
                            Copy *= this->data[j].get_data_i(i);
                            this->data[j] -= Copy;
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
                
                Type a = X.get_data_i(i);
                if (abs(a) < 0.00000001)
                {
                    X.set_data_i(i, 0);
                } 
            }
            return X;
        }
        else
        {
            cout << "Error size" << endl;
            system("pause");
            exit(0);
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
    if (check == 2)
    {
        M0.set_matrix();
    }
    Matrix<double> M{M0};
    cout << "1: Print your matrix\n2: Don't print your matrix" << endl;
    cin >> check;
    if (check == 1)
    {
        cout << "Your matrix" << endl;
        M0.print_matrix();
    }
    cout << "1: Create a random vector of values\n2: Enter a vector of values" << endl;
    cin >> check;
    MyVector<double> X{m};
    if (check == 1)
    {
        X.random_set_data();
    }
    if (check == 2)
    {
        X.set_data();
    }
    MyVector<double> X0{X};
    cout << "1: Print your vector of values\n2: Don't print your vector of values" << endl;
    cin >> check;
    if (check == 1)
    {
        cout << "Your vector of values" << endl;
        X.print_vector();
    }
    cout << "Solving a system of linear equations by the Gauss method" << endl;
    M0.Gauss(X).print_vector();
    cout << "1: Test Gause\n2: End" << endl;
    cin >> check;
    if (check == 1)
    {
        cout << "Test" << endl;
        M.test(X, X0);   
    }

    system("pause");
}