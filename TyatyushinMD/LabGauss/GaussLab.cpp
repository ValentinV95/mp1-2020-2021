﻿#pragma once
#pragma warning(disable:6385)
#pragma warning(disable:4244)
#include <iostream>
using namespace std;


//#define CHECK
//#define SHOW

template<typename T>
T modul(T value)
{
	if (value < 0)
	{
		value = value * (-1);
	}
	return value;
}

template<typename T>
T NOD(T a, T b)
{
	a = modul(a);
	b = modul(b);
	while ((a != b) && (a != 0) && (b != 0))
	{
		if (a > b)
		{
			a = a - b;
		}
		else
		{
			b = b - a;
		}
	}

	T c = a;
	if (a != 0)
	{
		c = a;
	}
	else if (b != 0)
	{
		c = b;
	}
	return c;
}

template<typename T>
T NOK(T a, T b)
{
	T nok;

	nok = (a * b) / NOD(a, b);

	return nok;
}

template<typename T>
class Vector;

template<typename T>
class SqrMatrix;

template<typename T>
class Matrix;

template<typename T>
class SLAU;

template<typename T>
bool checkVector(Vector<T> vect, int i)
{
	bool key = 1;
	if (vect.GetI(i) == 0)
	{
		key = 0;
	}

	return key;
}

template<typename T>
bool checkMatrixNULL(Matrix<T> matrix)
{
	bool key = 1;
	for (int i = 0; i < matrix.GetN(); i++)
	{
		if (checkVector(matrix.GetMasI(i), i) == 0)
		{
			key = 0;
		}
	}

	return key;
}

template<typename T>
class Fraction
{
private:
	T numerator;
	T denominator;
public:

	Fraction()
	{
		this->numerator = 0;
		this->denominator = 0;
	}

	Fraction(T num)
	{
		this->numerator = num;
		this->denominator = 1;
	}

	Fraction(T num, T den)
	{
		this->numerator = num;
		this->denominator = den;
	}

	void SetNumerator(int numerator)
	{
		this->numerator = numerator;
	}

	void SetDenominator(int denominator)
	{
		this->denominator = denominator;
	}

	T GetNumerator()
	{
		return this->numerator;
	}

	T GetDenominator()
	{
		return this->denominator;
	}

	Fraction<T>& operator= (const Fraction& other)
	{
		this->numerator = other.numerator;
		this->denominator = other.denominator;

		return *this;
	}

	Fraction<T> operator+ (const Fraction& other)
	{
		Fraction<T> summ;

		summ.denominator = this->denominator * other.denominator;
		summ.numerator = (this->numerator * *other.denominator) + (other.numerator * this->denominator);

		return summ;
	}

	Fraction<T> operator- (const Fraction& other)
	{
		Fraction<T> dif;

		dif.denominator = this->denominator * other.denominator;
		dif.numerator = (this->numerator * other.denominator) - (other.numerator * this->denominator);

		return dif;
	}

	Fraction<T> operator* (T scal)
	{
		Fraction<T> mult;

		if (this->denominator > 0)
		{
			mult.numerator = scal * this->numerator;
			mult.denominator = this->denominator;
		}
		else
		{
			mult.numerator = this->numerator;
			mult.denominator = scal * this->denominator;
		}

		return mult;
	}

	Fraction<T> operator/ (T scal)
	{
		Fraction<T> mult;

		mult.numerator = this->numerator;
		mult.denominator = this->denominator * scal;

		return mult;
	}

	Fraction<T> operator* (Fraction& other)
	{
		Fraction<T> mult(this->numerator, this->denominator);
		mult.numerator = mult.numerator * other.numerator;
		mult.denominator = mult.denominator * other.denominator;
		return mult;
	}

	bool operator== (Fraction other)
	{
		other.Cut();
		Fraction<T> saver;
		saver = *this;

		saver.Cut();

		return saver.numerator == other.numerator && saver.denominator == other.denominator;
	}

	bool operator!= (Fraction other)
	{
		other.Cut();
		Fraction<T> saver;
		saver = *this;

		saver.Cut();

		return !(saver.numerator == other.numerator && saver.denominator == other.denominator);
	}

	bool operator> (Fraction other)
	{
		other.Cut();
		Fraction<T> saver;
		saver = *this;

		saver.Cut();

		return (saver.numerator * other.denominator) > (saver.denominator * other.numerator);
	}

	bool operator>= (Fraction other)
	{
		other.Cut();
		Fraction<T> saver;
		saver = *this;

		saver.Cut();

		return (saver.numerator * other.denominator) >= (saver.denominator * other.numerator);
	}

	bool operator<= (Fraction other)
	{
		other.Cut();
		Fraction<T> saver;
		saver = *this;

		saver.Cut();

		return (saver.numerator * other.denominator) <= (saver.denominator * other.numerator);
	}

	bool operator< (Fraction other)
	{
		other.Cut();
		Fraction<T> saver;
		saver = *this;

		saver.Cut();

		return (saver.numerator * other.denominator) < (saver.denominator * other.numerator);
	}

	void Cut()
	{
		T nod;
		nod = NOD(this->numerator, this->denominator);
		this->numerator = (numerator / nod);
		this->denominator = (denominator / nod);
	}

	~Fraction()
	{

	}

	friend Vector<Fraction<T>> FractionMult(Vector<T>& vect, const Fraction<T>& fract);
};

template<typename T>
Fraction<T> turnOver(Fraction<T> other)
{
	Fraction<T> turn;
	if ((other.GetNumerator() < 0) && (other.GetDenominator() > 0))
	{
		turn.SetNumerator(other.GetDenominator() * (-1));
		turn.SetDenominator(other.GetNumerator() * (-1));
	}
	else
	{
		turn.SetNumerator(other.GetDenominator());
		turn.SetDenominator(other.GetNumerator());
	}
	return turn;
}

template<typename T>
std::ostream& operator<< (std::ostream& out, Fraction<T>& d)
{
	if ((d.GetNumerator() != 0) && (d.GetDenominator() != 1) && (d.GetNumerator() != d.GetDenominator()))
	{
		out << d.GetNumerator() << "/" << d.GetDenominator();
	}

	else if (d.GetDenominator() == 1)
	{
		out << d.GetNumerator();
	}
	else if (d.GetNumerator() == d.GetDenominator())
	{
		out << "1";
	}
	else
	{
		out << "0";
	}
	return out;
}

template<typename T>
Fraction<T> modulFraction(Fraction<T> value)
{
	if ((value.GetNumerator() < 0) || (value.GetDenominator() < 0))
	{
		value = value * (-1);
	}
	return value;
}


template<typename T>
Vector<Fraction<T>> FractionMult(const Vector<T>& vect, const Fraction<T>& fract)
{
	int n = vect.GetN();
	Vector<Fraction<T>> mult(n);
	mult = vect;
	for (int i = 0; i < n; i++)
	{
		mult.SetI(mult.GetI(i) * fract.numerator, i);
		mult.SetI(mult.GetN(i) / fract.denominator, i);
	}

	return mult;
}

template<typename T>
Vector<Fraction<T>> to_FractionVector(Vector<T> vect)
{
	int n = vect.GetN();
	Vector<Fraction<T>> changer(n);
	for (int i = 0; i < n; i++)
	{
		Fraction<T> extractor = vect.GetI(i);
		changer.SetI(extractor, i);
	}

	return changer;
}

template<typename T>
class SqrMatrix;

template<typename T>
SqrMatrix<Fraction<T>> to_FractionSqrMatrix(SqrMatrix<T>& matrix)
{
	int n = matrix.GetN();
	SqrMatrix<Fraction<T>> changer(n);
	for (int i = 0; i < n; i++)
	{
		Vector<Fraction<T>> extractor = to_FractionVector(matrix.GetMasI(i));
		changer.SetMasI(extractor, i);
	}

	return changer;
}

template<typename T>
Matrix<Fraction<T>> to_FractionMatrix(Matrix<T>& matrix)
{
	int n = matrix.GetN();
	int m = matrix.GetM();
	Matrix<Fraction<T>> changer(n, m);
	for (int i = 0; i < n; i++)
	{
		Vector<Fraction<T>> extractor = to_FractionVector(matrix.GetMasI(i));
		changer.SetMasI(extractor, i);
	}

	return changer;
}

template<typename T>
Vector<Fraction<T>> CutVector(Vector<Fraction<T>> vect)
{
	for (int i = 0; i < vect.GetN(); i++)
	{
		Fraction<T> saver = vect.GetI(i);
		saver.Cut();
		vect.SetI(saver, i);
	}

	return vect;
}


template<typename T>
class Vector
{
protected:
	T* arr;
	int n = 0;
public:

	int GetN()
	{
		return n;
	}

	void SetI(T num, int i)
	{
		this->arr[i] = num;
	}

	Vector()
	{
		this->arr = NULL;
#ifdef CHECK
		std::cout << "Вызвался конструктор по умолчанию класса Vector" << " " << this << std::endl << std::endl;
#endif
	}

	Vector(int n)
	{
		this->n = n;
		this->arr = new T[n];

#ifdef CHECK
		std::cout << "Вызвался конструктор класса Vector" << " " << this << std::endl << std::endl;
#endif
	}

	void SetRand(int min, int max)
	{
		for (int i = 0; i < this->n; i++)
		{
			this->arr[i] = (rand() % (max - min + 1)) + min;
		}
	}


	void FillVector()
	{
		for (int i = 0; i < this->n; i++)
		{
			this->arr[i] = 0;
		}
	}

	void SetVector()
	{
		for (int i = 0; i < this->n; i++)
		{
			std::cin >> this->arr[i];
		}
	}


	void Show()
	{
		std::cout << "(";
		for (int i = 0; i < n; i++)
		{
			if (i != (n - 1))
			{
				std::cout << arr[i] << "\t";
			}
			else
			{
				std::cout << arr[i];
			}

		}
		std::cout << ")" << std::endl;
	}

	void ShowForMatrix()
	{
		std::cout << "(";
		for (int i = 0; i < n; i++)
		{
			if (i <= (n - 2))
			{
				std::cout << arr[i] << "\t";
			}
			else
			{
				std::cout << "|" << arr[i];
			}

		}
		std::cout << ")" << std::endl;
	}

	Vector(const Vector& other)
	{
		this->arr = new T[other.n];
		this->n = other.n;

		for (int i = 0; i < other.n; i++)
		{
			this->arr[i] = other.arr[i];
		}
#ifdef CHECK
		std::cout << "Вызвался конструктор копирования класса Vector" << " " << this << std::endl << std::endl;
#endif
	}

	Vector<T>& operator= (const Vector& other)
	{
		delete[] arr;
		this->arr = new T[other.n];
		this->n = other.n;

		for (int i = 0; i < other.n; i++)
		{
			this->arr[i] = other.arr[i];
		}

		return *this;
	}

	Vector<T> operator+ (const Vector& vec)
	{
		Vector<T> summ(vec.n);

		for (int i = 0; i < n; i++)
		{
			summ.arr[i] = this->arr[i] + vec.arr[i];
		}

		return summ;
	}

	Vector<T> operator- (const Vector& vec)
	{
		Vector<T> dif(vec.n);

		for (int i = 0; i < n; i++)
		{
			dif.arr[i] = this->arr[i] - vec.arr[i];
		}

		return dif;
	}

	Vector<T> operator* (T num)
	{
		Vector<T> scal(this->n);

		for (int i = 0; i < n; i++)
		{
			scal.arr[i] = num * this->arr[i];
		}

		return scal;
	}
	Vector<T> operator/ (T num)
	{
		Vector<T> scal(this->n);

		for (int i = 0; i < n; i++)
		{
			scal.arr[i] = this->arr[i] / num;
		}

		return scal;
	}

	void AddElement(T num)
	{
		Vector<T> saver(this->n);

		for (int i = 0; i < this->n; i++)
		{
			saver.arr[i] = this->arr[i];
		}

		delete[] arr;
		this->n += 1;
		this->arr = new T[this->n];

		for (int i = 0; i < (this->n - 1); i++)
		{
			this->arr[i] = saver.arr[i];
		}

		this->arr[this->n - 1] = num;

	}

	T GetI(int i)
	{
		return this->arr[i];
	}

	~Vector()
	{
		delete[] this->arr;
#ifdef CHECK
		std::cout << "Вызвался деструктор класса Vector" << " " << this << std::endl << std::endl;;
#endif
	}
};

template<typename T>
T GetRK(Vector<T> vec, int i)
{
	return vec.GetI(i);
}

template<typename T>
class SqrMatrix : public Vector<Vector<T>>
{
private:
	
public:

	int GetN()
	{
		return this->n;
	}

	Vector<T> GetMasI(int i)
	{
		return this->arr[i];
	}

	void SetMasI( Vector<T>& vect, int i)
	{
		this->arr[i] = vect;
	}

	void SetSqrMatrix()
	{
		for (int i = 0; i < this->n; i++)
		{
			std::cout << "Введите строчку под номером "<< i + 1 <<" основной матрицы:  " << std::endl;
			this->arr[i].SetVector();
			std::cout << std::endl;
		}
	}

	void SetSqrMatrixRand(int min, int max)
	{
		for (int i = 0; i < this->n; i++)
		{
			this->arr[i].SetRand(min, max);
			
		}
	}


	SqrMatrix()
	{
		
#ifdef CHECK
		std::cout << "Вызвался конструктор по умолчанию класса SqrMatrix" << " " << this << std::endl << std::endl;
#endif
	}

	SqrMatrix(int n) : Vector<Vector<T>>(n)
	{
		
#ifdef CHECK
		std::cout << "Вызвался конструктор класса SqrMatrix" << " " << this << std::endl << std::endl;
#endif
	}

	SqrMatrix(const SqrMatrix& other)
	{
		this->arr = new Vector<T>[other.n];
		this->n = other.n;

		for (int i = 0; i < other.n; i++)
		{
			this->arr[i] = other.arr[i];
		}
#ifdef CHECK
		std::cout << "Вызвался конструктор копирования класса SqrMatrix" << " " << this << endl << endl;
#endif
	}

	void FillSqrMatrix()
	{
		for (int i = 0; i < this->n; i++)
		{
			Vector<T> a(this->n);
			a.FillVector();
			this->arr[i] = a;
		}
	}

	SqrMatrix<T>& operator= (const SqrMatrix& otherMatrix)
	{

		delete[] this->arr;
		this->arr = new Vector<T>[otherMatrix.n];

		this->n = otherMatrix.n;
		this->FillSqrMatrix();

		for (int i = 0; i < this->n; i++)
		{
			this->arr[i] = otherMatrix.arr[i];
		}
		return *this;
	}

	void ShowBaseMatrix()
	{
		for (int i = 0; i < this->n; i++)
		{
			this->arr[i].Show();
		}
	}

	void AddVector(Vector<T>& other)
	{
		for (int i = 0; i < other.GetN(); i++)
		{
			this->arr[i].AddElement(other.GetI(i));
		}
	}

	int LeadingRow(int start, int k)
	{
		T maxElement = 0;
		int row = 0;

		for (int i = start; i < this->n; i++)
		{
			if (modul(GetRK(this->arr[i], k)) >= maxElement)
			{
				maxElement = modul(GetRK(this->arr[i], k));
				row = i;
			}
		}

		return row;
	}

	T Leading(int start, int k)
	{
		T maxElement = 0;

		for (int i = start; i < this->n; i++)
		{
			if (modul(GetRK(this->arr[i], k)) >= modul(maxElement))
			{
				maxElement = GetRK(this->arr[i], k);
			}
		}

		return maxElement;
	}

	void Swap(int i, int k)
	{
		Vector<T> saver(this->n);

		saver = this->arr[i];

		this->arr[i] = this->arr[k];

		this->arr[k] = saver;
	}

	~SqrMatrix()
	{
		
#ifdef CHECK
		std::cout << "Вызвался деструктор класса SqrMatrix" << " " << this << endl << endl;
#endif
	}
};

template<typename T>
class Matrix : public Vector<Vector<T>>
{
private:
	int m;
public:

	int GetN()
	{
		return this->n;
	}

	int GetM()
	{
		return this->m;
	}

	Vector<T> GetMasI(int i)
	{
		return this->arr[i];
	}

	void SetMasI(const Vector<T>& vect, int i)
	{
		this->arr[i] = vect;
	}

	Matrix()
	{
		this->m = 0;
#ifdef CHECK
		std::cout << "Вызвался конструктор по умолчанию класса SqrMatrix" << " " << this << std::endl << std::endl;
#endif
	}

	Matrix(int n, int m)
	{
		this->arr = new Vector<T>[m];
		this->n = n;
		this->m = m;
#ifdef CHECK
		std::cout << "Вызвался конструктор класса SqrMatrix" << " " << this << std::endl << std::endl;
#endif
	}

	Matrix(const Matrix& other)
	{
		this->arr = new Vector<T>[other.m];
		this->n = other.n;
		this->m = other.m;

		for (int i = 0; i < other.n; i++)
		{
			this->arr[i] = other.arr[i];
		}
#ifdef CHECK
		std::cout << "Вызвался конструктор копирования класса SqrMatrix" << " " << this << std::endl << std::endl;
#endif
	}

	void FillMatrix()
	{
		for (int i = 0; i < this->n; i++)
		{
			Vector<T> a(m);
			a.FillVector();
			this->arr[i] = a;
		}
	}

	Matrix<T>& operator= (const Matrix& otherMatrix)
	{

		delete[] this->arr;
		this->arr = new Vector<T>[otherMatrix.m];

		this->n = otherMatrix.n;
		this->m = otherMatrix.m;
		this->FillMatrix();

		for (int i = 0; i < this->n; i++)
		{
			this->arr[i] = otherMatrix.arr[i];
		}
		return *this;
	}

	void ShowMatrix()
	{
		for (int i = 0; i < this->n; i++)
		{
			this->arr[i].ShowForMatrix();
		}
	}

	void SetMatrix()
	{
		for (int i = 0; i < this->n; i++)
		{
			std::cout << "Введите строчку матрицы под номером " << i + 1 << ": " << std::endl;
			this->arr[i].SetVector();
			std::cout << std::endl;
		}
	}

	void AddVector(const Vector<T>& other)
	{
		this->m = m + 1;
		for (int i = 0; i < other.n; i++)
		{
			this->arr[i].AddElement(other.arr[i]);
		}
	}

	int LeadingRow(int start, int k)
	{
		T maxElement = 0;
		int row = 0;

		for (int i = start; i < this->n; i++)
		{
			T x = GetRK(this->arr[i], k);
			if (modul(x) >= maxElement)
			{
				maxElement = modul(GetRK(this->arr[i], k));
				row = i;
			}
		}

		return row;
	}

	int LeadingRowFraction(int start, int k)
	{
		T maxElement = 0;
		int row = 0;

		for (int i = start; i < this->n; i++)
		{
			T x = GetRK(this->arr[i], k);
			if (modulFraction(x) >= maxElement)
			{
				maxElement = modulFraction(GetRK(this->arr[i], k));
				row = i;
			}
		}

		return row;
	}

	T Leading(int start, int k)
	{
		T maxElement = 0;

		for (int i = start; i < this->n; i++)
		{
			if (modul(GetRK(this->arr[i], k)) >= modul(maxElement))
			{
				maxElement = GetRK(this->arr[i], k);
			}
		}

		return maxElement;
	}

	T LeadingFraction(int start, int k)
	{
		T maxElement = 0;

		for (int i = start; i < this->n; i++)
		{
			if (modulFraction(GetRK(this->arr[i], k)) >= modulFraction(maxElement))
			{
				maxElement = GetRK(this->arr[i], k);
			}
		}

		return maxElement;
	}

	void Swap(int i, int k)
	{
		Vector<T> saver(this->n);

		saver = this->arr[i];

		this->arr[i] = this->arr[k];

		this->arr[k] = saver;
	}

	~Matrix()
	{
#ifdef CHECK
		std::cout << "Вызвался деструктор класса SqrMatrix" << " " << this << std::endl << std::endl;
#endif
	}
};

template<typename T>
class SLAU : public SqrMatrix<T>
{
private:
	
	Matrix<T> BaseMatrix;
	

public:

	SLAU()
	{
#ifdef CHECK
		std::cout << "Вызвался конструктор по умолчанию класса SLAU" << " " << this << std::endl << std::endl;
#endif
	}

	SLAU(int n, int k) : SqrMatrix<T>(n)
	{
		Matrix<T> GiverMatrix(n, n + 1);
		
		this->FillSqrMatrix();

		Vector<T> vect(n);
		if (k == 0)
		{
			int min = 1, max = 0;
			while (min > max)
			{
				std::cout << "Введите нижнюю границу рандомной генерации: " << std::endl;
				std::cin >> min;
				std::cout << "Введите верхнюю границу рандомной генерации: " << std::endl;
				std::cin >> max;
			}
			

			vect.SetRand(min, max);
			this->SetSqrMatrixRand(min, max);
			this->AddVector(vect);

		}
		else if (k == 1)
		{
			this->SetSqrMatrix();

			std::cout << "Введите столбец свободных членов системы: " << std::endl;
			vect.SetVector();
			std::cout << std::endl;
			this->AddVector(vect);
		}
		
		

		for (int i = 0; i < this->n; i++)
		{
			GiverMatrix.SetMasI(this->GetMasI(i), i);
		}

		//GiverMatrix.SetMatrix();

		BaseMatrix = GiverMatrix;
#ifdef CHECK
		cout << "Вызвался конструктор класса SLAU" << " " << this << std::endl << std::endl;
#endif
	}

	void ShowSLAU()
	{
		this->BaseMatrix.ShowMatrix();
	}

	Vector<T> Gauss()
	{
		Matrix<T> saver(this->n, this->n + 1);

		saver = BaseMatrix;

#ifdef SHOW
		std::cout << "---------------------------------------------------------------" << std::endl;
		saver.ShowMatrix();
		std::cout << "---------------------------------------------------------------" << std::endl;
#endif
		Vector<T> x(this->n);
		bool vectCheck = 1;

		int row0 = 0;
		for (int i = 0; (i < this->n) && (vectCheck != 0); i++)
		{
			row0 = saver.LeadingRow(i, i);
			T max = saver.Leading(i, i);
			saver.Swap(row0, i);


#ifdef SHOW
			std::cout << "---------------------------------------------------------------" << std::endl;
			saver.ShowMatrix();
			std::cout << "---------------------------------------------------------------" << std::endl;
#endif


			vectCheck = checkVector(saver.GetMasI(i), i);

			switch (vectCheck)
			{
			case 0:
				std::cout << "Система не совместна или имеет не одно решение!" << std::endl;
				x = x * 0;

				break;
			case 1:
				for (int j = (i + 1); j < this->n; j++)
				{
					T scal = (GetRK(saver.GetMasI(j), i));

					saver.SetMasI(saver.GetMasI(j) - ((saver.GetMasI(i) * scal) / max), j);

#ifdef SHOW
					std::cout << "---------------------------------------------------------------" << std::endl;
					saver.ShowMatrix();
					std::cout << "---------------------------------------------------------------" << std::endl;
#endif
				}
#ifdef SHOW
				std::cout << "---------------------------------------------------------------" << std::endl;
				saver.ShowMatrix();
				std::cout << "---------------------------------------------------------------" << std::endl;
#endif
			}




		}

		int KeyNULL = 0;

		KeyNULL = checkMatrixNULL(saver);

		switch (KeyNULL)
		{
		case 1:
			for (int row = this->n - 1; row >= 0; row--)
			{
				for (int i = 1; i <= row; i++)
				{
					saver.SetMasI(saver.GetMasI(row - i) - ((saver.GetMasI(row) * GetRK(saver.GetMasI(row - i), row)) / (GetRK(saver.GetMasI(row), row))), row - i);

#ifdef SHOW
					std::cout << "---------------------------------------------------------------" << std::endl;
					saver.ShowMatrix();
					std::cout << "---------------------------------------------------------------" << std::endl;
#endif
				}
				saver.SetMasI((saver.GetMasI(row) / (GetRK(saver.GetMasI(row), row))), row);

#ifdef SHOW
				std::cout << "---------------------------------------------------------------" << std::endl;
				saver.ShowMatrix();
				std::cout << "---------------------------------------------------------------" << std::endl;
#endif
			}


			for (int row = 0; row < this->n; row++)
			{
				x.SetI(GetRK(saver.GetMasI(row), this->n), row);
			}

			break;

		case 0:
			if (vectCheck)
			{
				std::cout << "Система не совместна или имеет не одно решение!" << std::endl;
				x = x * 0;
			}
			break;
		}

		return x;

	}

	Vector<Fraction<T>> Gauss1()
	{
		Matrix<Fraction<T>> saver(this->n, this->n + 1);

		saver = to_FractionMatrix(BaseMatrix);

#ifdef SHOW
		std::cout << "---------------------------------------------------------------" << std::endl;
		saver.ShowMatrix();
		std::cout << "---------------------------------------------------------------" << std::endl;
#endif
		Vector<Fraction<T>> x(this->n);
		bool vectCheck = 1;

		int row0 = 0;
		for (int i = 0; (i < this->n) && (vectCheck != 0); i++)
		{
			row0 = saver.LeadingRowFraction(i, i);
			Fraction<T> max = saver.LeadingFraction(i, i);
			saver.Swap(row0, i);


#ifdef SHOW
			std::cout << "---------------------------------------------------------------" << std::endl;
			saver.ShowMatrix();
			std::cout << "---------------------------------------------------------------" << std::endl;
#endif


			vectCheck = checkVector(saver.GetMasI(i), i);

			switch (vectCheck)
			{
			case 0:
				std::cout << "Система не совместна или имеет не одно решение!" << std::endl;
				x = x * 0;

				break;
			case 1:
				for (int j = (i + 1); j < this->n; j++)
				{
					Fraction<T> scal = (GetRK(saver.GetMasI(j), i));

					saver.SetMasI(saver.GetMasI(j) - ((saver.GetMasI(i) * scal) * (turnOver(max))), j);

#ifdef SHOW
					std::cout << "---------------------------------------------------------------" << std::endl;
					saver.ShowMatrix();
					std::cout << "---------------------------------------------------------------" << std::endl;
#endif

					saver.SetMasI(CutVector(saver.GetMasI(j)), j);
#ifdef SHOW
					std::cout << "---------------------------------------------------------------" << std::endl;
					saver.ShowMatrix();
					std::cout << "---------------------------------------------------------------" << std::endl;
#endif
				}
#ifdef SHOW
				std::cout << "---------------------------------------------------------------" << std::endl;
				saver.ShowMatrix();
				std::cout << "---------------------------------------------------------------" << std::endl;
#endif
			}




		}

		int KeyNULL = 0;

		KeyNULL = checkMatrixNULL(saver);

		switch (KeyNULL)
		{
		case 1:
			for (int row = this->n - 1; row >= 0; row--)
			{
				for (int i = 1; i <= row; i++)
				{
					saver.SetMasI((saver.GetMasI(row - i) - ((saver.GetMasI(row) * GetRK(saver.GetMasI(row - i), row)) * turnOver(GetRK(saver.GetMasI(row), row)))), row - i);
					saver.SetMasI(CutVector(saver.GetMasI(row - i)), row - i);

#ifdef SHOW
					std::cout << "---------------------------------------------------------------" << std::endl;
					saver.ShowMatrix();
					std::cout << "---------------------------------------------------------------" << std::endl;
#endif
				}
				saver.SetMasI(saver.GetMasI(row) * (turnOver(GetRK(saver.GetMasI(row), row))), row);
				saver.SetMasI(CutVector(saver.GetMasI(row)), row);

#ifdef SHOW
				std::cout << "---------------------------------------------------------------" << std::endl;
				saver.ShowMatrix();
				std::cout << "---------------------------------------------------------------" << std::endl;
#endif
			}


			for (int row = 0; row < this->n; row++)
			{
				x.SetI(GetRK(saver.GetMasI(row), this->n), row);
			}

			break;

		case 0:
			if (vectCheck)
			{
				std::cout << "Система не совместна или имеет не одно решение!" << std::endl;
				x = x * 0;
			}
			break;
		}

		return x;

	}

	~SLAU()
	{
#ifdef CHECK
		std::cout << "Вызвался деструктор класса SLAU" << " " << this << endl << endl;
#endif
	}
};


int main()
{
	setlocale(LC_ALL, "ru");
	srand(time(NULL));
	int n = 0;
	int key = 0;

	std::cout << "Введите количество строк СЛАУ: " << std::endl;
	std::cin >> n;
	

	std::cout << "Для вызова метода Гаусса с рандомной генерацией элементов матрицы и ответом в виде десятичных дробей введите 1" << std::endl;
	std::cout << "Для вызова метода Гаусса с рандомной генерацией элементов матрицы и ответом в виде обыкновенных дробей введите 2" << std::endl;
	std::cout << "Для вызова метода Гаусса с самостоятельным вводом элементов матрицы и ответом в виде десятичных дробей введите 3" << std::endl;
	std::cout << "Для вызова метода Гаусса с самостоятельным вводом элементов матрицы и ответом в виде обыкновенных дробей введите 4" << std::endl;
	while ((key != 1) && (key != 2) && (key != 3) && (key != 4))
	{
		std::cin >> key;
	}

	int set = 0;
	if (key < 3)
	{
		set = 0;
	}
	else
	{
		set = 1;
	}

	switch (key % 2)
	{
	case 1:
	{
		
		SLAU<double> A(n, set);
		std::cout << "Исходная матрица: " << std::endl;
		A.ShowSLAU();
		Vector<double> x_0(n);
		x_0 = A.Gauss();
		std::cout << "------------------------------------------------------" << std::endl;
		std::cout << "Решение: ";
		x_0.Show();
		break;
	}

	case 0:
	{
		
		SLAU<double> B(n, set);
		std::cout << "Исходная матрица: " << std::endl;
		B.ShowSLAU();
		Vector<Fraction<double>> x(n);
		x = B.Gauss1();
		std::cout << "-------------------------------------------------------" << std::endl;
		std::cout << "Решение: ";
		x.Show();
		break;
	}

	}
	system("pause");

	return 0;
}