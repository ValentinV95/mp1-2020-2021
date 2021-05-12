#pragma once

#include "vector.h"
#include "Matrix.h"
#include <type_traits>

enum class eqResults { OK, INCONSISTENT, INF_SOLUTIONS, NOT_SQUARE, UNKNOWN };

template <typename T>
class equationsSystem
{
public:
   
	equationsSystem(const Matrix<T>& matrix) : m(matrix), err(eqResults::UNKNOWN) {}

	Vector<T> operator()()
	{
		this->err = eqResults::UNKNOWN;

		if (m.geth() + 1 != m.getw()) 
		{
			this->err = eqResults::NOT_SQUARE;
		}
		else 
		{
			for (size_t i = 0; i < m.geth(); i++)
			{
				size_t row = this->m.MaxIndexInCol(i);
				if (row != i) 
				{
					swap(m[i], m[row]);
				}

				if (m[i][i] == 0) 
				{
					if (m[i][m.getw() - 1] != 0) 
					{
						for (size_t j = i + 1; j + 1 < m.getsize(); j++)
						{
							if (m[i][j] != 0) 
							{
								this->err = eqResults::INF_SOLUTIONS;
								break;
							}
						}

						if (this->err == eqResults::UNKNOWN) 
						{
							this->err = eqResults::INCONSISTENT;
						}
					}
					else 
					{
						this->err = eqResults::INF_SOLUTIONS;
					}

					break;
				}
				else 
				{
					for (size_t j = i + 1; j < m.geth(); j++)
					{
						T tmp = m[j][i] / m[i][i];
						for (size_t k = i + 1; k < m.getw(); k++)
						{
							if (compare(m[j][k], tmp * m[i][k]) )
							{
								m[j][k] = 0;
							}
							else 
							{
								m[j][k] -= tmp * m[i][k];
							}
						}

						m[j][i] = 0;
					}
				}
			}
		}

		Vector<T> ans(m.getw() - 1, T(0));
		T sum;

		if (this->err == eqResults::UNKNOWN)
		{
			for (int i = m.geth() - 1; i >= 0; i--)
			{
				sum = 0;
				for (size_t j = i + 1; j + 1 < m.getw(); j++)
				{
					sum += m[i][j] * ans[j];
				}

				ans[i] = (m[i][m.getw() - 1] - sum) / m[i][i];
			}
		
		    this->err = eqResults::OK;

		}
		

		return ans;
	}

	eqResults getErr()
	{
		return this->err;
	}

private:
	Matrix<T> m;
	eqResults err;

	bool compare(const T& l, const T& r)
	{
		if (is_floating_point<T>::value) 
		{
			return std::abs(l - r) < std::numeric_limits<T>::epsilon() * 1000;
		}
		else 
		{
			return l == r;
		}
	}
};



