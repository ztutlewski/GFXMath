#ifndef SSE_VEC_DOT_H
#define SSE_VEC_DOT_H
#include "ssevec_math_defs.h"
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"

/*! 
 * \file 
 */

/*!
 * \defgroup SIMDVecMath SIMD Vector Math
 */

/*!
 * \namespace	gofxmath
 *
 * \brief	G of F of X math namespace.
 */
namespace gofxmath
{
	/*!
	 * \ingroup SIMDVecMath
	 * @{
	 */

	/*!
	 * \brief	Shuffles two values from the left SseVec into the lower two positions of the result
	 *			SseVec, and two values from the right SseVec into the upper two positions of the
	 *			result.
	 *
	 * \date	2/21/2015
	 *
	 * \tparam	coordX	The index of the coordinate to take from the left SseVec 
	 *					and put into the first (x-coordinate) position of the result.
	 *
	 * \tparam	coordY	The index of the coordinate to take from the left SseVec 
	 *					and put into the second (y-coordinate) position of the result.
	 *
	 * \tparam	coordZ	The index of the coordinate to take from the left SseVec 
	 *					and put into the third (z-coordinate) position of the result.
	 *
	 * \tparam	coordW	The index of the coordinate to take from the left SseVec 
	 *					and put into the fourth (w-coordinate) position of the result.
	 *
	 * \param	v0	The first SseVec to shuffle values from.
	 *
	 * \param	v1	The second SseVec to shuffle values from.
	 *
	 * \return	An SseVec containing the values shuffled in from the two respective SseVecs.
	 *
	 * \remarks	As with all SseVec calls, the x, y, z, and w coordinates are "reversed" with
	 *			respect to memory location in the vector.  While Intel uses little-endian
	 *			memory layouts, all implementations (including this one) within this library
	 *			utilize a big-endian method, for the sake of readability.
	 */
	template<VecCoord coordX, VecCoord coordY, VecCoord coordZ, VecCoord coordW>
	SSE_VEC_CALL VecShuffle(const SseVec& v0, const SseVec& v1)
	{
		return _mm_shuffle_ps(v0, v1, _MM_SHUFFLE(coordW, coordZ, coordY, coordX));
	}

	/*!
	 * \brief	Swizzles the given SseVec into itself, allowing for mixing and matching of
	 *			coordinate values.
	 *
	 * \date	2/21/2015
	 *
	 * \tparam	coordX	The index of the coordinate to take from the original SseVec 
	 *					and put into the first (x-coordinate) position of the result.
	 *
	 * \tparam	coordY	The index of the coordinate to take from the original SseVec 
	 *					and put into the second (y-coordinate) position of the result.
	 *
	 * \tparam	coordZ	The index of the coordinate to take from the original SseVec 
	 *					and put into the third (z-coordinate) position of the result.
	 *
	 * \tparam	coordW	The index of the coordinate to take from the original SseVec 
	 *					and put into the fourth (w-coordinate) position of the result.
	 *
	 * \param	vec	The SseVec being swizzled.
	 *
	 * \return	An SseVec containing the values swizzled in from the respective SseVec.
	 *
	 * \remarks	As with all SseVec calls, the x, y, z, and w coordinates are "reversed" with
	 *			respect to memory location in the vector.  While Intel uses little-endian
	 *			memory layouts, all implementations (including this one) within this library
	 *			utilize a big-endian method, for the sake of readability.
	 */
	template<VecCoord cX, VecCoord cY, VecCoord cZ, VecCoord cW>
	SSE_VEC_CALL VecSwizzle(const SseVec& vec)
	{
		return _mm_shuffle_ps(vec, vec, _MM_SHUFFLE(cW, cZ, cY, cX));
	}

	/*!
	 * \brief	Splats the given SseVec into itself, setting all four values of
	 *			the result SseVec to only one of the values from the original SseVec.
	 *
	 * \date	2/21/2015
	 *
	 * \tparam	coordX	The index of the coordinate to take from the original SseVec 
	 *					and put into all four positions of the result.
	 *
	 * \param	vec	The SseVec being splatted.
	 * 
	 * \return	An SseVec containing the values splatted in from the two respective vectors.
	 *
	 * \remarks	As with all SseVec calls, the x, y, z, and w coordinates are "reversed" with
	 *			respect to memory location in the vector.  While Intel uses little-endian
	 *			memory layouts, all implementations (including this one) within this library
	 *			utilize a big-endian method, for the sake of readability.
	 */
	template<VecCoord c>
	SSE_VEC_CALL VecSplat(const SseVec& vec)
	{
		return _mm_shuffle_ps(vec, vec, _MM_SHUFFLE(c, c, c, c));
	}

	/*!
	 * \brief	Blends the two given SseVecs together, selecting values from the left or right
	 *			arguments depending on the chosen template arguments.
	 *
	 * \date	2/21/2015
	 *
	 * \tparam	bX	The BlendOrder value determining whether the x-coordinate should 
	 *				come from the x-coordinate of the left or right SseVec argument.
	 *				BlendOrder::LEFT selects the coordinate from the left argument,
	 *				BlendOrder::RIGHT selects the coordinate from the right argument.
	 * 
	 * \tparam	bY	The BlendOrder value determining whether the x-coordinate should 
	 *				come from the x-coordinate of the left or right SseVec argument.
	 *				BlendOrder::LEFT selects the coordinate from the left argument,
	 *				BlendOrder::RIGHT selects the coordinate from the right argument.
	 * 
	 * \tparam	bZ	The BlendOrder value determining whether the x-coordinate should
	 *				come from the x-coordinate of the left or right SseVec argument.
	 *				BlendOrder::LEFT selects the coordinate from the left argument,
	 *				BlendOrder::RIGHT selects the coordinate from the right argument.
	 * 
	 * \tparam	bW	The BlendOrder value determining whether the x-coordinate should
	 *				come from the x-coordinate of the left or right SseVec argument.
	 *				BlendOrder::LEFT selects the coordinate from the left argument,
	 *				BlendOrder::RIGHT selects the coordinate from the right argument.
	 * 
	 * \param	left	The left SseVec argument to blend.
	 * \param	right	The right SseVec argument to blend.
	 *
	 * \return	An SseVec containing the blended values from the left and right SseVec arguments,
	 *			via the BlendOrder arguments.
	 */
	template<BlendOrder bX, BlendOrder bY, BlendOrder bZ, BlendOrder bW>
	SSE_VEC_CALL VecBlend(const SseVec& left, const SseVec& right)
	{
		return _mm_blend_ps(left, right, (((bW) << 3) | ((bZ) << 2) | ((bY) << 1) | ((bX))));
	}

	/*!
	 * \brief	Blends the two given SseVecs together, selecting values from the left or right
	 *			arguments depending on the chosen template arguments.
	 *
	 * \date	2/21/2015
	 *
	 * \tparam	bX	The SinCosFlag value determining whether the x-coordinate should 
	 *				come from the x-coordinate of the left or right SseVec argument.
	 *				BlendOrder::LEFT selects the coordinate from the left argument,
	 *				BlendOrder::RIGHT selects the coordinate from the right argument.
	 * 
	 * \tparam	bY	The SinCosFlag value determining whether the x-coordinate should 
	 *				come from the x-coordinate of the left or right SseVec argument.
	 *				BlendOrder::LEFT selects the coordinate from the left argument,
	 *				BlendOrder::RIGHT selects the coordinate from the right argument.
	 * 
	 * \tparam	bZ	The SinCosFlag value determining whether the x-coordinate should
	 *				come from the x-coordinate of the left or right SseVec argument.
	 *				BlendOrder::LEFT selects the coordinate from the left argument,
	 *				BlendOrder::RIGHT selects the coordinate from the right argument.
	 * 
	 * \tparam	bW	The SinCosFlag value determining whether the x-coordinate should
	 *				come from the x-coordinate of the left or right SseVec argument.
	 *				BlendOrder::LEFT selects the coordinate from the left argument,
	 *				BlendOrder::RIGHT selects the coordinate from the right argument.
	 * 
	 * \param	left	The left SseVec argument to blend.
	 * \param	right	The right SseVec argument to blend.
	 *
	 * \return	An SseVec containing the blended values from the left and right SseVec arguments,
	 *			via the BlendOrder arguments.
	 */
	template<SinCosFlag bX, SinCosFlag bY, SinCosFlag bZ, SinCosFlag bW>
	SSE_VEC_CALL VecSinCosBlend(const SseVec& left, const SseVec& right)
	{
		return _mm_blend_ps(left, right, (((bW) << 3) | ((bZ) << 2) | ((bY) << 1) | ((bX))));
	}

	/*!
	 * \brief	Performs a bitwise "and" on the two given SseVecs.
	 *
	 * \date	2/21/2015
	 * 
	 * \param	left	The left operand in the bitwise "and" operation.
	 * \param	right	The right operand in the bitwise "and" operation.
	 * 
	 * \return	An SseVec containing the resulting values from the bitwise "and" operation
	 *			on the two given SseVecs.
	 * 
	 * \remarks Equivalent to `_mm_and_ps(__m128,__m128)`
	 */
	SSE_VEC_CALL VecAnd(const SseVec& left, const SseVec& right)
	{
		return _mm_and_ps(left, right);
	}

	/*!
	 * \brief	Performs a bitwise "or" on the two given SseVecs.
	 *
	 * \date	2/21/2015
	 * 
	 * \param	left	The left operand in the bitwise "or" operation.
	 * \param	right	The right operand in the bitwise "or" operation.
	 * 
	 * \return	An SseVec containing the resulting values from the bitwise "or" operation
	 *			on the two given SseVecs.
	 *
	 * \remarks Equivalent to `_mm_or_ps(__m128,__m128)`
	 */
	SSE_VEC_CALL VecOr(const SseVec& left, const SseVec& right)
	{
		return _mm_or_ps(left, right);
	}

	/*!
	 * \brief	Performs a bitwise "exclusive or" on the two given SseVecs.
	 *
	 * \date	2/21/2015
	 * 
	 * \param	left	The left operand in the bitwise "exclusive or" operation.
	 * \param	right	The right operand in the bitwise "exclusive or" operation.
	 * 
	 * \return	An SseVec containing the resulting values from the bitwise "exclusive or" operation
	 *			on the two given SseVecs.
	 *
	 * \remarks Equivalent to `_mm_xor_ps(__m128,__m128)`
	 */
	SSE_VEC_CALL VecXOr(const SseVec& left, const SseVec& right)
	{
		return _mm_xor_ps(left, right);
	}

	/*!
	 * \brief	Rounds the values of all four components of the given SseVec
	 *			to the next whole number in the direction of %%-\\infty%%,
	 *			and returns the result.
	 *
	 * \date	2/21/2015
	 * 
	 * \param	vec	The original SseVec for which the values are to be rounded toward
	 *			%%-\\infty%%
	 * 
	 * \return	An SseVec containing the values from the original given SseVec after
	 *			rounding them all toward %%-\\infty%%.
	 * 
	 * \remarks Equivalent to the intel&reg; SSE macro `_mm_floor_ps(__m128)`
	 */
	SSE_VEC_CALL VecFloor(const SseVec& vec)
	{
		return _mm_floor_ps(vec);
	}

	/*!
	 * \brief	Rounds the values of all four components of the given SseVec
	 *			to the next whole number in the direction of %%\\infty%%,
	 *			and returns the result.
	 *
	 * \date	2/21/2015
	 * 
	 * \param	vec	The original SseVec for which the values are to be rounded toward
	 *			%%\\infty%%
	 * 
	 * \return	An SseVec containing the values from the original given SseVec after
	 *			rounding them all toward %%\\infty%%.
	 * 
	 * \remarks Equivalent to the intel&reg; SSE macro `_mm_ceil_ps(__m128)`
	 */
	SSE_VEC_CALL VecCeil(const SseVec& vec)
	{
		return _mm_ceil_ps(vec);
	}

	/*!
	 * \brief	Rounds the values of all four components of the given SseVec
	 *			toward the closest whole number, and returns the result.
	 *
	 * \date	2/21/2015
	 * 
	 * \param	vec The SseVec for which the coordinates will be rounded.
	 * 
	 * \return	An SseVec containing the values from the original given SseVec after
	 *			rounding them all toward %%-\\infty%%.
	 */
	SSE_VEC_CALL VecRound(const SseVec& vec)
	{
		return _mm_round_ps(vec, _MM_FROUND_TO_NEAREST_INT);
	}


	/*!
	 * \brief	Sets and returns an SseVec with all 0 values.
	 *
	 * \date	2/21/2015
	 * 
	 * \return	An SseVec containign all 0 values.
	 * 
	 * \remarks Equivalent to `_mm_setzero_ps();`
	 */
	SSE_VEC_CALL SetVecZero()
	{
		return _mm_setzero_ps();
	}

	/*!
	 * \brief	Loads and returns a SseVec with the components from the given Vec2.
	 *
	 * \date	2/21/2015
	 *
	 * \param	vec	The 2D vector containing the components to be loaded.
	 *
	 * \return	A SseVec loaded with the components from the given Vec2.
	 *
	 * \remarks	The 128-bit registers are loaded in "reverse" order (with respect to intel
	 * 			specifications). Intel loads packed registers in descending order of indices (that is,
	 * 			the highest index is also the left-most index).  
	 *
	 *			Sets the third and fourth components of the SseVec to 0.0f and 1.0f, respectively.
	 */
	SSE_VEC_CALL LoadSseVec2(const Vec2& vec)
	{
		return _mm_load_ps(vec.ToColVec().vals);
	}

	/*!
	 * \brief	Loads and returns a SseVec with the components from the given Vec3.
	 *
	 * \date	2/21/2015
	 *
	 * \param	vec	The 3D vector containing the components to be loaded.
	 *
	 * \return	A SseVec loaded with the components from the given Vec3.
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
	SSE_VEC_CALL LoadSseVec3(const Vec3& vec)
	{
		return _mm_load_ps(vec.ToColVec().vals);
	}

	/*!
	 * \brief	Loads and returns a SseVec with the components from the given Vec4.
	 *
	 * \date	2/21/2015
	 *
	 * \param	vec	The 4D vector containing the components to be loaded.
	 *
	 * \return	A SseVec loaded with the components from the given Vec4.
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
	SSE_VEC_CALL LoadSseVec4(const Vec4& vec)
	{
		return _mm_load_ps(vec.vals);
	}

	/*!
	 * \brief	Stores the SseVec representation of a 2D vector.
	 *
	 * \date	2/21/2015
	 *
	 * \param	vec	The SseVec.
	 *
	 * \return	The Vec2 containing the respective components from the SseVec.
	 *
	 * \remarks	The ordering of the components should not matter here, unless they weren't loaded
	 * 			into the SseVec properly, to begin with.
	 */
	inline Vec2 StoreSseVec2(const SseVec& vec)
	{
		Vec4 tmp;
		_mm_store_ps(tmp.vals, vec);
		return (Vec2)tmp;
	}

	/*!
	 * \brief	Stores the SseVec representation of a 3D vector.
	 *
	 * \date	2/21/2015
	 *
	 * \param	vec	The SseVec.
	 *
	 * \return	The Vec3 containing the respective components from the SseVec.
	 *
	 * \remarks	The ordering of the components should not matter here, unless they weren't loaded
	 * 			into the SseVec properly, to begin with.
	 */
	inline Vec3 StoreSseVec3(const SseVec& vec)
	{
		Vec4 tmp;
		_mm_store_ps(tmp.vals, vec);
		return (Vec3)tmp;
	}

	/*!
	 * \brief	Stores the SseVec representation of a 4D vector.
	 *
	 * \date	2/21/2015
	 *
	 * \param	vec	The SseVec.
	 *
	 * \return	The Vec4 containing the respective components from the SseVec.
	 *
	 * \remarks	The ordering of the components should not matter here, unless they weren't loaded
	 * 			into the SseVec properly, to begin with.
	 */
	inline Vec4 StoreSseVec4(const SseVec& vec)
	{
		Vec4 result;
		_mm_store_ps(result.vals, vec);
		return result;
	}

	/*!
	 * \brief	Negates the 2D components of the given SseVec.
	 *
	 * \date	2/21/2015
	 *
	 * \tparam	nX	Boolean representing whether the x-coordinate will be negated (negated if true, not negated if false).
	 * \tparam	nY	Boolean representing whether the y-coordinate will be negated (negated if true, not negated if false).
	 * \param	vec	The given SseVec to perform a negation on.
	 *
	 * \return	The SseVec resulting from the negation of the 2D components.
	 */
	template<bool nX = true, bool nY = true>
	SSE_VEC_CALL Vec2Negate(const SseVec& vec)
	{
		static const SseVec NEGATE_MASK = SetSseVecMask(nX << 31, nY << 31, 0x0, 0x0);
		return VecXOr(vec, NEGATE_MASK);
	}

	/*!
	 * \brief	Negates the 3D components of the given SseVec.
	 *
	 * \date	2/21/2015
	 *
	 * \tparam	nX	Boolean representing whether the x-coordinate will be negated (negated if true, not negated if false).
	 * \tparam	nY	Boolean representing whether the y-coordinate will be negated (negated if true, not negated if false).
	 * \tparam	nZ	Boolean representing whether the z-coordinate will be negated (negated if true, not negated if false).
	 * \param	vec	The given SseVec to perform a negation on.
	 *
	 * \return	The SseVec resulting from the negation of the 3D components.
	 */
	template<bool nX = true, bool nY = true, bool nZ = true>
	SSE_VEC_CALL Vec3Negate(const SseVec& vec)
	{
		static const SseVec NEGATE_MASK = SetSseVecMask(nX << 31, nY << 31, nZ << 31, 0x0);
		return VecXOr(vec, NEGATE_MASK);
	}

	/*!
	 * \brief	Negates the 4D components of the given SseVec.
	 *
	 * \date	2/21/2015
	 *
	 * \tparam	nX	Boolean representing whether the x-coordinate will be negated (negated if true, not negated if false).
	 * \tparam	nY	Boolean representing whether the y-coordinate will be negated (negated if true, not negated if false).
	 * \tparam	nZ	Boolean representing whether the z-coordinate will be negated (negated if true, not negated if false).
	 * \tparam	nW	Boolean representing whether the w-coordinate will be negated (negated if true, not negated if false).
	 * \param	vec	The given SseVec to perform a negation on.
	 *
	 * \return	The SseVec resulting from the negation of the 4D components.
	 */
	template<bool nX = true, bool nY = true, bool nZ = true, bool nW = true>
	SSE_VEC_CALL Vec4Negate(const SseVec& vec)
	{
		static const SseVec NEGATE_MASK = SetSseVecMask(nX << 31, nY << 31, nZ << 31, nW << 31);
		return VecXOr(vec, NEGATE_MASK);
	}

	/*!
	 * \brief	Negates the 2D components of the given SseVec.
	 *
	 * \date	2/21/2015
	 *
	 * \tparam	nX	Boolean representing whether the x-coordinate will be negated (negated if true, not negated if false).
	 * \tparam	nY	Boolean representing whether the y-coordinate will be negated (negated if true, not negated if false).
	 * \param	vec	The given SseVec for which to calculate the absolute value of the components.
	 *
	 * \return	The SseVec resulting from the negation of the 2D components.
	 */
	template<bool aX = true, bool aY = true>
	SSE_VEC_CALL Vec2Abs(const SseVec& vec)
	{
		static const SseVec NEGATE_MASK = SetSseVecMask(~(aX << 31), ~(aY << 31), 0x0, 0x1);
		return VecAnd(vec, NEGATE_MASK);
	}

	/*!
	 * \brief	Negates the 3D components of the given SseVec.
	 *
	 * \date	2/21/2015
	 *
	 * \tparam	nX	Boolean representing whether the x-coordinate will be negated (negated if true, not negated if false).
	 * \tparam	nY	Boolean representing whether the y-coordinate will be negated (negated if true, not negated if false).
	 * \tparam	nZ	Boolean representing whether the z-coordinate will be negated (negated if true, not negated if false).
	 * \param	vec	The given SseVec for which to calculate the absolute value of the components.
	 *
	 * \return	The SseVec resulting from the negation of the 3D components.
	 */
	template<bool aX = true, bool aY = true, bool aZ = true>
	SSE_VEC_CALL Vec3Abs(const SseVec& vec)
	{
		static const SseVec NEGATE_MASK = SetSseVecMask(~(aX << 31), ~(aY << 31), ~(aZ << 31), 0x1);
		return VecAnd(vec, NEGATE_MASK);
	}

	/*!
	 * \brief	Negates the 4D components of the given SseVec.
	 *
	 * \date	2/21/2015
	 *
	 * \tparam	nX	Boolean representing whether the x-coordinate will be negated (negated if true, not negated if false).
	 * \tparam	nY	Boolean representing whether the y-coordinate will be negated (negated if true, not negated if false).
	 * \tparam	nZ	Boolean representing whether the z-coordinate will be negated (negated if true, not negated if false).
	 * \tparam	nW	Boolean representing whether the w-coordinate will be negated (negated if true, not negated if false).
	 * \param	vec	The given SseVec for which to calculate the absolute value of the components.
	 *
	 * \return	The SseVec resulting from the negation of the 4D components.
	 */
	template<bool aX = true, bool aY = true, bool aZ = true, bool aW = true>
	SSE_VEC_CALL Vec4Abs(const SseVec& vec)
	{
		static const SseVec NEGATE_MASK = SetSseVecMask(~(aX << 31), ~(aY << 31), ~(aZ << 31), ~(aW << 31));
		return VecAnd(vec, NEGATE_MASK);
	}

	/*!
	 * \brief	Prints the 2D components of the given SseVec.
	 *
	 * \date	2/21/2015
	 *
	 * \param	vec	The SseVec to print as a 2-coordinate vector.
	 */
	void PrintSseVec2(const SseVec& vec);

	/*!
	 * \brief	Prints the 3D components of the given SseVec.
	 *
	 * \date	2/21/2015
	 *
	 * \param	vec	The SseVec to print as a 3-coordinate vector.
	 */
	void PrintSseVec3(const SseVec& vec);

	/*!
	 * \brief	Prints the 4D components of the given SseVec.
	 *
	 * \date	2/21/2015
	 *
	 * \param	vec	The SseVec to print as a 4-coordinate vector.
	 */
	void PrintSseVec4(const SseVec& vec);

	/*!
	 * \brief	Takes the dot product of the two given 2D SseVecs and loads
	 *			the resulting value into all four positions in the returned
	 *			SseVec.
	 *
	 * \date	2/21/2015
	 *
	 * \param	v0	The first 2D vector in the operation.
	 * \param	v1	The second 2D vector in the operation.
	 *
	 * \return	A 4D SseVec containing four copies of the dot product of the 
	 *			two given 2D vectors.
	 */
	SSE_VEC_CALL Vec2Dot(const SseVec& v0, const SseVec& v1)
	{
		return _mm_dp_ps(v0, v1, 0x3F);
	}

	/*!
	 * \brief	Takes the dot product of the two given 3D SseVecs and loads
	 *			the resulting value into all four positions in the returned
	 *			SseVec.
	 *
	 * \date	2/21/2015
	 *
	 * \param	v0	The first 3D vector in the operation.
	 * \param	v1	The second 3D vector in the operation.
	 *
	 * \return	A 4D SseVec containing four copies of the dot product of the 
	 *			two given 3D vectors.
	 */
	SSE_VEC_CALL Vec3Dot(const SseVec& v0, const SseVec& v1)
	{
		return _mm_dp_ps(v0, v1, 0x7F);
	}

	/*!
	 * \brief	Takes the dot product of the two given 4D SseVecs and loads
	 *			the resulting value into all four positions in the returned
	 *			SseVec.
	 *
	 * \date	2/21/2015
	 *
	 * \param	v0	The first 4D vector.
	 * \param	v1	The second 4D vector.
	 *
	 * \return	A 4D SseVec containing four copies of the dot product of the 
	 *			two given 4D vectors.
	 */
	SSE_VEC_CALL Vec4Dot(const SseVec& v0, const SseVec& v1)
	{
		return _mm_dp_ps(v0, v1, 0xFF);
	}

	/*!
	 * \brief	Adds two given SseVecs and returns the sum SseVec.
	 *
	 * \date	2/21/2015
	 *
	 * \param	v0	The first vector.
	 * \param	v1	The second vector.
	 *
	 * \return	The sum of the first and second vectors.
	 *
	 * \remarks Equivalent to a call to <CODE>_mm_add_ps(v0, v1)</CODE>.
	 */
	SSE_VEC_CALL VecAdd(const SseVec& v0, const SseVec& v1)
	{
		return _mm_add_ps(v0, v1);
	}

	/*!
	* \brief	Subtracts two given SseVecs and returns the difference SseVec.
	*
	* \date	2/21/2015
	*
	* \param	v0	The first vector.
	* \param	v1	The second vector.
	*
	* \return	The difference of the first and second vectors.
	*
	* \remarks Equivalent to a call to <CODE>_mm_sub_ps(v0, v1)</CODE>.
	*/
	SSE_VEC_CALL VecSub(const SseVec& v0, const SseVec& v1)
	{
		return _mm_sub_ps(v0, v1);
	}

	/*!
	 * \brief	Subtracts even-indexed positions and adds on 
	 *			odd-indexed positions.
	 *
	 * \remarks Equivalent to _mm_addsub_ps(__m128 v0, __m128 v1);
	 */
	SSE_VEC_CALL VecAddSub(const SseVec& v0, const SseVec& v1)
	{
		return _mm_addsub_ps(v0, v1);
	}

	/*!
	 * \brief	Multiplies the two given SseVecs.
	 *
	 * \date	2/21/2015
	 *
	 * \param	v0	The first vector.
	 * \param	v1	The second vector.
	 *
	 * \return	The product of the two vectors' respective components.
	 *
	 * \remarks Equivalent to a call to <CODE>_mm_mul_ps(v0, v1)</CODE>.
	 */
	SSE_VEC_CALL VecMul(const SseVec& v0, const SseVec& v1)
	{
		return _mm_mul_ps(v0, v1);
	}

	/*!
	 * \brief	Calculates and returns the reciprocal square root of the given
	 *			SseVec.
	 *
	 * \date	2/21/2015
	 *
	 * \param	vec	The vector for which to compute the reciprocal square root of the
	 *				components.
	 *
	 * \return	The SseVec containing the reciprocal square roots of the components
	 *			of the given vector.
	 * 
	 * \remarks Equivalent to a call to <CODE>_mm_rsqrt_ps(vec)</CODE>.
	 */
	SSE_VEC_CALL VecRSqrt(const SseVec& vec)
	{
		return _mm_rsqrt_ps(vec);
	}


	/*!
	 * \brief	Calculates and returns the square root of the given SseVec.
	 *
	 * \date	2/21/2015
	 *
	 * \param	vec	The vector for which to compute the square root of the components.
	 *
	 * \return	The SseVec containing the square roots of the components of the given vector.
	 *
	 * \remarks Equivalent to a call to <CODE>_mm_sqrt_ps(vec)</CODE>.
	 */
	SSE_VEC_CALL VecSqrt(const SseVec& vec)
	{
		return _mm_sqrt_ps(vec);
	}

	/*!
	 * \brief	Divides the two given SseVecs.
	 *
	 * \date	2/21/2015
	 *
	 * \param	v0	The first vector.
	 * \param	v1	The second vector.
	 *
	 * \return	The quotient of the two vectors' respective components.
	 *
	 * \remarks Equivalent to a call to <CODE>_mm_div_ps(vec)</CODE>.
	 */
	SSE_VEC_CALL VecDiv(const SseVec& v0, const SseVec& v1)
	{
		return _mm_div_ps(v0, v1);
	}

	/*!
	 * \brief	Adds two SseVecs representing Vec2s.
	 *
	 * \date	2/21/2015
	 *
	 * \param	v0	The first 2D vector.
	 * \param	v1	The second 2D vector.
	 *
	 * \return	The sum SseVec of the two original SseVecs.
	 */
	SSE_VEC_CALL Vec2Add(const SseVec& v0, const SseVec& v1)
	{
		static const SseVec VEC2_MASK = SetSseVecMask(0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x0);
		SseVec tmp = VecAnd(v0, VEC2_MASK);
		SseVec result = VecAdd(tmp, v1);

		return result;
	}

	/*!
	 * \brief	Adds two SseVecs representing Vec3s.
	 *
	 * \date	2/21/2015
	 *
	 * \param	v0	The first 3D vector.
	 * \param	v1	The second 3D vector.
	 *
	 * \return	The sum SseVec of the two original SseVecs.
	 */
	SSE_VEC_CALL Vec3Add(const SseVec& v0, const SseVec& v1)
	{
		static const SseVec VEC3_MASK = SetSseVecMask(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0);
		SseVec tmp = VecAnd(v0, VEC3_MASK);
		SseVec result = VecAdd(tmp, v1);

		return result;
	}
	
	/*!
	 * \brief	Subtracts two SseVecs representing Vec2s.
	 * 
	 * \date	2/21/2015
	 *
	 * \param	v0	The first 2D vector.
	 * \param	v1	The second 2D vector.
	 *
	 * \return	The difference SseVec of the two original SseVecs.
	 */
	SSE_VEC_CALL Vec2Sub(const SseVec& v0, const SseVec& v1)
	{
		static const SseVec VEC3_MASK = SetSseVecMask(0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x0);
		SseVec tmp = VecAnd(v1, VEC3_MASK);
		return VecSub(v0, tmp);
	}

	/*!
	 * \brief	Subtracts two SseVecs representing Vec3s.
	 * 
	 * \date	2/21/2015
	 *
	 * \param	v0	The first 3D vector.
	 * \param	v1	The second 3D vector.
	 *
	 * \return	The difference SseVec of the two original SseVecs.
	 */
	SSE_VEC_CALL Vec3Sub(const SseVec& v0, const SseVec& v1)
	{
		static const SseVec VEC3_MASK = SetSseVecMask(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0);
		SseVec tmp = VecAnd(v1, VEC3_MASK);
		return VecSub(v0, tmp);
	}

	/*!
	 * \brief	Multiplies two SseVecs representing Vec2s and then adds a third.
	 *
	 * \date	2/21/2015
	 *
	 * \param	v0	The first 2D vector.
	 * \param	v1	The second 2D vector.
	 * \param	v2	The third 2D vector.
	 *
	 * \return	The result of the multiplication of the first two vectors summed with the third.
	 */
	SSE_VEC_CALL Vec2MulAdd(const SseVec& v0, const SseVec& v1, const SseVec& v2)
	{
		SseVec tmp0 = VecMul(v0, v1);
		return VecAdd(tmp0, v2);
	}

	/*!
	 * \brief	Multiplies two SseVecs representing Vec3s then adds a third.
	 *
	 * \date	2/21/2015
	 *
	 * \param	v0	The first 3D vector.
	 * \param	v1	The second 3D vector.
	 * \param	v2	The third 3D vector.
	 *
	 * \return	The result of the multiplication of the first two vectors summed with the third.
	 */
	SSE_VEC_CALL Vec3MulAdd(const SseVec& v0, const SseVec& v1, const SseVec& v2)
	{
		SseVec tmp = VecMul(v0, v1);
		SseVec result = VecAdd(tmp, v2);

		return result;
	}

	/*!
	 * \brief	Multiplies two SseVecs representing Vec4s then adds a third.
	 *
	 * \date	2/21/2015
	 *
	 * \param	v0	The first 4D vector.
	 * \param	v1	The second 4D vector.
	 * \param	v2	The third 4D vector.
	 *
	 * \return	The result of the multiplication of the first two vectors summed with the third.
	 */
	SSE_VEC_CALL Vec4MulAdd(const SseVec& v0, const SseVec& v1, const SseVec& v2)
	{
		SseVec tmp = VecMul(v0, v1);
		return VecAdd(tmp, v2);
	}

	/*!
	 * \brief	Multiplies the given SseVec representing a Vec2 by the given scalar.
	 *
	 * \date	2/21/2015
	 *
	 * \param	v0	  	The 2D vector to be scaled.
	 * \param	scalar	The scalar to multiply against the vector.
	 *
	 * \return	The scaled form of the given 2D vector.
	 */
	SSE_VEC_CALL Vec2MulScalar(const SseVec& v0, float scalar)
	{
		SseVec s = SetSseVec2(scalar, scalar);
		return VecMul(v0, s);
	}

	/*!
	 * \brief	Multiplies the given SseVec representing a Vec3 by the given scalar.
	 *
	 * \date	2/21/2015
	 *
	 * \param	v0	  	The 3D vector to be scaled.
	 * \param	scalar	The scalar to multiply against the vector.
	 *
	 * \return	The scaled form of the given 3D vector.
	 */
	SSE_VEC_CALL Vec3MulScalar(const SseVec& v0, float scalar)
	{
		SseVec s = SetSseVec3(scalar, scalar, scalar);
		return VecMul(v0, s);
	}

	/*!
	 * \brief	Multiplies the given SseVec representing a Vec4 by the given scalar.
	 *
	 * \date	2/21/2015
	 *
	 * \param	v0	  	The 4D vector to be scaled.
	 * \param	scalar	The scalar to multiply against the vector.
	 *
	 * \return	The scaled form of the given 4D vector.
	 */
	SSE_VEC_CALL Vec4MulScalar(const SseVec& v0, float scalar)
	{
		SseVec s = SetSseVec4(scalar, scalar, scalar, scalar);
		return VecMul(v0, s);
	}

	/*!
	 * \brief	Calculates the normalized form of the given 2D vector.
	 *
	 * \date	2/21/2015
	 *
	 * \param	vec	The 2D vector to find the normalized form of.
	 *
	 * \return	The normalized form of the given 2D vector.
	 */
	SSE_VEC_CALL Vec2Normalize(const SseVec& vec)
	{
		SseVec tmp0;
		tmp0 = Vec2Dot(vec, vec);

		SseVec result = VecSqrt(tmp0);

		SseVec zeroMask = _mm_cmpnle_ps(result, EPSILON_1111);

		result = VecDiv(vec, result);

		result = VecAnd(zeroMask, result);
		return VecBlend<BlendOrder::LEFT, BlendOrder::LEFT, BlendOrder::RIGHT, BlendOrder::RIGHT>(result, UNIT_0001);
	}

	/*!
	 * \brief	Calculates the normalized form of the given 3D vector.
	 *
	 * \date	2/21/2015
	 *
	 * \param	vec	The 3D vector to find the normalized form of.
	 *
	 * \return	The normalized form of the given 3D vector.
	 */
	SSE_VEC_CALL Vec3Normalize(const SseVec& vec)
	{
		static const SseVec UNIT_0001 = SetSseVec4(0.0f, 0.0f, 0.0f, 1.0f);
		static const SseVec EPSILON_1111 = SetSseVec4(Epsilon());
		static const SseVec INFINITY_1111 = SetSseVec4(Infinity());

		SseVec tmp0;
		tmp0 = Vec3Dot(vec, vec);

		SseVec result = VecSqrt(tmp0);
		SseVec zeroMask = _mm_cmpnle_ps(result, EPSILON_1111);
		result = _mm_div_ps(vec, result);

		SseVec infMask = _mm_cmpneq_ps(result, INFINITY_1111);
		SseVec mask = VecAnd(zeroMask, infMask);

		result = VecAnd(mask, result);
		return VecBlend<BlendOrder::LEFT, BlendOrder::LEFT, BlendOrder::LEFT, BlendOrder::RIGHT>(result, UNIT_0001);
	}

	/*!
	 * \brief	Calculates the normalized form of the given 4D vector.
	 *
	 * \date	2/21/2015
	 *
	 * \param	vec	The 4D vector to find the normalized form of.
	 *
	 * \return	The normalized form of the given 4D vector.
	 */
	SSE_VEC_CALL Vec4Normalize(const SseVec& vec)
	{
		static const SseVec EPSILON_1111 = SetSseVec4(Epsilon());
		static const SseVec INFINITY_1111 = SetSseVec4(Infinity());

		SseVec tmp0;
		tmp0 = Vec4Dot(vec, vec);

		SseVec result = VecSqrt(tmp0);
		SseVec zeroMask = _mm_cmpnle_ps(result, EPSILON_1111);
		result = VecDiv(vec, result);

		SseVec infMask = _mm_cmpneq_ps(result, INFINITY_1111);
		SseVec mask = VecAnd(zeroMask, infMask);

		return VecAnd(mask, result);
	}

	/*!
	 * \brief	Calculates a fast approximation of the normalized form of a given 2D vector.
	 *
	 * \date	2/21/2015
	 *
	 * \param	vec	The 2D vector to find the approximate normalized form of.
	 *
	 * \return	The approimate normalized form of the given 2D vector.
	 *
	 * \remarks	Uses the fast inverse square root to approximate the normalized vector considerably
	 * 			more quickly, without losing a lot of accuracy.
	 */
	SSE_VEC_CALL FastVec2Normalize(const SseVec& vec)
	{
		SseVec tmp0;
		SseVec result;
		tmp0 = Vec3Dot(vec, vec);

		tmp0 = VecRSqrt(tmp0);
		result = VecMul(vec, tmp0);
		result = VecBlend<BlendOrder::LEFT, BlendOrder::LEFT, BlendOrder::LEFT, BlendOrder::RIGHT>(result, UNIT_0001);
		return result;
	}

	/*!
	 * \brief	Calculates a fast approximation of the normalized form of a given 3D vector.
	 *
	 * \date	2/21/2015
	 *
	 * \param	vec	The 3D vector to find the approximate normalized form of.
	 *
	 * \return	The approimate normalized form of the given 3D vector.
	 *
	 * \remarks	Uses the fast inverse square root to approximate the normalized vector considerably
	 * 			more quickly, without losing a lot of accuracy.
	 */
	SSE_VEC_CALL FastVec3Normalize(const SseVec& vec)
	{
		SseVec result;
		SseVec tmp0 = _mm_dp_ps(vec, vec, 0x7F);
		tmp0 = _mm_rsqrt_ps(tmp0);
		result = VecMul(vec, tmp0);
		result = VecBlend<BlendOrder::LEFT, BlendOrder::LEFT, BlendOrder::LEFT, BlendOrder::RIGHT>(result, UNIT_0001);

		return result;
	}

	/*!
	 * \brief	Calculates a fast approximation of the normalized form of a given 4D vector.
	 *
	 * \date	2/21/2015
	 *
	 * \param	vec	The 4D vector to find the approximate normalized form of.
	 *
	 * \return	The approimate normalized form of the given 4D vector.
	 *
	 * \remarks	Uses the fast inverse square root to approximate the normalized vector considerably
	 * 			more quickly, without losing a lot of accuracy.
	 */
	SSE_VEC_CALL FastVec4Normalize(const SseVec& vec)
	{
		SseVec tmp0 = _mm_dp_ps(vec, vec, 0xFF);
		tmp0 = _mm_rsqrt_ps(tmp0);
		return VecMul(vec, tmp0);
	}

	/*!
	 * \brief	Calculates the cross product of the two given 3D vectors.
	 *
	 * \date	2/21/2015
	 *
	 * \param	v0	The first 3D vector in the cross product.
	 * \param	v1	The second 3D vector in the cross product.
	 *
	 * \return	The cross product of the two given 3D vectors.
	 */
	SSE_VEC_CALL Vec3Cross(const SseVec& v0, const SseVec& v1)
	{
		SseVec tmp0, tmp1, tmp2, tmp3;
		SseVec result;

		tmp0 = VecSwizzle<VecCoord::Y, VecCoord::Z, VecCoord::X, VecCoord::NA>(v0);
		tmp1 = VecSwizzle<VecCoord::Z, VecCoord::X, VecCoord::Y, VecCoord::NA>(v1);
		tmp2 = VecSwizzle<VecCoord::Z, VecCoord::X, VecCoord::Y, VecCoord::NA>(v0);
		tmp3 = VecSwizzle<VecCoord::Y, VecCoord::Z, VecCoord::X, VecCoord::NA>(v1);

		tmp0 = VecMul(tmp0, tmp1);
		tmp2 = VecMul(tmp2, tmp3);

		result = VecSub(tmp0, tmp2);
		result = VecOr(result, UNIT_0001);

		return result;
	}

	/*!
	 * \brief	Normalizes the given angles (assumed radians) to (-PI,PI).
	 *
	 * \date	2/21/2015
	 *
	 * \param	angles	The angles (assumed radians).
	 *
	 * \return	A SSE_VEC_CALL.
	 */
	SSE_VEC_CALL NormalizeAngles(const SseVec& angles)
	{
		SseVec tmp0, tmp1;

		tmp0 = VecAdd(angles, F_PI_1111);
		tmp0 = VecMul(tmp0, F_1_2PI_1111);
		tmp1 = _mm_floor_ps(tmp0);
		tmp0 = VecMul(F_2PI_1111, tmp1);
		tmp0 = VecSub(angles, tmp0);

		return tmp0;
	}

	/*!
	 * \brief	Calculates a fast approximation of the cosine of the various angles in the given
	 * 			column vector.
	 *
	 * \date	2/21/2015
	 *
	 * \param	angles	The angles in radians.
	 *
	 * \return	A column vector containing the respective calculated cosine approximations from the
	 * 			angles in the original column vector.
	 *
	 * \remarks	Approximates the cosine of the given angles within an error of about 0.001.
	 */
	SSE_VEC_CALL FastCosSseVec(const SseVec& angles)
	{
		static const SseVec F_9_40_1111 = SetSseVec4(0.225f);
		SseVec tmp0, tmp1;
		tmp0 = VecAdd(angles, F_PI_2_1111);
		tmp0 = NormalizeAngles(tmp0);

		tmp1 = Vec4Abs(tmp0);
		tmp1 = VecMul(tmp1, tmp0);
		tmp0 = VecMul(tmp0, F_4_PI_1111);
		tmp1 = VecMul(tmp1, F_NEG4_PI2_1111);
		tmp0 = VecAdd(tmp0, tmp1);

		tmp1 = Vec4Abs(tmp0);
		tmp1 = VecMul(tmp1, tmp0);
		tmp1 = VecSub(tmp1, tmp0);
		tmp1 = VecMul(tmp1, F_9_40_1111);
		tmp0 = VecAdd(tmp0, tmp1);

		return tmp0;
	}

	/*!
	 * \brief	Calculates a fast approximation of the sine of the various angles in the given column
	 * 			vector.
	 *
	 * \date	2/21/2015
	 *
	 * \param	angles	The angles in radians.
	 *
	 * \return	A column vector containing the respective calculated sine approximations from the
	 * 			angles in the original column vector.
	 *
	 * \remarks	Approximates the sine of the given angles within an error of about 0.001.
	 */
	SSE_VEC_CALL FastSinSseVec(const SseVec& angles)
	{
		static const SseVec F_9_40_1111 = SetSseVec4(0.225f);

		SseVec tmp0, tmp1, norm;
		norm = NormalizeAngles(angles);
		tmp1 = Vec4Abs(norm);
		tmp1 = VecMul(tmp1, norm);
		tmp0 = VecMul(norm, F_4_PI_1111);
		tmp1 = VecMul(tmp1, F_NEG4_PI2_1111);
		tmp0 = VecAdd(tmp0, tmp1);

		tmp1 = Vec4Abs(tmp0);
		tmp1 = VecMul(tmp1, tmp0);
		tmp1 = VecSub(tmp1, tmp0);
		tmp1 = VecMul(tmp1, F_9_40_1111);
		tmp0 = VecAdd(tmp0, tmp1);

		return tmp0;
	}

	/*!
	 * \brief	Calculates a rougher (but generally much faster) approximation of the sine and/or
	 * 			cosine of the various angles in the given column vector.
	 *
	 * \date	2/21/2015
	 * 
	 * \tparam	xFlag The x-coordinate index
	 * \tparam	yFlag The y-coordinate index
	 * \tparam	zFlag The z-coordinate index
	 * \tparam	wFlag The w-coordinate index
	 * 
	 * \param	angles	The angles in radians.
	 *
	 * \return	A column vector containing the respective calculated sine and/or cosine
	 * 			approximations from the angles in the original column vector.
	 *
	 * \remarks	Approximates the sine of the given angles using a parabolic approximation.  Is
	 * 			generally "accurate enough" and will more often than not run considerably faster than
	 * 			the Taylor approximation.
	 * 			
	 * 			This function generally calculates within 0.001 radians of the standard sine and
	 * 			cosine functions.
	 */
	template<SinCosFlag xFlag, SinCosFlag yFlag, SinCosFlag zFlag, SinCosFlag wFlag>
	SSE_VEC_CALL FastSinCosSseVec(const SseVec& angles)
	{
		static const SseVec F_9_40_1111 = SetSseVec4(0.225f);
		SseVec tmp0, tmp1;
		tmp0 = VecAdd(angles, F_PI_2_1111);
		tmp0 = VecSinCosBlend<xFlag, yFlag, zFlag, wFlag>(angles, tmp0);
		tmp0 = NormalizeAngles(tmp0);

		tmp1 = Vec4Abs(tmp0);
		tmp1 = VecMul(tmp1, tmp0);
        tmp0 = VecMul(tmp0, F_4_PI_1111);
        tmp1 = VecMul(tmp1, F_NEG4_PI2_1111);
		tmp0 = VecAdd(tmp0, tmp1);

		tmp1 = Vec4Abs(tmp0);
        tmp1 = VecMul(tmp1, tmp0);
		tmp1 = VecSub(tmp1, tmp0);
		tmp1 = VecMul(tmp1, F_9_40_1111);
		tmp0 = VecAdd(tmp0, tmp1);

		return tmp0;
	}
	
	/*!
	 * \brief	Calculates an approximation of the cosine of the various angles in the given column
	 * 			vector.
	 *
	 * \date	2/21/2015
	 *
	 * \tparam	precisionLevel	Type of the precision level.
	 * \param	angles	The angles in radians.
	 *
	 * \return	A column vector containing the respective calculated cosine approximations from the
	 * 			angles in the original column vector.
	 *
	 * \remarks	Approximates the cosine of the given angles using a taylor aproximation with a
	 * 			variable number of iterations.
	 * 			
	 * 			It is usually more accurate than FastCosSseVec, though it also ranges significantly
	 * 			in relative computational complexity.  At lower levels of precision, it can be only
	 * 			very slightly more expensive than the fast version, but at its highest precision
	 * 			levels, it is quite a bit more expensive.
	 */
	template<FloatPrecision precisionLevel = FloatPrecision::HIGH>
	SSE_VEC_CALL CosSseVec(const SseVec& angles)
	{
		SseVec tmp0, tmp1, tmp2, norm;

		static const size_t PRECISION = TrigPrecisionValue<precisionLevel>();

		norm = NormalizeAngles(angles);

		tmp1 = VecMul(norm, norm);
		tmp2 = VecMul(tmp1, CosCoefSseVec(PRECISION));

		for (size_t i = PRECISION - 1; i-- > 0;)
		{
			tmp2 = VecAdd(tmp2, CosCoefSseVec((int)i));
			tmp2 = VecMul(tmp1, tmp2);
		}

		tmp0 = VecAdd(tmp2, SSE_VEC_ONE);

		return tmp0;
	}

	/*!
	 * \brief	Calculates an approximation of the sine of the various angles in the given column
	 * 			vector.
	 *
	 * \date	2/21/2015
	 *
	 * \tparam	precisionLevel	Type of the precision level.
	 * \param	angles	The angles in radians.
	 *
	 * \return	A column vector containing the respective calculated sine approximations from the
	 * 			angles in the original column vector.
	 *
	 * \remarks	Approximates the sine of the given angles using a taylor aproximation with a variable
	 * 			number of iterations.
	 * 			
	 * 			It is usually more accurate than FastSinSseVec, though it also ranges significantly
	 * 			in relative computational complexity.  At lower levels of precision, it can be only
	 * 			very slightly more expensive than the fast version, though the fast version is
	 * 			typically more accurate at these levels, anyway, but at its highest precision levels,
	 * 			it is quite a bit more expensive, but also quite a bit more accurate.
	 */
	template<FloatPrecision precisionLevel = FloatPrecision::HIGH>
	SSE_VEC_CALL SinSseVec(const SseVec& angles)
	{
		SseVec tmp0 = VecSub(angles, F_PI_2_1111);

		return CosSseVec<precisionLevel>(tmp0);
	}

	/*!
	 * \brief	Calculates an approximation of the sine and/or cosine of the various angles in the
	 * 			given column vector.
	 *
	 * \date	2/21/2015
	 * 
	 * \tparam	xFlag		  	The SinCosFlag used to decide between calculating the sine or the cosine 
	 *							for the x-coordinate of the given SseVec containing the angles.
	 * 
	 * \tparam	yFlag		  	The SinCosFlag used to decide between calculating the sine or the cosine 
	 *							for the y-coordinate of the given SseVec containing the angles.
	 * 
	 * \tparam	zFlag		  	The SinCosFlag used to decide between calculating the sine or the cosine 
	 *							for the z-coordinate of the given SseVec containing the angles.
	 * 
	 * \tparam	wFlag		  	The SinCosFlag used to decide between calculating the sine or the cosine 
	 *							for the w-coordinate of the given SseVec containing the angles.
	 * 
	 * \tparam	precisionLevel	Level of precision to use in the approximation.
	 * 
	 * \param	angles	The angles in radians.
	 *
	 * \return	A column vector containing the respective calculated sine and/or cosine
	 * 			approximations from the angles in the original column vector.
	 *
	 * \remarks	Approximates the sine and/or cosine of the given angles using a Taylor approximation
	 * 			with a variable number of iterations (depending on the FloatPrecision template
	 * 			setting used to call it).
	 * 
	 * 			It is usually more accurate than FastSinCosSseVec, though it becomes relatively more
	 *			expensive as the precision level is raised.  At lower levels of precision, it
	 * 			can be only very slightly more expensive than the fast version, though the fast
	 * 			version is typically more accurate at these levels, anyway. At its highest
	 * 			precision levels, however, it is quite a bit more expensive, but also quite a bit more
	 * 			accurate.
	 */
    template<SinCosFlag xFlag, SinCosFlag yFlag, SinCosFlag zFlag, SinCosFlag wFlag, FloatPrecision precisionLevel = FloatPrecision::HIGH>
	SSE_VEC_CALL SinCosSseVec(const SseVec& angles)
	{
		SseVec tmp0;
		tmp0 = VecSub(angles, F_PI_2_1111);

		tmp0 = VecSinCosBlend<xFlag, yFlag, zFlag, wFlag>(tmp0, angles);
		return CosSseVec<precisionLevel>(tmp0);
	}
	
	/*!
	 * \brief	Multiplies the two given SseVecs representing unit quaternions, then returns another
	 * 			unit quaternion.
	 * 
	 * \date	2/21/2015
	 *
	 * \param	quat0	The first quaternion SseVec.
	 * \param	quat1	The second quaternion SseVec.
	 *
	 * \return	The product unit quaternion of the two given unit quaternions.
	 */
	inline SseVec QuaternionMultiply(const SseVec& quat0, const SseVec& quat1)
	{
		SseVec tmp0, tmp1, tmp2, tmp3;

		//w0x1 + x0w1 + y0z1 - z0y1
		//w0y1 + y0w1 + x0z1 - z0x1
		//w0z1 + z0w1 + x0y1 - y0x1
		//w0w1 - x0x1 - y0y1 - z0z1

		tmp0 = VecSplat<VecCoord::W>(quat0);// w0 w0 w0 w0
		tmp0 = VecMul(tmp0, quat1);// w0x1 w0y1 w0z1 w0w1

		tmp1 = VecSwizzle<VecCoord::X, VecCoord::Y, VecCoord::Z, VecCoord::X>(quat0);// x0 y0 z0 x0
		tmp2 = VecSwizzle<VecCoord::W, VecCoord::W, VecCoord::W, VecCoord::X>(quat1);// w1 w1 w1 x1
		tmp1 = VecMul(tmp1, tmp2);// x0w1 y0w1 z0w1 x0x1

		tmp2 = VecSwizzle<VecCoord::Y, VecCoord::X, VecCoord::X, VecCoord::Y>(quat0);// y0 x0 x0 y0
		tmp3 = VecSwizzle<VecCoord::Z, VecCoord::Z, VecCoord::Y, VecCoord::Y>(quat1);// z1 z1 y1 y1
		tmp2 = VecMul(tmp2, tmp3);// y0z1 x0z1 x0y1 y0y1

		tmp1 = VecAdd(tmp1, tmp2);// (x0w1 + y0z1) (y0w1 + x0z1) (z0w1 + x0y1) (x0x1 + y0y1)
		tmp1 = Vec4Negate<false, false, false, true>(tmp1);// (x0w1 + y0z1) (y0w1 + x0z1) (z0w1 + x0y1) -(x0x1 + y0y1)

		tmp0 = VecAdd(tmp0, tmp1);// (w0x1 + x0w1 + y0z1) (w0y1 + y0w1 + x0z1) (w0z1 + z0w1 + x0y1) (w0w1 - x0x1 - y0y1)

		tmp1 = VecSwizzle<VecCoord::Z, VecCoord::Z, VecCoord::Y, VecCoord::Z>(quat0);// z0 z0 y0 z0
		tmp2 = VecSwizzle<VecCoord::Y, VecCoord::X, VecCoord::X, VecCoord::Z>(quat1);// y1 x1 x1 z1
		tmp1 = VecMul(tmp1, tmp2);// z0y1 z0x1 y0x1 z0z1

		return VecSub(tmp0, tmp1);// (w0x1 + x0w1 + y0z1 - z0y1) (w0y1 + y0w1 + x0z1 - z0x1) (w0z1 + z0w1 + x0y1 - y0x1) (w0w1 - x0x1 - y0y1 - z0z1)
	}

	/*!
	 * \brief	Produces a quaternion representation of the given axis-angle rotation.
	 *
	 * \date	2/21/2015
	 *
	 * \param	axisVec	The axis vec.
	 * \param	angle  	The angle.
	 *
	 * \return	The quaternion representation of the given axis-angle rotation.
	 */
	SSE_VEC_CALL QuaternionFromAxisAngle(const SseVec& axisVec, float angle)
	{
		SseVec tmp0;
		tmp0 = SetSseVec4(angle*0.5f);
		tmp0 = SinCosSseVec<SinCosFlag::SIN, SinCosFlag::SIN, SinCosFlag::SIN, SinCosFlag::COS>(tmp0);

		SseVec result = Vec3Normalize(axisVec);
		return VecMul(result, tmp0);
	}

	/*!
	 * \brief	Generates a quick approximation of the quaternion representing the given axis-angle.
	 *
	 * \date	2/21/2015
	 *
	 * \param	axisVec	The axis vec.
	 * \param	angle  	The angle.
	 *
	 * \return	A quick approximation of the quaternion representing the given axis-angle.
	 */
	SSE_VEC_CALL FastQuaternionFromAxisAngle(const SseVec& axisVec, float angle)
	{
		SseVec tmp0;
		tmp0 = SetSseVec4(angle*0.5f);
		tmp0 = SinCosSseVec<SinCosFlag::SIN, SinCosFlag::SIN, SinCosFlag::SIN, SinCosFlag::COS>(tmp0);

		SseVec result = FastVec3Normalize(axisVec);
		return VecMul(result, tmp0);
	}

	/*!
	 * \brief	Linearly interpolates between the two given quaternion SseVecs by the given
	 * 			interpolation weight.
	 *
	 * \date	2/21/2015
	 *
	 * \param	start 	The start.
	 * \param	end   	The end.
	 * \param	weight	The weight.
	 *
	 * \return	The quaternion between the two given quaternions that is reached by the given weight.
	 */
	SSE_VEC_CALL QuaternionLerp(const SseVec& start, const SseVec& end, float weight)
	{
		static const SseVec NEGATE_MASK_1111 = SetSseVecMask(0x80000000, 0x80000000, 0x80000000, 0x80000000);
		SseVec tmp0, tmp1, tmp2;
		SseVec result;
		SseVec weightVecEnd = SetSseVec4(weight);
		SseVec weightVecStart = SetSseVec4(1.0f - weight);

		tmp0 = Vec4Dot(start, end);
		tmp1 = VecAnd(tmp0, NEGATE_MASK_1111);
		tmp1 = VecXOr(end, tmp1);
		tmp2 = VecMul(weightVecStart, start);
		tmp1 = VecMul(weightVecEnd, tmp1);

		result = VecAdd(tmp1, tmp2);

		result = Vec4Normalize(result);

		return result;
	}

	/*!
	 * \brief	Approximates the linear interpolation between the two given quaternion SseVecs by the
	 * 			given interpolation weight.
	 *
	 * \date	2/21/2015
	 *
	 * \param	start 	The start.
	 * \param	end   	The end.
	 * \param	weight	The weight.
	 *
	 * \return	The approximate quaternion between the two given quaternions that is reached by the
	 * 			given weight.
	 */
	SSE_VEC_CALL FastQuaternionLerp(const SseVec& start, const SseVec& end, float weight)
	{
		static const SseVec SIGN_MASK_1111 = SetSseVecMask(0x80000000, 0x80000000, 0x80000000, 0x80000000);

		SseVec tmp0, tmp1, tmp2;
		SseVec result;
		SseVec weightVecEnd = SetSseVec4(weight);
		SseVec weightVecStart = SetSseVec4(1.0f - weight);

		tmp0 = Vec4Dot(start, end);
		tmp1 = VecAnd(tmp0, SIGN_MASK_1111);
		tmp1 = VecXOr(end, tmp1);
		tmp2 = VecMul(weightVecStart, start);
		tmp1 = VecMul(weightVecEnd, tmp1);

		result = VecAdd(tmp1, tmp2);

		return FastVec4Normalize(result);
	}

	/*!
	 * \brief	Converts the given euler angles to a quaternion.
	 *
	 * \date	2/21/2015
	 *
	 * \tparam	precisionLevel	Type of the precision level.
	 * \param	angles	The angles (in radians).
	 *
	 * \return	A quaternion representing the given euler angles.
	 */
	template<FloatPrecision precisionLevel = FloatPrecision::HIGH>
	SSE_VEC_CALL QuaternionFromEuler(const SseVec& angles)
	{
		static const SseVec HALF = SetSseVec4(0.5f);

		SseVec tmp0, tmp1, tmp2, tmp3, tmp4, tmp5;
		SseVec sinCosXY, sinCosZW;
		SseVec result;

		tmp0 = VecMul(HALF, angles);// x/2 y/2 z/2 w/2
		tmp1 = CosSseVec<precisionLevel>(tmp0);// cx cy cz cw
		tmp0 = SinSseVec<precisionLevel>(tmp0);// sx sy sz sw

		tmp1 = VecSwizzle<VecCoord::NA, VecCoord::Z, VecCoord::Y, VecCoord::X>(tmp1);// na cz cy cx
		tmp2 = VecBlend<BlendOrder::LEFT, BlendOrder::LEFT, BlendOrder::LEFT, BlendOrder::RIGHT>(tmp0, tmp1);// sx sy sz cx

		tmp1 = VecSwizzle<VecCoord::NA, VecCoord::Y, VecCoord::W, VecCoord::Z>(tmp1);// na cz cx cy
		tmp3 = VecBlend<BlendOrder::LEFT, BlendOrder::LEFT, BlendOrder::LEFT, BlendOrder::RIGHT>(tmp0, tmp1);// sx sy sz cy

		tmp1 = VecSwizzle<VecCoord::NA, VecCoord::Z, VecCoord::W, VecCoord::Y>(tmp1);// na cx cy cz
		tmp4 = VecBlend<BlendOrder::LEFT, BlendOrder::LEFT, BlendOrder::LEFT, BlendOrder::RIGHT>(tmp0, tmp1);// sx sy sz cz

		tmp2 = VecAnd(tmp2, MASK_1001);// sx 0  0  cx
		tmp3 = VecAnd(tmp3, MASK_0101);// 0  sy 0  cy
		tmp4 = VecAnd(tmp4, MASK_0011);// 0  0  sz cz

		result = QuaternionMultiply(tmp3, tmp2);
		result = QuaternionMultiply(result, tmp4);

		return result;
	}

	/*!
	* \brief	Converts the given euler angles to a quaternion.
	*
	* \date	2/21/2015
	*
	* \tparam	precisionLevel	Type of the precision level.
	* 
	* \param	pitch	The angle (in radians) to rotate along the x-axis.
	* \param   yaw		The angle (in radians) to rotate along the y-axis.
	* \param	roll	The angle (in radians) to rotate along the z-axis.
	*
	* \return	A quaternion representing the given euler angles.
	*/
	template<FloatPrecision precisionLevel = FloatPrecision::HIGH>
	SSE_VEC_CALL SseQuaternionFromEuler(float pitch, float yaw, float roll)
	{
		return QuaternionFromEuler<precisionLevel>(SetSseVec3(pitch, yaw, roll));
	}

	/*! @} */
}

#endif // SSE_VEC_DOT_H