#include <iostream>
#include <math.h>
#include <algorithm>
#include <string>
#include <ctime>
using namespace std;
template <typename T>
class Vector {
protected:
public:
    T* vector;
    size_t size;
public:
    T GetElement(size_t num) {
        return vector[num];
    }
    void ScanSize() { 
        cin >> size;
    }
    void Random() {  
        for (size_t i = 0; i < size; i++) {
            vector[i] = rand();
        }
    }
    void PrintVector() {
        for (size_t i = 0; i < size; i++)
            cout << vector[i] << "   ";
        cout << endl;
    }
    T& GetVector(size_t num) {
        return vector[num];
    }
    void Swap(size_t first, size_t second) { 
        T tmp = vector[first];
        vector[first] = vector[second];
        vector[second] = tmp;
    }
    Vector() { size = 0; vector = nullptr; }
    Vector(size_t ssize) {
        size = ssize;
        vector = new T[size];
    }
    Vector(Vector& tmp) {
        size = tmp.size;
        vector = new T[size];
        for (size_t i = 0; i < size; i++)
            vector[i] = tmp.vector[i];
    }
    Vector& operator =(Vector tmp) {
        if (size == tmp.size) {
            size = tmp.size;
            for (size_t i = 0; i < size; i++)
                vector[i] = tmp.vector[i];
        }
        else if (size == 0) {
            size = tmp.size;
            vector = new T[size];
            for (size_t i = 0; i < size; i++)
                vector[i] = tmp.vector[i];
        }
        return *this;
    }
    Vector<T>& operator *=(T second) {
        for (size_t i = 0; i < size; i++)
            vector[i] *= second;
        return*this;
    }
    Vector<T>& operator /=(T second) {
        for (size_t i = 0; i < size; i++)
            vector[i] /= second;
        return*this;
    }
    Vector& operator -=(Vector second) {
        for (size_t i = 0; i < size; i++)
            vector[i] -= second.vector[i];
        return*this;
    }
    ~Vector() {
        delete[]vector;
    }
};

template<typename T2>
ostream& operator <<(ostream& ost, Vector<T2>& tmp) {
    for (size_t i = 0; i < tmp.size; i++)
        ost << tmp.vector[i] << endl;
    return ost;
}

template <typename T1>
class Matrix : public Vector < Vector < T1>> {
public:
    size_t col;
    Matrix<T1>() { col = 0; }
    Matrix(size_t row, size_t Col) :Vector < Vector < T1>>{ row } {
        this->size = row;
        col = Col;
        Vector<T1> A{ col };
        for (size_t i = 0; i < this->size; i++) {
            this->vector[i] = A;
            this->vector[i].ScanVector();
        }

    }
    Matrix(size_t row, size_t Col, string check) :Vector < Vector < T1>>{ row } {
        this->size = row;
        col = Col;
        Vector<T1> A{ col };
        for (size_t i = 0; i < this->size; i++) {
            this->vector[i] = A;
            this->vector[i].Random();
        }
    }
    void OutMatx() {
        for (size_t i = 0; i < this->size; i++)
            this->vector[i].PrintVector();
    }
    T1 MaxCh(size_t Ncol, size_t BottomLine) {
        T1 Max = this->vector[BottomLine].GetElement(BottomLine);
        size_t Max1 = BottomLine;
        for (size_t i = BottomLine; i < this->size - 1; i++)
            if (abs(Max) < abs(this->vector[i + 1].GetElement(Ncol))) {
                Max = this->vector[i + 1].GetElement(Ncol);
                Max1 = i + 1;
            }
        return Max1;
    }
    T1 printEL(size_t col, size_t row) {
        return this->vector[row].GetElement(col);
    }
};

template <typename T2>
void SwapEl(Matrix<T2>& A, size_t Nrow) {
    A.Swap(Nrow, A.MaxCh(Nrow, Nrow));
}

template <typename T2>
void High(Matrix<T2>& A, size_t Nelement, size_t size) {
    A.GetVector(Nelement) /= A.printEL(Nelement, Nelement);
    Vector<T2> tmp = A.GetVector(Nelement);
    for (size_t i = Nelement; i > 0; i--) {
        if (Nelement - i < 0)
            continue;
        else {
            tmp *= A.printEL(Nelement, Nelement - i);
            A.GetVector(Nelement - i) -= tmp;
            tmp = A.GetVector(Nelement);
        }
    }
}

template <typename T2>
void Low(Matrix<T2>& A, size_t Nelement, size_t size) {
    A.GetVector(Nelement) /= A.printEL(Nelement, Nelement);
    Vector<T2> tmp = A.GetVector(Nelement);
    for (size_t i = 1; i < size - Nelement; i++) {
        if (Nelement + i > size - 1)
            continue;
        else {
            tmp *= A.printEL(Nelement, Nelement + i);
            A.GetVector(Nelement + i) -= tmp;
            tmp = A.GetVector(Nelement);
        }
    }
}

template <typename T2>
void GetSol(Matrix<T2>& A, size_t size) { 
    cout << endl << "Solution Column:" << endl;
    for (size_t i = 0; i < size; i++)
        if (A.printEL(size, i) >= 0 || A.printEL(size, i) <= 0) {
            cout << " = " << A.printEL(size, i) << endl;
        }
}




int main()
{
    size_t a;
    string choice;
    int comm = 0;
    Matrix<float> A;
    cout << "Dim matrix:" << endl;

    cin >> a;

    cout << "Show example?" << endl;
    cout << "Write yes/ok to continue." << endl;

    
    while (comm == 0) {
        cin >> choice;
        if (choice == "Yes" or choice == "Ok" or choice == "ok" or choice == "yes") {
            comm = 0;
            Matrix<float> A(a, a + 1, "RandomMatx");
            cout << endl << "matrix:" << endl;
            A.OutMatx();
            cout << endl;
            for (size_t i = 0; i < a; i++) {
                SwapEl(A, i);
                Low(A, i, a);
            }
            for (size_t i = 1; i < a; i++)
                High(A, i, a);
            cout << endl << "Matrix Gauss method:" << endl;
            A.OutMatx();
            GetSol(A, a);
            cout << "Another example?" << endl;
        }
        else if(choice == "No" or choice == "no" or choice == "stop"){
            comm = 0;
            cout << "Programm stopped" << endl;
            return 0;
            
        }
        else {
            comm = 0;
            cout << "Unknown command" << endl;
        }
    }
    return 0;

}