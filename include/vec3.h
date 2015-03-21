#ifndef VEC3_DOT_H
#define VEC3_DOT_H

#include <array>
#include <iostream>
#include "sisd_defns.h"

/*! \file 
 */

/*!
 * \namespace	gofxmath
 *
 * \brief	G of F of X math namespace.
 */
namespace gofxmath
{
	class Vec2;
	class Vec4;


	/*!
	 * \ingroup SISDVecMath 
	 * @{
	 */

	/*!
	 * \class Vec3
	 *
	 * \brief	A mathematical vector with 3 components.
	 */
	ALIGNED_CLASS(16) Vec3
	{
	public:		

		/*!
		 * \brief	Constructs a Vec3 with all three components being initialized to 0.0f.
		 *
		 * \date	2/22/2015
		 */
		Vec3();

		/*!
		 * \brief	Constructs a Vec3 with the given x, y, and z values assigned to their respective
		 * 			components.
		 *
		 * \date	2/22/2015
		 *
		 * \param	x	The x coordinate to load into this Vec3.
		 * \param	y	The y coordinate to load into this Vec3.
		 * \param	z	The z coordinate to load into this Vec3.
		 */
		Vec3(float x, float y, float z);

		/*!
		 * \brief	Constructor.
		 *
		 * \date	2/22/2015
		 *
		 * \param	xy	The value of the x and y-coordinate components of this Vec3.
		 * \param	z 	The value to load into the z-cordinate of this Vec3.
		 */
		Vec3(const Vec2& xy, float z);

		/*!
		 * \brief	Constructor.
		 *
		 * \date	2/22/2015
		 *
		 * \param	x 	The x-coordinate of this Vec3.
		 * \param	yz	The value of the y and z-coordinate components of this Vec3.
		 */
		Vec3(float x, const Vec2& yz);

		/*!
		 * \brief	Constructor taking a single float argument that will be copied into all three component values.
		 *
		 * \date	2/22/2015
		 *
		 * \param	xyz	The value of the x, y, and z-coordinate components of this Vec3.
		 */
		Vec3(float xyz);

		/*!
		 * \brief	A function that writes the given 3D vector to the given output stream.
		 *
		 * \date	2/22/2015
		 *
		 * \param [in,out]	stream	The output stream to be written to.
		 * \param	vec			  	The Vec3 to write to the stream.
		 *
		 * \return	Writes the value of the given Vec3 to the given output stream.
		 */
		friend std::ostream &operator << (std::ostream& stream, const Vec3& vec);

		/*!
		 * \brief	A function that reads in the a 3D vector from the given input stream.
		 *
		 * \date	2/22/2015
		 *
		 * \param [in,out]	stream	The input stream to be read from.
		 * \param [in,out]	vec   	The Vec3 to read values into from the stream.
		 *
		 * \return	Reads the value of the given input stream to the given Vec3.
		 */
		friend std::istream &operator >> (std::istream& stream, Vec3& vec);

		/*!
		 * \brief	Equality operator.
		 *
		 * \date	2/22/2015
		 *
		 * \param	left 	The first instance to compare.
		 * \param	right	The second instance to compare.
		 *
		 * \return	true if the parameters are considered equivalent.
		 */
		friend bool operator==(const Vec3& left, const Vec3& right);

		/*!
		 * \brief	Inequality operator.
		 *
		 * \date	2/22/2015
		 *
		 * \param	left 	The first instance to compare.
		 * \param	right	The second instance to compare.
		 *
		 * \return	true if the parameters are not considered equivalent.
		 */
		friend bool operator!=(const Vec3& left, const Vec3& right);

		/*!
		 * \brief	Explicit cast that converts the given Vec3 to a Vec2.
		 *
		 * \date	2/22/2015
		 *
		 * \return	The result of the operation.
		 */
		explicit operator Vec2() const;

		/*!
		 * \brief	Explicit cast that converts the given Vec3 to a Vec4.
		 *
		 * \date	2/22/2015
		 *
		 * \return	The resulting Vec4 from the cast.
		 */
		explicit operator Vec4() const;

		/*!
		 * \brief	Creates the 4-component column vector version of this Vec3.
		 * 
		 * \date	3/20/2015
		 * 
		 * \return	The resulting Vec4 representing a transformable 3D column vector.
		 * 
		 * \remarks	Sets the fourth component to 1.0f.  Otherwise identical to the
		 *			explicit cast from Vec3 to Vec4;
		 */
		Vec4 ToColVec() const;

		//! \cond 
		union {
		//! \endcond

			float vals[3];  /*!< The 3 components of the Vec3 
							 *
							 *	 \remarks Points to the same values as the x, y
							 *			  and z components (at indices 0, 1,
							 *			  and 2, respectively).
							 */

			//! \cond 
			struct {
			//! \endcond

				float x;	/*!< The x-coordinate 
							 *
							 * \remarks Equivalent to <B>vals[0]</B>.	
							 */

				float y;	/*!< The y-coordinate 
							 *
							 *	\remarks Equivalent to <B>vals[1]</B>.		 
							 */

				float z;	/*!< The z-coordinate 
							 * 
							 * \remarks Equivalent to <B>vals[2]</B>.	
							 */

			//! \cond 
			};
		};
		//! \endcond

		static Vec3 Right();	/*!< The Vec3 right direction vector*/
		static Vec3 Up();   /*!< The Vec3 up direction vector */
		static Vec3 Forward();  /*!< The forward Vec3 direction vector */
		static Vec3 Left(); /*!< The Vec3 left direction vector */
		static Vec3 Down(); /*!< The Vec3 down direction vector */
		static Vec3 Back(); /*!< The Vec3 back direction vector */

		static Vec3 One();  /*!< The Vec3 one vector (all components are 1.0f) */
		static Vec3 NegOne();  /*!< The Vec3 negative one vector (all components are -1.0f) */

		static Vec3 Zero(); /*!< The Vec3 zero vector (all components are 0.0f) */
	};

	/*! @} */
}
#endif // VEC3_DOT_H