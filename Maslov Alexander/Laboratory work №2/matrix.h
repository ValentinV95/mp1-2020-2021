#pragma once

#include "vector.h"

template<class T>
class Matrix : public Vector<Vector<T> >           //класс двумерный вектор
{
public:
    Matrix(int n) : Vector<Vector<T> >(n, Vector<T>(n, 0)) {}

    T &operator=(T targ) {
        T *tmp = new T;
        *tmp = targ;
        return tmp;
    }

    Matrix<T> &operator=(Matrix<T> targ) {
        Matrix<T> *tmp = new Matrix<T>(targ.Size());
        *tmp = targ;
        this = tmp;
        return *this;
    }

};

template<class T>
void SwapRow(int firstID, int secondID, Matrix<T> &matr) {
    Vector<T> tmp(matr.Size(), 0);
    for (int i = 0; i < matr.Size(); ++i)
        tmp[i] = matr[firstID][i];
    for (int i = 0; i < matr.Size(); ++i)
        matr[firstID][i] = matr[secondID][i];
    for (int i = 0; i < matr.Size(); ++i)
        matr[secondID][i] = tmp[i];
}
