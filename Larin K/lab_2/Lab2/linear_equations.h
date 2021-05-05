#pragma once

#include "matrix.h"

namespace lab {

	enum equationsResults { OK, INCONSISTENT, INF_SOLUTIONS };

	template <typename T, typename pivotType = basePivot<T>, typename predType = isEqual<T>>
	Matrix<T> solveEquationSystem(Matrix<T> sys, vector<T>& ans, int& err, 
								  pivotType pivot = pivotType(), predType pred = predType(),
								  bool isTriangle = false)
	{
		err = equationsResults::OK;

		if (!isTriangle) {
			sys.gauss(pivot, pred);
		}

		if (sys.size().first + 1 != sys.size().second) {
			err = equationsResults::INF_SOLUTIONS;
			
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
					err = equationsResults::INCONSISTENT;
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
						err = equationsResults::INF_SOLUTIONS;
					}
					else {
						err = equationsResults::INCONSISTENT;
					}

					break;
				}

				ans[i] /= sys[i][i];
			}
		}

		return sys;
	}


}

