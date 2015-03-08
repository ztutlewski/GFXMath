#include "mat44.h"
#include "ssemat44.h"
#include "vecmath.h"
#include <sstream>
#include <iomanip>


namespace gfxmath
{
	Mat44 Mat44::Identity()
	{
		static const Mat44 identity(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4::E3(), MatrixType::IDENTITY);
		return identity;
	}

	Mat44::Mat44() : col0(Vec4()), 
					 col1(Vec4()), 
					 col2(Vec4()), 
					 col3(Vec4()), matrixTypeVal(MatrixType::MISC) {}

	Mat44::Mat44(const Vec4& c0, const Vec4& c1, const Vec4& c2, const Vec4& c3, MatrixType matrixTypeVal) :
		col0(c0), 
		col1(c1),
		col2(c2),
		col3(c3), 
		matrixTypeVal(matrixTypeVal)  {}

	Mat44::Mat44(float m00, float m01, float m02, float m03,
				 float m10, float m11, float m12, float m13,
				 float m20, float m21, float m22, float m23,
				 float m30, float m31, float m32, float m33,
				 MatrixType matrixTypeVal) :
				 col0(Vec4(m00, m10, m20, m30)),
				 col1(Vec4(m01, m11, m21, m31)),
				 col2(Vec4(m02, m12, m22, m32)),
				 col3(Vec4(m03, m13, m23, m33)),
				 matrixTypeVal(matrixTypeVal) {}

	Mat44::Mat44(const SseMat44& mat) : col0(StoreSseVec4(mat.col0)), 
										col1(StoreSseVec4(mat.col1)), 
										col2(StoreSseVec4(mat.col2)), 
										col3(StoreSseVec4(mat.col3)), matrixTypeVal(mat.matrixTypeVal) { }

	Mat44::Mat44(const Mat44& mat) : col0(mat.col0), 
									 col1(mat.col1), 
									 col2(mat.col2), 
									 col3(mat.col3),
									 matrixTypeVal(mat.matrixTypeVal) {}

	std::ostream &operator << (std::ostream& stream, const Mat44& mat)
	{
		stream << "[" << mat.col0 << "][" << mat.col1 << "][" << mat.col2 << "][" << mat.col3 << "]";

		return stream;
	}

	std::istream &operator >> (std::istream& stream, Mat44& mat)
	{
		stream.ignore(1) >> mat.col0;
		stream.ignore(2) >> mat.col1;
		stream.ignore(2) >> mat.col2;
		stream.ignore(2) >> mat.col3;
		stream.ignore(1);

		return stream;
	}

	bool operator==(const Mat44& left, const Mat44& right)
	{
		if (left.col0 != right.col0)
		{
			return false;
		}

		return left.matrixTypeVal == right.matrixTypeVal;
	}

	bool operator!=(const Mat44& left, const Mat44& right)
	{
		return !(left == right);
	}

	void Print(const Mat44& mat)
	{
		std::cout << ToConsoleDebugString(mat);
	}

	std::string ToConsoleDebugString(const Mat44& mat)
	{
		std::stringstream str;

		for (size_t i = 0; i < 4; i++)
		{
			str << mat.col0.vals[i] << " ";
			str << mat.col1.vals[i] << " ";
			str << mat.col2.vals[i] << " ";
			str << mat.col3.vals[i] << " ";
			str << std::endl;
		}

		return str.str();
	}
}