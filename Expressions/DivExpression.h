/*
 * DivExpression.h
 *
 *  Created on: Aug 25, 2017
 *      Author: tim
 */

#ifndef EXPRESSIONS_DIVEXPRESSION_H_
#define EXPRESSIONS_DIVEXPRESSION_H_

#include "Traits/ExpressionTraits.h"
namespace cvx{
template <class T, class Name, class U, ptrdiff_t M, ptrdiff_t N>
decltype(auto) derivative_of(const T & arg, const Variable<Name, U, M, N> & var);
template <class Left, class Right>
class DivExpression: public FunctionExpression<DivExpression<Left, Right>>
{
public:
	using self_type = AddExpression<Left, Right>;
	using base_type = FunctionExpression<AddExpression<Left, Right>>;
	using left_type = derived_type_t<Left>;
	using right_type = derived_type_t<Right>;
	using eval_result_type = CVX_OP_RESULT_TYPE(left_type, right_type, /);
	DivExpression(const left_type & left, const right_type & right):
		left_(left), right_(right)
	{

	}
	eval_result_type evaluate() const
	{
		return evaluate_expression(left_) / evaluate_expression(right_);
	}
	const left_type & left() const
	{
		return left_;
	}
	const right_type & right() const
	{
		return left_;
	}
	template <class Name, class T, ptrdiff_t M, ptrdiff_t N>
	decltype(auto) diff(const Variable<Name, T, M, N> & var) const
	{
		return (derivative_of(left_, var) * right_ - derivative_of(right_, var) * left_) / (right_ * right_);
	}

private:
	const left_type left_;
	const right_type right_;
};

template <class Left, class Right>
DivExpression<derived_type_t<Left>, derived_type_t<Right>> make_div_expression(Left && left, Right && right)
{
	return DivExpression<derived_type_t<Left>, derived_type_t<Right>>(forward_as_derived(left), forward_as_derived(right));
}

} /* namespace cvx */


#endif /* EXPRESSIONS_DIVEXPRESSION_H_ */
