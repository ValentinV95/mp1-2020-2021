#include <iostream>
using namespace std;
template <class T>
class vector
{
public:
	T** link, input; size_t size_1, size_2; 
	vector()
	{ 
		 link = nullptr; 
	};
	vector<T>(size_t size1, size_t size2)
	{
		size_1 = size1;
		size_2 = size2;
		input = 0;
		link = new T*[size_1];
		for (size_t i = 0; i < this->size_1; i++)
		{
			link[i] = new T[size_2];
		}
		for (size_t i = 0; i < (this->size_1); i++)
		{
			for (size_t j = 0; j < this->size_2; j++)
			{
				link[i][j] =0;
			}
		}
	}
	void fill_manually(vector A)
	{
		for (size_t i = 0; i < (this->size_1); i++)
		{
			for (size_t j = 0; j < this->size_2; j++)
			{
				cin >> input;
				A.link[i][j] = input;
			}
		}
	}
	void fill_randomly(vector A)
	{
		srand(time(NULL));
		for (size_t i = 0; i < (this->size_1); i++)
		{
			for (size_t j = 0; j < this->size_2; j++)
			{
				A.link[i][j] = rand();
			}
		}
	}
	size_t getsize() { return(size_1); }
	T** getlink() { return(link); }
	/*void setlink_manual()
	{
		for(size_t i=0; i<this->size;i++)
		cin >> this->link[i];
	}*/
	//~vector(){ delete[] link;}
	friend vector<T> operator + (vector& left, vector& right)
	{
		vector<T> temp(left.size_1, left.size_2);
		for (size_t i = 0; i < temp.size_1; i++)
		{
			for (size_t j = 0; j < temp.size_2; j++)
			{
				temp.link[i][j] = left.link[i][j] + right.link[i][j];
			}
		}
		return(temp);
	}
	friend vector<T> operator - (vector& left, vector& right)
	{
		vector<T> temp(left.size_1, left.size_2);
		for (size_t i = 0; i < temp.size_1; i++)
		{
			for (size_t j = 0; j < temp.size_2; j++)
			{
				temp.link[i][j] = left.link[i][j] - right.link[i][j];
			}
		}
		return(temp);
	}
	friend vector<T> operator * (T left, vector<T> right)
	{
		vector temp(right.size_1, right.size_2);
		for (size_t i = 0; i < temp.size_1; i++)
		{
			for (size_t j = 0; j < temp.size_2; j++)
			{
				temp.link[i][j] = left * right.link[i][j];
			}
		}
		return(temp);
	}
	friend vector<T> operator / (vector left, T right)
	{
		vector temp(left.size_1, left.size_2);
		for (size_t i = 0; i < temp.size_1; i++)
		{
			for (size_t j = 0; j < temp.size_2; j++)
			{
				temp.link[i][j] = (left.link[i][j]) / right;
			}
		}
		return(temp);
	}
	vector<T>& operator = (vector right)
	{
		this->size_1 = right.size_1;
		this->size_2 = right.size_2;
		for (size_t i = 0; i < this->size_1; i++)
		{
			for (size_t j = 0; j < this->size_2; j++)
			{
				this->link[i][j] = right.link[i][j];
			}
		}
		return(*this);
	}
	void print()
	{
		for (int i = 0; i < (this->size_1); i++)
		{
			for (size_t j = 0; j < this->size_2; j++)
			{
				cout << this->link[i][j] << "		";
			}
			cout << "" << endl;
		}
	}
};
template <class T>
class matrix :public vector<vector<T>>
{
public:
	/*vector<T> A{};
	matrix<T>(size_t size1)
	{
	vector<T> matrix(size1, size1);
	A = matrix;
	}
	void fill_manually()
	{
		vector<T> temp(A.size_1, A.size_1);
		temp.fill_manually(temp);
		A = temp;
	}
	void printm()
	{
		vector<T> temp(A.size1, A.size1);
		temp = A;
		temp.print();
	}*/
	T** linkM, inputM; size_t size_1M, size_2M;
	matrix<T>(size_t size1, size_t size2)
	{
		size_1M = size1;
		size_2M = size2;
		inputM = 0;
		linkM = new T * [size_1M];
		for (size_t i = 0; i < this->size_1M; i++)
		{
			linkM[i] = new T[size_2M];
		}
		for (size_t i = 0; i < (this->size_1M); i++)
		{
			for (size_t j = 0; j < this->size_2M; j++)
			{
				linkM[i][j] = 0;
			}
		}
	}
	matrix<T>(size_t size1)
	{
		size_1M = size1;
		size_2M = size1;
		inputM = 0;
		linkM = new T * [size_1M];
		for (size_t i = 0; i < this->size_1M; i++)
		{
			linkM[i] = new T[size_2M];
		}
		for (size_t i = 0; i < (this->size_1M); i++)
		{
			for (size_t j = 0; j < this->size_2M; j++)
			{
				linkM[i][j] = 0;
			}
		}
	}
	void fill_manually()
	{
		for (size_t i = 0; i < (this->size_1M); i++)
		{
			for (size_t j = 0; j < this->size_2M; j++)
			{
				cin >> inputM;
				this->linkM[i][j] = inputM;
			}
		}
	}
	void printm()
	{
		for (int i = 0; i < (this->size_1M); i++)
		{
			for (size_t j = 0; j < this->size_2M; j++)
			{
				cout << this->linkM[i][j] << "		";
			}
			cout << "" << endl;
		}
	}
	void fill_randomly()
	{
		srand(time(NULL));
		for (size_t i = 0; i < (this->size_1M); i++)
		{
			for (size_t j = 0; j < this->size_2M; j++)
			{
				this->linkM[i][j] = rand();
			}
		}
	}
	void swap(size_t initial, size_t swappable)
	{
		T* temp;
		temp = new T[this->size_1M];
		for (size_t j = 0; j < size_1M; j++)
		{
			temp[j] = linkM[initial][j];
			linkM[initial][j] = linkM[swappable][j];
			linkM[swappable][j] = temp[j];
		}
	}
	void nullify_row(size_t i)
	{
		T temp;
		if (linkM[i][i] != 0)
		{
			if (linkM[i][i] < 0)
			{
				for (size_t j = 0; j < this->size_1M; j++)
				{
					linkM[i][j] = (-1) * linkM[i][j];
				}
			}
			for (size_t i1 = i; i1 < this->size_1M - 1; i1++)
			{
				if (linkM[i1 + 1][i] != 0)
				{
					if (linkM[i1 + 1][i] < 0)
					{
						for (size_t j = 0; j < this->size_1M; j++)
						{
							linkM[i1 + 1][j] = (-1) * linkM[i1 + 1][j];
						}
					}
					temp = linkM[i1 + 1][i] / linkM[i][i];
					for (size_t J = 0; J < this->size_1M; J++)
					{
						linkM[i1 + 1][J] = linkM[i1 + 1][J] - linkM[i][J] * temp;
					}
				}
			}
			/*for (size_t i1 = i; i1 > 1; i1--)
			{
				if (linkM[i1-1][i] != 0)
				{
					if (linkM[i1 - 1][i] < 0)
					{
						for (size_t j = 0; j < this->size_1M; j++)
						{
							linkM[i1 - 1][j] = (-1) * linkM[i1 - 1][j];
						}
					}
					temp = linkM[i1 - 1][i] / linkM[i][i];
					for (size_t J = 0; J < this->size_1M; J++)
					{
						linkM[i1 - 1][J] = linkM[i1 - 1][J] - linkM[i][J] * temp;
					}
				}
			}*/
		}
		else
		{
			cout << "Бесконечно много решений" << endl;
		}
	}
	void Gauss()
	{
		/*{
			T temp, temp1; int* counter; size_t count = 0, trash = 0, count1 = 0, count2 = 0, spare1 = 0, spare2 = 0;
			for (size_t i = 0; i < size_1M; i++)
				{
					for (size_t j = 0; j < size_1M; j++)
					{
						if (linkM[j][i] == 0) { count1++; }
						if (linkM[i][j] == 0) { count2++; }
					}
					if (count1 == size_1M)
					{
						spare1++;
					}
					if (count2 == size_1M)
					{
						spare2++;
					}
					count1 = 0;
					count2 = 0;
				}
			if (spare1 != 0)
				{
					cout << "Нет решений" << endl;
				}
			else { if (spare2 != 0) { cout << "Бесконечно много решений" << endl; } }
			/*for (size_t i = 0; i < size_1M; i++)
					{
						count1 = 0;
						while (count1 == 0)
						{
							if (linkM[tj][i] != 0 && counter[tj] == 0)
							{
								counter[tj]++;
								temp = linkM[tj][i];
								for (size_t J=0; J < size_1M; J++)
								{
									linkM[tj][J] = linkM[tj][J] / temp;
									if (linkM[tj][J] < 0)
									{
										linkM[tj][J] = (-1) * linkM[tj][J];
									}
								}
								if (tj < size_1M)
								{
									if (linkM[(tj + 1)][i] != 0)//зануляем ниже ведущего
									{
										if (linkM[(tj + 1)][i] > 0)
										{
											for (size_t i1 = (tj + 1); i1 < size_1M; i1++)
											{
												temp1 = linkM[i1][i] / linkM[tj][i];
												for (size_t B = tj; B < size_1M; B++)
												{
													linkM[i1][B] = linkM[i1][B] - temp1 * linkM[tj][i];
												}

											}
											cout << "Получилось:" << endl;
											this->printm();
										}
										else
										{
											for (size_t i1 = tj + 1; i1 < size_1M; i1++)
											{
												temp1 = linkM[tj][i] / linkM[i1][i];
												for (size_t B = 0; B < size_1M; B++)
												{
													linkM[i1][B] = linkM[i1][B] + temp1 * linkM[tj][i];
												}

											}
										}
									}


								}
								if (tj != 0)
								{
									if (linkM[tj - 1][i] != 0)//зануляем выше ведущего
									{
										if (linkM[tj - 1][i] > 0)
										{
											for (size_t i1 = tj - 1; i1 > 0; i1--)
											{
												temp1 = linkM[i1][i] / linkM[tj][i];
												for (size_t B = 0; B < size_1M; B++)
												{
													linkM[i1][B] = linkM[i1][B] - temp1 * linkM[tj][i];
												}

											}
										}
										else
										{
											for (size_t i1 = tj - 1; i1 > 0; i1--)
											{
												temp1 = linkM[i1][i] / linkM[tj][i];
												for (size_t B = 0; B < size_1M; B++)
												{
													linkM[i1][B] = linkM[i1][B] + temp1 * linkM[tj][i];
												}

											}
										}
									}
								}
								else
								{

								}
								count1++;
							}
							tj++;
							if (tj >= size_1M-1) { count1++; tj = 0; }
						}
					}
					
		}*/
		size_t tempc=0;
		for (size_t i = 0; i < this->size_1M; i++)
		{
			for (size_t j = i; j < this->size_1M-1; j++)
			{
				tempc = j;
				if(linkM[i][j]<linkM[i][j+1])
				{
					tempc = j + 1;
				}
				
			}
			this->swap(i, tempc);
			this->nullify_row(i);
		}


	}
};
void main()
{
	setlocale(LC_ALL, "Russian");
	matrix<double> test(4);
	test.fill_randomly();
	test.printm();
	test.Gauss();
	cout<< "    " << endl;
	test.printm();
}