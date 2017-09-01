/*
 * FunctionTraits.h
 *
 *  Created on: Sep 1, 2017
 *      Author: tim
 */

#ifndef CVX_CPP_FUNCTIONS_FUNCTIONTRAITS_H_
#define CVX_CPP_FUNCTIONS_FUNCTIONTRAITS_H_

#include "../Expressions/Traits/ExpressionDeclarations.h"

namespace cvx{

	namespace detail
	{
		template <curvature_t FuncCurv, curvature_t ArgCurv, curvature_t ... ArgCurvs>
		struct CurvatureFold
		{
			//static constexpr const curvature_t value =
		};
	} /* namespace detail */
	template <template <class...> class FunctionName>
	struct FunctionTraits
	{
		static constexpr const curvature_t curvature = CURV_UNKNOWN;
		static constexpr const monotonicity_t monotonicity = MONO_NONMONOTONIC;
	};
	template <>
	struct FunctionTraits<ExpFunction>
	{
		static constexpr const curvature_t curvature = CURV_CONVEX;
		static constexpr const monotonicity_t monotonicity = MONO_NONDECREASING;
	};
	template <>
	struct FunctionTraits<PowFunction>
	{
		static constexpr const curvature_t curvature = CURV_UNKNOWN;
		static constexpr const monotonicity_t monotonicity = MONO_NONMONOTONIC;
	};
	template <>
	struct FunctionTraits<LogFunction>
	{
		static constexpr const curvature_t curvature = CURV_CONCAVE;
		static constexpr const monotonicity_t monotonicity = MONO_NONDECREASING;
	};

} /* namespace cvx */

#endif /* CVX_CPP_FUNCTIONS_FUNCTIONTRAITS_H_ */
