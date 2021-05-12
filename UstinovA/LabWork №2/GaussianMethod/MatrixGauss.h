#pragma once
#include <type_traits>
#include "TemplateVector.h"

template <typename T>
class Matrix : public Vector<Vector<T>> {
public:
	Matrix(size_t column, const Vector<T>& sample) : Vector<Vector<T>>(column, sample) {}

	Vector<T> operator* (const Vector<T>& v) {
		size_t column_size = this->GetSize();
		size_t row_size = (*this)[0].GetSize();
		Vector<T> result(column_size, 0);

		for (int i = 0; i < column_size; i++)
			for (int j = 0; j < row_size; j++)
				result[i] += (*this)[i][j] * v[j];

		return result;
	}
};

template <typename T>
class GaussianMethod : public Matrix<T> {
protected:
	T zero; // Ноль типа Т (необходим для сравнения с ним элементов)
	bool HasUniqueSolution; // Индикатор единственности решения

	bool ZeroColumnCheck(const GaussianMethod<T>& system, size_t row, size_t column) {
		// Проверка на наличие нулевых столбцов (при наличии выдаётся ошибка)
		for (size_t i = 0; i < column; i++) {
			int count = 0;

			for (size_t j = 0; j < row; j++)
				if (system[j][i] != zero) count++;
			if (count == 0) return true;
		}
		return false;
	}

	void CheckSystem(GaussianMethod<T>& system, size_t column_size, size_t row_size, size_t current_column, Vector<T>& b) {
		// Проверка системы на вырожденность (нет решений) и наличие свободных переменных (бесконечно много решений)
		size_t non_zero_row = 0; // Счётчик ненулевых строк

		for (size_t i = 0; i < column_size; i++)
		{
			size_t count = 0; // Счётчик ненулевых элементов строки (без свободного коэффициента)
			for (size_t j = 0; j < row_size; j++) {
				if (system[i][j] != zero) count++;
			}

			if (count == 0 && b[i] != zero) {
				// Система вырожденная, решений нет (строка нулевая, а свободный коэффициент - нет)
				error(2);
				HasUniqueSolution = false;
				return;
			}
			else if (!(count == 0 && b[i] == zero)) non_zero_row++; // Подсчёт ненулевых строк у невырожденной системы
		}

		if (non_zero_row < current_column + 1) {
			// Решений бесконечно много, т.к. столбцов больше, чем ненулевых строк => есть свободные неизвестные;
			error(3);
			HasUniqueSolution = false;
			return;
		}
	}

	int SearchMaxInColumn(const GaussianMethod<T>& system, size_t column_size, size_t column) {

		// Поиск максимального элемента в столбце
		T element = system[column][column]; // Максимальный по модулю элемент
		size_t max_point = column; // Индекс максимального по модулю элемента в столбце
		size_t count = 0; // Счётчик ненулевых элементов столбца (ниже column)

		// Поиск наибольшего по модулю ненулевого элемента в столбце ниже заданной строки
		for (size_t i = column; i < column_size; i++) {
			if (system[i][column] != zero) count++;
			if (system[i][column] * system[i][column] > element * element) {
				element = system[i][column];
				max_point = i;
			}
		}

		// Если все рассмотренные элементы нулевые, переменная в данном столбце свободная => решений бесконечно много
		if (count == 0) max_point = -1; 

		return max_point;
	}

	void MatrixZeroTrimmer(GaussianMethod<T>& system, size_t m, size_t n) { 
		// Зануление малых по модулю элементов вещественных типов (в матрице)
		double eps = 10e-9; // Верхняя граница погрешности при сравнении с 0
		if (std::is_same<T, float>::value || std::is_same<T, double>::value)
			for (size_t i = 0; i < m; i++)
				for (size_t j = 0; j < n; j++)
					if (abs(system[i][j]) < eps) system[i][j] = zero;
	}

	void VectorZeroTrimmer(Vector<T>& vector, size_t n) { 
		// Зануление малых по модулю элементов вещественных типов (в векторе-ответе)
		double eps = 10e-9; // Верхняя граница погрешности при сравнении с 0
		if (std::is_same<T, float>::value || std::is_same<T, double>::value)
			for (size_t i = 0; i < n; i++)
				if (abs(vector[i]) < eps) vector[i] = zero;
	}

	void CheckSolution(const GaussianMethod<T>& system, const Vector<T>& sol, const Vector<T>& rhs) { // Проверка решения
		Vector<T> check = (Matrix<T>)system * sol; // Проверка - вычисляется правый столбец (произведение матрицы на вектор решения)
		double eps = 10e-7; // Точность сравнения
		bool is_equal = true;
		for (size_t i = 0; i < check.GetSize(); i++)
			if (abs(check[i] - rhs[i]) > eps) is_equal = false;
		if (is_equal) cout << "Solution checked: it is right!" << endl;
		else cout << "Solution checked: it is wrong :/" << endl;
		cout << std::defaultfloat << "The current value of error is " << eps << endl;
	}

public:
	GaussianMethod(size_t column, const Vector<T>& sample, const T& zero) : Matrix<T>(column, sample) {
		this->zero = zero;
		HasUniqueSolution = true;
	}

	bool GetHasUniqueSolution() { return HasUniqueSolution; }

	Vector<T> Solve(Vector<T>& b) {


		size_t column_size = this->GetSize(); // Количество строк в матрице
		size_t row_size = (*this)[0].GetSize(); // Количество столбцов в матрице (без учёта столбца свободных коэффициентов)
		GaussianMethod<T> system_copy = *this;
		Vector<T> solution(row_size, zero); // Вектор решения
		Vector<T> b_copy = b; // Копия b для проверки верности решения
		size_t max_point; // Позиция ведущего элемента в столбце
		Vector<T> zero_vector(row_size, zero); // Нулевой вектор (возвращается из метода, когда нет единственного решения)

		// Прямой ход метода Гаусса
		// Есть нулевой столбец => нет единственного решения
		if (ZeroColumnCheck(*this, column_size, row_size)) {
			error(4);
			HasUniqueSolution = false;
			return zero_vector;
		}

		else {
			for (size_t i = 0; i < row_size; i++) {
				CheckSystem(*this, column_size, row_size, i, b); // Проверка СЛАУ
				// Если нет решений/их бесконечно много
				if (!HasUniqueSolution) return zero_vector;

				// Поиск наибольшего по модулю элемента в столбце
				max_point = SearchMaxInColumn(*this, column_size, i);
				if (max_point != -1) {

					// Ставим ведущий элемент на главную диагональ
					std::swap<Vector<T>>((*this)[i], (*this)[max_point]); 
					std::swap<T>(b[i], b[max_point]);

					// Нормирование строки
					T diag_elem = (*this)[i][i]; 
					(*this)[i] /= diag_elem;
					b[i] /= diag_elem;

					// Зануляем всё ниже ведущего элемента
					for (size_t j = i + 1; j < column_size; j++) { 
						T coeff = (*this)[j][i];
						(*this)[j] -= (*this)[i] * coeff;
						b[j] -= b[i] * coeff;
					}

					// Зануляем близкие к нулю значения вещественных типов в матрице
					MatrixZeroTrimmer(*this, column_size, row_size); 
					VectorZeroTrimmer(b, column_size);

				}
				// Если рассмотренные элементы в столбце - нули, есть свободная переменная => решений бесконечно много
				else {
					error(3);
					HasUniqueSolution = false;
					return zero_vector; 
				}
			}
		}

		// Обратный ход метода Гаусса
		// Вычисление вектора-решения, если решение единственное 
		for (int i = row_size - 1; i >= 0; i--) {
			solution[i] = b[i];

			for (int j = row_size - 1; j >= i + 1; j--)
				solution[i] -= (*this)[i][j] * solution[j];
		}

		VectorZeroTrimmer(solution, row_size); // Зануляем близкие к нулю значения вещественных типов в решении
		CheckSolution(system_copy, solution, b_copy); // Проверка решения
		return solution;

	}

};