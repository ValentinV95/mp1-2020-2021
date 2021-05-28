#include <ostream>
#include <istream>
#include <iostream>
using namespace std;
template <typename T> class Line;

template <typename T> class vector {
protected:
	T* data;
	size_t _size;

	static void copy_data(vector<T>& to, const vector<T>& from) {
		copy_data(to.data, from.data, min(to._size, from._size));
	}

	static void copy_data(T* to_array, T* from_array, size_t size) {
		for (size_t i = 0;i < size;i++) {
			to_array[i] = from_array[i];
		}
	}

	//reallocate memory with data deletion
	void realloc(size_t new_size) {
		if (new_size == _size)return;

		delete[] data;
		_size = new_size;
		data = new T[_size];
	}

	void set_zero(T* data, size_t size) {
		for (size_t i = 0;i < size;i++) {
			data[i] = 0;
		}
	}

public:
	friend Line<T>;
	vector() :vector(0) {}

	vector(const vector<T>& second) :vector(second._size) {
		copy_data(*this, second);
	}

	vector(size_t size) {
		_size = size;
		data = new T[_size];
		set_zero(data, size);
	}

	size_t size() {
		return _size;
	}

	//reallocate memory with data copying
	void resize(size_t new_size) {
		if (new_size == _size)return;

		T* temp_data = new T[new_size];
		set_zero(temp_data, new_size);
		copy_data(temp_data, data, min(_size, new_size));

		delete[] data;
		data = temp_data;
		_size = new_size;
	}

	T& operator[](size_t index) {
#ifdef DEBUG
		if (index >= _size) exit(1);
#endif // DEBUG
		return data[index];
	}
	//copied how much fits
	vector<T>& operator = (const vector<T>& second) {
		if (this != &second) {
			//this->realloc(second._size);
			copy_data(*this, second);
		}
		return *this;
	}

	~vector() {
		delete[] data;
	}

	static void swap(vector<T>& x, vector<T>& y) {
		if (&x == &y)return;
		T* temp_data = x.data;
		size_t temp_size = x._size;

		x.data = y.data;
		x._size = y._size;

		y.data = temp_data;
		y._size = temp_size;
	}
};

template<typename T> std::ostream& operator << (std::ostream& ost, vector<T>& second) {
	size_t si = second.size();
	for (size_t i = 0;i < si;i++) {
		ost.precision(3);
		ost.setf(std::ios::left);
		ost.width(5);
		ost << second[i] << " ";
	}
	return ost;
};

template <typename T> class Line
{
protected:
	T*& data;
	size_t& _size;
public:
	Line(vector<T>& v) : data(v.data), _size(v._size) {}

	size_t size() {
		return _size;
	}

	T& operator[](size_t index) {
#ifdef DEBUG
		if (index >= _size) exit(1);
#endif // DEBUG
		return data[index];
	}

	void set_zero() {
		for (size_t i = 0;i < _size;i++) {
			data[i] = 0;
		}
	}

	Line<T>& operator = (const Line<T>& second) {
		if (_size != second._size) exit(1);
		for (size_t i = 0;i < _size;i++) {
			data[i] = second.data[i];
		}
		return *this;
	}

	Line<T>& operator += (const Line<T>& second) {
		if (_size != second._size) exit(1);
		for (size_t i = 0;i < _size;i++) {
			data[i] += second.data[i];
		}
		return *this;
	}

	Line<T>& operator -= (const Line<T>& second) {
		if (_size != second._size) exit(1);
		for (size_t i = 0;i < _size;i++) {
			data[i] -= second.data[i];
		}
		return *this;
	}

	Line<T>& operator *= (const T& second) {
		for (size_t i = 0;i < _size;i++) {
			data[i] *= second;
		}
		return *this;
	}
};

//perceived as an array of strings
template <typename T> class matrix :
	protected vector<vector<T>>
{
protected:
	size_t& _n = this->_size, _m;
	vector<T>*& _data = this->data;

public:
	matrix() :matrix(1, 0) {}
	matrix(size_t n, size_t m) {
		if (n == 0) n = 1;

		_n = n;	_m = m;
		_data = new vector<T>[_n];
		for (size_t i = 0;i < _n;i++) {
			_data[i].resize(_m);
		}
	}

	matrix(const matrix<T>& mat) {
		_n = 1;	_m = 0;
		_data = new vector<T>[_n];
		for (size_t i = 0;i < _n;i++) {
			_data[i].resize(_m);
		}
		(*this) = mat;
	}

	void swap(size_t u, size_t v) {
		if ((u >= _n) || (v >= _n))return;
		vector<T>::swap(_data[u], _data[v]);
	}

	size_t size() {
		return _n;
	}

	void resize(size_t new_n, size_t new_m) {
		if (new_n == 0) new_n = 1;
		if (new_n == _n && new_m == _m)return;
		vector<T>* temp_data = new vector<T>[new_n];

		for (size_t i = 0;i < new_n;i++) {
			temp_data[i].resize(new_m);
			if (i < _n) {
				temp_data[i] = _data[i];
			}
		}

		delete[] _data;
		_data = temp_data;
		_n = new_n; _m = new_m;
	}

	Line<T> operator[](size_t index) {
#ifdef DEBUG
		if (index >= _n) exit(1);
#endif // DEBUG
		return Line<T>(_data[index]);
	}

	const Line<T> operator[](size_t index) const {
#ifdef DEBUG
		if (index >= _n) exit(1);
#endif // DEBUG
		return Line<T>(_data[index]);
	}

	matrix<T>& operator = (const matrix<T>& second) {
		this->resize(second._n, second._m);
		for (size_t i = 0;i < _n;i++) {
			_data[i] = second._data[i];
		}
		return *this;
	}

	matrix<T> operator *(const matrix<T>& second) {
		if (_m != second._n) exit(567);
		size_t n = _n, m = _m, p = second._m;
		matrix<T> ans(n, p);

		//auxiliary variables
		vector<T> temp(p);
		Line<T> temp_line(temp);

		for (size_t line = 0;line < n;line++) {
			ans[line].set_zero();

			for (size_t count = 0;count < m;count++) {
				temp_line.set_zero();
				temp_line = second[count];
				temp_line *= this->_data[line][count];
				ans[line] += temp_line;
			}
		}
		return ans;
	}
};

template <typename T> std::ostream& operator <<(std::ostream& ost, matrix<T>& mat) {
	for (size_t i = 0; i < mat.size(); i++) {
		ost << "|";
		for (size_t j = 0;j < mat[i].size();j++) {
			ost.precision(2);
			ost.setf(std::ios::right);
			ost.width(7);
			ost << mat[i][j] << "|";
		}
		ost << "\n";
	}
	return ost;
};

template <typename T> std::istream& operator >>(std::istream& ist, matrix<T>& mat) {
	for (size_t i = 0; i < mat.size(); i++) {
		for (size_t j = 0;j < mat[i].size();j++) {
			ist >> mat[i][j];
		}
	}
	return ist;
};

template<typename T> class System {
private:
	matrix<T> _mat;
public:
	System(const matrix<T>& mat) {
		_mat = mat;
	};

	/*if solve is inf then 2
	if solve is one then return 1 and answer in b
	if system have not answer then  0
	if -1 is error*/
	int gaussian_method(vector<T>& b) {
		if (b.size() != _mat.size()) return -1;

		matrix<T> mat = _mat;
		mat.resize(mat.size(), mat[0].size() + 1);

		size_t position = mat[0].size() - 1;
		for (size_t i = 0;i < mat.size();i++) {
			mat[i][position] = b[i];
		}
		cout << "Исходная система:\n";
		cout << mat << "\n";
		size_t mi = min(mat.size(), mat[0].size());
		for (size_t leader = 0;leader < mi;leader++) {
			T max = 0;
			size_t number = leader;

			//find max abs
			for (size_t num_row = leader;num_row < mat.size();num_row++) {
				if (abs(max) <= abs(mat[num_row][leader])) {
					max = mat[num_row][leader];
					number = num_row;
				}
			}
			mat.swap(number, leader);

			if (mat[leader][leader] != 0) {
				for (size_t i = leader + 1;i < mat.size();i++) {
					if (mat[i][leader] == 0)continue;
					mat[i] *= (mat[leader][leader] / mat[i][leader]);
					mat[i] -= mat[leader];
				}
			}
		}
		for (int i = mi - 1;i >= 0;i--) {
			if (mat[i][i] != 0) {
				for (int j = i - 1;j >= 0;j--) {
					if (mat[j][i] != 0) {
						mat[j] *= (mat[i][i] / mat[j][i]);
						mat[j] -= mat[i];
					}
				}
				b[i] = mat[i][mat[0].size() - 1] / mat[i][i];
			}
		}
		cout << "После преобразований:\n";
		cout << mat;

		bool flag = true;
		bool inf = false;
		for (int i = 0;i < mat.size();i++) {
			flag = true;
			for (int j = 0;j < mat[0].size() - 1;j++) {
				if (mat[i][j] != 0)flag = false;
			}
			if (flag) {
				if (mat[i][mat[0].size() - 1] != 0) {
					return 0;//система несовместна
				}
				else {
					inf = true;//решений бесконечно много
				}
			}
		}
		if (inf)return 2;
		return 1;
	};

};