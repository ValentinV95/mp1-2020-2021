#pragma once
#include "Vector.h"
#include "reloadedMatrix.h"

using namespace std;


template < typename T >
class Gauss : public Matrix<T>
{
public:
	double* rightVector;
	Gauss(int n) : Matrix <T>(n){
		
		for (int i = 0; i < this->size; i++){
			for (int j = 0; j < this->size; j++){
				cout << "Введите элемент [" << j + 1 << "] [" << i + 1 << "]:" << endl;
				cin >> this->data[i][j];
			}
		}

		this->rightVector = new double[this->size];

		for (int i = 0; i < this->size; i++) {
			cout << "Введите " << i + 1 << " элемент правой части:" << endl;
			cin >> rightVector[i];
		}
	}
	
	~Gauss() {
		delete[] rightVector;
	}

	void check(){
		T* check = new T[this->size];
		cout << endl;
		cout << "Результат при проверке:" << endl;
		for (int i = 0; i < this->size; i++){
			for (int j = 0; j < this->size; j++){
				check[i] += this->data[i][j] * rightVector[j];
			}
			cout << rightVector[i] << "\t";
		}
	}

	void swap(int a, int b){
		if (a < this->size && b < this->size){
			T r_tmp;
			r_tmp = rightVector[a];
			rightVector[a] = rightVector[b];
			rightVector[b] = r_tmp;
			T* tmp = new T[this->size];
			for (int i = 0; i < this->size; i++){
				tmp[i] = this->data[a][i];
				this->data[a][i] = this->data[b][i];
				this->data[b][i] = tmp[i];
			}
			delete[]tmp;
		}
		else{
			cout << "Неправильная строка!";
			exit(1);
		}
	}

	void showSystem(){
		for (int i = 0; i < this->size; i++){
			for (int j = 0; j < this->size; j++){
				cout << this->data[i][j] << "\t";
			}
			cout << "| " << rightVector[i] << endl;
		}
		cout << endl;
	}

	T mod(T a) {
		if (a < 0)
		{
			return -a;
		}
		else
		{
			return a;
		}
	}

	Vector <T> gaussMethod()
	{
		for (int j = 0; j < this->size; j++)
		{
			int i = 0;
			int max_index = i + j;
			T max = mod(this->data[i + j][j]);
			for (i + j + 1; i + j + 1 < this->size; i++);
			{
				if (mod(this->data[i + j][j]) > max)
				{
					max_index = i + j;
				}
			}
			swap(j, max_index);
			for (int n = j + 1; n < this->size; n++)
			{
				if (this->data[j][j] != 0)
				{
					for (int k = j; k < this->size; k++)
					{
						this->data[n][k] += this->data[j][k] * (-(this->data[n][j] / this->data[j][j]));
					}
					rightVector[n] += rightVector[j] * (-(this->data[n][j] / this->data[j][j]));
				}
				else
				{
					cout << "ERROR: Деление на 0" << endl;
					exit(3);
				}
			}
		}

		for (int i = 0; i < this->size; i++)
		{
			T sum = 0;
			for (int j = 0; j < this->size; j++)
			{
				sum += mod(this->data[i][j]);
			}
			if ((sum == 0) && (rightVector[i] != 0))
			{
				cout << "Система не совместна - решений не имеет" << endl;
				exit(2);
			}
			if ((sum == 0) && (rightVector[i] == 0))
			{
				cout << "Система не имеет частных решений." << endl;
				exit(3);
			}
		}

		T* res = new T[this->size];
		for (int i = this->size - 1; i >= 0; i--)
		{
			T tmp = 0;
			for (int j = i + 1; j < this->size; j++)
			{
				tmp += this->data[i][j] * res[j];
			}
			res[i] = (rightVector[i] - tmp) / this->data[i][i];
		}
		return Vector<T>(this->size, res);
	}

};