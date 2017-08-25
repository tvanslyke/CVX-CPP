/*
 * Functions.h
 *
 *  Created on: Aug 25, 2017
 *      Author: tim
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
#include "ExpressionObjects.h"
#include "Variable.h"
#include "ConstantExpression.h"
#include <cmath>
namespace cvx{


template <class T, class U, size_t M, size_t N>
auto derivative_of(const T & arg, const cvx::Variable<U, M, N> & var)
{
	if /* constexpr */ (is_function_expression<T>())
	{
		if(same_expression(arg, var))
		{
			return ConstantExpression<double>(1.0);
		}
		return arg.diff(var);
	}
	else
	{
		return 0;
	}
}


template <class T, class Impl>
class Function: public FunctionExpression<Function<T, Impl>>, public detail::FunctionBase
{
public:
	Function(const T & arg, const Impl & impl):
		arg_(arg), impl_(impl)
	{

	}
	decltype(auto) evaluate() const
	{
		return impl_(evaluate_espression(arg_));
	}

	const T & arg() const
	{
		return arg_;
	}
	const Impl & impl() const
	{
		return impl_;
	}
	Impl & impl()
	{
		return impl_;
	}
private:
	const T & arg_;
	Impl impl_;
};

template <class T, class Impl = decltype(exp)>
class ExpFunction: public Function<T, Impl>
{
	using self_type = ExpFunction<T, Impl>;
	ExpFunction(const T & arg, const Impl & impl = exp):
		Function<T, Impl>(arg, impl)
	{

	}

	template <class T>
	decltype(auto) differentiate(const Variable<T, 1, 1> & var)
	{
		return self_type(arg(), impl()) * derivative_of(arg(), var);
	}

};

} /* namespace cvx */

#endif /* FUNCTIONS_H_ */
