#include <iostream>
#include <ctime>
#include <math.h>
double p;
using namespace std;  
template <class T>
class Vector {
protected:
	T* data;
	size_t size;
public:
	Vector() {
		size = 0;
		data = new T[0];
	}
	Vector(size_t size) {
		this->size = size;
		data = new T[size];
	}
	Vector(size_t size, T v) {
		this->size = size;
		data = new T[size];
		for (size_t i = 0; i < size; i++)
			data[i] = v;
	}
	Vector(const Vector& vec)
	{
		size = vec.size;
		data = new T[size];
		for (size_t i = 0; i < size; i++)
			data[i] = vec.data[i];
	}
	~Vector() {
		delete[] data;
	}

	size_t getsize() { return size; }
	friend ostream& operator<<(ostream& ost, const Vector& vec) {
		for (size_t i = 0; i < vec.size; i++) {
			ost << vec.data[i] << "\t";
		}
		return ost;
	}
	friend istream& operator>>(istream& ist, const Vector& vec) {
		for (size_t i = 0; i < vec.size; i++)
			ist >> vec.data[i];

		return ist;
	}
	Vector& operator=(const Vector& vec) {
		if (this == &vec) return *this;

		if (size != vec.size) {
			size = vec.size;
			delete[] data;
			data = new T[size];
		}
		for (size_t i = 0; i < size; i++)
			data[i] = vec.data[i];

		return *this;
	}
	Vector operator+(const Vector& vec) {
		Vector result = *this;
		for (size_t i = 0; i < size; i++)
		{
			result.data[i] += vec.data[i];
		}

		return result;
	}
	Vector operator- (const Vector& vec) {
		Vector result = *this;
		for (size_t i = 0; i < size; i++)
		{
			result.data[i] -= vec.data[i];
		}

		return result;
	}
	Vector operator* (const T& n) {
		Vector result = *this;
		for (size_t i = 0; i < size; i++)
		{
			result.data[i] *= n;
		}

		return result;
	}
	Vector operator/(const T& n) {
		Vector result = *this;
		for (size_t i = 0; i < size; i++)
		{
			result.data[i] /= n;
		}

		return result;
	}
	T& operator[](size_t i) {
 		return data[i];
	}
	const T& operator[](size_t i) const {
		return data[i];
	}
	bool operator==(const Vector& vec) {
		if (this == &vec) return true;
		if (size != vec.size) return false;
		for (size_t i = 0; i < size; i++)
		{
			if (data[i] != vec.data[i]) return false;
		}
		return true;
	}
	bool operator!= (const Vector& vec) {
		return !(*this == vec);
	}
};
template <class T>
class Matrix : public Vector<Vector<T>> {
public:
	Matrix(size_t size, const Vector<T>& vec): Vector<Vector<T>>(size, vec) {}
	Vector<T> operator* (const Vector<T>& v) {
		size_t col = this->getsize();
		size_t row = (*this)[0].getsize();
		Vector<T> res(col, 0);
		for (int i = 0; i < col; i++)
		{  for (int j = 0; j < row; j++)
			{res[i] = res[i] + ((*this)[i][j] * v[j]);
			}
		}
		return res;
	}
};
template <class T>
class SLE : public Matrix<T> {
protected:
	bool flagsol; // есть ли единственное решение
	int maxsrch(const SLE<T>& sle, size_t col, size_t i_col)// поиск максимума в столбце
	{   T max_el = sle[i_col][i_col]; //максимум
		size_t max_ind = i_col; // индекс максимума в столбце
		int count = 0; // подсчет ненулевых элементов в столбце
		for (size_t i = i_col; i < col; i++) {
			if (sle[i][i_col] != 0) count++;
			if (sle[i][i_col] * sle[i][i_col] > max_el * max_el) {
				max_el = sle[i][i_col];
				max_ind = i;
			}
		}
		if (count == 0) max_ind = -1;
		return max_ind;
	};
	bool nullcol(const SLE<T>& sle, size_t row, size_t col) {//проверка нулевых столбцов
		for (size_t i = 0; i < col; i++)
		{  int count = 0;//количество ненулевых элементов в столбце
			for (size_t j = 0; j < row; j++)
				if (sle[j][i] != 0) count++;
			if (count == 0) return true;
		}
		return false;
	};
	void slecheck(SLE<T>& sle, size_t col, size_t row, size_t i_col, Vector<T>& v) // проверка на нулевые строки  и  свободные переменные 
	{   int count_nozerorow = 0; // подсчет ненулевых строк
		for (size_t i = 0; i < col; i++)
		{   int count = 0; // подсчет ненулевых элементов строки
			for (size_t j = 0; j < row; j++)
			{ if (sle[i][j] != 0) count++;}
			if ((count == 0) && (v[i] != 0))
			{   cout << "No solutions" << endl << endl;;
				flagsol = false;
				return;
			}
			else if (!(count == 0 && v[i] == 0)) count_nozerorow++;
		}
		if (count_nozerorow < i_col + 1)
		{   cout << "Infinitely many solutions" << endl << endl;
			flagsol = false;
			return;
		}
	};
public:
	SLE(size_t col, const Vector<T>& vec): Matrix<T>(col, vec)
	{   
		flagsol = true;
	}
	Vector<T> GaussSolve(Vector<T>& v)
	{   size_t row = (*this)[0].getsize();
		size_t col = this->getsize();
		size_t ved; // индекс ведущего 
		Vector<T> sol_vec(row); 
		Vector<T> zero_vec(row);
		// Прямой ход Гаусса
		if (!(nullcol(*this, col, row)))
		{  for (size_t i = 0; i < row; i++)
			{   slecheck(*this, col, row, i, v);
				if (!flagsol) return zero_vec;
				ved = maxsrch(*this, col, i);
				if (ved != -1)
				{   swap<Vector<T>>((*this)[i], (*this)[ved]);
					swap<T>(v[i], v[ved]);
					T elem = (*this)[i][i];
					(*this)[i] = (*this)[i] / elem;
					v[i] = v[i] / elem;
					for (size_t j = i + 1; j < col; j++)
					{   T n = (*this)[j][i];
						(*this)[j] = (*this)[j] - ((*this)[i] * n);
						v[j] = v[j] - (v[i] * n);
					}
				}
				else
				{   cout << "Infinitely many solutions" << endl << endl;
					flagsol = false;
					return zero_vec;
				}
			}
		}
		else {
			cout << "No solutions or infinitely many solutions " << endl << endl;
			flagsol = false;
			return zero_vec;
		}
		// Обратный ход Гаусса
		for (int i = row - 1; i >= 0; i--)
		{  sol_vec[i] = v[i];
			for (int j = row - 1; j >= i + 1; j--)
			{ sol_vec[i] = sol_vec[i] - ((*this)[i][j] * sol_vec[j]);
			}
		}
		return sol_vec;
	}
};
template <class T>
void check(const SLE<T>& sle, const Vector<T>& sol, const Vector<T>& vec_copy) {
	Vector<T> check = (Matrix<T>)sle * sol;
	double eps = 10e-7;
	bool checkflag = true;
	for (size_t i = 0; i < check.getsize(); i++)
	{
		p += abs(check[i] - vec_copy[i]);
		if (abs(check[i] - vec_copy[i]) > eps) checkflag = false;
	}
	p/= check.getsize();
	if (checkflag) cout << "System solved successfully" << endl << "The error value: " << p << endl;
	else cout << "System solved unsuccessfully " << endl << "The error value: " << p << endl;
	
}
void main()
{   int  k1, k2;
	int col_size, row_size;
	cout << "Enter number of equations: ";
	cin >> col_size;
	cout << endl;
	cout << "Enter number of variables: ";
	cin >> row_size;
	cout << endl;
	Vector<double> vec(row_size), right_vec(col_size); 
	SLE<double> system(col_size, vec);
	Vector<double> solution(row_size);
	cout << "Method of filling the system of equations: " << endl;
	cout << endl << "1. Keyboard input" << endl << "2. Random system" << endl << "3. Hilbert Matrix" << endl;
	cout << "Enter the method number: ";
	cin >> k1;
	cout << endl;
	if (k1 == 1) {
		cout << "Enter the matrix of coefficients: " << endl;
		cin >> system; // Ввод матрицы коэффициентов в левой части
		cout << endl;
	};
	if (k1 == 2) {
		srand(time(NULL));
		for (size_t i = 0; i < col_size; i++)
		{
			for (size_t j = 0; j < row_size; j++)
			{
				system[i][j] = (double)rand()*0.000001;
			}
		}
	};
	if (k1 == 3) {
		for (size_t i = 0; i < col_size; i++)
		{
			for (size_t j = 0; j < row_size; j++)
			{
				system[i][j] = (double)1.0 /((i + 1) + (j + 1) - 1.0);
			}
		}
	};
	cout << "Method of filling the right-hand vector" << endl << "1. Keyboard input" << endl << "2. Random vector" << endl << "3. Vector for Hilbert Matrix" << endl;
	cout << "Enter the method number: ";
	cin >> k2;
	cout << endl;
	if (k2 == 1) {
		cout << "Enter the column of coefficients in right-hand vector: " << endl;
		cin >> right_vec; // Ввод столбца свободных коэффициентов в правой части
		cout << endl;
	}
	if (k2 == 2) {
		srand(time(NULL));
		for (size_t i = 0; i < col_size; i++)
		{
			right_vec[i] = (double)rand()*0.0000001 ;
		}
	}
	if (k2 == 3) {
		for (size_t i = 0; i < col_size; i++)
		{
			right_vec[i] = (double)rand() * ((double)1.0 / (i + 1));
		}
	};
	cout << "System: " << endl;
	for (size_t i = 0; i < system.getsize(); i++)
	{
		cout << system[i] << "|" << right_vec[i] << endl;
	}
	solution = system.GaussSolve(right_vec);
	cout << "Solution-vector: " << endl;
	for (size_t i = 0; i < solution.getsize(); i++)
	{
		cout << solution[i] << endl;
	}
	cout << endl;
	check(system, solution, right_vec);

}
