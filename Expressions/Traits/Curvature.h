/*
 * Curvature.h
 *
 *  Created on: Sep 1, 2017
 *      Author: tim
 */

#ifndef CVX_CPP_EXPRESSIONS_TRAITS_CURVATURE_H_
#define CVX_CPP_EXPRESSIONS_TRAITS_CURVATURE_H_

#include "ExpressionDeclarations.h"

namespace cvx{




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
	template <class ... T>
	struct Curvature<ConstantExpression<T>>
	{
		static constexpr const curvature_t value = CURV_AFFINE;
	};


} /* namespace cvx */

#endif /* CVX_CPP_EXPRESSIONS_TRAITS_CURVATURE_H_ */
