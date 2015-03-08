#ifndef SCALAR_MATH_DOT_H
#define SCALAR_MATH_DOT_H
#include "math_defs.h"
#include <stdint.h>
#include "gfxmath_config.h"
/*! \file 
 */

/*!
 * \namespace	gfxmath
 *
 * \brief	G of F of X math namespace.
 */
namespace gfxmath
{
	/*!
	 * \defgroup SISDScalarMath SISD Scalar Math
	 * @{
	 */

	/*!
	 * \brief	Normalize the angle to the range of [-PI,PI).
	 *
	 * \date	2/21/2015
	 *
	 * \param	angle	The angle to normalize.
	 *
	 * \return	The angle representing the same rotation as the
	 *			originally passed angle, but contained in the range
	 *			%%[-\\pi,\\pi)%%
	 *
	 * \remarks Uses additive range reduction by %%2\\pi%% to replace
	 *			the value within the proper range.
	 */
	inline float NormalizeAngle(float angle)
	{
		int shiftedAndScaled = (int)((angle + F_PI) * F_1_2PI + Epsilon());
		return angle - ((float)shiftedAndScaled * F_2PI);
	}

	/*!
	 * \brief	Fast sine approximation.
	 *
	 * \date	2/21/2015
	 *
	 * \param	angle	The angle to approximate the sine for.
	 *
	 * \return	An approximation of the sine of the given angle.
	 */
	inline float FastSinApprox(float angle)
	{
		float coef = angle < 0 ? F_4_PI2 : -F_4_PI2;		
		float sin = (F_4_PI + angle * coef) * angle;
		
		float absSin = sin < 0 ? -sin : sin;
		return sin * (0.775f + 0.225f * absSin);
	}

	/*!
	 * \brief	Fast cosine approximation.
	 *
	 * \date	2/21/2015
	 *
	 * \param	angle	The angle for which to approximate the cosine.
	 *
	 * \return	An approximation of the cosine of the given angle.
	 */
	inline float FastCosApprox(float angle)
	{
		angle += angle > F_PI_2 ? -F_3PI_2 : F_PI_2;
		return FastSinApprox(angle);
	}

	/*!
	 * \brief	Fast tangent approximation.
	 *
	 * \date	2/21/2015
	 *
	 * \param	angle	The angle for which to approximate the tangent.
	 *
	 * \return	An approximation of the tangent of the given angle.
	 */
	inline float FastTanApprox(float angle)
	{
		return  FastSinApprox(angle) / FastCosApprox(angle);
	}

	/*!
	 * \brief	Fast cotangent approximation.
	 *
	 * \date	2/21/2015
	 *
	 * \param	angle	The angle to calculate the cotangent.
	 *
	 * \return	An approximation of the cotangent of the given angle.
	 */
	inline float FastCotApprox(float angle)
	{
		return FastCosApprox(angle) / FastSinApprox(angle);
	}

	/*!
	 * \brief	Sine Approximation
	 *
	 * \date	2/21/2015
	 *
	 * \tparam	precisionLevel	The precision level to use for the approximation.
	 * \param	angle	The angle for which to approximate the sine.
	 *
	 * \return	The approximation of the sine of the given angle.
	 *
	 * \sa FloatPrecision
	 */
	template<FloatPrecision precisionLevel = FloatPrecision::HIGH>
	inline float SinApprox(float angle)
	{
		static const size_t PRECISION = TrigPrecisionValue<precisionLevel>();

		float norm = NormalizeAngle(angle - F_PI_2);
		float normSqr = norm * norm;

		float sinAngle = normSqr * CosCoef(PRECISION);

		for (size_t i = PRECISION - 1; i-- > 0;)
		{
			sinAngle += CosCoef(i);

			sinAngle *= normSqr;
		}

		sinAngle = (sinAngle + 1.0f);

		return sinAngle;
	}

	/*!
	 * \brief	Cosine approximation.
	 *
	 * \date	2/21/2015
	 *
	 * \tparam	precisionLevel	The precision level to use for the approximation.
	 * \param	angle	The angle for which to approximate the cosine.
	 *
	 * \return	The approximation of the cosine of the given angle.
	 *
	 * \sa FloatPrecision
	 */
	template<FloatPrecision precisionLevel = FloatPrecision::HIGH>
	inline float CosApprox(float angle)
	{
		static const size_t PRECISION = TrigPrecisionValue<precisionLevel>();

		float norm = NormalizeAngle(angle);
		float normSqr = norm * norm;

		float cosAngle = normSqr * CosCoef(PRECISION);

		for (size_t i = PRECISION - 1; i-- > 0;)
		{
			cosAngle += CosCoef(i);

			cosAngle *= normSqr;
		}
		cosAngle = (cosAngle + 1.0f);

		return cosAngle;
	}

	/*!
	 * \brief	Tangent approximation
	 *
	 * \date	2/21/2015
	 *
	 * \tparam	precisionLevel	The precision level to use for the approximation.
	 * \param	angle	The angle for which to approximate the tangent.
	 *
	 * \return	The approximation of the tangent of the given angle.
	 *
	 * \sa FloatPrecision
	 */
	template<FloatPrecision precisionLevel = FloatPrecision::HIGH>
	inline float TanApprox(float angle)
	{
		static const size_t PRECISION = TrigPrecisionValue<precisionLevel>();

		float norm = NormalizeAngle(angle);
		float normSqr = norm * norm;

		float sinAngle = normSqr * SinCoef(PRECISION);
		float cosAngle = normSqr * CosCoef(PRECISION);

		for (size_t i = PRECISION - 1; i-- > 0;)
		{
			sinAngle += SinCoef(i);
			cosAngle += CosCoef(i);

			sinAngle *= normSqr;
			cosAngle *= normSqr;
		}

		sinAngle = (sinAngle + 1.0f) * norm;
		cosAngle = (cosAngle + 1.0f);

		return sinAngle / cosAngle;
	}

	/*!
	 * \brief	Cotangent Approximation
	 *
	 * \date	2/21/2015
	 *
	 * \tparam	precisionLevel	The precision level to use for the approximation.
	 * \param	angle	The angle for which to approximate the cotangent.
	 *
	 * \return	The approximation of the cotangent of the given angle.
	 * 
	 * \sa FloatPrecision
	 */
	template<FloatPrecision precisionLevel = FloatPrecision::HIGH>
	inline float CotApprox(float angle)
	{
		static const size_t PRECISION = TrigPrecisionValue<precisionLevel>();

		float norm = NormalizeAngle(angle);
		float normSqr = norm * norm;

		float sinAngle = normSqr * SinCoef(PRECISION);
		float cosAngle = normSqr * CosCoef(PRECISION);

		for (int i = PRECISION - 1; i-- > 0;)
		{
			sinAngle += SinCoef(i);
			cosAngle += CosCoef(i);

			sinAngle *= normSqr;
			cosAngle *= normSqr;
		}

		sinAngle = (sinAngle + 1.0f) * norm;
		cosAngle = (cosAngle + 1.0f);

		return cosAngle / sinAngle;
	}

	/*!
	 * \brief	Check for approximate equality of two floating point numbers.
	 *
	 * \date	2/21/2015
	 *
	 * \tparam	precision	The precision level to use for the approximation.
	 * \param	left 	The left float.
	 * \param	right	The right float.
	 *
	 * \return	true if the two floats are within the given precision epsilon of one another, otherwise false.
	 * 
	 * \sa FloatPrecision
	 */
	template<FloatPrecision precision = FloatPrecision::HIGH>
	inline bool ApproxEqual(float left, float right)
	{
		static const float EPSILON = FloatPrecisionValue<precision>();

		float dif = left - right;

		return (dif < 0 ? -dif : dif) <= EPSILON;
	}

	/*!
	 * \brief	Check if the given float value is NaN.
	 *
	 * \date	2/21/2015
	 *
	 * \param	val	The float value to check.
	 *
	 * \return	true if the given float value is designated as
	 *			"not a number," otherwise false.
	 * 
	 * \remarks Uses the definition of NaN such that the number
	 *			is not equal to itself.
	 */
	inline bool IsNaN(float val)
	{
		return val != val;
	}

	/*!
	 * \brief	Check if the given float value is positive or negative infinity.
	 *
	 * \date	2/21/2015
	 *
	 * \param	val	The float value to check.
	 *
	 * \return	true if the given float value is positive or negative infinity, otherwise false.
	 * 
	 * \remarks Uses the definition of infinity where the number is equal to itself,
	 *			but when subtracted by itself, does not produce zero.
	 */
	inline bool IsInfinity(float val)
	{
		return (val == val) && (val - val) != 0.0f;
	}

	/*! @} */
}

#endif