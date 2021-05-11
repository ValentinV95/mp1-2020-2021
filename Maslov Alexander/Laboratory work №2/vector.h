#pragma once

#include <stdlib.h>

template<class T>
class Vector {
private:
    T **values;                     //указатель на массив значений
    int size;                       //текущий размер вектора
    int maxsize;                    //максимальный размер вектора
public:
    Vector();

    Vector(int _size);

    Vector(int _size, T value);

    void push_back(T value);

    void double_size();

    void clear();

    int Size();

    int MaxSize();

    T &operator[](int index);

    Vector<T> &operator=(Vector<T> target);

    T **Values();

};

template<class T>
Vector<T>::Vector() {
    maxsize = 10;                                      //конструктор без параметров, функция задает
    size = 0;                                          //максимальный размер вектора(массива)-maxsize и
    values = (T **) malloc(maxsize * sizeof(T *));//настоящий размер, который равен 0, так же
}                                                      //выделяет память под значение

template<class T>
Vector<T>::Vector(int _size) {
    maxsize = _size;                                   //конструктор, где параметр- размер(максимальный)
    size = 0;                                          //выделяется память на данное количество
    values = (T **) malloc(maxsize * sizeof(T *));
    for (int i = 0; i < _size; ++i)
        values[i] = (T *) malloc(_size * sizeof(T));
}

template<class T>
Vector<T>::Vector(int _size, T value) {
    maxsize = _size;                                    //конструктор, где максимальный размер равен
    size = 0;                                           //передаваемому значению, все значения равны
    values = (T **) malloc(maxsize * sizeof(T *)); //второму передаваемому параметру
    for (int i = 0; i < _size; ++i) {
        values[i] = (T *) malloc(sizeof(T));
        this->push_back(value);
    }
}

template<class T>
void Vector<T>::push_back(T value) {
    if (size == maxsize)                        //кладет элемент в конец вектора
        this->double_size();
    T *tmp = (T *) malloc(sizeof(T));
    *tmp = value;
    values[size] = tmp;
    size++;
}

template<class T>
void Vector<T>::double_size() {
    T **tmp = (T **) malloc(maxsize * sizeof(T *));
    for (int i = 0; i < maxsize; ++i) {
        T *tmp2 = (T *) malloc(sizeof(T));            //в два раза увеличивает размер вектора
        tmp2 = values[i];                           //перевыделяет память
        tmp[i] = tmp2;
    }

    free(values);
    maxsize *= 2;
    values = (T **) malloc(maxsize * sizeof(T *));
    for (int i = 0; i < size; ++i) {
        T *tmp2 = (T *) malloc(sizeof(T));
        tmp2 = tmp[i];
        values[i] = tmp2;
    }

    free(tmp);
}

template<class T>
void Vector<T>::clear() {
    if (!values)                     //чистит вектор
        free(values);
    size = 0;
}

template<class T>
inline int Vector<T>::Size() {
    return size;                        //возвращает количество элементов в векторе
}

template<class T>
inline int Vector<T>::MaxSize() {
    return maxsize;                     //возвращает максимальное количество элементов в векторе
}

template<class T>
T &Vector<T>::operator[](int index) {
    return *(values[index]);            //перегрузка квадратных скобок, чтобы можно было
}                                       //обращаться к элементу по индексу

template<class T>
Vector<T> &Vector<T>::operator=(Vector<T> target) {
    this->clear();
    values = (T **) malloc(target.size * sizeof(T *));         //перегрузка оператора присваивания
    for (int i = 0; i < target.size; ++i) {
        values[i] = (T *) malloc(sizeof(T));
        T *tmp = (T *) malloc(sizeof(T));
        *tmp = target[i];
        values[i] = tmp;
    }
    size = target.size;
    return *this;
}

template<class T>
inline T **Vector<T>::Values() {
    return values;                          //возвращает указатель на массив указателей на
}                                           //значения(все значения хранящиеся в векторе)

