#ifndef SSE_MAT_TESTS_DOT_H
#define SSE_MAT_TESTS_DOT_H
#include "ssevec_tests.h"
#include "scalar_tests.h"
#include "matmath.h"
#include "ssemat44.h"
#include <iomanip>
#ifdef __MINGW32__
#include "mingw_tostring_patch.h"
#endif

typedef std::array<std::array<float, 4>, 4> Mat44Contents;

ALIGNED_CLASS(16) SseMat44TestContext
{
public:
	Mat44Contents m;

	int matrixTypeVal;

	SseMat44TestContext() : matrixTypeVal(gofxmath::MatrixType::MISC), m() {}

	SseMat44TestContext(const Mat44Contents& mParam, int matrixTypeVal = gofxmath::MatrixType::MISC) : m(mParam), matrixTypeVal(matrixTypeVal) {}

	SseMat44TestContext(const gofxmath::SseMat44& mat) : matrixTypeVal(mat.matrixTypeVal)
	{
		Mat44Contents tmp;
		_mm_store_ps(tmp[0].data(), mat.col0);
		_mm_store_ps(tmp[1].data(), mat.col1);
		_mm_store_ps(tmp[2].data(), mat.col2);
		_mm_store_ps(tmp[3].data(), mat.col3);

		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = 0; j < 4; j++)
			{
				m[i][j] = tmp[j][i];
			}
		}
	}

	template<gofxmath::FloatPrecision precisionLevel>
	bool ApproxEqual(const SseMat44TestContext& mat)
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

	friend std::ostream& operator <<(std::ostream& stream, const SseMat44TestContext& mat);
	friend std::istream& operator >>(std::istream& stream, const SseMat44TestContext& mat);
};

template<gofxmath::FloatPrecision precisionLevel = gofxmath::FloatPrecision::LOW>
inline void RunSseMat44Test(const gofxmath::SseMat44& result, const gofxmath::SseMat44& expected)
{
	SseMat44TestContext res(result);
	SseMat44TestContext exp(expected);

	INFO("RESULT:");
	INFO(res);
	INFO("MATRIX TYPE: " << result.matrixTypeVal);
	INFO("EXPECTED:");
	INFO(exp);
	INFO("MATRIX TYPE: " << expected.matrixTypeVal);
	CHECK(res.ApproxEqual<precisionLevel>(exp));
}

void RunSseMat44InvalidTest(const gofxmath::SseMat44& result);

#endif