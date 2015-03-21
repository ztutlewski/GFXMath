#ifndef VEC2_DOT_H
#define VEC2_DOT_H

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
	class Vec3;
	class Vec4;

	/*!
	 * \ingroup SISDVecMath 
	 * @{
	 */

	/*!
	 * \class Vec2
	 *
	 * \brief	A 2D Vector.
	 */
	ALIGNED_CLASS(16) Vec2
	{
	public:

		/*!
		 * \brief	Constructs a Vec2 with both components being initialized to 0.0f.
		 *
		 * \date	2/21/2015
		 */
		Vec2();

		/*!
		 * \brief	Constructor taking a single float argument that will be copied into both component values.
		 *
		 * \date	2/21/2015
		 *
		 * \param	xy	The value of the x and y-coordinate components of this Vec3.
		 */
		Vec2(float xy);

		/*!
		 * \brief	Constructs a Vec2 with the given x and y values assigned to their respective
		 * 			components.
		 *
		 * \date	2/21/2015
		 *
		 * \param	x	The x coordinate of the resulting Vec2.
		 * \param	y	The y coordinate of the resulting Vec2.
		 */
		Vec2(float x, float y);

		/*!
		 * \brief	A function that writes the given 2D vector to the given output stream.
		 *
		 * \date	2/22/2015
		 *
		 * \param [in,out]	stream	The output stream to be written to.
		 * \param	vec			  	The Vec2 to write to the stream.
		 *
		 * \return	Writes the value of the given Vec2 to the given output stream.
		 */
		friend std::ostream &operator<<(std::ostream& stream, const Vec2& vec);

		/*!
		 * \brief	A function that reads in the a 2D vector from the given input stream.
		 *
		 * \date	2/22/2015
		 *
		 * \param [in,out]	input	The input stream to be read from.
		 * \param [in,out]	vec  	The Vec2 to read values into from the stream.
		 *
		 * \return	Reads the value of the given input stream to the given Vec2.
		 */
		friend std::istream &operator>>(std::istream& input, Vec2& vec);

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
		friend bool operator==(const Vec2& left, const Vec2& right);

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
		friend bool operator!=(const Vec2& left, const Vec2& right);

		/*!
		 * \brief	Explicit cast that converts the given  to a Vec3.
		 *
		 * \date	2/22/2015
		 *
		 * \return	The result of the operation.
		 */
		explicit operator Vec3() const;

		/*!
		 * \brief	Explicit cast that converts the given  to a Vec4.
		 *
		 * \date	2/22/2015
		 *
		 * \return	The result of the operation.
		 */
		explicit operator Vec4() const;

		/*!
		 * \brief	Creates the 4-component column vector version of this Vec2.
		 * 
		 * \date	3/20/2015
		 * 
		 * \return	The resulting Vec4 representing a transformable 2D column vector.
		 * 
		 * \remarks	Sets the fourth component to 1.0f.  Otherwise identical to the
		 *			explicit cast from Vec2 to Vec4;
		 */
		Vec4 ToColVec() const;

		//! \cond 
		union
		{
		//! \endcond
			float vals[2];  /*!< The 2 components of the Vec2 
							 *	 \remarks Points to the same values as the x, 
							 *			  and y components (at indices 0 and
							 *			  1, respectively).
							 */
			//! \cond 
			struct {
			//! \endcond

				float x;	/*!< The x-coordinate.
							 *
							 * \remarks	Equivalent to <B>vals[0]</B>. 
							 */

				float y;	/*!< The y-coordinate.
							 *
							 * \remarks Equivalent to <B>vals[1]</B>.
							 */
			//! \cond 
			};
		};
		//! \endcond

		static Vec2 Right();	/*!< The right direction Vec2 */
		static Vec2 Up();   /*!< The up direction Vec2 */
		static Vec2 Left(); /*!< The left direction Vec2 */
		static Vec2 Down(); /*!< The down direction Vec2 */

		static Vec2 One();  /*!< The Vec2 with both components set to 1.0f */
		static Vec2 NegOne();  /*!< The Vec2 with both components set to -1.0f */

		static Vec2 Zero(); /*!< The zero Vec2 */
	};

	/*! @} */
}
#endif // VEC2_DOT_H