#include "TemplateVector.h"
#include "MatrixGauss.h"

int main() {
	int column_size, row_size; // Количество уравнений и неизвестных соответственно
	cout << "Number of equations: ";
	cin >> column_size;
	cout << "Number of variables: ";
	cin >> row_size;

	Vector<double> sample(row_size), right_hand_vector(column_size); // Строка-образец для инициализации матрицы
	GaussianMethod<double> system(column_size, sample, 0);
	Vector<double> solution(row_size);

	cout << "Enter the matrix of coefficients in left-hand side: " << endl;
	cin >> system; // Ввод матрицы коэффициентов в левой части

	cout << "Enter the right-hand side vector: ";
	cin >> right_hand_vector; // Ввод столбца коэффициентов в правой части
	solution = system.Solve(right_hand_vector);
	cout << "Solution: " << solution;

}