#include <iostream>
#include <math.h>
#include <ctime>


using namespace std; // так как другие пространства имен не используются


template <typename T>
void swap1(T& vec1, T& vec2)
{
	T tmp = vec1;
	vec1 = vec2;
	vec2 = tmp;
}

template <class T>
class Vector
{
protected:
	T* vect;
	long size;
public:

	//конструкторы, деструктор
	Vector() : Vector(0) {}

	Vector(long size)
	{
		this->size = size;
		this->vect = new T[size];
	}

	Vector(long size, T val)
	{
		this->size = size;
		vect = new T[size];
		for (long i = 0; i < size; i++)
			vect[i] = val;
	}


	Vector(const Vector& other_vect)//конструктор копирования
	{
		this->size = other_vect.size;
		this->vect = new T[size];
		for (long i = 0; i < size; i++)
			this->vect[i] = other_vect.vect[i];
	}

	~Vector()
	{
		delete[] vect;
	}

	// гетеры

	long getSize()
	{
		return this.size;
	}

	T& getVect()
	{
		return *this.vect;
	}


	//перегрузки операторов


	Vector& operator= (const Vector& other_vect)
	{
		if (this->size == other_vect.size)
		{
			for (long i = 0; i < size; i++)
				this->vect[i] = other_vect.vect[i];
		}
		else
		{
			delete[] this->vect;
			this->size = other_vect.size;
			this->vect = new T[other_vect.size];
			for (long i = 0; i < other_vect.size; i++)
				this->vect[i] = other_vect.vect[i];
		}
		return *this;
	}

	bool operator== (const Vector& other_vect)     //сравнение векторов
	{
		bool flag = true;
		if (this->size != other_vect.size)
		{
			flag = false;
			return flag;
		}
		else
		{	
			for (unsigned int i = 0; i < other_vect.size; i++)
				if (this->vect[i] != other_vect.vect[i])
				{
					flag = false;
					return flag;
				}
			return flag;
		}
	}
	
	Vector operator+ (const Vector& other_vect)     //сложение векторов
	{
		if (this->size != other_vect.size)
		{
			cout << "Sizes don`t match!" << endl;
			exit(1);
		}
		else
		{
			Vector tmp(other_vect.size);              
			for (unsigned int i = 0; i < other_vect.size; i++)
				tmp.vect[i] = vect[i] + other_vect.vect[i];
			return tmp;
		}
	}

	Vector operator+= (const Vector& other_vect)
	{
		if (this->size != other_vect.size)
			return Vector(0);
		else
		{

			for (unsigned int i = 0; i < other_vect.size; i++)
				vect[i] = vect[i] + other_vect.vect[i];
			return *this;
		}
	}

	Vector& operator++ () //префиксный инкримент
	{
			for (unsigned int i = 0; i < this->size; i++)
				vect[i] = ++vect[i];
			return *this;
		
	}

	Vector operator++ (int a) //постфиксный инкримент
	{
		Vector tmp(*this);
		operator++ ();
		return tmp;

	}


	Vector operator- () //унарный минус
	{
		Vector tmp(this->size);
		for (unsigned int i = 0; i < this->size; i++)
			tmp.vect[i] = -vect[i];
		return tmp;
	}

	
	Vector operator- (const Vector& other_vect) // вычитание векторов
	{
		if (this->size != other_vect.size)
		{
			cout << "Sizes don`t match!" << endl;
			exit(1);
		}
		else
		{
			Vector tmp(other_vect.size);
			for (unsigned int i = 0; i < other_vect.size; i++)
				tmp.vect[i] = vect[i] - other_vect.vect[i];
			return tmp;
		}
	}

	Vector operator-= (const Vector& other_vect)
	{
		if (this->size != other_vect.size)
			return Vector(0);
		else
		{
			for (unsigned int i = 0; i < other_vect.size; i++)
				vect[i] = vect[i] - other_vect.vect[i];
			return *this;
		}
	}

	Vector& operator-- () //префиксный декримент
	{
		for (unsigned int i = 0; i < this->size; i++)
			vect[i] = --vect[i];
		return *this;

	}

	Vector operator-- (int a) //постфиксный декримент
	{
		Vector tmp(*this);
		operator-- ();
		return tmp;

	}

	Vector operator+ (T scalar)     //прибавление скаляра
	{
		    Vector tmp(this->size);
			for (unsigned int i = 0; i < this->size; i++)
			tmp.vect[i] = vect[i] + scalar;
			return tmp;
	}

	Vector operator- (T scalar)     //вычитание скаляра
	{
		Vector tmp(this->size);
		for (unsigned int i = 0; i < this->size; i++)
			tmp.vect[i] = vect[i] - scalar;
		return tmp;
	}

	Vector operator* (const T& scalar)     //умножение на скаляр
	{
		Vector tmp(this->size);
		for (long i = 0; i < this->size; i++)
			tmp.vect[i] = vect[i] * scalar;
		return tmp;
	}

	Vector operator/ (const T& scalar)     //деление на скаляр
	{
		if (scalar != 0)
		{
			Vector tmp(this->size);
			for (unsigned int i = 0; i < this->size; i++)
				tmp.vect[i] = vect[i] / scalar;
			return tmp;
		}
		else
		{
			cout << "ERROR: scalar = 0 \n";
			exit(1);
		}
	}
	
	T& operator [](long i) const
	{
		return(vect[i]);
	}

	friend std::istream& operator>> (std::istream& ist, const Vector& vect)
	{
		for (long i = 0; i < vect.size; i++)
			ist >> vect.vect[i];

		return ist;
	}

	friend::std::ostream& operator<< (std::ostream& ost, const Vector& vect)
	{
		ost << "\t";
		for (long i = 0; i < vect.size; i++)
			ost << vect.vect[i] << "\t";
		ost << std::endl;

		return ost;
	}


};

	
template <typename T>
class Matrix : public Vector<Vector<T>>
{
public:
	Matrix(long size, const Vector<T>& vectr) : Vector<Vector<T>>(size, vectr) {}

};


template <typename T>
class SLE : public Matrix<T>
{
public:
	SLE(long size, const Vector<T>& vectr) : Matrix<T>(size, vectr) {}


	Vector<T> GaussMethod()
	{

		long size = this->size;
		Vector<T> answr(size, 0);
		long max;

		Vector<T> ForHelpMatrix(size, 0);
		Matrix<T> HelpMatrix(size, ForHelpMatrix);


		long flag = 0;
		long tflag = 0;

		for (long i = 0; i < size; i++)
		{
			flag = 0;
			for (long j = 0; j < size; j++)
				if ((*this)[j][i] == 0)
					flag++;
			if (flag == size)
			{
				std::cout << "Wrong matrix, there are zero rows!" << std::endl;
				exit(1);
			}
		}

		flag = 0;

		for (long i = 0; i < size; i++)
		{
			i = i + tflag;
			if (i - flag >= size)
				break;

			max = i;
			for (long j = i + 1; j < size; j++)
			{
				if (abs((*this)[max][i - flag]) < abs((*this)[j][i - flag]))
					max = j;
			}

			if (i != max)
				swap1 <Vector<T>>((*this)[i], (*this)[max]);

			tflag = 0;
			if ((*this)[i][i - flag] == 0)
			{
				flag--;
				tflag = -1;
			}
			else
			{
				(*this)[i] = (*this)[i] / (*this)[i][i - flag];
				HelpMatrix[i][i - flag] = 1;

				for (long j = i + 1; j < size; j++)
					(*this)[j] = (*this)[j] - ((*this)[i] * (*this)[j][i - flag]);

				for (long j = 0; j < i; j++)
					(*this)[j] = (*this)[j] - ((*this)[i] * (*this)[j][i - flag]);
			}
		}


		tflag = 0;
		for (long i = size - 1; i >= 0; i--)
		{
			for (long j = size - 1; j >= 0; j--)
				if ((*this)[i][j] == 0)
					tflag++;
			if (tflag == size && (*this)[i][size] != 0)
			{
				cout << "Inconsistent system of equations:" << endl;
				cout << *this << endl;
				exit(0);
			}
			tflag = 0;
		}

		int infnt = 0;
		for (long i = size - 1; i >= 0; i--)
		{
			for (long j = size - 1; j >= 0; j--)
			{
				if ((*this)[i][j] != 0)
					tflag++;
				if (tflag > 1)
					infnt = 1;
				if (HelpMatrix[i][j] == 1)
					answr[j] = (*this)[i][size];
			}
			tflag = 0;
		}

		if (infnt)
			cout << "infinite number of solutions. Particular solution:" << endl;
		return answr;

	}

}; 


int main() {
	srand(time(NULL));
	long size;
	int choice;
	cout << "Enter size of your SLU: ";
	cin >> size;
	cout << endl;
	Vector<double> vectr(size + 1);

	SLE<double> sle1(size, vectr);

	cout << "Choose a filling method:\n1 - manual input\n2 - random SLU\n" << endl;
	cin >> choice;
	switch (choice) 
	{
	case 1:
	{
		cout << "Enter SLU:\n " << endl;
		cout << " (For convenience, the system can be entered line by line:\n" << size << " numbers and one more from the column of answers are entered";
		cout << " through\nthe 'space', then press 'enter' and enter the next line.)" << endl;
		cin >> sle1;
		break;
	}
	case 2:
	{
		for (long i = 0; i < size; i++)
		{
			for (long j = 0; j < size + 1; j++)
			{
				sle1[i][j] = ((double)(rand() % 1000) - 500) / 10;
				cout << "\t";
				cout << sle1[i][j] << "\t";
			}
			cout <<endl;
		}
		break;
	}
	default:
	{
		cout << "Wrong number!" << endl;
		exit(1);
	}
	}

	Vector<double> answer(size);
	answer = sle1.GaussMethod();
	cout << "Answer:" << endl;
	cout << "\t";
	cout << answer;

	cout << "Show solved matrix?\n1 - yes\n2 - no\n" << endl;
	cin >> choice;
	if (choice == 1)
	{
		cout << "Solved matrix:" << endl;
		cout << sle1;
	}

	return (0);
}