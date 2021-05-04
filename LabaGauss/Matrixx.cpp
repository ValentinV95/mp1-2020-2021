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
    void ScanSize() {  //Ввод размерности
        cin >> size;
    }
    void ScanVector() {  //Ввод вектора
        for (size_t i = 0; i < size; i++)
            cin >> vector[i];
    }
    void RandomGenerateVector() {  //Случайная генерация чисел
       // srand(time(NULL));
        for (size_t i = 0; i < size; i++) { 
            vector[i] = rand() % 50;
        } 
    }
    void PrintVector() {
        for (size_t i = 0; i < size; i++)
            cout << vector[i] << "   ";
        cout << endl;
    }
    T& GetVector(size_t num){
        return vector[num];
    }
    void Swap(size_t first, size_t second) {  //Меняет векторы местами
        T tmp = vector[first];
        vector[first] = vector[second];
        vector[second] = tmp;
    } 
    //Конструкторы
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
    //Перегрузки операторов
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
    //Деструктор
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
    //Конструкторы
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
                this->vector[i].RandomGenerateVector();          
        }
    }
    void PrintMatrix() {  //Выводит матрицу
        for (size_t i = 0; i < this->size; i++)
            this->vector[i].PrintVector();
    }
    T1 MaxInCol(size_t NumberOfcol, size_t BottomLine) {  //Возвращает максимальный элемент в столбце
        T1 Max = this->vector[BottomLine].GetElement(BottomLine);
        size_t NumberOfMax = BottomLine;
        for (size_t i = BottomLine; i < this->size - 1; i++)
            if (abs(Max) < abs(this->vector[i + 1].GetElement(NumberOfcol))) {
                Max = this->vector[i + 1].GetElement(NumberOfcol);
                NumberOfMax = i + 1;
            }
        return NumberOfMax;
    }
    T1 printEL(size_t col, size_t row) {  //Возвращает конкретный элемент матрицы
        return this->vector[row].GetElement(col);
    }
};

template <typename T2>
void CompareAndSwap(Matrix<T2>& A, size_t NumberOfRow) {  //Ищет максимальный элемент в столбце и меняет ставит его на главную диагональ
        A.Swap(NumberOfRow, A.MaxInCol(NumberOfRow, NumberOfRow));
    }
template <typename T2>
void Magic(Matrix<T2>& A, size_t NumberOfElement, size_t size) {  //Зануляет элементы ниже главной диагонали
    A.GetVector(NumberOfElement) /= A.printEL(NumberOfElement, NumberOfElement);
    Vector<T2> tmp = A.GetVector(NumberOfElement); 
    for (size_t i = 1; i < size - NumberOfElement; i++) {
        if (NumberOfElement + i > size - 1)
            continue;
        else {
            tmp *= A.printEL(NumberOfElement, NumberOfElement + i);
            A.GetVector(NumberOfElement + i) -= tmp;
            tmp = A.GetVector(NumberOfElement);
        }
    }
}
template <typename T2>
void Magic2(Matrix<T2>& A, size_t NumberOfElement, size_t size) {  //Зануляет элементы выше главной диагонали
    A.GetVector(NumberOfElement) /= A.printEL(NumberOfElement, NumberOfElement);
    Vector<T2> tmp = A.GetVector(NumberOfElement);
    for (size_t i = NumberOfElement; i > 0; i--) {
        if (NumberOfElement - i < 0)
            continue;
        else {
            tmp *= A.printEL(NumberOfElement, NumberOfElement - i);
            A.GetVector(NumberOfElement - i) -= tmp;
            tmp = A.GetVector(NumberOfElement);
        }
    }
}
template <typename T2>
void GetAnswer(Matrix<T2>& A, size_t size) {  //Выводит ответ
    cout << endl << "Answer:" << endl;
    for (size_t i = 0; i < size; i++)
        if (A.printEL(size, i) >= 0 || A.printEL(size, i) <= 0) {
            cout << "x" << i + 1 << " = " << A.printEL(size, i) << endl;
        }
        else {
            cout << "System is linearly dependent. The answer is not correct" << endl;
            break;
        }
}

    

int main()
{
    size_t a;
    int choice;
    
    Matrix<double> A;
    cout << "Enter the dimension of the matrix:" << endl;
    cin >> a;

    cout << "What to do with the matrix?" << endl;
    cout << "1)Enter the matrix manually" << endl << "2)Generate matrix randomly" << endl;
    cin >> choice;
    if (choice == 1) {
        Matrix<double> A(a, a + 1);
        cout << endl << "Your matrix:" << endl;
        A.PrintMatrix();
        cout << endl;
        for (size_t i = 0; i < a; i++) {
            CompareAndSwap(A, i);
            Magic(A, i, a);
        }       
        for (size_t i = 1; i < a; i++)
            Magic2(A, i, a);
        cout << endl << "Matrix after transformations:" << endl;
        A.PrintMatrix();
        GetAnswer(A, a);
    }
    else if (choice == 2) {
        Matrix<double> A(a, a + 1, "ItIsRandomMatrix");
        cout << endl << "Your matrix:" << endl;
        A.PrintMatrix();
        cout << endl;
        for (size_t i = 0; i < a; i++) {
            CompareAndSwap(A, i);
            Magic(A, i, a);
        }      
        for (size_t i = 1; i < a; i++)
            Magic2(A, i, a);
        cout << endl << "Matrix after transformations:" << endl;
        A.PrintMatrix();
        GetAnswer(A, a);
    }
    else {
        cout << "Wrong choice..." << endl;
        return 0;
    }  

   
}