#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <locale.h>

typedef unsigned int uint;
using namespace std;


template <typename T>
class Vector {
public:
	uint size;
	T* coords;
public:
	Vector<T>() { size = 0; coords = nullptr; }
	Vector<T>(uint size) {
		this->size = size;
		coords = new T[size];
	}

	Vector<T>(const Vector& second) {
		size = second.size;
		coords = new T[size];
		for (int i = 0; i < size; i++)
			coords[i] = second.coords[i];
	}

	~Vector() { delete[] coords; }

	uint Get_size() { return size; }

	Vector<T>& operator = (const Vector<T>& second) {
		if (this == &second)
			return *this;
		size = second.size;
		delete[] coords;
		coords = new T[size];
		for (int i = 0; i < size; i++)
			coords[i] = second.coords[i];
		return *this;
	}

	Vector<T> operator + (Vector<T>& second) {
		if (size != second.size) {
			cout << "Сложение векторов разной размерности невозможно!" << endl;
			exit(-2);
		}
		Vector result = *this;
		for (int i = 0; i < size; i++)
			result.coords[i] += second.coords[i];
		return result;
	}

	Vector<T> operator - (Vector<T>& second) {
		if (size != second.size) {
			cout << "Вычитание векторов разной размерности невозможно!" << endl;
			exit(-3);
		}
		Vector result = *this;
		for (int i = 0; i < size; i++)
			result.coords[i] -= second.coords[i];
		return result;
	}

	Vector<T> operator * (T& number) {
		Vector result = *this;
		for (int i = 0; i < size; i++)
			result.coords[i] *= number;
		return result;
	}

	Vector<T> operator / (T& number) {
		if (number == 0) {
			cout << "Деление на 0!" << endl;
			exit(-4);
		}
		Vector result = *this;
		for (int i = 0; i < size; i++)
			result.coords[i] /= number;
		return result;
	}

	T& operator [] (uint coord) {
		if (coord < 0 || coord >= size) {
			cout << "Выход за границы массива!" << endl;
			exit(-5);
		}
		return coords[coord];
	}

	// Необходимо для дальнейшей перегрузки оператора умножения матрицы на вектор-столбец
	Vector<T> operator = (int number) {
		for (int i = 0; i < size; i++)
			coords[i] = 0;
		return *this;
	}
	
	// Первый неправильный вариант проверки решений на корректность
	bool Is_equal(const Vector<T>& second) {
		this->size = second.size;
		for (int i = 0; i < size; i++) {
			if (coords[i] != second.coords[i]) {
				return false;
				break;
			}
		}
		return true;
	}

	void generate_random_vector() {
		for (int i = 0; i < size; i++)
			coords[i] = 0.3 + (double)((10.0 + rand() % 50) / 1000000);
	}

	template <typename T> friend istream& operator>>(istream& input, Vector<T>& vec);
	template <typename T> friend ostream& operator<<(ostream& output, Vector<T>& vec);
};

template <typename T>
ostream& operator << (ostream& output, Vector<T>& vec) {
	for (int i = 0; i < vec.size; i++)
		output << vec.coords[i] << endl;
	return output;
}

template <typename T>
istream& operator >> (istream& input, Vector <T>& vec) {
	cout << "Ввод столбца свободных значений:" << endl;
	for (int i = 0; i < vec.size; i++) {
		cout << "b[" << i << "] = ";
		input >> vec.coords[i];
	}
	return input;
}


template <typename T>
class Matrix : public Vector<Vector<T>> {
public:
	Matrix<T>() {}

	Matrix<T>(uint matrix_size) : Vector<Vector<T>>(matrix_size) {
		for (int i = 0; i < matrix_size; i++)
			this->coords[i] = Vector<T>(matrix_size);
	}

	Matrix<T>(const Matrix& second) : Matrix(second.size) {
		for (int i = 0; i < second.size; i++)
			this->coords[i] = second.coords[i];
	}


	void generate_random_matrix() {
		for (int i = 0; i < this->size; i++)
			for (int j = 0; j < this->size; j++)
				this->coords[i][j] = 0.3 + (double)((10.0 + rand() % 100) / 1000000);
	}

	Vector<T> operator* (Vector<T>& v) {
		uint columns = this->size;
		uint rows = (*this)[0].size;
		Vector<T> result(columns);
		result = 0;

		for (int i = 0; i < columns; i++)
			for (int j = 0; j < rows; j++)
				result[i] += (*this)[i][j] * v[j];

		return result;
	}

	Matrix<T>& operator=(const Matrix<T>& second) {
		if (this == &second)
			return *this;
		this->size = second.size;
		delete[] this->coords;
		this->coords = new Vector<T>[this->size];
		for (int i = 0; i < this->size; i++)
			this->coords[i] = second.coords[i];
		return *this;
	}


	template <typename T> friend istream& operator>>(istream& input, Matrix<T>& matrix);
	template <typename T> friend ostream& operator<<(ostream& output, Matrix<T>& matrix);
};

template <typename T>
istream& operator >> (istream& input, Matrix<T>& matrix) {
	for (int i = 0; i < matrix.size; i++) {
		for (int j = 0; j < matrix.size; j++) {
			cout << "a[" << i << "][" << j << "] = ";
			input >> matrix[i][j];
		}
	}
	return input;
}

template <typename T>
ostream& operator << (ostream& output, Matrix<T>& matrix) {
	output << "Матрица системы:" << endl;
	for (int i = 0; i < matrix.size; i++) {
		for (int j = 0; j < matrix.size; j++)
			output << matrix.coords[i][j] << ' ';
		output << endl;
	}
	return output;
}

template <typename T>
class GaussMethod {
private:
	Matrix <T> A;
public:
	
	GaussMethod<T>(const Matrix<T>& matrix) {
		A = matrix;
	}


	Vector<T> Solve(Vector<T>& y) {
		uint n = y.Get_size();
		Vector<T> answer(n);
		T max;
		int k = 0, index;
		const double eps = 10e-9;

		while (k < n) {
			max = abs(A.coords[k][k]);
			index = k;
			for (int i = k + 1; i < n; i++) {
				if (abs(A.coords[i][k]) > max) {
					max = abs(A.coords[i][k]);
					index = i;
				}
			}

			if (max < eps) {
				cout << "Решение не удалось получить из-за нулевого столбца " << index << " матрицы А" << endl;
				exit(-8);
			}

			for (int j = 0; j < n; j++) {
				T tmp = A.coords[k][j];
				A.coords[k][j] = A.coords[index][j];
				A.coords[index][j] = tmp;
			}

			T temp = y.coords[k];
			y.coords[k] = y.coords[index];
			y.coords[index] = temp;

			for (int i = k; i < n; i++) {
				T temp = A.coords[i][k];
				if (abs(temp) < eps)
					continue;
				for (int j = 0; j < n; j++)
					A.coords[i][j] /= temp;
				y.coords[i] /= temp;
				if (i == k)
					continue;
				for (int j = 0; j < n; j++)
					A.coords[i][j] = A.coords[i][j] - A.coords[k][j];
				y.coords[i] -= y.coords[k];
			}
			k++;
		}

		for (k = n - 1; k >= 0; k--) {
			answer.coords[k] = y.coords[k];
			for (int i = 0; i < k; i++)
				y.coords[i] = y.coords[i] - A.coords[i][k] * answer.coords[k];
		}
		return answer;
	}

	void display_system(Vector <T>& y) {
		for (int i = 0; i < A.size; i++) {
			for (int j = 0; j < A.size; j++) {
				cout << A.coords[i][j] << "*x" << j;
				if (j <= A.size - 2)
					cout << " + ";
			}
			cout << " = " << y.coords[i] << endl;
		}
	}
};