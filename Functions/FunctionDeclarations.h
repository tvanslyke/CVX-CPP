/*
 * FunctionDeclarations.h
 *
 *  Created on: Sep 1, 2017
 *      Author: tim
 */

#ifndef CVX_CPP_FUNCTIONS_FUNCTIONDECLARATIONS_H_
#define CVX_CPP_FUNCTIONS_FUNCTIONDECLARATIONS_H_



namespace cvx{

template <class Func, class Arg, class ... Args>
class Function;

template <class T>
class ExpFunction;
template <class T>
class PowFunction;
template <class T>
class LogFunction;

} /* namespace cvx */

#endif /* CVX_CPP_FUNCTIONS_FUNCTIONDECLARATIONS_H_ */
