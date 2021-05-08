#pragma once

#include "matrix.h"

namespace lab {

	enum class eqResults { OK, INCONSISTENT, INF_SOLUTIONS };

	template <typename T, typename pivotType = basePivot<T>, typename predType = isEqual<T>>
	Matrix<T> solveEquationSystem(Matrix<T> sys, vector<T>& ans, eqResults& err,
								  pivotType pivot = pivotType(), predType pred = predType(),
								  bool isTriangle = false)
	{
		err = eqResults::OK;

		if (!isTriangle) {
			sys.gauss(pivot, pred);
		}

		if (sys.size().first + 1 != sys.size().second) {
			err = eqResults::INF_SOLUTIONS;
			
			if (sys.size().first + 1 > sys.size().second) {
				bool flag = true;
				for (size_t i = 0; i + 1 < sys.size().second; i++)
				{
					if (sys.back()[i] != 0) {
						flag = false;
						break;
					}
				}

				if (flag) {
					err = eqResults::INCONSISTENT;
				}
			}
		}
		else {
			ans.resize(sys.size().first);
			T sum;
			for (size_t i = sys.size().first; i > 0;)
			{
				--i;

				sum = 0;
				for (size_t j = i + 1; j < sys.size().first; j++)
				{
					sum += sys[i][j] * ans[j];
				}

				bool ansIsNull = pred(sys[i].back(), sum);
				ans[i] = sys[i].back() - sum;
				if (sys[i][i] == 0) {
					if (ansIsNull) {
						err = eqResults::INF_SOLUTIONS;
					}
					else {
						err = eqResults::INCONSISTENT;
					}

					break;
				}

				ans[i] /= sys[i][i];
			}
		}

		return sys;
	}


}

