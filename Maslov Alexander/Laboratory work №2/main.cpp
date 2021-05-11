#include "vector.h"
#include "slau.h"
#include <iostream>
#include <time.h>

using namespace std;

int main() {

    srand(time_t(NULL));

    Vector<double> b;
    //for (int i = 10; i < 12; ++i)
    b.push_back(34);
    b.push_back(22);
    b.push_back(493);
    b.push_back(2);

    SLAU<double> test(4);

    test[0][0] = 2;
    test[0][1] = 4;
    test[0][2] = 1;
    test[0][3] = 4;
    test[1][0] = 5;
    test[1][1] = 2;
    test[1][2] = 1;
    test[1][3] = 7;
    test[2][0] = 2;
    test[2][1] = 3;
    test[2][2] = 4;
    test[2][3] = 9;
    test[3][0] = 5;
    test[3][1] = 8;
    test[3][2] = 6;
    test[3][3] = 1;

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
            test[i][j] = rand() % 100;
    }

    for (int i = 0; i < test.Size(); ++i) {
        for (int j = 0; j < test[i].Size(); ++j)
            cout << test[i][j] << " ";
        cout << b[i] << endl;
    }

    Vector<double> *answer = test.Gausse(b);

    cout << endl << "X : ";
    if (answer)
        for (int k = 0; k < answer->Size(); ++k)
            cout << (*answer)[k] << " ";

    return 0;
}
