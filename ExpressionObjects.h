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
	template <class T> using right_add_type = AddExpression<Func, T>;
	template <class T> using left_add_type  = AddExpression<T, Func>;
	template <class T> using right_sub_type = SubExpression<Func, T>;
	template <class T> using left_sub_type  = SubExpression<T, Func>;
	template <class T> using right_mul_type = MulExpression<Func, T>;
	template <class T> using left_mul_type  = MulExpression<T, Func>;
	template <class T> using right_div_type = DivExpression<Func, T>;
	template <class T> using left_div_type  = DivExpression<T, Func>;

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




template <class T, class Func>
auto operator+(const FunctionExpression<T> & left, const FunctionExpression<Func> & right)
{
	return make_add_expression(forward_as_derived(left), forward_as_derived(right));
}
template <class T, class Func>
auto operator-(const FunctionExpression<T> & left, const FunctionExpression<Func> & right)
{
	return make_sub_expression(forward_as_derived(left), forward_as_derived(right));
}
template <class T, class Func>
auto operator*(const FunctionExpression<T> & left, const FunctionExpression<Func> & right)
{
	return make_mul_expression(forward_as_derived(left), forward_as_derived(right));
}
template <class T, class Func>
auto operator/(const FunctionExpression<T> & left, const FunctionExpression<Func> & right)
{
	return make_div_expression(forward_as_derived(left), forward_as_derived(right));
}

} /* namespace cvx */

#endif /* EXPRESSIONOBJECTS_H_ */
