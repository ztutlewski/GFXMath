#ifndef SSE_MAT44_DOT_H
#define SSE_MAT44_DOT_H
#include "gfxmath_config.h"
#include "ssemat_math_defs.h"
#include "ssevec_math_defs.h"
#include "ssevec.h"
#include "mat44.h"
#include "scalar_math.h"
#include "sisd_defns.h"
#include <array>

/*!
 * \file 
 */

/*!
 * \defgroup SIMDMatMath SIMD Matrix Math
 */

/*!
 * \namespace	gfxmath
 *
 * \brief	G of F of X math namespace.
 */
namespace gfxmath
{
	/*!
	 * \ingroup SIMDMatMath
	 * @{
	 */

	/*!
	 * \class SseMat44
	 *
	 * \brief	A 4x4 column-major matrix that uses four SseVecs for column vectors.
	 * 	
	 *
	 * \return	The SSE matrix 44.
     * 
     * 
     * \remarks This class is used to take advantage of sse intrinsics for substantial performance
	 * 			gains in cpu-heavy rendering calculations.
	 */
	ALIGNED_CLASS(16) SseMat44
	{
	public:	
		MatrixType matrixTypeVal;/*!< A MatrixType used to track the matrix state.
								 *	\sa MatrixType
								 */

		SseVec col0;/*!< The first column vector
					 *	 \sa SseVec
					 */

		SseVec col1;/*!< The second column vector
					 *	 \sa SseVec
					 */

		SseVec col2;/*!< The third column vector
					 *	 \sa SseVec
					 */

		SseVec col3;/*!< The fourth column vector
					 *	 \sa SseVec
					 */

		/*!
		 * \brief	Empty SseMat44 constructor.
		 *
		 * \date	2/21/2015
		 * 			
		 * \remarks Sets all member columns to zerovectors,
		 * 		    and sets the matrixTypeVal to MatrixType::MISC.
		 */
		SseMat44() : 
			col0(_mm_setzero_ps()), 
			col1(_mm_setzero_ps()), 
			col2(_mm_setzero_ps()), 
			col3(_mm_setzero_ps()), 
			matrixTypeVal(MatrixType::MISC)  {}

		/*!
		 * \brief SseMat44 constructor that takes SseVec arguments to fill the columns,
		 * 		  and an optional MatrixType argument to initialize its state.
		 *
		 * \date	2/21/2015
         * 
         * \param	v0	 	An SseVec that will be placed in the first column.
		 * \param	v1	 	An SseVec that will be placed in the second column.
		 * \param	v2	 	An SseVec that will be placed in the third column.
		 * \param	v3	 	An SseVec that will be placed in the fourth column.
		 * \param	matrixTypeVal	The matrix type value.  Defaults as MatrixType::MISC
		 * 
		 * \remarks Sets its respective column vectors to the given SseVec arguments, 
		 * 			and optionally sets the matrixTypeVal to the given MatrixType
		 * 			(defaults to MatrixType::MISC)
		 */
		SseMat44(const SseVec& v0, const  SseVec& v1, const SseVec& v2, const SseVec& v3, MatrixType matrixTypeVal = MatrixType::MISC) :
			col0(v0), 
			col1(v1), 
			col2(v2), 
			col3(v3), 
			matrixTypeVal(matrixTypeVal) {}

		/*!
		 * \brief SseMat44 constructor that takes Vec4 arguments to fill the columns,
		 * 		  and an optional MatrixType argument to initialize its state.
		 * 
		 * \remarks	Sets its respective column vectors to the given SseVec arguments, and optionally sets
		 * 			the matrixTypeVal to the given MatrixType (defaults to MatrixType::MISC)
		 *
		 * \date	2/21/2015
		 *
		 * \param	col0Param	 	A Vec4 that will be placed in the first column.
		 * \param	col1Param	 	A Vec4 that will be placed in the second column.
		 * \param	col2Param	 	A Vec4 that will be placed in the third column.
		 * \param	col3Param	 	A Vec4 that will be placed in the fourth column.
		 * \param	matrixTypeVal	The matrix type value.  Defaults as MatrixType::MISC
		 *
		 */
		SseMat44(const Vec4& col0Param, const Vec4& col1Param, const Vec4& col2Param, const Vec4& col3Param, MatrixType matrixTypeVal = MatrixType::MISC) :
			col0(LoadSseVec4(col0Param)),
			col1(LoadSseVec4(col1Param)),
			col2(LoadSseVec4(col2Param)),
			col3(LoadSseVec4(col3Param)),
			matrixTypeVal(matrixTypeVal) {}

		/*!
		 * \brief	An SseMat44 constructor that takes 16 floats.
		 * 			
		 * \remarks Each four floats correspond to the columns of the resulting matrix.
		 * 
		 * \date	2/21/2015
		 *
		 * \param	f00			 	The column 0, row 0 value.
		 * \param	f10			 	The column 0, row 1 value.
		 * \param	f20			 	The column 0, row 2 value.
		 * \param	f30			 	The column 0, row 3 value.
		 * 							
		 * \param	f01			 	The column 1, row 0 value.
		 * \param	f11			 	The column 1, row 1 value.
		 * \param	f21			 	The column 1, row 2 value.
		 * \param	f31			 	The column 1, row 3 value.
		 * 							
		 * \param	f02			 	The column 2, row 0 value.
		 * \param	f12			 	The column 2, row 1 value.
		 * \param	f22			 	The column 2, row 2 value.
		 * \param	f32			 	The column 2, row 3 value.
		 * 							
		 * \param	f03			 	The column 3, row 0 value.
		 * \param	f13			 	The column 3, row 1 value.
		 * \param	f23			 	The column 3, row 2 value.
		 * \param	f33			 	The column 3, row 3 value.
		 * \param	matrixTypeVal	The matrix type value.
		 */
		SseMat44(float f00, float f10, float f20, float f30,
				 float f01, float f11, float f21, float f31,
				 float f02, float f12, float f22, float f32,
				 float f03, float f13, float f23, float f33,
				 MatrixType matrixTypeVal = MatrixType::MISC) :
				 col0(SetSseVec4(f00, f10, f20, f30)),
				 col1(SetSseVec4(f01, f11, f21, f31)),
				 col2(SetSseVec4(f02, f12, f22, f32)),
				 col3(SetSseVec4(f03, f13, f23, f33)),
				 matrixTypeVal(matrixTypeVal) {}

		/*!
		 * \brief	A conversion constructor from Mat44 to SseMat44.
		 *
		 * \date	2/21/2015
		 *
		 * \param [in,out]	mat	The Mat44 matrix to copy from.
         * 
         * \remarks Copies the values from the given Mat44 columns into the columns for this SseMat44,
		 * 			and sets the matrixTypeVal to the corresponding matrixTypeVal from the Mat44 passed in.
		 */
		SseMat44(Mat44& mat) :
			col0(SetSseVec4(mat.col0.w, mat.col0.x, mat.col0.y, mat.col0.z)),
			col1(SetSseVec4(mat.col1.w, mat.col1.x, mat.col1.y, mat.col1.z)),
			col2(SetSseVec4(mat.col2.w, mat.col2.x, mat.col2.y, mat.col2.z)),
			col3(SetSseVec4(mat.col3.w, mat.col3.x, mat.col3.y, mat.col3.z)),
			matrixTypeVal(mat.matrixTypeVal) {}

		static const SseMat44 IDENTITY; /*!< The identity matrix */
	};

	/*!
	 * \brief Converts the given 4x4 matrix to an array of floats.
	 * 
	 * \date	2/21/2015
	 *
	 * \param	mat	The matrix to convert to an array.
	 *
	 * \return	The array of floats representing the given 4x4 matrix.
	 *
	 * \relatedalso gfxmath::SseMat44
	 */
	inline std::array<float, 16>  MatrixToArray(const SseMat44& mat)
	{
		std::array<float, 16> result;

		_mm_storel_pi((__m64*)(result.data()), mat.col0);//		 m00 m10
		_mm_storeh_pi((__m64*)(result.data() + 2), mat.col0);//  m00 m10 m20 m30 |

		_mm_storel_pi((__m64*)(result.data() + 4), mat.col1);//  m00 m10 m20 m30 | m01 m11 
		_mm_storeh_pi((__m64*)(result.data() + 6), mat.col1);//  m00 m10 m20 m30 | m01 m11 m21 m31 |

		_mm_storel_pi((__m64*)(result.data() + 8), mat.col2);//  m00 m10 m20 m30 | m01 m11 m21 m31 | m02 m12
		_mm_storeh_pi((__m64*)(result.data() + 10), mat.col2);// m00 m10 m20 m30 | m01 m11 m21 m31 | m02 m12 m22 m32 |

		_mm_storel_pi((__m64*)(result.data() + 12), mat.col3);// m00 m10 m20 m30 | m01 m11 m21 m31 | m02 m12 m22 m32 | m03 m13
		_mm_storeh_pi((__m64*)(result.data() + 14), mat.col3);// m00 m10 m20 m30 | m01 m11 m21 m31 | m02 m12 m22 m32 | m03 m13 m23 m33

		return result;
	}

	/*!
	 * \brief Calculates the product (post-multiplication) of the two given 4x4 matrices.
	 * 
	 * \date	2/21/2015
	 *
	 * \param	left 	The left matrix.
	 * \param	right	The right matrix.
	 *
	 * \return	The post-multiplied product of the two matrices.
	 *
	 * \relatedalso gfxmath::SseMat44
	 */
	SSE_MAT_CALL MatrixMultiply(const SseMat44& left, const SseMat44& right)
	{
		SseVec tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, leftCol0, leftCol1, leftCol2, leftCol3, res0, res1, res2, res3;

		// Load all the result registers with the columns of the 
		// first matrix
		res0 = right.col0;
		res1 = right.col1;
		res2 = right.col2;
		res3 = right.col3;

		// Load all the temporary second column registers with the 
		// columns from the second matrix
		leftCol0 = left.col0;
		leftCol1 = left.col1;
		leftCol2 = left.col2;
		leftCol3 = left.col3;

		// Splat all the members from the first and second column
		// of the first matrix into registers for multiplication.
		tmp0 = VecSplat<VecCoord::X>(res0);
		tmp1 = VecSplat<VecCoord::Y>(res0);
		tmp2 = VecSplat<VecCoord::Z>(res0);
		res0 = VecSplat<W>(res0);

		tmp3 = VecSplat<VecCoord::X>(res1);
		tmp4 = VecSplat<VecCoord::Y>(res1);
		tmp5 = VecSplat<VecCoord::Z>(res1);
		res1 = VecSplat<W>(res1);

		// Multiply the two groups of splatted columns by
		// the columns of the second matrix
		tmp0 = VecMul(leftCol0, tmp0);
		tmp1 = VecMul(leftCol1, tmp1);
		tmp2 = VecMul(leftCol2, tmp2);
		res0 = VecMul(leftCol3, res0);

		tmp3 = VecMul(leftCol0, tmp3);
		tmp4 = VecMul(leftCol1, tmp4);
		tmp5 = VecMul(leftCol2, tmp5);
		res1 = VecMul(leftCol3, res1);

		// Add the products of the first multiplication 
		// into the first two result registers
		tmp0 = VecAdd(tmp0, tmp1);
		res0 = VecAdd(tmp2, res0);
		res0 = VecAdd(res0, tmp0);

		tmp3 = VecAdd(tmp3, tmp4);
		res1 = VecAdd(res1, tmp5);
		res1 = VecAdd(res1, tmp3);

		// Splat all the members from the third and fourth column
		// of the first matrix into registers for multiplication.
		tmp0 = VecSplat<VecCoord::X>(res2);
		tmp1 = VecSplat<VecCoord::Y>(res2);
		tmp2 = VecSplat<VecCoord::Z>(res2);
		res2 = VecSplat<W>(res2);

		tmp3 = VecSplat<VecCoord::X>(res3);
		tmp4 = VecSplat<VecCoord::Y>(res3);
		tmp5 = VecSplat<VecCoord::Z>(res3);
		res3 = VecSplat<W>(res3);

		// Multiply the two groups of splatted columns by
		// the columns of the second matrix, again
		tmp0 = VecMul(leftCol0, tmp0);
		tmp1 = VecMul(leftCol1, tmp1);
		tmp2 = VecMul(leftCol2, tmp2);
		res2 = VecMul(leftCol3, res2);

		tmp3 = VecMul(leftCol0, tmp3);
		tmp4 = VecMul(leftCol1, tmp4);
		tmp5 = VecMul(leftCol2, tmp5);
		res3 = VecMul(leftCol3, res3);

		// Add the products of the second multiplication 
		// into the second two result registers
		tmp0 = VecAdd(tmp0, tmp1);
		res2 = VecAdd(tmp2, res2);
		res2 = VecAdd(res2, tmp0);

		tmp3 = VecAdd(tmp3, tmp4);
		res3 = VecAdd(res3, tmp5);
		res3 = VecAdd(res3, tmp3);

		SseMat44 result(res0, res1, res2, res3);
		result.matrixTypeVal = (MatrixType)(left.matrixTypeVal | right.matrixTypeVal);
		return result;
	}

	/*!
	 * \brief Calculates the inverse of the given 4x4 matrix.
	 * 
	 * \date	2/21/2015
	 *
	 * \param	mat	The matrix to invert.
	 *
	 * \return	The inverse of the given matrix.
	 *
	 * \relatedalso gfxmath::SseMat44
	 */
	SSE_MAT_CALL MatrixInverse(const SseMat44& mat)
	{
		SseVec tmp0, tmp1, tmp2, tmp3;
		SseVec col0, col1, col2, col3;
		SseVec minor0, minor1, minor2, minor3;
		SseVec det;

		// 00 01 02 03
		// 10 11 12 13
		// 20 21 22 23
		// 30 31 32 33

		// Load the registers
		col0 = mat.col0;
		col1 = mat.col1;
		col2 = mat.col2;
		col3 = mat.col3;

		col1 = VecSwizzle<VecCoord::Z, W, X, Y>(col1);//  2 3 0 1
		col3 = VecSwizzle<VecCoord::Z, W, X, Y>(col3);// 2 3 0 1

		// Calculate Cofactors
		// 1 -----------------------------------------------
		tmp2 = VecMul(col2, col3);
		tmp0 = VecSwizzle<VecCoord::Y, X, W, Z>(tmp2);// 1 0 3 2
		tmp1 = VecSwizzle<W, Z, Y, X>(tmp2);// 3 2 1 0

		minor0 = VecMul(col1, tmp0);
		minor1 = VecMul(col0, tmp0);

		tmp2 = VecMul(col1, tmp1);
		tmp1 = VecMul(col0, tmp1);
		minor0 = VecSub(tmp2, minor0);
		minor1 = VecSub(tmp1, minor1);

		// 2 -----------------------------------------------

		tmp2 = VecMul(col1, col2);
		tmp0 = VecSwizzle<VecCoord::Y, X, W, Z>(tmp2);// 1 0 3 2
		tmp1 = VecSwizzle<W, Z, Y, X>(tmp2);// 3 2 1 0
		minor1 = VecSwizzle<VecCoord::Z, W, X, Y>(minor1);// 2 3 0 1

		tmp3 = VecMul(col0, tmp0);
		tmp0 = VecMul(col3, tmp0);
		tmp2 = VecMul(col3, tmp1);
		tmp1 = VecMul(col0, tmp1);

		minor0 = VecAdd(tmp0, minor0);

		minor0 = VecSub(minor0, tmp2);

		minor3 = VecSub(tmp1, tmp3);

		// 3 -----------------------------------------------

		minor3 = VecSwizzle<VecCoord::Z, W, X, Y>(minor3);// 2 3 0 1
		tmp2 = VecSwizzle<VecCoord::Z, W, X, Y>(col1);// 2 3 0 1
		tmp2 = VecMul(tmp2, col3);

		tmp0 = VecSwizzle<VecCoord::Y, X, W, Z>(tmp2);// 1 0 3 2
		col2 = VecSwizzle<VecCoord::Z, W, X, Y>(col2);// 2 3 0 1
		tmp1 = VecSwizzle<W, Z, Y, X>(tmp2);// 3 2 1 0

		tmp3 = VecMul(col2, tmp0);
		tmp0 = VecMul(col0, tmp0);
		tmp2 = VecMul(col2, tmp1);
		tmp1 = VecMul(col0, tmp1);

		minor0 = VecAdd(tmp3, minor0);
		minor0 = VecSub(minor0, tmp2);
		minor2 = VecSub(tmp1, tmp0);

		// 4 -----------------------------------------------
		tmp2 = VecMul(col0, col1);
		tmp0 = VecSwizzle<VecCoord::Y, X, W, Z>(tmp2);// 1 0 3 2
		tmp1 = VecSwizzle<W, Z, Y, X>(tmp2);// 3 2 1 0
		minor2 = VecSwizzle<VecCoord::Z, W, X, Y>(minor2);// 2 3 0 1

		tmp2 = VecMul(col3, tmp0);
		tmp3 = VecMul(col2, tmp0);
		tmp0 = VecMul(col3, tmp1);
		tmp1 = VecMul(col2, tmp1);

		minor2 = VecAdd(tmp2, minor2);
		minor3 = VecSub(tmp3, minor3);
		minor2 = VecSub(tmp0, minor2);
		minor3 = VecSub(minor3, tmp1);

		// 5 -----------------------------------------------

		tmp2 = VecMul(col0, col3);
		tmp0 = VecSwizzle<VecCoord::Y, X, W, Z>(tmp2);// 1 0 3 2
		tmp1 = VecSwizzle<W, Z, Y, X>(tmp2);// 3 2 1 0

		tmp3 = VecMul(col2, tmp0);
		tmp0 = VecMul(col1, tmp0);
		tmp2 = VecMul(col2, tmp1);
		tmp1 = VecMul(col1, tmp1);

		tmp3 = VecSub(minor1, tmp3);
		tmp0 = VecAdd(tmp0, minor2);

		minor1 = VecAdd(tmp2, tmp3);
		minor2 = VecSub(tmp0, tmp1);

		// 6 -----------------------------------------------

		tmp2 = VecMul(col0, col2);
		tmp0 = VecSwizzle<VecCoord::Y, X, W, Z>(tmp2);// 1 0 3 2
		tmp1 = VecSwizzle<W, Z, Y, X>(tmp2);// 3 2 1 0

		tmp3 = VecMul(col3, tmp0);
		tmp0 = VecMul(col1, tmp0);
		tmp2 = VecMul(col3, tmp1);
		tmp1 = VecMul(col1, tmp1);

		tmp3 = VecAdd(tmp3, minor1);
		tmp0 = VecSub(minor3, tmp0);

		minor1 = VecSub(tmp3, tmp2);
		minor3 = VecAdd(tmp1, tmp0);

		// Calculate Determinant
		det = VecMul(col0, minor0);
		tmp0 = VecSwizzle<VecCoord::Z, W, X, Y>(det);// 2 3 0 1
		det = VecAdd(tmp0, det);
		tmp0 = VecSwizzle<VecCoord::Y, X, W, Z>(det);// 1 0 3 2
		det = _mm_add_ss(tmp0, det);
		tmp1 = _mm_rcp_ss(det);
		tmp0 = _mm_add_ss(tmp1, tmp1);
		tmp2 = _mm_mul_ss(tmp1, tmp1);
		tmp3 = _mm_mul_ss(det, tmp2);
		det = _mm_sub_ss(tmp0, tmp3);
		det = VecSplat<VecCoord::X>(det);

		minor0 = VecMul(det, minor0);
		minor1 = VecMul(det, minor1);
		minor2 = VecMul(det, minor2);
		minor3 = VecMul(det, minor3);

		tmp0 = VecShuffle<VecCoord::X, Y, X, Y>(minor0, minor1);// 0 1 0 1
		tmp1 = VecShuffle<VecCoord::X, Y, X, Y>(minor2, minor3);// 0 1 0 1
		tmp2 = VecShuffle<VecCoord::Z, W, Z, W>(minor0, minor1);// 2 3 2 3
		tmp3 = VecShuffle<VecCoord::Z, W, Z, W>(minor2, minor3);// 2 3 2 3

		minor0 = VecShuffle<VecCoord::X, Z, X, Z>(tmp0, tmp1);// 0 2 0 2
		minor2 = VecShuffle<VecCoord::X, Z, X, Z>(tmp2, tmp3);// 0 2 0 2
		minor1 = VecShuffle<VecCoord::Y, W, Y, W>(tmp0, tmp1);// 1 3 1 3
		minor3 = VecShuffle<VecCoord::Y, W, Y, W>(tmp2, tmp3);// 1 3 1 3

		SseMat44 result = SseMat44(minor0, minor1, minor2, minor3);
		tmp0 = SetVecZero();

		result.matrixTypeVal = _mm_comineq_ss(tmp0, det) ? mat.matrixTypeVal : MatrixType::INVALID;

		return result;
	}

	/*!
	 * \brief Calculates the transpose of the given 4x4 matrix.
	 * 
	 * \date	2/21/2015
	 *
	 * \param	mat	The matrix to transpose.
	 *
	 * \return	The transpose matrix of the given matrix.
	 *
	 * \relatedalso gfxmath::SseMat44
	 */
	SSE_MAT_CALL MatrixTranspose(const SseMat44& mat)
	{
		SseVec tmp0, tmp1, tmp2, tmp3, col0, col1, col2, col3;

		col0 = mat.col0;
		col1 = mat.col1;
		col2 = mat.col2;
		col3 = mat.col3;

		// 00 10 01 11
		tmp0 = VecShuffle<VecCoord::X, Y, X, Y>(col0, col1);
		// 02 12 03 13
		tmp1 = VecShuffle<VecCoord::X, Y, X, Y>(col2, col3);
		// 20 30 21 31
		tmp2 = VecShuffle<VecCoord::Z, W, Z, W>(col0, col1);
		// 22 32 23 33
		tmp3 = VecShuffle<VecCoord::Z, W, Z, W>(col2, col3);

		// 00 01 02 03
		col0 = VecShuffle<VecCoord::X, Z, X, Z>(tmp0, tmp1);
		// 20 21 22 23
		col2 = VecShuffle<VecCoord::X, Z, X, Z>(tmp2, tmp3);
		// 10 11 12 13
		col1 = VecShuffle<VecCoord::Y, W, Y, W>(tmp0, tmp1);
		// 30 31 32 33
		col3 = VecShuffle<VecCoord::Y, W, Y, W>(tmp2, tmp3);

		return SseMat44(col0, col1, col2, col3, mat.matrixTypeVal);
	}
	
	/*!
	 * \brief Calculates the determinant of the given SseMat44
	 * 
	 * \date	2/21/2015
	 *
	 * \param	mat	The matrix to calculate the determinant of.
	 *
	 * \return	An SseVec containing four identical copies of this matrix's determinant.
	 *
	 * \relatedalso gfxmath::SseMat44
	 */
	inline SseVec MatrixDeterminant(const SseMat44& mat)
	{
		SseVec col0, col1, col2, col3;
		SseVec tmp0, tmp1, tmp2, tmp3, tmp4, tmp5;
		SseVec res0, res1, res2, res3;
		SseVec det;

		// 00 01 02 03
		// 10 11 12 13
		// 20 21 22 23
		// 30 31 32 33

		// Load the registers
		col0 = mat.col0;
		col1 = mat.col1;
		col2 = mat.col2;
		col3 = mat.col3;

		tmp0 = VecSwizzle<VecCoord::Z, X, Y, X>(col1);//  2 0 1 0
		tmp1 = VecSwizzle<W, W, W, Z>(col2);//  3 3 3 2
		tmp2 = VecSwizzle<VecCoord::Y, Z, X, Y>(col3);//  1 2 0 1

		tmp3 = VecSwizzle<W, Z, W, Y>(col1);//  3 2 3 1
		tmp4 = VecSwizzle<VecCoord::Y, X, X, X>(col2);//  1 0 0 0
		tmp5 = VecSwizzle<VecCoord::Z, W, Y, Z>(col3);//  2 3 1 2

		res0 = VecMul(col0, tmp0);
		res1 = VecMul(tmp1, tmp2);

		res2 = VecMul(col0, tmp3);
		res3 = VecMul(tmp4, tmp5);

		tmp0 = VecMul(res0, res1);
		tmp1 = VecMul(res2, res3);

		det = VecAdd(tmp0, tmp1);

		tmp0 = VecSwizzle<W, X, W, W>(col0);//  3 0 3 3
		tmp1 = VecSwizzle<VecCoord::Y, Y, Z, Z>(col1);//  1 1 2 2
		res2 = VecSwizzle<VecCoord::Z, Z, X, Y>(col2);//  2 2 0 1
		res3 = VecSwizzle<VecCoord::X, W, Y, X>(col3);//  0 3 1 0

		tmp2 = VecSwizzle<VecCoord::Z, Z, Y, Y>(col0);//  2 2 1 1
		tmp3 = VecSwizzle<W, X, Z, W>(col1);//  3 0 2 3
		tmp4 = VecSwizzle<VecCoord::Y, Y, W, Z>(col2);//  1 1 3 2
		tmp5 = VecSwizzle<VecCoord::X, W, X, X>(col3);//  0 3 0 0

		res0 = VecMul(tmp0, tmp1);
		res1 = VecMul(res2, res3);

		res2 = VecMul(tmp2, tmp3);
		res3 = VecMul(tmp4, tmp5);

		tmp0 = VecMul(res0, res1);
		tmp1 = VecMul(res2, res3);
		tmp0 = VecAdd(tmp0, tmp1);

		det = VecAddSub(det, tmp0);

		tmp0 = VecSwizzle<VecCoord::X, Y, X, X>(col0);//  0 1 0 0
		tmp1 = VecSwizzle<W, W, Y, Z>(col1);//  3 3 1 2
		res2 = VecSwizzle<VecCoord::Z, X, W, Y>(col2);//  2 0 3 1
		res3 = VecSwizzle<VecCoord::Y, Z, Z, W>(col3);//  1 2 2 3

		tmp2 = VecSwizzle<VecCoord::Z, W, Z, Y>(col0);//  2 3 2 1
		tmp3 = VecSwizzle<VecCoord::X, X, Y, X>(col1);//  0 0 1 0
		tmp4 = VecSwizzle<W, Y, X, Z>(col2);//  3 1 0 2
		tmp5 = VecSwizzle<VecCoord::Y, Z, W, W>(col3);//  1 2 3 3

		res0 = VecMul(tmp0, tmp1);
		res1 = VecMul(res2, res3);
		res2 = VecMul(tmp2, tmp3);
		res3 = VecMul(tmp4, tmp5);

		tmp0 = VecMul(res0, res1);
		tmp1 = VecMul(res2, res3);

		tmp0 = VecAdd(tmp0, tmp1);
		tmp1 = VecSub(det, tmp0);

		tmp0 = VecSwizzle<VecCoord::Y, X, W, Z>(tmp1);//  1 0 3 2
		tmp1 = VecAdd(tmp0, tmp1);
		tmp0 = VecSwizzle<VecCoord::Z, W, X, Y>(tmp1);//  2 3 0 1
		det = VecAdd(tmp0, tmp1);

		return det;
	}

	/*!
	 * \brief Calculates the 4x4 rotation matrix represented by the given quaternion rotation.
	 * 
	 * \date	2/21/2015
	 *
	 * \param	quat	The quaternion rotation to transform into a 4x4 matrix.
	 *
	 * \return	An SseMat44 with values representing the rotation that was given by. the passed
	 * 			SseVec quaternion.
	 *
	 * \relatedalso gfxmath::SseMat44
	 */
	SSE_MAT_CALL RotationMatrixFromQuaternion(const SseVec& quat)
	{
		// Variable declarations ======================================================================================================
		SseVec tmp0, tmp1, tmp2, tmp3, tmp4, tmp5;
		SseVec quatSqr, twoQuat;
		SseMat44 result;

		// Initialize commonly reused variables =======================================================================================
		quatSqr = VecMul(quat, quat);
		twoQuat = VecAdd(quat, quat);

		tmp0 = VecSwizzle<VecCoord::X, X, Y, NA>(twoQuat);// 2x 2x 2y na
		tmp1 = VecSwizzle<VecCoord::Y, Z, Z, NA>(quat);// y z z na
		tmp2 = VecSwizzle<W, W, W, NA>(twoQuat);// 2w 2w 2w na
		tmp3 = VecSwizzle<VecCoord::X, Y, Z, NA>(quat);// x y z na


		tmp0 = VecMul(tmp0, tmp1);// xy xz yz na
		tmp1 = VecMul(tmp2, tmp3);// wx wy wz na

		tmp2 = VecSplat<W>(quatSqr);// ww ww ww ww
		tmp3 = VecSplat<VecCoord::X>(quatSqr);// xx xx xx xx

		// Perform diagonal calculations ==============================================================================================
		tmp2 = VecAddSub(tmp2, tmp3);// (ww - xx) (ww + xx) (ww - xx) na

		tmp2 = VecSwizzle<VecCoord::Y, X, Z, NA>(tmp2);// (ww + xx) (ww - xx) (ww - xx) na
		tmp3 = VecSplat<VecCoord::Y>(quatSqr);// yy yy yy yy

		tmp2 = VecAddSub(tmp2, tmp3);// (ww + xx - yy) (ww - xx + yy) (ww - xx - yy) na

		tmp2 = VecSwizzle<VecCoord::X, Z, Y, NA>(tmp2);// (ww + xx - yy) (ww - xx - yy) (ww - xx + yy) na
		tmp3 = VecSplat<VecCoord::Z>(quatSqr);// zz zz zz zz

		tmp2 = VecAddSub(tmp2, tmp3);// (ww + xx - yy - zz) (ww - xx - yy + zz) (ww - xx + yy - zz) na
		tmp2 = VecSwizzle<VecCoord::X, Z, Y, NA>(tmp2);// (ww + xx - yy - zz) (ww - xx + yy - zz) (ww - xx - yy + zz) na

		// Perform other component calcuations ========================================================================================
		tmp3 = VecSwizzle<VecCoord::Z, Y, X, NA>(tmp1);// wz wy wx na
		tmp3 = VecAddSub(tmp0, tmp3);// (xy - wz) (xz + wy) (yz - wx) na

		tmp4 = VecSwizzle<VecCoord::Y, Z, NA, X>(tmp0);// xz yz na xy
		tmp5 = VecSwizzle<VecCoord::Y, X, NA, Z>(tmp1);// wy wx na wz

		tmp1 = VecAddSub(tmp4, tmp5);// (xz - wy) (yz + wx) na (xy + wz)

		
		// Shift values and fill the result matrix ====================================================================================
		tmp5 = VecShuffle<VecCoord::X, NA, W, X>(tmp2, tmp1);// (ww + xx - yy - zz) na (xy + wz) (xz - wy)
		tmp4 = VecSwizzle<VecCoord::X, Z, W, NA>(tmp5);// (ww + xx - yy - zz) (xy + wz) (xz - wy) na

		result.col0 = VecAnd(tmp4, MASK_1110);// (ww + xx - yy - zz) (xy + wz) (xz - wy) 0

		tmp5 = VecShuffle<NA, Y, X, NA>(tmp2, tmp3);// na (ww - xx + yy - zz) (xy - wz) na
		tmp4 = VecShuffle<VecCoord::Z, Y, Y, NA>(tmp5, tmp1);// (xy - wz) (ww - xx + yy - zz) (yz + wx) na

		result.col1 = VecAnd(tmp4, MASK_1110);// (xy - wz) (ww - xx + yy - zz) (yz + wx) 0

		tmp5 = VecShuffle<VecCoord::Y, Z, Z, NA>(tmp3, tmp2);// (xz + wy) (yz - wx) (ww - xx - yy + zz) na

		result.col2 = VecAnd(tmp5, MASK_1110);// (xz + wy) (yz - wx) (ww - xx - yy + zz) 0

		result.col3 = UNIT_0001;// 0 0 0 1

		// Resulting Matrix:
		// 
		// [(ww + xx - yy - zz)      (xy - wz)           (xz + wy)      0 ]
		// [     (xy + wz)      (ww - xx + yy - zz)      (yz - wx)      0 ]
		// [     (xz - wy)           (yz + wx)      (ww - xx - yy + zz) 0 ]
		// [         0                   0                   0          1 ]
		// 

		return result;
	}

	/*!
	 * \brief Calculates the 4x4 rotation matrix represented by the given euler angle rotation.
	 * 
	 * \date	2/21/2015
	 *
	 * \param	angles	The euler angles to use for generating the 4x4 matrix.
	 *
	 * \return	The 4x4 rotation matrix represented by the given euler angle rotation.
	 *
	 * \relatedalso gfxmath::SseMat44
	 */
	SSE_MAT_CALL RotationMatrixFromEuler(const SseVec& angles)
	{
		//return RotationMatrixFromQuaternion(quat);

		//  cycz  ( sxsy - cxcysz)  ( cxsy + sxcysz)  0
		//  sz      cxcz             -sxcz            0
		// -sycz  ( sxcy + cxsysz)  ( cxcy - sxsysz)  0
		//  0       0                 0               1

		SseVec tmp0, tmp1, tmp2, tmp3, tmp4, tmp5;
		SseVec sinAngles, cosAngles;
		SseMat44 result;

		sinAngles = FastSinSseVec(angles);// sx sy sz na
		cosAngles = FastCosSseVec(angles);// cx cy cz na

		tmp0 = VecSplat<VecCoord::Z>(cosAngles);// cz cz cz cz
		tmp1 = VecShuffle<VecCoord::X, VecCoord::Y, VecCoord::X, VecCoord::Y>(cosAngles, sinAngles);// cx cy sx sy
		
		tmp2 = VecMul(tmp0, tmp1);// cxcz cycz sxcz sycz

		tmp3 = VecShuffle<VecCoord::Y, VecCoord::W, VecCoord::Z, VecCoord::NA>(tmp2, sinAngles);// cycz sycz sz na
		tmp3 = VecSwizzle<VecCoord::X, VecCoord::Z, VecCoord::Y, VecCoord::NA>(tmp3);// cycz sz sycz na
		tmp3 = Vec4Negate<false, false, true, false>(tmp3);// cycz sz -sycz na

		result.col0 = VecAnd(tmp3, MASK_1110);// cycz sz -sycz 0

		tmp3 = VecShuffle<VecCoord::X, VecCoord::X, VecCoord::X, VecCoord::X>(cosAngles, sinAngles);// cx cx sx sx
		tmp4 = VecShuffle<VecCoord::Y, VecCoord::NA, VecCoord::Y, VecCoord::NA>(cosAngles, sinAngles);// cy na sy na
		tmp4 = VecSwizzle<VecCoord::X, VecCoord::Z, VecCoord::Z, VecCoord::X>(tmp4);// cy sy sy cy
		tmp5 = VecSplat<VecCoord::Z>(sinAngles);// sz sz sz sz

		tmp4 = VecMul(tmp3, tmp4);// cxcy cxsy sxsy sxcy
		tmp3 = VecMul(tmp4, tmp5);// cxcysz cxsysz sxsysz sxcysz

		tmp4 = VecSwizzle<VecCoord::Z, VecCoord::W, VecCoord::X, VecCoord::Y>(tmp4);// sxsy sxcy cxcy cxsy

		tmp4 = VecAddSub(tmp4, tmp3);// (sxsy - cxcysz) (sxcy + cxsysz) (cxcy - sxsysz) (cxsy + sxcysz)

		tmp3 = VecShuffle<VecCoord::NA, VecCoord::X, VecCoord::X, VecCoord::Y>(tmp2, tmp4);// na cxcz (sxsy - cxcysz) (sxcy + cxsysz)
		tmp3 = VecSwizzle<VecCoord::Z, VecCoord::Y, VecCoord::W, VecCoord::NA>(tmp3);// (sxsy - cxcysz) cxcz (sxcy + cxsysz) na

		result.col1 = VecAnd(tmp3, MASK_1110);// (sxsy - cxcysz) cxcz (sxcy + cxsysz) 0

		tmp0 = VecShuffle<VecCoord::NA, VecCoord::Z, VecCoord::W, VecCoord::Z>(tmp2, tmp4);// na sxcz (cxsy + sxcysz) (cxcy - sxsysz)
		tmp0 = VecSwizzle<VecCoord::Z, VecCoord::Y, VecCoord::W, VecCoord::NA>(tmp0);// (cxsy + sxcysz) sxcz (cxcy - sxsysz) na
		tmp0 = Vec4Negate<false, true, false, false>(tmp0);// (cxsy + sxcysz) -sxcz (cxcy - sxsysz) na

		result.col2 = VecAnd(tmp0, MASK_1110);// (cxsy + sxcysz) -sxcz (cxcy - sxsysz) 0

		result.col3 = UNIT_0001;

		return result;
	}

	/*!
	 * \brief Calculates the 4x4 translation matrix represented by the given 3D position vector.
	 * 
	 * \date	2/21/2015
	 *
	 * \param	vec	The given 3D position vector.
	 *
	 * \return	The translation matrix represented by the given 3D position vector.
	 *
	 * \relatedalso gfxmath::SseMat44
	 */
	SSE_MAT_CALL TranslationMatrixFromVec3(const SseVec& vec)
	{
		SseMat44 result;
		result.col0 = UNIT_1000;
		result.col1 = UNIT_0100;
		result.col2 = UNIT_0010;
		result.col3 = vec;

		return result;
	}

	/*!
	 * \brief	Calculates the 4x4 scale matrix represented by the given 3D scale vector.
	 *
	 * \date	2/21/2015
	 *
	 * \param	vec	The given 3D scale vector.
	 *
	 * \return	The scale matrix represented by the given 3D position vector.
	 *
	 * \relatedalso gfxmath::SseMat44
	 */
	SSE_MAT_CALL ScaleMatrixFromVec3(const SseVec& vec)
	{
		SseMat44 result;
		result.col0 = VecAnd(vec, MASK_1000);
		result.col1 = VecAnd(vec, MASK_0100);
		result.col2 = VecAnd(vec, MASK_0010);
		result.col3 = UNIT_0001;

		return result;
	}

	/*!
	 * \brief Calculates the right-handed perspective projection matrix.
	 * 
	 * \date	2/21/2015
	 *
	 * \param	near  	The distance to the near clip plane.
	 * \param	far   	The distance to the far clip plane.
	 * \param	fov   	The vertical field of view angle.
	 * \param	aspect	The aspect ratio (width / height).
	 * 
	 * \return	The right-handed perspective projection matrix.
	 * 
	 * \remarks This form of the perspective projection matrix takes on the following format:
	 * 			
	 *			\f[
	 * 			P_{m,n} = 
	 * 			 \begin{pmatrix}
	 *			  \cot(\theta)  &    0               &	 0			&    0		\\
	 *			   0            &   \cot(\theta) * a &	-f/(f-n)	&	-1		\\
	 *			   0			&	 0				 &  -fn/(f-n)	&	 0
	 *			 \end{pmatrix}
	 *			\f]
	 *
	 * 
	 * Where:
	 * + \\(\\theta\\) is the fov (field of view) angle.
	 * + \\(f\\) is the distance to the far clipping plane.
	 * + \\(n\\) is the distance to the near clipping plane.
	 * + \\(a\\) is the aspect ratio of the viewport.
	 *
	 * This is the SseMat44 equivalent of the Mat44 version of this function:<BR>
	 * PerspectiveProjectionMatrix(float near, float far, float fov, float aspect, Mat44& result)
	 *
	 * \sa void PerspectiveProjectionMatrix(float near, float far, float fov, float aspect, Mat44& result)
	 *
	 * \relatedalso gfxmath::SseMat44
	 */
	SSE_MAT_CALL PerspectiveProjectionMatrix(float near, float far, float fov, float aspect)
	{		
		SseMat44 result;
		static const SseVec NEGATIVE_UNIT_0001 = Vec4Negate(UNIT_0001);

		float farDistOverDepth = far / (far - near);
		float cotFOV = CotApprox(fov*0.5f);
		
		// Multiply the second cotFOV by the aspect ratio to reduce stretching near the edges.
		SseVec tmp0 = SetSseVec4(cotFOV, cotFOV * aspect, -farDistOverDepth, -farDistOverDepth * near);
		SseVec zero = SetVecZero();
		
        result.col0 = VecBlend<RIGHT, LEFT, LEFT, LEFT>(zero, tmp0);//				    [cotFOV	    0.0f			  0.0f		 0.0f]
        result.col1 = VecBlend<LEFT, RIGHT, LEFT, LEFT>(zero, tmp0);//				    [0.0f		cotFOV * aspect	  0.0f		 0.0f]
        result.col2 = VecBlend<LEFT, LEFT, RIGHT, LEFT>(NEGATIVE_UNIT_0001, tmp0);//   [0.0f		0.0f			 -f/(f-n)	-1.0f]
		tmp0 = VecSwizzle<VecCoord::X, Y, W, Z>(tmp0);
        result.col3 = VecBlend<LEFT, LEFT, RIGHT, LEFT>(zero, tmp0);//					[0.0f		0.0f			 -fn/(f-n)	 0.0f]

		return result;
	}

	/*!
	 * \brief	Calculates the view matrix given the forward direction vector, rather than a target
	 * 			position.
	 *
	 * \date	2/21/2015
	 *
	 * \param	eye	The position of the camera, in world space.
	 * \param	dir	The direction the camera is facing.
	 * \param	up 	The camera's relative "up" direction - should always be <0 1 0> 
     *                  unless the camera has a roll/bank rotation that isn't 0, or the
     *                  camera has its pitch value at %%\\pm\\frac{\\pi}{2}%% radians (\\pm %%90^{\\circ}%%%).
	 *
	 * \return	The calculated view matrix.
	 *
	 * \relatedalso gfxmath::SseMat44
	 */
	SSE_MAT_CALL LookDir(const SseVec& eye, const SseVec& dir, const SseVec& up)
	{
		SseMat44 result;
		SseVec zero = SetVecZero();
		SseVec fwdAxis = Vec3Normalize(dir);
		SseVec rightAxis = Vec3Normalize(Vec3Cross(fwdAxis, up));
		SseVec upAxis = Vec3Cross(rightAxis, fwdAxis);

		SseVec negativeDir = Vec3Negate(fwdAxis);
		SseVec negativeEye = Vec3Negate(eye);

		SseVec tmp0;
		SseVec rightDotNegEye, upDotNegEye, backwardDotNegEye;

		// rx ry ux uy
		tmp0 = VecShuffle<VecCoord::X, Y, X, Y>(rightAxis, upAxis);
		// rx ux -dx na
		result.col0 = VecShuffle<VecCoord::X, Z, X, NA>(tmp0, negativeDir);
		// ry uy -dy na
		result.col1 = VecShuffle<VecCoord::Y, W, Y, NA>(tmp0, negativeDir);

		// rz na uz na
		tmp0 = VecShuffle<VecCoord::Z, NA, Z, NA>(rightAxis, upAxis);
		// rz uz -dz na
		result.col2 = VecShuffle<VecCoord::X, Z, Z, NA>(tmp0, negativeDir);

		// rx ux -dx 0
		result.col0 = VecAnd(MASK_1110, result.col0);

		// ry uy -dy 0
		result.col1 = VecAnd(MASK_1110, result.col1);

		// rz uz -dz 0
		result.col2 = VecAnd(MASK_1110, result.col2);

		//  rx  ry  rz 0
		//  ux  uy  uz 0
		// -dx -dy -dz 0
		//  0   0   0  1
		
		rightDotNegEye = Vec3Dot(rightAxis, negativeEye);// -rDPe na na na
		upDotNegEye = Vec3Dot(upAxis, negativeEye);// -uDPe na na na
		backwardDotNegEye = Vec3Dot(negativeDir, negativeEye);// dDPe na na na


		// -rDPe na -uDPe na
		tmp0 = VecShuffle<VecCoord::X, NA, X, NA>(rightDotNegEye, upDotNegEye);

		// -rDPe -uDPe dDPe na
		tmp0 = VecShuffle<VecCoord::X, Z, X, NA>(tmp0, backwardDotNegEye);

		// -rDPe -uDPe dDPe 1
        result.col3 = VecBlend<LEFT, LEFT, LEFT, RIGHT>(tmp0, UNIT_0001);

		//  rx  ry  rz -rDPe
		//  ux	uy  uz -uDPe
		// -dx -dy -dz  dDPe
		//  0   0   0   1

		return result;
	}

	/*!
	 * \brief	Calculates the standard lookat matrix for the camera, given the camera's position,
	 * 			the target's position, and a given "up" vector.
	 *
	 * \date	2/21/2015
	 *
	 * \param	eye   	The position of the camera, in world space.
	 * \param	target	The position of the target that the camera is facing.
	 * \param	up	  	The camera's relative "up" direction - should always be <0 1 0> 
     *                  unless the camera has a roll/bank rotation that isn't 0, or the
     *                  camera has its pitch value at %%\\pm\\frac{\\pi}{2}%% radians (\\pm %%90^{\\circ}%%%).
	 *
	 * \return	The calculated view matrix.
	 *
	 * \relatedalso gfxmath::SseMat44
	 */
	SSE_MAT_CALL LookAt(const SseVec& eye, const SseVec& target, const SseVec& up)
	{
		SseVec dir = VecSub(target, eye);
		return LookDir(eye, dir, up);
	}

	/*!
	 * \brief	Transforms the given 3D vector via the given SseMat44 matrix.
	 *
	 * \date	2/21/2015
	 *
	 * \param	mat	The matrix that will be multiplied against the 3D vector.
	 * \param	vec	The 3D vector to transform.
	 *
	 * \return	The transformed 3D vector.
	 *
	 * \relatedalso gfxmath::SseMat44
	 */
	inline SseVec TransformVec3(const SseMat44& mat, const SseVec& vec)
	{
		SseVec result;
		SseVec xVec, yVec, zVec;
		SseVec tmp0, tmp1, tmp2, tmp3;

		xVec = VecSplat<VecCoord::X>(vec);// vx vx vx vx
		yVec = VecSplat<VecCoord::Y>(vec);// vy vy vy vy
		zVec = VecSplat<VecCoord::Z>(vec);// vz vz vz vz

		tmp0 = VecMul(mat.col0, xVec);// vxc0x vxc0y vxc0z na
		tmp1 = VecMul(mat.col1, yVec);// vyc1x vyc1y vyc1z na
		tmp2 = VecMul(mat.col2, zVec);// vzc2x vzc2y vzc2z na

		tmp3 = VecAdd(tmp0, tmp1);// (vxc0x + vyc1x) (vxc0y + vyc1y) (vxc0z + vyc1z)
		result = VecAdd(tmp2, mat.col3);// (vzc2x + c3x) (vzc2y + c3y) (vzc2z + c3z)
		result = VecAdd(result, tmp3);// (vxc0x + vyc1x + vzc2x + c3x) (vxc0y + vyc1y + vzc2y + c3y) (vxc0z + vyc1z + vzc2z + c3z)

        result = VecBlend<LEFT, LEFT, LEFT, RIGHT>(result, UNIT_0001);

		return result;
	}

	/*! @} */
}
#endif // SSE_MAT44_DOT_H