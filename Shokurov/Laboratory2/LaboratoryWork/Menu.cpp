#include <iostream>
#include "classes.h"
#define sqr(x) ((x)*(x))
using namespace std;

matrix<double> mat;
vector<double> b;
int limit;
int mod;
double d;
const int Exit = 9;

void input_size() {
	int size;
	do {
		printf("Введите новый размер квад. матрицы\n");
		printf(">");
		cin >> size;
	} while (size <= 0);
	mat.resize(size, size);
	b.resize(size);
	printf("Размер матрицы изменен\n");
}

void random_input() {
	cout << "Формула заполнения: mat(i,j) = rand() % mod + d\n";
	int input = -1;
	while (input != 1) {
		printf("1. Заполнить матрицу случайно\n");
		printf("2. Изменить модуль (mod = %d)\n", mod);
		printf("3. Изменить смещение (d = %lf)\n", d);
		printf(">");
		cin >> input;
		//printf("\n");
		switch (input){
		case 1: {
			for (int i = 0;i < mat.size();i++) {
				for (int j = 0;j < mat[i].size();j++) {
					mat[i][j] = rand() % mod + d;
				}
			}
			printf("Матрица заполнена случайными числами\n");
			break;
		}
		case 2: {
			int value;
			do {
				printf("Введите mod:\n");
				printf(">");
				cin >> value;
			} while (value <= 0);
			mod = value;
			break;
		}
		case 3: {
				printf("Введите d:\n");
				printf(">");
				cin >> d;
			break;
		}
		}
	}
}

void input_matrix() {
	int input = 1;
	if (mat.size() > limit) {
		printf("Потребуется ввести %d значений\n", sqr(mat.size()));
		printf("Продолжить? (1 -> да, 0 -> нет)\n");
		do {
			printf(">");
			cin >> input;
		} while (input != 0 && input != 1);
	}
	if (input == 1) {
		printf("Введите %d значений:\n", sqr(mat.size()));
				cin >> mat;
		printf("Матрица заполнена\n");
	}
}

void show_matrix() {
	int input = 1;
	if (mat.size() > limit) {
		printf("Размер матрицы больше (%dx%d)\n", limit, limit);
		printf("Продолжить? (1 -> да, 0 -> нет)\n");
		do {
			printf(">");
			cin >> input;
		} while (input != 0 && input != 1);
	}
	if (input == 1) {
		cout << mat;
	}
};

void input_vector() {
	printf("Введите %d значений:\n", b.size());
	for (int i = 0;i < b.size();i++) {
		double value;
		cin >> value;
		b[i] = value;
	}
}

void random_vector() {
	cout << "Формула заполнения: b(i) = rand() % mod + d\n";
	int input = -1;
	while (input != 1) {
		printf("1. Заполнить вектор случайно\n");
		printf("2. Изменить модуль (mod = %d)\n", mod);
		printf("3. Изменить смещение (d = %lf)\n", d);
		printf(">");
		cin >> input;
		//printf("\n");
		switch (input) {
		case 1: {
			for (int i = 0;i < b.size();i++) {
					b[i] = rand() % mod + d;
			}
			printf("Вектор заполнен случайными числами\n");
			break;
		}
		case 2: {
			int value;
			do {
				printf("Введите mod:\n");
				printf(">");
				cin >> value;
			} while (value <= 0);
			mod = value;
			break;
		}
		case 3: {
			printf("Введите d:\n");
			printf(">");
			cin >> d;
			break;
		}
		}
	}
};

void show_vector() {
	int input = 1;
	if (b.size() > limit) {
		printf("Размер вектора значений  больше (%d)\n", limit);
		printf("Продолжить? (1 -> да, 0 -> нет)\n");
		do {
			printf(">");
			cin >> input;
		} while (input != 0 && input != 1);
	}
	if (input == 1) {
		cout << b << "\n";
	}
}

void solve_system() {
	System<double> sys(mat);
	vector<double> temp = b;
	int ans = sys.gaussian_method(temp);
	switch (ans) {
	case 2: {
		printf("Решений бесконечно много\n");
		break;
	}
	case 1: {
		cout << temp << "\n";

		matrix<double> b_copy(b.size(), 1);
		for (size_t i = 0;i < b.size();i++) {
			b_copy[i][0] = temp[i];
		}
		matrix<double> b2 = mat * b_copy;
		double error = 0;
		for (int i = 0;i < b.size();i++) {
			error += abs(b2[i][0] - b[i]);
		}
		cout.precision(20);
		cout << "Погрешность: " << error << "\n";
		break;

	}
	case 0: {
		printf("Решений нет\n");
		break;
	}
	}
};

void UpdateMenu() {
	int input = -1;
	while (input != Exit) {
		system("cls");
		printf("+----------------------------+\n");
		printf("| Программа для решения СЛАУ |\n");
		printf("+----------------------------+\n");
		printf("Выберите действие:\n");
		printf("\n");
		printf("[Работа с матрицей] (%d x %d)\n", mat.size(), mat[0].size());
		printf("1. Ввод размера матрицы\n");
		printf("2. Случайный ввод\n");
		printf("3. Ручной ввод (nxm) < (%d x %d)\n", limit, limit);
		printf("4. Вывести матрицу\n");
		printf("\n");
		printf("[Работа с вектором значений] (size = %d)\n", b.size());
		printf("5. Случайный вектор значений\n");
		printf("6. Ввести вектор значений\n");
		printf("7. Вывести вектор значений\n");
		printf("\n");
		printf("[Решение СЛАУ]\n");
		printf("8. Решить\n");
		printf("\n");
		printf("9. Выход\n");

		printf(">");
		cin >> input;
		switch (input) {
		case 1: {
			input_size();
			break;
		}
		case 2: {
			random_input();
			break;
		}
		case 3: {
			input_matrix();
			break;
		}
		case 4: {
			show_matrix();
			break;
		}
		case 5: {
			random_vector();
			break;
		}
		case 6: {
			input_vector();
			break;
		}
		case 7: {
			show_vector();
			break;
		}
		case 8: {
			solve_system();
			break;
		}
		case 9: {
			printf("Goodbye!\n");
			break;
		}
		default: {
			printf("Команда не найдена\n");
		}
		}
		system("pause");
	}
	return;
}

void Initialize() {
	system("chcp 1251");
	system("cls");
	srand(time(0));
	cout.setf(ios::fixed);
	size_t n = 3;
	mat.resize(n, n);
	b.resize(n);
	limit = 5;
	mod = RAND_MAX;
	d = 0;
};

int main()
{
	Initialize();
	UpdateMenu();
}