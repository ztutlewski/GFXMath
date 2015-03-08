#ifndef VEC_MATH_DOT_H
#define VEC_MATH_DOT_H

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "quaternion.h"
#include "scalar_math.h"
#include "gfxmath_config.h"
/*! 
 * \file 
 */

/*!
 * \defgroup SISDVecMath SISD Vector Math
 */

/*!
 * \namespace	gfxmath
 *
 * \brief	G of F of X math namespace.
 */

namespace gfxmath
{
	/*!
	 * \ingroup SISDVecMath
	 * @{
	 */

	/*!
	 * \brief	Add the two given Vec2s.
	 *
	 * \date	2/22/2015
	 *
	 * \param	first 	The first Vec2 in the sum.
	 * \param	second	The second Vec2 in the sum.
	 *
	 * \return	The Vec2 representing the sum of the two given Vec2s' components.
	 *
	 * \relatedalso gfxmath::Vec2
	 */
	Vec2 Vec2Add(const Vec2& first, const Vec2& second);

	/*!
	 * \brief	Add the two given Vec3s.
	 *
	 * \date	2/22/2015
	 *
	 * \param	first 	The first Vec3 in the sum.
	 * \param	second	The second Vec3 in the sum.
	 *
	 * \return	The Vec3 representing the sum of the two given Vec3s' components.
	 *
	 * \relatedalso gfxmath::Vec3
	 */
	Vec3 Vec3Add(const Vec3& first, const Vec3& second);

	/*!
	 * \brief	Add the two given Vec4s.
	 *
	 * \date	2/22/2015
	 *
	 * \param	first 	The first Vec4 in the sum.
	 * \param	second	The second Vec4 in the sum.
	 *
	 * \return	The Vec4 representing the sum of the two given Vec4s' components.
	 *
	 * \relatedalso gfxmath::Vec4
	 */
	Vec4 Vec4Add(const Vec4& first, const Vec4& second);

	/*!
	 * \brief	Subtract the two given Vec2s.
	 *
	 * \date	2/22/2015
	 *
	 * \param	first 	The first Vec2 in the subtraction.
	 * \param	second	The second Vec2 in the subtraction.
	 *
	 * \return	The Vec2 representing the difference of the two given Vec2s' coponents.
	 *
	 * \relatedalso gfxmath::Vec2
	 */
	Vec2 Vec2Sub(const Vec2& first, const Vec2& second);

	/*!
	 * \brief	Subtract the two given Vec3s.
	 *
	 * \date	2/22/2015
	 *
	 * \param	first 	The first Vec3 in the subtraction.
	 * \param	second	The second Vec3 in the subtraction.
	 *
	 * \return	The Vec3 representing the difference of the two given Vec3s' coponents.
	 *
	 * \relatedalso gfxmath::Vec3
	 */
	Vec3 Vec3Sub(const Vec3& first, const Vec3& second);

	/*!
	 * \brief	Subtract the two given Vec4s.
	 *
	 * \date	2/22/2015
	 *
	 * \param	first 	The first Vec4 in the subtraction.
	 * \param	second	The second Vec4 in the subtraction.
	 *
	 * \return	The Vec4 representing the difference of the two given Vec4s' coponents.
	 *
	 * \relatedalso gfxmath::Vec4
	 */
	Vec4 Vec4Sub(const Vec4& first, const Vec4& second);

	/*!
	 * \brief	Vec2 dot product.
	 *
	 * \date	2/22/2015
	 *
	 * \param	first 	The first Vec2 in the dot product.
	 * \param	second	The second Vec2 in the dot product.
	 *
	 * \return	The scalar value resulting from the dot product of the two Vec2s' components.
	 *
	 * \relatedalso gfxmath::Vec2
	 */
	float Vec2Dot(const Vec2& first, const Vec2& second);

	/*!
	 * \brief	Vec3 dot product.
	 *
	 * \date	2/22/2015
	 *
	 * \param	first 	The first Vec3 in the dot product.
	 * \param	second	The second Vec3 in the dot product.
	 *
	 * \return	The scalar value resulting from the dot product of the two Vec3s' components.
	 *
	 * \relatedalso gfxmath::Vec3
	 */
	float Vec3Dot(const Vec3& first, const Vec3& second);

	/*!
	 * \brief	Vec4 dot product.
	 *
	 * \date	2/22/2015
	 *
	 * \param	first 	The first Vec4 in the dot product.
	 * \param	second	The second Vec4 in the dot product.
	 *
	 * \return	The scalar value resulting from the dot product of the two Vec4s' components.
	 *
	 * \relatedalso gfxmath::Vec4
	 */
	float Vec4Dot(const Vec4& first, const Vec4& second);

	/*!
	 * \brief	Multiply the components of the given Vec2 by the given scalar.
	 *
	 * \date	2/22/2015
	 *
	 * \param	vec   	The Vec2 to multiply.
	 * \param	factor	The scalar to multiply by.
	 *
	 * \return	The scaled Vec2.
	 *
	 * \relatedalso gfxmath::Vec2
	 */
	Vec2 Vec2MulScalar(const Vec2& vec, float factor);

	/*!
	 * \brief	Multiply the components of the given Vec3 by the given scalar.
	 *
	 * \date	2/22/2015
	 *
	 * \param	vec   	The Vec3 to multiply.
	 * \param	factor	The scalar to multiply by.
	 *
	 * \return	The scaled Vec3.
	 *
	 * \relatedalso gfxmath::Vec3
	 */
	Vec3 Vec3MulScalar(const Vec3& vec, float factor);

	/*!
	 * \brief	Multiply the components of the given Vec4 by the given scalar.
	 *
	 * \date	2/22/2015
	 *
	 * \param	vec   	The Vec4 to multiply.
	 * \param	factor	The scalar to multiply by.
	 *
	 * \return	The scaled Vec4.
	 *
	 * \relatedalso gfxmath::Vec4
	 */
	Vec4 Vec4MulScalar(const Vec4& vec, float factor);

	/*!
	 * \brief	Divide the components of the given Vec2 by the given scalar.
	 *
	 * \date	2/22/2015
	 *
	 * \param	vec	   	The Vec2 to divide.
	 * \param	divisor	The scalar to divide by.
	 *
	 * \return	The scaled Vec2
	 *
	 * \relatedalso gfxmath::Vec2
	 */
	Vec2 Vec2DivScalar(const Vec2& vec, float divisor);

	/*!
	 * \brief	Divide the components of the given Vec3 by the given scalar.
	 *
	 * \date	2/22/2015
	 *
	 * \param	vec	   	The Vec3 to divide.
	 * \param	divisor	The scalar to divide by.
	 *
	 * \return	The scaled Vec3
	 *
	 * \relatedalso gfxmath::Vec3
	 */
	Vec3 Vec3DivScalar(const Vec3& vec, float divisor);

	/*!
	 * \brief	Divide the components of the given Vec4 by the given scalar.
	 *
	 * \date	2/22/2015
	 *
	 * \param	vec	   	The Vec4 to divide.
	 * \param	divisor	The scalar to divide by.
	 *
	 * \return	The scaled Vec4
	 *
	 * \relatedalso gfxmath::Vec4
	 */
	Vec4 Vec4DivScalar(const Vec4& vec, float divisor);

	/*!
	 * \brief	Normalize the given Vec2.
	 *
	 * \date	2/22/2015
	 *
	 * \param	vec	The Vec2 to normalize.
	 *
	 *
	 * \return	The normalized form of the given Vec2.
	 *
	 * \remarks Scales the components of the Vec2 such that its
	 *			length is 1 (unit length).
	 *
	 * \relatedalso gfxmath::Vec2
	 */
	Vec2 Vec2Normalize(const Vec2& vec);

	/*!
	 * \brief	Normalize the given Vec3.
	 *
	 * \date	2/22/2015
	 *
	 * \param	vec	The Vec3 to normalize.
	 *
	 *
	 * \return	The normalized form of the given Vec3.
	 *
	 * \remarks Scales the components of the Vec3 such that its
	 *			length is 1 (unit length).
	 *
	 * \relatedalso gfxmath::Vec3
	 */
	Vec3 Vec3Normalize(const Vec3& vec);

	/*!
	 * \brief	Normalize the given Vec4.
	 *
	 * \date	2/22/2015
	 *
	 * \param	vec	The Vec4 to normalize.
	 *
	 *
	 * \return	The normalized form of the given Vec4.
	 *
	 * \remarks Scales the components of the Vec4 such that its
	 *			length is 1 (unit length).
	 *
	 * \relatedalso gfxmath::Vec4
	 */
	Vec4 Vec4Normalize(const Vec4& vec);

	/*!
	 * \brief	Normalize the given quaternion.
	 *
	 * \date	2/22/2015
	 *
	 * \param	quat	The quaternion.
	 *
	 * \return	A Quaternion.
	 *
	 * \remarks Scales the components of the Quaternion such that its
	 *			length is 1 (unit length).
	 *
	 * \relatedalso gfxmath::Quaternion
	 */
	Quaternion QuaternionNormalize(const Quaternion& quat);

	/*!
	 * \brief	Negate the given Vec2 components.
	 *
	 * \date	2/22/2015
	 *
	 * \param	vec	The Vec2 being negated.
	 *
	 * \return	The Vec2 with components that are of opposite sign of the given Vec2.
	 *
	 * \relatedalso gfxmath::Vec2
	 */
	Vec2 Vec2Negate(const Vec2& vec);

	/*!
	 * \brief	Negate the given Vec3 components.
	 *
	 * \date	2/22/2015
	 *
	 * \param	vec	The Vec3 being negated.
	 *
	 * \return	The Vec3 with components that are of opposite sign of the given Vec3.
	 *
	 * \relatedalso gfxmath::Vec3
	 */
	Vec3 Vec3Negate(const Vec3& vec);

	/*!
	 * \brief	Negate the given Vec4 components.
	 *
	 * \date	2/22/2015
	 *
	 * \param	vec	The Vec4 being negated.
	 *
	 * \return	The Vec4 with components that are of opposite sign of the given Vec4.
	 *
	 * \relatedalso gfxmath::Vec4
	 */
	Vec4 Vec4Negate(const Vec4& vec);

	/*!
	 * \brief	Determines whether the two Vec2s are approximately equal, based on the given Precision template argument (defaults to HIGH precision).
	 *
	 * \date	2/22/2015
	 *
	 * \tparam	precision	Type of the precision.
	 * \param	first 	The first Vec2 in the comparison.
	 * \param	second	The second Vec2 in the comparison.
	 *
	 * \return  true if the x and y components of the two given Vec2s have values that are within the FloatPrecision accuracy definition of one another, otherwise false.
	 *
	 * \relatedalso gfxmath::Vec2
	 */
	template<FloatPrecision precision = FloatPrecision::HIGH>
	inline bool Vec2ApproxEqual(const Vec2& first, const Vec2& second)
	{
		return ApproxEqual<precision>(first.x, second.x) && ApproxEqual<precision>(first.y, second.y);
	}

	/*!
	 * \brief	Determines whether the two Vec3s are approximately equal, based on the given Precision template argument (defaults to HIGH precision).
	 *
	 * \date	2/22/2015
	 *
	 * \tparam	precision	Type of the precision.
	 * \param	first 	The first Vec3 in the comparison.
	 * \param	second	The second Vec3 in the comparison.
	 *
	 * \return  true if the x, y and z components of the two given Vec3s have values that are within the FloatPrecision accuracy definition of one another, otherwise false.
	 *
	 * \relatedalso gfxmath::Vec3
	 */
	template<FloatPrecision precision = FloatPrecision::HIGH>
	inline bool Vec3ApproxEqual(const Vec3& first, const Vec3& second)
	{
		return ApproxEqual<precision>(first.x, second.x) && ApproxEqual<precision>(first.y, second.y) && ApproxEqual<precision>(first.z, second.z);
	}

	/*!
	 * \brief	Determines whether the two Vec4s are approximately equal, based on the given Precision template argument (defaults to HIGH precision).
	 *
	 * \date	2/22/2015
	 *
	 * \tparam	precision	Type of the precision.
	 * \param	first 	The first Vec4 in the comparison.
	 * \param	second	The second Vec4 in the comparison.
	 *
	 * \return  true if the x, y, z and w components of the two given Vec4s have values that are within the FloatPrecision accuracy definition of one another, otherwise false.
	 *
	 * \relatedalso gfxmath::Vec4
	 */
	template<FloatPrecision precision = FloatPrecision::HIGH>
	inline bool Vec4ApproxEqual(const Vec4& first, const Vec4& second)
	{
		return ApproxEqual<precision>(first.x, second.x) && ApproxEqual<precision>(first.y, second.y) && ApproxEqual<precision>(first.z, second.z) && ApproxEqual<precision>(first.w, second.w);
	}

	/*!
	 * \brief	Vector 2 has a NaN component value.
	 *
	 * \date	2/22/2015
	 *
	 * \param	vec	The vector.
	 *
	 * \return	true if the given Vec2 has at least one NaN value, otherwise false.
	 *
	 * \relatedalso gfxmath::Vec2
	 */
	bool Vec2HasNaN(const Vec2& vec);

	/*!
	 * \brief	Vector 2 has a NaN component value.
	 *
	 * \date	2/22/2015
	 *
	 * \param	vec	The vector.
	 *
	 * \return	true if the given Vec3 has at least one NaN value, otherwise false.
	 *
	 * \relatedalso gfxmath::Vec3
	 */
	bool Vec3HasNaN(const Vec3& vec);

	/*!
	 * \brief	Vector 2 has a NaN component value.
	 *
	 * \date	2/22/2015
	 *
	 * \param	vec	The vector.
	 *
	 * \return	true if the given Vec4 has at least one NaN value, otherwise false.
	 *
	 * \relatedalso gfxmath::Vec4
	 */
	bool Vec4HasNaN(const Vec4& vec);

	/*!
	 * \brief	Determines whether or not the given Vec2 has an infinite value component.
	 *
	 * \date	2/22/2015
	 *
	 * \param	vec	The given Vec2 to check for infinite values.
	 *
	 * \return	true if the given Vec2 has at least one infinite value in its components, otherwise false.
	 *
	 * \relatedalso gfxmath::Vec2
	 */
	bool Vec2HasInfinite(const Vec2& vec);

	/*!
	 * \brief	Determines whether or not the given Vec3 has an infinite value component.
	 *
	 * \date	2/22/2015
	 *
	 * \param	vec	The given Vec3 to check for infinite values.
	 *
	 * \return	true if the given Vec3 has at least one infinite value in its components, otherwise false.
	 *
	 * \relatedalso gfxmath::Vec3
	 */
	bool Vec3HasInfinite(const Vec3& vec);

	/*!
	 * \brief	Determines whether or not the given Vec4 has an infinite value component.
	 *
	 * \date	2/22/2015
	 *
	 * \param	vec	The given Vec4 to check for infinite values.
	 *
	 * \return	true if the given Vec4 has at least one infinite value in its components, otherwise false.
	 *
	 * \relatedalso gfxmath::Vec4
	 */
	bool Vec4HasInfinite(const Vec4& vec);

	/*!
	 * \brief	The cross product of the two given Vec3s.
	 *
	 * \date	2/22/2015
	 *
	 * \param	first 	The first Vec3 in the cross product.
	 * \param	second	The second Vec3 in the cross product.
	 *
	 * \return	The cross produc of the two given Vec3s.
	 *
	 * \relatedalso gfxmath::Vec3
	 */
	Vec3 Vec3Cross(const Vec3& first, const Vec3& second);

	/*!
	 * \brief	Multiply the two given Quaternions
	 *
	 * \date	2/22/2015
	 *
	 * \param	q0	The first quaternion in the multiplication.
	 * \param	q1	The second quaternion in the multiplication.
	 *
	 * \return	The product of the two given quaternions.
	 *
	 * \relatedalso gfxmath::Quaternion
	 */
	Quaternion QuaternionMultiply(const Quaternion& q0, const Quaternion& q1);

	/*!
	 * \brief	Linearly interpolate the given quaternions for time t.
	 *
	 * \date	2/22/2015
	 *
	 * \param	qStart	The start quaternion.
	 * \param	qEnd  	The end quaternion.
	 * \param	t	  	The "time" between the two quaternions.
	 *
	 * \return	The quaternion lerped between qStart and qEnd at time 't'.
	 *
	 * \relatedalso gfxmath::Quaternion
	 */
	Quaternion QuaternionLerp(const Quaternion& qStart, const Quaternion& qEnd, float t);

	/*!
	 * \brief	Produces a quaternion representation of the given axis-angle rotation.
	 *
	 * \date	2/22/2015
	 *
	 * \param	axisVec	The axis vec.
	 * \param	angle  	The angle.
	 *
	 * \return	The quaternion representation of the given axis-angle rotation.
	 *
	 * \relatedalso gfxmath::Quaternion
	 */
	Quaternion QuaternionFromAxisAngle(const Vec3& axisVec, float angle);

	/*!
	 * \brief	Converts the given euler angles to a quaternion.
	 *
	 * \date	2/22/2015
	 *
	 * \param	angles	The angles (in radians).
	 *
	 * \return	A quaternion representing the given euler angles.
	 *
	 * \relatedalso gfxmath::Quaternion
	 */
	Quaternion QuaternionFromEuler(const Vec3& angles);

	/*! @} */
}

#endif// VEC_MATH_DOT_H