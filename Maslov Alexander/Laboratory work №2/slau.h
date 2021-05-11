#pragma once

#include "Matrix.h"
#include <iostream>

using namespace std;

template<class T>
class SLAU : public Matrix<T> {
public:
    SLAU(int n) : Matrix<T>::Matrix(n) {}

    Vector<double> *Gausse(Vector<T> y);

};

template<class T>
inline Vector<double> *SLAU<T>::Gausse(Vector<T> y) {
    Vector<Vector<T> > b = this[0];
    Vector<Vector<T> > a;// = b;
    for (int i = 0; i < b.Size(); ++i) {
        Vector<T> tmp;
        for (int j = 0; j < b.Size(); ++j) {
            tmp.push_back(b[i][j]);
        }
        a.push_back(tmp);
    }

    Vector<double> *x = new Vector<double>(a.Size(), 0);
    int k, index;
    const double eps = 0.00001;  // точность
    int n = a.Size();
    double max;
    k = 0;
    while (k < n) {
        // Поиск строки с максимальным a[i][k]
        max = abs(a[k][k]);
        index = k;
        for (int i = k + 1; i < n; i++) {
            if (abs(a[i][k]) > max) {
                max = abs(a[i][k]);
                index = i;
            }
        }

        if (max < eps) {
            // нет ненулевых диагональных элементов
            cout << "The solution cannot be obtained due to the zero column ";
            cout << index << " of the matrix A" << endl;
            return 0;
        }
        // Перестановка строк
        for (int j = 0; j < n; j++) {
            T temp = a[k][j];
            a[k][j] = a[index][j];
            a[index][j] = temp;
        }

        // SwapRow(index, k, &a);

        double temp = y[k];
        y[k] = y[index];
        y[index] = temp;


        // Нормализация уравнений
        for (int i = k; i < n; i++) {
            double temp = a[i][k];
            if (abs(temp) < eps) continue; // для нулевого коэффициента пропустить
            for (int j = 0; j < n; j++)
                a[i][j] = a[i][j] / temp;
            y[i] = y[i] / temp;
            if (i == k) continue; // уравнение не вычитать само из себя
            for (int j = 0; j < n; j++)
                a[i][j] = a[i][j] - a[k][j];
            y[i] = y[i] - y[k];
        }

        k++;
    }
    // обратная подстановка
    for (k = n - 1; k >= 0; k--) {
        (*x)[k] = y[k];
        for (int i = 0; i < k; i++)
            y[i] = y[i] - a[i][k] * (*x)[k];
    }
    return x;

}
