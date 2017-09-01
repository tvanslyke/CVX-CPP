/*
 * Functions.h
 *
 *  Created on: Aug 25, 2017
 *      Author: tim
 */

#ifndef FUNCTIONOBJECTS_H_
#define FUNCTIONOBJECTS_H_
#include "../ExpressionObjects.h"
#include "../Variable.h"
#include "../Calculus.h"
#include <cmath>

namespace cvx{

namespace detail{
	static auto exp_impl = [&](double d){return std::exp(d);};
	static auto pow_impl = [&](double x, double p){return std::pow(x, p);};
	static auto log_impl = [&](double x){ return std::log(x); };

	template <class Func, class Tuple, size_t ... I>
	decltype(auto) invoke_with_tuple_(Func && func, const Tuple & args, std::index_sequence<I...>)
	{
		return std::forward<Func>(func)(std::get<I>(args) ...);
	}

	template <class Func, class ... T>
	decltype(auto) invoke_with_tuple(Func && func, const std::tuple<T...> & args)
	{
		return invoke_with_tuple_(std::forward<Func>(func), args, std::index_sequence_for<T...>{});
	}

} /* namespace detail */
template <class Func, class Arg>
class Function:
		public detail::FunctionBase
{
public:
	using derived_type = Func;
	Function(const Arg & arg):
		arg_{arg}
	{

	}
	Function(Arg && arg):
		arg_{std::move(arg)}
	{

	}
	decltype(auto) evaluate() const
	{
		return as_derived()();
	}

protected:
	const Arg & arg() const
	{
		return arg_;
	}
private:
	const derived_type & as_derived() const
	{
		return *static_cast<const derived_type*>(this);
	}
	derived_type & as_derived()
	{
		return *static_cast<derived_type*>(this);
	}
	const Arg arg_;
};

template <class T>
class ExpFunction: 	public FunctionExpression<ExpFunction<T>>,
					public Function<ExpFunction<T>, T>
{
public:
	using self_type = ExpFunction<T>;
	using base_type = Function<self_type, T>;
	ExpFunction(const T & arg):
		base_type(arg)
	{

	}
	decltype(auto) operator()() const
	{
		return std::exp(evaluate_expression(base_type::arg()));
	}
	template <class Name, class U>
	decltype(auto) diff(const Variable<Name, U, 1, 1> & var)
	{
		return self_type(base_type::arg()) * derivative_of(base_type::arg(), var);
	}
	template <class Name, class U>
	decltype(auto) diff(const Variable<Name, U, 1, 1> & var) const
	{
		return self_type(base_type::arg()) * derivative_of(base_type::arg(), var);
	}
};

template <class T>
class PowFunction: 	public FunctionExpression<PowFunction<T>>,
					public Function<PowFunction<T>, T>
{
public:
	using self_type = PowFunction<T>;
	using base_type = Function<self_type, T>;
	PowFunction(const T & arg, double power):
		base_type(arg), power_(power)
	{

	}
	decltype(auto) operator()() const
	{
		return std::pow(evaluate_expression(base_type::arg()), power_);
	}
	template <class Name, class U>
	decltype(auto) diff(const Variable<Name, U, 1, 1> & var)
	{
		return power_ * self_type(base_type::arg(), power_ - 1) * derivative_of(base_type::arg(), var);
	}
	template <class Name, class U>
	decltype(auto) diff(const Variable<Name, U, 1, 1> & var) const
	{
		return power_ * self_type(base_type::arg(), power_ - 1) * derivative_of(base_type::arg(), var);
	}
private:
	double power_;
};


template <class T>
class LogFunction: 	public FunctionExpression<LogFunction<T>>,
					public Function<LogFunction<T>, T>
{
public:
	using self_type = LogFunction<T>;
	using base_type = Function<self_type, T>;
	LogFunction(const T & arg):
		base_type(arg)
	{

	}
	decltype(auto) operator()() const
	{
		return std::log(evaluate_expression(base_type::arg()));
	}
	template <class Name, class U>
	decltype(auto) diff(const Variable<Name, U, 1, 1> & var)
	{
		return derivative_of(base_type::arg(), var) / base_type::arg();
	}
	template <class Name, class U>
	decltype(auto) diff(const Variable<Name, U, 1, 1> & var) const
	{
		return derivative_of(base_type::arg(), var) / base_type::arg();
	}
};


} /* namespace cvx */

#endif /* FUNCTIONOBJECTS_H_ */
