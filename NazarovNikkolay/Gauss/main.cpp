#include <iostream>
#include "clocale"
#include "Vector.h"
#include "reloadedMatrix.h"
#include "Gauss.h"

using namespace std;

int main()
{
	while (true) {
		setlocale(LC_ALL, "Russian");
		int size;
		cout << "������� ������ �������:" << endl;
		cin >> size;

		Gauss<double>mainMatrix(size);
		Vector<double>resultMatrix(size);
		
		cout << "����������� �������:" << endl;
		mainMatrix.showSystem();

		//����� ������ ������
		resultMatrix = mainMatrix.gaussMethod();

		//�������� ������� � ������� ���������� ������� ������ Gauss
		mainMatrix.check();
		cout << endl;

		//����� ������� �� �����
		cout << "�������:" << endl;
		resultMatrix.print();

		//����������� �������
		int repeatCheck;
		cout << "���� ������ ������ ��� ���� ������� �� ������� 1, ���� ���, ������� 0" << endl;
		cin >> repeatCheck;
		if (repeatCheck == 0){
			delete &mainMatrix;
			delete &resultMatrix;
			break;
		}
		else if (repeatCheck != 1) {
			cout << "�� ���������� ����";
		}
	}
}