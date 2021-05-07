#include <iostream>
#include <cmath>

using namespace std;

template <typename T>
class vector
{
protected:
    size_t size;
    T* data;
public:
    vector()
    {
        size = 0;
        data = nullptr;
    }
    vector(size_t size)
    {
        this->size = size;
        if (size == 0)
        {
            data = nullptr;
        }
        else
        {
            data = new T[size];
        }
    }
    vector(const vector& orig)
    {
        size = orig.size;
        data = new T[size];
        for (size_t i = 0; i < size; i++)
        {
            data[i] = orig[i];
        }
    }
    ~vector()
    {
        delete[] data;
    }
    T& operator [](size_t i) const
    {
        return(data[i]);
    }
    vector& operator =(const vector& second)
    {
        if (second.size > size)
        {
            resize(second.size);
        }
        for (size_t i = 0; i < second.size; i++)
        {
            data[i] = second[i];
        }
        return (*this);
    }
    vector operator * (T a)
    {
        vector<T> result = vector<T>(size);
        for (size_t i = 0; i < size; i++)
        {
            result[i] = data[i] * a;
        }
        return(result);
    }
    vector& operator -= (const vector& second)
    {
        if (second.size > size)
        {
            resize(second.size);
        }
        for (size_t i = 0; i < second.size; i++)
        {
            data[i] -= second[i];
        }
        return (*this);
    }
    vector& operator /= (T a)
    {
        for (size_t i = 0; i < size; i++)
        {
            data[i] /= a;
        }
        return (*this);
    }
    size_t getsize()
    {
        return(size);
    }
    void setdata()
    {
        T a;
        for (size_t i = 0; i < size; i++)
        {
            cin >> a;
            data[i] = a;
        }
    }
    void resize(size_t size2)
    {
        if (size2 > size)
        {
            T* data2;
            data2 = new T[size2];
            for (size_t i = 0; i < size; i++)
            {
                data2[i] = data[i];
            }
            for (size_t i = size; i < size2; i++)
            {
                data2[i] = 0;
            }
            delete[] data;
            data = data2;
        }
        size = size2;
    }
    void swap(size_t i, size_t j)
    {
        T tmp;
        tmp = data[i];
        data[i] = data[j];
        data[j] = tmp;
    }
};

template <typename U>
ostream& operator << (ostream& ost, vector<U>& vec)
{
    size_t size = vec.getsize();
    for (size_t i = 0; i < (size - 1); i++)
    {
        ost << vec[i] << " ";
    }
    ost << vec[size - 1] << endl;
    return ost;
}

template <typename V>
class matrix : public vector<vector<V>>
{
protected:
    size_t width;
public:
    matrix() {}
    matrix(size_t height, size_t width) : vector<vector<V>>{ height }
    {
        this->size = height;
        this->width = width;
        vector<V> tmp = vector<V>(width);
        for (size_t i = 0; i < this->size; i++)
        {
            this->data[i] = tmp;
        }
    }
    void setmatrix()
    {
        for (size_t i = 0; i < this->size; i++)
        {
            this->data[i].setdata();
        }
    }
    size_t collmax(size_t j0, size_t i0)
    {
        V max = this->data[i0][j0];
        size_t j = i0;
        for (size_t i = (i0 + 1); i < this->size; i++)
        {
            if (abs(max) < abs(this->data[i][j0]))
            {
                max = this->data[i][j0];
                j = i;
            }
        }
        return(j);
    }
    void printmat()
    {
        for (size_t i = 0; i < this->size; i++)
        {
            cout << this->data[i];
        }
    }
};

class SLAU : public matrix<double>
{
private:
    vector<double> VOV;
public:
    SLAU(size_t height) : matrix(height, height)
    {
        VOV = vector<double>(height);
    }
    void setVOV()
    {
        VOV.setdata();
    }
    vector<double> gaussSolve()
    {
        size_t indmax;
        for (size_t i = 0; i < width; i++)
        {
            indmax = collmax(i, i);
            double max = this->data[indmax][i];
            if (indmax > i)
            {
                this->swap(indmax, i);
                VOV.swap(indmax, i);
            }
            indmax = i;
            if (abs(max) != 0)
            {
                this->data[indmax] /= max;
                VOV[indmax] /= max;
                for (size_t j = 0; j < this->size; j++)
                {
                    if (j != indmax)
                    {
                        VOV[j] -= (VOV[indmax] * this->data[j][i]);
                        this->data[j] -= (this->data[indmax] * this->data[j][i]);
                    }
                }
            }
        }
        for (size_t i = 0; i < this->size; i++)
        {
            if (this->data[i][i] == 0)
            {
                if (VOV[i] == 0)
                    cout << "More than one solutions" << endl;
                else cout << "No solution" << endl;
                exit(1);
            }
        }
        for (size_t i = 0; i < VOV.getsize(); i++)
        {
            double a = VOV[i];
            if (abs(a) < 0.00000001)
            {
                VOV[i] = 0;
            }
        }
        return VOV;
    }
    vector<double> gaussSolve2(vector<double> vec)
    {
        VOV = vec;
        return gaussSolve();
    }
};

int main()
{
    cout << "Size of the matrix: ";
    size_t height;
    cin >> height;
    SLAU M = SLAU(height);
    cout << "Enter the matrix" << endl;
    M.setmatrix();
    cout << "Your matrix:" << endl;
    M.printmat();
    cout << "Enter vector of value:" << endl;
    vector<double> X = vector<double>(height);
    X.setdata();
    cout << "Oh great gods, solve this matrix for me!!!" << endl;
    vector<double> Sol = M.gaussSolve2(X);
    cout << Sol;
    cout << "IT JUST WORKS!!!";
    return 0;
}

/*{
    int main()
    {
        cout << "Size of the matrix: ";
        size_t height;
        cin >> height;
        SLAU M = SLAU(height);
        cout << "Enter the matrix" << endl;
        M.setmatrix();
        cout << "Your matrix:" << endl;
        M.printmat();
        cout << "Enter vector of value:" << endl;
        M.setVOV();
        cout << "Oh great gods, solve this matrix for me!!!" << endl;
        vector<double> Solve = M.gaussSolve();
        cout << Solve;
        cout << "IT JUST WORKS!!!";
        return 0;
    }
}*/