#ifndef VEC_TESTS_DOT_H
#define VEC_TESTS_DOT_H
#include "vecmath.h"
#include "scalar_tests.h"

void CheckVec2IsInfinite(const gofxmath::Vec2& vec);
void CheckVec3IsInfinite(const gofxmath::Vec3& vec);
void CheckVec4IsInfinite(const gofxmath::Vec4& vec);

void CheckVec2IsNaN(const gofxmath::Vec2& vec);
void CheckVec3IsNaN(const gofxmath::Vec3& vec);
void CheckVec4IsNaN(const gofxmath::Vec4& vec);

void RunVec2IsNaNTest(const gofxmath::Vec2& result, std::string info = "");
void RunVec3IsNaNTest(const gofxmath::Vec3& result, std::string info = "");
void RunVec4IsNaNTest(const gofxmath::Vec4& result, std::string info = "");

void RunVec2InfTest(const gofxmath::Vec2& result, std::string info = "");
void RunVec3InfTest(const gofxmath::Vec3& result, std::string info = "");
void RunVec4InfTest(const gofxmath::Vec4& result, std::string info = "");



template<gofxmath::FloatPrecision precisionLevel = gofxmath::FloatPrecision::HIGH>
inline bool Vec2ApproxEqual_Debug(const gofxmath::Vec2& left, const gofxmath::Vec2& right)
{
	return ApproxEqual_Debug<precisionLevel>(left.x, right.x) && ApproxEqual_Debug<precisionLevel>(left.y, right.y);
}

template<gofxmath::FloatPrecision precisionLevel = gofxmath::FloatPrecision::HIGH>
inline bool Vec3ApproxEqual_Debug(const gofxmath::Vec3& left, const gofxmath::Vec3& right)
{
	return ApproxEqual_Debug<precisionLevel>(left.x, right.x) && ApproxEqual_Debug<precisionLevel>(left.y, right.y) && ApproxEqual_Debug<precisionLevel>(left.z, right.z);
}

template<gofxmath::FloatPrecision precisionLevel = gofxmath::FloatPrecision::HIGH>
inline bool Vec4ApproxEqual_Debug(const gofxmath::Vec4& left, const gofxmath::Vec4& right)
{
	return ApproxEqual_Debug<precisionLevel>(left.x, right.x) && ApproxEqual_Debug<precisionLevel>(left.y, right.y) && ApproxEqual_Debug<precisionLevel>(left.z, right.z) && ApproxEqual_Debug<precisionLevel>(left.w, right.w);
}


template<gofxmath::FloatPrecision precisionLevel = gofxmath::FloatPrecision::HIGH>
inline void RunVec2Test(const gofxmath::Vec2& result, const gofxmath::Vec2& expected)
{
	INFO("RESULT: " << result.x << " " << result.y);
	INFO("EXPECTED: " << expected.x << " " << expected.y);
	CHECK(Vec2ApproxEqual_Debug<precisionLevel>(result, expected));
}

template<gofxmath::FloatPrecision precisionLevel = gofxmath::FloatPrecision::HIGH>
inline void RunVec3Test(const gofxmath::Vec3& result, const gofxmath::Vec3& expected)
{
	INFO("RESULT: " << result.x << " " << result.y << " " << expected.z);
	INFO("EXPECTED: " << expected.x << " " << expected.y << " " << expected.z);
	CHECK(Vec3ApproxEqual_Debug<precisionLevel>(result, expected));
}

template<gofxmath::FloatPrecision precisionLevel = gofxmath::FloatPrecision::HIGH>
inline void RunVec4Test(const gofxmath::Vec4& result, const gofxmath::Vec4& expected)
{
	INFO("RESULT: " << result.x << " " << result.y << " " << result.z << " " << result.w);
	INFO("EXPECTED: " << expected.x << " " << expected.y << " " << expected.z << " " << expected.w);
	CHECK(Vec4ApproxEqual_Debug<precisionLevel>(result, expected));
}

#endif