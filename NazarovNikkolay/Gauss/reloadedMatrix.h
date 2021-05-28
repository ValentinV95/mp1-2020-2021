#pragma once
#include "Vector.h"

using namespace std;

template < typename T >
class Matrix : public Vector< Vector < T > >{
public:
	Matrix(int lines) : Vector < Vector < T > >(lines, Vector < T >(lines)) {}
};