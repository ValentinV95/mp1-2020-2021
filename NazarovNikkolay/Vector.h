#pragma once

using namespace std;

template <typename T>
class Vector{
public:
	Vector(){
		data = new T[1];
		size = 1;
	}

	Vector(int _size, T _value = T()){
		size = _size;
		data = new T[_size];
		for (int i = 0; i < _size; i++){
			data[i] = _value;
		}
	}

	Vector(int _size, T* values){
		size = _size;
		data = new T[_size];
		for (int i = 0; i < _size; i++){
			data[i] = values[i];
		}
	}

	Vector(const Vector& v){
		delete[]this->data;
		this->size = v.size;
		this->data = new T[v.size];
		for (int i = 0; i < v.size; i++){
			this->data[i] = v.data[i];
		}
		return *this;
	}

	T& operator[](int i){
		return data[i];
	}

	Vector& operator=(const Vector& v){
		delete[]this->data;
		this->size = v.size;
		this->data = new T[v.size];
		for (int i = 0; i < v.size; i++){
			this->data[i] = v.data[i];
		}
		return *this;
	}

	void print(){
		for (int i = 0; i < size; i++){
			cout << "x" << i << "= " << data[i] << "\t";
		}
	}

	void getSize(){
		return size;
	}

	~Vector(){
		delete[]data;
	}

private:
protected:
	T* data;
	int size;
};