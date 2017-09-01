/*
 * Main.cpp
 *
 *  Created on: Aug 25, 2017
 *      Author: tim
 */

#include "Variable.h"
#include <iostream>

#include "ExpressionObjects.h"
#include "Functions/Functions.h"

using namespace cvx;
int main()
{
	Variable<SYMB("y"), double> x(1.0);
	Variable<SYMB("x"), double> y(2.0);
	double expr = (x * y + (x + y) / (x - y)).eval();
	std::cout << expr << ", " << 1.0 * 2.0 + (1.0 + 2.0) / (1.0 - 2.0) << std::endl;
	double exprdiffx = derivative_of((x * y + (x + y) / (x - y)), x).eval();
	std::cout << exprdiffx << std::endl;
	std::cout << (2 * cvx::pow(4*x, 2)).eval() << std::endl;
	std::cout << derivative_of(2 * cvx::pow(4*x, 2), x).eval() << std::endl;
	std::cout << x << ", " << y << std::endl;
	std::cout << "Done." << std::endl;
	return 0;
}
