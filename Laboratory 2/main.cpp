#include <iostream>
#include <ctime>
#include <iomanip>
#include "interface.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(0));
	cout << "\t\t----------------------------------------------------------------------------\n";
	cout << "\t\t|A program for solving a system of linear equations by the Gaussian method |\n";
	cout << "\t\t----------------------------------------------------------------------------\n\n";
	cout << "    What do you want to do? \n\n";

	logic();

	return 0;
}