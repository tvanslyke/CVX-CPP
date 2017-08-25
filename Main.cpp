/*
 * Main.cpp
 *
 *  Created on: Aug 25, 2017
 *      Author: tim
 */

#include "Variable.h"
#include <iostream>

#include "ExpressionObjects.h"

using namespace cvx;
int main()
{
	Variable<SYMB("y"), double> x(1.0);
	Variable<SYMB("x"), double> y(2.0);
	double expr = (x * y + (x + y) / (x - y)).eval();
	std::cout << expr << ", " << 1.0 * 2.0 + (1.0 + 2.0) / (1.0 - 2.0) << std::endl;
	std::cout << x << ", " << y << std::endl;
	return 0;
}
