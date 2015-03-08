#ifndef VEC_TESTS_DOT_H
#define VEC_TESTS_DOT_H
#include "vecmath.h"
#include "scalar_tests.h"

void CheckVec2IsInfinite(const gfxmath::Vec2& vec);
void CheckVec3IsInfinite(const gfxmath::Vec3& vec);
void CheckVec4IsInfinite(const gfxmath::Vec4& vec);

void CheckVec2IsNaN(const gfxmath::Vec2& vec);
void CheckVec3IsNaN(const gfxmath::Vec3& vec);
void CheckVec4IsNaN(const gfxmath::Vec4& vec);

void RunVec2IsNaNTest(const gfxmath::Vec2& result, std::string info = "");
void RunVec3IsNaNTest(const gfxmath::Vec3& result, std::string info = "");
void RunVec4IsNaNTest(const gfxmath::Vec4& result, std::string info = "");

void RunVec2InfTest(const gfxmath::Vec2& result, std::string info = "");
void RunVec3InfTest(const gfxmath::Vec3& result, std::string info = "");
void RunVec4InfTest(const gfxmath::Vec4& result, std::string info = "");



template<gfxmath::FloatPrecision precisionLevel = gfxmath::FloatPrecision::HIGH>
inline bool Vec2ApproxEqual_Debug(const gfxmath::Vec2& left, const gfxmath::Vec2& right)
{
	return ApproxEqual_Debug<precisionLevel>(left.x, right.x) && ApproxEqual_Debug<precisionLevel>(left.y, right.y);
}

template<gfxmath::FloatPrecision precisionLevel = gfxmath::FloatPrecision::HIGH>
inline bool Vec3ApproxEqual_Debug(const gfxmath::Vec3& left, const gfxmath::Vec3& right)
{
	return ApproxEqual_Debug<precisionLevel>(left.x, right.x) && ApproxEqual_Debug<precisionLevel>(left.y, right.y) && ApproxEqual_Debug<precisionLevel>(left.z, right.z);
}

template<gfxmath::FloatPrecision precisionLevel = gfxmath::FloatPrecision::HIGH>
inline bool Vec4ApproxEqual_Debug(const gfxmath::Vec4& left, const gfxmath::Vec4& right)
{
	return ApproxEqual_Debug<precisionLevel>(left.x, right.x) && ApproxEqual_Debug<precisionLevel>(left.y, right.y) && ApproxEqual_Debug<precisionLevel>(left.z, right.z) && ApproxEqual_Debug<precisionLevel>(left.w, right.w);
}


template<gfxmath::FloatPrecision precisionLevel = gfxmath::FloatPrecision::HIGH>
inline void RunVec2Test(const gfxmath::Vec2& result, const gfxmath::Vec2& expected)
{
	INFO("RESULT: " << result.x << " " << result.y);
	INFO("EXPECTED: " << expected.x << " " << expected.y);
	CHECK(Vec2ApproxEqual_Debug<precisionLevel>(result, expected));
}

template<gfxmath::FloatPrecision precisionLevel = gfxmath::FloatPrecision::HIGH>
inline void RunVec3Test(const gfxmath::Vec3& result, const gfxmath::Vec3& expected)
{
	INFO("RESULT: " << result.x << " " << result.y << " " << expected.z);
	INFO("EXPECTED: " << expected.x << " " << expected.y << " " << expected.z);
	CHECK(Vec3ApproxEqual_Debug<precisionLevel>(result, expected));
}

template<gfxmath::FloatPrecision precisionLevel = gfxmath::FloatPrecision::HIGH>
inline void RunVec4Test(const gfxmath::Vec4& result, const gfxmath::Vec4& expected)
{
	INFO("RESULT: " << result.x << " " << result.y << " " << result.z << " " << result.w);
	INFO("EXPECTED: " << expected.x << " " << expected.y << " " << expected.z << " " << expected.w);
	CHECK(Vec4ApproxEqual_Debug<precisionLevel>(result, expected));
}

#endif