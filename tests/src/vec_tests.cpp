#include "vec_tests.h"

using namespace gofxmath;
using namespace std;


bool Vec2IsNaN_Debug(const Vec2& vec)
{
	return isnan(vec.x) || isnan(vec.y);
}

bool Vec3IsNaN_Debug(const Vec3& vec)
{
	return isnan(vec.x) || isnan(vec.y) || isnan(vec.z);
}

bool Vec4IsNaN_Debug(const Vec4& vec)
{
	return isnan(vec.x) || isnan(vec.y) || isnan(vec.z) || isnan(vec.w);
}


bool Vec2IsInf_Debug(const Vec2& vec)
{
	return isinf(vec.x) || isinf(vec.y);
}

bool Vec3IsInf_Debug(const Vec3& vec)
{
	return isinf(vec.x) || isinf(vec.y) || isinf(vec.z);
}

bool Vec4IsInf_Debug(const Vec4& vec)
{
	return isinf(vec.x) || isinf(vec.y) || isinf(vec.z) || isinf(vec.w);
}


void CheckVec2IsNaN(const gofxmath::Vec2& vec)
{
	CHECK(Vec2IsNaN_Debug(vec));
}

void CheckVec3IsNaN(const gofxmath::Vec3& vec)
{
	CHECK(Vec3IsNaN_Debug(vec));
}

void CheckVec4IsNaN(const gofxmath::Vec4& vec)
{
	CHECK(Vec4IsNaN_Debug(vec));
}


void CheckVec2IsInfinite(const Vec2& result)
{
	CHECK(Vec2IsInf_Debug(result));
}

void CheckVec3IsInfinite(const Vec3& result)
{
	CHECK(Vec3IsInf_Debug(result));
}

void CheckVec4IsInfinite(const Vec4& result)
{
	CHECK(Vec4IsInf_Debug(result));
}


void RunVec2IsNaNTest(const Vec2& result, std::string info)
{
	INFO("Test " << info << " Vector <" << result << ">");
	CheckVec2IsNaN(result);
}

void RunVec3IsNaNTest(const Vec3& result, std::string info)
{
	INFO("Test " << info << " Vector <" << result << ">");
	CheckVec3IsNaN(result);
}

void RunVec4IsNaNTest(const Vec4& result, std::string info)
{
	INFO("Test " << info << " Vector <" << result << ">");
	CheckVec4IsNaN(result);
}

void RunVec2InfTest(const Vec2& result, std::string info)
{
	INFO("Test " << info << " Vector <" << result << ">");
	CheckVec2IsInfinite(result);
}

void RunVec3InfTest(const Vec3& result, std::string info)
{
	INFO("Test " << info << " Vector <" << result << ">");
	CheckVec3IsInfinite(result);
}

void RunVec4InfTest(const Vec4& result, std::string info)
{
	INFO("Test " << info << " Vector <" << result << ">");
	CheckVec4IsInfinite(result);
}



TEST_CASE("Vec2Add can add two 2D vectors","[Vec2][2D]")
{
	SECTION("Zero components")
	{
		Vec2 result = Vec2Add(Vec2::Zero(), Vec2::Zero());
		Vec2 expected = Vec2::Zero();

		RunVec2Test(result, expected);
	}

	SECTION("Positive components")
	{
		Vec2 first(1.0f, 2.0f);
		Vec2 second(3.0f, 4.0f);

		Vec2 result = Vec2Add(first, second);
		Vec2 expected(4.0f, 6.0f);

		RunVec2Test(result, expected);
	}

	SECTION("Negative components")
	{
		Vec2 first(-1.0f, -2.0f);
		Vec2 second(-3.0f, -4.0f);

		Vec2 result = Vec2Add(first, second);
		Vec2 expected(-4.0f, -6.0f);

		RunVec2Test(result, expected);
	}

	SECTION("Mixed components")
	{
		Vec2 first(-1.0f, 2.0f);
		Vec2 second(3.0f, -4.0f);

		Vec2 result = Vec2Add(first, second);
		Vec2 expected(2.0f, -2.0f);

		RunVec2Test(result, expected);
	}
}

TEST_CASE("Vec2Sub can subtract two 2D vectors", "[Vec2][2D]")
{
	SECTION("Zero components")
	{
		Vec2 result = Vec2Sub(Vec2::Zero(), Vec2::Zero());
		Vec2 expected = Vec2::Zero();

		RunVec2Test(result, expected);
	}

	SECTION("Positive components")
	{
		Vec2 first(1.0f, 2.0f);
		Vec2 second(3.0f, 5.0f);

		Vec2 result = Vec2Sub(first, second);
		Vec2 expected(-2.0f, -3.0f);

		RunVec2Test(result, expected);
	}

	SECTION("Negative components")
	{
		Vec2 first(-1.0f, -2.0f);
		Vec2 second(-3.0f, -5.0f);

		Vec2 result = Vec2Sub(first, second);
		Vec2 expected(2.0f, 3.0f);

		RunVec2Test(result, expected);
	}

	SECTION("Mixed components")
	{
		Vec2 first(-1.0f, 2.0f);
		Vec2 second(3.0f, -4.0f);

		Vec2 result = Vec2Sub(first, second);
		Vec2 expected(-4.0f, 6.0f);

		RunVec2Test(result, expected);
	}
}

TEST_CASE("Vec2Dot can calculate the dot product of a 2D vector", "[Vec2][2D]")
{
	SECTION("Zero Components")
	{
		Vec2 arg0 = Vec2::Zero();
		Vec2 arg1 = Vec2::Zero();
		INFO("ARG 0: " << arg0);
		INFO("Arg 1: " << arg1);
		float result = Vec2Dot(arg0, arg1);
		float expected = 0.0f;

		RunScalarTest(result, expected);
	}

	SECTION("Positive Components")
	{
		Vec2 arg0 = Vec2::One();
		Vec2 arg1 = Vec2::One();
		float result = Vec2Dot(arg0, arg1);
		float expected = 2.0f;

		INFO("ARG 0: " << arg0);
		INFO("Arg 1: " << arg1);
		RunScalarTest(result, expected);
	}

	SECTION("Negative Components")
	{
		Vec2 arg0 = Vec2::NegOne();
		Vec2 arg1 = Vec2::NegOne();
		float result = Vec2Dot(arg0, arg1);
		float expected = 2.0f;

		RunScalarTest(result, expected);
	}

	SECTION("Mixed Sign Components")
	{
		float result = Vec2Dot(Vec2::One(), Vec2::NegOne());
		float expected = -2.0f;

		RunScalarTest(result, expected);
	}

	SECTION("Non-zero Dot Zero Components")
	{
		float result = Vec2Dot(Vec2::One(), Vec2::Zero());
		float expected = 0.0f;

		RunScalarTest(result, expected);
	}
}

TEST_CASE("Vec2MulScalar can multiply a 2D vector by a scalar value", "[Vec2][2D]")
{
	SECTION("Zero components, zero scalar value")
	{
		Vec2 vecValue = Vec2::Zero();
		float scalarValue = 0.0f;

		Vec2 result = Vec2MulScalar(vecValue, scalarValue);
		Vec2 expected = Vec2::Zero();

		RunVec2Test(result, expected);
	}

	SECTION("Zero components, non-zero scalar value")
	{
		Vec2 vecValue = Vec2::Zero();
		float scalarValue = 2.0f;

		Vec2 result = Vec2MulScalar(vecValue, scalarValue);
		Vec2 expected = Vec2::Zero();

		RunVec2Test(result, expected);
	}

	SECTION("Non-zero components, Zero scalar value")
	{
		Vec2 vecValue(1.0f, 2.0f);
		float scalarValue = 0.0f;

		Vec2 result = Vec2MulScalar(vecValue, scalarValue);
		Vec2 expected = Vec2::Zero();

		RunVec2Test(result, expected);
	}

	SECTION("Positive components, positive scalar value")
	{
		Vec2 vecValue(1.0f, 2.0f);
		float scalarValue = 2.0f;

		Vec2 result = Vec2MulScalar(vecValue, scalarValue);
		Vec2 expected = Vec2(2.0f, 4.0f);

		RunVec2Test(result, expected);
	}

	SECTION("Negative components, positive scalar value")
	{
		Vec2 vecValue(-1.0f, -2.0f);
		float scalarValue = 2.0f;

		Vec2 result = Vec2MulScalar(vecValue, scalarValue);
		Vec2 expected = Vec2(-2.0f, -4.0f);

		RunVec2Test(result, expected);
	}

	SECTION("Positive components, negative scalar value")
	{
		Vec2 vecValue(1.0f, 2.0f);
		float scalarValue = -2.0f;

		Vec2 result = Vec2MulScalar(vecValue, scalarValue);
		Vec2 expected = Vec2(-2.0f, -4.0f);

		RunVec2Test(result, expected);
	}
}

TEST_CASE("Vec2DivScalar can multiply a 2D vector by a scalar value", "[Vec2][2D]")
{
	SECTION("Zero components, zero scalar value")
	{
		Vec2 vecValue = Vec2::Zero();
		float scalarValue = 0.0f;

		Vec2 result = Vec2DivScalar(vecValue, scalarValue);

		RunVec2IsNaNTest(result);
	}

	SECTION("Zero components, non-zero scalar value")
	{
		Vec2 vecValue = Vec2::Zero();
		float scalarValue = 2.0f;

		Vec2 result = Vec2DivScalar(vecValue, scalarValue);
		Vec2 expected = Vec2::Zero();

		RunVec2Test(result, expected);
	}

	SECTION("Non-zero components, Zero scalar value")
	{
		Vec2 vecValue(1.0f, 2.0f);
		float scalarValue = 0.0f;

		Vec2 result = Vec2DivScalar(vecValue, scalarValue);

		RunVec2InfTest(result);
	}

	SECTION("Positive components, positive scalar value")
	{
		Vec2 vecValue(1.0f, 2.0f);
		float scalarValue = 2.0f;

		Vec2 result = Vec2DivScalar(vecValue, scalarValue);
		Vec2 expected = Vec2(0.5f, 1.0f);

		RunVec2Test(result, expected);
	}

	SECTION("Negative components, positive scalar value")
	{
		Vec2 vecValue(-1.0f, -2.0f);
		float scalarValue = 2.0f;

		Vec2 result = Vec2DivScalar(vecValue, scalarValue);
		Vec2 expected = Vec2(-0.5f, -1.0f);

		RunVec2Test(result, expected);
	}

	SECTION("Positive components, negative scalar value")
	{
		Vec2 vecValue(1.0f, 2.0f);
		float scalarValue = -2.0f;

		Vec2 result = Vec2DivScalar(vecValue, scalarValue);
		Vec2 expected = Vec2(-0.5f, -1.0f);

		RunVec2Test(result, expected);
	}
}

TEST_CASE("Vec2Normalize can normalize a 2D vector", "[Vec2][2D]")
{
	SECTION("Zero Vector")
	{
		Vec2 value = Vec2::Zero();
		Vec2 result = Vec2Normalize(value);
		
		RunVec2IsNaNTest(result);
	}

	SECTION("Positive Unit Vector")
	{
		Vec2 value = Vec2::Right();
		Vec2 result = Vec2Normalize(value);
		Vec2 expected = Vec2::Right();

		RunVec2Test(result, expected);
	}

	SECTION("Negative Unit Vector")
	{
		Vec2 value = Vec2::Down();
		Vec2 result = Vec2Normalize(value);
		Vec2 expected = Vec2::Down();

		RunVec2Test(result, expected);
	}

	SECTION("Positive Arbitrary Vector")
	{
		// Using the pathagorean triple 3^2 + 4^2 = 5^2 to yield 
		// a simple, rational magnitude and result, to aid readability.
		Vec2 value = Vec2(3.0f, 4.0f);
		Vec2 result = Vec2Normalize(value);
		Vec2 expected = Vec2(0.6f, 0.8f);

		RunVec2Test(result, expected);
	}

	SECTION("Negative Arbitrary Vector")
	{
		// Using the pathagorean triple (-3)^2 + (-4)^2 = 5^2 to yield 
		// a simple, rational magnitude and result, to aid readability.
		Vec2 value = Vec2(-3.0f, -4.0f);
		Vec2 result = Vec2Normalize(value);
		Vec2 expected = Vec2(-0.6f, -0.8f);

		RunVec2Test(result, expected);
	}
}

TEST_CASE("Vec2Negate can negate a 2D vector", "[Vec2][2D]")
{
	SECTION("Zero Components")
	{
		Vec2 value = Vec2::Zero();
		Vec2 result = Vec2Negate(value);
		Vec2 expected = Vec2::Zero();

		RunVec2Test(result, expected);
	}

	SECTION("Positive Components")
	{
		Vec2 value(1.0f, 2.0f);
		Vec2 result = Vec2Negate(value);
		Vec2 expected = Vec2(-1.0f, -2.0f);

		RunVec2Test(result, expected);
	}

	SECTION("Negative Components")
	{
		Vec2 value(-1.0f, -2.0f);
		Vec2 result = Vec2Negate(value);
		Vec2 expected = Vec2(1.0f, 2.0f);

		RunVec2Test(result, expected);
	}

	SECTION("Mixed Components")
	{
		Vec2 value(-1.0f, 2.0f);
		Vec2 result = Vec2Negate(value);
		Vec2 expected = Vec2(1.0f, -2.0f);

		RunVec2Test(result, expected);
	}
}

TEST_CASE("Vec2HasNan can detect if a 2D vector contains a NaN value", "[Vec2][2D]")
{
	SECTION("No NaN components")
	{
		Vec2 value = Vec2::Zero();
		CHECK_FALSE(Vec2HasNaN(value));
	}

	SECTION("One NaN component")
	{
		Vec2 value(NAN, 0.0f);
		CHECK(Vec2HasNaN(value));
	}

	SECTION("Two NaN components")
	{
		Vec2 value(NAN, NAN);
		CHECK(Vec2HasNaN(value));
	}
}

TEST_CASE("Vec2HasInfinite can detect if a 2D vector contains a +/- Infinity value", "[Vec2][2D]")
{
	SECTION("No Inf components")
	{
		Vec2 value = Vec2::Zero();
		CHECK_FALSE(Vec2HasInfinite(value));
	}

	SECTION("One Inf component")
	{
		Vec2 value(Infinity(), 0.0f);
		CHECK(Vec2HasInfinite(value));
	}

	SECTION("Two Inf components")
	{
		Vec2 value(Infinity(), Infinity());
		CHECK(Vec2HasInfinite(value));
	}
}



TEST_CASE("Vec3Add can add two 3D vectors", "[Vec3][3D]")
{
	SECTION("Zero components")
	{
		Vec3 result = Vec3Add(Vec3::Zero(), Vec3::Zero());
		Vec3 expected = Vec3::Zero();

		RunVec3Test(result, expected);
	}

	SECTION("Positive components")
	{
		Vec3 first(1.0f, 2.0f, 3.0f);
		Vec3 second(4.0f, 5.0f, 6.0f);

		Vec3 result = Vec3Add(first, second);
		Vec3 expected(5.0f, 7.0f, 9.0f);

		RunVec3Test(result, expected);
	}

	SECTION("Negative components")
	{
		Vec3 first(-1.0f, -2.0f, -3.0f);
		Vec3 second(-4.0f, -5.0f, -6.0f);

		Vec3 result = Vec3Add(first, second);
		Vec3 expected(-5.0f, -7.0f, -9.0f);

		RunVec3Test(result, expected);
	}

	SECTION("Mixed components")
	{
		Vec3 first(-1.0f, 2.0f, -3.0f);
		Vec3 second(4.0f, -5.0f, 7.0f);

		Vec3 result = Vec3Add(first, second);
		Vec3 expected(3.0f, -3.0f, 4.0f);

		RunVec3Test(result, expected);
	}
}

TEST_CASE("Vec3Sub can subtract two 3D vectors", "[Vec3][3D]")
{
	SECTION("Zero components")
	{
		Vec3 result = Vec3Sub(Vec3::Zero(), Vec3::Zero());
		Vec3 expected = Vec3::Zero();

		RunVec3Test(result, expected);
	}

	SECTION("Positive components")
	{
		Vec3 first(1.0f, 2.0f, 3.0f);
		Vec3 second(3.0f, 5.0f, 7.0f);

		Vec3 result = Vec3Sub(first, second);
		Vec3 expected(-2.0f, -3.0f, -4.0f);

		RunVec3Test(result, expected);
	}

	SECTION("Negative components")
	{
		Vec3 first(-1.0f, -2.0f, -3.0f);
		Vec3 second(-3.0f, -5.0f, -7.0f);

		Vec3 result = Vec3Sub(first, second);
		Vec3 expected(2.0f, 3.0f, 4.0f);

		RunVec3Test(result, expected);
	}

	SECTION("Mixed components")
	{
		Vec3 first(-1.0f, 2.0f, -3.0f);
		Vec3 second(3.0f, -5.0f, 7.0f);

		Vec3 result = Vec3Sub(first, second);
		Vec3 expected(-4.0f, 7.0f, -10.0f);

		RunVec3Test(result, expected);
	}
}

TEST_CASE("Vec3Dot can calculate the dot product of a 3D vector", "[Vec3][3D]")
{
	SECTION("Zero Components")
	{
		Vec3 arg0 = Vec3::Zero();
		Vec3 arg1 = Vec3::Zero();
		INFO("ARG 0: " << arg0);
		INFO("Arg 1: " << arg1);
		float result = Vec3Dot(arg0, arg1);
		float expected = 0.0f;

		RunScalarTest(result, expected);
	}

	SECTION("Positive Components")
	{
		Vec3 arg0 = Vec3::One();
		Vec3 arg1 = Vec3::One();
		float result = Vec3Dot(arg0, arg1);
		float expected = 3.0f;

		INFO("ARG 0: " << arg0);
		INFO("Arg 1: " << arg1);
		RunScalarTest(result, expected);
	}

	SECTION("Negative Components")
	{
		Vec3 arg0 = Vec3::NegOne();
		Vec3 arg1 = Vec3::NegOne();
		float result = Vec3Dot(arg0, arg1);
		float expected = 3.0f;

		RunScalarTest(result, expected);
	}

	SECTION("Mixed Sign Components")
	{
		float result = Vec3Dot(Vec3::One(), Vec3::NegOne());
		float expected = -3.0f;

		RunScalarTest(result, expected);
	}

	SECTION("Non-zero Dot Zero Components")
	{
		float result = Vec3Dot(Vec3::One(), Vec3::Zero());
		float expected = 0.0f;

		RunScalarTest(result, expected);
	}
}

TEST_CASE("Vec3MulScalar can multiply a 3D vector by a scalar value", "[Vec3][3D]")
{
	SECTION("Zero components, zero scalar value")
	{
		Vec3 vecValue = Vec3::Zero();
		float scalarValue = 0.0f;

		Vec3 result = Vec3MulScalar(vecValue, scalarValue);
		Vec3 expected = Vec3::Zero();

		RunVec3Test(result, expected);
	}

	SECTION("Zero components, non-zero scalar value")
	{
		Vec3 vecValue = Vec3::Zero();
		float scalarValue = 2.0f;

		Vec3 result = Vec3MulScalar(vecValue, scalarValue);
		Vec3 expected = Vec3::Zero();

		RunVec3Test(result, expected);
	}

	SECTION("Non-zero components, Zero scalar value")
	{
		Vec3 vecValue(1.0f, 2.0f, 3.0f);
		float scalarValue = 0.0f;

		Vec3 result = Vec3MulScalar(vecValue, scalarValue);
		Vec3 expected = Vec3::Zero();

		RunVec3Test(result, expected);
	}

	SECTION("Positive components, positive scalar value")
	{
		Vec3 vecValue(1.0f, 2.0f, 3.0f);
		float scalarValue = 2.0f;

		Vec3 result = Vec3MulScalar(vecValue, scalarValue);
		Vec3 expected = Vec3(2.0f, 4.0f, 6.0f);

		RunVec3Test(result, expected);
	}

	SECTION("Negative components, positive scalar value")
	{
		Vec3 vecValue(-1.0f, -2.0f, -3.0f);
		float scalarValue = 2.0f;

		Vec3 result = Vec3MulScalar(vecValue, scalarValue);
		Vec3 expected = Vec3(-2.0f, -4.0f, -6.0f);

		RunVec3Test(result, expected);
	}

	SECTION("Positive components, negative scalar value")
	{
		Vec3 vecValue(1.0f, 2.0f, 3.0f);
		float scalarValue = -2.0f;

		Vec3 result = Vec3MulScalar(vecValue, scalarValue);
		Vec3 expected = Vec3(-2.0f, -4.0f, -6.0f);

		RunVec3Test(result, expected);
	}
}

TEST_CASE("Vec3DivScalar can multiply a 3D vector by a scalar value", "[Vec3][3D]")
{
	SECTION("Zero components, zero scalar value")
	{
		Vec3 vecValue = Vec3::Zero();
		float scalarValue = 0.0f;

		Vec3 result = Vec3DivScalar(vecValue, scalarValue);

		RunVec3IsNaNTest(result);
	}

	SECTION("Zero components, non-zero scalar value")
	{
		Vec3 vecValue = Vec3::Zero();
		float scalarValue = 2.0f;

		Vec3 result = Vec3DivScalar(vecValue, scalarValue);
		Vec3 expected = Vec3::Zero();

		RunVec3Test(result, expected);
	}

	SECTION("Non-zero components, Zero scalar value")
	{
		Vec3 vecValue(1.0f, 2.0f, 3.0f);
		float scalarValue = 0.0f;

		Vec3 result = Vec3DivScalar(vecValue, scalarValue);

		RunVec3InfTest(result);
	}

	SECTION("Positive components, positive scalar value")
	{
		Vec3 vecValue(1.0f, 2.0f, 3.0f);
		float scalarValue = 2.0f;

		Vec3 result = Vec3DivScalar(vecValue, scalarValue);
		Vec3 expected = Vec3(0.5f, 1.0f, 1.5f);

		RunVec3Test(result, expected);
	}

	SECTION("Negative components, positive scalar value")
	{
		Vec3 vecValue(-1.0f, -2.0f, -3.0f);
		float scalarValue = 2.0f;

		Vec3 result = Vec3DivScalar(vecValue, scalarValue);
		Vec3 expected = Vec3(-0.5f, -1.0f, -1.5f);

		RunVec3Test(result, expected);
	}

	SECTION("Positive components, negative scalar value")
	{
		Vec3 vecValue(1.0f, 2.0f, 3.0f);
		float scalarValue = -2.0f;

		Vec3 result = Vec3DivScalar(vecValue, scalarValue);
		Vec3 expected = Vec3(-0.5f, -1.0f, -1.5f);

		RunVec3Test(result, expected);
	}
}

TEST_CASE("Vec3Normalize can normalize a 3D vector", "[Vec3][3D]")
{
	SECTION("Zero Vector")
	{
		Vec3 value = Vec3::Zero();
		Vec3 result = Vec3Normalize(value);

		RunVec3IsNaNTest(result);
	}

	SECTION("Positive Unit Vector")
	{
		Vec3 value = Vec3::Right();
		Vec3 result = Vec3Normalize(value);
		Vec3 expected = Vec3::Right();

		RunVec3Test(result, expected);
	}

	SECTION("Negative Unit Vector")
	{
		Vec3 value = Vec3::Down();
		Vec3 result = Vec3Normalize(value);
		Vec3 expected = Vec3::Down();

		RunVec3Test(result, expected);
	}

	SECTION("Positive Arbitrary Vector")
	{
		// Using the pathagorean quadruple 12^2 + 15^2 + 16^2 = 25^2 to yield 
		// a simple, rational magnitude and result, to aid readability.
		Vec3 value = Vec3(12.0f, 15.0f, 16.0f);
		Vec3 result = Vec3Normalize(value);
		Vec3 expected = Vec3(0.48f, 0.6f, 0.64f);

		RunVec3Test(result, expected);
	}

	SECTION("Negative Arbitrary Vector")
	{
		// Using the pathagorean quadruple (-12)^2 + (-15)^2 + (-16)^2 = 25^2 to yield 
		// a simple, rational magnitude and result, to aid readability.
		Vec3 value = Vec3(-12.0f, -15.0f, -16.0f);
		Vec3 result = Vec3Normalize(value);
		Vec3 expected = Vec3(-0.48f, -0.6f, -0.64f);

		RunVec3Test(result, expected);
	}
}

TEST_CASE("Vec3Negate can negate a 3D vector", "[Vec3][3D]")
{
	SECTION("Zero Components")
	{
		Vec3 value = Vec3::Zero();
		Vec3 result = Vec3Negate(value);
		Vec3 expected = Vec3::Zero();

		RunVec3Test(result, expected);
	}

	SECTION("Positive Components")
	{
		Vec3 value(1.0f, 2.0f, 3.0f);
		Vec3 result = Vec3Negate(value);
		Vec3 expected = Vec3(-1.0f, -2.0f, -3.0f);

		RunVec3Test(result, expected);
	}

	SECTION("Negative Components")
	{
		Vec3 value(-1.0f, -2.0f, -3.0f);
		Vec3 result = Vec3Negate(value);
		Vec3 expected = Vec3(1.0f, 2.0f, 3.0f);

		RunVec3Test(result, expected);
	}

	SECTION("Mixed Components")
	{
		Vec3 value(-1.0f, 2.0f, -3.0f);
		Vec3 result = Vec3Negate(value);
		Vec3 expected = Vec3(1.0f, -2.0f, 3.0f);

		RunVec3Test(result, expected);
	}
}

TEST_CASE("Vec3HasNan can detect if a 3D vector contains a NaN value", "[Vec3][3D]")
{
	SECTION("No NaN components")
	{
		Vec3 value = Vec3::Zero();
		CHECK_FALSE(Vec3HasNaN(value));
	}

	SECTION("One NaN component")
	{
		Vec3 value(NAN, 0.0f, 0.0f);
		CHECK(Vec3HasNaN(value));
	}

	SECTION("Two NaN components")
	{
		Vec3 value(NAN, NAN, 0.0f);
		CHECK(Vec3HasNaN(value));
	}

	SECTION("Three NaN components")
	{
		Vec3 value(NAN, NAN, NAN);
		CHECK(Vec3HasNaN(value));
	}
}

TEST_CASE("Vec3HasInfinite can detect if a 3D vector contains a +/- Infinity value", "[Vec3][3D]")
{
	SECTION("No Inf components")
	{
		Vec3 value = Vec3::Zero();
		CHECK_FALSE(Vec3HasInfinite(value));
	}

	SECTION("One Inf component")
	{
		Vec3 value(Infinity(), 0.0f, 0.0f);
		CHECK(Vec3HasInfinite(value));
	}

	SECTION("Two Inf components")
	{
		Vec3 value(Infinity(), Infinity(), 0.0f);
		CHECK(Vec3HasInfinite(value));
	}

	SECTION("Three Inf components")
	{
		Vec3 value(Infinity(), Infinity(), Infinity());
		CHECK(Vec3HasInfinite(value));
	}
}



TEST_CASE("Vec4Add can add two 4D vectors", "[Vec4][4D]")
{
	SECTION("Zero components")
	{
		Vec4 result = Vec4Add(Vec4::Zero(), Vec4::Zero());
		Vec4 expected = Vec4::Zero();

		RunVec4Test(result, expected);
	}

	SECTION("Positive components")
	{
		Vec4 first(1.0f, 2.0f, 3.0f, 4.0f);
		Vec4 second(5.0f, 6.0f, 7.0f, 8.0f);

		Vec4 result = Vec4Add(first, second);
		Vec4 expected(6.0f, 8.0f, 10.0f, 12.0f);

		RunVec4Test(result, expected);
	}

	SECTION("Negative components")
	{
		Vec4 first(-1.0f, -2.0f, -3.0f, -4.0f);
		Vec4 second(-5.0f, -6.0f, -7.0f, -8.0f);

		Vec4 result = Vec4Add(first, second);
		Vec4 expected(-6.0f, -8.0f, -10.0f, -12.0f);

		RunVec4Test(result, expected);
	}

	SECTION("Mixed components")
	{
		Vec4 first(-1.0f, 2.0f, -3.0f, 4.0f);
		Vec4 second(5.0f, -7.0f, 9.0f, -11.0f);

		Vec4 result = Vec4Add(first, second);
		Vec4 expected(4.0f, -5.0f, 6.0f, -7.0f);

		RunVec4Test(result, expected);
	}
}

TEST_CASE("Vec4Sub can subtract two 4D vectors", "[Vec4][4D]")
{
	SECTION("Zero components")
	{
		Vec4 result = Vec4Sub(Vec4::Zero(), Vec4::Zero());
		Vec4 expected = Vec4::Zero();

		RunVec4Test(result, expected);
	}

	SECTION("Positive components")
	{
		Vec4 first(1.0f, 2.0f, 3.0f, 4.0f);
		Vec4 second(5.0f, 7.0f, 9.0f, 11.0f);

		Vec4 result = Vec4Sub(first, second);
		Vec4 expected(-4.0f, -5.0f, -6.0f, -7.0f);

		RunVec4Test(result, expected);
	}

	SECTION("Negative components")
	{
		Vec4 first(-1.0f, -2.0f, -3.0f, -4.0f);
		Vec4 second(-5.0f, -7.0f, -9.0f, -11.0f);

		Vec4 result = Vec4Sub(first, second);
		Vec4 expected(4.0f, 5.0f, 6.0f, 7.0f);

		RunVec4Test(result, expected);
	}

	SECTION("Mixed components")
	{
		Vec4 first(-1.0f, 2.0f, -3.0f, 4.0f);
		Vec4 second(5.0f, -7.0f, 9.0f, -11.0f);

		Vec4 result = Vec4Sub(first, second);
		Vec4 expected(-6.0f, 9.0f, -12.0f, 15.0f);

		RunVec4Test(result, expected);
	}
}

TEST_CASE("Vec4Dot can calculate the dot product of a 4D vector", "[Vec4][4D]")
{
	SECTION("Zero Components")
	{
		Vec4 arg0 = Vec4::Zero();
		Vec4 arg1 = Vec4::Zero();
		INFO("ARG 0: " << arg0);
		INFO("Arg 1: " << arg1);
		float result = Vec4Dot(arg0, arg1);
		float expected = 0.0f;

		RunScalarTest(result, expected);
	}

	SECTION("Positive Components")
	{
		Vec4 arg0 = Vec4::One();
		Vec4 arg1 = Vec4::One();
		float result = Vec4Dot(arg0, arg1);
		float expected = 4.0f;

		INFO("ARG 0: " << arg0);
		INFO("Arg 1: " << arg1);
		RunScalarTest(result, expected);
	}

	SECTION("Negative Components")
	{
		Vec4 arg0 = Vec4::NegOne();
		Vec4 arg1 = Vec4::NegOne();
		float result = Vec4Dot(arg0, arg1);
		float expected = 4.0f;

		INFO("ARG 0: " << arg0);
		INFO("Arg 1: " << arg1);
		RunScalarTest(result, expected);
	}

	SECTION("Mixed Sign Components")
	{
		Vec4 arg0 = Vec4::One();
		Vec4 arg1 = Vec4::NegOne();
		float result = Vec4Dot(arg0, arg1);
		float expected = -4.0f;

		INFO("ARG 0: " << arg0);
		INFO("Arg 1: " << arg1);
		RunScalarTest(result, expected);
	}

	SECTION("Non-zero Dot Zero Components")
	{
		Vec4 arg0 = Vec4::One();
		Vec4 arg1 = Vec4::Zero();
		float result = Vec4Dot(arg0, arg1);
		float expected = 0.0f;

		INFO("ARG 0: " << arg0);
		INFO("Arg 1: " << arg1);
		RunScalarTest(result, expected);
	}
}

TEST_CASE("Vec4MulScalar can multiply a 4D vector by a scalar value", "[Vec4][4D]")
{
	SECTION("Zero components, zero scalar value")
	{
		Vec4 vecValue = Vec4::Zero();
		float scalarValue = 0.0f;

		Vec4 result = Vec4MulScalar(vecValue, scalarValue);
		Vec4 expected = Vec4::Zero();

		RunVec4Test(result, expected);
	}

	SECTION("Zero components, non-zero scalar value")
	{
		Vec4 vecValue = Vec4::Zero();
		float scalarValue = 2.0f;

		Vec4 result = Vec4MulScalar(vecValue, scalarValue);
		Vec4 expected = Vec4::Zero();

		RunVec4Test(result, expected);
	}

	SECTION("Non-zero components, Zero scalar value")
	{
		Vec4 vecValue(1.0f, 2.0f, 3.0f, 4.0f);
		float scalarValue = 0.0f;

		Vec4 result = Vec4MulScalar(vecValue, scalarValue);
		Vec4 expected = Vec4::Zero();

		RunVec4Test(result, expected);
	}

	SECTION("Positive components, positive scalar value")
	{
		Vec4 vecValue(1.0f, 2.0f, 3.0f, 4.0f);
		float scalarValue = 2.0f;

		Vec4 result = Vec4MulScalar(vecValue, scalarValue);
		Vec4 expected = Vec4(2.0f, 4.0f, 6.0f, 8.0f);

		RunVec4Test(result, expected);
	}

	SECTION("Negative components, positive scalar value")
	{
		Vec4 vecValue(-1.0f, -2.0f, -3.0f, -4.0f);
		float scalarValue = 2.0f;

		Vec4 result = Vec4MulScalar(vecValue, scalarValue);
		Vec4 expected = Vec4(-2.0f, -4.0f, -6.0f, -8.0f);

		RunVec4Test(result, expected);
	}

	SECTION("Positive components, negative scalar value")
	{
		Vec4 vecValue(1.0f, 2.0f, 3.0f, 4.0f);
		float scalarValue = -2.0f;

		Vec4 result = Vec4MulScalar(vecValue, scalarValue);
		Vec4 expected = Vec4(-2.0f, -4.0f, -6.0f, -8.0f);

		RunVec4Test(result, expected);
	}
}

TEST_CASE("Vec4DivScalar can multiply a 4D vector by a scalar value", "[Vec4][4D]")
{
	SECTION("Zero components, zero scalar value")
	{
		Vec4 vecValue = Vec4::Zero();
		float scalarValue = 0.0f;

		Vec4 result = Vec4DivScalar(vecValue, scalarValue);

		RunVec4IsNaNTest(result);
	}

	SECTION("Zero components, non-zero scalar value")
	{
		Vec4 vecValue = Vec4::Zero();
		float scalarValue = 2.0f;

		Vec4 result = Vec4DivScalar(vecValue, scalarValue);
		Vec4 expected = Vec4::Zero();

		RunVec4Test(result, expected);
	}

	SECTION("Non-zero components, Zero scalar value")
	{
		Vec4 vecValue(1.0f, 2.0f, 3.0f, 4.0f);
		float scalarValue = 0.0f;

		Vec4 result = Vec4DivScalar(vecValue, scalarValue);

		RunVec4InfTest(result);
	}

	SECTION("Positive components, positive scalar value")
	{
		Vec4 vecValue(1.0f, 2.0f, 3.0f, 4.0f);
		float scalarValue = 2.0f;

		Vec4 result = Vec4DivScalar(vecValue, scalarValue);
		Vec4 expected = Vec4(0.5f, 1.0f, 1.5f, 2.0f);

		RunVec4Test(result, expected);
	}

	SECTION("Negative components, positive scalar value")
	{
		Vec4 vecValue(-1.0f, -2.0f, -3.0f, -4.0f);
		float scalarValue = 2.0f;

		Vec4 result = Vec4DivScalar(vecValue, scalarValue);
		Vec4 expected = Vec4(-0.5f, -1.0f, -1.5f, -2.0f);

		RunVec4Test(result, expected);
	}

	SECTION("Positive components, negative scalar value")
	{
		Vec4 vecValue(1.0f, 2.0f, 3.0f, 4.0f);
		float scalarValue = -2.0f;

		Vec4 result = Vec4DivScalar(vecValue, scalarValue);
		Vec4 expected = Vec4(-0.5f, -1.0f, -1.5f, -2.0f);

		RunVec4Test(result, expected);
	}
}

TEST_CASE("Vec4Normalize can normalize a 4D vector", "[Vec4][4D]")
{
	SECTION("Zero Vector")
	{
		Vec4 value = Vec4::Zero();
		Vec4 result = Vec4Normalize(value);

		RunVec4IsNaNTest(result);
	}

	SECTION("Positive Unit Vector")
	{
		Vec4 value = Vec4::E0();
		Vec4 result = Vec4Normalize(value);
		Vec4 expected = Vec4::E0();

		RunVec4Test(result, expected);
	}

	SECTION("Negative Unit Vector")
	{
		Vec4 value = Vec4::NegE1();
		Vec4 result = Vec4Normalize(value);
		Vec4 expected = Vec4::NegE1();

		RunVec4Test(result, expected);
	}

	SECTION("Positive Arbitrary Vector")
	{
		// Using the pathagorean quintuple 2^2 + 5^2 + 14^2 + 20^2 = 25^2 to yield 
		// a simple, rational magnitude and result, to aid readability.
		Vec4 value = Vec4(2.0f, 5.0f, 14.0f, 20.0f);
		Vec4 result = Vec4Normalize(value);
		Vec4 expected = Vec4(0.08f, 0.2f, 0.56f, 0.8f);

		RunVec4Test(result, expected);
	}

	SECTION("Negative Arbitrary Vector")
	{
		// Using the pathagorean quintuple (-2)^2 + (-5)^2 + (-14)^2 + (-20)^2 = 25^2 to yield 
		// a simple, rational magnitude and result, to aid readability.
		Vec4 value = Vec4(-2.0f, -5.0f, -14.0f, -20.0f);
		Vec4 result = Vec4Normalize(value);
		Vec4 expected = Vec4(-0.08f, -0.2f, -0.56f, -0.8f);

		RunVec4Test(result, expected);
	}
}

TEST_CASE("Vec4Negate can negate a 4D vector", "[Vec4][4D]")
{
	SECTION("Zero Components")
	{
		Vec4 value = Vec4::Zero();
		Vec4 result = Vec4Negate(value);
		Vec4 expected = Vec4::Zero();

		RunVec4Test(result, expected);
	}

	SECTION("Positive Components")
	{
		Vec4 value(1.0f, 2.0f, 3.0f, 4.0f);
		Vec4 result = Vec4Negate(value);
		Vec4 expected = Vec4(-1.0f, -2.0f, -3.0f, -4.0f);

		RunVec4Test(result, expected);
	}

	SECTION("Negative Components")
	{
		Vec4 value(-1.0f, -2.0f, -3.0f, -4.0f);
		Vec4 result = Vec4Negate(value);
		Vec4 expected = Vec4(1.0f, 2.0f, 3.0f, 4.0f);

		RunVec4Test(result, expected);
	}

	SECTION("Mixed Components")
	{
		Vec4 value(-1.0f, 2.0f, -3.0f, 4.0f);
		Vec4 result = Vec4Negate(value);
		Vec4 expected = Vec4(1.0f, -2.0f, 3.0f, -4.0f);

		RunVec4Test(result, expected);
	}
}

TEST_CASE("Vec4HasNan can detect if a 4D vector contains a NaN value", "[Vec4][4D]")
{
	SECTION("No NaN components")
	{
		Vec4 value = Vec4::Zero();
		CHECK_FALSE(Vec4HasNaN(value));
	}

	SECTION("One NaN component")
	{
		Vec4 value(NAN, 0.0f, 0.0f, 0.0f);
		CHECK(Vec4HasNaN(value));
	}

	SECTION("Two NaN components")
	{
		Vec4 value(NAN, NAN, 0.0f, 0.0f);
		CHECK(Vec4HasNaN(value));
	}

	SECTION("Three NaN components")
	{
		Vec4 value(NAN, NAN, NAN, 0.0f);
		CHECK(Vec4HasNaN(value));
	}

	SECTION("Four NaN components")
	{
		Vec4 value(NAN, NAN, NAN, NAN);
		CHECK(Vec4HasNaN(value));
	}
}

TEST_CASE("Vec4HasInfinite can detect if a 4D vector contains a +/- Infinity value", "[Vec4][4D]")
{
	SECTION("No Inf components")
	{
		Vec4 value = Vec4::Zero();
		CHECK_FALSE(Vec4HasInfinite(value));
	}

	SECTION("One Inf component")
	{
		Vec4 value(Infinity(), 0.0f, 0.0f, 0.0f);
		CHECK(Vec4HasInfinite(value));
	}

	SECTION("Two Inf components")
	{
		Vec4 value(Infinity(), Infinity(), 0.0f, 0.0f);
		CHECK(Vec4HasInfinite(value));
	}

	SECTION("Three Inf components")
	{
		Vec4 value(Infinity(), Infinity(), Infinity(), 0.0f);
		CHECK(Vec4HasInfinite(value));
	}

	SECTION("Four Inf components")
	{
		Vec4 value(Infinity(), Infinity(), Infinity(), Infinity());
		CHECK(Vec4HasInfinite(value));
	}
}


TEST_CASE("QuaternionNormalize can normalize a Quaternion", "[Quaternion]")
{
	SECTION("Zero Vector")
	{
		Quaternion value = (Quaternion)Vec4::Zero();
		Quaternion result = QuaternionNormalize(value);

		RunVec4IsNaNTest(result);
	}

	SECTION("Positive Unit Vector")
	{
		Quaternion value = (Quaternion)Vec4::E0();
		Quaternion result = QuaternionNormalize(value);
		Quaternion expected = (Quaternion)Vec4::E0();

		RunVec4Test(result, expected);
	}

	SECTION("Negative Unit Vector")
	{
		Quaternion value = (Quaternion)Vec4::NegE1();
		Quaternion result = QuaternionNormalize(value);
		Quaternion expected = (Quaternion)Vec4::NegE1();

		RunVec4Test(result, expected);
	}

	SECTION("Positive Arbitrary Vector")
	{
		// Using the pathagorean quintuple 2^2 + 5^2 + 14^2 + 20^2 = 25^2 to yield 
		// a simple, rational magnitude and result, to aid readability.
		Quaternion value = Quaternion(2.0f, 5.0f, 14.0f, 20.0f);
		Quaternion result = QuaternionNormalize(value);
		Quaternion expected = Quaternion(0.08f, 0.2f, 0.56f, 0.8f);

		RunVec4Test(result, expected);
	}

	SECTION("Negative Arbitrary Vector")
	{
		// Using the pathagorean quintuple (-2)^2 + (-5)^2 + (-14)^2 + (-20)^2 = 25^2 to yield 
		// a simple, rational magnitude and result, to aid readability.
		Quaternion value = Quaternion(-2.0f, -5.0f, -14.0f, -20.0f);
		Quaternion result = QuaternionNormalize(value);
		Quaternion expected = Quaternion(-0.08f, -0.2f, -0.56f, -0.8f);

		RunVec4Test(result, expected);
	}
}

TEST_CASE("QuaternionMultiply can multiply two quaternions and yield the normalized result", "[Quaternion]")
{
	Quaternion q0 = (Quaternion)Vec4::One();
	Quaternion q1 = (Quaternion)Vec4::One();

	Quaternion result = QuaternionMultiply(q0, q1);
	Quaternion expected(2.0f, 2.0f, 2.0f, -2.0f);

	RunVec4Test(result, expected);
}

TEST_CASE("QuaternionLerp can linearly interpolate between two quaternions", "[Quaternion]")
{
	Quaternion q0 = (Quaternion)Vec4::E0();
	Quaternion q1 = (Quaternion)Vec4::E1();
	float weight = 0.25f;
	float mag_25_75 = sqrtf(0.75f * 0.75f + 0.25f * 0.25f);

	Quaternion result = QuaternionLerp(q0, q1, weight);
	Quaternion expected = Quaternion(0.75f / mag_25_75, 0.25f / mag_25_75, 0.0f, 0.0f);

	RunVec4Test(result, expected);
}

TEST_CASE("QuaternionFromAxisAngle can produce a rotation quaternion from an axis-angle", "[Quaternion]")
{
	Vec3 axis = Vec3(1.0f, 0.0f, 0.0f); 
	float angle = F_PI_2; 

	Quaternion result = QuaternionFromAxisAngle(axis, angle);
	Quaternion expected = Quaternion(F_1_SQRT2, 0.0f, 0.0f, F_1_SQRT2);

	RunVec4Test(result, expected);
}

TEST_CASE("QuaternionFromEuler can produce a rotation quaternion from a 3D euler angle vector", "[Quaternion]")
{
	Vec3 euler = Vec3(F_PI_2, 0.0f, 0.0f);

	Quaternion result = QuaternionFromEuler(euler);
	Quaternion expected = Quaternion(F_1_SQRT2, 0.0f, 0.0f, F_1_SQRT2);

	RunVec4Test(result, expected);
}

TEST_CASE("Vec3Cross can calculate the cross product of two Vec3s", "[Vec3][3D]")
{
	SECTION("Unit Vectors")
	{
		Vec3 arg0 = Vec3::Right();
		Vec3 arg1 = Vec3::Up();
		Vec3 result = Vec3Cross(arg0, arg1);
		Vec3 expected = Vec3::Forward();

		RunVec3Test(result, expected);
	}

	SECTION("Non-unit vectors")
	{
		SECTION("Vector Crossed with itself")
		{
			Vec3 arg0 = Vec3::One();
			Vec3 arg1 = Vec3::One();

			Vec3 result = Vec3Cross(arg0, arg1);
			Vec3 expected = Vec3::Zero();

			RunVec3Test(result, expected);
		}

		SECTION("Arbitrary Unit Vectors")
		{
			Vec3 arg0 = Vec3(1.0f, 1.0f, 0.0f);
			Vec3 arg1 = Vec3(0.0f, 1.0f, 1.0f);

			Vec3 result = Vec3Cross(arg0, arg1);
			Vec3 expected = Vec3(1.0f, -1.0f, 1.0f);

			RunVec3Test(result, expected);
		}
	}		
}