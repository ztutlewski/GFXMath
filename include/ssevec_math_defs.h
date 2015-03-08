#ifndef SSE_VEC_MATH_DEFS_DOT_H
#define SSE_VEC_MATH_DEFS_DOT_H
#include <xmmintrin.h>
#include <emmintrin.h>
#include <smmintrin.h>
#include <immintrin.h>
#include "math_defs.h"

/*!
 * \namespace	gofxmath
 *
 * \brief	G of F of X math namespace.
 */
namespace gofxmath
{
	/*! \defgroup VecMathDefs Vector Math Definitions */
	
	/*!
	 * \file 
	 * \ingroup VecMathDefs
	 * @{
	 */

	/*!
	 * \typedef	__m128 SseVec
	 *
	 * \brief	Defines an alias representing the SseVec.
	 * 
	 * \remarks It should be noted that the intel&reg; SSE registers (__m128 types) use little-endian logic.
	 *			That is to say the memory layout is arranged like such: [3 2 1 0] where the numbers represent
	 *			the indexed positions of the 32-bit sections where single-precision floating point or standard
	 *			1-word int values can be placed.
	 *			Because this can lead to some confusion with regards to where the indices of the vector are
	 *			located, vectors are located in reverse order, like so: [w z y x]. where the letters represent
	 *			the coordinate components of the vectors.
	 */
	typedef __m128 SseVec;

	/*!
	* \enum	SinCosFlag
	*
	* \brief	Values that represent sine cosine flags.
	*/
	enum SinCosFlag
	{
		SIN = 0,	/*!< Sine option */
		COS = 1,	/*!< Cosine option */
	};

	/*!
	* \enum	BlendOrder
	*
	* \brief	Values that represent blend orders.
	*
	* \remarks Used with vector blending operations.
	*/
	enum BlendOrder
	{
		LEFT = 0,   /*!< The left blend order option.
					*	 Chooses the left argument in the blend call.
					*/

		RIGHT = 1,  /*!< The right blend order option.
								*   Chooses the right argument in the blend call.
								*/

		NO_ORDER = 0 /*!< The NO_ORDER option.
											 * \remarks	This represents a coordinate we "don't care about."
											 *
											 *				When blending, much like when swizzling or shuffling, there may be times when you must blend in
											 *				more values than you need, or values that you don't need in certain positions.  Sometimes this is
											 *				because the values that are needed for those positions are not available in the source vector.
											 *
											 *				For example, when loading a 3D vector, the final (fourth) value should (ideally) be <B>1.0f</B>,
											 *		 		yielding a vector layout that looks like <CODE>&lt;x y z 1.0f&gt;</CODE>.
											 *	 			This is largely for the sake of mathematical completeness, and to prevent errors during other calculations.
											 *
											 *				It is likely more convenient for other calculations, and for readability, to simply ignore what
											 *				values are pushed into the fourth position of the vector until the end of the calculations, at
											 *				which time one might use a VecBlend call or a similar method to force a value of 1.0f in that
											 *				space.
											 *
											 *				The NO_ORDER value is designated for any such situations where the value in the given SseVec position
											 *				is not important to the calculations, and is <EM>purely</EM> intended to be used for purposes of
											 *				readability.
											 *
											 *				<B>Note:</B> It is <EM>strongly</EM> discouraged that one use the NO_ORDER for its numerical value during calculations,
											 *				as its use implies that the numerical value of the index in that position, as well as the value the index points
											 *				to, <B>do not matter to the calculations</B>.
											 */
	};

/*!
 * \def	SSE_VEC_CALL();
 *
 * \brief The calling convention for most SseVec functions.
 *
 * \date	2/21/2015
 */
#define SSE_VEC_CALL inline SseVec

	/*!
	 * \brief	Sets the SseVec to represent a 2-component vector, with the given floating point components.
	 *
	 * \date	2/21/2015
	 *
	 * \param	x	The x component of the resulting 2D SseVec.
	 * \param	y	The y component of the resulting 2D SseVec.
	 *
	 * \return	A SseVec representation of a 2-component vector, using the given components.
	 *
	 * \remarks	The 128-bit registers are loaded in "reverse" order (with respect to intel
	 * 			specifications). Intel loads packed registers in descending order of indices (that is,
	 * 			the highest index is also the left-most index).  The resulting layout looks something
	 * 			like this: [3 2 1 0] where the numbers represent the index of the packed member.
	 *
	 * 			These representations load the registers in ascending order of indices. This produces
	 * 			a memory structure that can be represented as such: [0 1 2 3], which is generally
	 * 			more readable and maintainable.
	 *
	 *			Sets the third and fourth components of the SseVec to 0.0f and 1.0f, respectively.
	 */
	SSE_VEC_CALL SetSseVec2(float x, float y)
	{
		return _mm_set_ps(1.0f, 0.0f, y, x);
	}

	/*!
	 * \brief	Sets the SseVec to represent a 3-component vector, with the given floating point components.
	 *
	 * \date	2/21/2015
	 *
	 * \param	x	The x component.
	 * \param	y	The y component.
	 * \param	z	The z component.
	 *
	 * \return	A SseVec representation of a 3-component vector, using the given components.
	 *
	 * \remarks	The 128-bit registers are loaded in "reverse" order (with respect to intel
	 * 			specifications). Intel loads packed registers in descending order of indices (that is,
	 * 			the highest index is also the left-most index).  The resulting layout looks something
	 * 			like this: [3 2 1 0] where the numbers represent the index of the packed member.
	 *
	 * 			These representations load the registers in ascending order of indices. This produces
	 * 			a memory structure that can be represented as such: [0 1 2 3], which is generally
	 * 			more readable and maintainable.
	 *
	 *			Sets the fourth component value of the SseVec to 1.0f.
	 */
	SSE_VEC_CALL SetSseVec3(float x, float y, float z)
	{
		return _mm_set_ps(1.0f, z, y, x);
	}

	/*!
	 * \brief	Sets the SseVec to represent a 4-component vector, with the given floating point components.
	 *
	 * \date	2/21/2015
	 *
	 * \param	x	The x component.
	 * \param	y	The y component.
	 * \param	z	The z component.
	 * \param	w	The w component.
	 *
	 * \return	A SseVec representation of a 4-component vector, using the given components.
	 *
	 * \remarks	The 128-bit registers are loaded in "reverse" order (with respect to intel
	 * 			specifications). Intel loads packed registers in descending order of indices (that is,
	 * 			the highest index is also the left-most index).  The resulting layout looks something
	 * 			like this: [3 2 1 0] where the numbers represent the index of the packed member.
	 *
	 * 			These representations load the registers in ascending order of indices. This produces
	 * 			a memory structure that can be represented as such: [0 1 2 3], which is generally
	 * 			more readable and maintainable.
	 */
	SSE_VEC_CALL SetSseVec4(float x, float y, float z, float w)
	{
		return _mm_set_ps(w, z, y, x);
	}

	/*!
	 * \brief	Sets the SseVec to represent a 4-component vector, with the given floating point components.
	 *
	 * \date	2/21/2015
	 *
	 * \param	xyzw	The float value to load in all four components.
	 *
	 * \return	A SseVec representation of a 4-component vector, using the given component value.
	 *
	 * \remarks	An SseVec loaded with all four components set to the given float value.
	 */
	SSE_VEC_CALL SetSseVec4(float xyzw)
	{
		return _mm_set_ps(xyzw, xyzw, xyzw, xyzw);
	}

	/*!
	 * \brief	Creates a "masking" SseVec, using the bits from x, y, z, and w.
	 *
	 * \date	2/21/2015
	 *
	 * \param	x	The x-coordinate mask value.
	 * \param	y	The y-coordinate mask value.
	 * \param	z	The z-coordinate mask value.
	 * \param	w	The w-coordinate mask value.
	 *
	 * \return	An SseVec with the bits copied into its components from the four given
	 *			MaskVals.
	 *
	 * \remarks		SseVec masks allow for quick, easy, and readable bitwise operations on other SseVecs.
	 *				The four MaskVal values passed to this function are loaded into an 
	 *				[__m128i](https://msdn.microsoft.com/en-us/library/26232t5c.aspx) register,
	 *				then the register's contents are then statically cast to an 
	 *				[__m128](https://msdn.microsoft.com/en-us/library/ayeb3ayc.aspx) value register,
	 *				keeping the exact bit layout that was contained in the __m128i register.
	 */
	SSE_VEC_CALL SetSseVecMask(MaskVal x, MaskVal y, MaskVal z, MaskVal w)
	{
		return _mm_castsi128_ps(_mm_set_epi32(w, z, y, x));
	}

	/*!
	 * \brief	Sets an SseVec mask with one value, placing said value into each of the four positions in the register.
	 *
	 * \date	2/21/2015
	 *
	 * \param	xyzw	The value to place in all four coordinate positions.
	 *
	 * \return	An SseVec with the given value placed in all four coordinate positions.
	 */
	SSE_VEC_CALL Set1SseVecMask(MaskVal xyzw)
	{
		return _mm_castsi128_ps(_mm_set1_epi32(xyzw));
	}

	const SseVec UNIT_0001 = SetSseVec4(0.0f, 0.0f, 0.0f, 1.0f);/*!< The unit SseVec <0 0 0 1> */
	const SseVec UNIT_0010 = SetSseVec4(0.0f, 0.0f, 1.0f, 0.0f);/*!< The unit SseVec <0 0 1 0> */
	const SseVec UNIT_0100 = SetSseVec4(0.0f, 1.0f, 0.0f, 0.0f);/*!< The unit SseVec <0 1 0 0> */
	const SseVec UNIT_1000 = SetSseVec4(1.0f, 0.0f, 0.0f, 0.0f);/*!< The unit SseVec <1 0 0 0> */

	const SseVec F_NEG4_PI2_1111 = SetSseVec4(F_NEG4_PI2);/*!< SseVec of the form <\\(\\frac{-4}{\\pi^2} \\frac{-4}{\\pi^2} \\frac{-4}{\\pi^2} \\frac{-4}{\\pi^2})> */
	const SseVec F_4_PI_1111 = SetSseVec4(F_4_PI);/*!< SseVec of the form <\\(\\frac{4}{\\pi} \\frac{4}{\\pi} \\frac{4}{\\pi} \\frac{4}{\\pi}\\)> */
	const SseVec F_1_2PI_1111 = SetSseVec4(F_1_2PI);/*!< SseVec of the form <\\(\\frac{1}{2\\pi} \\frac{1}{2\\pi} \\frac{1}{2\\pi} \\frac{1}{2\\pi}\\)> */

	const SseVec F_PI_2_1111 = SetSseVec4(F_PI_2);/*!< SseVec of the form <\\(\\frac{\\pi}{2} \\frac{\\pi}{2} \\frac{\\pi}{2} \\frac{\\pi}{2})> */
	const SseVec F_PI_1111 = SetSseVec4(F_PI);/*!< SseVec of the form <\\(\\pi \\pi \\pi \\pi\\)>*/
	const SseVec F_2PI_1111 = SetSseVec4(F_2PI);/*!< SseVec of the form <\\(2\\pi 2\\pi 2\\pi 2\\pi\\)> */

	const SseVec MASK_1000 = SetSseVecMask(0xFFFFFFFF, 0x0,		  0x0,			  0x0);			/*!< SseVec mask that will match any bit in the x-coordinate position. Takes the form < 0xFFFFFFFF 0x0 0x0 0x0>*/
	const SseVec MASK_0100 = SetSseVecMask(0x0,		   0xFFFFFFFF, 0x0,			  0x0);			/*!< SseVec mask that will match any bit in the y-coordinate position. Takes the form < 0x0 0xFFFFFFFF 0x0 0x0> */
	const SseVec MASK_0010 = SetSseVecMask(0x0,		   0x0,		  0xFFFFFFFF,	  0x0);			/*!< SseVec mask that will match any bit in the z-coordinate position. Takes the form < 0x0 0x0 0xFFFFFFFF 0x0> */
	const SseVec MASK_0001 = SetSseVecMask(0x0,		   0x0,		  0x0,			  0xFFFFFFFF);	/*!< SseVec mask that will match any bit in the w-coordinate position. Takes the form < 0x0 0x0 0x0 0xFFFFFFFF> */
	
	const SseVec MASK_1100 = SetSseVecMask(0xFFFFFFFF,	0xFFFFFFFF, 0x0,		0x0);			/*!< SseVec mask that will match any bit in the x or y-coordinate positions. Takes the form <0xFFFFFFFF 0xFFFFFFFF 0x0 0x0> */
	const SseVec MASK_1010 = SetSseVecMask(0xFFFFFFFF,	0x0,		0xFFFFFFFF, 0x0);			/*!< SseVec mask that will match any bit in the x or z-coordinate positions. Takes the form <0xFFFFFFFF 0x0 0xFFFFFFFF 0x0> */
	const SseVec MASK_1001 = SetSseVecMask(0xFFFFFFFF,	0x0,		0x0,		0xFFFFFFFF);	/*!< SseVec mask that will match any bit in the x or w-coordinate positions. Takes the form <0xFFFFFFFF 0x0 0x0 0xFFFFFFFF> */
	const SseVec MASK_0110 = SetSseVecMask(0x0,			0xFFFFFFFF, 0xFFFFFFFF, 0x0);			/*!< SseVec mask that will match any bit in the y or z-coordinate positions. Takes the form <0x0 0xFFFFFFFF 0xFFFFFFFF 0x0> */
	const SseVec MASK_0101 = SetSseVecMask(0x0,			0xFFFFFFFF, 0x0,		0xFFFFFFFF);	/*!< SseVec mask that will match any bit in the y or w-coordinate positions. Takes the form <0x0 0xFFFFFFFF 0x0 0xFFFFFFFF> */
	const SseVec MASK_0011 = SetSseVecMask(0x0,			0x0,		0xFFFFFFFF, 0xFFFFFFFF);	/*!< SseVec mask that will match any bit in the z or w-coordinate positions. Takes the form <0x0 0x0 0xFFFFFFFF 0xFFFFFFFF> */

	const SseVec MASK_0111 = SetSseVecMask(0x0,			0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF);	/*!< SseVec mask that will match any bit in the y, z, or w-coordinate positions. Takes the form <0x0 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF> */
	const SseVec MASK_1011 = SetSseVecMask(0xFFFFFFFF,	0x0,		0xFFFFFFFF, 0xFFFFFFFF);	/*!< SseVec mask that will match any bit in the x, z, or w-coordinate positions. Takes the form <0xFFFFFFFF 0x0 0xFFFFFFFF 0xFFFFFFFF> */
	const SseVec MASK_1101 = SetSseVecMask(0xFFFFFFFF,	0xFFFFFFFF, 0x0,		0xFFFFFFFF);	/*!< SseVec mask that will match any bit in the x, y, or w-coordinate positions. Takes the form <0xFFFFFFFF 0xFFFFFFFF 0x0 0xFFFFFFFF> */
	const SseVec MASK_1110 = SetSseVecMask(0xFFFFFFFF,	0xFFFFFFFF, 0xFFFFFFFF, 0x0);			/*!< SseVec mask that will match any bit in the x, y, or z-coordinate positions. Takes the form <0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF 0x0> */

	const SseVec SSE_VEC_ONE = SetSseVec4(1.0f);/*!< SseVec of the form <1.0f 1.0f 1.0f 1.0f> */
	const SseVec EPSILON_1111 = SetSseVec4(Epsilon());/*!< SseVec of the form <%%\\epsilon \\epsilon \\epsilon \\epsilon%%> where %%\\epsilon%% is the smallest value such that %%1.0f + \\epsilon 	\\not= 1.0f%% */

	/*!
	 * \brief First 16 taylor series sine approximation coefficients loaded into all four components of their respective SseVecs.
	 */
	inline SseVec SinCoefSseVec(int i)
	{
		static const std::array<SseVec, NUM_TRIG_COEFS> SIN_COEFFICIENT_SSEVECS =
		{
			SetSseVec4(SinCoef(0)),  // 1/(1+2*1)!  = 1/3!
			SetSseVec4(SinCoef(1)),  // 1/(1+2*2)!  = 1/5!
			SetSseVec4(SinCoef(2)),  // 1/(1+2*3)!  = 1/7!
			SetSseVec4(SinCoef(3)),  // 1/(1+2*4)!  = 1/9!
			SetSseVec4(SinCoef(4)),  // 1/(1+2*5)!  = 1/11!
			SetSseVec4(SinCoef(5)),  // 1/(1+2*6)!  = 1/13!
			SetSseVec4(SinCoef(6)),  // 1/(1+2*7)!  = 1/15!
			SetSseVec4(SinCoef(7)),  // 1/(1+2*8)!  = 1/17!
			SetSseVec4(SinCoef(8)),  // 1/(1+2*9)!  = 1/19!
			SetSseVec4(SinCoef(9)),  // 1/(1+2*10)! = 1/21!
			SetSseVec4(SinCoef(10)), // 1/(1+2*11)! = 1/23!
			SetSseVec4(SinCoef(11)), // 1/(1+2*12)! = 1/25!
			SetSseVec4(SinCoef(12)), // 1/(1+2*13)! = 1/27!
			SetSseVec4(SinCoef(13)), // 1/(1+2*14)! = 1/29!
			SetSseVec4(SinCoef(14)), // 1/(1+2*15)! = 1/31!
			SetSseVec4(SinCoef(15)), // 1/(1+2*16)! = 1/33!
		};

		return SIN_COEFFICIENT_SSEVECS[i];
	}
	

	/*! 
	 * \brief First 16 taylor series cosine approximation coefficients loaded into all four components of their respective SseVecs. 
	 */
	inline SseVec CosCoefSseVec(int i)
	{
		static const std::array<SseVec, NUM_TRIG_COEFS> COS_COEFFICIENT_SSEVECS =
		{
			SetSseVec4(CosCoef(0)),  // 1/(2*1)!  = 1/2!
			SetSseVec4(CosCoef(1)),  // 1/(2*2)!  = 1/4!
			SetSseVec4(CosCoef(2)),  // 1/(2*3)!  = 1/6!
			SetSseVec4(CosCoef(3)),  // 1/(2*4)!  = 1/8!
			SetSseVec4(CosCoef(4)),  // 1/(2*5)!  = 1/10!
			SetSseVec4(CosCoef(5)),  // 1/(2*6)!  = 1/12!
			SetSseVec4(CosCoef(6)),  // 1/(2*7)!  = 1/14!
			SetSseVec4(CosCoef(7)),  // 1/(2*8)!  = 1/16!
			SetSseVec4(CosCoef(8)),  // 1/(2*9)!  = 1/18!
			SetSseVec4(CosCoef(9)),  // 1/(2*10)! = 1/20!
			SetSseVec4(CosCoef(10)), // 1/(2*11)! = 1/22!
			SetSseVec4(CosCoef(11)), // 1/(2*12)! = 1/24!
			SetSseVec4(CosCoef(12)), // 1/(2*13)! = 1/26!
			SetSseVec4(CosCoef(13)), // 1/(2*14)! = 1/28!
			SetSseVec4(CosCoef(14)), // 1/(2*15)! = 1/30!
			SetSseVec4(CosCoef(15)), // 1/(2*16)! = 1/32!
		};

		return COS_COEFFICIENT_SSEVECS[i];
	}
	

	/*!
	 * \enum	VecCoord
	 *
	 * \brief	Values that represent vector coordinates.
	 *
	 * \date	2/21/2015
	 * 
	 * \remarks Used for ssevec swizzling and shuffling function calls.
	 * 
	 * \sa 
	 */
	enum VecCoord
	{
		X = 0,  /*!< The x coordinate option (int value 0) */
		Y = 1,  /*!< The y coordinate option (int value 1) */
		Z = 2,  /*!< The z coordinate option (int value 2) */
		W = 3,  /*!< The w coordinate option (int value 3) */
		NA = 0	/*!< The NA option.
				 * \remarks This represents a coordinate we "don't care about."
				 *			
				 *				When swizzling or shuffling, there may be times when you must shuffle in
				 *				more values than you need, or values that you don't need in certain positions.  Sometimes this is
				 *				because the values that are needed for those positions are not available in the source vector.
				 *			
				 *				For example, when loading a 3D vector, the final (fourth) value should (ideally) be <B>1.0f</B>,
				 *				yielding a vector layout that looks like <CODE>&lt;x y z 1.0f&gt;</CODE>.
				 *				This is largely for the sake of mathematical completeness, and to prevent errors during other calculations.
				 *			
				 *				It is likely more convenient for other calculations, and for readability, to simply ignore what
				 *				values are pushed into the fourth position of the vector until the end of the calculations, at
				 *				which time one might use a VecBlend call or a similar method to force a value of 1.0f in that
				 *				space.
				 *			
				 *				The NA value is designated for any such situations where the value in the given SseVec position
				 *				is not important to the calculations, and while it is given a valid vector index value, and
				 *				theoretically <EM>could</EM> be used in place of one of the other VecCoord enum constants,
				 *				is purely intended to be used for purposes of readability, and should never be used for its
				 *				numeric value.
				 */
	};
	/*! @} */
}
#endif