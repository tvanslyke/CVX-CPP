/*
 * IsFunction.h
 *
 *  Created on: Sep 1, 2017
 *      Author: tim
 */

#ifndef CVX_CPP_EXPRESSIONS_TRAITS_ISFUNCTION_H_
#define CVX_CPP_EXPRESSIONS_TRAITS_ISFUNCTION_H_


#include "ExpressionDeclarations.h"


namespace cvx{

template <class T>
struct IsFunctionExpression;

template <class T>
struct IsFunction
{
	static constexpr const bool value = std::is_base_of_v<detail::FunctionBase, T>;
};
template <class T>
struct IsFunction<FunctionExpression<T>>
{
	static constexpr const bool value = std::is_base_of_v<detail::FunctionBase, T>;
};
template <class T, class Impl>
struct IsFunction<Function<T, Impl>>
{
	static constexpr const bool value = true;
};

template <class T>
constexpr bool is_function()
{
	return IsFunction<detail::remove_const_ref_t<T>>::value;
};


} /* namespace cvx */

#endif /* CVX_CPP_EXPRESSIONS_TRAITS_ISFUNCTION_H_ */
