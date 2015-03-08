#ifndef MAT_MATH_DOT_H
#define MAT_MATH_DOT_H


#include <array>
#include "mat44.h"

/*!
 * \file 
 */

/*!
 * \defgroup SISDMatMath SISD Matrix Math
 */

/*!
 * \namespace	gofxmath
 *
 * \brief	G of F of X math namespace.
 */
namespace gofxmath
{
	class Quaternion;
	class Vec3;
	
	/*!
	 * \ingroup SISDMatMath
	 * @{
	 */

	/*!
	 * \brief Calculates the product (post-multiplication) of the two given 4x4 matrices.
	 * 		 
	 * \date	2/21/2015
	 *
	 * \param	first 	The left matrix.
	 * \param	second	The right matrix.
	 *
	 * \return	The post-multiplied product of the two matrices.
	 * 
	 * \relatedalso gofxmath::Mat44
	 */
	Mat44 MatrixMultiply(const Mat44& first, const Mat44& second);

	/*!
	 * \brief Calculates the determinant of the given 4x4 matrix.
	 * 		 
	 * \date	2/21/2015
	 *
	 * \param	mat	The matrix to find the determinant of.
	 *
	 * \return	A float.
	 * 
	 * \relatedalso gofxmath::Mat44
	 */
	float MatrixDeterminant(const Mat44& mat);

	/*!
	 * \brief Calculates the inverse of the given 4x4 matrix.
	 * 
	 * \date	2/21/2015
	 *
	 * \param	mat	The matrix to invert.
	 *
	 * \return	The inverse of the given matrix.
	 * 
	 * \relatedalso gofxmath::Mat44
	 */
	Mat44 MatrixInverse(const Mat44& mat);

	/*!
	 * \brief Calculates the transpose of the given 4x4 matrix.
	 * 
	 * \date	2/21/2015
	 *
	 * \param	mat	The matrix to transpose.
	 *
	 * \return	The transpose matrix of the given matrix.
	 * 
	 * \relatedalso gofxmath::Mat44
	 */
	Mat44 MatrixTranspose(const Mat44& mat);

	/*!
	 * \brief Calculates the 4x4 rotation matrix represented by the given quaternion rotation.
	 * 		  
	 * \date	2/21/2015
	 *
	 * \param	quat	The quaternion rotation to transform into a 4x4 matrix.
	 *
	 * \return	A Mat44.
	 * 
	 * \relatedalso gofxmath::Mat44
	 */
	Mat44 RotationMatrixFromQuaternion(const Quaternion& quat);

	/*!
	 * \brief Calculates the 4x4 rotation matrix represented by the given euler angle rotation.
	 *
	 * \date	2/21/2015
	 *
	 * \param	angles	The euler angles to use for generating the 4x4 matrix.
	 *
	 * \return	The 4x4 rotation matrix represented by the given euler angle rotation.
	 * 
	 * \relatedalso gofxmath::Mat44
	 */
	Mat44 RotationMatrixFromEuler(const Vec3& angles);

	/*!
	 * \brief Calculates the 4x4 translation matrix represented by the given 3D position vector.
	 *
	 * \date	2/21/2015
	 *
	 * \param	vec	The given 3D position vector.
	 *
	 * \return	The translation matrix represented by the given 3D position vector.
	 * 
	 * \relatedalso gofxmath::Mat44
	 */
	Mat44 TranslationMatrixFromVec3(const Vec3& vec);

	/*!
	 * \brief Calculates the 4x4 scale matrix represented by the given 3D scale vector.
	 *
	 * \date	2/21/2015
	 *
	 * \param	vec	The given 3D scale vector.
	 *
	 * \return	The scale matrix represented by the given 3D position vector.
	 * 
	 * \relatedalso gofxmath::Mat44
	 */
	Mat44 ScaleMatrixFromVec3(const Vec3& vec);

	/*!
	 * \brief Calculates the right-handed perspective projection matrix.
	 * 
	 * \date	2/21/2015
	 *
	 * \param	near		  	The distance to the near clip plane.
	 * \param	far			  	The distance to the far clip plane.
	 * \param	fov			  	The vertical field of view angle.
	 * \param	aspect		  	The aspect ratio (width / height).
	 * \param [in,out]	result	The result matrix.
	 * 					
	 * \remarks This form of the perspective projection matrix takes on the following format:
	 * 			
	 *			\f[
	 * 			P_{m,n} = 
	 * 			 \begin{pmatrix}
	 *			  \cot(\theta)  &	0				 &	 0			&	 0		\\
	 *			   0			&	\cot(\theta) * a &	-f/(f-n)	&	-1		\\
	 *			   0			&	 0				 &	-fn/(f-n)	&	 0
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
	 * \relatedalso gofxmath::Mat44
	 */
	void PerspectiveProjectionMatrix(float near, float far, float fov, float aspect, Mat44& result);

	/*!
	 * \brief	Calculates the view matrix given the forward direction vector, rather than a target
	 * 			position.
	 *
	 * \date	2/21/2015
	 *
	 * \param	eye	The position of the camera, in world space.
	 * \param	dir	The direction the camera is facing.
	 * \param	up 	The camera's relative "up" direction - should always be <0 1 0> 
     *              unless the camera has a roll/bank rotation that isn't 0, or the
     *              camera has its pitch value at %%\\pm\\frac{\\pi}{2}%% radians (\\pm %%90^{\\circ}%%%).
	 *
	 * \return	The calculated view matrix.
	 * 
	 * \relatedalso gofxmath::Mat44
	 */
	Mat44 LookDir(const Vec3& eye, const Vec3& dir, const Vec3& up);

    /*!
     * \brief Calculates the standard lookat matrix for the camera, given the camera's position, the target's position, and a given "up" vector.
     * 
	 * \date	2/21/2015
     * 
     * \param	eye	    The position of the camera, in world space.
     * \param	target	The position of the target that the camera is facing.
     * \param	up 	    The camera's relative "up" direction - should always be <0 1 0> 
     *                  unless the camera has a roll/bank rotation that isn't 0, or the
     *                  camera has its pitch value at %%\\pm\\frac{\\pi}{2}%% radians (\\pm %%90^{\\circ}%%%).
     *
     * \return The calculated view matrix.
	 * 
	 * \relatedalso gofxmath::Mat44
     */
	Mat44 LookAt(const Vec3& eye, const Vec3& target, const Vec3& up);

    /*!
     * \brief Transforms the given 3D vector.
     * 
     * \date	2/21/2015
     * 
     * \param mat The matrix that will be multiplied against the 3D vector.
     * \param vec The 3D vector to transform.
     *
     * \return The transformed 3D vector.
	 * 
	 * \relatedalso gofxmath::Mat44
     */
	Vec3 TransformVec3(const Mat44& mat, const Vec3& vec);

    /*!
     * \brief Calculates the determinant of the given Mat44
     *
     * \date	2/21/2015
     * 
     * \param mat The matrix for which to calculate the determinant.
     * 
     * \return the determinant of the given matrix.
	 * 
	 * \relatedalso gofxmath::Mat44
     */
	float MatrixDeterminant(const Mat44& mat);

	/*! @} */
}
#endif // MAT_MATH_DOT_H