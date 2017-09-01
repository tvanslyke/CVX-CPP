/*
 * Variable.h
 *
 *  Created on: Aug 25, 2017
 *      Author: tim
 */

#ifndef VARIABLE_H_
#define VARIABLE_H_

#include <eigen3/Eigen/Dense>
#include <cstddef>
#include "Expressions/ExpressionObjects.h"
#include "Utilities/Name.h"
#include "Expressions/ConstantExpression.h"


namespace cvx{

template <class NameType, class T, ptrdiff_t M, ptrdiff_t N>
class Variable: public FunctionExpression<Variable<NameType, T, M, N>>
{
public:
	using value_type = Eigen::Matrix<T, M, N>;
	using name = NameType;
	Variable() = default;
	template <class ... U>
	Variable(U&& ... args):
		value_(std::forward<U>(args)...)
	{

	}
	const value_type & evaluate() const
	{
		return value_;
	}
	const value_type & value() const
	{
		return value_;
	}
	value_type & value()
	{
		return value_;
	}
	template <class Name, class U, ptrdiff_t R, ptrdiff_t C>
	decltype(auto) diff(const Variable<Name, U, R, C>) const
	{
		if(std::is_same_v<Name, NameType> and std::is_same_v<U, T> and M == R and N == C)
		{
			return ConstantExpression<T>(1);
		}
		else
		{
			return ConstantExpression<T>(0);
		}
	}
private:
	value_type value_;
};
template <class NameType, class T>
class Variable<NameType, T, 1, 1>: public FunctionExpression<Variable<NameType, T, 1, 1>>
{
public:
	using value_type = T;
	using name = NameType;
	Variable() = default;
	template <class ... U>
	Variable(U&& ... args):
		value_(std::forward<U>(args)...)
	{

	}
	const value_type & evaluate() const
	{
		return value_;
	}
	const value_type & value() const
	{
		return value_;
	}
	value_type & value()
	{
		return value_;
	}

	template <class Name, class U, ptrdiff_t M, ptrdiff_t N>
	decltype(auto) diff(const Variable<Name, U, M, N>) const
	{
		if(std::is_same_v<Name, NameType> and std::is_same_v<U, T> and M == 1 and N == 1)
		{
			return ConstantExpression<T>(1);
		}
		else
		{
			return ConstantExpression<T>(0);
		}
	}
private:
	value_type value_;
};

template <class NameType, class T>
class Variable<NameType, T, -1, -1>: public FunctionExpression<Variable<NameType, T, -1, -1>>
{
public:
	using value_type = Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>;
	using name = NameType;
	Variable() = default;
	template <class ... U>
	Variable(U&& ... args):
		value_(std::forward<U>(args)...)
	{

	}
	const value_type & evaluate() const
	{
		return value_;
	}
	const value_type & value() const
	{
		return value_;
	}
	value_type & value()
	{
		return value_;
	}

	template <class Name, class U, ptrdiff_t M, ptrdiff_t N>
	decltype(auto) diff(const Variable<Name, U, M, N>) const
	{
		if(std::is_same_v<Name, NameType> and std::is_same_v<U, T> and M == 1 and N == 1)
		{
			value_type v(value_.rows(), value_.cols());
			value.setConstant(1);
			return ConstantExpression<value_type>();
		}
		else
		{
			return ConstantExpression<T>(0);
		}
	}
private:
	value_type value_;
};

template <class NameType, class T, ptrdiff_t M, ptrdiff_t N>
constexpr const char * name_of(const Variable<NameType, T, M, N> &)
{
	return NameType::name();
}



template <class Stream, class NameType, class T, ptrdiff_t M, ptrdiff_t N>
Stream & operator<<(Stream & strm, const Variable<NameType, T, M, N> & var)
{
	return strm << name_of(var) << " (" << M << " x " << N << ") = " << var.value();
}

template <class NameType, class T, ptrdiff_t M, ptrdiff_t N>
constexpr size_t row_count(const cvx::Variable<NameType, T, M, N>& var)
{
	if constexpr(M == -1)
	{
		return var.value().rows();
	}
	else
	{
		return M;
	}
}

template <class NameType, class T, ptrdiff_t M, ptrdiff_t N>
constexpr size_t col_count(const cvx::Variable<NameType, T, M, N>& var)
{
	if constexpr(M == -1)
	{
		return var.value().rows();
	}
	else
	{
		return M;
	}
}

} /* namespace cvx */

#endif /* VARIABLE_H_ */
