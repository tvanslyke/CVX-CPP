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
#include "ExpressionObjects.h"
#include "Utilities/Name.h"


namespace cvx{
template <class NameType, class T, ptrdiff_t M = 1, ptrdiff_t N = 1>
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
} /* namespace cvx */

#endif /* VARIABLE_H_ */
