#ifndef MAT44_DOT_H
#define MAT44_DOT_H


#include "vec4.h"
#include "sisd_defns.h"
#include <string>
#include <sstream>

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
	/*!
	 * \ingroup SISDMatMath
	 * @{
	 */

	/*!
	 * \brief The type of matrix being used.
	 * \enum	MatrixType
	 */
	enum MatrixType
	{
		IDENTITY = 0x1,
		MISC = 0x3,
		INVALID = -1
	};

	ALIGNED_CLASS(16) SseMat44;

	/*!
	 * \class	Mat44
	 * 			
	 * \brief 4x4 Column Matrix.		
	 * 									
	 * \date	2/21/2015
	 */
	ALIGNED_CLASS(16) Mat44
	{
	public:

		/*!
		 * \brief Constructs a Mat44 with all four column vectors being initialized to 0 vectors.
		 *
		 * \date	2/21/2015
		 */
		Mat44();

		/*!
		 * \brief	Constructs a Mat44 with all four column vectors being initialized to the given 4D
		 * 			vectors and (optionally) the matrixTypeVal with the given MatrixType value.
		 *
		 * \date	2/21/2015
		 *
		 * \param	c0			 	The first column.
		 * \param	c1			 	The second column.
		 * \param	c2			 	The third column.
		 * \param	c3			 	The fourth column.
		 * \param	matrixTypeVal	The matrix type value.
		 */
		Mat44(const Vec4& c0, const Vec4& c1, const Vec4& c2, const Vec4& c3, MatrixType matrixTypeVal = MatrixType::MISC);

		/*!
		 * \brief	Constructs a Mat44 with all 4 column vectors being initialized to the given scalar
		 * 			values.
		 *
		 * \date	2/21/2015
		 *
		 * \param	m00			 	Row 0 Col 0 Value.
		 * \param	m10			 	Row 1 Col 0 Value.
		 * \param	m20			 	Row 2 Col 0 Value.
		 * \param	m30			 	Row 3 Col 0 Value.
		 *
		 * \param	m01			 	Row 0 Col 1 Value.
		 * \param	m11			 	Row 1 Col 1 Value.
		 * \param	m21			 	Row 2 Col 1 Value.
		 * \param	m31			 	Row 3 Col 1 Value.
		 *
		 * \param	m02			 	Row 0 Col 2 Value.
		 * \param	m12			 	Row 1 Col 2 Value.
		 * \param	m22			 	Row 2 Col 2 Value.
		 * \param	m32			 	Row 3 Col 2 Value.
		 *
		 * \param	m03			 	Row 0 Col 3 Value.
		 * \param	m13			 	Row 1 Col 3 Value.
		 * \param	m23			 	Row 2 Col 3 Value.
		 * \param	m33			 	Row 3 Col 3 Value.
		 *
		 * \param	matrixTypeVal	The matrix type value.
		 */
		Mat44(float m00, float m10, float m20, float m30,
			float m01, float m11, float m21, float m31,
			float m02, float m12, float m22, float m32,
			float m03, float m13, float m23, float m33,
			MatrixType matrixTypeVal = MatrixType::MISC);

		/*!
		 * \brief Copies the values from the given matrix's columns into the respective columns of this matrix,
		 * 		  sets this instance's matrixTypeVal to the matrixTypeVal given by the converted matrix.
		 *
		 * \date	2/21/2015
		 *
		 * \param	mat	The matrix to convert.
		 */
		Mat44(const SseMat44& mat);

		/*!
		 * \brief Copy constructor.
		 *
		 * \date	2/21/2015
		 *
		 * \param	mat	The matrix.
		 */
		Mat44(const Mat44& mat);

		/*!
		 * \brief Stream insertion operator.
		 *
		 * \date	2/21/2015
		 *
		 * \param [in,out]	stream	The stream.
		 * \param	mat			  	The matrix.
		 *
		 * \return	The shifted result.
		 */
		friend std::ostream &operator << (std::ostream& stream, const Mat44& mat);

		/*!
		 * \brief Stream extraction operator.
		 *
		 * \date	2/21/2015
		 *
		 * \param [in,out]	stream	The stream.
		 * \param [in,out]	mat   	The matrix.
		 *
		 * \return	The shifted result.
		 */
		friend std::istream &operator >> (std::istream& stream, Mat44& mat);

		/*!
		 * \brief Equality operator.
		 *
		 * \date	2/21/2015
		 *
		 * \param	left 	The first instance to compare.
		 * \param	right	The second instance to compare.
		 *
		 * \return	true if the parameters are considered equivalent.
		 */
		friend bool operator==(const Mat44& left, const Mat44& right);

		/*!
		 * \brief Inequality operator.
		 *
		 * \date	2/21/2015
		 *
		 * \param	left 	The first instance to compare.
		 * \param	right	The second instance to compare.
		 *
		 * \return	true if the parameters are not considered equivalent.
		 */
		friend bool operator!=(const Mat44& left, const Mat44& right);

		/*!
		 * \brief Prints the given matrix.
		 *
		 * \date	2/21/2015
		 *
		 * \param	mat	The matrix.
		 */
		friend void Print(const Mat44& mat);

		/*!
		 * \brief Converts a mat to a console debug string.
		 *
		 * \date	2/21/2015
		 *
		 * \param	mat	The matrix.
		 *
		 * \return	mat as a std::string.
		 */
		friend std::string ToConsoleDebugString(const Mat44& mat);

		/*!
		 * \brief Gets the column associated with the given index.
		 *
		 * \param	arg	The given index.
		 *
		 * \return The column associated with the given index (0 for col0, 1 for col1, etc.).
		 */
		inline const Vec4& operator[](int arg) const
		{
			switch (arg)
			{
			case 0:
				return col0;
			case 1:
				return col1;
			case 2:
				return col2;
			case 3:
				return col3;
			}

			std::ostringstream msgStream;
			msgStream << "Value " << arg << " is not valid.  Use an int value between 0 and 3 (inclusive).";
			throw std::invalid_argument(msgStream.str().c_str());
		}

		/*!
		 * \brief	Gets/Sets the column associated with the given index.
		 * 
		 * \param	arg	The given index.
		 * 
		 * \return The column associated with the given index (0 for col0, 1 for col1, etc.).
		 */
		inline Vec4& operator[](int arg)
		{
			switch (arg)
			{
			case 0:
				return col0;
			case 1:
				return col1;
			case 2:
				return col2;
			case 3:
				return col3;
			}

			std::ostringstream msgStream;
			msgStream << "Value " << arg << " is not valid.  Use an int value between 0 and 3 (inclusive).";
			throw std::invalid_argument(msgStream.str().c_str());
		}

		Vec4 col0;/*!< The first column of this matrix */
		Vec4 col1;/*!< The second column of this matrix */
		Vec4 col2;/*!< The third column of this matrix */
		Vec4 col3;/*!< The fourth column of this matrix */

		MatrixType matrixTypeVal;   /*!< The matrix type value */

		static Mat44 Identity();	/*!< The 4x4 identity matrix. */
	};
	/*!@}*/
}

#endif // MAT44_DOT_H