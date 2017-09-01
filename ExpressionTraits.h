/*
 * ExpressionTraits.h
 *
 *  Created on: Aug 25, 2017
 *      Author: tim
 */

#ifndef EXPRESSIONTRAITS_H_
#define EXPRESSIONTRAITS_H_
#include <type_traits>


#define OP_RESULT_TYPE(left_type, right_type, op) \
	    std::remove_reference_t<std::remove_const_t<decltype(evaluate_expression(std::declval<left_type>()) op evaluate_expression(std::declval<right_type>()))>>

namespace cvx{

	namespace detail{
		template <class T>
		using remove_const_ref_t = std::remove_const_t<std::remove_reference_t<T>>;
	} /* namespace detail */



template <class Func>
class FunctionExpression;

template <class T, class Impl>
class Function;

template <class, class, ptrdiff_t = 1, ptrdiff_t = 1>
class Variable;

template <class T>
class ConstantExpression;

namespace detail{
	struct FunctionBase{};
} /* namespace detail */

template <class T>
struct IsFunction;
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
