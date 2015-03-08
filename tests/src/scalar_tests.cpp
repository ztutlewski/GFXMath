#include "scalar_tests.h"

using namespace gofxmath;

const std::array<float, NUM_PRECISION_VALS> INF_PRECISION_VALS
{{
	Infinity(),	// HIGH
	10e+6,		// MEDIUM_HIGH
	10e+4,		// MEDIUM
	10e+3,		// MEDIUM_LOW
	10e+2,		// LOW
}};

void RunScalarInfTest(float result)
{
	INFO("RESULT: " << result);

	bool resultIsInf = std::isinf(result);

	CHECK(resultIsInf);
}

TEST_CASE("NormalizeAngle can shift and scale an angle (in radians) from any non-infinite, real number float to the range [-PI,PI)")
{
	SECTION("Zero")
	{
		float value = 0.0f;
		float result = NormalizeAngle(value);
		float expected = 0.0f;
		
		RunScalarTest(result, expected);
	}

	SECTION("PI/4")
	{
		float value = F_PI_4;
		float result = NormalizeAngle(value);
		float expected = F_PI_4;

		RunScalarTest(result, expected);
	}

	SECTION("PI/2")
	{
		float value = F_PI_2;
		float result = NormalizeAngle(value);
		float expected = F_PI_2;

		RunScalarTest(result, expected);
	}

	SECTION("PI")
	{
		float value = F_PI;
		float result = NormalizeAngle(value);
		float expected = -F_PI;

		RunScalarTest(result, expected);
	}

	SECTION("4PI/3")
	{
		float value = F_4PI_3;
		float result = NormalizeAngle(value);
		float expected = -F_2PI_3;

		RunScalarTest(result, expected);
	}

	SECTION("49PI")
	{
		float value = 49 * F_PI;
		float result = NormalizeAngle(value);
		float expected = -F_PI;

		RunScalarTest<FloatPrecision::MEDIUM_HIGH>(result, expected);
	}

	SECTION("50PI")
	{
		float value = 50 * F_PI;
		float result = NormalizeAngle(value);
		float expected = 0.0f;

		RunScalarTest(result, expected);
	}
}

TEST_CASE("FastSinApprox can approximate sine within 0.01 margin of error from the standard implementation, within the range [-PI,PI)")
{
	SECTION("Zero")
	{
		float value = 0.0f;
		float result = FastSinApprox(value);
		float expected = 0.0f;

		RunScalarTest<FloatPrecision::MEDIUM>(result, expected);
	}

	SECTION("PI/4")
	{
		float value = F_PI_4;
		float result = FastSinApprox(value);
		float expected = F_1_SQRT2;

		RunScalarTest<FloatPrecision::MEDIUM>(result, expected);
	}

	SECTION("PI/2")
	{
		float value = F_PI_2;
		float result = FastSinApprox(value);
		float expected = 1.0f;

		RunScalarTest<FloatPrecision::MEDIUM>(result, expected);
	}

	SECTION("PI")
	{
		float value = F_PI;
		float result = FastSinApprox(value);
		float expected = 0.0f;

		RunScalarTest<FloatPrecision::MEDIUM>(result, expected);
	}

	/*SECTION("4PI/3")
	{
		float value = F_4PI_3;
		float result = FastSinApprox(value);
		float expected = -F_SQRT3_2;

		RunScalarTest<FloatPrecision::MEDIUM>(result, expected);
	}

	SECTION("49PI")
	{
		float value = 49 * F_PI;
		float result = FastSinApprox(value);
		float expected = 0.0f;

		RunScalarTest<FloatPrecision::MEDIUM>(result, expected);
	}

	SECTION("49.5PI")
	{
		float value = 49.5f * F_PI;
		float result = FastSinApprox(value);
		float expected = -1.0f;

		RunScalarTest<FloatPrecision::MEDIUM>(result, expected);
	}*/
}

TEST_CASE("FastCosApprox can approximate cosine within 0.01 margin of error from the standard implementation, within the range [-PI,PI)")
{
	SECTION("Zero")
	{
		float value = 0.0f;
		float result = FastCosApprox(value);
		float expected = 1.0f;

		RunScalarTest<FloatPrecision::MEDIUM>(result, expected);
	}

	SECTION("PI/4")
	{
		float value = F_PI_4;
		float result = FastCosApprox(value);
		float expected = F_1_SQRT2;

		RunScalarTest<FloatPrecision::MEDIUM>(result, expected);
	}

	SECTION("PI/2")
	{
		float value = F_PI_2;
		float result = FastCosApprox(value);
		float expected = 0.0f;

		RunScalarTest<FloatPrecision::MEDIUM>(result, expected);
	}

	SECTION("PI")
	{
		float value = F_PI;
		float result = FastCosApprox(value);
		float expected = -1.0f;

		RunScalarTest<FloatPrecision::MEDIUM>(result, expected);
	}

	/*SECTION("4PI/3")
	{
		float value = F_4PI_3;
		float result = FastCosApprox(value);
		float expected = -0.5f;

		RunScalarTest<FloatPrecision::MEDIUM>(result, expected);
	}

	SECTION("49PI")
	{
		float value = 49 * F_PI;
		float result = FastCosApprox(value);
		float expected = -1.0f;

		RunScalarTest<FloatPrecision::MEDIUM>(result, expected);
	}

	SECTION("49.5PI")
	{
		float value = 49.5f * F_PI;
		float result = FastCosApprox(value);
		float expected = 0.0f;

		RunScalarTest<FloatPrecision::MEDIUM>(result, expected);
	}*/
}

TEST_CASE("FastTanApprox can approximate tangent within 0.01 margin of error from the standard implementation, within the range [-PI,PI)")
{
	SECTION("Zero")
	{
		float value = 0.0f;
		float result = FastTanApprox(value);
		float expected = 0.0f;

		RunScalarTest<FloatPrecision::MEDIUM>(result, expected);
	}

	SECTION("PI/4")
	{
		float value = F_PI_4;
		float result = FastTanApprox(value);
		float expected = 1.0f;

		RunScalarTest<FloatPrecision::MEDIUM>(result, expected);
	}

	SECTION("PI/2")
	{
		float value = F_PI_2;
		float result = FastTanApprox(value);

		RunScalarApproxInfTest<FloatPrecision::MEDIUM>(result);
	}

	SECTION("PI")
	{
		float value = F_PI;
		float result = FastTanApprox(value);
		float expected = 0.0f;

		RunScalarTest<FloatPrecision::MEDIUM>(result, expected);
	}

	/*SECTION("4PI/3")
	{
		float value = F_4PI_3;
		float result = FastTanApprox(value);
		float expected = F_SQRT3;

		RunScalarTest<FloatPrecision::MEDIUM_LOW>(result, expected);
	}

	SECTION("49PI")
	{
		float value = 49 * F_PI;
		float result = FastTanApprox(value);
		float expected = 0.0f;

		RunScalarTest<FloatPrecision::MEDIUM>(result, expected);
	}

	SECTION("49.5PI")
	{
		float value = 49.5f * F_PI;
		float result = FastTanApprox(value);

		RunScalarApproxInfTest<FloatPrecision::MEDIUM>(result);
	}*/
}

TEST_CASE("FastCotApprox can approximate cotangent within 0.01 margin of error from the standard implementation, within the range [-PI,PI)")
{
	SECTION("Zero")
	{
		float value = 0.0f;
		float result = FastCotApprox(value);

		RunScalarApproxInfTest<FloatPrecision::MEDIUM>(result);
	}

	SECTION("PI/4")
	{
		float value = F_PI_4;
		float result = FastCotApprox(value);
		float expected = 1.0f;

		RunScalarTest<FloatPrecision::MEDIUM>(result, expected);
	}

	SECTION("PI/2")
	{
		float value = F_PI_2;
		float result = FastCotApprox(value);
		float expected = 0.0f;

		RunScalarTest<FloatPrecision::MEDIUM>(result, expected);
	}

	SECTION("PI")
	{
		float value = F_PI;
		float result = FastCotApprox(value);

		RunScalarApproxInfTest<FloatPrecision::MEDIUM>(result);
	}

	/*SECTION("4PI/3")
	{
		float value = F_4PI_3;
		float result = FastCotApprox(value);
		float expected = F_1_SQRT3;

		RunScalarTest<FloatPrecision::MEDIUM>(result, expected);
	}

	SECTION("49PI")
	{
		float value = 49 * F_PI;
		float result = FastCotApprox(value);

		RunScalarApproxInfTest<FloatPrecision::MEDIUM>(result);
	}

	SECTION("49.5PI")
	{
		float value = 49.5f * F_PI;
		float result = FastCotApprox(value);
		float expected = 0.0f;

		RunScalarTest<FloatPrecision::MEDIUM>(result, expected);
	}*/
}

TEST_CASE("SinApprox can approximate the sine within varying levels of accuracy, given specific settings")
{
	SECTION("HIGH")
	{
		const FloatPrecision PRECISION = FloatPrecision::HIGH;
		const FloatPrecision DROPOFF_PRECISION = FloatPrecision::MEDIUM_HIGH;

		SECTION("Zero")
		{
			float value = 0.0f;
			float result = SinApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI/4")
		{
			float value = F_PI_4;
			float result = SinApprox<PRECISION>(value);
			float expected = F_1_SQRT2;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI/2")
		{
			float value = F_PI_2;
			float result = SinApprox<PRECISION>(value);
			float expected = 1.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI")
		{
			float value = F_PI;
			float result = SinApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("4PI/3")
		{
			float value = F_4PI_3;
			float result = SinApprox<PRECISION>(value);
			float expected = -F_SQRT3_2;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("49PI")
		{
			float value = 49 * F_PI;
			float result = SinApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<DROPOFF_PRECISION>(result, expected);
		}

		SECTION("49.5PI")
		{
			float value = 49.5f * F_PI;
			float result = SinApprox<PRECISION>(value);
			float expected = -1.0f;

			RunScalarTest<DROPOFF_PRECISION>(result, expected);
		}
	}

	SECTION("MEDIUM_HIGH")
	{
		const FloatPrecision PRECISION = FloatPrecision::MEDIUM_HIGH;
		const FloatPrecision DROPOFF_PRECISION = FloatPrecision::MEDIUM_HIGH;

		SECTION("Zero")
		{
			float value = 0.0f;
			float result = SinApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI/4")
		{
			float value = F_PI_4;
			float result = SinApprox<PRECISION>(value);
			float expected = F_1_SQRT2;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI/2")
		{
			float value = F_PI_2;
			float result = SinApprox<PRECISION>(value);
			float expected = 1.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI")
		{
			float value = F_PI;
			float result = SinApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("4PI/3")
		{
			float value = F_4PI_3;
			float result = SinApprox<PRECISION>(value);
			float expected = -F_SQRT3_2;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("49PI")
		{
			float value = 49 * F_PI;
			float result = SinApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<DROPOFF_PRECISION>(result, expected);
		}

		SECTION("49.5PI")
		{
			float value = 49.5f * F_PI;
			float result = SinApprox<PRECISION>(value);
			float expected = -1.0f;

			RunScalarTest<DROPOFF_PRECISION>(result, expected);
		}
	}

	SECTION("MEDIUM")
	{
		const FloatPrecision PRECISION = FloatPrecision::MEDIUM;
		const FloatPrecision DROPOFF_PRECISION = FloatPrecision::MEDIUM;

		SECTION("Zero")
		{
			float value = 0.0f;
			float result = SinApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI/4")
		{
			float value = F_PI_4;
			float result = SinApprox<PRECISION>(value);
			float expected = F_1_SQRT2;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI/2")
		{
			float value = F_PI_2;
			float result = SinApprox<PRECISION>(value);
			float expected = 1.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI")
		{
			float value = F_PI;
			float result = SinApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("4PI/3")
		{
			float value = F_4PI_3;
			float result = SinApprox<PRECISION>(value);
			float expected = -F_SQRT3_2;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("49PI")
		{
			float value = 49 * F_PI;
			float result = SinApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<DROPOFF_PRECISION>(result, expected);
		}

		SECTION("49.5PI")
		{
			float value = 49.5f * F_PI;
			float result = SinApprox<PRECISION>(value);
			float expected = -1.0f;

			RunScalarTest<DROPOFF_PRECISION>(result, expected);
		}
	}

	SECTION("MEDIUM_LOW")
	{
		const FloatPrecision PRECISION = FloatPrecision::MEDIUM_LOW;
		const FloatPrecision DROPOFF_PRECISION = FloatPrecision::MEDIUM_LOW;

		SECTION("Zero")
		{
			float value = 0.0f;
			float result = SinApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI/4")
		{
			float value = F_PI_4;
			float result = SinApprox<PRECISION>(value);
			float expected = F_1_SQRT2;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI/2")
		{
			float value = F_PI_2;
			float result = SinApprox<PRECISION>(value);
			float expected = 1.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI")
		{
			float value = F_PI;
			float result = SinApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("4PI/3")
		{
			float value = F_4PI_3;
			float result = SinApprox<PRECISION>(value);
			float expected = -F_SQRT3_2;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("49PI")
		{
			float value = 49 * F_PI;
			float result = SinApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<DROPOFF_PRECISION>(result, expected);
		}

		SECTION("49.5PI")
		{
			float value = 49.5f * F_PI;
			float result = SinApprox<PRECISION>(value);
			float expected = -1.0f;

			RunScalarTest<DROPOFF_PRECISION>(result, expected);
		}
	}

	SECTION("LOW")
	{
		const FloatPrecision PRECISION = FloatPrecision::LOW;
		const FloatPrecision DROPOFF_PRECISION = FloatPrecision::LOW;

		SECTION("Zero")
		{
			float value = 0.0f;
			float result = SinApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI/4")
		{
			float value = F_PI_4;
			float result = SinApprox<PRECISION>(value);
			float expected = F_1_SQRT2;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI/2")
		{
			float value = F_PI_2;
			float result = SinApprox<PRECISION>(value);
			float expected = 1.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI")
		{
			float value = F_PI;
			float result = SinApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("4PI/3")
		{
			float value = F_4PI_3;
			float result = SinApprox<PRECISION>(value);
			float expected = -F_SQRT3_2;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("49PI")
		{
			float value = 49 * F_PI;
			float result = SinApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<DROPOFF_PRECISION>(result, expected);
		}

		SECTION("49.5PI")
		{
			float value = 49.5f * F_PI;
			float result = SinApprox<PRECISION>(value);
			float expected = -1.0f;

			RunScalarTest<DROPOFF_PRECISION>(result, expected);
		}
	}
}

TEST_CASE("CosApprox can approximate the cosine within varying levels of accuracy, given specific settings")
{
	SECTION("HIGH")
	{
		const FloatPrecision PRECISION = FloatPrecision::HIGH;
		const FloatPrecision DROPOFF_PRECISION = FloatPrecision::MEDIUM_HIGH;

		SECTION("Zero")
		{
			float value = 0.0f;
			float result = CosApprox<PRECISION>(value);
			float expected = 1.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI/4")
		{
			float value = F_PI_4;
			float result = CosApprox<PRECISION>(value);
			float expected = F_1_SQRT2;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI/2")
		{
			float value = F_PI_2;
			float result = CosApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI")
		{
			float value = F_PI;
			float result = CosApprox<PRECISION>(value);
			float expected = -1.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("4PI/3")
		{
			float value = F_4PI_3;
			float result = CosApprox<PRECISION>(value);
			float expected = -0.5f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("49PI")
		{
			float value = 49 * F_PI;
			float result = CosApprox<PRECISION>(value);
			float expected = -1.0f;

			RunScalarTest<DROPOFF_PRECISION>(result, expected);
		}

		SECTION("49.5PI")
		{
			float value = 49.5f * F_PI;
			float result = CosApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<DROPOFF_PRECISION>(result, expected);
		}
	}

	SECTION("MEDIUM_HIGH")
	{
		const FloatPrecision PRECISION = FloatPrecision::MEDIUM_HIGH;
		const FloatPrecision DROPOFF_PRECISION = FloatPrecision::MEDIUM_HIGH;

		SECTION("Zero")
		{
			float value = 0.0f;
			float result = CosApprox<PRECISION>(value);
			float expected = 1.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI/4")
		{
			float value = F_PI_4;
			float result = CosApprox<PRECISION>(value);
			float expected = F_1_SQRT2;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI/2")
		{
			float value = F_PI_2;
			float result = CosApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI")
		{
			float value = F_PI;
			float result = CosApprox<PRECISION>(value);
			float expected = -1.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("4PI/3")
		{
			float value = F_4PI_3;
			float result = CosApprox<PRECISION>(value);
			float expected = -0.5f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("49PI")
		{
			float value = 49 * F_PI;
			float result = CosApprox<PRECISION>(value);
			float expected = -1.0f;

			RunScalarTest<DROPOFF_PRECISION>(result, expected);
		}

		SECTION("49.5PI")
		{
			float value = 49.5f * F_PI;
			float result = CosApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<DROPOFF_PRECISION>(result, expected);
		}
	}

	SECTION("MEDIUM")
	{
		const FloatPrecision PRECISION = FloatPrecision::MEDIUM;
		const FloatPrecision DROPOFF_PRECISION = FloatPrecision::MEDIUM;

		SECTION("Zero")
		{
			float value = 0.0f;
			float result = CosApprox<PRECISION>(value);
			float expected = 1.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI/4")
		{
			float value = F_PI_4;
			float result = CosApprox<PRECISION>(value);
			float expected = F_1_SQRT2;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI/2")
		{
			float value = F_PI_2;
			float result = CosApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI")
		{
			float value = F_PI;
			float result = CosApprox<PRECISION>(value);
			float expected = -1.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("4PI/3")
		{
			float value = F_4PI_3;
			float result = CosApprox<PRECISION>(value);
			float expected = -0.5f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("49PI")
		{
			float value = 49 * F_PI;
			float result = CosApprox<PRECISION>(value);
			float expected = -1.0f;

			RunScalarTest<DROPOFF_PRECISION>(result, expected);
		}

		SECTION("49.5PI")
		{
			float value = 49.5f * F_PI;
			float result = CosApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<DROPOFF_PRECISION>(result, expected);
		}
	}

	SECTION("MEDIUM_LOW")
	{
		const FloatPrecision PRECISION = FloatPrecision::MEDIUM_LOW;
		const FloatPrecision DROPOFF_PRECISION = FloatPrecision::MEDIUM_LOW;

		SECTION("Zero")
		{
			float value = 0.0f;
			float result = CosApprox<PRECISION>(value);
			float expected = 1.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI/4")
		{
			float value = F_PI_4;
			float result = CosApprox<PRECISION>(value);
			float expected = F_1_SQRT2;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI/2")
		{
			float value = F_PI_2;
			float result = CosApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI")
		{
			float value = F_PI;
			float result = CosApprox<PRECISION>(value);
			float expected = -1.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("4PI/3")
		{
			float value = F_4PI_3;
			float result = CosApprox<PRECISION>(value);
			float expected = -0.5f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("49PI")
		{
			float value = 49 * F_PI;
			float result = CosApprox<PRECISION>(value);
			float expected = -1.0f;

			RunScalarTest<DROPOFF_PRECISION>(result, expected);
		}

		SECTION("49.5PI")
		{
			float value = 49.5f * F_PI;
			float result = CosApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<DROPOFF_PRECISION>(result, expected);
		}
	}

	SECTION("LOW")
	{
		const FloatPrecision PRECISION = FloatPrecision::LOW;
		const FloatPrecision DROPOFF_PRECISION = FloatPrecision::LOW;

		SECTION("Zero")
		{
			float value = 0.0f;
			float result = CosApprox<PRECISION>(value);
			float expected = 1.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI/4")
		{
			float value = F_PI_4;
			float result = CosApprox<PRECISION>(value);
			float expected = F_1_SQRT2;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI/2")
		{
			float value = F_PI_2;
			float result = CosApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI")
		{
			float value = F_PI;
			float result = CosApprox<PRECISION>(value);
			float expected = -1.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("4PI/3")
		{
			float value = F_4PI_3;
			float result = CosApprox<PRECISION>(value);
			float expected = -0.5f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("49PI")
		{
			float value = 49 * F_PI;
			float result = CosApprox<PRECISION>(value);
			float expected = -1.0f;

			RunScalarTest<DROPOFF_PRECISION>(result, expected);
		}

		SECTION("49.5PI")
		{
			float value = 49.5f * F_PI;
			float result = CosApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<DROPOFF_PRECISION>(result, expected);
		}
	}
}

TEST_CASE("TanApprox can approximate the tangent within varying levels of accuracy, given specific settings")
{
	// The PRECISION and DROPOFF_PRECISION constants May produce compiler warnings with Visual C++ stating "local variable initialized but not referenced"
	// This is very likely due to the fact that they are used only as template parameters.  It is quite evident that this is simply a bug with the compiler, 
	// as removal of these variables produces errors at every instance of their use (as would be expected).

	SECTION("HIGH")
	{
		const FloatPrecision PRECISION = FloatPrecision::HIGH;
		const FloatPrecision DROPOFF_PRECISION = FloatPrecision::MEDIUM_HIGH;

		SECTION("Zero")
		{
			float value = 0.0f;
			float result = TanApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI/4")
		{
			float value = F_PI_4;
			float result = TanApprox<PRECISION>(value);
			float expected = 1.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI/2")
		{
			float value = F_PI_2;
			float result = TanApprox<PRECISION>(value);

			RunScalarApproxInfTest<PRECISION>(result);
		}

		SECTION("PI")
		{
			float value = F_PI;
			float result = TanApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("4PI/3")
		{
			float value = F_4PI_3;
			float result = TanApprox<PRECISION>(value);
			float expected = F_SQRT3;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("49PI")
		{
			float value = 49 * F_PI;
			float result = TanApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<FloatPrecision::MEDIUM>(result, expected);
		}

		SECTION("49.5PI")
		{
			float value = 49.5f * F_PI;
			float result = TanApprox<PRECISION>(value);

			RunScalarApproxInfTest<PRECISION>(result);
		}
	}

	SECTION("MEDIUM_HIGH")
	{
		const FloatPrecision PRECISION = FloatPrecision::MEDIUM_HIGH;
		const FloatPrecision DROPOFF_PRECISION = FloatPrecision::MEDIUM_HIGH;

		SECTION("Zero")
		{
			float value = 0.0f;
			float result = TanApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI/4")
		{
			float value = F_PI_4;
			float result = TanApprox<PRECISION>(value);
			float expected = 1.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI/2")
		{
			float value = F_PI_2;
			float result = TanApprox<PRECISION>(value);

			RunScalarApproxInfTest<PRECISION>(result);
		}

		SECTION("PI")
		{
			float value = F_PI;
			float result = TanApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("4PI/3")
		{
			float value = F_4PI_3;
			float result = TanApprox<PRECISION>(value);
			float expected = F_SQRT3;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("49PI")
		{
			float value = 49 * F_PI;
			float result = TanApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<FloatPrecision::MEDIUM>(result, expected);
		}

		SECTION("49.5PI")
		{
			float value = 49.5f * F_PI;
			float result = TanApprox<PRECISION>(value);

			RunScalarApproxInfTest<PRECISION>(result);
		}
	}

	SECTION("MEDIUM")
	{
		const FloatPrecision PRECISION = FloatPrecision::MEDIUM;
		const FloatPrecision DROPOFF_PRECISION = FloatPrecision::MEDIUM;

		SECTION("Zero")
		{
			float value = 0.0f;
			float result = TanApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI/4")
		{
			float value = F_PI_4;
			float result = TanApprox<PRECISION>(value);
			float expected = 1.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI/2")
		{
			float value = F_PI_2;
			float result = TanApprox<PRECISION>(value);

			RunScalarApproxInfTest<PRECISION>(result);
		}

		SECTION("PI")
		{
			float value = F_PI;
			float result = TanApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("4PI/3")
		{
			float value = F_4PI_3;
			float result = TanApprox<PRECISION>(value);
			float expected = F_SQRT3;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("49PI")
		{
			float value = 49 * F_PI;
			float result = TanApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<FloatPrecision::MEDIUM>(result, expected);
		}

		SECTION("49.5PI")
		{
			float value = 49.5f * F_PI;
			float result = TanApprox<PRECISION>(value);

			RunScalarApproxInfTest<PRECISION>(result);
		}
	}

	SECTION("MEDIUM_LOW")
	{
		const FloatPrecision PRECISION = FloatPrecision::MEDIUM_LOW;
		const FloatPrecision DROPOFF_PRECISION = FloatPrecision::MEDIUM_LOW;

		SECTION("Zero")
		{
			float value = 0.0f;
			float result = TanApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI/4")
		{
			float value = F_PI_4;
			float result = TanApprox<PRECISION>(value);
			float expected = 1.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI/2")
		{
			float value = F_PI_2;
			float result = TanApprox<PRECISION>(value);

			RunScalarApproxInfTest<PRECISION>(result);
		}

		SECTION("PI")
		{
			float value = F_PI;
			float result = TanApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("4PI/3")
		{
			float value = F_4PI_3;
			float result = TanApprox<PRECISION>(value);
			float expected = F_SQRT3;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("49PI")
		{
			float value = 49 * F_PI;
			float result = TanApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<FloatPrecision::MEDIUM>(result, expected);
		}

		SECTION("49.5PI")
		{
			float value = 49.5f * F_PI;
			float result = TanApprox<PRECISION>(value);

			RunScalarApproxInfTest<PRECISION>(result);
		}
	}

	SECTION("LOW")
	{
		const FloatPrecision PRECISION = FloatPrecision::LOW;
		const FloatPrecision DROPOFF_PRECISION = FloatPrecision::LOW;

		SECTION("Zero")
		{
			float value = 0.0f;
			float result = TanApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI/4")
		{
			float value = F_PI_4;
			float result = TanApprox<PRECISION>(value);
			float expected = 1.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI/2")
		{
			float value = F_PI_2;
			float result = TanApprox<PRECISION>(value);

			RunScalarApproxInfTest<PRECISION>(result);
		}

		SECTION("PI")
		{
			float value = F_PI;
			float result = TanApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("4PI/3")
		{
			float value = F_4PI_3;
			float result = TanApprox<PRECISION>(value);
			float expected = F_SQRT3;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("49PI")
		{
			float value = 49 * F_PI;
			float result = TanApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("49.5PI")
		{
			float value = 49.5f * F_PI;
			float result = TanApprox<PRECISION>(value);

			RunScalarApproxInfTest<PRECISION>(result);
		}
	}
}

TEST_CASE("CotApprox can approximate the cotangent within varying levels of accuracy, given specific settings")
{
	SECTION("HIGH")
	{
		const FloatPrecision PRECISION = FloatPrecision::HIGH;
		const FloatPrecision DROPOFF_PRECISION = FloatPrecision::MEDIUM_HIGH;

		SECTION("Zero")
		{
			float value = 0.0f;
			float result = CotApprox<PRECISION>(value);

			RunScalarApproxInfTest<PRECISION>(result);
		}

		SECTION("PI/4")
		{
			float value = F_PI_4;
			float result = CotApprox<PRECISION>(value);
			float expected = 1.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI/2")
		{
			float value = F_PI_2;
			float result = CotApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI")
		{
			float value = F_PI;
			float result = CotApprox<PRECISION>(value);

			RunScalarApproxInfTest<PRECISION>(result);
		}

		SECTION("4PI/3")
		{
			float value = F_4PI_3;
			float result = CotApprox<PRECISION>(value);
			float expected = F_1_SQRT3;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("49PI")
		{
			float value = 49 * F_PI;
			float result = CotApprox<PRECISION>(value);

			RunScalarApproxInfTest<DROPOFF_PRECISION>(result);
		}

		SECTION("49.5PI")
		{
			float value = 49.5f * F_PI;
			float result = CotApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<DROPOFF_PRECISION>(result, expected);
		}
	}

	SECTION("MEDIUM_HIGH")
	{
		const FloatPrecision PRECISION = FloatPrecision::MEDIUM_HIGH;
		const FloatPrecision DROPOFF_PRECISION = FloatPrecision::MEDIUM_HIGH;

		SECTION("Zero")
		{
			float value = 0.0f;
			float result = CotApprox<PRECISION>(value);

			RunScalarApproxInfTest<PRECISION>(result);
		}

		SECTION("PI/4")
		{
			float value = F_PI_4;
			float result = CotApprox<PRECISION>(value);
			float expected = 1.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI/2")
		{
			float value = F_PI_2;
			float result = CotApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI")
		{
			float value = F_PI;
			float result = CotApprox<PRECISION>(value);

			RunScalarApproxInfTest<PRECISION>(result);
		}

		SECTION("4PI/3")
		{
			float value = F_4PI_3;
			float result = CotApprox<PRECISION>(value);
			float expected = F_1_SQRT3;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("49PI")
		{
			float value = 49 * F_PI;
			float result = CotApprox<PRECISION>(value);

			RunScalarApproxInfTest<DROPOFF_PRECISION>(result);
		}

		SECTION("49.5PI")
		{
			float value = 49.5f * F_PI;
			float result = CotApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<DROPOFF_PRECISION>(result, expected);
		}
	}

	SECTION("MEDIUM")
	{
		const FloatPrecision PRECISION = FloatPrecision::MEDIUM;
		const FloatPrecision DROPOFF_PRECISION = FloatPrecision::MEDIUM;

		SECTION("Zero")
		{
			float value = 0.0f;
			float result = CotApprox<PRECISION>(value);

			RunScalarApproxInfTest<PRECISION>(result);
		}

		SECTION("PI/4")
		{
			float value = F_PI_4;
			float result = CotApprox<PRECISION>(value);
			float expected = 1.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI/2")
		{
			float value = F_PI_2;
			float result = CotApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI")
		{
			float value = F_PI;
			float result = CotApprox<PRECISION>(value);

			RunScalarApproxInfTest<PRECISION>(result);
		}

		SECTION("4PI/3")
		{
			float value = F_4PI_3;
			float result = CotApprox<PRECISION>(value);
			float expected = F_1_SQRT3;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("49PI")
		{
			float value = 49 * F_PI;
			float result = CotApprox<PRECISION>(value);

			RunScalarApproxInfTest<DROPOFF_PRECISION>(result);
		}

		SECTION("49.5PI")
		{
			float value = 49.5f * F_PI;
			float result = CotApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<DROPOFF_PRECISION>(result, expected);
		}
	}

	SECTION("MEDIUM_LOW")
	{
		const FloatPrecision PRECISION = FloatPrecision::MEDIUM_LOW;
		const FloatPrecision DROPOFF_PRECISION = FloatPrecision::MEDIUM_LOW;

		SECTION("Zero")
		{
			float value = 0.0f;
			float result = CotApprox<PRECISION>(value);

			RunScalarApproxInfTest<PRECISION>(result);
		}

		SECTION("PI/4")
		{
			float value = F_PI_4;
			float result = CotApprox<PRECISION>(value);
			float expected = 1.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI/2")
		{
			float value = F_PI_2;
			float result = CotApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI")
		{
			float value = F_PI;
			float result = CotApprox<PRECISION>(value);

			RunScalarApproxInfTest<PRECISION>(result);
		}

		SECTION("4PI/3")
		{
			float value = F_4PI_3;
			float result = CotApprox<PRECISION>(value);
			float expected = F_1_SQRT3;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("49PI")
		{
			float value = 49 * F_PI;
			float result = CotApprox<PRECISION>(value);

			RunScalarApproxInfTest<DROPOFF_PRECISION>(result);
		}

		SECTION("49.5PI")
		{
			float value = 49.5f * F_PI;
			float result = CotApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<DROPOFF_PRECISION>(result, expected);
		}
	}

	SECTION("LOW")
	{
		const FloatPrecision PRECISION = FloatPrecision::LOW;
		const FloatPrecision DROPOFF_PRECISION = FloatPrecision::LOW;

		SECTION("Zero")
		{
			float value = 0.0f;
			float result = CotApprox<PRECISION>(value);

			RunScalarApproxInfTest<PRECISION>(result);
		}

		SECTION("PI/4")
		{
			float value = F_PI_4;
			float result = CotApprox<PRECISION>(value);
			float expected = 1.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI/2")
		{
			float value = F_PI_2;
			float result = CotApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("PI")
		{
			float value = F_PI;
			float result = CotApprox<PRECISION>(value);

			RunScalarApproxInfTest<PRECISION>(result);
		}

		SECTION("4PI/3")
		{
			float value = F_4PI_3;
			float result = CotApprox<PRECISION>(value);
			float expected = F_1_SQRT3;

			RunScalarTest<PRECISION>(result, expected);
		}

		SECTION("49PI")
		{
			float value = 49 * F_PI;
			float result = CotApprox<PRECISION>(value);

			RunScalarApproxInfTest<DROPOFF_PRECISION>(result);
		}

		SECTION("49.5PI")
		{
			float value = 49.5f * F_PI;
			float result = CotApprox<PRECISION>(value);
			float expected = 0.0f;

			RunScalarTest<DROPOFF_PRECISION>(result, expected);
		}
	}
}

TEST_CASE("ApproxEqual can determine whether or not two floating point numbers are approximately the same, within a given window of accuracy")
{
	SECTION("Returns true")
	{
		SECTION("Exactly Equal")
		{
			float left = 0.0f;
			float right = 0.0f;
			CHECK(ApproxEqual<FloatPrecision::HIGH>(left, right));
		}

		SECTION("Within 0.0000005 (5.0e-07F)")
		{
			float left = 0.0f;
			float right = 5.0e-7f;
			CHECK(ApproxEqual<FloatPrecision::HIGH>(left, right));
		}

		SECTION("Within 0.00001 (1e-5)")
		{
			float left = 0.0f;
			float right = 1.0e-5f;
			CHECK(ApproxEqual<FloatPrecision::MEDIUM_HIGH>(left, right));
		}

		SECTION("Within 0.001 (1e-3)")
		{
			float left = 0.0f;
			float right = 1.0e-3f;
			CHECK(ApproxEqual<FloatPrecision::MEDIUM>(left, right));
		}

		SECTION("Within 0.01 (1e-2)")
		{
			float left = 0.0f;
			float right = 1.0e-2f;
			CHECK(ApproxEqual<FloatPrecision::MEDIUM_LOW>(left, right));
		}

		SECTION("Within 0.1 (1e-1)")
		{
			float left = 0.0f;
			float right = 1.0e-1f;
			CHECK(ApproxEqual<FloatPrecision::LOW>(left, right));
		}
	}
	
	SECTION("Returns false")
	{
		SECTION("Would be exactly equal, but opposite sign")
		{
			float left = 1.0f;
			float right = -1.0f;
			CHECK_FALSE(ApproxEqual<FloatPrecision::HIGH>(left, right));
		}

		SECTION("Within 0.0000005 (5.0e-07F)")
		{
			float left = 0.0f;
			float right = 5.0e-6f;
			CHECK_FALSE(ApproxEqual<FloatPrecision::HIGH>(left, right));
		}

		SECTION("Within 0.00001 (1e-5)")
		{
			float left = 0.0f;
			float right = 1.0e-4f;
			CHECK_FALSE(ApproxEqual<FloatPrecision::MEDIUM_HIGH>(left, right));
		}

		SECTION("Within 0.001 (1e-3)")
		{
			float left = 0.0f;
			float right = 1.0e-2f;
			CHECK_FALSE(ApproxEqual<FloatPrecision::MEDIUM>(left, right));
		}

		SECTION("Within 0.01 (1e-2)")
		{
			float left = 0.0f;
			float right = 1.0e-1f;
			CHECK_FALSE(ApproxEqual<FloatPrecision::MEDIUM_LOW>(left, right));
		}

		SECTION("Within 0.1 (1e-1)")
		{
			float left = 0.0f;
			float right = 1.0f;
			CHECK_FALSE(ApproxEqual<FloatPrecision::LOW>(left, right));
		}
	}
}

TEST_CASE("IsNaN can determine if a float contains the NaN value")
{
	SECTION("Returns true")
	{
		CHECK(IsNaN(NAN));
	}
	SECTION("Returns false")
	{
		SECTION("Zero")
		{
			CHECK_FALSE(IsNaN(0.0f));
		}
		SECTION("Positive")
		{
			CHECK_FALSE(IsNaN(1.0f));
		}
		SECTION("Negative")
		{
			CHECK_FALSE(IsNaN(-1.0f));
		}
	}
}

TEST_CASE("IsInfinity can determine if a float contains the floating-point Infinity() value")
{
	SECTION("Returns true")
	{
		SECTION("Positive Infinity")
		{
			CHECK(IsInfinity(Infinity()));
		}
		SECTION("Negative Infinity")
		{
			CHECK(IsInfinity(-Infinity()));
		}
	}
	SECTION("Returns false")
	{
		SECTION("Zero")
		{
			CHECK_FALSE(IsInfinity(0.0f));
		}
		SECTION("Positive")
		{
			CHECK_FALSE(IsInfinity(1.0f));
		}
		SECTION("Negative")
		{
			CHECK_FALSE(IsInfinity(-1.0f));
		}
	}
}