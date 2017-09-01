/*
 * IsFunctionExpression.h
 *
 *  Created on: Sep 1, 2017
 *      Author: tim
 */

#ifndef CVX_CPP_EXPRESSIONS_TRAITS_ISFUNCTIONEXPRESSION_H_
#define CVX_CPP_EXPRESSIONS_TRAITS_ISFUNCTIONEXPRESSION_H_

#include "ExpressionDeclarations.h"

namespace cvx{

template <class T>
struct IsFunctionExpression
{
	static constexpr const bool value = std::is_base_of_v<FunctionExpression<T>, T>;
};
template <class T>
struct IsFunctionExpression<FunctionExpression<T>>
{
	static constexpr const bool value = true;
};
template <class T>
constexpr bool is_function_expression()
{
	return IsFunctionExpression<detail::remove_const_ref_t<T>>::value;
};


} /* namespace cvx */

#endif /* CVX_CPP_EXPRESSIONS_TRAITS_ISFUNCTIONEXPRESSION_H_ */
