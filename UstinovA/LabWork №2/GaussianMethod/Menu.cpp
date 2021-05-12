#include <ctime>
#include "MatrixGauss.h"


#define current_zero 0 // Ноль текущего типа данных для СЛУ
typedef double current_type; // Текущий тип данных для СЛУ

#pragma warning (push)
#pragma warning (disable: 4244)

using namespace std;

void menu() {
	cout << "HELLO!" << endl;
	short code0, code1, code2; // Переменные для хранения вариантов выбора при вводе
	int column_size, row_size; // Кол-во уравнений и переменных в системе

	for(;;) {
		short flag0 = 0, flag1 = 0, flag2 = 0; // Флаги для обработки некорректного ввода

		// Будет ли юзер решать систему или выйдет из программы? 1 - да, 0 - нет (закрытие программы)
		cout << "Do you want to solve system of linear equations? " << endl << "1 - Yes!" << endl << "0 - No :/" << endl;
		cout << "Your choice: ";
		cin >> code0;
		cout << endl;

		// Обработка выбора о решении СЛУ
		do {
			switch (code0) {
			case 0:
				exit(0);
			default:
				// Введено что-то кроме 0 либо 1
				cout << "Incorrect input, try again" << endl;
				cout << "Do you want to solve system of linear equations? " << endl << "1 - Yes!" << endl << "0 - No :/" << endl;
				cout << "Your choice: ";
				cin >> code0;
				cout << endl;
				break;
			case 1: {
				// Юзер будет решать систему
				flag0 = 1;

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

				GaussianMethod<current_type> system(column_size, Vector<current_type>(row_size), current_zero); // Расширенная матрица коэффициентов
				Vector<current_type> right_hand_vector(column_size); // Вектор-столбец правой части
				Vector<current_type> solution(row_size); // Вектор решения
				Vector<current_type> zero_vector(row_size); // Нулевой вектор (индикатор отсутствия единственного решения)

				cout << "Choose the way to enter the system of equations: " << endl << endl;
				
				// Как заполнить матрицу? 1 - с клавиатуры, 2 - случайно; 0 - закрыть программу
				cout << "How to fill left-hand matrix?" << endl
					<< "1 - By keyboard" << endl << "2 - Random" << endl << "0 - Exit program" << endl;
				cout << "Your choice: ";
				cin >> code1;
				cout << endl;

				// Обработка выбора о заполнении матрицы
				do {
					switch (code1) {

					case 0:
						exit(0);
					case 1:
						flag1 = 1;

						cout << "Enter the matrix of coefficients in left-hand side: " << endl;
						cin >> system; // Ввод матрицы коэффициентов в левой части
						cout << endl;
						break;
					case 2:
						flag1 = 1;

						srand(time(NULL));
						for (size_t i = 0; i < column_size; i++)
							for (size_t j = 0; j < row_size; j++)
								system[i][j] = rand();
						break;
					default:
						// Введено что-то кроме 0, 1 либо 2
						cout << "Incorrect input, try again" << endl;
						cout << "How to fill left-hand matrix?" << endl
							<< "1 - By keyboard" << endl << "2 - Random" << endl << "0 - Exit program" << endl;
						cout << "Your choice: ";
						cin >> code1;
						cout << endl;
						break;
					}
				} while (flag1 == 0);

				// Как заполнить вектор свободных коэффициентов? 1 - с клавиатуры, 2 - случайно; 0 - закрыть программу
				cout << "How to fill right-hand vector?" << endl
					<< "1 - By keyboard" << endl << "2 - Random" << endl << "0 - Exit program" << endl;
				cout << "Your choice: ";
				cin >> code2;
				cout << endl;

				// Обработка выбора о заполнении правого вектора
				do {
					switch (code2) {

					case 0:
						exit(0);
					case 1:
						flag2 = 1;

						cout << "Enter the coefficients of right-hand vector: " << endl;
						cin >> right_hand_vector; // Ввод столбца свободных коэффициентов в правой части
						cout << endl;
						break;
					case 2:
						flag2 = 1;

						srand(time(NULL));
						for (size_t i = 0; i < column_size; i++)
							right_hand_vector[i] = rand();
						break;
					default:
						// Введено что-то кроме 0, 1 либо 2
						cout << "Incorrect input, try again" << endl;
						cout << "How to fill right-hand vector?" << endl
							<< "1 - By keyboard" << endl << "2 - Random" << endl << "0 - Exit program" << endl;
						cout << "Your choice: ";
						cin >> code2;
						cout << endl;
						break;
					}
				} while (flag2 == 0);

				// Вывод системы (расширенная матрица) и её решение
				cout << "System: " << endl;
				for (size_t i = 0; i < system.GetSize(); i++)
					cout << system[i] << "|" << right_hand_vector[i] << endl;

				solution = system.Solve(right_hand_vector);
				if (system.GetHasUniqueSolution()) { // Если решение единственно, выводим его

					// Вывод решения в аккуратном виде (не через оператор << класса Vector, там возникли неудобства)
					cout << "Solution: " << endl;
					for (size_t i = 0; i < solution.GetSize(); i++) {
						cout << std::setprecision(5) << solution[i] << "  ";
					}
					cout << endl << endl;
				}
				break;
				}
			}
		} while (flag0 == 0);
	}
}