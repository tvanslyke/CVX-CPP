/*
 * Calculus.h
 *
 *  Created on: Aug 26, 2017
 *      Author: tim
 */

#ifndef CALCULUS_H_
#define CALCULUS_H_

#include "Expressions/ConstantExpression.h"
#include "Expressions/Traits/ExpressionTraits.h"
#include "Variable.h"

namespace cvx{
template <class T, class Name, class U, ptrdiff_t M, ptrdiff_t N>
decltype(auto) derivative_of(const T & arg, const Variable<Name, U, M, N> & var)
{
	if constexpr (is_function_expression<T>())
	{
		if constexpr(expression_traits<T>::is_variable and std::is_same_v<typename expression_traits<T>::derived_type, Variable<Name, U, M, N>>)
		{
			return ConstantExpression<double>(1);
		}
		else
		{
			return arg.differentiate(var);
		}
	}
	else
	{
		return 0;
	}
}
} /* namespace cvx */
#endif /* CALCULUS_H_ */
