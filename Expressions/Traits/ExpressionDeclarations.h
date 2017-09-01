/*
 * ExpressionDeclarations.h
 *
 *  Created on: Sep 1, 2017
 *      Author: tim
 */

#ifndef CVX_CPP_EXPRESSIONS_TRAITS_EXPRESSIONDECLARATIONS_H_
#define CVX_CPP_EXPRESSIONS_TRAITS_EXPRESSIONDECLARATIONS_H_

#include <type_traits>
#include <cstddef>
namespace cvx{


using curvature_t = enum curvature_
{
	CURV_UNKNOWN,
	CURV_CONSTANT,
	CURV_AFFINE,
	CURV_CONVEX,
	CURV_CONCAVE
};
using sign_t = enum sign_
{
	SIGN_UNKNOWN,
	SIGN_POSITIVE,
	SIGN_NEGATIVE

};
using monotonicity_t = enum monotonicity_
{
	MONO_NONMONOTONIC,
	MONO_NONDECREASING,
	MONO_NONINCREASING
};

namespace detail{
	template <class T>
	using remove_const_ref_t = std::remove_const_t<std::remove_reference_t<T>>;
	struct FunctionBase{};
} /* namespace detail */


template <class T, class U>
class AddExpression;

template <class T, class U>
class SubExpression;

template <class T, class U>
class DivExpression;

template <class T, class U>
class MulExpression;

template <class T>
class ConstantExpression;


template <class Func>
class FunctionExpression;

template <class T, class Arg, class ... Args>
class Function;

template <class, class, ptrdiff_t = 1, ptrdiff_t = 1>
class Variable;

template <class T>
struct IsFunction;

template <class T>
struct IsFunctionExpression;

template <class T>
struct IsVariable;





} /* namespace cvx */
#endif /* CVX_CPP_EXPRESSIONS_TRAITS_EXPRESSIONDECLARATIONS_H_ */
