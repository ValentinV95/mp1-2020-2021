#pragma once

#include<iostream>




template <class T>
class Vector {
private:
    size_t size;
    T* data;
public:

    Vector() {
        size = 0;
        data = 0;
    }

    ~Vector() {
        delete[] data;
    }

    Vector(size_t size) : size(size), data(new T[size]) {}

    Vector(Vector const& a) :size(a.size), data(new T[size]) {
        for (int i = 0; i < size; i++) {
            data[i] = a.data[i];
        }
    }


    Vector& operator=(const Vector& other) {
        if (this != &other) {



            if (size != other.size) {
                delete[] data;
                size = other.size;
                data = new T[size];
            }
            for (int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }

        }
        return *this;
    }

    Vector operator-() const {
        Vector temp(*this);
        for (int i = 0; i < size; i++)
            temp.data[i] = -temp.data[i];
        return temp;
    }

    Vector& operator+=(const Vector& other) {
        for (int i = 0; i < size; i++)
            data[i] += other.data[i];
        return *this;
    }

    Vector& operator-=(const Vector& other) {
        for (int i = 0; i < size; i++)
            data[i] -= other.data[i];
        return *this;
    }



    T& operator[](int index) {
        return data[index];
    }

    T operator[](int index) const {
        return data[index];
    }




    void setSize(size_t size) {
        this->size = size;
        data = new T[size];
    }


    size_t getSize() const {
        return size;
    }




};

template<class F>
Vector<F> operator+(Vector<F> left, const Vector<F>& right)
{
    left += right;
    return left;
}




template<class U>
std::ostream& operator<< (std::ostream& out, const Vector<U>& other)
{
    for (int i = 0; i < other.getSize(); i++)
        out << other[i] << " ";

    out << "\n";

    return out;
}





template<class T, class U>
Vector<T> operator*(Vector<T> left, const U& right) {
    for (int i = 0; i < left.getSize(); i++)
        left[i] = left[i] * right;

    return left;

}


template<class T, class U>
Vector<T> operator*(const U& left, Vector<T> right) {
    for (int i = 0; i < right.getSize(); i++)
        right[i] = right[i] * left;

    return right;

}



template<class T, class U>
Vector<T> operator/(Vector<T> left, const U& right) {
    for (int i = 0; i < left.getSize(); i++)
        left[i] = left[i] / right;

    return left;

}








template<class T>
class SLAU {


    Vector<T> input;
    Vector<Vector<T>> matrix;
    size_t size;


    T random()
    {
        T min = -100000;
        T max = 100000;

        return (T)(rand()) / RAND_MAX * (max - min) + min;
    }



    void CreateMatrix() {

        matrix.setSize(size);
        for (int i = 0; i < size; i++)
            matrix[i].setSize(size);

        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                matrix[i][j] = random();

    }



    void CreateInput() {

        input.setSize(size);
        for (int i = 0; i < size; i++)
            input[i] = random();

    }




    bool isEqual(const T& left, const T& right) {
        return std::abs(left - right) < std::numeric_limits<T>::epsilon() * 1000;
    }





public:

    SLAU(size_t size) {
        this->size = size;

        CreateInput();

        CreateMatrix();
    }





    SLAU(Vector<T> input) :input(input) {
        size = input.getSize();

        CreateMatrix();
    }

    SLAU(Vector<T> input, Vector<Vector<T>>& matrix) :input(input), matrix(matrix), size(input.getSize()) {

    }



    bool solve() {

        //прямой ход

        for (int i = 0; i < size; i++) {
            
            int sel = i;
            for (int k = i + 1; k < size; k++)
                if (abs(matrix[k][i]) > abs(matrix[sel][i]))
                    sel = k;

            if (isEqual(matrix[sel][i], 0)) {
                return 0;

            }

            if (i != sel) {
                swap(matrix[i], matrix[sel]);
                swap(input[i], input[sel]);
            }


            for (int k = i + 1; k < size; k++) {


                input[k] -= matrix[k][i] * (input[i] / matrix[i][i]);

                matrix[k] -= matrix[k][i] * (matrix[i] / matrix[i][i]);
            }

        }


        //обратный ход


        input[size - 1] /= matrix[size - 1][size - 1];
        matrix[size - 1][size - 1] = 1;


        for (int i = size - 2; i >= 0; i--) {


            for (int k = i + 1; k < size; k++)
                input[i] -= matrix[i][k] * input[k];



            for (int k = i + 1; k < size; k++)
                matrix[i][k] = 0;




            input[i] /= matrix[i][i];
            matrix[i][i] = 1;


        }


        for (int i = 0; i < size; i++)
            if (isEqual(input[i], 0))
                input[i] = 0;

        return 1;


    }




    void printMatrix() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++)
                std::cout << std::right << std::setw(12) << matrix[i][j] << " ";
            std::cout << " | " << std::left << std::setw(12) << input[i] << "\n";
        }
    }


    template <class F>
    void swap(F& first, F& second) {
        F temp = first;
        first = second;
        second = temp;


    }

    Vector <T> getSolution() const {
        return input;
    }



};

