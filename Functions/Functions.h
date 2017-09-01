/*
 * Functions.h
 *
 *  Created on: Aug 26, 2017
 *      Author: tim
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
#include "FunctionObjects.h"


namespace cvx{


template <class T>
auto exp(T && arg)
{
	return ExpFunction<T>(std::forward<T>(arg));
}
template <class T>
auto pow(T && arg, double power)
{
	return PowFunction<T>(std::forward<T>(arg), power);
}

template <class T>
auto log(T && arg)
{
	return LogFunction<T>(std::forward<T>(arg));
}

} /* namespace cvx */

#endif /* FUNCTIONS_H_ */
