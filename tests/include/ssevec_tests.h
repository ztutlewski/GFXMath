#ifndef SSE_VEC_TESTS_DOT_H
#define SSE_VEC_TESTS_DOT_H

#include "catch.hpp"
#include "ssevec.h"
#include "vecmath.h"
#include <iostream>
#include <string>
#include "string_convert.h"
#include "vec_tests.h"

const extern float SMALL;
const extern float MED;
const extern float BIG;
const extern float MAX;

const extern float SQRT_2;
const extern float SQRT_3;
const extern float SQRT_2_OVER_2;
const extern float SQRT_3_OVER_3;

const extern float SMALL_SQR;
const extern float MED_SQR;
const extern float BIG_SQR;

const extern float SMALL_MED;
const extern float SMALL_BIG;
const extern float MED_BIG;

const extern float ONE_OVER_BIG;
const extern float SMALL_OVER_SQRT_2;

struct SseVecContext;

struct SseVec2Context;
struct SseVec3Context;
struct SseVec4Context;

void RunVec2IsNaNTest(const SseVec2Context& context, const gfxmath::SseVec& result);
void RunVec3IsNaNTest(const SseVec2Context& context, const gfxmath::SseVec& result);
void RunVec4IsNaNTest(const SseVec2Context& context, const gfxmath::SseVec& result);

void RunVec2InfTest(const SseVec2Context& context, const gfxmath::SseVec& result);
void RunVec3InfTest(const SseVec2Context& context, const gfxmath::SseVec& result);
void RunVec4InfTest(const SseVec2Context& context, const gfxmath::SseVec& result);

void CheckSseVec2IsInfinite(const gfxmath::SseVec& vec);
void CheckSseVec3IsInfinite(const gfxmath::SseVec& vec);
void CheckSseVec4IsInfinite(const gfxmath::SseVec& vec);

void CheckSseVec2IsNaN(const gfxmath::SseVec& vec);
void CheckSseVec3IsNaN(const gfxmath::SseVec& vec);
void CheckSseVec4IsNaN(const gfxmath::SseVec& vec);

std::string FLoatPrecisionToString(gfxmath::FloatPrecision precision);

gfxmath::SseVec SetSseVec4_Debug(float x, float y, float z, float w);
gfxmath::SseVec SetSseVec3_Debug(float x, float y, float z);
gfxmath::SseVec SetSseVec2_Debug(float x, float y);

gfxmath::Vec4 StoreSseVec4_Debug(gfxmath::SseVec col);
gfxmath::Vec3 StoreSseVec3_Debug(gfxmath::SseVec col);
gfxmath::Vec2 StoreSseVec2_Debug(gfxmath::SseVec col);

ALIGNED_STRUCT(16) AlignedFloat4
{
	float vals[4];
};

ALIGNED_STRUCT(16) SseVecContext
{
	std::string info;

	SseVecContext()
	{
		info = "";
	}

	SseVecContext(const std::string& infoParam)
	{
		info = infoParam;
	}
};



ALIGNED_STRUCT(16) SseVec2Context : public SseVecContext
{
	gfxmath::Vec2 expected;

	SseVec2Context() : SseVecContext()
	{
		expected = gfxmath::Vec2();
	}

	SseVec2Context(const std::string& infoParam, const gfxmath::Vec2& expectedParam) : SseVecContext(infoParam)
	{
		expected = expectedParam;
	}
};

ALIGNED_STRUCT(16) SseVec3Context : public SseVecContext
{
	gfxmath::Vec3 expected;

	SseVec3Context() : SseVecContext()
	{
		expected = gfxmath::Vec3();
	}

	SseVec3Context(const std::string& infoParam, const gfxmath::Vec3& expectedParam) : SseVecContext(infoParam)
	{
		expected = expectedParam;
	}
};

ALIGNED_STRUCT(16) SseVec4Context : public SseVecContext
{
	gfxmath::Vec4 expected;

	SseVec4Context() : SseVecContext()
	{
		expected = gfxmath::Vec4();
	}

	SseVec4Context(const std::string& infoParam, const gfxmath::Vec4& expectedParam) : SseVecContext(infoParam)
	{
		expected = expectedParam;
	}
};



ALIGNED_STRUCT(16) SseVec2Context_1Arg : public SseVec2Context
{
	gfxmath::SseVec arg;

	SseVec2Context_1Arg() : SseVec2Context()
	{
		arg = _mm_setzero_ps();
	}

	SseVec2Context_1Arg(const std::string& infoParam, const gfxmath::Vec2& argParam, const gfxmath::Vec2& expectedParam) : SseVec2Context(infoParam, expectedParam)
	{
		info = infoParam;
		arg = gfxmath::LoadSseVec2(argParam);
		expected = expectedParam;
	}

	SseVec2Context_1Arg(const std::string& infoParam, const gfxmath::Vec2& argParam) : SseVec2Context_1Arg(infoParam, argParam, argParam) {}
};

ALIGNED_STRUCT(16) SseVec3Context_1Arg : public SseVec3Context
{
	gfxmath::SseVec arg;

	SseVec3Context_1Arg() : SseVec3Context()
	{
		arg = _mm_setzero_ps();
	}

	SseVec3Context_1Arg(const std::string& infoParam, const gfxmath::Vec3& argParam, const gfxmath::Vec3& expectedParam) : SseVec3Context(infoParam, expectedParam)
	{
		info = infoParam;
		arg = gfxmath::SetSseVec3(argParam.x, argParam.y, argParam.z);
		expected = expectedParam;
	}

	SseVec3Context_1Arg(const std::string& infoParam, const gfxmath::Vec3& argParam) : SseVec3Context_1Arg(infoParam, argParam, argParam) {}
};

ALIGNED_STRUCT(16) SseVec4Context_1Arg : public SseVec4Context
{
	gfxmath::SseVec arg;

	SseVec4Context_1Arg() : SseVec4Context()
	{
		arg = _mm_setzero_ps();
	}

	SseVec4Context_1Arg(const std::string& infoParam, const gfxmath::Vec4& argParam, const gfxmath::Vec4& expectedParam) : SseVec4Context(infoParam, expectedParam)
	{
		arg = gfxmath::LoadSseVec4(argParam);
	}

	SseVec4Context_1Arg(const std::string& infoParam, const gfxmath::Vec4& argParam) : SseVec4Context_1Arg(infoParam, argParam, argParam) {}
};

ALIGNED_STRUCT(16) SseVec4Context_2Vec4Args1ScalarArg : public SseVec4Context
{
	gfxmath::SseVec arg0;
	gfxmath::SseVec arg1;
	float scalarArg;

	SseVec4Context_2Vec4Args1ScalarArg() : SseVec4Context()
	{
		arg0 = arg1 = _mm_setzero_ps();
		scalarArg = 0.0f;
	}

	SseVec4Context_2Vec4Args1ScalarArg(const std::string& infoParam, const gfxmath::Vec4& arg0Param, const gfxmath::Vec4& arg1Param, float scalarArgParam, const gfxmath::Vec4& expectedParam) : SseVec4Context(infoParam, expectedParam)
	{
		arg0 = gfxmath::LoadSseVec4(arg0Param);
		arg1 = gfxmath::LoadSseVec4(arg1Param);
		scalarArg = scalarArgParam;
	}
};

ALIGNED_STRUCT(16) SseVec4Context_1Vec3Arg1ScalarArg : public SseVec4Context
{
	gfxmath::SseVec arg;
	float scalarArg;

	SseVec4Context_1Vec3Arg1ScalarArg() : SseVec4Context()
	{
		arg = _mm_setzero_ps();
		scalarArg = 0.0f;
	}

	SseVec4Context_1Vec3Arg1ScalarArg(const std::string& infoParam, const gfxmath::Vec3& argParam, float scalarArgParam, const gfxmath::Vec4& expectedParam) : SseVec4Context(infoParam, expectedParam)
	{
		arg = LoadSseVec3(argParam);
		scalarArg = scalarArgParam;
	}
};

ALIGNED_STRUCT(16) SseVec4Context_1Vec3Arg : public SseVec4Context
{
	gfxmath::SseVec arg;

	SseVec4Context_1Vec3Arg() : SseVec4Context()
	{
		arg = _mm_setzero_ps();
	}

	SseVec4Context_1Vec3Arg(const std::string& infoParam, const gfxmath::Vec3& argParam, const gfxmath::Vec4& expectedParam) : SseVec4Context(infoParam, expectedParam)
	{
		arg = gfxmath::LoadSseVec3(argParam);
	}
};


ALIGNED_STRUCT(16) SseVec2Context_2Args : public SseVec2Context
{
	gfxmath::SseVec arg0;
	gfxmath::SseVec arg1;

	SseVec2Context_2Args() : SseVec2Context()
	{
		arg0 = arg1 = _mm_setzero_ps();
	}

	SseVec2Context_2Args(const std::string& infoParam, const gfxmath::Vec2& arg0Param, const gfxmath::Vec2& arg1Param, const gfxmath::Vec2& expectedParam) : SseVec2Context(infoParam, expectedParam)
	{
		arg0 = gfxmath::LoadSseVec2(arg0Param);
		arg1 = gfxmath::LoadSseVec2(arg1Param);
	}
};

ALIGNED_STRUCT(16) SseVec3Context_2Args : public SseVec3Context
{
	std::string info;
	gfxmath::SseVec arg0;
	gfxmath::SseVec arg1;
	gfxmath::Vec3 expected;

	SseVec3Context_2Args() : SseVec3Context()
	{
		arg0 = arg1 = _mm_setzero_ps();
	}

	SseVec3Context_2Args(const std::string& infoParam, const gfxmath::Vec3& arg0Param, const gfxmath::Vec3& arg1Param, const gfxmath::Vec3& expectedParam) : SseVec3Context(infoParam, expectedParam)
	{
		arg0 = gfxmath::LoadSseVec3(arg0Param);
		arg1 = gfxmath::LoadSseVec3(arg1Param);
	}
};

ALIGNED_STRUCT(16) SseVec4Context_2Args : public SseVec4Context
{
	gfxmath::SseVec arg0;
	gfxmath::SseVec arg1;

	SseVec4Context_2Args() : SseVec4Context()
	{
		arg0 = arg1 = _mm_setzero_ps();
	}

	SseVec4Context_2Args(const std::string& infoParam, const gfxmath::Vec4& arg0Param, const gfxmath::Vec4& arg1Param, const gfxmath::Vec4& expectedParam) : SseVec4Context(infoParam, expectedParam)
	{
		arg0 = gfxmath::LoadSseVec4(arg0Param);
		arg1 = gfxmath::LoadSseVec4(arg1Param);
	}
};

template<gfxmath::FloatPrecision precisionLevel = gfxmath::FloatPrecision::HIGH>
inline bool SseVecEqual(const gfxmath::SseVec& leftVec, const gfxmath::SseVec& rightVec)
{
	static const float precisionValue = gfxmath::FloatPrecisionValue<precisionLevel>();

	AlignedFloat4 leftContainer;
	AlignedFloat4 rightContainer;
	_mm_store_ps(leftContainer.vals, leftVec);
	_mm_store_ps(rightContainer.vals, rightVec);

	for (size_t i = 0; i < 4; i++)
	{
		if (abs(leftContainer.vals[i] - rightContainer.vals[i]) > precisionValue)
		{
			return false;
		}
	}

	return true;
}

template<gfxmath::FloatPrecision precision = gfxmath::FloatPrecision::HIGH>
inline void CheckSseVec2(const gfxmath::SseVec& vec, const gfxmath::Vec2& expected)
{
	gfxmath::Vec2 result = StoreSseVec2_Debug(vec);

	CHECK(Vec2ApproxEqual_Debug<precision>(result, expected));
}

template<gfxmath::FloatPrecision precision = gfxmath::FloatPrecision::HIGH>
inline void CheckSseVec3(const gfxmath::SseVec& vec, const gfxmath::Vec3& expected)
{
	gfxmath::Vec3 result = StoreSseVec3_Debug(vec);

	CHECK(Vec3ApproxEqual_Debug<precision>(result, expected));
}

template<gfxmath::FloatPrecision precision = gfxmath::FloatPrecision::HIGH>
inline void CheckSseVec4(const gfxmath::SseVec& vec, const gfxmath::Vec4& expected)
{
	gfxmath::Vec4 result = StoreSseVec4_Debug(vec);

	CHECK(Vec4ApproxEqual_Debug<precision>(result, expected));
}

template<gfxmath::FloatPrecision precision = gfxmath::FloatPrecision::HIGH>
inline void CheckSseVec(const gfxmath::SseVec& resultVec, const gfxmath::SseVec& expectedVec)
{
	AlignedFloat4 resultContainer;
	AlignedFloat4 expectedContainer;
	_mm_store_ps(resultContainer.vals, resultVec);
	_mm_store_ps(expectedContainer.vals, expectedVec);

	INFO("RESULT: " << resultContainer.vals[0] << " " << resultContainer.vals[1] << " " << resultContainer.vals[2] << " " << resultContainer.vals[3]);
	INFO("EXPECTED: " << expectedContainer.vals[0] << " " << expectedContainer.vals[1] << " " << expectedContainer.vals[2] << " " << expectedContainer.vals[3]);
	CHECK(SseVecEqual<precision>(resultVec, expectedVec));
}

template<gfxmath::FloatPrecision precision = gfxmath::FloatPrecision::HIGH>
inline void RunVec2Test(const SseVec2Context& context, const gfxmath::SseVec& result, int index = -1)
{
	std::string closing = index >= 0 ? "> at index " + gfxengine::cvt_to_string(index) : ">";
	std::string resultString = "Result Vector <";
	std::string expectedString = "Expected Vector <";
	INFO("Test " << context.info);
	INFO(resultString << StoreSseVec2_Debug(result) << ">");
	INFO(expectedString << context.expected << closing);
	INFO("PRECISION: " << FLoatPrecisionToString(precision));
	CheckSseVec2<precision>(result, context.expected);
}

template<gfxmath::FloatPrecision precision = gfxmath::FloatPrecision::HIGH>
inline void RunVec3Test(const SseVec3Context& context, const gfxmath::SseVec& result, int index = -1)
{
	std::string closing = index >= 0 ? "> at index " + gfxengine::cvt_to_string(index) : ">";
	std::string resultString = "Result Vector <";
	std::string expectedString = "Expected Vector <";
	INFO("Test " << context.info);
	INFO(resultString << StoreSseVec3_Debug(result) << ">");
	INFO(expectedString << context.expected << closing);
	INFO("PRECISION: " << FLoatPrecisionToString(precision));
	CheckSseVec3<precision>(result, context.expected);
}

template<gfxmath::FloatPrecision precision = gfxmath::FloatPrecision::HIGH>
inline void RunVec4Test(const SseVec4Context& context, const gfxmath::SseVec& result, int index = -1)
{
	std::string closing = index >= 0 ? "> at index " + gfxengine::cvt_to_string(index) : ">";
	std::string resultString = "Result Vector <";
	std::string expectedString = "Expected Vector <";

	gfxmath::Vec4 res = StoreSseVec4_Debug(result);

	INFO("Test " << context.info);
	INFO(resultString << res << ">");
	INFO(expectedString << context.expected << closing);
	INFO("Difference: " << (Vec4Sub(res, context.expected)));
	INFO("PRECISION: " << FLoatPrecisionToString(precision));
	CheckSseVec4<precision>(result, context.expected);
}

#endif