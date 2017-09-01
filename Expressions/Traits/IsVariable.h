/*
 * IsVariable.h
 *
 *  Created on: Sep 1, 2017
 *      Author: tim
 */

#ifndef CVX_CPP_EXPRESSIONS_TRAITS_ISVARIABLE_H_
#define CVX_CPP_EXPRESSIONS_TRAITS_ISVARIABLE_H_

#include "ExpressionDeclarations.h"

namespace cvx{



template <class T>
struct IsVariable
{
	static constexpr const bool value = false;
};
template <class T>
struct IsVariable<FunctionExpression<T>>
{
	static constexpr const bool value = IsVariable<T>::value;
};
template <class Name, class T, ptrdiff_t M, ptrdiff_t N>
struct IsVariable<Variable<Name, T, M, N>>
{
	static constexpr const bool value = true;
};
template <class T>
constexpr bool is_variable()
{
	return IsVariable<detail::remove_const_ref_t<T>>::value;
};


} /* namespace cvx */

#endif /* CVX_CPP_EXPRESSIONS_TRAITS_ISVARIABLE_H_ */
