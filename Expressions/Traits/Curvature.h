/*
 * Curvature.h
 *
 *  Created on: Sep 1, 2017
 *      Author: tim
 */

#ifndef CVX_CPP_EXPRESSIONS_TRAITS_CURVATURE_H_
#define CVX_CPP_EXPRESSIONS_TRAITS_CURVATURE_H_

#include "../../CVX_Declarations.h"

namespace cvx{



	static constexpr const curvature_t curv_combine(curvature_t left, curvature_t right)
	{
		if constexpr(left == CURV_AFFINE)
			return right;
		else if(right == CURV_AFFINE)
			return left;
		else if(left == right)
			return left;
		else
			return CURV_UNKNOWN;
	}
	template <class T>
	struct Curvature
	{
 		static constexpr const curvature_t value = CURV_UNKNOWN;
	};
	template <class T>
	struct Curvature<FunctionExpression<T>>
	{
		static constexpr const curvature_t value = Curvature<T>::value;
	};
	template <class T>
	struct Curvature<ConstantExpression<T>>
	{
		static constexpr const curvature_t value = CURV_AFFINE;
	};
	template <class T, class U>
	struct Curvature<AddExpression<T, U>>
	{
		static constexpr const curvature_t value = curv_combine(Curvature<T>::value, Curvature<U>::value);
	};
	template <class T, class U>
	struct Curvature<SubExpression<T, U>>
	{
		static constexpr const curvature_t value = curv_combine(Curvature<T>::value, Curvature<U>::value);
	};
	template <class T, class U>
	struct Curvature<MulExpression<ConstantExpression<T>, U>>
	{
		static constexpr const curvature_t value = Curvature<U>::value;
	};
	template <class T, class U>
	struct Curvature<MulExpression<T, ConstantExpression<U>>>
	{
		static constexpr const curvature_t value = Curvature<T>::value;
	};
	template <class T, class U>
	struct Curvature<MulExpression<ConstantExpression<T>, ConstantExpression<U>>>
	{
		static constexpr const curvature_t value = CURV_AFFINE;
	};

	template <class T, class U>
	struct Curvature<DivExpression<T, ConstantExpression<U>>>
	{
		static constexpr const curvature_t value = Curvature<T>::value;
	};

	template <class T, class U>
	struct Curvature<DivExpression<ConstantExpression<T>, ConstantExpression<U>>>
	{
		static constexpr const curvature_t value = CURV_AFFINE;
	};
} /* namespace cvx */

#endif /* CVX_CPP_EXPRESSIONS_TRAITS_CURVATURE_H_ */
