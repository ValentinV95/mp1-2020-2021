#include <iostream>
#include <iomanip>
using namespace std;
unsigned int i = 0, I = 0;
class matrix
{
protected:
unsigned int d=0;
double** link;
public:
	matrix()
	{
		cout << "Введите размерность матрицы" << endl;
		cin >> d;
		double** contents = new double* [d];
		link =  contents;
	};
	matrix(unsigned int d1)
	{
		unsigned int d2 = d1;
		double** contents = new double* [d2];
		for (i = 0; i < d2; i++)
		{
			for (I = 0; I < d2; I++)
			{
				contents[i][I] = 0;
			}
		}
		link = contents;
	};
	double** getlink() { return(link); }
	unsigned int getd() { return(d); }
	void fill(double** link)
	{
		srand(time(NULL));
		double** contents = link;
		for (i = 0; i < d; i++)
		{
			contents[i] = new double[d];
		}
		cout << "Введите 1 для случайной матрицы, 0 для своей матрицы" << endl;
		cin >> I;
		if (I == 1)
		{
			cout << "Заполнение матрицы случайными элементами double" << endl;
			for (i = 0; i < d; i++)
			{
				for (I = 0; I < d; I++)
				{
					contents[i][I] = (pow(-1, rand())) * rand();
				}
			}

		}
		else
		{
			cout << "Введите double элементы матрицы построчно" << endl;
			for (i = 0; i < d; i++)
			{
				for (I = 0; I < d; I++)
				{
					double a;
					cin >> a;
					contents[i][I] = a;
				}
			}
		}
	}
	void print(double** link)
	{
		double** contents = link;
		for (i = 0; i < d; i++)
		{
			for (I = 0; I < d; I++)
			{
				cout << setw(d) << setprecision(d) << contents[i][I] << "     ";
			}
			cout << endl;
		}
	}
	friend matrix operator + (matrix& left, matrix& right)
	{
		if (left.getd() == right.getd()) 
		{
			matrix temp(left.getd());
			temp = left;
			unsigned int d = left.getd();
			double** contents_temp = left.getlink();
			double** contents_right = right.getlink();
			for (i = 0; i < d; i++)
			{
				for (I = 0; I < d; I++)
				{
					contents_temp[i][I] += contents_right[i][I];
				}
			}
			return(temp);
		}
		else
		{
			cout << "Ошибка: попытка сложить матрицы разных размерностей." << endl; return(0);
		}
	}
	friend matrix operator * (matrix& left, matrix& right)
	{
		if (left.getd() == right.getd())
		{
			matrix temp(left.getd());
			unsigned int d = left.getd();
			double** contents_temp = temp.getlink();
			double** contents_right = right.getlink();
			double** contents_left = left.getlink();
			for ( i = 0; i <d; i++)
			{
				for ( I = 0; I < d; I++) 
				{
					contents_temp[i][I] = 0;
					for (unsigned int k = 0; k < d; k++) 
					{
					contents_temp[i][I] += contents_left[i][k] * contents_right[k][I];
					}
				}
			}
			return(temp);
		}
		else { cout << "Ошибка: попытка перемножить матрицы разных размерностей." << endl; }
	}
};
int main()
{
		setlocale(LC_ALL, "Russian");
		matrix A; 
		A.fill(A.getlink()); 
		A.print(A.getlink());
		matrix B;
		B.fill(B.getlink());
		B.print(B.getlink());
		cout << "Результат сложения:" << endl;
		matrix C = A * B;
		C.print(C.getlink());
		cout << "Результат сложения:" << endl;
		C.print(C.getlink());
		cout << "Результат умножения матриц" << endl;
		matrix G = C * B;
}