#ifndef VEC4_DOT_H
#define VEC4_DOT_H

#include <array>
#include <iostream>
#include "sisd_defns.h"

/*! 
 * \file 
 */

/*!
 * \namespace	gofxmath
 *
 * \brief	G of F of X math namespace.
 */
namespace gofxmath
{
	class Vec2;
	class Vec3;
	class Quaternion;

	/*!
	 * \ingroup SISDVecMath SISD Vector Math
	 * @{
	 */

	/*!
	 * \class Vec4
	 *
	 * \brief	A mathematical vector with 4 components.
	 */
	ALIGNED_CLASS(16) Vec4
	{
	public:
		/*!
		 * \fn	Vec4();
		 *
		 * \brief	Constructs a Vec4 with all four components being initialized to 0.0f.
		 *
		 * \date	2/22/2015
		 */
		Vec4();

		/*!
		 * \fn	Vec4(float xyzw);
		 *
		 * \brief	Constructor taking a single float argument that will be copied into all four component values.
		 *
		 * \date	2/22/2015
		 *
		 * \param	xyzw	The value that will be copied into the x, y, z, and w components.
		 */
		Vec4(float xyzw);

		/*!
		 * \fn	Vec4(float x, float y, float z, float w);
		 *
		 * \brief	Constructor taking four separate component values to use for the respective coordinate components of this Vec4.
		 *
		 * \date	2/22/2015
		 *
		 * \param	x	The x-coordinate component value of this Vec4.
		 * \param	y	The y-coordinate component value  of this Vec4.
		 * \param	z	The z-coordinate component value  of this Vec4.
		 * \param	w	The w-coordinate component value  of this Vec4.
		 */
		Vec4(float x, float y, float z, float w);

		/*!
		 * \fn	Vec4(const Vec2& xy, const Vec2& zw);
		 *
		 * \brief	Constructor that takes two Vec2 arguments and copies their values into the first and second pair of components, respectively.
		 *
		 * \date	2/22/2015
		 *
		 * \param	xy	The Vec2 that will contribute its components to the x and y-coordinate components of this Vec4.
		 * \param	zw	The Vec2 that will contribute its components to the z and w-coordinate components of this Vec4.
		 */
		Vec4(const Vec2& xy, const Vec2& zw);

		/*!
		 * \fn	Vec4(const Vec2& xy, float z, float w);
		 *
		 * \brief	Constructor taking a Vec2 for the x and y-component values, then two separate floats for the z and w-coordinate component values.
		 *
		 * \date	2/22/2015
		 *
		 * \param	xy	The Vec2 that will contribute its components to the x and y-coordinate components of this Vec4.
		 * \param	z 	The z-coordinate component value of this Vec4.
		 * \param	w 	The w-coordinate component value of this Vec4.
		 */
		Vec4(const Vec2& xy, float z, float w);

		/*!
		 * \fn	Vec4(float x, const Vec2& yz, float w);
		 *
		 * \brief	Constructor taking a single float for the x-coordinate component, followed by a Vec2 for the y and z-coordinate component values, then another floats for the w-coordinate component.
		 *
		 * \date	2/22/2015
		 *
		 * \param	x 	The x-coordinate component value of this Vec4.
		 * \param	yz	The Vec2 that will contribute its components to the y and z-coordinate components of this Vec4.
		 * \param	w 	The w-coordinate component value of this Vec4.
		 */
		Vec4(float x, const Vec2& yz, float w);

		/*!
		 * \fn	Vec4(float x, float y, const Vec2& zw);
		 *
		 * \brief	Constructor taking two float values for the x and y-coordinate component values, followed by a Vec2 for the z and w-coordinate component values.
		 *
		 * \date	2/22/2015
		 *
		 * \param	x 	The x-coordinate component value of this Vec4.
		 * \param	y 	The y-coordinate component value of this Vec4.
		 * \param	zw	The Vec2 that will contribute its components to the z and w-coordinate components of this Vec4.
		 */
		Vec4(float x, float y, const Vec2& zw);

		/*!
		 * \fn	Vec4(const Vec3& xyz, float w);
		 *
		 * \brief	Constructor taking a single Vec3 for the x, y, and z-coordinate component values, followed by a single float for the w-coordinate component value.
		 *
		 * \date	2/22/2015
		 *
		 * \param	xyz	The Vec3 that will contribute its components to the x, y and z-coordinate components of this Vec4.
		 * \param	w  	The w-coordinate component value of this Vec4.
		 */
		Vec4(const Vec3& xyz, float w);

		/*!
		 * \fn	Vec4(float x, const Vec3& yzw);
		 *
		 * \brief	Constructor taking a single float for the w-coordinate component value, followed by a single Vec3 for the x, y, and z-coordinate component values.
		 *
		 * \date	2/22/2015
		 *
		 * \param	x  	The x-coordinate component value of this Vec4.
		 * \param	yzw	The Vec3 that will contribute its components to the y, z and w-coordinate components of this Vec4.
		 */
		Vec4(float x, const Vec3& yzw);

		/*!
		 * \fn	friend std::ostream &operator<< (std::ostream& stream, const Vec4& vec);
		 *
		 * \brief	A function that writes the given 4D vector to the given output stream.
		 *
		 * \date	2/22/2015
		 *
		 * \param [in,out]	stream	The output stream to be written to.
		 * \param	vec			  	The Vec4 to write to the stream.
		 *
		 * \return	Writes the value of the given Vec4 to the given output stream.
		 */
		friend std::ostream &operator << (std::ostream& stream, const Vec4& vec);

		/*!
		 * \fn	friend std::istream &operator>> (std::istream& stream, Vec4& vec);
		 *
		 * \brief	A function that reads in the a 4D vector from the given input stream.
		 *
		 * \date	2/22/2015
		 *
		 * \param [in,out]	stream	The input stream to be read from.
		 * \param [in,out]	vec   	The Vec4 to read values into from the stream.
		 *
		 * \return	Reads the value of the given input stream to the given Vec4.
		 */
		friend std::istream &operator >> (std::istream& stream, Vec4& vec);

		/*!
		 * \fn	friend bool operator==(const Vec4& left, const Vec4& right);
		 *
		 * \brief	Equality operator.
		 *
		 * \date	2/22/2015
		 *
		 * \param	left 	The first instance to compare.
		 * \param	right	The second instance to compare.
		 *
		 * \return	true if the parameters are considered equivalent.
		 */
		friend bool operator==(const Vec4& left, const Vec4& right);

		/*!
		 * \fn	friend bool operator!=(const Vec4& left, const Vec4& right);
		 *
		 * \brief	Inequality operator.
		 *
		 * \date	2/22/2015
		 *
		 * \param	left 	The first instance to compare.
		 * \param	right	The second instance to compare.
		 *
		 * \return	true if the parameters are not considered equivalent.
		 */
		friend bool operator!=(const Vec4& left, const Vec4& right);

		/*!
		 * \fn	explicit operator Vec2() const;
		 *
		 * \brief	Explicit cast that converts the given  to a Vec2.
		 *
		 * \date	2/22/2015
		 *
		 * \return	The result of the operation.
		 */
        explicit operator Vec2() const;

		/*!
		 * \fn	explicit operator Vec3() const;
		 *
		 * \brief	Explicit cast that converts the given  to a Vec3.
		 *
		 * \date	2/22/2015
		 *
		 * \return	The result of the operation.
		 */
        explicit operator Vec3() const;

		/*!
		 * \fn	explicit operator Quaternion() const;
		 *
		 * \brief	Explicit cast that converts the given  to a Quaternion.
		 *
		 * \date	2/22/2015
		 *
		 * \return	The result of the operation.
		 */
        explicit operator Quaternion() const;

		//! \cond 
		union
		{
		//! \endcond

		public:
			float vals[4];  /*!< The 4 components of the Vec4
							 *
							 *	 \remarks Points to the same values as the x, y,
							 *			  z, and w components (at indices 0, 1,
							 *			  2, and 3, respectively).
							 */

			//! \cond 
			struct {
			//! \endcond

				float x;	/*!< The x-coordinate 
							 *
							 * \remarks Equivalent to vals[0].
							 */

				float y;	/*!< The y-coordinate 
							 *
							 * \remarks Equivalent to vals[1].
							 */

				float z;	/*!< The z-coordinate 
							 *
							 * \remarks Equivalent to vals[2].
							 */

				float w;	/*!< The w-coordinate 
							 *
							 * \remarks Equivalent to vals[3].
							 */

			//! \cond 
			};
		};
		//! \endcond

		static Vec4 E0();   /*!< The elementary vector with components <1 0 0 0> */
		static Vec4 E1();   /*!< The elementary vector with components <0 1 0 0> */
		static Vec4 E2();   /*!< The elementary vector with components <0 0 1 0> */
		static Vec4 E3();   /*!< The elementary vector with components <0 0 0 1> */
		static Vec4 E(int i); /*!< The array of elementary 4-component vectors */

		static Vec4 NegE0();   /*!< The negative form of the first elementary vector (takes the form <-1 0 0 0>) */
		static Vec4 NegE1();   /*!< The negative form of the second elementary vector (takes the form <0 -1 0 0>) */
		static Vec4 NegE2();   /*!< The negative form of the third elementary vector (takes the form < 0 0 -1 0>) */
		static Vec4 NegE3();   /*!< The negative form of the fourth elementary vector (takes the form <0 0 0 -1>) */
		static Vec4 NegE(int i); /*!< The array of negated elementary 4-component vectors */

		static Vec4 One();  /*!< The 4-component vector containing the values <1 1 1 1> */
		static Vec4 NegOne();  /*!< The 4-component vector containing the values <-1 -1 -1 -1> */

		static Vec4 Zero(); /*!< The 4-component zero vector (takes the form <0 0 0 0> */
	};

	/*! @} */
}
#endif // VEC4_DOT_H
