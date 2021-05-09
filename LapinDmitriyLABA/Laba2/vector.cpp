// vector.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<iomanip>
#include"Vector.h"






void printMenu() {
    std::cout << "\n1.Create new random SLAU\n";
    std::cout << "2.Create new user SLAU\n";
    std::cout << "3.Print SLAU\n";
    std::cout << "4.Solve SLAU\n";
    std::cout << "5.EXIT\n";
}









int main()
{



    int size = 0; int inp;
    SLAU<double> * sll = 0;


    srand(time(NULL));


    printMenu();


    std::cout << ">> ";
    std::cin >> inp;
    while (inp != 5) {
        switch (inp) {
        case 1:


            std::cout << "Input Size:\n>> ";
            std::cin >> size;
            if (sll!=NULL)
                delete sll;
            sll = new SLAU<double>(size);
            std::cout << "SLAU created, slau size:\n" << size;
            break;
        case 2:
        {
            std::cout << "Input Size:\n>> ";
            std::cin >> size;



            std::cout << "Input " << size * size << " matrix elements\n>> ";
            Vector<Vector<double>> matrix(size);
            for (int i = 0; i < size; i++)
                matrix[i].setSize(size);

            for (int i = 0; i < size; i++)
                for (int j = 0; j < size; j++)
                    std::cin >> matrix[i][j];


            std::cout << "Input " << size << " vector elements\n>> ";
            Vector<double> input(size);

            for (int i = 0; i < size; i++)
                std::cin >> input[i];



            if (sll != NULL)
                delete sll;
            sll = new  SLAU <double>(input, matrix);



            break;
        }
        
        case 3:
            sll->printMatrix();
            break;
        case 4:
            if (sll->solve()) {

                Vector<double> s(sll->getSolution());
                sll->printMatrix();
                
                std::cout << "\n\n\nVector answer is: (";
                for (int i = 0; i < s.getSize()-1; i++)
                    std::cout << s[i] << ", ";
                std::cout << s[s.getSize() - 1] << ")";
            }
            else {

                std::cout << "SLAU is unsolvable";
            }

            break;

        }


        printMenu();
        std::cout << "\n>> ";
        std::cin >> inp;



    }



}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
