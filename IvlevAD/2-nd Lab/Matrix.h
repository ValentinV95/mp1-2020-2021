#pragma once

using namespace std;

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

	MyVec<Type> Gauss(MyVec<Type> X, int StepByStep) // For type double, With an accuracy of 10^-8.
    //If StepByStep != 1 step-by-step solution
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
                    if (StepByStep != 2)
                    {
                        cout << "Matrix Gauss step " << i << endl;
                        cout << *this;
                        cout << "Vector of values" << endl;
                        cout << X;
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

	void test(MyVec<Type> & X, MyVec<Type> & _X) // X solution vector, _X vector of values
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

    Matrix operator * (Type sec)
	{
		Matrix<Type> A{ this->size, size_column };
		for (size_t i = 0; i < this->size; i++)
		{
			A[i] = ((*this)[i] * sec);
		}
		return(A);
	}

    Matrix& operator /= (Type sec)
	{
		for (size_t i = 0; i < this->size; i++)
		{
			(*this)[i] /= sec;
		}
		return (*this);
	}
};

template <typename U>

istream& operator >> (istream& ist, Matrix<U> & sec)
{
    for (size_t i = 0; i < sec.get_size(); i++)
    {
        ist >> sec[i];
    }
    return ist;
}

template <typename U>

ostream& operator << (ostream& ost, Matrix<U> & sec)
{
    for (size_t i = 0; i < sec.get_size(); i++)
    {
        ost << sec[i];
    }
    return ost;
}