#include "ssevec_tests.h"
#include <array>

using namespace gfxmath;
using namespace std;

const float SMALL = Epsilon();
const float MED = 1.0f;
const float BIG = sqrt(FloatMax()) * 0.1f;
const float MAX = FloatMax();

const float SQRT_2 = 1.414213562373195f;
const float SQRT_3 = 1.732050807568877f;
const float SQRT_2_OVER_2 = 0.7071067811865f;
const float SQRT_3_OVER_3 = 0.5773502691896f;

const float SMALL_SQR = SMALL * SMALL;
const float MED_SQR = MED * MED;
const float BIG_SQR = BIG * BIG;

const float MED_BIG = MED * BIG;

const Vec4 V_PI = { F_PI };
const Vec4 V_2PI = { F_2PI };
const Vec4 V_PI_2 = { F_PI_2 };
const Vec4 V_3PI_4 = { F_3PI_4 };
const Vec4 V_4PI_3 = { F_4PI_3 };
const Vec4 V_3PI_2 = { F_3PI_2 };

SseVec SetSseVec4_Debug(float x, float y, float z, float w)
{
	return _mm_set_ps(w, z, y, x);
}

SseVec SetSseVec3_Debug(float x, float y, float z)
{
	return SetSseVec4_Debug(x, y, z, 1.0f);
}

SseVec SetSseVec2_Debug(float x, float y)
{
	return SetSseVec4(x, y, 0.0f, 1.0f);
}

Vec4 StoreSseVec4_Debug(SseVec col)
{
	AlignedFloat4 result;
	_mm_store_ps(result.vals, col);

	return Vec4(result.vals[0], result.vals[1], result.vals[2], result.vals[3]);
}

Vec3 StoreSseVec3_Debug(SseVec col)
{
	AlignedFloat4 result;
	_mm_store_ps(result.vals, col);

	return Vec3(result.vals[0], result.vals[1], result.vals[2]);
}

Vec2 StoreSseVec2_Debug(SseVec col)
{
	AlignedFloat4 result;
	_mm_store_ps(result.vals, col);

	return Vec2(result.vals[0], result.vals[1]);
}



std::string FLoatPrecisionToString(FloatPrecision precision)
{
	switch (precision)
	{
	case FloatPrecision::HIGH:
		return "HIGH";
	case FloatPrecision::MEDIUM_HIGH:
		return "MEDIUM_HIGH";
	case FloatPrecision::MEDIUM:
		return "MEDIUM";
	case FloatPrecision::MEDIUM_LOW:
		return "MEDIUM_LOW";
	case FloatPrecision::LOW:
		return "LOW";
	}

	return "";
}

void CheckSseVec3IsNaN(const SseVec& vec)
{
	Vec3 result = StoreSseVec3(vec);

	CHECK(Vec3HasNaN(result));
}

void CheckSseVec4IsNaN(const SseVec& vec)
{
	Vec4 result = StoreSseVec4(vec);

	CHECK(Vec4HasNaN(result));
}

void CheckSseVec2IsNaN(const SseVec& vec)
{
	Vec2 result = StoreSseVec2(vec);

	CHECK(Vec2HasNaN(result));
}

void CheckSseVec2HasInfinite(const SseVec& vec)
{
	Vec2 result = StoreSseVec2(vec);

	CHECK(Vec2HasInfinite(result));
}

void CheckSseVec3HasInfinite(const SseVec& vec)
{
	Vec3 result = StoreSseVec3(vec);

	CHECK(Vec3HasInfinite(result));
}

void CheckSseVec4HasInfinite(const SseVec& vec)
{
	Vec4 result = StoreSseVec4(vec);

	CHECK(Vec4HasInfinite(result));
}

void RunVec2IsNaNTest(const SseVec2Context& context, const SseVec& result)
{
	INFO("Test " << context.info << " Vector <" << StoreSseVec2(result) << ">");
	CheckSseVec2IsNaN(result);
}

void RunVec3IsNaNTest(const SseVec3Context& context, const SseVec& result)
{
	INFO("Test " << context.info << " Vector <" << StoreSseVec2(result) << ">");
	CheckSseVec3IsNaN(result);
}

void RunVec4IsNaNTest(const SseVec4Context& context, const SseVec& result)
{
	INFO("Test " << context.info << " Vector <" << StoreSseVec2(result) << ">");
	CheckSseVec4IsNaN(result);
}

void RunVec2InfTest(const SseVec2Context& context, const SseVec& result)
{
	INFO("Test " << context.info << " Vector <" << StoreSseVec2(result) << ">");
	CheckSseVec2HasInfinite(result);
}

void RunVec3InfTest(const SseVec3Context& context, const SseVec& result)
{
	INFO("Test " << context.info << " Vector <" << StoreSseVec3(result) << ">");
	CheckSseVec3HasInfinite(result);
}

void RunVec4InfTest(const SseVec4Context& context, const SseVec& result)
{
	INFO("Test " << context.info << " Vector <" << StoreSseVec4(result) << ">");
	CheckSseVec4HasInfinite(result);
}



TEST_CASE("The dot product of 2D SseVecs can be calculated", "[SseVec][2D]")
{
	SECTION("All Positive Components")
	{
		const int TEST_COUNT = 3;

		SseVec2Context_2Args tests[TEST_COUNT] {
			{ "<MED MED> <MED MED>", Vec2(MED, MED), Vec2(MED, MED), Vec2(2 * MED_SQR, 2 * MED_SQR) },
			{ "<BIG BIG> <BIG BIG>", Vec2(BIG, BIG), Vec2(BIG, BIG), Vec2(2 * BIG_SQR, 2 * BIG_SQR) },
			{ "<MED BIG> <BIG MED>", Vec2(MED, BIG), Vec2(BIG, MED), Vec2(2 * MED_BIG, 2 * MED_BIG) },
		};

		for (size_t i = 0; i < TEST_COUNT; i++)
		{
			SseVec result = Vec2Dot(tests[i].arg0, tests[i].arg1);
			RunVec2Test(tests[i], result);
		}
	}

	SECTION("All Negative Components")
	{
		const int TEST_COUNT = 3;

		SseVec2Context_2Args tests[TEST_COUNT] {
			{ "<-MED -MED> <-MED -MED>", Vec2(-MED, -MED), Vec2(-MED, -MED), Vec2(2 * MED_SQR, 2 * MED_SQR) },
			{ "<-BIG -BIG> <-BIG -BIG>", Vec2(-BIG, -BIG), Vec2(-BIG, -BIG), Vec2(2 * BIG_SQR, 2 * BIG_SQR) },
			{ "<-MED -BIG> <-BIG -MED>", Vec2(-MED, -BIG), Vec2(-BIG, -MED), Vec2(2 * MED_BIG, 2 * MED_BIG) },
		};

		for (size_t i = 0; i < TEST_COUNT; i++)
		{
			SseVec result = Vec2Dot(tests[i].arg0, tests[i].arg1);
			RunVec2Test(tests[i], result);
		}
	}

	SECTION("Some Zero Components With Positive Components")
	{
		const int TEST_COUNT = 3;

		SseVec2Context_2Args tests[TEST_COUNT] {
			{ "<Zero() MED> <Zero() MED>", Vec2(0.0f, MED), Vec2(0.0f, MED), Vec2(MED_SQR, MED_SQR) },
			{ "<Zero() MED> <MED Zero()>", Vec2(0.0f, MED), Vec2(MED, 0.0f), Vec2::Zero() },
			{ "<Zero() BIG> <Zero() BIG>", Vec2(0.0f, BIG), Vec2(0.0f, BIG), Vec2(BIG_SQR, BIG_SQR) },
		};

		for (size_t i = 0; i < TEST_COUNT; i++)
		{
			SseVec result = Vec2Dot(tests[i].arg0, tests[i].arg1);
			RunVec2Test(tests[i], result, (int)i);
		}
	}

	SECTION("Some Zero Components With Negative Components")
	{
		const int TEST_COUNT = 3;

		SseVec2Context_2Args tests[TEST_COUNT] {
			{ "<Zero() -MED> <Zero() -MED>", Vec2(0.0f, MED), Vec2(0.0f, MED), Vec2(MED_SQR, MED_SQR) },
			{ "<Zero() -MED> <-MED Zero()>", Vec2(0.0f, MED), Vec2(MED, 0.0f), Vec2::Zero() },
			{ "<Zero() -BIG> <Zero() -BIG>", Vec2(0.0f, BIG), Vec2(0.0f, BIG), Vec2(BIG_SQR, BIG_SQR) },
		};

		for (size_t i = 0; i < TEST_COUNT; i++)
		{
			SseVec result = Vec2Dot(tests[i].arg0, tests[i].arg1);
			RunVec2Test(tests[i], result);
		}
	}

	SECTION("All Zero Components")
	{
		SseVec2Context_2Args test("<Zero() Zero()> <Zero() Zero()>", Vec2::Zero(), Vec2::Zero(), Vec2::Zero());
		SseVec result = Vec2Dot(test.arg0, test.arg1);
		RunVec2Test(test, result);
	}

	SECTION("All Infinite Components")
	{
		SseVec2Context_2Args test("<INFINITE INFINITE> <INFINITE INFINITE>", Vec2(Infinity(), Infinity()), Vec2(Infinity(), Infinity()), Vec2(Infinity(), Infinity()));
		SseVec result = Vec2Dot(test.arg0, test.arg1);
		RunVec2InfTest(test, result);
	}
}

TEST_CASE("The dot product of 3D SseVecs can be calculated", "[SseVec][3D]")
{
	SECTION("Full SseVec3 Dot")
	{
		SseVec3Context_2Args test0("<MED MED MED> <MED MED MED>", Vec3(MED, MED, MED), Vec3(MED, MED, MED), Vec3(3 * MED_SQR, 3 * MED_SQR, 3 * MED_SQR));
	}
	SseVec3Context_2Args test("<MED MED Zero()> <MED MED Zero()>", Vec3(MED, MED, 0.0f), Vec3(MED, MED, 0.0f), Vec3(2 * MED_SQR, 2 * MED_SQR, 2 * MED_SQR));

	SseVec result0 = Vec3Dot(test.arg0, test.arg1);
	RunVec3Test(test, result0);
}

TEST_CASE("The dot product of 4D SseVecs can be calculated", "[SseVec][4D]")
{
	SseVec4Context_2Args("<MED MED Zero() MED> <MED MED Zero() MED>", Vec4(MED, MED, 0.0f, MED), Vec4(MED, 0.0f, MED, MED), Vec4(2 * MED_SQR, 2 * MED_SQR, 2 * MED_SQR, 2 * MED_SQR));
}



TEST_CASE("2D SseVec can be normalized", "[SseVec][2D]")
{
	SECTION("Non-Zero, Non-Infinite Length")
	{
		SECTION("Unit Length")
		{
			const int TEST_COUNT = 6;

			SseVec2Context_1Arg tests[TEST_COUNT] {
				{ "Right",	Vec2::Right() },
				{ "Up",		Vec2::Up() },
				{ "Left",	Vec2Negate(Vec2::Right()) },
				{ "Down",	Vec2Negate(Vec2::Up()) },

				{ "Right-Up",	Vec2( SQRT_2_OVER_2,  SQRT_2_OVER_2) },
				{ "Left-Down",	Vec2(-SQRT_2_OVER_2, -SQRT_2_OVER_2) }
			};
			
			for (size_t i = 0; i < TEST_COUNT; i++)
			{
				SseVec result = Vec2Normalize(tests[i].arg);
				RunVec2Test(tests[i], result, (int)i);
			}
		}

		SECTION("Non-Unit Length")
		{
			const int TEST_COUNT = 6;

			SseVec2Context_1Arg tests[TEST_COUNT] {
				{ "<SMALL, SMALL>",	Vec2(SMALL, SMALL),	Vec2(SQRT_2_OVER_2, SQRT_2_OVER_2)},
				{ "<MED, MED>", Vec2(MED, MED), Vec2(SQRT_2_OVER_2, SQRT_2_OVER_2) },
				{ "<BIG, BIG>", Vec2(BIG, BIG), Vec2(SQRT_2_OVER_2, SQRT_2_OVER_2) },

				{ "<SMALL, MED>",	Vec2(SMALL, MED),	Vec2(SMALL, 1.0f) },
				{ "<SMALL, BIG>",	Vec2(SMALL, BIG),	Vec2(0.0f, 1.0f) },
				{ "<MED, BIG>", Vec2(MED, BIG), Vec2(0.0f, 1.0f) }
			};

			for (size_t i = 0; i < TEST_COUNT; i++)
			{
				SseVec result = Vec2Normalize(tests[i].arg);
				RunVec2Test(tests[i], result, (int)i);
			}
		}
	}

	SECTION("Zero Length")
	{
		SseVec2Context_1Arg test("Zero", Vec2::Zero());
		SseVec result = Vec2Normalize(test.arg);

		RunVec2Test(test, result);
	}

	SECTION("Infinite Length")
	{
		SseVec2Context_1Arg test("Infinite", Vec2(Infinity(), Infinity()));
		SseVec result = Vec2Normalize(test.arg);

		RunVec2IsNaNTest(test, result);
	}
}

TEST_CASE("3D SseVec can be normalized", "[SseVec][3D]")
{
	SECTION("Non-Zero, Non-Infinite Length")
	{
		SECTION("Unit Length")
		{
			const int TEST_COUNT = 13;

			SseVec3Context_1Arg tests[TEST_COUNT] {
				{ "Right",		Vec3::Right() },
				{ "Up",			Vec3::Up() },
				{ "Forward",	Vec3::Forward() },

				{ "Left",		Vec3Negate(Vec3::Right()) },
				{ "Down",		Vec3Negate(Vec3::Up()) },
				{ "Back",		Vec3Negate(Vec3::Forward()) },

				{ "Right-Up",		Vec3(SQRT_2_OVER_2, SQRT_2_OVER_2, 0.0f) },
				{ "Right-Forward", Vec3(SQRT_2_OVER_2, 0.0f, SQRT_2_OVER_2) },
				{ "Up-Forward",		Vec3(0.0f, SQRT_2_OVER_2, SQRT_2_OVER_2) },

				{ "Left-Down",		Vec3(-SQRT_2_OVER_2, -SQRT_2_OVER_2, 0.0f) },
				{ "Down-Back",		Vec3(0.0f, -SQRT_2_OVER_2, -SQRT_2_OVER_2) },				
				{ "Left-Back",		Vec3(-SQRT_2_OVER_2, 0.0f, -SQRT_2_OVER_2) },

				{ "Left-Down-Back",		Vec3(-SQRT_3_OVER_3, -SQRT_3_OVER_3, -SQRT_3_OVER_3) },
			};

			for (size_t i = 0; i < TEST_COUNT; i++)
			{
				SseVec result = Vec3Normalize(tests[i].arg);
				RunVec3Test(tests[i], result, (int)i);
			}
		}

		SECTION("Non-Unit Length")
		{
			const int TEST_COUNT = 10;

			SseVec3Context_1Arg tests[TEST_COUNT] {
				// All the same
				{ "<SMALL SMALL SMALL>",	Vec3(SMALL, SMALL, SMALL),	Vec3(SQRT_3_OVER_3, SQRT_3_OVER_3, SQRT_3_OVER_3) },
				{ "<MED MED MED>", Vec3(MED, MED, MED), Vec3(SQRT_3_OVER_3, SQRT_3_OVER_3, SQRT_3_OVER_3) },
				{ "<BIG BIG BIG>", Vec3(BIG, BIG, BIG), Vec3(SQRT_3_OVER_3, SQRT_3_OVER_3, SQRT_3_OVER_3) },

				// Two of one, one of the other
				{ "<SMALL SMALL MED>",		Vec3(SMALL, SMALL, MED),	Vec3(SMALL, SMALL, 1.0f) },
				{ "<SMALL SMALL BIG>",		Vec3(SMALL, SMALL, BIG),	Vec3(0.0f, 0.0f, 1.0f) },
				{ "<SMALL MED MED>",		Vec3(SMALL, MED, MED),		Vec3(SMALL, SQRT_2_OVER_2, SQRT_2_OVER_2) },
				{ "<MED MED BIG>",			Vec3(MED, MED, BIG),		Vec3(0.0f, 0.0f, 1.0f) },
				{ "<SMALL BIG BIG>",		Vec3(SMALL, BIG, BIG),		Vec3(0.0f, SQRT_2_OVER_2, SQRT_2_OVER_2) },
				{ "<MED BIG BIG>",			Vec3(MED, BIG, BIG),		Vec3(0.0f, SQRT_2_OVER_2, SQRT_2_OVER_2) },
				
				// One of each
				{ "<SMALL MED BIG>",		Vec3(SMALL, MED, BIG),		Vec3(0.0f, 0.0f, 1.0f) },
			};

			for (size_t i = 0; i < TEST_COUNT; i++)
			{
				SseVec result = Vec3Normalize(tests[i].arg);
				RunVec3Test(tests[i], result, (int)i);
			}
		}
	}

	SECTION("Zero Length")
	{
		SseVec3Context_1Arg test("Zero", Vec3::Zero());
		SseVec result = Vec3Normalize(test.arg);

		RunVec3Test(test, result);
	}

	SECTION("Infinite Length")
	{
		SseVec3Context_1Arg test("Infinity", Vec3(Infinity(), Infinity(), Infinity()));
		SseVec result = Vec3Normalize(test.arg);

		RunVec3IsNaNTest(test, result);
	}
}

TEST_CASE("4D SseVec can be normalized", "[SseVec][4D]")
{
	SECTION("Non-Zero, Non-Infinite Length")
	{
		SECTION("Unit Length")
		{
			const int TEST_COUNT = 30;

			SseVec4Context_1Arg tests[TEST_COUNT] {
				{ "e0", Vec4::E0() },
				{ "e1", Vec4::E1() },
				{ "e2", Vec4::E2() },
				{ "e3", Vec4::E3() },

				{ "-e0", Vec4Negate(Vec4::E0()) },
				{ "-e1", Vec4Negate(Vec4::E1()) },
				{ "-e2", Vec4Negate(Vec4::E2()) },
				{ "-e3", Vec4Negate(Vec4::E3()) },

				{ "e0 e1", Vec4(SQRT_2_OVER_2, SQRT_2_OVER_2, 0.0f, 0.0f) },
				{ "e0 e2", Vec4(SQRT_2_OVER_2, 0.0f, SQRT_2_OVER_2, 0.0f) },
				{ "e0 e2", Vec4(SQRT_2_OVER_2, 0.0f, 0.0f, SQRT_2_OVER_2) },
				{ "e1 e2", Vec4(0.0f, SQRT_2_OVER_2, SQRT_2_OVER_2, 0.0f) },
				{ "e1 e3", Vec4(0.0f, SQRT_2_OVER_2, 0.0f, SQRT_2_OVER_2) },
				{ "e2 e3", Vec4(0.0f, 0.0f, SQRT_2_OVER_2, SQRT_2_OVER_2) },

				{ "-e0 -e1", Vec4(-SQRT_2_OVER_2, -SQRT_2_OVER_2, 0.0f, 0.0f) },
				{ "-e0 -e2", Vec4(-SQRT_2_OVER_2, 0.0f, -SQRT_2_OVER_2, 0.0f) },
				{ "-e0 -e2", Vec4(-SQRT_2_OVER_2, 0.0f, 0.0f, -SQRT_2_OVER_2) },
				{ "-e1 -e2", Vec4(0.0f, -SQRT_2_OVER_2, -SQRT_2_OVER_2, 0.0f) },
				{ "-e1 -e3", Vec4(0.0f, -SQRT_2_OVER_2, 0.0f, -SQRT_2_OVER_2) },
				{ "-e2 -e3", Vec4(0.0f, 0.0f, -SQRT_2_OVER_2, -SQRT_2_OVER_2) },

				{ "e0 e1 e2", Vec4(SQRT_3_OVER_3, SQRT_3_OVER_3, SQRT_3_OVER_3, 0.0f) },
				{ "e0 e1 e3", Vec4(SQRT_3_OVER_3, SQRT_3_OVER_3, 0.0f, SQRT_3_OVER_3) },
				{ "e0 e2 e3", Vec4(SQRT_3_OVER_3, 0.0f, SQRT_3_OVER_3, SQRT_3_OVER_3) },
				{ "e1 e2 e3", Vec4(0.0f, SQRT_3_OVER_3, SQRT_3_OVER_3, SQRT_3_OVER_3) },

				{ "-e0 -e1 -e2", Vec4(-SQRT_3_OVER_3, -SQRT_3_OVER_3, -SQRT_3_OVER_3, 0.0f) },
				{ "-e0 -e1 -e3", Vec4(-SQRT_3_OVER_3, -SQRT_3_OVER_3, 0.0f, -SQRT_3_OVER_3) },
				{ "-e0 -e2 -e3", Vec4(-SQRT_3_OVER_3, 0.0f, -SQRT_3_OVER_3, -SQRT_3_OVER_3) },
				{ "-e1 -e2 -e3", Vec4(0.0f, -SQRT_3_OVER_3, -SQRT_3_OVER_3, -SQRT_3_OVER_3) },

				{ "e0 e1 e2 e3", Vec4(0.5f, 0.5f, 0.5f, 0.5f) },

				{ "-e0 -e1 -e2 -e3", Vec4(-0.5f, -0.5f, -0.5f, -0.5f) }
			};

			for (size_t i = 0; i < TEST_COUNT; i++)
			{
				SseVec result = Vec4Normalize(tests[i].arg);
				RunVec4Test(tests[i], result, (int)i);
			}
		}

		SECTION("Non-Unit Length")
		{
			const int TEST_COUNT = 15;

			SseVec4Context_1Arg tests[TEST_COUNT] {
				// All the same
				{ "<SMALL SMALL SMALL SMALL>", Vec4(SMALL, SMALL, SMALL, SMALL), Vec4(0.5f, 0.5f, 0.5f, 0.5f) },
				{ "<MED MED MED MED>", Vec4(MED, MED, MED, MED), Vec4(0.5f, 0.5f, 0.5f, 0.5f) },
				{ "<BIG BIG BIG BIG>", Vec4(BIG, BIG, BIG, BIG), Vec4(0.5f, 0.5f, 0.5f, 0.5f) },

				// Pairs
				{ "<SMALL SMALL MED MED>", Vec4(SMALL, SMALL, MED, MED), Vec4(SMALL, SMALL, SQRT_2_OVER_2, SQRT_2_OVER_2) },
				{ "<SMALL SMALL BIG BIG>", Vec4(SMALL, SMALL, BIG, BIG), Vec4(0.0f, 0.0f, SQRT_2_OVER_2, SQRT_2_OVER_2) },
				{ "<MED MED BIG BIG>", Vec4(SMALL, SMALL, BIG, BIG), Vec4(0.0f, 0.0f, SQRT_2_OVER_2, SQRT_2_OVER_2) },

				// Three of one, one of another
				{ "<SMALL SMALL SMALL MED>", Vec4(SMALL, SMALL, SMALL, MED), Vec4(SMALL, SMALL, SMALL, 1.0f) },
				{ "<SMALL SMALL SMALL BIG>", Vec4(SMALL, SMALL, SMALL, BIG), Vec4(0.0f, 0.0f, 0.0f, 1.0f) },
				{ "<SMALL MED MED MED>", Vec4(SMALL, MED, MED, MED), Vec4(SMALL, SQRT_3_OVER_3, SQRT_3_OVER_3, SQRT_3_OVER_3) },
				{ "<MED MED MED BIG>", Vec4(MED, MED, MED, BIG), Vec4(0.0f, 0.0f, 0.0f, 1.0f) },
				{ "<SMALL BIG BIG BIG>", Vec4(SMALL, BIG, BIG, BIG), Vec4(0.0f, SQRT_3_OVER_3, SQRT_3_OVER_3, SQRT_3_OVER_3) },
				{ "<MED BIG BIG BIG>", Vec4(MED, BIG, BIG, BIG), Vec4(0.0f, SQRT_3_OVER_3, SQRT_3_OVER_3, SQRT_3_OVER_3) },
				
				// Pair of one, one of each of the other two
				{ "<SMALL SMALL MED BIG>", Vec4(SMALL, SMALL, MED, BIG), Vec4(0.0f, 0.0f, 0.0f, 1.0f) },
				{ "<SMALL MED MED BIG>", Vec4(SMALL, MED, MED, BIG), Vec4(0.0f, 0.0f, 0.0f, 1.0f) },
				{ "<SMALL MED BIG BIG>", Vec4(SMALL, MED, BIG, BIG), Vec4(0.0f, 0.0f, SQRT_2_OVER_2, SQRT_2_OVER_2) },
			};

			for (size_t i = 0; i < TEST_COUNT; i++)
			{
				SseVec result = Vec4Normalize(tests[i].arg);
				RunVec4Test(tests[i], result, (int)i);
			}
		}
	}

	SECTION("Zero Length")
	{
		SseVec4Context_1Arg test("Zero", Vec4::Zero());
		SseVec result = Vec4Normalize(test.arg);

		RunVec4Test(test, result);
	}

	SECTION("Infinite Length")
	{
		SseVec4Context_1Arg test("Infinity", Vec4(Infinity(), Infinity(), Infinity(), Infinity()));
		SseVec result = Vec4Normalize(test.arg);

		RunVec4IsNaNTest(test, result);
	}
}



TEST_CASE("2D SseVec can have its normalized form approximated", "[SseVec][2D][APPROX]")
{
	SECTION("Non-Zero, Non-Infinite Length")
	{
		SECTION("Unit Length")
		{
			const int TEST_COUNT = 6;

			SseVec2Context_1Arg tests[TEST_COUNT] {
				{ "Right", Vec2::Right() },
				{ "Up", Vec2::Up() },
				{ "Left", Vec2Negate(Vec2::Right()) },
				{ "Down", Vec2Negate(Vec2::Up()) },

				{ "Right-Up", Vec2(SQRT_2_OVER_2, SQRT_2_OVER_2) },
				{ "Left-Down", Vec2(-SQRT_2_OVER_2, -SQRT_2_OVER_2) }
			};

			for (size_t i = 0; i < TEST_COUNT; i++)
			{
				SseVec result = FastVec2Normalize(tests[i].arg);
				RunVec2Test<FloatPrecision::LOW>(tests[i], result, (int)i);
			}
		}

		SECTION("Non-Unit Length")
		{
			const int TEST_COUNT = 6;

			SseVec2Context_1Arg tests[TEST_COUNT] {
				{ "<SMALL, SMALL>", Vec2(SMALL, SMALL), Vec2(SQRT_2_OVER_2, SQRT_2_OVER_2)},
				{ "<MED, MED>", Vec2(MED, MED), Vec2(SQRT_2_OVER_2, SQRT_2_OVER_2) },
				{ "<BIG, BIG>", Vec2(BIG, BIG), Vec2(SQRT_2_OVER_2, SQRT_2_OVER_2) },

				{ "<SMALL, MED>", Vec2(SMALL, MED), Vec2(SMALL, 1.0f) },
				{ "<SMALL, BIG>", Vec2(SMALL, BIG), Vec2(0.0f, 1.0f) },
				{ "<MED, BIG>", Vec2(MED, BIG), Vec2(0.0f, 1.0f) }
			};

			for (size_t i = 0; i < TEST_COUNT; i++)
			{
				SseVec result = FastVec2Normalize(tests[i].arg);
				RunVec2Test<FloatPrecision::LOW>(tests[i], result, (int)i);
			}
		}
	}

	SECTION("Zero Length")
	{
		SseVec2Context_1Arg test("Zero", Vec2::Zero());
		SseVec result = FastVec2Normalize(test.arg);

		RunVec2IsNaNTest(test, result);
	}

	SECTION("Infinite Length")
	{
		SseVec2Context_1Arg test("Infinite", Vec2(Infinity(), Infinity()));

		SseVec result = FastVec2Normalize(test.arg);

		RunVec2IsNaNTest(test, result);
	}
}

TEST_CASE("3D SseVec can have its normalized form approximated", "[SseVec][3D][APPROX]")
{
	SECTION("Non-Zero, Non-Infinite Length")
	{
		SECTION("Unit Length")
		{
			const int TEST_COUNT = 13;

			SseVec3Context_1Arg tests[TEST_COUNT] {
				{ "Right", Vec3::Right() },
				{ "Up", Vec3::Up() },
				{ "Forward", Vec3::Forward() },

				{ "Left", Vec3Negate(Vec3::Right()) },
				{ "Down", Vec3Negate(Vec3::Up()) },
				{ "Back", Vec3Negate(Vec3::Forward()) },

				{ "Right-Up", Vec3(SQRT_2_OVER_2, SQRT_2_OVER_2, 0.0f) },
				{ "Right-Forward", Vec3(SQRT_2_OVER_2, 0.0f, SQRT_2_OVER_2) },
				{ "Up-Forward", Vec3(0.0f, SQRT_2_OVER_2, SQRT_2_OVER_2) },

				{ "Left-Down", Vec3(-SQRT_2_OVER_2, -SQRT_2_OVER_2, 0.0f) },
				{ "Down-Back", Vec3(0.0f, -SQRT_2_OVER_2, -SQRT_2_OVER_2) },
				{ "Left-Back", Vec3(-SQRT_2_OVER_2, 0.0f, -SQRT_2_OVER_2) },

				{ "Left-Down-Back", Vec3(-SQRT_3_OVER_3, -SQRT_3_OVER_3, -SQRT_3_OVER_3) },
			};

			for (size_t i = 0; i < TEST_COUNT; i++)
			{
				SseVec result = FastVec3Normalize(tests[i].arg);
				RunVec3Test<FloatPrecision::LOW>(tests[i], result, (int)i);
			}
		}

		SECTION("Non-Unit Length")
		{
			const int TEST_COUNT = 10;

			SseVec3Context_1Arg tests[TEST_COUNT] {
				// All the same
				{ "<SMALL SMALL SMALL>", Vec3(SMALL, SMALL, SMALL), Vec3(SQRT_3_OVER_3, SQRT_3_OVER_3, SQRT_3_OVER_3) },
				{ "<MED MED MED>", Vec3(MED, MED, MED), Vec3(SQRT_3_OVER_3, SQRT_3_OVER_3, SQRT_3_OVER_3) },
				{ "<BIG BIG BIG>", Vec3(BIG, BIG, BIG), Vec3(SQRT_3_OVER_3, SQRT_3_OVER_3, SQRT_3_OVER_3) },

				// Two of one, one of the other
				{ "<SMALL SMALL MED>", Vec3(SMALL, SMALL, MED), Vec3(SMALL, SMALL, 1.0f) },
				{ "<SMALL SMALL BIG>", Vec3(SMALL, SMALL, BIG), Vec3(0.0f, 0.0f, 1.0f) },
				{ "<SMALL MED MED>", Vec3(SMALL, MED, MED), Vec3(SMALL, SQRT_2_OVER_2, SQRT_2_OVER_2) },
				{ "<MED MED BIG>", Vec3(MED, MED, BIG), Vec3(0.0f, 0.0f, 1.0f) },
				{ "<SMALL BIG BIG>", Vec3(SMALL, BIG, BIG), Vec3(0.0f, SQRT_2_OVER_2, SQRT_2_OVER_2) },
				{ "<MED BIG BIG>", Vec3(MED, BIG, BIG), Vec3(0.0f, SQRT_2_OVER_2, SQRT_2_OVER_2) },

				// One of each
				{ "<SMALL MED BIG>", Vec3(SMALL, MED, BIG), Vec3(0.0f, 0.0f, 1.0f) },
			};

			for (size_t i = 0; i < TEST_COUNT; i++)
			{
				SseVec result = FastVec3Normalize(tests[i].arg);
				RunVec3Test<FloatPrecision::LOW>(tests[i], result, (int)i);
			}
		}
	}

	SECTION("Zero Length")
	{
		SseVec3Context_1Arg test("Zero", Vec3::Zero());
		SseVec result = FastVec3Normalize(test.arg);

		RunVec3IsNaNTest(test, result);
	}

	SECTION("Infinite Length")
	{
		SseVec3Context_1Arg test("Infinity", Vec3(Infinity(), Infinity(), Infinity()));
		SseVec result = FastVec3Normalize(test.arg);

		RunVec3IsNaNTest(test, result);
	}
}

TEST_CASE("4D SseVec can have its normalized form approximated", "[SseVec][4D][APPROX]")
{
	SECTION("Non-Zero, Non-Infinite Length")
	{
		SECTION("Unit Length")
		{
			const int TEST_COUNT = 30;

			SseVec4Context_1Arg tests[TEST_COUNT] {
				{ "e0", Vec4::E0() },
				{ "e1", Vec4::E1() },
				{ "e2", Vec4::E2() },
				{ "e3", Vec4::E3() },

				{ "-e0", Vec4Negate(Vec4::E0()) },
				{ "-e1", Vec4Negate(Vec4::E1()) },
				{ "-e2", Vec4Negate(Vec4::E2()) },
				{ "-e3", Vec4Negate(Vec4::E3()) },

				{ "e0 e1", Vec4(SQRT_2_OVER_2, SQRT_2_OVER_2, 0.0f, 0.0f) },
				{ "e0 e2", Vec4(SQRT_2_OVER_2, 0.0f, SQRT_2_OVER_2, 0.0f) },
				{ "e0 e2", Vec4(SQRT_2_OVER_2, 0.0f, 0.0f, SQRT_2_OVER_2) },
				{ "e1 e2", Vec4(0.0f, SQRT_2_OVER_2, SQRT_2_OVER_2, 0.0f) },
				{ "e1 e3", Vec4(0.0f, SQRT_2_OVER_2, 0.0f, SQRT_2_OVER_2) },
				{ "e2 e3", Vec4(0.0f, 0.0f, SQRT_2_OVER_2, SQRT_2_OVER_2) },

				{ "-e0 -e1", Vec4(-SQRT_2_OVER_2, -SQRT_2_OVER_2, 0.0f, 0.0f) },
				{ "-e0 -e2", Vec4(-SQRT_2_OVER_2, 0.0f, -SQRT_2_OVER_2, 0.0f) },
				{ "-e0 -e2", Vec4(-SQRT_2_OVER_2, 0.0f, 0.0f, -SQRT_2_OVER_2) },
				{ "-e1 -e2", Vec4(0.0f, -SQRT_2_OVER_2, -SQRT_2_OVER_2, 0.0f) },
				{ "-e1 -e3", Vec4(0.0f, -SQRT_2_OVER_2, 0.0f, -SQRT_2_OVER_2) },
				{ "-e2 -e3", Vec4(0.0f, 0.0f, -SQRT_2_OVER_2, -SQRT_2_OVER_2) },

				{ "e0 e1 e2", Vec4(SQRT_3_OVER_3, SQRT_3_OVER_3, SQRT_3_OVER_3, 0.0f) },
				{ "e0 e1 e3", Vec4(SQRT_3_OVER_3, SQRT_3_OVER_3, 0.0f, SQRT_3_OVER_3) },
				{ "e0 e2 e3", Vec4(SQRT_3_OVER_3, 0.0f, SQRT_3_OVER_3, SQRT_3_OVER_3) },
				{ "e1 e2 e3", Vec4(0.0f, SQRT_3_OVER_3, SQRT_3_OVER_3, SQRT_3_OVER_3) },

				{ "-e0 -e1 -e2", Vec4(-SQRT_3_OVER_3, -SQRT_3_OVER_3, -SQRT_3_OVER_3, 0.0f) },
				{ "-e0 -e1 -e3", Vec4(-SQRT_3_OVER_3, -SQRT_3_OVER_3, 0.0f, -SQRT_3_OVER_3) },
				{ "-e0 -e2 -e3", Vec4(-SQRT_3_OVER_3, 0.0f, -SQRT_3_OVER_3, -SQRT_3_OVER_3) },
				{ "-e1 -e2 -e3", Vec4(0.0f, -SQRT_3_OVER_3, -SQRT_3_OVER_3, -SQRT_3_OVER_3) },

				{ "e0 e1 e2 e3", Vec4(0.5f, 0.5f, 0.5f, 0.5f) },

				{ "-e0 -e1 -e2 -e3", Vec4(-0.5f, -0.5f, -0.5f, -0.5f) }
			};

			for (size_t i = 0; i < TEST_COUNT; i++)
			{
				SseVec result = FastVec4Normalize(tests[i].arg);
				RunVec4Test<FloatPrecision::LOW>(tests[i], result, (int)i);
			}
		}

		SECTION("Non-Unit Length")
		{
			const int TEST_COUNT = 15;

			SseVec4Context_1Arg tests[TEST_COUNT] {
				// All the same
				{ "<SMALL SMALL SMALL SMALL>", Vec4(SMALL, SMALL, SMALL, SMALL), Vec4(0.5f, 0.5f, 0.5f, 0.5f) },
				{ "<MED MED MED MED>", Vec4(MED, MED, MED, MED), Vec4(0.5f, 0.5f, 0.5f, 0.5f) },
				{ "<BIG BIG BIG BIG>", Vec4(BIG, BIG, BIG, BIG), Vec4(0.5f, 0.5f, 0.5f, 0.5f) },

				// Pairs
				{ "<SMALL SMALL MED MED>", Vec4(SMALL, SMALL, MED, MED), Vec4(SMALL, SMALL, SQRT_2_OVER_2, SQRT_2_OVER_2) },
				{ "<SMALL SMALL BIG BIG>", Vec4(SMALL, SMALL, BIG, BIG), Vec4(0.0f, 0.0f, SQRT_2_OVER_2, SQRT_2_OVER_2) },
				{ "<MED MED BIG BIG>", Vec4(SMALL, SMALL, BIG, BIG), Vec4(0.0f, 0.0f, SQRT_2_OVER_2, SQRT_2_OVER_2) },

				// Three of one, one of another
				{ "<SMALL SMALL SMALL MED>", Vec4(SMALL, SMALL, SMALL, MED), Vec4(SMALL, SMALL, SMALL, 1.0f) },
				{ "<SMALL SMALL SMALL BIG>", Vec4(SMALL, SMALL, SMALL, BIG), Vec4(0.0f, 0.0f, 0.0f, 1.0f) },
				{ "<SMALL MED MED MED>", Vec4(SMALL, MED, MED, MED), Vec4(SMALL, SQRT_3_OVER_3, SQRT_3_OVER_3, SQRT_3_OVER_3) },
				{ "<MED MED MED BIG>", Vec4(MED, MED, MED, BIG), Vec4(0.0f, 0.0f, 0.0f, 1.0f) },
				{ "<SMALL BIG BIG BIG>", Vec4(SMALL, BIG, BIG, BIG), Vec4(0.0f, SQRT_3_OVER_3, SQRT_3_OVER_3, SQRT_3_OVER_3) },
				{ "<MED BIG BIG BIG>", Vec4(MED, BIG, BIG, BIG), Vec4(0.0f, SQRT_3_OVER_3, SQRT_3_OVER_3, SQRT_3_OVER_3) },

				// Pair of one, one of each of the other two
				{ "<SMALL SMALL MED BIG>", Vec4(SMALL, SMALL, MED, BIG), Vec4(0.0f, 0.0f, 0.0f, 1.0f) },
				{ "<SMALL MED MED BIG>", Vec4(SMALL, MED, MED, BIG), Vec4(0.0f, 0.0f, 0.0f, 1.0f) },
				{ "<SMALL MED BIG BIG>", Vec4(SMALL, MED, BIG, BIG), Vec4(0.0f, 0.0f, SQRT_2_OVER_2, SQRT_2_OVER_2) },
			};

			for (size_t i = 0; i < TEST_COUNT; i++)
			{
				SseVec result = FastVec4Normalize(tests[i].arg);
				RunVec4Test<FloatPrecision::LOW>(tests[i], result, (int)i);
			}
		}
	}

	SECTION("Zero Length")
	{
		SseVec4Context_1Arg test("Zero", Vec4::Zero());
		SseVec result = FastVec4Normalize(test.arg);

		RunVec4IsNaNTest(test, result);
	}

	SECTION("Infinite Length")
	{
		SseVec4Context_1Arg test("Infinity", Vec4(Infinity(), Infinity(), Infinity(), Infinity()));
		SseVec result = FastVec4Normalize(test.arg);

		RunVec4IsNaNTest(test, result);
	}
}


TEST_CASE("3D SseVecs can be crossed", "[SseVec][3D]")
{
	SECTION("Unit Vectors")
	{
		const int TEST_COUNT = 4;
		SseVec3Context_2Args tests[TEST_COUNT] {
			{ "<1 0 0> <0 1 0>", Vec3::Right(), Vec3::Up(), Vec3::Forward() },
			{ "<0 1 0> <0 0 1>", Vec3::Up(), Vec3::Forward(), Vec3::Right() },
			{ "<-1 0 0> <0 1 0>", Vec3::Left(), Vec3::Up(), Vec3::Back() },
			{ "<0 -1 0> <0 0 1>", Vec3::Down(), Vec3::Forward(), Vec3::Left() },
		};

		for (size_t i = 0; i < TEST_COUNT; i++)
		{
			RunVec3Test(tests[i], Vec3Cross(tests[i].arg0, tests[i].arg1), (int)i);
		}
	}

	SECTION("Non-Unit Vectors")
	{
		SECTION("Zero-Vector Results")
		{
			const int TEST_COUNT = 4;
			SseVec3Context_2Args tests[TEST_COUNT] {
				{ "< 1  1  1> < 1  1  1>", Vec3::One(), Vec3::One(), Vec3::Zero() },
				{ "<-1 -1 -1> < 1  1  1>", Vec3(-1.0f), Vec3::One(), Vec3::Zero() },
				{ "<BIG BIG BIG> <BIG BIG BIG>", Vec3(BIG), Vec3(BIG), Vec3::Zero() },
				{ "<Zero() Zero() Zero()> <MED MED MED>", Vec3::Zero(), Vec3(MED), Vec3::Zero() },
			};

			for (size_t i = 0; i < TEST_COUNT; i++)
			{
				RunVec3Test(tests[i], Vec3Cross(tests[i].arg0, tests[i].arg1), (int)i);
			}
		}
		SECTION("Non-zero Vector Results")
		{
			const int TEST_COUNT = 6;
			SseVec3Context_2Args tests[TEST_COUNT] {
				{ "< 1  1  0> < 0  1  1>", Vec3(1.0f, 1.0f, 0.0f), Vec3(0.0f, 1.0f, 1.0f), Vec3( 1.0f, -1.0f,  1.0f) },
				{ "< 1  0  1> < 0  1  0>", Vec3(1.0f, 0.0f, 1.0f), Vec3::Up(), Vec3(-1.0f,  0.0f,  1.0f) },
				{ "< 1  1  1> < 0  1  0>", Vec3::One(), Vec3::Up(), Vec3(-1.0f, 0.0f, 1.0f) },
				{ "<-1  0  1> < 0  1 -1>", Vec3(-1.0f, 0.0f, 1.0f), Vec3(0.0f, 1.0f, -1.0f), Vec3::NegOne() },
				{ "<-1  1  1> < 1 -1  0>", Vec3(-1.0f, 1.0f, 1.0f), Vec3(1.0f, -1.0f, 0.0f), Vec3( 1.0f,  1.0f,  0.0f) },
				{ "<BIG BIG BIG> <BIG 0 BIG>", Vec3(BIG), Vec3(BIG, 0.0f, BIG), Vec3(BIG_SQR, 0.0f, -BIG_SQR) }
			};

			for (size_t i = 0; i < TEST_COUNT; i++)
			{
				RunVec3Test(tests[i], Vec3Cross(tests[i].arg0, tests[i].arg1), (int)i);
			}
		}
	}
}


TEST_CASE("CosSseVec can calculate cosines of SseVec angles", "[SseVec][TRIG]")
{
	const int TEST_COUNT = 4;
	SseVec4Context_1Arg tests[TEST_COUNT] {
		{ "<0 0 0 0>", Vec4::Zero(), Vec4::One() },
		{ "<PI PI PI PI>", V_PI, Vec4::NegOne() },
		{ "<PI/2 PI/2 PI/2 PI/2>", V_PI_2, Vec4::Zero() },
		{ "<PI PI/2 2PI 0>", Vec4(F_PI, F_PI_2, F_2PI, 0.0f), Vec4(-1.0f, 0.0f, 1.0f, 1.0f) }
	};

	for (size_t i = 0; i < TEST_COUNT; i++)
	{
		RunVec4Test<FloatPrecision::HIGH>(tests[i], CosSseVec<FloatPrecision::HIGH>(tests[i].arg), (int)i);
		RunVec4Test<FloatPrecision::MEDIUM_HIGH>(tests[i], CosSseVec<FloatPrecision::MEDIUM_HIGH>(tests[i].arg), (int)i);
		RunVec4Test<FloatPrecision::MEDIUM>(tests[i], CosSseVec<FloatPrecision::MEDIUM>(tests[i].arg), (int)i);
		RunVec4Test<FloatPrecision::MEDIUM_LOW>(tests[i], CosSseVec<FloatPrecision::MEDIUM_LOW>(tests[i].arg), (int)i);
		RunVec4Test<FloatPrecision::LOW>(tests[i], CosSseVec<FloatPrecision::LOW>(tests[i].arg), (int)i);
	}
}

TEST_CASE("SinSseVec can calculate sines of SseVec angles", "[SseVec][TRIG]")
{
	const int TEST_COUNT = 4;
	SseVec4Context_1Arg tests[TEST_COUNT] {
		{ "<0 0 0 0>", Vec4::Zero(), Vec4::Zero() },
		{ "<3PI/2 3PI/2 3PI/2 3PI/2>", V_3PI_2, Vec4::NegOne() },
		{ "<PI/2 PI/2 PI/2 PI/2>", V_PI_2, Vec4::One() },
		{ "<2PI 3PI/2 PI PI/2>", Vec4(F_2PI, F_3PI_2, F_PI, F_PI_2), Vec4(0.0f, -1.0f, 0.0f, 1.0f) }
	};

	for (size_t i = 0; i < TEST_COUNT; i++)
	{
		RunVec4Test<FloatPrecision::HIGH>(tests[i], SinSseVec<FloatPrecision::HIGH>(tests[i].arg), (int)i);
		RunVec4Test<FloatPrecision::MEDIUM_HIGH>(tests[i], SinSseVec<FloatPrecision::MEDIUM_HIGH>(tests[i].arg), (int)i);
		RunVec4Test<FloatPrecision::MEDIUM>(tests[i], SinSseVec<FloatPrecision::MEDIUM>(tests[i].arg), (int)i);
		RunVec4Test<FloatPrecision::MEDIUM_LOW>(tests[i], SinSseVec<FloatPrecision::MEDIUM_LOW>(tests[i].arg), (int)i);
		RunVec4Test<FloatPrecision::LOW>(tests[i], SinSseVec<FloatPrecision::LOW>(tests[i].arg), (int)i);
	}
}

TEST_CASE("FastCosSseVec can calculate approximate cosines of SseVec angles", "[SseVec][TRIG][APPROX]")
{
	const int TEST_COUNT = 4;
	SseVec4Context_1Arg tests[TEST_COUNT] {
		{ "<0 0 0 0>", Vec4::Zero(), Vec4::One() },
		{ "<PI PI PI PI>", V_PI, Vec4::NegOne() },
		{ "<PI/2 PI/2 PI/2 PI/2>", V_PI_2, Vec4::Zero() },
		{ "<PI PI/2 2PI 0>", Vec4(F_PI, F_PI_2, F_2PI, 0.0f), Vec4(-1.0f, 0.0f, 1.0f, 1.0f) }
	};

	for (size_t i = 0; i < TEST_COUNT; i++)
	{
		RunVec4Test<FloatPrecision::MEDIUM>(tests[i], FastCosSseVec(tests[i].arg), (int)i);
	}
}

TEST_CASE("FastSinSseVec can calculate approximate sines of SseVec angles", "[SseVec][TRIG][APPROX]")
{
	const int TEST_COUNT = 4;
	SseVec4Context_1Arg tests[TEST_COUNT] {
		{ "<0 0 0 0>", Vec4::Zero(), Vec4::Zero() },
		{ "<3PI/2 3PI/2 3PI/2 3PI/2>", V_3PI_2, Vec4::NegOne() },
		{ "<PI/2 PI/2 PI/2 PI/2>", V_PI_2, Vec4::One() },
		{ "<2PI 3PI/2 PI PI/2>", Vec4(F_2PI, F_3PI_2, F_PI, F_PI_2), Vec4(0.0f, -1.0f, 0.0f, 1.0f) }
	};

	for (size_t i = 0; i < TEST_COUNT; i++)
	{
		RunVec4Test<FloatPrecision::MEDIUM>(tests[i], FastSinSseVec(tests[i].arg), (int)i);
	}
}

TEST_CASE("SinCosSseVec can calculate the sines and cosines of SseVec angles", "[SseVec][TRIG]")
{
	const int TEST_COUNT = 8;

	float vals[TEST_COUNT] {
		0.0f,
		F_PI_4,
		F_PI_2,
		F_3PI_4,
		F_PI,
		F_4PI_3,
		F_3PI_2,
		F_2PI
	};

	std::string valStrings[TEST_COUNT] {
		"0.0f",
		"F_PI_4",
		"F_PI_2",
		"F_3PI_4",
		"F_PI",
		"F_4PI_3",
		"F_3PI_2",
		"F_2PI"
	};

	SECTION("All Sines")
	{
		for (size_t j = 0; j < 2; j++)
		{
			std::string message = "";
			size_t k = j * 4;
			message += "<" + valStrings[k] + " " + valStrings[k+1] + " " + valStrings[k+2] + " " + valStrings[k+3] + ">";

			Vec4 value = Vec4(vals[k], vals[k + 1], vals[k + 2], vals[k + 3]);
			Vec4 expected = Vec4(sinf(vals[k]), sinf(vals[k + 1]), sinf(vals[k + 2]), sinf(vals[k + 3]));

			SseVec4Context_1Arg test = { message, value, expected };

			RunVec4Test<FloatPrecision::HIGH>(test, SinCosSseVec<SIN,SIN,SIN,SIN, FloatPrecision::HIGH>(test.arg), (int)k);
			RunVec4Test<FloatPrecision::MEDIUM_HIGH>(test, SinCosSseVec<SIN,SIN,SIN,SIN, FloatPrecision::MEDIUM_HIGH>(test.arg), (int)k);
			RunVec4Test<FloatPrecision::MEDIUM>(test, SinCosSseVec<SIN,SIN,SIN,SIN, FloatPrecision::MEDIUM>(test.arg), (int)k);
			RunVec4Test<FloatPrecision::MEDIUM_LOW>(test, SinCosSseVec<SIN,SIN,SIN,SIN, FloatPrecision::MEDIUM_LOW>(test.arg), (int)k);
			RunVec4Test<FloatPrecision::LOW>(test, SinCosSseVec<SIN,SIN,SIN,SIN, FloatPrecision::LOW>(test.arg), (int)k);
		}
	}

	SECTION("All Cosines")
	{
		for (size_t j = 0; j < 2; j++)
		{
			std::string message = "";
			size_t k = j * 4;
			message += "<" + valStrings[k] + " " + valStrings[k + 1] + " " + valStrings[k + 2] + " " + valStrings[k + 3] + ">";

			Vec4 value = Vec4(vals[k], vals[k + 1], vals[k + 2], vals[k + 3]);
			Vec4 expected = Vec4(cosf(vals[k]), cosf(vals[k + 1]), cosf(vals[k + 2]), cosf(vals[k + 3]));

			SseVec4Context_1Arg test = { message, value, expected };

			RunVec4Test<HIGH>(test, SinCosSseVec<COS,COS,COS,COS, HIGH>(test.arg), (int)k);
			RunVec4Test<MEDIUM_HIGH>(test, SinCosSseVec<COS,COS,COS,COS, MEDIUM_HIGH>(test.arg), (int)k);
			RunVec4Test<MEDIUM>(test, SinCosSseVec<COS,COS,COS,COS, MEDIUM>(test.arg), (int)k);
			RunVec4Test<MEDIUM_LOW>(test, SinCosSseVec<COS,COS,COS,COS, MEDIUM_LOW>(test.arg), (int)k);
			RunVec4Test<LOW>(test, SinCosSseVec<COS,COS,COS,COS, LOW>(test.arg), (int)k);
		}
	}
	
	SECTION("Half Sines Half Cosines")
	{
		for (size_t j = 0; j < 2; j++)
		{
			std::string message = "";
			size_t k = j * 4;
			message += "<" + valStrings[k] + " " + valStrings[k + 1] + " " + valStrings[k + 2] + " " + valStrings[k + 3] + ">";

			Vec4 value = Vec4(vals[k], vals[k + 1], vals[k + 2], vals[k + 3]);
			Vec4 expected = Vec4(sinf(vals[k]), sinf(vals[k + 1]), cosf(vals[k + 2]), cosf(vals[k + 3]));

			SseVec4Context_1Arg test = { message, value, expected };

			RunVec4Test<HIGH>(test, SinCosSseVec<SIN, SIN, COS, COS, HIGH>(test.arg), (int)k);
			RunVec4Test<MEDIUM_HIGH>(test, SinCosSseVec<SIN, SIN, COS, COS, MEDIUM_HIGH>(test.arg), (int)k);
			RunVec4Test<MEDIUM>(test, SinCosSseVec<SIN, SIN, COS, COS, MEDIUM>(test.arg), (int)k);
			RunVec4Test<MEDIUM_LOW>(test, SinCosSseVec<SIN, SIN, COS, COS, MEDIUM_LOW>(test.arg), (int)k);
			RunVec4Test<LOW>(test, SinCosSseVec<SIN, SIN, COS, COS, LOW>(test.arg), (int)k);
		}

		for (size_t j = 0; j < 2; j++)
		{
			std::string message = "";
			size_t k = j * 4;
			message += "<" + valStrings[k] + " " + valStrings[k + 1] + " " + valStrings[k + 2] + " " + valStrings[k + 3] + ">";

			Vec4 value = Vec4(vals[k], vals[k + 1], vals[k + 2], vals[k + 3]);
			Vec4 expected = Vec4(cosf(vals[k]), cosf(vals[k + 1]), sinf(vals[k + 2]), sinf(vals[k + 3]));

			SseVec4Context_1Arg test = { message, value, expected };

			RunVec4Test<HIGH>(test, SinCosSseVec<COS, COS, SIN, SIN, HIGH>(test.arg), (int)k);
			RunVec4Test<MEDIUM_HIGH>(test, SinCosSseVec<COS, COS, SIN, SIN, MEDIUM_HIGH>(test.arg), (int)k);
			RunVec4Test<MEDIUM>(test, SinCosSseVec<COS, COS, SIN, SIN, MEDIUM>(test.arg), (int)k);
			RunVec4Test<MEDIUM_LOW>(test, SinCosSseVec<COS, COS, SIN, SIN, MEDIUM_LOW>(test.arg), (int)k);
			RunVec4Test<LOW>(test, SinCosSseVec<COS, COS, SIN, SIN, LOW>(test.arg), (int)k);
		}
	}
}

TEST_CASE("FastSinCosSseVec can calculate approximate sines and cosines of SseVec angles", "[SseVec][TRIG][APPROX]")
{
	const int TEST_COUNT = 8;

	float vals[TEST_COUNT] {
		0.0f,
			F_PI_4,
			F_PI_2,
			F_3PI_4,
			F_PI,
			F_4PI_3,
			F_3PI_2,
			F_2PI
	};

	std::string valStrings[TEST_COUNT] {
		"0.0f",
			"F_PI_4",
			"F_PI_2",
			"F_3PI_4",
			"F_PI",
			"F_4PI_3",
			"F_3PI_2",
			"F_2PI"
	};

	SECTION("All Sines")
	{
		for (size_t j = 0; j < 2; j++)
		{
			std::string message = "";
			size_t k = j * 4;
			message += "<" + valStrings[k] + " " + valStrings[k + 1] + " " + valStrings[k + 2] + " " + valStrings[k + 3] + ">";

			Vec4 value = Vec4(vals[k], vals[k + 1], vals[k + 2], vals[k + 3]);
			Vec4 expected = Vec4(sinf(vals[k]), sinf(vals[k + 1]), sinf(vals[k + 2]), sinf(vals[k + 3]));

			SseVec4Context_1Arg test = { message, value, expected };

			RunVec4Test<FloatPrecision::MEDIUM>(test, FastSinCosSseVec<SIN,SIN,SIN,SIN>(test.arg), (int)k);
		}
	}

	SECTION("All Cosines")
	{
		for (size_t j = 0; j < 2; j++)
		{
			std::string message = "";
			size_t k = j * 4;
			message += "<" + valStrings[k] + " " + valStrings[k + 1] + " " + valStrings[k + 2] + " " + valStrings[k + 3] + ">";

			Vec4 value = Vec4(vals[k], vals[k + 1], vals[k + 2], vals[k + 3]);
			Vec4 expected = Vec4(cosf(vals[k]), cosf(vals[k + 1]), cosf(vals[k + 2]), cosf(vals[k + 3]));

			SseVec4Context_1Arg test = { message, value, expected };

			RunVec4Test<FloatPrecision::MEDIUM>(test, FastSinCosSseVec<COS,COS,COS,COS>(test.arg), (int)k);
		}
	}

	SECTION("Half Sines Half Cosines")
	{
		for (size_t j = 0; j < 2; j++)
		{
			std::string message = "";
			size_t k = j * 4;
			message += "<" + valStrings[k] + " " + valStrings[k + 1] + " " + valStrings[k + 2] + " " + valStrings[k + 3] + ">";

			Vec4 value = Vec4(vals[k], vals[k + 1], vals[k + 2], vals[k + 3]);
			Vec4 expected = Vec4(sinf(vals[k]), sinf(vals[k + 1]), cosf(vals[k + 2]), cosf(vals[k + 3]));

			SseVec4Context_1Arg test = { message, value, expected };

			RunVec4Test<FloatPrecision::MEDIUM>(test, FastSinCosSseVec<SIN,SIN,COS,COS>(test.arg), (int)k);
		}

		for (size_t j = 0; j < 2; j++)
		{
			std::string message = "";
			size_t k = j * 4;
			message += "<" + valStrings[k] + " " + valStrings[k + 1] + " " + valStrings[k + 2] + " " + valStrings[k + 3] + ">";

			Vec4 value = Vec4(vals[k], vals[k + 1], vals[k + 2], vals[k + 3]);
			Vec4 expected = Vec4(cosf(vals[k]), cosf(vals[k + 1]), sinf(vals[k + 2]), sinf(vals[k + 3]));

			SseVec4Context_1Arg test = { message, value, expected };

			RunVec4Test<FloatPrecision::MEDIUM>(test, FastSinCosSseVec<COS,COS,SIN,SIN>(test.arg), (int)k);
		}
	}
}


TEST_CASE("QuaternionMultiply can calculate the product of two quaternions","[SseVec][3D][Rotation]")
{
	const int NUM_TESTS = 6;
	SseVec4Context_2Args tests[NUM_TESTS] = { 
		{ "<0 1 0 0> <-1 0 0 0>", Quaternion(0.0f, 1.0f, 0.0f, 0.0f), Quaternion(-1.0f, 0.0f, 0.0f, 0.0f), Quaternion(0.0f, 0.0f, 1.0f, 0.0f) },
		{ "<1 0 0 1> <0 1 0 1>", Quaternion(1.0f, 0.0f, 0.0f, 1.0f), Quaternion(0.0f, 1.0f, 0.0f, 1.0f), Quaternion(1.0f) },
		{ "<1 0 1 0> <0 0 0 1>", Quaternion(1.0f, 0.0f, 1.0f, 0.0f), Quaternion::Identity(), Quaternion(1.0f, 0.0f, 1.0f, 0.0f) },
		{ "<1 1 1 1> <1 1 1 1>", Quaternion::One(), Quaternion::One(), Quaternion(2.0f, 2.0f, 2.0f, -2.0f)},
		{ "<0 0 0 0> <1 1 1 1>", Quaternion::Zero(), Quaternion::One(), Quaternion::Zero() },
		{ "<0 0 0 0> <0 0 0 0>", Quaternion::Zero(), Quaternion::Zero(), Quaternion::Zero() }
	};

	for (size_t i = 0; i < NUM_TESTS; i++)
	{
		RunVec4Test(tests[i], QuaternionMultiply(tests[i].arg0, tests[i].arg1));
	}
}

TEST_CASE("QuaternionFromAxisAngle can produce a quaternion SseVec from an axis-angle rotation", "[SseVec][3D][Rotation]")
{
	const int NUM_TESTS = 24;
	SseVec4Context_1Vec3Arg1ScalarArg tests[NUM_TESTS] {
		{ "< 1  0  0>  PI/2", Vec3( 1.0f,  0.0f,  0.0f),  F_PI_2, Quaternion( F_1_SQRT2,		  0.0f,		  0.0f,	F_1_SQRT2) },
		{ "< 0  1  0>  PI/2", Vec3( 0.0f,  1.0f,  0.0f),  F_PI_2, Quaternion(		 0.0f,	 F_1_SQRT2,		  0.0f,	F_1_SQRT2) },
		{ "< 0  0  1>  PI/2", Vec3( 0.0f,  0.0f,  1.0f),  F_PI_2, Quaternion(		 0.0f,		  0.0f,	 F_1_SQRT2,	F_1_SQRT2) },

		{ "< 1  0  0> -PI/2", Vec3( 1.0f,  0.0f,  0.0f), -F_PI_2, Quaternion(-F_1_SQRT2,		  0.0f,		  0.0f,	F_1_SQRT2) },
		{ "< 0  1  0> -PI/2", Vec3( 0.0f,  1.0f,  0.0f), -F_PI_2, Quaternion(		 0.0f,	-F_1_SQRT2,		  0.0f,	F_1_SQRT2) },
		{ "< 0  0  1> -PI/2", Vec3( 0.0f,  0.0f,  1.0f), -F_PI_2, Quaternion(		 0.0f,		  0.0f,	-F_1_SQRT2,	F_1_SQRT2) },

		{ "<-1  0  0>  PI/2", Vec3(-1.0f,  0.0f,  0.0f),  F_PI_2, Quaternion(-F_1_SQRT2,		  0.0f,		  0.0f,	F_1_SQRT2) },
		{ "< 0 -1  0>  PI/2", Vec3( 0.0f, -1.0f,  0.0f),  F_PI_2, Quaternion(		 0.0f,	-F_1_SQRT2,		  0.0f,	F_1_SQRT2) },
		{ "< 0  0 -1>  PI/2", Vec3( 0.0f,  0.0f, -1.0f),  F_PI_2, Quaternion(		 0.0f,		  0.0f,	-F_1_SQRT2,	F_1_SQRT2) },

		{ "<-1  0  0> -PI/2", Vec3(-1.0f,  0.0f,  0.0f), -F_PI_2, Quaternion( F_1_SQRT2,		  0.0f,		  0.0f,	F_1_SQRT2) },
		{ "< 0 -1  0> -PI/2", Vec3( 0.0f, -1.0f,  0.0f), -F_PI_2, Quaternion(		 0.0f,	 F_1_SQRT2,		  0.0f,	F_1_SQRT2) },
		{ "< 0  0 -1> -PI/2", Vec3( 0.0f,  0.0f, -1.0f), -F_PI_2, Quaternion(		 0.0f,		  0.0f,	 F_1_SQRT2,	F_1_SQRT2) },


		{ "< 1  0  0>  PI", Vec3( 1.0f,  0.0f,  0.0f),  F_PI, Quaternion( 1.0f,  0.0f,  0.0f, 0.0f) },
		{ "< 0  1  0>  PI", Vec3( 0.0f,  1.0f,  0.0f),  F_PI, Quaternion( 0.0f,  1.0f,  0.0f, 0.0f) },
		{ "< 0  0  1>  PI", Vec3( 0.0f,  0.0f,  1.0f),  F_PI, Quaternion( 0.0f,  0.0f,  1.0f, 0.0f) },

		{ "< 1  0  0> -PI", Vec3( 1.0f,  0.0f,  0.0f), -F_PI, Quaternion(-1.0f,  0.0f,  0.0f, 0.0f) },
		{ "< 0  1  0> -PI", Vec3( 0.0f,  1.0f,  0.0f), -F_PI, Quaternion( 0.0f, -1.0f,  0.0f, 0.0f) },
		{ "< 0  0  1> -PI", Vec3( 0.0f,  0.0f,  1.0f), -F_PI, Quaternion( 0.0f,  0.0f, -1.0f, 0.0f) },

		{ "<-1  0  0>  PI", Vec3(-1.0f,  0.0f,  0.0f),  F_PI, Quaternion(-1.0f,  0.0f,  0.0f, 0.0f) },
		{ "< 0 -1  0>  PI", Vec3( 0.0f, -1.0f,  0.0f),  F_PI, Quaternion( 0.0f, -1.0f,  0.0f, 0.0f) },
		{ "< 0  0 -1>  PI", Vec3( 0.0f,  0.0f, -1.0f),  F_PI, Quaternion( 0.0f,  0.0f, -1.0f, 0.0f) },

		{ "<-1  0  0> -PI", Vec3(-1.0f,  0.0f,  0.0f), -F_PI, Quaternion( 1.0f,  0.0f,  0.0f, 0.0f) },
		{ "< 0 -1  0> -PI", Vec3( 0.0f, -1.0f,  0.0f), -F_PI, Quaternion( 0.0f,  1.0f,  0.0f, 0.0f) },
		{ "< 0  0 -1> -PI", Vec3( 0.0f,  0.0f, -1.0f), -F_PI, Quaternion( 0.0f,  0.0f,  1.0f, 0.0f) },
	};

	for (size_t i = 0; i < NUM_TESTS; i++)
	{
		RunVec4Test(tests[i], QuaternionFromAxisAngle(tests[i].arg, tests[i].scalarArg), (int)i);
	}
}

TEST_CASE("QuaternionLerp can produce the linear interpolation of two quaternions", "[SseVec][3D][Rotation]")
{
	float mag_25_75 = sqrtf(0.75f * 0.75f + 0.25f * 0.25f);
	float mag_50_50 = sqrtf(0.5f  * 0.5f +  0.5f  * 0.5f);

	const int NUM_TESTS = 60;
	SseVec4Context_2Vec4Args1ScalarArg tests[NUM_TESTS] {
		{ "< 1  0  0  0> < 0  1  0  0>  0.0",  Vec4::E0(),	 Vec4::E1(),		0.0f,  Vec4::E0() },
		{ "<-1  0  0  0> < 0  1  0  0>  0.0",  Vec4::NegE0(), Vec4::E1(),		0.0f,  Vec4::NegE0() },
		{ "< 1  0  0  0> < 0 -1  0  0>  0.0",  Vec4::E0(),	 Vec4::NegE1(),  0.0f,  Vec4::E0() },
		{ "<-1  0  0  0> < 0 -1  0  0>  0.0",  Vec4::NegE0(), Vec4::NegE1(),	0.0f,  Vec4::NegE0() },

		{ "< 1  0  0  0> < 0  1  0  0>  0.25", Vec4::E0(),	 Vec4::E1(),		0.25f, Vec4( 0.75f / mag_25_75,  0.25f / mag_25_75, 0.0f, 0.0f) },
		{ "<-1  0  0  0> < 0  1  0  0>  0.25", Vec4::NegE0(), Vec4::E1(),		0.25f, Vec4(-0.75f / mag_25_75,  0.25f / mag_25_75, 0.0f, 0.0f) },
		{ "< 1  0  0  0> < 0 -1  0  0>  0.25", Vec4::E0(),	 Vec4::NegE1(),	0.25f, Vec4( 0.75f / mag_25_75, -0.25f / mag_25_75, 0.0f, 0.0f) },
		{ "<-1  0  0  0> < 0 -1  0  0>  0.25", Vec4::NegE0(), Vec4::NegE1(),	0.25f, Vec4(-0.75f / mag_25_75, -0.25f / mag_25_75, 0.0f, 0.0f) },

		{ "< 1  0  0  0> < 0  1  0  0>  0.5",  Vec4::E0(),	 Vec4::E1(),		0.5f,  Vec4( 0.5f / mag_50_50,   0.5f / mag_50_50,  0.0f, 0.0f) },
		{ "<-1  0  0  0> < 0  1  0  0>  0.5",  Vec4::NegE0(), Vec4::E1(),		0.5f,  Vec4(-0.5f / mag_50_50,   0.5f / mag_50_50,  0.0f, 0.0f) },
		{ "< 1  0  0  0> < 0 -1  0  0>  0.5",  Vec4::E0(),	 Vec4::NegE1(),   0.5f, Vec4( 0.5f / mag_50_50,  -0.5f / mag_50_50,  0.0f, 0.0f) },
		{ "<-1  0  0  0> < 0 -1  0  0>  0.5",  Vec4::NegE0(), Vec4::NegE1(),	0.5f,  Vec4(-0.5f / mag_50_50,  -0.5f / mag_50_50,  0.0f, 0.0f) },

		{ "< 1  0  0  0> < 0  1  0  0>  0.75", Vec4::E0(),	 Vec4::E1(),		0.75f, Vec4( 0.25f / mag_25_75,  0.75f / mag_25_75, 0.0f, 0.0f) },
		{ "<-1  0  0  0> < 0  1  0  0>  0.75", Vec4::NegE0(), Vec4::E1(),		0.75f, Vec4(-0.25f / mag_25_75,  0.75f / mag_25_75, 0.0f, 0.0f) },
		{ "< 1  0  0  0> < 0 -1  0  0>  0.75", Vec4::E0(),	 Vec4::NegE1(),	0.75f, Vec4( 0.25f / mag_25_75, -0.75f / mag_25_75, 0.0f, 0.0f) },
		{ "<-1  0  0  0> < 0 -1  0  0>  0.75", Vec4::NegE0(), Vec4::NegE1(),	0.75f, Vec4(-0.25f / mag_25_75, -0.75f / mag_25_75, 0.0f, 0.0f) },

		{ "< 1  0  0  0> < 0  1  0  0>  1.0",  Vec4::E0(),	 Vec4::E1(),		1.0f,  Vec4::E1() },
		{ "<-1  0  0  0> < 0  1  0  0>  1.0",  Vec4::NegE0(), Vec4::E1(),		1.0f,  Vec4::E1() },
		{ "< 1  0  0  0> < 0 -1  0  0>  1.0",  Vec4::E0(),	 Vec4::NegE1(),	1.0f,  Vec4::NegE1() },
		{ "<-1  0  0  0> < 0 -1  0  0>  1.0",  Vec4::NegE0(), Vec4::NegE1(),	1.0f,  Vec4::NegE1() },

		{ "<-1  0  0  0> < 1  0  0  0>  0.0",  Vec4::NegE0(), Vec4::E0(),		0.0f,  Vec4::NegE0() },
		{ "<-1  0  0  0> < 1  0  0  0>  0.25", Vec4::NegE0(), Vec4::E0(),		0.25f, Vec4::NegE0() },
		{ "<-1  0  0  0> < 1  0  0  0>  0.5",  Vec4::NegE0(), Vec4::E0(),		0.5f,  Vec4::NegE0() },
		{ "<-1  0  0  0> < 1  0  0  0>  0.75", Vec4::NegE0(), Vec4::E0(),		0.75f, Vec4::NegE0() },
		{ "<-1  0  0  0> < 1  0  0  0>  1.0",  Vec4::NegE0(), Vec4::E0(),		1.0f,  Vec4::NegE0() },

		{ "< 1  0  0  0> <-1  0  0  0>  0.0",  Vec4::E0(), Vec4::NegE0(),		0.0f,  Vec4::E0() },
		{ "< 1  0  0  0> <-1  0  0  0>  0.25", Vec4::E0(), Vec4::NegE0(),		0.25f, Vec4::E0() },
		{ "< 1  0  0  0> <-1  0  0  0>  0.5",  Vec4::E0(), Vec4::NegE0(),		0.5f,  Vec4::E0() },
		{ "< 1  0  0  0> <-1  0  0  0>  0.75", Vec4::E0(), Vec4::NegE0(),		0.75f, Vec4::E0() },
		{ "< 1  0  0  0> <-1  0  0  0>  1.0",  Vec4::E0(), Vec4::NegE0(),		1.0f,  Vec4::E0() },

		{ "< 0 -1  0  0> < 0  1  0  0>  0.0",  Vec4::NegE1(), Vec4::E1(),		0.0f,  Vec4::NegE1() },
		{ "< 0 -1  0  0> < 0  1  0  0>  0.25", Vec4::NegE1(), Vec4::E1(),		0.25f, Vec4::NegE1() },
		{ "< 0 -1  0  0> < 0  1  0  0>  0.5",  Vec4::NegE1(), Vec4::E1(),		0.5f,  Vec4::NegE1() },
		{ "< 0 -1  0  0> < 0  1  0  0>  0.75", Vec4::NegE1(), Vec4::E1(),		0.75f, Vec4::NegE1() },
		{ "< 0 -1  0  0> < 0  1  0  0>  1.0",  Vec4::NegE1(), Vec4::E1(),		1.0f,  Vec4::NegE1() },

		{ "< 0  1  0  0> < 0 -1  0  0>  0.0",  Vec4::E1(), Vec4::NegE1(),		0.0f,  Vec4::E1() },
		{ "< 0  1  0  0> < 0 -1  0  0>  0.25", Vec4::E1(), Vec4::NegE1(),		0.25f, Vec4::E1() },
		{ "< 0  1  0  0> < 0 -1  0  0>  0.5",  Vec4::E1(), Vec4::NegE1(),		0.5f,  Vec4::E1() },
		{ "< 0  1  0  0> < 0 -1  0  0>  0.75", Vec4::E1(), Vec4::NegE1(),		0.75f, Vec4::E1() },
		{ "< 0  1  0  0> < 0 -1  0  0>  1.0",  Vec4::E1(), Vec4::NegE1(),		1.0f,  Vec4::E1() },

		{ "< 0  0 -1  0> < 0  0  1  0>  0.0",  Vec4::NegE2(), Vec4::E2(),		0.0f,  Vec4::NegE2() },
		{ "< 0  0 -1  0> < 0  0  1  0>  0.25", Vec4::NegE2(), Vec4::E2(),		0.25f, Vec4::NegE2() },
		{ "< 0  0 -1  0> < 0  0  1  0>  0.5",  Vec4::NegE2(), Vec4::E2(),		0.5f,  Vec4::NegE2() },
		{ "< 0  0 -1  0> < 0  0  1  0>  0.75", Vec4::NegE2(), Vec4::E2(),		0.75f, Vec4::NegE2() },
		{ "< 0  0 -1  0> < 0  0  1  0>  1.0",  Vec4::NegE2(), Vec4::E2(),		1.0f,  Vec4::NegE2() },

		{ "< 0  0  1  0> < 0  0 -1  0>  0.0",  Vec4::E2(), Vec4::NegE2(),		0.0f,  Vec4::E2() },
		{ "< 0  0  1  0> < 0  0 -1  0>  0.25", Vec4::E2(), Vec4::NegE2(),		0.25f, Vec4::E2() },
		{ "< 0  0  1  0> < 0  0 -1  0>  0.5",  Vec4::E2(), Vec4::NegE2(),		0.5f,  Vec4::E2() },
		{ "< 0  0  1  0> < 0  0 -1  0>  0.75", Vec4::E2(), Vec4::NegE2(),		0.75f, Vec4::E2() },
		{ "< 0  0  1  0> < 0  0 -1  0>  1.0",  Vec4::E2(), Vec4::NegE2(),		1.0f,  Vec4::E2() },

		{ "< 0  0  0 -1> < 0  0  0  1>  0.0",  Vec4::NegE3(), Vec4::E3(),		0.0f,  Vec4::NegE3() },
		{ "< 0  0  0 -1> < 0  0  0  1>  0.25", Vec4::NegE3(), Vec4::E3(),		0.25f, Vec4::NegE3() },
		{ "< 0  0  0 -1> < 0  0  0  1>  0.5",  Vec4::NegE3(), Vec4::E3(),		0.5f,  Vec4::NegE3() },
		{ "< 0  0  0 -1> < 0  0  0  1>  0.75", Vec4::NegE3(), Vec4::E3(),		0.75f, Vec4::NegE3() },
		{ "< 0  0  0 -1> < 0  0  0  1>  1.0",  Vec4::NegE3(), Vec4::E3(),		1.0f,  Vec4::NegE3() },

		{ "< 0  0  0  1> < 0  0  0 -1>  0.0",  Vec4::E3(), Vec4::NegE3(),		0.0f,  Vec4::E3() },
		{ "< 0  0  0  1> < 0  0  0 -1>  0.25", Vec4::E3(), Vec4::NegE3(),		0.25f, Vec4::E3() },
		{ "< 0  0  0  1> < 0  0  0 -1>  0.5",  Vec4::E3(), Vec4::NegE3(),		0.5f,  Vec4::E3() },
		{ "< 0  0  0  1> < 0  0  0 -1>  0.75", Vec4::E3(), Vec4::NegE3(),		0.75f, Vec4::E3() },
		{ "< 0  0  0  1> < 0  0  0 -1>  1.0",  Vec4::E3(), Vec4::NegE3(),		1.0f,  Vec4::E3() },
	};

	for (size_t i = 0; i < NUM_TESTS; i++)
	{
		RunVec4Test(tests[i], QuaternionLerp(tests[i].arg0, tests[i].arg1, tests[i].scalarArg));
	}
}

TEST_CASE("QuaternionFromEuler can produce quaternions from euler angles", "[SseVec][3D][Rotation]")
{
	const int NUM_TESTS = 12;
	SseVec4Context_1Vec3Arg tests[NUM_TESTS] {
		{ "< PI/2      0     0>", Vec3(F_PI_2, 0.0f, 0.0f), Quaternion( F_1_SQRT2,	 0.0f,		 0.0f,		F_1_SQRT2) },
		{ "<    0   PI/2     0>", Vec3(0.0f, F_PI_2, 0.0f), Quaternion( 0.0f,		 F_1_SQRT2,	 0.0f,	    F_1_SQRT2) },
		{ "<    0      0  PI/2>", Vec3(0.0f, 0.0f, F_PI_2), Quaternion( 0.0f,		 0.0f,		 F_1_SQRT2, F_1_SQRT2) },

		{ "< -PI/2     0     0>", Vec3(-F_PI_2, 0.0f, 0.0f), Quaternion(-F_1_SQRT2,	 0.0f,		 0.0f,		F_1_SQRT2) },
		{ "<     0 -PI/2     0>", Vec3(0.0f, -F_PI_2, 0.0f), Quaternion(0.0f,		-F_1_SQRT2,  0.0f,		F_1_SQRT2) },
		{ "<     0     0 -PI/2>", Vec3(0.0f, 0.0f, -F_PI_2), Quaternion(0.0f,		 0.0f,		-F_1_SQRT2, F_1_SQRT2) },

		{ "< PI   0   0>", Vec3( F_PI,  0.0f,  0.0f), Quaternion( 1.0f,  0.0f,  0.0f, 0.0f) },
		{ "<  0  PI   0>", Vec3( 0.0f,  F_PI,  0.0f), Quaternion( 0.0f,  1.0f,  0.0f, 0.0f) },
		{ "<  0   0  PI>", Vec3( 0.0f,  0.0f,  F_PI), Quaternion( 0.0f,  0.0f,  1.0f, 0.0f) },

		{ "<-PI   0   0>", Vec3(-F_PI,  0.0f,  0.0f), Quaternion(-1.0f,  0.0f,  0.0f, 0.0f) },
		{ "<  0 -PI   0>", Vec3( 0.0f, -F_PI,  0.0f), Quaternion( 0.0f, -1.0f,  0.0f, 0.0f) },
		{ "<  0   0 -PI>", Vec3( 0.0f,  0.0f, -F_PI), Quaternion( 0.0f,  0.0f, -1.0f, 0.0f) },
	};

	for (size_t i = 0; i < NUM_TESTS; i++)
	{
		RunVec4Test(tests[i], QuaternionFromEuler(tests[i].arg), (int)i);
	}
}



TEST_CASE("FastQuaternionFromAxisAngle can produce an approximated quaternion SseVec from an axis-angle rotation", "[SseVec][3D][Rotation][APPROX]")
{
	const int NUM_TESTS = 24;
	SseVec4Context_1Vec3Arg1ScalarArg tests[NUM_TESTS] {
		{ "< 1  0  0>  PI/2", Vec3(1.0f, 0.0f, 0.0f), F_PI_2, Quaternion(F_1_SQRT2, 0.0f, 0.0f, F_1_SQRT2) },
		{ "< 0  1  0>  PI/2", Vec3(0.0f, 1.0f, 0.0f), F_PI_2, Quaternion(0.0f, F_1_SQRT2, 0.0f, F_1_SQRT2) },
		{ "< 0  0  1>  PI/2", Vec3(0.0f, 0.0f, 1.0f), F_PI_2, Quaternion(0.0f, 0.0f, F_1_SQRT2, F_1_SQRT2) },

		{ "< 1  0  0> -PI/2", Vec3(1.0f, 0.0f, 0.0f), -F_PI_2, Quaternion(-F_1_SQRT2, 0.0f, 0.0f, F_1_SQRT2) },
		{ "< 0  1  0> -PI/2", Vec3(0.0f, 1.0f, 0.0f), -F_PI_2, Quaternion(0.0f, -F_1_SQRT2, 0.0f, F_1_SQRT2) },
		{ "< 0  0  1> -PI/2", Vec3(0.0f, 0.0f, 1.0f), -F_PI_2, Quaternion(0.0f, 0.0f, -F_1_SQRT2, F_1_SQRT2) },

		{ "<-1  0  0>  PI/2", Vec3(-1.0f, 0.0f, 0.0f), F_PI_2, Quaternion(-F_1_SQRT2, 0.0f, 0.0f, F_1_SQRT2) },
		{ "< 0 -1  0>  PI/2", Vec3(0.0f, -1.0f, 0.0f), F_PI_2, Quaternion(0.0f, -F_1_SQRT2, 0.0f, F_1_SQRT2) },
		{ "< 0  0 -1>  PI/2", Vec3(0.0f, 0.0f, -1.0f), F_PI_2, Quaternion(0.0f, 0.0f, -F_1_SQRT2, F_1_SQRT2) },

		{ "<-1  0  0> -PI/2", Vec3(-1.0f, 0.0f, 0.0f), -F_PI_2, Quaternion(F_1_SQRT2, 0.0f, 0.0f, F_1_SQRT2) },
		{ "< 0 -1  0> -PI/2", Vec3(0.0f, -1.0f, 0.0f), -F_PI_2, Quaternion(0.0f, F_1_SQRT2, 0.0f, F_1_SQRT2) },
		{ "< 0  0 -1> -PI/2", Vec3(0.0f, 0.0f, -1.0f), -F_PI_2, Quaternion(0.0f, 0.0f, F_1_SQRT2, F_1_SQRT2) },


		{ "< 1  0  0>  PI", Vec3(1.0f, 0.0f, 0.0f), F_PI, Quaternion(1.0f, 0.0f, 0.0f, 0.0f) },
		{ "< 0  1  0>  PI", Vec3(0.0f, 1.0f, 0.0f), F_PI, Quaternion(0.0f, 1.0f, 0.0f, 0.0f) },
		{ "< 0  0  1>  PI", Vec3(0.0f, 0.0f, 1.0f), F_PI, Quaternion(0.0f, 0.0f, 1.0f, 0.0f) },

		{ "< 1  0  0> -PI", Vec3(1.0f, 0.0f, 0.0f), -F_PI, Quaternion(-1.0f, 0.0f, 0.0f, 0.0f) },
		{ "< 0  1  0> -PI", Vec3(0.0f, 1.0f, 0.0f), -F_PI, Quaternion(0.0f, -1.0f, 0.0f, 0.0f) },
		{ "< 0  0  1> -PI", Vec3(0.0f, 0.0f, 1.0f), -F_PI, Quaternion(0.0f, 0.0f, -1.0f, 0.0f) },

		{ "<-1  0  0>  PI", Vec3(-1.0f, 0.0f, 0.0f), F_PI, Quaternion(-1.0f, 0.0f, 0.0f, 0.0f) },
		{ "< 0 -1  0>  PI", Vec3(0.0f, -1.0f, 0.0f), F_PI, Quaternion(0.0f, -1.0f, 0.0f, 0.0f) },
		{ "< 0  0 -1>  PI", Vec3(0.0f, 0.0f, -1.0f), F_PI, Quaternion(0.0f, 0.0f, -1.0f, 0.0f) },

		{ "<-1  0  0> -PI", Vec3(-1.0f, 0.0f, 0.0f), -F_PI, Quaternion(1.0f, 0.0f, 0.0f, 0.0f) },
		{ "< 0 -1  0> -PI", Vec3(0.0f, -1.0f, 0.0f), -F_PI, Quaternion(0.0f, 1.0f, 0.0f, 0.0f) },
		{ "< 0  0 -1> -PI", Vec3(0.0f, 0.0f, -1.0f), -F_PI, Quaternion(0.0f, 0.0f, 1.0f, 0.0f) },
	};

	for (size_t i = 0; i < NUM_TESTS; i++)
	{
		RunVec4Test<FloatPrecision::MEDIUM>(tests[i], FastQuaternionFromAxisAngle(tests[i].arg, tests[i].scalarArg), (int)i);
	}
}

TEST_CASE("FastQuaternionLerp can produce the approximate linear interpolation of two quaternions", "[SseVec][3D][Rotation][APPROX]")
{
	float mag_25_75 = sqrtf(0.75f * 0.75f + 0.25f * 0.25f);
	float mag_50_50 = sqrtf(0.5f  * 0.5f + 0.5f  * 0.5f);

	const int NUM_TESTS = 60;
	SseVec4Context_2Vec4Args1ScalarArg tests[NUM_TESTS] {
		{ "< 1  0  0  0> < 0  1  0  0>  0.0", Vec4::E0(), Vec4::E1(), 0.0f, Vec4::E0() },
		{ "<-1  0  0  0> < 0  1  0  0>  0.0", Vec4::NegE0(), Vec4::E1(), 0.0f, Vec4::NegE0() },
		{ "< 1  0  0  0> < 0 -1  0  0>  0.0", Vec4::E0(), Vec4::NegE1(), 0.0f, Vec4::E0() },
		{ "<-1  0  0  0> < 0 -1  0  0>  0.0", Vec4::NegE0(), Vec4::NegE1(), 0.0f, Vec4::NegE0() },

		{ "< 1  0  0  0> < 0  1  0  0>  0.25", Vec4::E0(), Vec4::E1(), 0.25f, Vec4(0.75f / mag_25_75, 0.25f / mag_25_75, 0.0f, 0.0f) },
		{ "<-1  0  0  0> < 0  1  0  0>  0.25", Vec4::NegE0(), Vec4::E1(), 0.25f, Vec4(-0.75f / mag_25_75, 0.25f / mag_25_75, 0.0f, 0.0f) },
		{ "< 1  0  0  0> < 0 -1  0  0>  0.25", Vec4::E0(), Vec4::NegE1(), 0.25f, Vec4(0.75f / mag_25_75, -0.25f / mag_25_75, 0.0f, 0.0f) },
		{ "<-1  0  0  0> < 0 -1  0  0>  0.25", Vec4::NegE0(), Vec4::NegE1(), 0.25f, Vec4(-0.75f / mag_25_75, -0.25f / mag_25_75, 0.0f, 0.0f) },

		{ "< 1  0  0  0> < 0  1  0  0>  0.5", Vec4::E0(), Vec4::E1(), 0.5f, Vec4(0.5f / mag_50_50, 0.5f / mag_50_50, 0.0f, 0.0f) },
		{ "<-1  0  0  0> < 0  1  0  0>  0.5", Vec4::NegE0(), Vec4::E1(), 0.5f, Vec4(-0.5f / mag_50_50, 0.5f / mag_50_50, 0.0f, 0.0f) },
		{ "< 1  0  0  0> < 0 -1  0  0>  0.5", Vec4::E0(), Vec4::NegE1(), 0.5f, Vec4(0.5f / mag_50_50, -0.5f / mag_50_50, 0.0f, 0.0f) },
		{ "<-1  0  0  0> < 0 -1  0  0>  0.5", Vec4::NegE0(), Vec4::NegE1(), 0.5f, Vec4(-0.5f / mag_50_50, -0.5f / mag_50_50, 0.0f, 0.0f) },

		{ "< 1  0  0  0> < 0  1  0  0>  0.75", Vec4::E0(), Vec4::E1(), 0.75f, Vec4(0.25f / mag_25_75, 0.75f / mag_25_75, 0.0f, 0.0f) },
		{ "<-1  0  0  0> < 0  1  0  0>  0.75", Vec4::NegE0(), Vec4::E1(), 0.75f, Vec4(-0.25f / mag_25_75, 0.75f / mag_25_75, 0.0f, 0.0f) },
		{ "< 1  0  0  0> < 0 -1  0  0>  0.75", Vec4::E0(), Vec4::NegE1(), 0.75f, Vec4(0.25f / mag_25_75, -0.75f / mag_25_75, 0.0f, 0.0f) },
		{ "<-1  0  0  0> < 0 -1  0  0>  0.75", Vec4::NegE0(), Vec4::NegE1(), 0.75f, Vec4(-0.25f / mag_25_75, -0.75f / mag_25_75, 0.0f, 0.0f) },

		{ "< 1  0  0  0> < 0  1  0  0>  1.0", Vec4::E0(), Vec4::E1(), 1.0f, Vec4::E1() },
		{ "<-1  0  0  0> < 0  1  0  0>  1.0", Vec4::NegE0(), Vec4::E1(), 1.0f, Vec4::E1() },
		{ "< 1  0  0  0> < 0 -1  0  0>  1.0", Vec4::E0(), Vec4::NegE1(), 1.0f, Vec4::NegE1() },
		{ "<-1  0  0  0> < 0 -1  0  0>  1.0", Vec4::NegE0(), Vec4::NegE1(), 1.0f, Vec4::NegE1() },

		{ "<-1  0  0  0> < 1  0  0  0>  0.0", Vec4::NegE0(), Vec4::E0(), 0.0f, Vec4::NegE0() },
		{ "<-1  0  0  0> < 1  0  0  0>  0.25", Vec4::NegE0(), Vec4::E0(), 0.25f, Vec4::NegE0() },
		{ "<-1  0  0  0> < 1  0  0  0>  0.5", Vec4::NegE0(), Vec4::E0(), 0.5f, Vec4::NegE0() },
		{ "<-1  0  0  0> < 1  0  0  0>  0.75", Vec4::NegE0(), Vec4::E0(), 0.75f, Vec4::NegE0() },
		{ "<-1  0  0  0> < 1  0  0  0>  1.0", Vec4::NegE0(), Vec4::E0(), 1.0f, Vec4::NegE0() },

		{ "< 1  0  0  0> <-1  0  0  0>  0.0", Vec4::E0(), Vec4::NegE0(), 0.0f, Vec4::E0() },
		{ "< 1  0  0  0> <-1  0  0  0>  0.25", Vec4::E0(), Vec4::NegE0(), 0.25f, Vec4::E0() },
		{ "< 1  0  0  0> <-1  0  0  0>  0.5", Vec4::E0(), Vec4::NegE0(), 0.5f, Vec4::E0() },
		{ "< 1  0  0  0> <-1  0  0  0>  0.75", Vec4::E0(), Vec4::NegE0(), 0.75f, Vec4::E0() },
		{ "< 1  0  0  0> <-1  0  0  0>  1.0", Vec4::E0(), Vec4::NegE0(), 1.0f, Vec4::E0() },

		{ "< 0 -1  0  0> < 0  1  0  0>  0.0", Vec4::NegE1(), Vec4::E1(), 0.0f, Vec4::NegE1() },
		{ "< 0 -1  0  0> < 0  1  0  0>  0.25", Vec4::NegE1(), Vec4::E1(), 0.25f, Vec4::NegE1() },
		{ "< 0 -1  0  0> < 0  1  0  0>  0.5", Vec4::NegE1(), Vec4::E1(), 0.5f, Vec4::NegE1() },
		{ "< 0 -1  0  0> < 0  1  0  0>  0.75", Vec4::NegE1(), Vec4::E1(), 0.75f, Vec4::NegE1() },
		{ "< 0 -1  0  0> < 0  1  0  0>  1.0", Vec4::NegE1(), Vec4::E1(), 1.0f, Vec4::NegE1() },

		{ "< 0  1  0  0> < 0 -1  0  0>  0.0", Vec4::E1(), Vec4::NegE1(), 0.0f, Vec4::E1() },
		{ "< 0  1  0  0> < 0 -1  0  0>  0.25", Vec4::E1(), Vec4::NegE1(), 0.25f, Vec4::E1() },
		{ "< 0  1  0  0> < 0 -1  0  0>  0.5", Vec4::E1(), Vec4::NegE1(), 0.5f, Vec4::E1() },
		{ "< 0  1  0  0> < 0 -1  0  0>  0.75", Vec4::E1(), Vec4::NegE1(), 0.75f, Vec4::E1() },
		{ "< 0  1  0  0> < 0 -1  0  0>  1.0", Vec4::E1(), Vec4::NegE1(), 1.0f, Vec4::E1() },

		{ "< 0  0 -1  0> < 0  0  1  0>  0.0", Vec4::NegE2(), Vec4::E2(), 0.0f, Vec4::NegE2() },
		{ "< 0  0 -1  0> < 0  0  1  0>  0.25", Vec4::NegE2(), Vec4::E2(), 0.25f, Vec4::NegE2() },
		{ "< 0  0 -1  0> < 0  0  1  0>  0.5", Vec4::NegE2(), Vec4::E2(), 0.5f, Vec4::NegE2() },
		{ "< 0  0 -1  0> < 0  0  1  0>  0.75", Vec4::NegE2(), Vec4::E2(), 0.75f, Vec4::NegE2() },
		{ "< 0  0 -1  0> < 0  0  1  0>  1.0", Vec4::NegE2(), Vec4::E2(), 1.0f, Vec4::NegE2() },

		{ "< 0  0  1  0> < 0  0 -1  0>  0.0", Vec4::E2(), Vec4::NegE2(), 0.0f, Vec4::E2() },
		{ "< 0  0  1  0> < 0  0 -1  0>  0.25", Vec4::E2(), Vec4::NegE2(), 0.25f, Vec4::E2() },
		{ "< 0  0  1  0> < 0  0 -1  0>  0.5", Vec4::E2(), Vec4::NegE2(), 0.5f, Vec4::E2() },
		{ "< 0  0  1  0> < 0  0 -1  0>  0.75", Vec4::E2(), Vec4::NegE2(), 0.75f, Vec4::E2() },
		{ "< 0  0  1  0> < 0  0 -1  0>  1.0", Vec4::E2(), Vec4::NegE2(), 1.0f, Vec4::E2() },

		{ "< 0  0  0 -1> < 0  0  0  1>  0.0", Vec4::NegE3(), Vec4::E3(), 0.0f, Vec4::NegE3() },
		{ "< 0  0  0 -1> < 0  0  0  1>  0.25", Vec4::NegE3(), Vec4::E3(), 0.25f, Vec4::NegE3() },
		{ "< 0  0  0 -1> < 0  0  0  1>  0.5", Vec4::NegE3(), Vec4::E3(), 0.5f, Vec4::NegE3() },
		{ "< 0  0  0 -1> < 0  0  0  1>  0.75", Vec4::NegE3(), Vec4::E3(), 0.75f, Vec4::NegE3() },
		{ "< 0  0  0 -1> < 0  0  0  1>  1.0", Vec4::NegE3(), Vec4::E3(), 1.0f, Vec4::NegE3() },

		{ "< 0  0  0  1> < 0  0  0 -1>  0.0", Vec4::E3(), Vec4::NegE3(), 0.0f, Vec4::E3() },
		{ "< 0  0  0  1> < 0  0  0 -1>  0.25", Vec4::E3(), Vec4::NegE3(), 0.25f, Vec4::E3() },
		{ "< 0  0  0  1> < 0  0  0 -1>  0.5", Vec4::E3(), Vec4::NegE3(), 0.5f, Vec4::E3() },
		{ "< 0  0  0  1> < 0  0  0 -1>  0.75", Vec4::E3(), Vec4::NegE3(), 0.75f, Vec4::E3() },
		{ "< 0  0  0  1> < 0  0  0 -1>  1.0", Vec4::E3(), Vec4::NegE3(), 1.0f, Vec4::E3() },
	};

	for (size_t i = 0; i < NUM_TESTS; i++)
	{
		RunVec4Test<FloatPrecision::MEDIUM>(tests[i], FastQuaternionLerp(tests[i].arg0, tests[i].arg1, tests[i].scalarArg));
	}
}

TEST_CASE("StoreSseVec2 should properly store a SseVec into a Vec2", "[SseVec][2D][MEMORY]")
{
	// Using standard intrinsics load function rather than custom, swizzled function.  
	// The leftmost 1 is only there as a formality.  This test shouldn't require that it be there,
	// as it is only important for various calculations, and this is simply a test to ensure the memory
	// of a SseVec is positioned as expected from a Vec2 by other functions.
	// 
	// For more info on the memory format, check out the documentation files.
	SseVec cv = _mm_set_ps(1.0f, 0.0f, 3.0f, 2.0f);
	Vec2 result = StoreSseVec2(cv);

	Vec2 expected(2.0f, 3.0f);

	CHECK(result == expected);
}

TEST_CASE("StoreSseVec3 should properly store a SseVec into a Vec3", "[SseVec][3D][MEMORY]")
{
	// Using standard intrinsics load function rather than custom, swizzled function.  
	// The leftmost 1 is only there as a formality.  This test shouldn't require that it be there,
	// as it is only important for various calculations, and this is simply a test to ensure the memory
	// of a SseVec is positioned as expected from a Vec3 by other functions.
	//
	// For more info on the memory format, check out the documentation files.
	SseVec cv = _mm_set_ps(1.0f, 4.0f, 3.0f, 2.0f);
	Vec3 result = StoreSseVec3(cv);

	Vec3 expected(2.0f, 3.0f, 4.0f);

	CHECK(result == expected);
}

TEST_CASE("StoreSseVec4 should properly store a SseVec into a Vec4", "[SseVec][4D][MEMORY]")
{
	SseVec cv = _mm_set_ps(1.0f, 4.0f, 3.0f, 2.0f);
	Vec4 result = StoreSseVec4(cv);

	Vec4 expected(2.0f, 3.0f, 4.0f, 1.0f);

	CHECK(result == expected);
}

TEST_CASE("LoadSseVec2 should properly load a Vec2 into a SseVec", "[SseVec][2D][MEMORY]")
{
	// Using standard intrinsics load function rather than custom, swizzled function.  
	// The leftmost 1 is only there as a formality.  This test shouldn't require that it be there,
	// as it is only important for various calculations, and this is simply a test to ensure the memory
	// of a SseVec is positioned as expected from a Vec2 by other functions.
	// 
	// For more info on the memory format, check out the documentation files.
	SseVec cv = LoadSseVec2(Vec2(2.0f, 3.0f));
	AlignedFloat4 resultContainer;
	_mm_store_ps(resultContainer.vals, cv);

	Vec2 result(resultContainer.vals[0], resultContainer.vals[1]);

	Vec2 expected(2.0f, 3.0f);

	CHECK(result == expected);
}

TEST_CASE("LoadSseVec3 should properly store a Vec3 into a SseVec", "[SseVec][3D][MEMORY]")
{
	// Using standard intrinsics load function rather than custom, swizzled function.  
	// The leftmost 1 is only there as a formality.  This test shouldn't require that it be there,
	// as it is only important for various calculations, and this is simply a test to ensure the memory
	// of a SseVec is positioned as expected from a Vec3 by other functions.
	//
	// For more info on the memory format, check out the documentation files.
	SseVec cv = LoadSseVec3(Vec3(2.0f, 3.0f, 4.0f));
	AlignedFloat4 resultContainer;
	_mm_store_ps(resultContainer.vals, cv);

	Vec3 result(resultContainer.vals[0], resultContainer.vals[1], resultContainer.vals[2]);
	Vec3 expected(2.0f, 3.0f, 4.0f);

	CHECK(result == expected);
}

TEST_CASE("LoadSseVec4 should properly store a Vec4 into a SseVec", "[SseVec][4D][MEMORY]")
{
	SseVec cv = LoadSseVec4(Vec4(2.0f, 3.0f, 4.0f, 1.0f));
	AlignedFloat4 resultContainer;
	_mm_store_ps(resultContainer.vals, cv);

	Vec4 result(resultContainer.vals[0], resultContainer.vals[1], resultContainer.vals[2], resultContainer.vals[3]);
	Vec4 expected(2.0f, 3.0f, 4.0f, 1.0f);

	CHECK(result == expected);
}
