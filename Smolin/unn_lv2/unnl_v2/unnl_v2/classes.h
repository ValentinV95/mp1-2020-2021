#include <iostream>
#include <cmath>

const double eps = 10e-9;

template <typename T>
class vector {
protected:
	T* data;
	size_t size;
public:
	vector() { size = 0; data = nullptr; }

	vector(size_t _size) {
		size = _size;
		data = new T[size];
	}

	vector(vector& sec) {
		size = sec.size;
		data = new T[size];
		for (size_t i = 0; i < size; i++)
			data[i] = sec.data[i];
	}

	void set_size(int _size)
	{
		if (size != _size)
		{
			delete[] data;
			data = new T[_size];
			size = _size;
		}
	}

	T get_data(size_t ind){
		return data[ind];
	}

	size_t get_size() {
		return size;
	}

	void set_random() {
		srand(static_cast<unsigned int>(time(0)));
		for (size_t i = 0; i < size; i++) {
			data[i] = (T)(rand() % 200) / 10.0;
		}
	}

	void set_manual() {
		for (size_t i = 0; i < size; i++)
		{
			std::cin >> data[i];
		}
	}

	void vec_swap(size_t first, size_t sec)
	{
		if (first != sec)
		{
			T tmp = this->data[first];
			this->data[first] = this->data[sec];
			this->data[first] = tmp;
		}
	}

	void print() {
		for (size_t i = 0; i < size; i++) {
			std::cout << data[i] << std::endl;
		}
	}

	vector& operator=(const vector& sec)
	{
		if (size != sec.size)
		{
			delete[] data;
			data = nullptr;
			size = 0;
			data = new T[sec.size];
			size = sec.size;
		}

		for (size_t i = 0; i < size; i++)
		{
			this->data[i] = sec.data[i];
		}
		return *this;

	}

	vector<T>& operator *=(T second) {
		for (size_t i = 0; i < size; i++)
			data[i] *= second;
		return *this;
	}

	vector<T>& operator /=(T second) {
		for (size_t i = 0; i < size; i++)
			data[i] /= second;
		return *this;
	}

	vector& operator-=(vector second) {
		for (size_t i = 0; i < size; i++)
			data[i] -= second.data[i];
		return *this;
	}

	vector<T>& operator+=(vector<T> a)
	{
		for (int i = 0; i < size; i++)
		{
			data[i] += a[i];
		}

		return *this;
	}

	vector operator+(vector& second) {
		if (size != second.size) {
			std::cout << "sizes are not equal" << std::endl;
			exit(-2);
		}
		vector result = *this;
		for (int i = 0; i < size; i++)
			result.data[i] += second.data[i];
		return result;
	}

	vector operator-(vector& second) {
		if (size != second.size) {
			std::cout << "sizes are not equal" << std::endl;
			exit(-3);
		};

		vector result = *this;
		for (int i = 0; i < size; i++)
			result.data[i] -= second.data[i];
		return result;
	}

	friend vector<T> operator*(const vector<T>& a, T b)
	{
		vector<T> result(a.size);
		for (int i = 0; i < a.size; i++)
		{
			result[i] = a[i] * b;
		}
		return result;
	}

	friend vector operator*(T b, const vector<T>& a) 
	{
		vector<T> result(a.size);
		for (int i = 0; i < a.size; i++)
		{
			result[i] = a[i] * b;
		}
		return result;
	}

	T& operator[](size_t i)
	{
		if (i < 0 || i >= size) 
		{
			std::cout << "out of arr";
			exit(-4);
		}

		return data[i];
	}

	const T& operator[](size_t i) const
	{
		if (i < 0 || i >= size) 
		{
			std::cout << "out of arr";
			exit(-5);
		}

		return data[i];
	}

	friend std::ostream& operator<<(std::ostream& out, const vector<T>& vec)
	{
		out << "\t";
		for (size_t i = 0; i < vec.size; i++)
			out << vec[i] << "\t";
		out << '\n';
		return out;
	}

	friend std::istream& operator>>(std::istream& in, vector<T>& vec)
	{
		for (size_t i = 0; i < vec.size; i++)
			in >> vec[i];

		return in;
	}

	~vector() {
		delete[] data;
	}
};


template <typename T>
class matrix : public vector<vector<T>> {
public:
	matrix(int _size) : vector<vector<T>>(_size)
	{
		for (size_t i = 0; i < this->size; i++)
		{
			this->data[i].set_size(this->size);
		}
	}

	~matrix(){}

	void set_random_matrix()
	{
		srand(static_cast<unsigned int>(time(0)));
		for (size_t i = 0; i < this->size; i++)
		{
			for (size_t j = 0; j < this->size; j++) 
			{
				this->data[i][j] = (T)(rand() % 200) / 10.0;
			}
		}
	}

	void set_manual_matrix()
	{
		srand(static_cast<unsigned int>(time(0)));
		for (size_t i = 0; i < this->size; i++)
		{
			for (size_t j = 0; j < this->size; j++)
			{
				std::cin >> this->data[i][j];
			}
		}
	}

	void show_system(vector<T> right_side) {
		for (size_t i = 0; i < this->size; i++) {
			for (size_t j = 0; j < this->size; j++) {
				std::cout << this->data[i][j] << "*x" << j+1;
				if (j <= this->size - 2)
					std::cout << " + ";
			}
			std::cout << " = " << right_side[i] << std::endl;
		}
	}

	size_t max_col(size_t col)
	{
		T max = this->data[col][col];
		int num = col;

		for (int i = col + 1; i < this->size; i++)
		{
			if (abs(max) < abs(this->data[i][col]))
			{
				max = this->data[i][col];
				num = i;
			}
		}

		return num;
	}

	void swap(int i, int j)
	{
		if (i != j)
		{
			vector<T> tmp = this->data[i];
			this->data[i] = this->data[j];
			this->data[j] = tmp;
		}
	}

	void solve(vector<T>& a)
	{
		std::cout << solve << std::endl;
	}
		
};
