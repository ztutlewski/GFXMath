#include "ssemat_tests.h"


using namespace std;
using namespace gofxmath;

void RunSseMat44InvalidTest(const SseMat44& result)
{
	CHECK(result.matrixTypeVal == MatrixType::INVALID);
}

ostream& operator <<(std::ostream& stream, const SseMat44TestContext& mat)
{
	stream << std::fixed << setprecision(5) << std::setfill(' ');

	for (size_t i = 0; i < 4; i++)
	{
		stream << "[";
		for (size_t j = 0; j < 4; j++)
		{
			stream << std::setw(9) << mat.m[i][j] << " ";
		}
		stream << "]" << endl;
	}

	return stream;
}

istream& operator >>(std::istream& stream, SseMat44TestContext& mat)
{
	for (size_t i = 0; i < 4; i++)
	{
		stream.ignore(1);
		for (size_t j = 0; j < 4; j++)
		{
			stream >> mat.m[i][j];
		}
		stream.ignore(1);
	}

	return stream;
}

SseMat44 MiscSseMat44Identity()
{
	SseMat44 result = SseMat44::IDENTITY;
	result.matrixTypeVal = MatrixType::MISC;

	return result;
}

void RunLookDirTest(float eyeX, float eyeY, float eyeZ)
{
	const SseVec EYE = SetSseVec3_Debug(eyeX, eyeY, eyeZ);
	SseVec direction, up;
	SseMat44 result, expected;

	INFO("Facing down the Z-axis");
	direction = SetSseVec3_Debug(0.0f, 0.0f, -1.0f);
	up = SetSseVec3_Debug(0.0f, 1.0f, 0.0f);

	result = LookDir(EYE, direction, up);

	expected = SseMat44(
		Vec4::E0(),
		Vec4::E1(),
		Vec4::E2(),
		Vec4(-eyeX, -eyeY, -eyeZ, 1.0f)
		);

	RunSseMat44Test(result, expected);

	INFO("Facing down the Y-axis");
	direction = SetSseVec3_Debug(0.0f, -1.0f, 0.0f);
	up = SetSseVec3_Debug(0.0f, 0.0f, -1.0f);

	result = LookDir(EYE, direction, up);

	expected = SseMat44(
		Vec4::E0(),
		Vec4::E2(),
		Vec4::NegE1(),
		Vec4(-eyeX, eyeZ, -eyeY, 1.0f)
		);

	RunSseMat44Test(result, expected);

	INFO("Facing down the X-axis");
	direction = SetSseVec3_Debug(-1.0f, 0.0f, 0.0f);
	up = SetSseVec3_Debug(0.0f, 1.0f, 0.0f);

	result = LookDir(EYE, direction, up);

	expected = SseMat44(
		Vec4::E2(),
		Vec4::E1(),
		Vec4::NegE0(),
		Vec4(eyeZ, -eyeY, -eyeX, 1.0f)
		);

	RunSseMat44Test(result, expected);

	INFO("Facing up the Z-axis");
	direction = SetSseVec3_Debug(0.0f, 0.0f, 1.0f);;
	up = SetSseVec3_Debug(0.0f, 1.0f, 0.0f);

	result = LookDir(EYE, direction, up);

	expected = SseMat44(
		Vec4::NegE0(),
		Vec4::E1(),
		Vec4::NegE2(),
		Vec4(eyeX, -eyeY, eyeZ, 1.0f)
		);

	RunSseMat44Test(result, expected);

	INFO("Facing up the Y-axis");
	direction = SetSseVec3_Debug(0.0f, 1.0f, 0.0f);
	up = SetSseVec3_Debug(0.0f, 0.0f, 1.0f);

	result = LookDir(EYE, direction, up);

	expected = SseMat44(
		Vec4::E0(),
		Vec4::NegE2(),
		Vec4::E1(),
		Vec4(-eyeX, -eyeZ, eyeY, 1.0f)
		);

	RunSseMat44Test(result, expected);

	INFO("Facing up the X-axis");
	direction = SetSseVec3_Debug(1.0f, 0.0f, 0.0f);
	up = SetSseVec3_Debug(0.0f, 1.0f, 0.0f);

	result = LookDir(EYE, direction, up);

	expected = SseMat44(
		Vec4::NegE2(),
		Vec4::E1(),
		Vec4::E0(),
		Vec4(-eyeZ, -eyeY, eyeX, 1.0f)
		);

	RunSseMat44Test(result, expected);
}

void RunLookAtTest(float eyeX, float eyeY, float eyeZ)
{
	const SseVec EYE = SetSseVec3_Debug(eyeX, eyeY, eyeZ);
	SseVec target, up;
	SseMat44 result, expected;

	INFO("Facing down the Z-axis");
	target = SetSseVec3_Debug(eyeX, eyeY, eyeZ - 1.0f);
	up = SetSseVec3_Debug(0.0f, 1.0f, 0.0f);

	result = LookAt(EYE, target, up);

	expected = SseMat44(
		Vec4::E0(),
		Vec4::E1(),
		Vec4::E2(),
		Vec4(-eyeX, -eyeY, -eyeZ, 1.0f)
		);

	RunSseMat44Test(result, expected);

	INFO("Facing down the Y-axis");
	target = SetSseVec3_Debug(eyeX, eyeY - 1.0f, eyeZ);
	up = SetSseVec3_Debug(0.0f, 0.0f, -1.0f);

	result = LookAt(EYE, target, up);

	expected = SseMat44(
		Vec4::E0(),
		Vec4::E2(),
		Vec4::NegE1(),
		Vec4(-eyeX, eyeZ, -eyeY, 1.0f)
		);

	RunSseMat44Test(result, expected);

	INFO("Facing down the X-axis");
	target = SetSseVec3_Debug(eyeX - 1.0f, eyeY, eyeZ);
	up = SetSseVec3_Debug(0.0f, 1.0f, 0.0f);

	result = LookAt(EYE, target, up);

	expected = SseMat44(
		Vec4::E2(),
		Vec4::E1(),
		Vec4::NegE0(),
		Vec4(eyeZ, -eyeY, -eyeX, 1.0f)
		);

	RunSseMat44Test(result, expected);

	INFO("Facing up the Z-axis");
	target = SetSseVec3_Debug(eyeX, eyeY, eyeZ + 1.0f);
	up = SetSseVec3_Debug(0.0f, 1.0f, 0.0f);

	result = LookAt(EYE, target, up);

	expected = SseMat44(
		Vec4::NegE0(),
		Vec4::E1(),
		Vec4::NegE2(),
		Vec4(eyeX, -eyeY, eyeZ, 1.0f)
		);

	RunSseMat44Test(result, expected);

	INFO("Facing up the Y-axis");
	target = SetSseVec3_Debug(eyeX, eyeY + 1.0f, eyeZ);
	up = SetSseVec3_Debug(0.0f, 0.0f, 1.0f);

	result = LookAt(EYE, target, up);

	expected = SseMat44(
		Vec4::E0(),
		Vec4::NegE2(),
		Vec4::E1(),
		Vec4(-eyeX, -eyeZ, eyeY, 1.0f)
		);

	RunSseMat44Test(result, expected);

	INFO("Facing up the X-axis");
	target = SetSseVec3_Debug(eyeX + 1.0f, eyeY, eyeZ);
	up = SetSseVec3_Debug(0.0f, 1.0f, 0.0f);

	result = LookAt(EYE, target, up);

	expected = SseMat44(
		Vec4::NegE2(),
		Vec4::E1(),
		Vec4::E0(),
		Vec4(-eyeZ, -eyeY, eyeX, 1.0f)
		);

	RunSseMat44Test(result, expected);
}


TEST_CASE("MatrixMultiply for SseMat44 can multiply two 4x4 SseMat44 matrices","[SseMat44]")
{
	SseMat44 m0 = SseMat44(Vec4::E3(), Vec4::E2(), Vec4::E1(), Vec4::E0());// positive involutory matrix
	SseMat44 m1 = SseMat44::IDENTITY;

	SECTION("Identity Multiplication")
	{
		SECTION("II = I")
		{
			SseMat44 result = MatrixMultiply(m1, m1);
			SseMat44 expected = SseMat44::IDENTITY;

			RunSseMat44Test(result, expected);
		}

		SECTION("AI = A")
		{
			SseMat44 expected = SseMat44(Vec4::E3(), Vec4::E2(), Vec4::E1(), Vec4::E0());
			SseMat44 result = MatrixMultiply(m0, m1);

			RunSseMat44Test(result, expected);
		}

		SECTION("IA = A")
		{
			SseMat44 expected = SseMat44(Vec4::E3(), Vec4::E2(), Vec4::E1(), Vec4::E0());
			SseMat44 result = MatrixMultiply(m1, m0);

			RunSseMat44Test(result, expected);
		}
	}

	SECTION("A(A-Inv) = I")
	{
		SseMat44 result = MatrixMultiply(m0, m0);
		SseMat44 expected = SseMat44::IDENTITY;

		// The system is not designed to "detect" if a specific type of matrix is obtained unless such detection is trivial.
		// e.g. If the matrix is non-invertible, it will be set to -1 to indicate that the resulting matrix inverse is invalid.
		// It performs these simple checks because they are computationally trivial and fast enough to not affect performance.
		expected.matrixTypeVal = MatrixType::MISC;

		RunSseMat44Test(result, expected);
	}


}

TEST_CASE("MatrixInverse for SseMat44 can produce the proper inverse of invertible 4x4 matrices, and an invalid matrix for non-invertible 4x4 matrices.","[SseMat44]")
{
	SECTION("(I-Inv) = I")
	{
		SseMat44 id = SseMat44::IDENTITY;
		SseMat44 result = MatrixInverse(id);

		SseMat44 expected = SseMat44::IDENTITY;

		RunSseMat44Test(result, expected);
	}

	SECTION("Translation Matrix")
	{
		SECTION("Right")
		{
			SseMat44 right = SseMat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4(1.0f, 0.0f, 0.0f, 1.0f));
			SseMat44 resRight = MatrixInverse(right);
			SseMat44 expectedRight = SseMat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4(-1.0f, 0.0f, 0.0f, 1.0f));

			RunSseMat44Test(resRight, expectedRight);
		}

		SECTION("Up")
		{
			SseMat44 up = SseMat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4(0.0f, 1.0f, 0.0f, 1.0f));
			SseMat44 resUp = MatrixInverse(up);
			SseMat44 expectedUp = SseMat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4(0.0f, -1.0f, 0.0f, 1.0f));

			RunSseMat44Test(resUp, expectedUp);
		}

		SECTION("Forward")
		{
			SseMat44 forward = SseMat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4(0.0f, 0.0f, 1.0f, 1.0f));
			SseMat44 resForward = MatrixInverse(forward);
			SseMat44 expectedForward = SseMat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4(0.0f, 0.0f, -1.0f, 1.0f));

			RunSseMat44Test(resForward, expectedForward);
		}
	}

	SECTION("Non-invertible matrix")
	{
		SseMat44 nonInvertible = SseMat44(Vec4::Zero(), Vec4::E1(), Vec4::E2(), Vec4::E3());
		SseMat44 result = MatrixInverse(nonInvertible);
		RunSseMat44InvalidTest(result);
	}
}

TEST_CASE("MatrixTranspose for SseMat44 can produce the proper transpose of a matrix", "[SseMat44]")
{
	SECTION("I-T = I")
	{
		SseMat44 id = SseMat44::IDENTITY;
		SseMat44 result = MatrixTranspose(id);

		SseMat44 expected = SseMat44::IDENTITY;
		RunSseMat44Test(result, expected);
	}

	SECTION("Translation Matrix")
	{
		SseMat44 translation;
	}
}

TEST_CASE("MatrixDeterminant for SseMat44 can calculate the determinant of a SseMat44", "[SseMat44][SseVec]")
{
	SECTION("Zero determinant")
	{
		SseMat44 m = SseMat44();

		SseVec result = MatrixDeterminant(m);
		Vec4 expected = Vec4::Zero();

		CheckSseVec4(result, expected);
	}

	SECTION("Non-zero determinant")
	{
		SECTION("|I| = 1")
		{
			SseMat44 id = SseMat44::IDENTITY;

			SseVec result = MatrixDeterminant(id);
			Vec4 expected = Vec4::One();

			CheckSseVec4(result, expected);
		}
		
		SECTION("Translation Matrix")
		{
			SECTION("Right")
			{
				SseMat44 right = SseMat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4(1.0f, 0.0f, 0.0f, 1.0f));
				SseVec resRight = MatrixDeterminant(right);
				Vec4 expectedRight = Vec4::One();

				CheckSseVec4(resRight, expectedRight);
			}

			SECTION("Up")
			{
				SseMat44 up = SseMat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4(0.0f, 1.0f, 0.0f, 1.0f));
				SseVec resUp = MatrixDeterminant(up);
				Vec4 expectedRight = Vec4::One();

				CheckSseVec4(resUp, expectedRight);
			}

			SECTION("Forward")
			{
				SseMat44 forward = SseMat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4(0.0f, 0.0f, 1.0f, 1.0f));
				SseVec resForward = MatrixDeterminant(forward);
				Vec4 expectedForward = Vec4::One();

				CheckSseVec4(resForward, expectedForward);
			}
		}
	}
}

TEST_CASE("RotationMatrixFromQuaternion can calculate the associated rotation matrix from the given quaternion", "[SseMat44][4D][SseVec][Rotation][Affine Transformation Matrix]")
{
	SECTION("Rotation by PI/2 on x-axis")
	{
		SseVec rotQuat = SetSseVec4(F_1_SQRT2, 0.0f, 0.0f, F_1_SQRT2);
		SseMat44 result = RotationMatrixFromQuaternion(rotQuat);
		SseMat44 expected = SseMat44(
			Vec4::E0(),
			Vec4(0.0f, 0.0f, 1.0f, 0.0f),
			Vec4(0.0f, -1.0f, 0.0f, 0.0f),
			Vec4::E3()
			);

		RunSseMat44Test(result, expected);
	}

	SECTION("Rotation by PI/2 on y-axis")
	{
		SseVec rotQuat = SetSseVec4(0.0f, F_1_SQRT2, 0.0f, F_1_SQRT2);
		SseMat44 result = RotationMatrixFromQuaternion(rotQuat);
		SseMat44 expected = SseMat44(
			Vec4(0.0f, 0.0f, -1.0f, 0.0f),
			Vec4::E1(),
			Vec4(1.0f, 0.0f, 0.0f, 0.0f),
			Vec4::E3());

		RunSseMat44Test(result, expected);
	}

	SECTION("Rotation by PI/2 on z-axis")
	{
		SseVec rotQuat = SetSseVec4(0.0f, 0.0f, F_1_SQRT2, F_1_SQRT2);
		SseMat44 result = RotationMatrixFromQuaternion(rotQuat);
		SseMat44 expected = SseMat44(
			Vec4(0.0f, 1.0f, 0.0f, 0.0f),
			Vec4(-1.0f, 0.0f, 0.0f, 0.0f),
			Vec4::E2(),
			Vec4::E3());

		RunSseMat44Test(result, expected);
	}
}

TEST_CASE("RotationMatrixFromEuler can calculate the associated rotation matrix from the given euler angles", "[SseMat44][3D][SseVec][Rotation][Affine Transformation Matrix]")
{
	SECTION("Rotation by PI/2 on x-axis")
	{
		SseVec rotEuler = SetSseVec3(F_PI_2, 0.0f, 0.0f);
		SseMat44 result = RotationMatrixFromEuler(rotEuler);
		SseMat44 expected = SseMat44(
			Vec4::E0(),
			Vec4(0.0f, 0.0f, 1.0f, 0.0f),
			Vec4(0.0f, -1.0f, 0.0f, 0.0f),
			Vec4::E3());

		RunSseMat44Test(result, expected);
	}

	SECTION("Rotation by PI/2 on y-axis")
	{
		SseVec rotQuat = SetSseVec3(0.0f, F_PI_2, 0.0f);
		SseMat44 result = RotationMatrixFromEuler(rotQuat);
		SseMat44 expected = SseMat44(
			Vec4(0.0f, 0.0f, -1.0f, 0.0f),
			Vec4::E1(),
			Vec4(1.0f, 0.0f, 0.0f, 0.0f),
			Vec4::E3());

		RunSseMat44Test(result, expected);
	}

	SECTION("Rotation by PI/2 on z-axis")
	{
		SseVec rotQuat = SetSseVec3(0.0f, 0.0f, F_PI_2);
		SseMat44 result = RotationMatrixFromEuler(rotQuat);
		SseMat44 expected = SseMat44(
			Vec4(0.0f, 1.0f, 0.0f, 0.0f),
			Vec4(-1.0f, 0.0f, 0.0f, 0.0f),
			Vec4::E2(),
			Vec4::E3());

		RunSseMat44Test(result, expected);
	}
}

TEST_CASE("TranslationMatrixFromVec3 can produce a translation matrix from a given SseVec representation of a 3D vector", "[SseMat44][3D][SseVec][Translation][Affine Transformation Matrix]")
{
	SECTION("Zero Vector")
	{
		SseVec vec = SetSseVec3_Debug(0.0f, 0.0f, 0.0f);
		SseMat44 result = TranslationMatrixFromVec3(vec);
		SseMat44 expected = SseMat44::IDENTITY;
		expected.matrixTypeVal = MatrixType::MISC;

		RunSseMat44Test(result, expected);
	}

	SECTION("Direction Vectors")
	{
		SECTION("Right")
		{
			SseVec vec = SetSseVec3_Debug(1.0f, 0.0f, 0.0f);
			SseMat44 result = TranslationMatrixFromVec3(vec);
			SseMat44 expected = SseMat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4(1.0f, 0.0f, 0.0f, 1.0f));

			RunSseMat44Test(result, expected);
		}

		SECTION("Up")
		{
			SseVec vec = SetSseVec3_Debug(0.0f, 1.0f, 0.0f);
			SseMat44 result = TranslationMatrixFromVec3(vec);
			SseMat44 expected = SseMat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4(0.0f, 1.0f, 0.0f, 1.0f));

			RunSseMat44Test(result, expected);
		}

		SECTION("Forward")
		{
			SseVec vec = SetSseVec3_Debug(0.0f, 0.0f, 1.0f);
			SseMat44 result = TranslationMatrixFromVec3(vec);
			SseMat44 expected = SseMat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4(0.0f, 0.0f, 1.0f, 1.0f));

			RunSseMat44Test(result, expected);
		}

		SECTION("Left")
		{
			SseVec vec = SetSseVec3_Debug(-1.0f, 0.0f, 0.0f);
			SseMat44 result = TranslationMatrixFromVec3(vec);
			SseMat44 expected = SseMat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4(-1.0f, 0.0f, 0.0f, 1.0f));

			RunSseMat44Test(result, expected);
		}

		SECTION("Down")
		{
			SseVec vec = SetSseVec3_Debug(0.0f, -1.0f, 0.0f);
			SseMat44 result = TranslationMatrixFromVec3(vec);
			SseMat44 expected = SseMat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4(0.0f, -1.0f, 0.0f, 1.0f));

			RunSseMat44Test(result, expected);
		}

		SECTION("Back")
		{
			SseVec vec = SetSseVec3_Debug(0.0f, 0.0f, -1.0f);
			SseMat44 result = TranslationMatrixFromVec3(vec);
			SseMat44 expected = SseMat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4(0.0f, 0.0f, -1.0f, 1.0f));

			RunSseMat44Test(result, expected);
		}
	}

	SECTION("All +/-1 components")
	{
		SECTION("+1 Components")
		{
			SseVec vec = SetSseVec3_Debug(1.0f, 1.0f, 1.0f);
			SseMat44 result = TranslationMatrixFromVec3(vec);
			SseMat44 expected = SseMat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4::One());

			RunSseMat44Test(result, expected);
		}

		SECTION("-1 Components")
		{
			SseVec vec = SetSseVec3_Debug(-1.0f, -1.0f, -1.0f);
			SseMat44 result = TranslationMatrixFromVec3(vec);
			SseMat44 expected = SseMat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4(-1.0f, -1.0f, -1.0f, 1.0f));

			RunSseMat44Test(result, expected);
		}

		SECTION("Mixed +1 and -1 Components")
		{
			SECTION("<-1 +1 +1>")
			{
				SseVec vec = SetSseVec3_Debug(-1.0f,  1.0f,  1.0f);
				SseMat44 result = TranslationMatrixFromVec3(vec);
				SseMat44 expected = SseMat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4(-1.0f,  1.0f,  1.0f,  1.0f));

				RunSseMat44Test(result, expected);
			}
			SECTION("<+1 -1 +1>")
			{
				SseVec vec = SetSseVec3_Debug( 1.0f, -1.0f,  1.0f);
				SseMat44 result = TranslationMatrixFromVec3(vec);
				SseMat44 expected = SseMat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4( 1.0f, -1.0f,  1.0f,  1.0f));

				RunSseMat44Test(result, expected);
			}
			SECTION("<+1 +1 -1>")
			{
				SseVec vec = SetSseVec3_Debug( 1.0f,  1.0f, -1.0f);
				SseMat44 result = TranslationMatrixFromVec3(vec);
				SseMat44 expected = SseMat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4( 1.0f,  1.0f, -1.0f,  1.0f));

				RunSseMat44Test(result, expected);
			}


			SECTION("<+1 -1 -1>")
			{
				SseVec vec = SetSseVec3_Debug( 1.0f, -1.0f, -1.0f);
				SseMat44 result = TranslationMatrixFromVec3(vec);
				SseMat44 expected = SseMat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4( 1.0f, -1.0f, -1.0f,  1.0f));

				RunSseMat44Test(result, expected);
			}
			SECTION("<-1 +1 -1>")
			{
				SseVec vec = SetSseVec3_Debug(-1.0f,  1.0f, -1.0f);
				SseMat44 result = TranslationMatrixFromVec3(vec);
				SseMat44 expected = SseMat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4(-1.0f,  1.0f, -1.0f,  1.0f));

				RunSseMat44Test(result, expected);
			}
			SECTION("<-1 -1 +1>")
			{
				SseVec vec = SetSseVec3_Debug(-1.0f, -1.0f, 1.0f);
				SseMat44 result = TranslationMatrixFromVec3(vec);
				SseMat44 expected = SseMat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4(-1.0f, -1.0f,  1.0f,  1.0f));

				RunSseMat44Test(result, expected);
			}
		}
	}

	SECTION("Arbitrary Components")
	{
		SECTION("Arbitrary Positive")
		{
			SseVec vec = SetSseVec3_Debug(2.0f, 30.0f, 400.0f);
			SseMat44 result = TranslationMatrixFromVec3(vec);
			SseMat44 expected = SseMat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4(2.0f, 30.0f, 400.0f, 1.0f));

			RunSseMat44Test(result, expected);
		}

		SECTION("Arbitray Negative")
		{
			SseVec vec = SetSseVec3_Debug(-2.0f, -30.0f, -400.0f);
			SseMat44 result = TranslationMatrixFromVec3(vec);
			SseMat44 expected = SseMat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4(-2.0f, -30.0f, -400.0f, 1.0f));

			RunSseMat44Test(result, expected);
		}
	}
}

TEST_CASE("ScaleMatrixFromVec3 can produce a scale matrix from a given SseVec representation of a 3D vector", "[SseMat44][3D][SseVec][Scale][Affine Transformation Matrix]")
{
	SECTION("Zero Vector")
	{
		SseVec vec = SetSseVec3_Debug(0.0f, 0.0f, 0.0f);
		SseMat44 result = ScaleMatrixFromVec3(vec);
		SseMat44 expected = SseMat44(Vec4::Zero(), Vec4::Zero(), Vec4::Zero(), Vec4::E3());
		expected.matrixTypeVal = MatrixType::MISC;

		RunSseMat44Test(result, expected);
	}

	SECTION("Direction Vectors")
	{
		SECTION("Right")
		{
			SseVec vec = SetSseVec3_Debug(1.0f, 0.0f, 0.0f);
			SseMat44 result = ScaleMatrixFromVec3(vec);
			SseMat44 expected = SseMat44(Vec4(1.0f, 0.0f, 0.0f, 0.0f), Vec4::Zero(), Vec4::Zero(), Vec4::E3());

			RunSseMat44Test(result, expected);
		}

		SECTION("Up")
		{
			SseVec vec = SetSseVec3_Debug(0.0f, 1.0f, 0.0f);
			SseMat44 result = ScaleMatrixFromVec3(vec);
			SseMat44 expected = SseMat44(Vec4::Zero(), Vec4(0.0f, 1.0f, 0.0f, 0.0f), Vec4::Zero(), Vec4::E3());

			RunSseMat44Test(result, expected);
		}

		SECTION("Forward")
		{
			SseVec vec = SetSseVec3_Debug(0.0f, 0.0f, 1.0f);
			SseMat44 result = ScaleMatrixFromVec3(vec);
			SseMat44 expected = SseMat44(Vec4::Zero(), Vec4::Zero(), Vec4(0.0f, 0.0f, 1.0f, 0.0f), Vec4::E3());

			RunSseMat44Test(result, expected);
		}

		SECTION("Left")
		{
			SseVec vec = SetSseVec3_Debug(-1.0f, 0.0f, 0.0f);
			SseMat44 result = ScaleMatrixFromVec3(vec);
			SseMat44 expected = SseMat44(Vec4(-1.0f, 0.0f, 0.0f, 0.0f), Vec4::Zero(), Vec4::Zero(), Vec4::E3());

			RunSseMat44Test(result, expected);
		}

		SECTION("Down")
		{
			SseVec vec = SetSseVec3_Debug(0.0f, -1.0f, 0.0f);
			SseMat44 result = ScaleMatrixFromVec3(vec);
			SseMat44 expected = SseMat44(Vec4::Zero(), Vec4(0.0f, -1.0f, 0.0f, 0.0f), Vec4::Zero(), Vec4::E3());

			RunSseMat44Test(result, expected);
		}

		SECTION("Back")
		{
			SseVec vec = SetSseVec3_Debug(0.0f, 0.0f, -1.0f);
			SseMat44 result = ScaleMatrixFromVec3(vec);
			SseMat44 expected = SseMat44(Vec4::Zero(), Vec4::Zero(), Vec4(0.0f, 0.0f, -1.0f, 0.0f), Vec4::E3());

			RunSseMat44Test(result, expected);
		}
	}

	SECTION("All +/-1 components")
	{
		SECTION("+1 Components")
		{
			SseVec vec = SetSseVec3_Debug(1.0f, 1.0f, 1.0f);
			SseMat44 result = ScaleMatrixFromVec3(vec);
			SseMat44 expected = SseMat44::IDENTITY;
			expected.matrixTypeVal = MatrixType::MISC;

			RunSseMat44Test(result, expected);
		}

		SECTION("-1 Components")
		{
			SseVec vec = SetSseVec3_Debug(-1.0f, -1.0f, -1.0f);
			SseMat44 result = ScaleMatrixFromVec3(vec);
			SseMat44 expected = SseMat44(Vec4::NegE0(), Vec4::NegE1(), Vec4::NegE2(), Vec4::E3());

			RunSseMat44Test(result, expected);
		}

		SECTION("Mixed +1 and -1 Components")
		{
			SECTION("<-1 +1 +1>")
			{
				SseVec vec = SetSseVec3_Debug(-1.0f, 1.0f, 1.0f);
				SseMat44 result = ScaleMatrixFromVec3(vec);
				SseMat44 expected = SseMat44(Vec4::NegE0(), Vec4::E1(), Vec4::E2(), Vec4::E3());

				RunSseMat44Test(result, expected);
			}
			SECTION("<+1 -1 +1>")
			{
				SseVec vec = SetSseVec3_Debug(1.0f, -1.0f, 1.0f);
				SseMat44 result = ScaleMatrixFromVec3(vec);
				SseMat44 expected = SseMat44(Vec4::E0(), Vec4::NegE1(), Vec4::E2(), Vec4::E3());

				RunSseMat44Test(result, expected);
			}
			SECTION("<+1 +1 -1>")
			{
				SseVec vec = SetSseVec3_Debug(1.0f, 1.0f, -1.0f);
				SseMat44 result = ScaleMatrixFromVec3(vec);
				SseMat44 expected = SseMat44(Vec4::E0(), Vec4::E1(), Vec4::NegE2(), Vec4::E3());

				RunSseMat44Test(result, expected);
			}


			SECTION("<+1 -1 -1>")
			{
				SseVec vec = SetSseVec3_Debug(1.0f, -1.0f, -1.0f);
				SseMat44 result = ScaleMatrixFromVec3(vec);
				SseMat44 expected = SseMat44(Vec4::E0(), Vec4::NegE1(), Vec4::NegE2(), Vec4::E3());

				RunSseMat44Test(result, expected);
			}
			SECTION("<-1 +1 -1>")
			{
				SseVec vec = SetSseVec3_Debug(-1.0f, 1.0f, -1.0f);
				SseMat44 result = ScaleMatrixFromVec3(vec);
				SseMat44 expected = SseMat44(Vec4::NegE0(), Vec4::E1(), Vec4::NegE2(), Vec4::E3());

				RunSseMat44Test(result, expected);
			}
			SECTION("<-1 -1 +1>")
			{
				SseVec vec = SetSseVec3_Debug(-1.0f, -1.0f, 1.0f);
				SseMat44 result = ScaleMatrixFromVec3(vec);
				SseMat44 expected = SseMat44(Vec4::NegE0(), Vec4::NegE1(), Vec4::E2(), Vec4::E3());

				RunSseMat44Test(result, expected);
			}
		}
	}

	SECTION("Arbitrary Components")
	{
		SECTION("Arbitrary Positive")
		{
			SseVec vec = SetSseVec3_Debug(2.0f, 30.0f, 400.0f);
			SseMat44 result = ScaleMatrixFromVec3(vec);
			SseMat44 expected = SseMat44(Vec4(2.0f, 0.0f, 0.0f, 0.0f), Vec4(0.0f, 30.0f, 0.0f, 0.0f), Vec4(0.0f, 0.0f, 400.0f, 0.0f), Vec4::E3());

			RunSseMat44Test(result, expected);
		}

		SECTION("Arbitray Negative")
		{
			SseVec vec = SetSseVec3_Debug(-2.0f, -30.0f, -400.0f);
			SseMat44 result = ScaleMatrixFromVec3(vec);
			SseMat44 expected = SseMat44(Vec4(-2.0f, 0.0f, 0.0f, 0.0f), Vec4(0.0f, -30.0f, 0.0f, 0.0f), Vec4(0.0f, 0.0f, -400.0f, 0.0f), Vec4::E3());

			RunSseMat44Test(result, expected);
		}
	}
}

TEST_CASE("PerspectiveProjectionMatrix can produce a perspective projection matrix", "[SseMat44][Projection Matrix]")
{
	SECTION("PI/2 radian FOV")
	{
		SECTION("0.1 near clip plane")
		{
			SECTION("16:10 Aspect Ratio")
			{
				static const float SIXTEEN_TENTHS = 16.0f / 10.0f;
				SseMat44 result = PerspectiveProjectionMatrix(0.1f, 1000.0f, F_PI_2, 1.6f);
				SseMat44 expected = SseMat44(
					Vec4(1.0f, 0.0f, 0.0f, 0.0f),
					Vec4(0.0f, SIXTEEN_TENTHS, 0.0f, 0.0f),
					Vec4(0.0f, 0.0f, -1.0001f, -1.0f),
					Vec4(0.0f, 0.0f, -0.10001f, 0.0f)
					);

				RunSseMat44Test(result, expected);
			}

			SECTION("4:3 Aspect Ratio")
			{
				static const float FOUR_THIRDS = 4.0f / 3.0f;
				SseMat44 result = PerspectiveProjectionMatrix(0.1f, 1000.0f, F_PI_2, FOUR_THIRDS);
				SseMat44 expected = SseMat44(
					Vec4(1.0f, 0.0f, 0.0f, 0.0f),
					Vec4(0.0f, FOUR_THIRDS, 0.0f, 0.0f),
					Vec4(0.0f, 0.0f, -1.0001f, -1.0f),
					Vec4(0.0f, 0.0f, -0.10001f, 0.0f)
					);

				RunSseMat44Test(result, expected);
			}
		}

		SECTION("0.0 near clip plane")
		{
			SECTION("16:10 Aspect Ratio")
			{
				static const float SIXTEEN_TENTHS = 16.0f / 10.0f;
				SseMat44 result = PerspectiveProjectionMatrix(0.0f, 1000.0f, F_PI_2, SIXTEEN_TENTHS);
				SseMat44 expected = SseMat44(
					Vec4(1.0f, 0.0f, 0.0f, 0.0f),
					Vec4(0.0f, SIXTEEN_TENTHS, 0.0f, 0.0f),
					Vec4(0.0f, 0.0f, -1.0f, -1.0f),
					Vec4(0.0f, 0.0f, 0.0f, 0.0f)
					);

				RunSseMat44Test(result, expected);
			}

			SECTION("4:3 Aspect Ratio")
			{
				static const float FOUR_THIRDS = 4.0f / 3.0f;
				SseMat44 result = PerspectiveProjectionMatrix(0.0f, 1000.0f, F_PI_2, FOUR_THIRDS);
				SseMat44 expected = SseMat44(
					Vec4(1.0f, 0.0f, 0.0f, 0.0f),
					Vec4(0.0f, FOUR_THIRDS, 0.0f, 0.0f),
					Vec4(0.0f, 0.0f, -1.0f, -1.0f),
					Vec4(0.0f, 0.0f, 0.0f, 0.0f)
					);

				RunSseMat44Test(result, expected);
			}
		}
	}

	SECTION("2PI/3 radian FOV")
	{
		static const float COT_2PI_3 = cosf(F_2PI_3 * 0.5f) / sinf(F_2PI_3 * 0.5f);

		SECTION("0.1 near clip plane")
		{
			SECTION("16:10 Aspect Ratio")
			{
				static const float SIXTEEN_TENTHS = 16.0f / 10.0f;
				SseMat44 result = PerspectiveProjectionMatrix(0.1f, 1000.0f, F_2PI_3, 1.6f);
				SseMat44 expected = SseMat44(
					Vec4(COT_2PI_3, 0.0f,						 0.0f,		 0.0f),
					Vec4(0.0f,		SIXTEEN_TENTHS * COT_2PI_3,  0.0f,		 0.0f),
					Vec4(0.0f,		0.0f,						-1.0001f,	-1.0f),
					Vec4(0.0f,		0.0f,						-0.10001f,	 0.0f)
					);

				RunSseMat44Test(result, expected);
			}

			SECTION("4:3 Aspect Ratio")
			{
				static const float FOUR_THIRDS = 4.0f / 3.0f;
				SseMat44 result = PerspectiveProjectionMatrix(0.1f, 1000.0f, F_2PI_3, FOUR_THIRDS);
				SseMat44 expected = SseMat44(
					Vec4(COT_2PI_3, 0.0f,						 0.0f,		 0.0f),
					Vec4(0.0f,		FOUR_THIRDS * COT_2PI_3,	 0.0f,		 0.0f),
					Vec4(0.0f,		0.0f,						-1.0001f,	-1.0f),
					Vec4(0.0f,		0.0f,						-0.10001f,	 0.0f)
					);

				RunSseMat44Test(result, expected);
			}
		}

		SECTION("0.0 near clip plane")
		{
			SECTION("16:10 Aspect Ratio")
			{
				static const float SIXTEEN_TENTHS = 16.0f / 10.0f;
				
				SseMat44 result = PerspectiveProjectionMatrix(0.0f, 1000.0f, F_2PI_3, SIXTEEN_TENTHS);
				SseMat44 expected = SseMat44(
					Vec4(COT_2PI_3,	0.0f,						 0.0f,  0.0f),
					Vec4(0.0f,		SIXTEEN_TENTHS * COT_2PI_3,	 0.0f,  0.0f),
					Vec4(0.0f,		0.0f,						-1.0f, -1.0f),
					Vec4(0.0f,		0.0f,						 0.0f,  0.0f)
					);

				RunSseMat44Test(result, expected);
			}

			SECTION("4:3 Aspect Ratio")
			{
				static const float FOUR_THIRDS = 4.0f / 3.0f;
				SseMat44 result = PerspectiveProjectionMatrix(0.0f, 1000.0f, F_2PI_3, FOUR_THIRDS);
				SseMat44 expected = SseMat44(
					Vec4(COT_2PI_3, 0.0f,						 0.0f,  0.0f),
					Vec4(0.0f,		FOUR_THIRDS * COT_2PI_3,	 0.0f,  0.0f),
					Vec4(0.0f,		0.0f,						-1.0f, -1.0f),
					Vec4(0.0f,		0.0f,						 0.0f,  0.0f)
					);

				RunSseMat44Test(result, expected);
			}
		}
	}
}

TEST_CASE("LookDir can produce a View matrix at the given position looking in the given direction","[SseMat44][View Matrix]")
{
	SECTION("At the origin")
	{
		RunLookDirTest(0.0f, 0.0f, 0.0f);
	}

	SECTION("Right of the origin")
	{
		RunLookDirTest(10.0f, 0.0f, 0.0f);
	}

	SECTION("Above the origin")
	{
		RunLookDirTest(0.0f, 10.0f, 0.0f);
	}

	SECTION("In front of the origin")
	{
		RunLookDirTest(0.0f, 0.0f, 10.0f);
	}

	SECTION("Left of the origin")
	{
		RunLookDirTest(-10.0f, 0.0f, 0.0f);
	}

	SECTION("Below the origin")
	{
		RunLookDirTest(0.0f, -10.0f, 0.0f);
	}

	SECTION("Behind of the origin")
	{
		RunLookDirTest(0.0f, 0.0f, -10.0f);
	}


	SECTION("Right up and forward from the origin")
	{
		RunLookDirTest(10.0f, 20.0f, 30.0f);
	}


	SECTION("Right up and back from the origin")
	{
		RunLookDirTest(10.0f, 20.0f, -30.0f);
	}


	SECTION("Right down and forward from the origin")
	{
		RunLookDirTest(10.0f, -20.0f, 30.0f);
	}


	SECTION("Right down and back from the origin")
	{
		RunLookDirTest(10.0f, -20.0f, -30.0f);
	}


	SECTION("Left up and forward from the origin")
	{
		RunLookDirTest(-10.0f, 20.0f, 30.0f);
	}


	SECTION("Left up and back from the origin")
	{
		RunLookDirTest(-10.0f, 20.0f, -30.0f);
	}


	SECTION("Left down and forward from the origin")
	{
		RunLookDirTest(-10.0f, -20.0f, 30.0f);
	}


	SECTION("Left down and back from the origin")
	{
		RunLookDirTest(-10.0f, -20.0f, -30.0f);
	}
}

TEST_CASE("LookAt can produce a View matrix at the given position looking at the given position","[SseMat44][ViewMatrix]")
{
	SECTION("At the origin")
	{
		RunLookAtTest(0.0f, 0.0f, 0.0f);
	}

	SECTION("Right of the origin")
	{
		RunLookAtTest(10.0f, 0.0f, 0.0f);
	}

	SECTION("Above the origin")
	{
		RunLookAtTest(0.0f, 10.0f, 0.0f);
	}

	SECTION("In front of the origin")
	{
		RunLookAtTest(0.0f, 0.0f, 10.0f);
	}

	SECTION("Left of the origin")
	{
		RunLookAtTest(-10.0f, 0.0f, 0.0f);
	}

	SECTION("Below the origin")
	{
		RunLookAtTest(0.0f, -10.0f, 0.0f);
	}

	SECTION("Behind of the origin")
	{
		RunLookAtTest(0.0f, 0.0f, -10.0f);
	}


	SECTION("Right up and forward from the origin")
	{
		RunLookAtTest(10.0f, 20.0f, 30.0f);
	}


	SECTION("Right up and back from the origin")
	{
		RunLookAtTest(10.0f, 20.0f, -30.0f);
	}


	SECTION("Right down and forward from the origin")
	{
		RunLookAtTest(10.0f, -20.0f, 30.0f);
	}


	SECTION("Right down and back from the origin")
	{
		RunLookAtTest(10.0f, -20.0f, -30.0f);
	}


	SECTION("Left up and forward from the origin")
	{
		RunLookAtTest(-10.0f, 20.0f, 30.0f);
	}


	SECTION("Left up and back from the origin")
	{
		RunLookAtTest(-10.0f, 20.0f, -30.0f);
	}


	SECTION("Left down and forward from the origin")
	{
		RunLookAtTest(-10.0f, -20.0f, 30.0f);
	}


	SECTION("Left down and back from the origin")
	{
		RunLookAtTest(-10.0f, -20.0f, -30.0f);
	}
}

TEST_CASE("TransformVec3 can produce a SseVec representation of a 3D vector that was transformed via a given affine transformation matrix", "[SseMat44][3D][SseVec][Affine Transformation Matrix]")
{
	SECTION("Translation")
	{
		// Translate by 1 on the x, y, and z axes
		SseMat44 translationMatrix = SseMat44(
			Vec4::E0(),
			Vec4::E1(),
			Vec4::E2(),
			Vec4::One()
			);

		SseVec value = SetSseVec3_Debug(0.0f, 0.0f, 0.0f);
		SseVec result = TransformVec3(translationMatrix, value);

		SseVec expected = SetSseVec3_Debug(1.0f, 1.0f, 1.0f);

		CheckSseVec(result, expected);
	}

	SECTION("Rotation")
	{
		// Rotate by PI/2 on the x-axis
		SseMat44 rotationMatrix = SseMat44(
			Vec4::E0(),
			Vec4(0.0f, 0.0f, 1.0f, 0.0f),
			Vec4(0.0f, -1.0f, 0.0f, 0.0f),
			Vec4::E3()
			);

		SseVec value = SetSseVec3_Debug(0.0f, 0.0f, 1.0f);
		SseVec result = TransformVec3(rotationMatrix, value);

		SseVec expected = SetSseVec3_Debug(0.0f, -1.0f, 0.0f);

		CheckSseVec(result, expected);
	}

	SECTION("Scale")
	{
		SseMat44 scaleMatrix = SseMat44(
			Vec4(4.0f, 0.0f, 0.0f, 0.0f),
			Vec4(0.0f, 3.0f, 0.0f, 0.0f),
			Vec4(0.0f, 0.0f, 2.0f, 0.0f),
			Vec4::E3()
			);

		SseVec value = SetSseVec3_Debug(1.0f, 1.0f, 1.0f);
		SseVec result = TransformVec3(scaleMatrix, value);

		SseVec expected = SetSseVec3_Debug(4.0f, 3.0f, 2.0f);

		CheckSseVec(result, expected);
	}
}