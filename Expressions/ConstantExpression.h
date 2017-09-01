/*
 * ConstantExpression.h
 *
 *  Created on: Aug 25, 2017
 *      Author: tim
 */

#ifndef EXPRESSIONS_CONSTANTEXPRESSION_H_
#define EXPRESSIONS_CONSTANTEXPRESSION_H_

#include <utility>

#include "Traits/ExpressionTraits.h"
namespace cvx{

template <class T>
class ConstantExpression: public FunctionExpression<ConstantExpression<T>>
{
public:
	template <class ... Args>
	ConstantExpression(Args && ... args):
		value_(std::forward<Args>(args) ... )
	{

	}
	const T & evaluate() const
	{
		return value_;
	}
	template <class ... Args>
	auto diff(Args && ... args) const
	{
		return ConstantExpression<T>(0);
	}
private:
	const T value_;
};

} /* namespace cvx */


#endif /* EXPRESSIONS_CONSTANTEXPRESSION_H_ */
