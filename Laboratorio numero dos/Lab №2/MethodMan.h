#pragma once
using namespace std;
template <typename T>
class Method : public Matrix<T>
{
private:
	T* el;
public:
	Method(int n, T _el = T()) : Matrix <T>(n)
	{
		el = new T[n];
		for (size_t i = 0; i < this->size; i++)
		{
			el[i] = _el;
		}
	}

	~Method()
	{
		delete[]el;
	}

	void swap(int str1, int str2, T* el)
	{
		T _tmp;
		_tmp = el[str1];
		el[str1] = el[str2];
		el[str2] = _tmp;
	}

	void s_print(T* el)
	{
		for (size_t i = 0; i < this->size; i++)
		{
			for (size_t j = 0; j < this->size; j++)
			{
				cout << this->arr[i][j] << "\t";
			}
			cout << " | " << el[i] << endl;
		}
		cout << endl;
	}

	void InputMat()
	{
		cout << "1) Enter values manually\n2) Generate random values\n";
		int mode = 1;
		cin >> mode;
		switch (mode) {
		case 1:
			for (size_t i = 0; i < this->size; i++)
			{
				for (size_t j = 0; j < this->size; j++)
				{
					cout << "Input [" << i << "]" << "[" << j << "] element:" << endl;
					cin >> this->arr[i][j];
				}
			}
			break;

		case 2:
			for (size_t i = 0; i < this->size; i++)
			{
				for (size_t j = 0; j < this->size; j++)
				{
					this->arr[i][j] = (double)((rand() / 80.0) - (rand() / 160.0));
				}
			}
			break;
		}
	}

	Vector <T> gauss(T* el)
	{
		T prec = 0.001;

		for (size_t j = 0; j < this->size; j++)
		{
			int i = 0;
			int max_abs_index = i + j;
			T max_abs = abs(this->arr[i + j][j]);
			for (i + j + 1; i + j + 1 < this->size; i++)
			{
				if (abs(this->arr[i + j][j]) > max_abs)
				{
					max_abs_index = i + j;
				}
			}
			swap(j, max_abs_index, el);

			for (size_t l = j + 1; l < this->size; l++)
			{
				if (this->arr[j][j] != 0)
				{
					T rate = -(this->arr[l][j] / this->arr[j][j]);
					for (size_t k = j; k < this->size; k++)
					{
						this->arr[l][k] += this->arr[j][k] * rate;
					}
					el[l] += el[j] * rate;
				}
				else
				{
					cout << "Error" << endl;
					exit(1);
				}
			}
		}

		for (size_t i = 0; i < this->size; i++)
		{
			for (size_t j = 0; j < this->size; j++)
			{
				if (abs(this->arr[i][j]) < prec)
				{
					this->arr[i][j] = 0;
				}
			}
			if (abs(el[i]) < prec)
			{
				el[i] = 0;
			}
		}

		for (size_t i = 0; i < this->size; i++)
		{
			T sum = 0;
			for (size_t j = 0; j < this->size; j++)
			{
				sum += abs(this->arr[i][j]);
			}
			if ((sum == 0) && (el[i] != 0))
			{
				cout << "No solutions" << endl;
				exit(2);
			}
			if ((sum == 0) && (el[i] == 0))
			{
				cout << "Can't solve: the equation depends on the variable" << endl;
				exit(3);
			}
		}

		T* sol = new T[this->size];

		for (int i = this->size - 1; i >= 0; i--)
		{
			T tmp = 0;
			for (int j = i + 1; j < this->size; j++)
			{
				tmp += this->arr[i][j] * sol[j];
			}
			sol[i] = (el[i] - tmp) / this->arr[i][i];

		}

		return Vector<T>(this->size, sol);
	}

	void Check(T* el)
	{
		T* P = new T[this->size - 1];

		double eps = 10e-7;
		bool ch = true;

		cout << "\nChecking values: " << endl;

		for (size_t i = 0; i < this->size; i++)
		{
			for (size_t j = 0; j < this->size; j++)
			{
				P[i] += (this->arr[i][j]) * el[j];
			}
			cout << el[i] << endl;

			if (abs(P[i] - el[i]) > eps)
			{
				ch = false;
			}
		}
		delete[]P;
	}
};


