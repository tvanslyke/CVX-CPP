/*
 * FunctionObjects.h
 *
 *  Created on: Aug 25, 2017
 *      Author: tim
 */

#ifndef EXPRESSIONOBJECTS_H_
#define EXPRESSIONOBJECTS_H_

#include <type_traits>
#include <utility>
#include "ExpressionTraits.h"
#include "Expressions/AddExpression.h"
#include "Expressions/SubExpression.h"
#include "Expressions/MulExpression.h"
#include "Expressions/DivExpression.h"
#include "Expressions/ConstantExpression.h"
namespace cvx{

template <class Func>
class FunctionExpression
{
public:
	FunctionExpression() = default;
	virtual ~FunctionExpression() = default;
	using self_type = FunctionExpression<Func>;
	using base_type = FunctionExpression<Func>;
	using derived_type = Func;
	using expression_type = Func;


	operator const expression_type&() const &
	{
		return *static_cast<const expression_type*>(this);
	}
	operator expression_type&&() &&
	{
		return std::move(*static_cast<expression_type*>(this));
	}


	template <class T>
	auto operator+(T && other) const
	{
		return make_add_expression(forward_self_as_derived(), std::forward<T>(other));
	}
	template <class T>
	auto operator-(T && other) const
	{
		return make_sub_expression(forward_self_as_derived(), std::forward<T>(other));
	}
	template <class T>
	auto operator*(T && other) const
	{
		return make_mul_expression(forward_self_as_derived(), std::forward<T>(other));
	}
	template <class T>
	auto operator/(T && other) const
	{
		return make_div_expression(forward_self_as_derived(), std::forward<T>(other));
	}
	decltype(auto) eval() const
	{
		return forward_self_as_derived().evaluate();
	}
	decltype(auto) eval()
	{
		return forward_self_as_derived().evaluate();
	}
	template <class Name, class T, ptrdiff_t M, ptrdiff_t N>
	decltype(auto) differentiate(const Variable<Name, T, M, N> & var) const
	{
		return forward_self_as_derived().diff(var);
	}
	template <class Name, class T, ptrdiff_t M, ptrdiff_t N>
	decltype(auto) differentiate(const Variable<Name, T, M, N> & var)
	{
		return forward_self_as_derived().diff(var);
	}
private:
	decltype(auto) forward_self_as_derived() const &
	{
		return static_cast<const expression_type &>(*this);
	}
	decltype(auto) forward_self_as_derived() &&
	{
		return static_cast<expression_type &&>(*this);
	}
};
template <class Func>
using fexpr = FunctionExpression<Func>;


template <class T>
using function_expression_overload_t = std::enable_if_t<is_function_expression<T>(), const FunctionExpression<T> &>;
template <class T>
using non_function_expression_overload_t = std::enable_if_t<not is_function_expression<T>(), const T &>;


template <class T, class Func, class = std::enable_if_t<is_function_expression<T>()>>
auto operator+(const FunctionExpression<T> & left, const FunctionExpression<Func> & right)
{
	return make_add_expression(forward_as_derived(left), forward_as_derived(right));
}
template <class T, class Func, class = std::enable_if_t<not is_function_expression<T>()>>
auto operator+(const T & left, const FunctionExpression<Func> & right)
{
	return make_add_expression(left, forward_as_derived(right));
}
template <class T, class Func, class = std::enable_if_t<is_function_expression<T>()>>
auto operator-(const FunctionExpression<T> & left, const FunctionExpression<Func> & right)
{
	return make_sub_expression(forward_as_derived(left), forward_as_derived(right));
}
template <class T, class Func, class = std::enable_if_t<not is_function_expression<T>()>>
auto operator-(const T & left, const FunctionExpression<Func> & right)
{
	return make_sub_expression(left, forward_as_derived(right));
}
template <class T, class Func, class = std::enable_if_t<is_function_expression<T>()>>
auto operator*(const FunctionExpression<T> & left, const FunctionExpression<Func> & right)
{
	return make_mul_expression(forward_as_derived(left), forward_as_derived(right));
}
template <class T, class Func, class = std::enable_if_t<not is_function_expression<T>()>>
auto operator*(const T & left, const FunctionExpression<Func> & right)
{
	return make_mul_expression(left, forward_as_derived(right));
}
template <class T, class Func, class = std::enable_if_t<is_function_expression<T>()>>
auto operator/(const FunctionExpression<T> & left, const FunctionExpression<Func> & right)
{
	return make_div_expression(forward_as_derived(left), forward_as_derived(right));
}
template <class T, class Func, class = std::enable_if_t<not is_function_expression<T>()>>
auto operator/(const T & left, const FunctionExpression<Func> & right)
{
	return make_div_expression(left, forward_as_derived(right));
}


} /* namespace cvx */

#endif /* EXPRESSIONOBJECTS_H_ */
