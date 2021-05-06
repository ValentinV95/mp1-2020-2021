#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <locale.h>
#include <cstdlib>
#include <ctime>
#include "VectorsMatrixGauss.h"


typedef unsigned int uint;
using namespace std;


template<typename T>
bool checking(Vector<T>& correct_y, Vector<T>& our_answer) {
	double eps = 10e-9;
	for (int i = 0; i < correct_y.Get_size(); i++)
		if (abs(correct_y.coords[i] - our_answer.coords[i]) > eps)
			return false;
	return true;
}

int main() {
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	uint dim;
	short int key;
	const double eps = 10e-9;
	cout << "������� ���-�� ���������� = ���-�� ���������: ";
	cin >> dim;
	Vector <double> b(dim);

	// ������ ����� �������-������� ��������� ������ ��� �������� �� ������������ � ����������
	Vector <double> copy(dim);
	Matrix <double> A(dim);
	cout << "���� ������� ������������� ������� �" << endl;
	cout << "1 - ���������� � ����������" << endl;
	cout << "2 - ������� �� ��������� �����" << endl;
	cout << "������� �����: " << endl;
	cin >> key;

	if (key == 1)
		cin >> A;
	else if (key == 2)
		A.generate_random_matrix();
	else {
		cout << "�������������� �����!" << endl;
		exit(-10);
	}

	cout << "���� ������� ��������� ������ b" << endl;
	cout << "1 - ���������� � ����������" << endl;
	cout << "2 - ������� �� ��������� �����" << endl;
	cin >> key;
	if (key == 1)
		cin >> b;
	else if (key == 2)
		b.generate_random_vector();
	else {
		cout << "�������������� �����!" << endl;
		exit(-11);
	}

	copy = b;
	cout << endl;
	GaussMethod<double> system(A);
	cout << "������� ���������: " << endl;
	system.display_system(b);
	cout << endl;

	cout << "������� ������� ������� ���������:" << endl;
	system.Solve(b);
	cout << b << endl;
	b = A * b;
	
	// ������ ������� �������� �� ������������
	/*if (copy.Is_equal(b))
		cout << "������� ��������� ������ �����!" << endl;
	else
		cout << "������� ������ �������!" << endl;
		*/


	// ���������� �������� �� ������������
	if (checking(copy, b))
		cout << "������� ��������� ������ �����!" << endl;
	else
		cout << "������� ������ �������!" << endl;
		
	cout << "����������� = " << eps << endl;
	return 0;
}