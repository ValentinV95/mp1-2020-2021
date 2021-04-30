#pragma once

#include <iomanip>
#include <iostream>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;

void error(int code) { // Выдача сообщений об ошибках и завершение программы
	switch (code) {
	case 1:
		cerr << "Error: can't complete the operation - vectors have different length" << endl;
		exit(1);
		break;
	case 2:
		cerr << "System has no solutions" << endl << endl;
		break;
	case 3:
		cerr << "System has infinitely many solutions" << endl << endl;
		break;
	case 4:
		cerr << "System has a zero-column so it has no solutions or infinitely many solutions" << endl << endl;
		break;
	default:
		cout << "Can't do anything with this input" << endl << endl;
		break;
	}
}

template <typename T>
class Vector {
protected:
	T* data;
	size_t size;
public:

	Vector(size_t _size = 0, const T& sample = T()) {
		size = _size;
		data = new T[size];
		for (size_t i = 0; i < size; i++)
			data[i] = sample;
	}

	Vector(const Vector& vec) {
		size = vec.size;
		data = new T[size];
		for (size_t i = 0; i < size; i++)
			data[i] = vec.data[i];
	}

	size_t GetSize() { return size; }

	friend std::ostream& operator<< (std::ostream& ost, const Vector& vec) {
		for (size_t i = 0; i < vec.size; i++) {
			ost << std::fixed << std::setprecision(5) << vec.data[i] << "\t";
		}
		return ost;
	}

	friend std::istream& operator>> (std::istream& ist, const Vector& vec) {
		for (size_t i = 0; i < vec.size; i++)
			ist >> vec.data[i];

		return ist;
	}

	Vector& operator= (const Vector& vec) {
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

	Vector operator+ (const Vector& vec) {
		if (this->size != vec.size) error(1);

		Vector result = *this;
		for (size_t i = 0; i < size; i++)
			result.data[i] += vec.data[i];

		return result;
	}

	Vector operator- (const Vector& vec) {
		if (this->size != vec.size) error(1);

		Vector result = *this;
		for (size_t i = 0; i < size; i++)
			result.data[i] -= vec.data[i];

		return result;
	}

	Vector operator* (const T& coefficient) {
		Vector result = *this;
		for (size_t i = 0; i < size; i++)
			result.data[i] *= coefficient;

		return result;
	}

	Vector operator/ (const T& coefficient) {
		Vector result = *this;
		for (size_t i = 0; i < size; i++)
			result.data[i] /= coefficient;

		return result;
	}

	Vector& operator+= (const Vector& vec) {
		if (this->size != vec.size) error(1);

		for (size_t i = 0; i < size; i++)
			data[i] += vec.data[i];

		return *this;
	}

	Vector& operator-= (const Vector& vec) {
		if (this->size != vec.size) error(1);

		for (size_t i = 0; i < size; i++)
			data[i] -= vec.data[i];

		return *this;
	}

	Vector& operator*= (const T& coefficient) {
		*this = *this * coefficient;
		return *this;
	}

	Vector& operator/= (const T& coefficient) {
		for (size_t i = 0; i < size; i++)
			data[i] /= coefficient;
		return *this;
	}

	T& operator[] (size_t i) {
		if (i >= size && i < 0) {
			cout << "Reading out of bounds!!!" << endl;
			exit(1);
		}
		else return data[i];
	}

	const T& operator[] (size_t i) const {
		if (i >= size && i < 0) {
			cout << "Reading out of bounds!!!" << endl;
			exit(1);
		}
		else return data[i];
	}

	bool operator== (const Vector& vec) {
		if (this == &vec) return true;

		if (size != vec.size) return false;

		for (size_t i = 0; i < size; i++)
			if (data[i] != vec.data[i]) return false;

		return true;
	}

	bool operator!= (const Vector& vec) {
		return !(*this == vec);
	}

	~Vector() {
		delete[] data;
	}
};