#include <iostream>
#include <cmath>
using namespace std;

template <typename T>
class Vector
{
private:
	int size;
	T* data;
public:
	Vector () // по умолчанию создаем нулевой вектор
	{	
		data = nullptr;
		size = 0;
	}

	Vector (int count)
	{
		size = count;
		data = new T[size];
	}

	Vector (const Vector& v)
	{
		size = v.size;
		data = new T[v.size];
		for (int i = 0; i < size; i++)
			data[i] = v.data[i];
	}

	~Vector ()
	{
		delete[] data;
		data = nullptr;
		size = 0;
	}

	T& operator [] (const int i) 
	{
		return data[i];
	}

	T operator * (const Vector& v) // переопределяем оператор * как скалярное произведение векторов
	{
		T res = (T)0; 
		if (this->size != v.size || this->data == nullptr || v.data == nullptr) // в случае нулевых указателей или разных размеров векторов завершаем работу программы с ошибкой
		{
			exit(1);
		}
		else
		{
			for (int i = 0; i < v.size; i++)
				res += this->data[i] * v.data[i];
			return res;
		}
	}

	Vector operator * (const int c) // переопределяем оператор * как умножение вектора на целочисленную константу
	{
		Vector v (*this);
		if (v.data == nullptr)
			exit(1);
		else
		{
			for (int i = 0; i < v.size; i++)
				v[i] *= c;
			return v;
		}
	}

	
	Vector operator + (const Vector& v)
	{
		if (this->size != v.size || this->data == nullptr || v.data == nullptr) // в случае нулевых указателей или разных размеров векторов завершаем работу программы с ошибкой
			exit(1);
		else
		{
			for (int i = 0; i < v.size; i++)
				this->data[i] += v.data[i];
			return *this;
		}
	}

	Vector operator - (const Vector& v)
	{
		if (this->size != v.size || this->data == nullptr || v.data == nullptr) // в случае нулевых указателей или разных размеров векторов завершаем работу программы с ошибкой
		exit(1);
		else
		{
			for (int i = 0; i < v.size; i++)
				this->data[i] -= v.data[i];
			return *this;
		}
	}

	Vector operator = (const Vector& v)
	{
		size = v.size;
		data = v.data;
		return *this;
	}

	// вывод вектора делаем в строчку для удобства читаемости ответа
	friend ostream& operator << (ostream& out, const Vector& v) // переопределяем оператор вывода << для объекта класса векторов
	{
		for (int i = 0; i < v.size; i++)
			out << v.data[i] << ' ';
		cout << endl;
		return out;
	}

	friend istream& operator >> (istream& in, Vector& v) // переопределяем оператор ввода >> для объекта класса векторов
	{
		for (int i = 0; i < v.size; i++)
			in >> v.data[i];
		return in;
	}

	int get_size () const
	{
		return size;
	}

	void set_size (const int count)
	{
		if (size == count) // здесь бессмысленно перезаписывать размер 
			return;
		if (count == 0) // в случае задания вектора нулевого размера необходимо обнулить указатель data, если он еще не обнулен, для предотвращения сбоев в программе
		{
			if (data != nullptr)
			{
				delete[] data;
				data = nullptr;
				size = 0;
			}
			return;
		}
		if (count < size) // если необходимо уменьшить размер вектора, сохраняем значения элементов индекса меньше count
		{
			T* obj;
			obj = new T[count];
			for (int i = 0; i < count; i++)
				if (data != nullptr)
				obj[i] = data[i];
			if (data != nullptr) // перезаписываем data и size для нового вектора
			delete[] data;
			size = count;
			data = obj;
			return;
		}

		if (count > size) // если необходимо увеличить размер вектора, увеличиваем его размер до count и заполняем новые "ячейки" нулями
		{
			T* obj;
			obj = new T[count];
			for (int i = 0; i < size; i++)
				if (data != nullptr)
					obj[i] = data[i];
			for (int i = size; i < count; i++)
				obj[i] = 0;
			if (data != nullptr) // перезаписываем data и size для нового вектора
				delete[] data;
			size = count;
			data = obj;
			return;
		}
	}
};

template <template <typename> typename Vector, typename T> // объявляем шаблонный класс матриц как вектор векторов
class Matrix
{
	private:
	Vector < Vector <T> > data;
	int size; // size - длина вектора (длина строки или столбца квадратной матрицы)
	public:
	Matrix() 
	{
		size = 0;
	}

	Matrix(int count) : size(count), data(count)
	{
		for (int i = 0; i < size; i++)
			data[i].set_size(size);
	}

	Matrix(const Matrix& v)
	{
		if (size != v.size) // в случае неравенства размеров копируемых матриц задаем размер data равным размеру копируемой матрицы с помощью set_size
		{
			data.set_size(v.size);
			for (int i = 0; i < size; i++)
				data[i].set_size(v.size);
			size = v.size;
		}
		for (int i = 0; i < size; i++) // поэлементно копируем матрицу 
			for (int j = 0; j < size; j++)
				data[i][j] = v.data[i][j];
	}

	~Matrix()
	{

	}

	friend ostream& operator << (ostream& out, Matrix& a) // переопределяем оператор вывода << для объекта класса матриц
	{
		for (int i = 0; i < a.size; i++)
		{
			for (int j = 0; j < a.size; j++)
				out << a.data[i][j] << ' ';
			cout << endl;
		}
		return out;
	}

	friend istream& operator >> (istream& in, Matrix& a) // переопределяем оператор ввода >> для объекта класса матриц
	{
		for (int i = 0; i < a.size; i++)
			for (int j = 0; j < a.size; j++)
				in >> a.data[i][j];
		return in;
	}

	void Random() // функция для случайного задания матриц
	{
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				data[i][j] = rand() % 100;
	}

	void Gauss_method(Vector<T> b)
	{
		T c;
		T d;
		for (int j = 0; j < size; j++)
		{
			for (int i = j; i < size; i++)
				if ((abs(data[i][j]) - abs(data[j][j])) > 1e-6) // в цикле перемещаем строки матрицы для перемещения максимального элемента вверх как ведущего
				{
					for (int k = j; k < size; k++)
					{
						c = data[j][k];
						data[j][k] = data[i][k];
						data[i][k] = c;
					} 
					T g = b[j]; // те же преобразования осуществляем с вектором значений
					b[j] = b[i];
					b[i] = g;
				}

			if (data[j][j] != 0)
			{
				T tmp = data[j][j];
				for (int i = 0; i < size; i++)
					data[j][i] = data[j][i] / (tmp); // делим каждый элемент строки на значение ведущего элемента, чтобы он равнялся единице
				b[j] = b[j] / (tmp); // аналогично с вектором значений
				for (int i = 0; i < size; i++)
				{ //зануляем все элементы столбца, кроме ведущего
					if (i != j && data[i][j] != 0)
					{
						T tmp2 = data[i][j];
						for (int k = j; k < size; k++)
						{
							d = data[j][k];
							data[j][k] = data[j][k] * tmp2;
							if (abs(abs(data[i][k]) - abs(data[j][k])) > 1e-6)  
								data[i][k] -=data[j][k];
							else  // в случае, если элементы различаются менее, чем на заданную малую величину, считаем их равными
								data[i][k] = 0; 
							data[j][k] = d;
						}
						d = b[j]; // те же действия осуществляем с вектором значений
						b[j] = b[j] * tmp2;
						if (abs(abs(b[i]) - abs(b[j])) > 1e-6)
							b[i] -= b[j];
						else
							b[i] = 0;
						b[j] = d;
					}
				}
			} 
		}
		int p = 0;
		int flag = 0; // флаг отвечает за наличие нулевых строк в матрице с нулевым элементом вектора значений того же индекса, что номер строки
		for (int i = 0; i < size; i++)
			if (data[i][i] == 0)
			{
				for (int j = 0; j < size; j++)
					if (data[i][j] == 0)
						p++;
				if (p == size && b[i] != 0)
				{
					cout << " Система не имеет решений. " << endl;
					exit(0);
				}
				if (p == size && b[i] == 0)
					flag = 1;
			}
		if (flag == 1) // если не было выхода из программы с ошибкой в случае равенства нулевой строки ненулевому числу и флаг = 1, делаем вывод о линейной зависимости системы столбцов (строк) матрицы
		{
			cout << "Система имеет бесконечное множество решений. " << endl;
			exit(0);
		}
		cout << "Искомый вектор: " << endl << b;
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");
	cout << " Введите размер строки квадратной матрицы:   ";
	int size; //
	cin >> size;
	if (size <= 0)
	{
		cout << "Длина строки не может быть неположительным числом! Повторите попытку. " << endl;
		exit(0);
	}
	Matrix <Vector, double> A(size);
	Vector <double> b(size);
	cout << "1. Сгенерировать рандомную матрицу размером " << size << "*" << size << endl;
	cout << "2. Ввести матрицу самостоятельно. " << endl;
	cout << "Ваш выбор:   ";
	int q;
	cin >> q;
	switch (q)
	{
	case 1: 
		A.Random();
		cout << "Сгенерированная матрица :" << endl << A << endl;
		break;
	case 2: 	
		cin >> A;
		break;
	}
	cout << "Введите вектор: " << endl;
	cin >> b;
	A.Gauss_method(b);
	return 0;
}