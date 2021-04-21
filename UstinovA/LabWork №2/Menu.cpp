#include <ctime>
#include "MatrixGauss.h"

#define current_zero 0 // Ноль текущего типа данных для СЛУ
typedef double current_type; // Текущий тип данных для СЛУ

#pragma warning (push)
#pragma warning (disable: 4244)

using std::cout;
using std::cin;
using std::endl;

void check(const GaussianMethod<current_type>& system, const Vector<current_type>& sol, const Vector<current_type>& rhs) {
	Vector<current_type> check = (Matrix<current_type>)system * sol;
	double eps = 10e-8;
	bool is_equal = true;
	for (size_t i = 0; i < check.GetSize(); i++)
		if (abs(check[i] - rhs[i]) > eps) is_equal = false;
	if (is_equal) cout << "Solution checked: it is right!" << endl;
	else cout << "Solution checked: it is wrong :/" << endl;
	cout << "The current value of error is " << eps << endl << endl;
}

void menu() {
	cout << "HELLO!" << endl;
	short code0, code1, code2, alright0 = 0, alright1 = 0, alright2 = 0;
	int column_size, row_size;

	for(;;) {
		cout << "Do you want to solve system of linear equations? " << endl << "1 - Yes!" << endl << "0 - No :/" << endl;
		cout << "Your choice: ";
		cin >> code0;
		cout << endl;

		do {
			switch (code0) {
			case 0:
				exit(0);
				break;
			default:
				cout << "Incorrect input, try again" << endl;
				cout << "Do you want to solve system of linear equations? " << endl << "1 - Yes!" << endl << "0 - No :/" << endl;
				cout << "Your choice: ";
				cin >> code0;
				cout << endl;
				break;
			case 1: {
				alright0 = 1;

				// Ввод количества уравнений
				do {
					cout << "Enter number of equations: ";
					cin >> column_size;
					cout << endl;
					if (column_size <= 0) cout << "Incorrect input, try again" << endl;
				} while (column_size <= 0);

				// Ввод количества неизвестных
				do {
					cout << "Enter number of variables: ";
					cin >> row_size;
					cout << endl;
					if (row_size <= 0) cout << "Incorrect input, try again" << endl;
				} while (row_size <= 0);

				cout << endl;

				Vector<current_type> sample(row_size), right_hand_vector(column_size); // Строка-образец для инициализации матрицы
				GaussianMethod<current_type> system(column_size, sample, current_zero); // Матрица коэффициентов
				Vector<current_type> solution(row_size); // Вектор решения

				cout << "Choose the way to enter the system of equations: " << endl << endl;

				cout << "How to fill left-hand matrix?" << endl
					<< "1 - By keyboard" << endl << "2 - Random" << endl << "0 - Exit program" << endl;
				cout << "Your choice: ";
				cin >> code1;
				cout << endl;

				do {
					switch (code1) {

					case 0:
						exit(0);
					case 1:
						alright1 = 1;

						cout << "Enter the matrix of coefficients in left-hand side: " << endl;
						cin >> system; // Ввод матрицы коэффициентов в левой части
						cout << endl;
						break;
					case 2:
						alright1 = 1;

						srand(time(NULL));
						for (size_t i = 0; i < column_size; i++)
							for (size_t j = 0; j < row_size; j++)
								system[i][j] = rand();
						break;
					default:
						cout << "Incorrect input, try again" << endl;
						cout << "How to fill left-hand matrix?" << endl
							<< "1 - By keyboard" << endl << "2 - Random" << endl << "0 - Exit program" << endl;
						cout << "Your choice: ";
						cin >> code1;
						cout << endl;
						break;
					}
				} while (alright1 == 0);

				cout << "How to fill right-hand vector?" << endl
					<< "1 - By keyboard" << endl << "2 - Random" << endl << "0 - Exit program" << endl;
				cout << "Your choice: ";
				cin >> code2;
				cout << endl;

				do {
					switch (code2) {

					case 0:
						exit(0);
					case 1:
						alright2 = 1;

						cout << "Enter the matrix of coefficients in right-hand vector: " << endl;
						cin >> right_hand_vector; // Ввод столбца свободных коэффициентов в правой части
						cout << endl;
						break;
					case 2:
						alright2 = 1;

						srand(time(NULL));
						for (size_t i = 0; i < column_size; i++)
							right_hand_vector[i] = rand();
						break;
					default:
						cout << "Incorrect input, try again" << endl;
						cout << "How to fill right-hand vector?" << endl
							<< "1 - By keyboard" << endl << "2 - Random" << endl << "0 - Exit program" << endl;
						cout << "Your choice: ";
						cin >> code2;
						cout << endl;
						break;
					}
				} while (alright2 == 0);

				cout << "System: " << endl;
				for (size_t i = 0; i < system.GetSize(); i++)
					cout << system[i] << "|" << right_hand_vector[i] << endl;
				solution = system.Solve(right_hand_vector);

				// Вывод решения в аккуратном виде (не через << класса Vector)
				cout << "Solution: " << endl;
				for (size_t i = 0; i < solution.GetSize(); i++) {
					cout << std::setprecision(5) << solution[i] << "  ";
				}
				cout << endl;

				check(system, solution, right_hand_vector);
				break;
				}
			}
		} while (alright0 == 0);
	}
}