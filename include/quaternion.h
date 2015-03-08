#ifndef QUATERNION_DOT_H
#define QUATERNION_DOT_H
#include "vec4.h"
#include "gfxmath_config.h"
/*! 
 * \file 
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
	 * \class	Quaternion
	 *
	 * \brief	The quaternion class.
	 *
	 * \date	2/21/2015
	 *
	 * \remarks A specialized Vec4 used to contain quaternion-based rotation data.
	 * 
	 * \sa	Vec4
	 */
	ALIGNED_CLASS(16) Quaternion : public Vec4
	{
	public:
		/*!
		 * \brief	Constructs a Quaternion with all four components being initialized to 0.0f.
		 *
		 * \date	2/22/2015
		 */
		Quaternion();

		/*!
		 * \brief	Constructor taking a single float argument that will be copied into all four component values.
		 *
		 * \date	2/22/2015
		 *
		 * \param	xyzw	The value that will be copied into the x, y, z, and w components.
		 */
		Quaternion(float xyzw);

		/*!
		 * \brief	Constructor taking four separate component values to use for the respective coordinate components of this Quaternion.
		 *
		 * \date	2/22/2015
		 *
		 * \param	x	The x-coordinate component value of this Quaternion.
		 * \param	y	The y-coordinate component value  of this Quaternion.
		 * \param	z	The z-coordinate component value  of this Quaternion.
		 * \param	w	The w-coordinate component value  of this Quaternion.
		 */
		Quaternion(float x, float y, float z, float w);

		/*!
		 * \brief	Constructor that takes two Vec2 arguments and copies their values into the first and second pair of components, respectively.
		 *
		 * \date	2/22/2015
		 *
		 * \param	xy	The Vec2 that will contribute its components to the x and y-coordinate components of this Quaternion.
		 * \param	zw	The Vec2 that will contribute its components to the z and w-coordinate components of this Quaternion.
		 */
		Quaternion(const Vec2& xy, const Vec2& zw);

		/*!
		 * \brief	Constructor taking a Vec2 for the x and y-component values, then two separate floats for the z and w-coordinate component values.
		 *
		 * \date	2/22/2015
		 *
		 * \param	xy	The Vec2 that will contribute its components to the x and y-coordinate components of this Quaternion.
		 * \param	z 	The z-coordinate component value of this Quaternion.
		 * \param	w 	The w-coordinate component value of this Quaternion.
		 */
		Quaternion(const Vec2& xy, float z, float w);

		/*!
		 * \brief	Constructor taking a single float for the x-coordinate component, followed by a Vec2 for the y and z-coordinate component values, then another floats for the w-coordinate component.
		 *
		 * \date	2/22/2015
		 *
		 * \param	x 	The x-coordinate component value of this Quaternion.
		 * \param	yz	The Vec2 that will contribute its components to the y and z-coordinate components of this Quaternion.
		 * \param	w 	The w-coordinate component value of this Quaternion.
		 */
		Quaternion(float x, const Vec2& yz, float w);

		/*!
		 * \brief	Constructor taking two float values for the x and y-coordinate component values, followed by a Vec2 for the z and w-coordinate component values.
		 *
		 * \date	2/22/2015
		 *
		 * \param	x 	The x-coordinate component value of this Quaternion.
		 * \param	y 	The y-coordinate component value of this Quaternion.
		 * \param	zw	The Vec2 that will contribute its components to the z and w-coordinate components of this Quaternion.
		 */
		Quaternion(float x, float y, const Vec2& zw);

		/*!
		 * \brief	Constructor taking a single Vec3 for the x, y, and z-coordinate component values, followed by a single float for the w-coordinate component value.
		 *
		 * \date	2/22/2015
		 *
		 * \param	xyz	The Vec3 that will contribute its components to the x, y and z-coordinate components of this Quaternion.
		 * \param	w  	The w-coordinate component value of this Quaternion.
		 */
		Quaternion(const Vec3& xyz, float w);

		/*!
		 * \brief	Constructor taking a single float for the w-coordinate component value, followed by a single Vec3 for the x, y, and z-coordinate component values.
		 *
		 * \date	2/22/2015
		 *
		 * \param	x  	The x-coordinate component value of this Quaternion.
		 * \param	yzw	The Vec3 that will contribute its components to the y, z and w-coordinate components of this Quaternion.
		 */
		Quaternion(float x, const Vec3& yzw);

		

		static Quaternion Identity();  /*!< The identity quaternion */
	};

	/*! @} */
}
#endif