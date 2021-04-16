#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <locale.h>
#include <cstdlib>
#include <ctime>

typedef unsigned int uint;
using namespace std;


template <typename T>
class Vector {
protected:
	int size;
	T* data;
public:
	Vector() { size = 0; data = nullptr; }
	Vector(int size) {
		this->size = size;
		data = new T[size];
	}

	Vector(const Vector& second) {
		size = second.size;
		data = new T[size];
		for (int i = 0; i < size; i++)
			data[i] = second.data[i];
	}


	~Vector() {
		delete[] data;
	}

	void Set_coords() {
		for (int i = 0; i < size; i++) {
			cout << i << "-�� ���������� = ";
			cin >> data[i];
		}
	}

	void display() {
		for (int i = 0; i < size; i++)
			cout << data[i] << endl;
	}

	uint Get_size() { return this->size; }

	Vector& operator = (const Vector& second) {
		if (size != second.size) {
			cout << "������������ �������� ������ ����������� ����������!" << endl;
			exit(-1);
		}
		size = second.size;
		for (int i = 0; i < size; i++)
			data[i] = second.data[i];
		return *this;
	}

	Vector operator + (const Vector& second) {
		if (size != second.size) {
			cout << "�������� �������� ������ ����������� ����������!" << endl;
			exit(-2);
		}
		Vector result = *this;
		for (int i = 0; i < size; i++)
			result.data[i] += second.data[i];
		return result;
	}

	Vector operator - (const Vector& second) {
		if (size != second.size) {
			cout << "��������� �������� ������ ����������� ����������!" << endl;
			exit(-4);
		}
		Vector result = *this;
		for (int i = 0; i < size; i++)
			result.data[i] -= second.data[i];
		return result;
	}

	Vector operator * (T& number) {
		Vector result = *this;
		for (int i = 0; i < size; i++)
			result.data[i] *= number;
		return result;
	}

	Vector operator / (T& number) {
		Vector result = *this;
		for (int i = 0; i < size; i++)
			result.data[i] /= number;
		return result;
	}

	T& operator [] (uint coord) {
		if (coord < 0 || coord >= size) {
			cout << "����� �� ������� �������!";
			exit(-3);
		}
		return data[coord];
	}
};

template <typename T>
class Matrix : public Vector< Vector<T> > {
	//Vector T*
public:
	Matrix(int matrix_size) : Vector< Vector<T> >(matrix_size) {
		for (int i = 0; i < matrix_size; i++)
			data[i] = Vector <T>(matrix_size);
	}

	void generate_random_matrix() {
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				data[i][j] = (10 + rand() % 50) / 100;
	}

	void show_matrix() {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++)
				cout << data[i][j] << ' ';
		}
		cout << endl;
	}
};


template <typename T>
class GaussMethod {
private:
	Matrix A;
	Vector <T> y;
public:
	bool is_equal_size(Vector <T>& vec, Matrix<T>& sample) {
		if (vec.size == sample.size)
			return true;
		return false;
	}

	void show_system() {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				cout << data[i][j] << "*x" << j;
				if (j <= size - 2)
					cout << " + ";
			}
			cout << " = " << y[i] << endl;
		}
	}



	Vector <T> Solve() {
		Vector <T> solution(y.size);
		double max;
		int k = 0, index;
		const double eps = 1e-16;

		if (!is_equal_size(y, A)) {
			cout << "������� �� �������� ����������! ����������� ������� �� ��������!"
				exit(-6);
		}

		while (k < y.size) {
			max = abs(A.data[k][k]);
			index = k;

			for (int i = k + 1; i < y.size; i++) {
				if (abs(A.data[i][k]) > max) {
					max = abs(A.data[i][k]);
					index = i;
				}
			}

			if (max < eps) {
				cout << "������� �� �������� ��-�� �������� ������� " << index << "������� �" << endl;
				exit(-5);
			}

			for (int j = 0; j < y.size; j++) {
				T tmp = A.data[k][j];
				A.data[k][j] = A.data[index][j];
				A.data[index][j] = tmp;
			}

			T temp = y.data[k];
			y.data[k] = y.data[index];
			y[index] = temp;

			for (int i = k; i < y.size; i++) {
				T temp = A.data[i][k];
				if (abs(temp) < eps)
					continue;
				for (int j = 0; j < y.size; j++)
					A.data[i][j] /= temp;
				y.data[i][j] /= temp;
				if (i == k) continue;

				for (int j = 0; j < y.size; j++)
					A.data[i][j] -= A.data[k][j];
				y.data[i] -= y.data[k];
			}

			k++;
		}

		for (k = n - 1; k >= 0; k--) {
			solution.data[k] = y.data[k];
			for (int i = 0; i < k; i++)
				y.data[i] = y.data[i] - A.data[i][k] * solution.data[k];
		}
		return solution;
	}
};




int main() {
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	Vector <double> a(3), b(3), c(3);
	Matrix <double> A(3);

	return 0;
}