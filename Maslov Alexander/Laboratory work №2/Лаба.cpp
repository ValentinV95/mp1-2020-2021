#include <iostream>
#include <clocale>
using namespace std;

template<typename Type>
class Vector {
protected:
public:
    Type *vector;
    int size;
public:

    Vector() {
        size = 0;
        vector = nullptr;
    }

    explicit Vector(int input_size) {
        size = input_size;
        vector = new Type[size];
    }

    Vector(Vector &tmp) {
        size = tmp.size;
        vector = new Type[size];
        for (int i = 0; i < size; i++)
            vector[i] = tmp.vector[i];
    }

    Type GetElement(int num) {
        return vector[num];
    }

    void ScanVector() {
        for (int i = 0; i < size; i++)
            cin >> vector[i];
    }

    void RandomGenerateVector() {
        for (int i = 0; i < size; i++) {
            vector[i] = rand() % 42;
        }
    }

    void PrintVector() {
        for (int i = 0; i < size; i++)
            cout << vector[i] << "   ";
        cout << endl;
    }

    Type &GetVector(int num) {
        return vector[num];
    }

    void Swap(int first, int another_vector) {
        Type tmp = vector[first];
        vector[first] = vector[another_vector];
        vector[another_vector] = tmp;
    }

    Vector &operator=(Vector tmp) {
        if (size == tmp.size) {
            size = tmp.size;
            for (int i = 0; i < size; i++)
                vector[i] = tmp.vector[i];
        } else if (size == 0) {
            size = tmp.size;
            vector = new Type[size];
            for (int i = 0; i < size; i++)
                vector[i] = tmp.vector[i];
        }
        return *this;
    }

    Vector<Type> &operator*=(Type another_vector) {
        for (int i = 0; i < size; i++)
            vector[i] *= another_vector;
        return *this;
    }

    Vector<Type> &operator/=(Type another_vector) {
        for (int i = 0; i < size; i++)
            vector[i] /= another_vector;
        return *this;
    }

    Vector &operator-=(Vector another_vector) {
        for (int i = 0; i < size; i++)
            vector[i] -= another_vector.vector[i];
        return *this;
    }

    ~Vector() {
        delete[]vector;
    }
};

template<typename Type2>
ostream &operator<<(ostream &ost, Vector<Type2> &tmp) {
    for (int i = 0; i < tmp.size; i++)
        ost << tmp.vector[i] << endl;
    return ost;
}

template<typename Type1
        >
class Matrix : public Vector<Vector<Type1
        >> {
public:
    int col;


    Matrix<Type1
    >() { col = 0; }

    Matrix(int row, int Col) : Vector<Vector<Type1
    >>{row} {
        this->size = row;
        col = Col;
        Vector<Type1
        > A{col};
        for (int i = 0; i < this->size; i++) {
            this->vector[i] = A;
            this->vector[i].ScanVector();
        }

    }

    Matrix(int row, int Col, const string& check) : Vector<Vector<Type1
    >>{row} {
        this->size = row;
        col = Col;
        Vector<Type1
        > A{col};
        for (int i = 0; i < this->size; i++) {
            this->vector[i] = A;
            this->vector[i].RandomGenerateVector();
        }
    }

    void PrintMatrix() {
        for (int i = 0; i < this->size; i++)
            this->vector[i].PrintVector();
    }

    Type1
    MaxInCol(int NumberOfCol, int BottomLine) {
        Type1
        Max = this->vector[BottomLine].GetElement(BottomLine);
        int NumberOfMax = BottomLine;
        for (int i = BottomLine; i < this->size - 1; i++)
            if (abs(Max) < abs(this->vector[i + 1].GetElement(NumberOfCol))) {
                Max = this->vector[i + 1].GetElement(NumberOfCol);
                NumberOfMax = i + 1;
            }
        return NumberOfMax;
    }

    Type1
    printEL(int column, int row) {
        return this->vector[row].GetElement(column);
    }
};

template<typename Type2>
void CompareAndSwap(Matrix<Type2> &A,
                    int NumberOfRow) {
    A.Swap(NumberOfRow, A.MaxInCol(NumberOfRow, NumberOfRow));
}

template<typename Type2>
void Action(Matrix<Type2> &A, int NumberOfElement, int size) {
    A.GetVector(NumberOfElement) /= A.printEL(NumberOfElement, NumberOfElement);
    Vector<Type2> tmp = A.GetVector(NumberOfElement);
    for (int i = 1; i < size - NumberOfElement; i++) {
        if (NumberOfElement + i > size - 1)
            continue;
        else {
            tmp *= A.printEL(NumberOfElement, NumberOfElement + i);
            A.GetVector(NumberOfElement + i) -= tmp;
            tmp = A.GetVector(NumberOfElement);
        }
    }
}

template<typename Type2>
void Action2(Matrix<Type2> &A, int NumberOfElement) {
    A.GetVector(NumberOfElement) /= A.printEL(NumberOfElement, NumberOfElement);
    Vector<Type2> tmp = A.GetVector(NumberOfElement);
    for (int i = NumberOfElement; i > 0; i--) {
        if (NumberOfElement - i < 0)
            continue;
        else {
            tmp *= A.printEL(NumberOfElement, NumberOfElement - i);
            A.GetVector(NumberOfElement - i) -= tmp;
            tmp = A.GetVector(NumberOfElement);
        }
    }
}

template<typename Type2>
void GetAnswer(Matrix<Type2> &A, int size) {
    cout << endl << "Ответ" << endl;
    for (int i = 0; i < size; i++)
        if (A.printEL(size, i) >= 0 || A.printEL(size, i) <= 0) {
            cout << "x" << i + 1 << " = " << A.printEL(size, i) << endl;
        } else {
            cout << "Система линейна зависима. Ответ не верный." << endl;
            break;
        }
}


int main() {
    int a;
    int choice;

    setlocale(LC_ALL, "Russian");

    Matrix<double> M;
    cout << "Введите размер матрицы:" << endl;
    cin >> a;

    cout << "Что сделать с матрицей?" << endl;
    cout << "1)Ввести в ручную" << endl << "2)Сгенерировать рандомно" << endl;
    cin >> choice;
    if (choice == 1) {
        Matrix<double> A(a, a + 1);
        cout << endl << "Ваша матрица:" << endl;
        A.PrintMatrix();
        cout << endl;
        for (int i = 0; i < a; i++) {
            CompareAndSwap(A, i);
            Action(A, i, a);
        }
        for (int i = 1; i < a; i++)
            Action2(A, i);
        cout << endl << "Матрица после преобразований:" << endl;
        A.PrintMatrix();
        GetAnswer(A, a);
    } else if (choice == 2) {
        Matrix<double> A(a, a + 1, "Это рандомная матрица");
        cout << endl << "Ваша матрица:" << endl;
        A.PrintMatrix();
        cout << endl;
        for (int i = 0; i < a; i++) {
            CompareAndSwap(A, i);
            Action(A, i, a);
        }
        for (int i = 1; i < a; i++)
            Action2(A, i);
        cout << endl << "Матрица после преобразований:" << endl;
        A.PrintMatrix();
        GetAnswer(A, a);
    } else {
        cout << "Неверный выбор..." << endl;
        return 0;
    }


}