/*
 * ExpressionTraits.h
 *
 *  Created on: Aug 25, 2017
 *      Author: tim
 */

#ifndef EXPRESSIONTRAITS_H_
#define EXPRESSIONTRAITS_H_
#include <type_traits>

#include "IsFunction.h"
#include "IsFunctionExpression.h"
#include "IsVariable.h"

#define CVX_OP_RESULT_TYPE(left_type, right_type, op) \
	    std::remove_reference_t<std::remove_const_t<decltype(evaluate_expression(std::declval<left_type>()) op evaluate_expression(std::declval<right_type>()))>>

namespace cvx{

template <class T, bool = is_function_expression<T>()>
struct ExpressionTraits;



template <class T>
struct ExpressionTraits<FunctionExpression<T>, true>
{
	static constexpr const bool is_expression = true;
	static constexpr const bool is_base = true;
	static constexpr const bool is_function = is_function<T>();
	static constexpr const bool is_variable = is_variable<T>();
	using self_type = FunctionExpression<T>;
	using derived_type = T;
	using base_type = FunctionExpression<T>;
};

template <class T>
struct ExpressionTraits<T, true>
{
	static constexpr const bool is_expression = true;
	static constexpr const bool is_base = false;
	static constexpr const bool is_function = is_function<T>();
	static constexpr const bool is_variable = is_variable<T>();
	using self_type = T;
	using derived_type = T;
	using base_type = FunctionExpression<T>;
};
template <class T>
struct ExpressionTraits<T, false>
{
	static constexpr const bool is_expression = false;
	static constexpr const bool is_base = false;
	static constexpr const bool is_function = false;
	static constexpr const bool is_variable = false;
	using self_type = T;
	using derived_type = T;
	using base_type = T;
};

template <class T>
using expression_traits = ExpressionTraits<detail::remove_const_ref_t<T>>;

template <class T>
using derived_type_t = typename expression_traits<T>::derived_type;

template <class T>
const derived_type_t<T>& forward_as_derived(const T& expression)
{
	using d_t = derived_type_t<T>;
	return static_cast<const d_t&>(expression);
}
template <class T>
derived_type_t<T>& forward_as_derived(T& expression)
{
	using d_t = derived_type_t<T>;
	return static_cast<d_t&>(expression);
}
template <class T>
derived_type_t<T>&& forward_as_derived(T&& expression)
{
	using d_t = derived_type_t<T>;
	return static_cast<d_t&&>(std::move(expression));
}

template <class T>
decltype(auto) evaluate_expression(T && value)
{
	if constexpr(is_function_expression<T>())
	{
		return forward_as_derived(std::forward<T>(value)).eval();
	}
	else
	{
		return std::forward<T>(value);
	}
}

} /* namespace cvx */

#endif /* EXPRESSIONTRAITS_H_ */
