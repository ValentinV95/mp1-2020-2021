#pragma once

#include "vector.h"
#include <cassert>
#include <cinttypes>
#include <initializer_list>
#include <type_traits>

namespace lab {
	template <typename T>
	class Matrix;

	template <typename T>
	struct isEqual
	{
		bool operator()(const T& left, const T& right)
		{
			if constexpr (is_floating_point_v<T>) {
				return std::abs(std::abs(left) - std::abs(right)) < std::numeric_limits<T>::epsilon() * 10000;
			}
			else {
				return left == right;
			}
		}
	};

	template <typename T>
	struct basePivot
	{
		size_t operator()(const Matrix<T>& matrix, size_t colum)
		{
			static auto abs = [](const T& val) {
				if (val < 0) return -val;
				return val;
			};

			size_t maxI = colum;

			for (size_t i = colum + 1; i < matrix.size().first; i++)
			{
				if (abs(matrix[maxI][colum]) < abs(matrix[i][colum])) {
					maxI = i;
				}
			}

			return maxI;
		}
	};

	template <typename T>
	class Matrix : public vector<vector<T>>
	{
	public:
		Matrix() = default;
		Matrix(const Matrix&) = default;
		Matrix(Matrix&&) = default;
		Matrix(size_t h, size_t w) : vector<vector<T>>(h, vector<T>(w)) {}
		Matrix(size_t h, size_t w, const T& val) : vector<vector<T>>(h, vector<T>(w, val)) {}
		Matrix(std::initializer_list<vector<T>> iList) : vector<vector<T>>(iList) {}

		~Matrix() = default;

		Matrix& operator=(const Matrix&) = default;
		Matrix& operator=(Matrix&&) = default;

		std::pair<size_t, size_t> size() const
		{
			if (this->_size == 0) {
				return { 0, 0 };
			}
			return { this->_size, this->_data[0].size() };
		}

		void resize(size_t h, size_t w)
		{
			this->vector<vector<T>>::resize(h);
			for (size_t i = 0; i < this->_size; i++)
			{
				this->_data[i].resize(w);
			}
		}

		template <typename pivotType = basePivot<T>, typename predType = isEqual<T>>
		void gauss(pivotType = pivotType(), predType = predType());
	};


	template <typename T>
	template <typename pivotType, typename predType>
	void Matrix<T>::gauss(pivotType pivot, predType pred)
	{
		auto& matrix = *this;

		for (size_t i = 0; i < matrix.size().first && i < matrix.size().second; i++)
		{
			size_t maxValRow = pivot(*this, i);
			if (maxValRow != i) {
				std::swap(matrix[i], matrix[maxValRow]);
			}

			if (matrix[i][i] != 0) {
				for (size_t j = i + 1; j < matrix.size().first; j++)
				{
					bool nullRow = true;

					T tmp = matrix[j][i] / matrix[i][i];
					for (size_t k = i + 1; k < matrix.size().second; k++)
					{
						if (pred(matrix[j][k], tmp * matrix[i][k])) {
							matrix[j][k] = 0;
						}
						else {
							matrix[j][k] -= tmp * matrix[i][k];
							nullRow = false;
						}
					}

					matrix[j][i] = 0;

					if (nullRow) {
						std::swap(matrix[j], matrix.back());
						matrix.pop_back();
						j--;
					}
				}
			}
		}
	}
}

