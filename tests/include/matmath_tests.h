#ifndef MAT_MATH_TESTS_DOT_H
#define MAT_MATH_TESTS_DOT_H
#include "matmath.h"
#include "ssemat_tests.h"
#include "scalar_tests.h"
#include "string_convert.h"

typedef std::array<std::array<float, 4>, 4> Mat44Contents;

ALIGNED_CLASS(16) Mat44TestContext
{
public:
	Mat44Contents m;

	int matrixTypeVal;

	Mat44TestContext() : matrixTypeVal(gofxmath::MatrixType::MISC), m() {}

	Mat44TestContext(const Mat44Contents& mParam, int matrixTypeVal = gofxmath::MatrixType::MISC) : m(mParam), matrixTypeVal(matrixTypeVal) {}

	Mat44TestContext(const gofxmath::Mat44& mat) : matrixTypeVal(mat.matrixTypeVal)
	{
		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = 0; j < 4; j++)
			{
				m[i][j] = mat[i].vals[j];
			}
		}
	}

	template<gofxmath::FloatPrecision precisionLevel>
	bool ApproxEqual(const Mat44TestContext& mat)
	{
		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = 0; j < 4; j++)
			{
				if (!ApproxEqual_Debug<precisionLevel>(m[i][j], mat.m[i][j]))
				{
					return false;
				}
			}
		}

		return matrixTypeVal == mat.matrixTypeVal;
	}

	friend std::ostream& operator <<(std::ostream& stream, const Mat44TestContext& mat);
	friend std::istream& operator >>(std::istream& stream, const Mat44TestContext& mat);
};

template<gofxmath::FloatPrecision precisionLevel = gofxmath::FloatPrecision::LOW>
inline void RunMat44Test(const gofxmath::Mat44& result, const gofxmath::Mat44& expected)
{
	Mat44TestContext res(result);
	Mat44TestContext exp(expected);

	INFO("RESULT:");
	INFO(res);
	INFO("MATRIX TYPE: " << result.matrixTypeVal);
	INFO("EXPECTED:");
	INFO(exp);
	INFO("MATRIX TYPE: " << expected.matrixTypeVal);
	CHECK(res.ApproxEqual<precisionLevel>(exp));
}

void RunMat44InvalidTest(const gofxmath::Mat44& result);

#endif