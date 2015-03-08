#include "matmath_tests.h"
#include "vec_tests.h"

using namespace std;
using namespace gfxmath;

void RunMat44InvalidTest(const Mat44& result)
{
	CHECK(result.matrixTypeVal == MatrixType::INVALID);
}

ostream& operator <<(std::ostream& stream, const Mat44TestContext& mat)
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

istream& operator >>(std::istream& stream, Mat44TestContext& mat)
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

Mat44 MiscMat44Identity()
{
	Mat44 result = Mat44::Identity();
	result.matrixTypeVal = MatrixType::MISC;

	return result;
}

void RunLookDirTestMat44(float eyeX, float eyeY, float eyeZ)
{
	const Vec3 EYE = Vec3(eyeX, eyeY, eyeZ);
	Vec3 direction, up;
	Mat44 result, expected;

	INFO("Facing down the Z-axis");
	direction = Vec3(0.0f, 0.0f, -1.0f);
	up = Vec3(0.0f, 1.0f, 0.0f);

	result = LookDir(EYE, direction, up);

	expected = Mat44(
		Vec4::E0(),
		Vec4::E1(),
		Vec4::E2(),
		Vec4(-eyeX, -eyeY, -eyeZ, 1.0f)
		);

	RunMat44Test(result, expected);

	INFO("Facing down the Y-axis");
	direction = Vec3(0.0f, -1.0f, 0.0f);
	up = Vec3(0.0f, 0.0f, -1.0f);

	result = LookDir(EYE, direction, up);

	expected = Mat44(
		Vec4::E0(),
		Vec4::E2(),
		Vec4::NegE1(),
		Vec4(-eyeX, eyeZ, -eyeY, 1.0f)
		);

	RunMat44Test(result, expected);

	INFO("Facing down the X-axis");
	direction = Vec3(-1.0f, 0.0f, 0.0f);
	up = Vec3(0.0f, 1.0f, 0.0f);

	result = LookDir(EYE, direction, up);

	expected = Mat44(
		Vec4::E2(),
		Vec4::E1(),
		Vec4::NegE0(),
		Vec4(eyeZ, -eyeY, -eyeX, 1.0f)
		);

	RunMat44Test(result, expected);

	INFO("Facing up the Z-axis");
	direction = Vec3(0.0f, 0.0f, 1.0f);;
	up = Vec3(0.0f, 1.0f, 0.0f);

	result = LookDir(EYE, direction, up);

	expected = Mat44(
		Vec4::NegE0(),
		Vec4::E1(),
		Vec4::NegE2(),
		Vec4(eyeX, -eyeY, eyeZ, 1.0f)
		);

	RunMat44Test(result, expected);

	INFO("Facing up the Y-axis");
	direction = Vec3(0.0f, 1.0f, 0.0f);
	up = Vec3(0.0f, 0.0f, 1.0f);

	result = LookDir(EYE, direction, up);

	expected = Mat44(
		Vec4::E0(),
		Vec4::NegE2(),
		Vec4::E1(),
		Vec4(-eyeX, -eyeZ, eyeY, 1.0f)
		);

	RunMat44Test(result, expected);

	INFO("Facing up the X-axis");
	direction = Vec3(1.0f, 0.0f, 0.0f);
	up = Vec3(0.0f, 1.0f, 0.0f);

	result = LookDir(EYE, direction, up);

	expected = Mat44(
		Vec4::NegE2(),
		Vec4::E1(),
		Vec4::E0(),
		Vec4(-eyeZ, -eyeY, eyeX, 1.0f)
		);

	RunMat44Test(result, expected);
}

void RunLookAtTestMat44(float eyeX, float eyeY, float eyeZ)
{
	const Vec3 EYE = Vec3(eyeX, eyeY, eyeZ);
	Vec3 target, up;
	Mat44 result, expected;

	INFO("Facing down the Z-axis");
	target = Vec3(eyeX, eyeY, eyeZ - 1.0f);
	up = Vec3(0.0f, 1.0f, 0.0f);

	result = LookAt(EYE, target, up);

	expected = Mat44(
		Vec4::E0(),
		Vec4::E1(),
		Vec4::E2(),
		Vec4(-eyeX, -eyeY, -eyeZ, 1.0f)
		);

	RunMat44Test(result, expected);

	INFO("Facing down the Y-axis");
	target = Vec3(eyeX, eyeY - 1.0f, eyeZ);
	up = Vec3(0.0f, 0.0f, -1.0f);

	result = LookAt(EYE, target, up);

	expected = Mat44(
		Vec4::E0(),
		Vec4::E2(),
		Vec4::NegE1(),
		Vec4(-eyeX, eyeZ, -eyeY, 1.0f)
		);

	RunMat44Test(result, expected);

	INFO("Facing down the X-axis");
	target = Vec3(eyeX - 1.0f, eyeY, eyeZ);
	up = Vec3(0.0f, 1.0f, 0.0f);

	result = LookAt(EYE, target, up);

	expected = Mat44(
		Vec4::E2(),
		Vec4::E1(),
		Vec4::NegE0(),
		Vec4(eyeZ, -eyeY, -eyeX, 1.0f)
		);

	RunMat44Test(result, expected);

	INFO("Facing up the Z-axis");
	target = Vec3(eyeX, eyeY, eyeZ + 1.0f);
	up = Vec3(0.0f, 1.0f, 0.0f);

	result = LookAt(EYE, target, up);

	expected = Mat44(
		Vec4::NegE0(),
		Vec4::E1(),
		Vec4::NegE2(),
		Vec4(eyeX, -eyeY, eyeZ, 1.0f)
		);

	RunMat44Test(result, expected);

	INFO("Facing up the Y-axis");
	target = Vec3(eyeX, eyeY + 1.0f, eyeZ);
	up = Vec3(0.0f, 0.0f, 1.0f);

	result = LookAt(EYE, target, up);

	expected = Mat44(
		Vec4::E0(),
		Vec4::NegE2(),
		Vec4::E1(),
		Vec4(-eyeX, -eyeZ, eyeY, 1.0f)
		);

	RunMat44Test(result, expected);

	INFO("Facing up the X-axis");
	target = Vec3(eyeX + 1.0f, eyeY, eyeZ);
	up = Vec3(0.0f, 1.0f, 0.0f);

	result = LookAt(EYE, target, up);

	expected = Mat44(
		Vec4::NegE2(),
		Vec4::E1(),
		Vec4::E0(),
		Vec4(-eyeZ, -eyeY, eyeX, 1.0f)
		);

	RunMat44Test(result, expected);
}


TEST_CASE("MatrixMultiply for Mat44 can multiply two 4x4 Mat44 matrices", "[Mat44]")
{
	Mat44 m0 = Mat44(Vec4::E3(), Vec4::E2(), Vec4::E1(), Vec4::E0());// positive involutory matrix
	Mat44 m1 = Mat44::Identity();

	SECTION("Identity Multiplication")
	{
		SECTION("II = I")
		{
			Mat44 result = MatrixMultiply(m1, m1);
			Mat44 expected = Mat44::Identity();

			RunMat44Test(result, expected);
		}

		SECTION("AI = A")
		{
			Mat44 expected = Mat44(Vec4::E3(), Vec4::E2(), Vec4::E1(), Vec4::E0());
			Mat44 result = MatrixMultiply(m0, m1);

			RunMat44Test(result, expected);
		}

		SECTION("IA = A")
		{
			Mat44 expected = Mat44(Vec4::E3(), Vec4::E2(), Vec4::E1(), Vec4::E0());
			Mat44 result = MatrixMultiply(m1, m0);

			RunMat44Test(result, expected);
		}
	}

	SECTION("A(A-Inv) = I")
	{
		Mat44 result = MatrixMultiply(m0, m0);
		Mat44 expected = Mat44::Identity();

		// The system is not designed to "detect" if a specific type of matrix is obtained unless such detection is trivial.
		// e.g. If the matrix is non-invertible, it will be set to -1 to indicate that the resulting matrix inverse is invalid.
		// It performs these simple checks because they are computationally trivial and fast enough to not affect performance.
		expected.matrixTypeVal = MatrixType::MISC;

		RunMat44Test(result, expected);
	}


}

TEST_CASE("MatrixInverse for Mat44 can produce the proper inverse of invertible 4x4 matrices, and an invalid matrix for non-invertible 4x4 matrices.", "[Mat44]")
{
	SECTION("(I-Inv) = I")
	{
		Mat44 id = Mat44::Identity();
		Mat44 result = MatrixInverse(id);

		Mat44 expected = Mat44::Identity();

		RunMat44Test(result, expected);
	}

	SECTION("Translation Matrix")
	{
		SECTION("Right")
		{
			Mat44 right = Mat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4(1.0f, 0.0f, 0.0f, 1.0f));
			Mat44 resRight = MatrixInverse(right);
			Mat44 expectedRight = Mat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4(-1.0f, 0.0f, 0.0f, 1.0f));

			RunMat44Test(resRight, expectedRight);
		}

		SECTION("Up")
		{
			Mat44 up = Mat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4(0.0f, 1.0f, 0.0f, 1.0f));
			Mat44 resUp = MatrixInverse(up);
			Mat44 expectedUp = Mat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4(0.0f, -1.0f, 0.0f, 1.0f));

			RunMat44Test(resUp, expectedUp);
		}

		SECTION("Forward")
		{
			Mat44 forward = Mat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4(0.0f, 0.0f, 1.0f, 1.0f));
			Mat44 resForward = MatrixInverse(forward);
			Mat44 expectedForward = Mat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4(0.0f, 0.0f, -1.0f, 1.0f));

			RunMat44Test(resForward, expectedForward);
		}
	}

	SECTION("Non-invertible matrix")
	{
		Mat44 nonInvertible = Mat44(Vec4::Zero(), Vec4::E1(), Vec4::E2(), Vec4::E3());
		Mat44 result = MatrixInverse(nonInvertible);
		RunMat44InvalidTest(result);
	}
}

TEST_CASE("MatrixTranspose for Mat44 can produce the proper transpose of a matrix", "[Mat44]")
{
	SECTION("I-T = I")
	{
		Mat44 id = Mat44::Identity();
		Mat44 result = MatrixTranspose(id);

		Mat44 expected = Mat44::Identity();
		RunMat44Test(result, expected);
	}

	SECTION("Translation Matrix")
	{
		Mat44 translation;
	}
}

TEST_CASE("MatrixDeterminant for Mat44 can calculate the determinant of a Mat44", "[Mat44][Vec3]")
{
	SECTION("Zero determinant")
	{
		Mat44 m = Mat44();

		float result = MatrixDeterminant(m);
		float expected = 0.0f;

		RunScalarTest(result, expected);
	}

	SECTION("Non-zero determinant")
	{
		SECTION("|I| = 1")
		{
			Mat44 id = Mat44::Identity();

			float result = MatrixDeterminant(id);
			float expected = 1.0f;

			RunScalarTest(result, expected);
		}

		SECTION("Translation Matrix")
		{
			SECTION("Right")
			{
				Mat44 right = Mat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4(1.0f, 0.0f, 0.0f, 1.0f));
				float result = MatrixDeterminant(right);
				float expected = 1.0f;

				RunScalarTest(result, expected);
			}

			SECTION("Up")
			{
				Mat44 up = Mat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4(0.0f, 1.0f, 0.0f, 1.0f));
				float result = MatrixDeterminant(up);
				float expected = 1.0f;

				RunScalarTest(result, expected);
			}

			SECTION("Forward")
			{
				Mat44 forward = Mat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4(0.0f, 0.0f, 1.0f, 1.0f));
				float result = MatrixDeterminant(forward);
				float expected = 1.0f;

				RunScalarTest(result, expected);
			}
		}
	}
}

TEST_CASE("RotationMatrixFromQuaternion for Mat44 can calculate the associated rotation matrix from the given quaternion", "[Mat44][4D][Vec3][Rotation][Affine Transformation Matrix]")
{
	SECTION("Rotation by PI/2 on x-axis")
	{
		Quaternion rotQuat = Quaternion(F_1_SQRT2, 0.0f, 0.0f, F_1_SQRT2);
		Mat44 result = RotationMatrixFromQuaternion(rotQuat);
		Mat44 expected = Mat44(
			Vec4::E0(),
			Vec4(0.0f, 0.0f, 1.0f, 0.0f),
			Vec4(0.0f, -1.0f, 0.0f, 0.0f),
			Vec4::E3()
			);

		RunMat44Test(result, expected);
	}

	SECTION("Rotation by PI/2 on y-axis")
	{
		Quaternion rotQuat = Quaternion(0.0f, F_1_SQRT2, 0.0f, F_1_SQRT2);
		Mat44 result = RotationMatrixFromQuaternion(rotQuat);
		Mat44 expected = Mat44(
			Vec4(0.0f, 0.0f, -1.0f, 0.0f),
			Vec4::E1(),
			Vec4(1.0f, 0.0f, 0.0f, 0.0f),
			Vec4::E3());

		RunMat44Test(result, expected);
	}

	SECTION("Rotation by PI/2 on z-axis")
	{
		Quaternion rotQuat = Quaternion(0.0f, 0.0f, F_1_SQRT2, F_1_SQRT2);
		Mat44 result = RotationMatrixFromQuaternion(rotQuat);
		Mat44 expected = Mat44(
			Vec4(0.0f, 1.0f, 0.0f, 0.0f),
			Vec4(-1.0f, 0.0f, 0.0f, 0.0f),
			Vec4::E2(),
			Vec4::E3());

		RunMat44Test(result, expected);
	}
}

TEST_CASE("RotationMatrixFromEuler for Mat44 can calculate the associated rotation matrix from the given euler angles", "[Mat44][3D][Vec3][Rotation][Affine Transformation Matrix]")
{
	SECTION("Rotation by PI/2 on x-axis")
	{
		Vec3 rotEuler = Vec3(F_PI_2, 0.0f, 0.0f);
		Mat44 result = RotationMatrixFromEuler(rotEuler);
		Mat44 expected = Mat44(
			Vec4::E0(),
			Vec4(0.0f, 0.0f, 1.0f, 0.0f),
			Vec4(0.0f, -1.0f, 0.0f, 0.0f),
			Vec4::E3());

		RunMat44Test(result, expected);
	}

	SECTION("Rotation by PI/2 on y-axis")
	{
		Vec3 rotQuat = Vec3(0.0f, F_PI_2, 0.0f);
		Mat44 result = RotationMatrixFromEuler(rotQuat);
		Mat44 expected = Mat44(
			Vec4(0.0f, 0.0f, -1.0f, 0.0f),
			Vec4::E1(),
			Vec4(1.0f, 0.0f, 0.0f, 0.0f),
			Vec4::E3());

		RunMat44Test(result, expected);
	}

	SECTION("Rotation by PI/2 on z-axis")
	{
		Vec3 rotQuat = Vec3(0.0f, 0.0f, F_PI_2);
		Mat44 result = RotationMatrixFromEuler(rotQuat);
		Mat44 expected = Mat44(
			Vec4(0.0f, 1.0f, 0.0f, 0.0f),
			Vec4(-1.0f, 0.0f, 0.0f, 0.0f),
			Vec4::E2(),
			Vec4::E3());

		RunMat44Test(result, expected);
	}
}

TEST_CASE("TranslationMatrixFromVec3 for Mat44 can produce a translation matrix from a given Vec3 representation of a 3D vector", "[Mat44][3D][Vec3][Translation][Affine Transformation Matrix]")
{
	SECTION("Zero Vector")
	{
		Vec3 vec = Vec3(0.0f, 0.0f, 0.0f);
		Mat44 result = TranslationMatrixFromVec3(vec);
		Mat44 expected = Mat44::Identity();
		expected.matrixTypeVal = MatrixType::MISC;

		RunMat44Test(result, expected);
	}

	SECTION("Direction Vectors")
	{
		SECTION("Right")
		{
			Vec3 vec = Vec3(1.0f, 0.0f, 0.0f);
			Mat44 result = TranslationMatrixFromVec3(vec);
			Mat44 expected = Mat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4(1.0f, 0.0f, 0.0f, 1.0f));

			RunMat44Test(result, expected);
		}

		SECTION("Up")
		{
			Vec3 vec = Vec3(0.0f, 1.0f, 0.0f);
			Mat44 result = TranslationMatrixFromVec3(vec);
			Mat44 expected = Mat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4(0.0f, 1.0f, 0.0f, 1.0f));

			RunMat44Test(result, expected);
		}

		SECTION("Forward")
		{
			Vec3 vec = Vec3(0.0f, 0.0f, 1.0f);
			Mat44 result = TranslationMatrixFromVec3(vec);
			Mat44 expected = Mat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4(0.0f, 0.0f, 1.0f, 1.0f));

			RunMat44Test(result, expected);
		}

		SECTION("Left")
		{
			Vec3 vec = Vec3(-1.0f, 0.0f, 0.0f);
			Mat44 result = TranslationMatrixFromVec3(vec);
			Mat44 expected = Mat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4(-1.0f, 0.0f, 0.0f, 1.0f));

			RunMat44Test(result, expected);
		}

		SECTION("Down")
		{
			Vec3 vec = Vec3(0.0f, -1.0f, 0.0f);
			Mat44 result = TranslationMatrixFromVec3(vec);
			Mat44 expected = Mat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4(0.0f, -1.0f, 0.0f, 1.0f));

			RunMat44Test(result, expected);
		}

		SECTION("Back")
		{
			Vec3 vec = Vec3(0.0f, 0.0f, -1.0f);
			Mat44 result = TranslationMatrixFromVec3(vec);
			Mat44 expected = Mat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4(0.0f, 0.0f, -1.0f, 1.0f));

			RunMat44Test(result, expected);
		}
	}

	SECTION("All +/-1 components")
	{
		SECTION("+1 Components")
		{
			Vec3 vec = Vec3(1.0f, 1.0f, 1.0f);
			Mat44 result = TranslationMatrixFromVec3(vec);
			Mat44 expected = Mat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4::One());

			RunMat44Test(result, expected);
		}

		SECTION("-1 Components")
		{
			Vec3 vec = Vec3(-1.0f, -1.0f, -1.0f);
			Mat44 result = TranslationMatrixFromVec3(vec);
			Mat44 expected = Mat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4(-1.0f, -1.0f, -1.0f, 1.0f));

			RunMat44Test(result, expected);
		}

		SECTION("Mixed +1 and -1 Components")
		{
			SECTION("<-1 +1 +1>")
			{
				Vec3 vec = Vec3(-1.0f, 1.0f, 1.0f);
				Mat44 result = TranslationMatrixFromVec3(vec);
				Mat44 expected = Mat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4(-1.0f, 1.0f, 1.0f, 1.0f));

				RunMat44Test(result, expected);
			}
			SECTION("<+1 -1 +1>")
			{
				Vec3 vec = Vec3(1.0f, -1.0f, 1.0f);
				Mat44 result = TranslationMatrixFromVec3(vec);
				Mat44 expected = Mat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4(1.0f, -1.0f, 1.0f, 1.0f));

				RunMat44Test(result, expected);
			}
			SECTION("<+1 +1 -1>")
			{
				Vec3 vec = Vec3(1.0f, 1.0f, -1.0f);
				Mat44 result = TranslationMatrixFromVec3(vec);
				Mat44 expected = Mat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4(1.0f, 1.0f, -1.0f, 1.0f));

				RunMat44Test(result, expected);
			}


			SECTION("<+1 -1 -1>")
			{
				Vec3 vec = Vec3(1.0f, -1.0f, -1.0f);
				Mat44 result = TranslationMatrixFromVec3(vec);
				Mat44 expected = Mat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4(1.0f, -1.0f, -1.0f, 1.0f));

				RunMat44Test(result, expected);
			}
			SECTION("<-1 +1 -1>")
			{
				Vec3 vec = Vec3(-1.0f, 1.0f, -1.0f);
				Mat44 result = TranslationMatrixFromVec3(vec);
				Mat44 expected = Mat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4(-1.0f, 1.0f, -1.0f, 1.0f));

				RunMat44Test(result, expected);
			}
			SECTION("<-1 -1 +1>")
			{
				Vec3 vec = Vec3(-1.0f, -1.0f, 1.0f);
				Mat44 result = TranslationMatrixFromVec3(vec);
				Mat44 expected = Mat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4(-1.0f, -1.0f, 1.0f, 1.0f));

				RunMat44Test(result, expected);
			}
		}
	}

	SECTION("Arbitrary Components")
	{
		SECTION("Arbitrary Positive")
		{
			Vec3 vec = Vec3(2.0f, 30.0f, 400.0f);
			Mat44 result = TranslationMatrixFromVec3(vec);
			Mat44 expected = Mat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4(2.0f, 30.0f, 400.0f, 1.0f));

			RunMat44Test(result, expected);
		}

		SECTION("Arbitray Negative")
		{
			Vec3 vec = Vec3(-2.0f, -30.0f, -400.0f);
			Mat44 result = TranslationMatrixFromVec3(vec);
			Mat44 expected = Mat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4(-2.0f, -30.0f, -400.0f, 1.0f));

			RunMat44Test(result, expected);
		}
	}
}

TEST_CASE("ScaleMatrixFromVec3 for Mat44 can produce a scale matrix from a given Vec3 representation of a 3D vector", "[Mat44][3D][Vec3][Scale][Affine Transformation Matrix]")
{
	SECTION("Zero Vector")
	{
		Vec3 vec = Vec3(0.0f, 0.0f, 0.0f);
		Mat44 result = ScaleMatrixFromVec3(vec);
		Mat44 expected = Mat44(Vec4::Zero(), Vec4::Zero(), Vec4::Zero(), Vec4::E3());
		expected.matrixTypeVal = MatrixType::MISC;

		RunMat44Test(result, expected);
	}

	SECTION("Direction Vectors")
	{
		SECTION("Right")
		{
			Vec3 vec = Vec3(1.0f, 0.0f, 0.0f);
			Mat44 result = ScaleMatrixFromVec3(vec);
			Mat44 expected = Mat44(Vec4(1.0f, 0.0f, 0.0f, 0.0f), Vec4::Zero(), Vec4::Zero(), Vec4::E3());

			RunMat44Test(result, expected);
		}

		SECTION("Up")
		{
			Vec3 vec = Vec3(0.0f, 1.0f, 0.0f);
			Mat44 result = ScaleMatrixFromVec3(vec);
			Mat44 expected = Mat44(Vec4::Zero(), Vec4(0.0f, 1.0f, 0.0f, 0.0f), Vec4::Zero(), Vec4::E3());

			RunMat44Test(result, expected);
		}

		SECTION("Forward")
		{
			Vec3 vec = Vec3(0.0f, 0.0f, 1.0f);
			Mat44 result = ScaleMatrixFromVec3(vec);
			Mat44 expected = Mat44(Vec4::Zero(), Vec4::Zero(), Vec4(0.0f, 0.0f, 1.0f, 0.0f), Vec4::E3());

			RunMat44Test(result, expected);
		}

		SECTION("Left")
		{
			Vec3 vec = Vec3(-1.0f, 0.0f, 0.0f);
			Mat44 result = ScaleMatrixFromVec3(vec);
			Mat44 expected = Mat44(Vec4(-1.0f, 0.0f, 0.0f, 0.0f), Vec4::Zero(), Vec4::Zero(), Vec4::E3());

			RunMat44Test(result, expected);
		}

		SECTION("Down")
		{
			Vec3 vec = Vec3(0.0f, -1.0f, 0.0f);
			Mat44 result = ScaleMatrixFromVec3(vec);
			Mat44 expected = Mat44(Vec4::Zero(), Vec4(0.0f, -1.0f, 0.0f, 0.0f), Vec4::Zero(), Vec4::E3());

			RunMat44Test(result, expected);
		}

		SECTION("Back")
		{
			Vec3 vec = Vec3(0.0f, 0.0f, -1.0f);
			Mat44 result = ScaleMatrixFromVec3(vec);
			Mat44 expected = Mat44(Vec4::Zero(), Vec4::Zero(), Vec4(0.0f, 0.0f, -1.0f, 0.0f), Vec4::E3());

			RunMat44Test(result, expected);
		}
	}

	SECTION("All +/-1 components")
	{
		SECTION("+1 Components")
		{
			Vec3 vec = Vec3(1.0f, 1.0f, 1.0f);
			Mat44 result = ScaleMatrixFromVec3(vec);
			Mat44 expected = Mat44::Identity();
			expected.matrixTypeVal = MatrixType::MISC;

			RunMat44Test(result, expected);
		}

		SECTION("-1 Components")
		{
			Vec3 vec = Vec3(-1.0f, -1.0f, -1.0f);
			Mat44 result = ScaleMatrixFromVec3(vec);
			Mat44 expected = Mat44(Vec4::NegE0(), Vec4::NegE1(), Vec4::NegE2(), Vec4::E3());

			RunMat44Test(result, expected);
		}

		SECTION("Mixed +1 and -1 Components")
		{
			SECTION("<-1 +1 +1>")
			{
				Vec3 vec = Vec3(-1.0f, 1.0f, 1.0f);
				Mat44 result = ScaleMatrixFromVec3(vec);
				Mat44 expected = Mat44(Vec4::NegE0(), Vec4::E1(), Vec4::E2(), Vec4::E3());

				RunMat44Test(result, expected);
			}
			SECTION("<+1 -1 +1>")
			{
				Vec3 vec = Vec3(1.0f, -1.0f, 1.0f);
				Mat44 result = ScaleMatrixFromVec3(vec);
				Mat44 expected = Mat44(Vec4::E0(), Vec4::NegE1(), Vec4::E2(), Vec4::E3());

				RunMat44Test(result, expected);
			}
			SECTION("<+1 +1 -1>")
			{
				Vec3 vec = Vec3(1.0f, 1.0f, -1.0f);
				Mat44 result = ScaleMatrixFromVec3(vec);
				Mat44 expected = Mat44(Vec4::E0(), Vec4::E1(), Vec4::NegE2(), Vec4::E3());

				RunMat44Test(result, expected);
			}


			SECTION("<+1 -1 -1>")
			{
				Vec3 vec = Vec3(1.0f, -1.0f, -1.0f);
				Mat44 result = ScaleMatrixFromVec3(vec);
				Mat44 expected = Mat44(Vec4::E0(), Vec4::NegE1(), Vec4::NegE2(), Vec4::E3());

				RunMat44Test(result, expected);
			}
			SECTION("<-1 +1 -1>")
			{
				Vec3 vec = Vec3(-1.0f, 1.0f, -1.0f);
				Mat44 result = ScaleMatrixFromVec3(vec);
				Mat44 expected = Mat44(Vec4::NegE0(), Vec4::E1(), Vec4::NegE2(), Vec4::E3());

				RunMat44Test(result, expected);
			}
			SECTION("<-1 -1 +1>")
			{
				Vec3 vec = Vec3(-1.0f, -1.0f, 1.0f);
				Mat44 result = ScaleMatrixFromVec3(vec);
				Mat44 expected = Mat44(Vec4::NegE0(), Vec4::NegE1(), Vec4::E2(), Vec4::E3());

				RunMat44Test(result, expected);
			}
		}
	}

	SECTION("Arbitrary Components")
	{
		SECTION("Arbitrary Positive")
		{
			Vec3 vec = Vec3(2.0f, 30.0f, 400.0f);
			Mat44 result = ScaleMatrixFromVec3(vec);
			Mat44 expected = Mat44(Vec4(2.0f, 0.0f, 0.0f, 0.0f), Vec4(0.0f, 30.0f, 0.0f, 0.0f), Vec4(0.0f, 0.0f, 400.0f, 0.0f), Vec4::E3());

			RunMat44Test(result, expected);
		}

		SECTION("Arbitray Negative")
		{
			Vec3 vec = Vec3(-2.0f, -30.0f, -400.0f);
			Mat44 result = ScaleMatrixFromVec3(vec);
			Mat44 expected = Mat44(Vec4(-2.0f, 0.0f, 0.0f, 0.0f), Vec4(0.0f, -30.0f, 0.0f, 0.0f), Vec4(0.0f, 0.0f, -400.0f, 0.0f), Vec4::E3());

			RunMat44Test(result, expected);
		}
	}
}

TEST_CASE("PerspectiveProjectionMatrix for Mat44 can produce a perspective projection matrix", "[Mat44][Projection Matrix]")
{
	SECTION("PI/2 radian FOV")
	{
		SECTION("0.1 near clip plane")
		{
			SECTION("16:10 Aspect Ratio")
			{
				static const float SIXTEEN_TENTHS = 16.0f / 10.0f;
				Mat44 result = PerspectiveProjectionMatrix(0.1f, 1000.0f, F_PI_2, 1.6f);
				Mat44 expected = Mat44(
					Vec4(1.0f, 0.0f, 0.0f, 0.0f),
					Vec4(0.0f, SIXTEEN_TENTHS, 0.0f, 0.0f),
					Vec4(0.0f, 0.0f, -1.0001f, -1.0f),
					Vec4(0.0f, 0.0f, -0.10001f, 0.0f)
					);

				RunMat44Test(result, expected);
			}

			SECTION("4:3 Aspect Ratio")
			{
				static const float FOUR_THIRDS = 4.0f / 3.0f;
				Mat44 result = PerspectiveProjectionMatrix(0.1f, 1000.0f, F_PI_2, FOUR_THIRDS);
				Mat44 expected = Mat44(
					Vec4(1.0f, 0.0f, 0.0f, 0.0f),
					Vec4(0.0f, FOUR_THIRDS, 0.0f, 0.0f),
					Vec4(0.0f, 0.0f, -1.0001f, -1.0f),
					Vec4(0.0f, 0.0f, -0.10001f, 0.0f)
					);

				RunMat44Test(result, expected);
			}
		}

		SECTION("0.0 near clip plane")
		{
			SECTION("16:10 Aspect Ratio")
			{
				static const float SIXTEEN_TENTHS = 16.0f / 10.0f;
				Mat44 result = PerspectiveProjectionMatrix(0.0f, 1000.0f, F_PI_2, SIXTEEN_TENTHS);
				Mat44 expected = Mat44(
					Vec4(1.0f, 0.0f, 0.0f, 0.0f),
					Vec4(0.0f, SIXTEEN_TENTHS, 0.0f, 0.0f),
					Vec4(0.0f, 0.0f, -1.0f, -1.0f),
					Vec4(0.0f, 0.0f, 0.0f, 0.0f)
					);

				RunMat44Test(result, expected);
			}

			SECTION("4:3 Aspect Ratio")
			{
				static const float FOUR_THIRDS = 4.0f / 3.0f;
				Mat44 result = PerspectiveProjectionMatrix(0.0f, 1000.0f, F_PI_2, FOUR_THIRDS);
				Mat44 expected = Mat44(
					Vec4(1.0f, 0.0f, 0.0f, 0.0f),
					Vec4(0.0f, FOUR_THIRDS, 0.0f, 0.0f),
					Vec4(0.0f, 0.0f, -1.0f, -1.0f),
					Vec4(0.0f, 0.0f, 0.0f, 0.0f)
					);

				RunMat44Test(result, expected);
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
				Mat44 result = PerspectiveProjectionMatrix(0.1f, 1000.0f, F_2PI_3, 1.6f);
				Mat44 expected = Mat44(
					Vec4(COT_2PI_3, 0.0f, 0.0f, 0.0f),
					Vec4(0.0f, SIXTEEN_TENTHS * COT_2PI_3, 0.0f, 0.0f),
					Vec4(0.0f, 0.0f, -1.0001f, -1.0f),
					Vec4(0.0f, 0.0f, -0.10001f, 0.0f)
					);

				RunMat44Test(result, expected);
			}

			SECTION("4:3 Aspect Ratio")
			{
				static const float FOUR_THIRDS = 4.0f / 3.0f;
				Mat44 result = PerspectiveProjectionMatrix(0.1f, 1000.0f, F_2PI_3, FOUR_THIRDS);
				Mat44 expected = Mat44(
					Vec4(COT_2PI_3, 0.0f, 0.0f, 0.0f),
					Vec4(0.0f, FOUR_THIRDS * COT_2PI_3, 0.0f, 0.0f),
					Vec4(0.0f, 0.0f, -1.0001f, -1.0f),
					Vec4(0.0f, 0.0f, -0.10001f, 0.0f)
					);

				RunMat44Test(result, expected);
			}
		}

		SECTION("0.0 near clip plane")
		{
			SECTION("16:10 Aspect Ratio")
			{
				static const float SIXTEEN_TENTHS = 16.0f / 10.0f;

				Mat44 result = PerspectiveProjectionMatrix(0.0f, 1000.0f, F_2PI_3, SIXTEEN_TENTHS);
				Mat44 expected = Mat44(
					Vec4(COT_2PI_3, 0.0f, 0.0f, 0.0f),
					Vec4(0.0f, SIXTEEN_TENTHS * COT_2PI_3, 0.0f, 0.0f),
					Vec4(0.0f, 0.0f, -1.0f, -1.0f),
					Vec4(0.0f, 0.0f, 0.0f, 0.0f)
					);

				RunMat44Test(result, expected);
			}

			SECTION("4:3 Aspect Ratio")
			{
				static const float FOUR_THIRDS = 4.0f / 3.0f;
				Mat44 result = PerspectiveProjectionMatrix(0.0f, 1000.0f, F_2PI_3, FOUR_THIRDS);
				Mat44 expected = Mat44(
					Vec4(COT_2PI_3, 0.0f, 0.0f, 0.0f),
					Vec4(0.0f, FOUR_THIRDS * COT_2PI_3, 0.0f, 0.0f),
					Vec4(0.0f, 0.0f, -1.0f, -1.0f),
					Vec4(0.0f, 0.0f, 0.0f, 0.0f)
					);

				RunMat44Test(result, expected);
			}
		}
	}
}

TEST_CASE("LookDir for Mat44 can produce a View matrix at the given position looking in the given direction", "[Mat44][View Matrix]")
{
	SECTION("At the origin")
	{
		RunLookDirTestMat44(0.0f, 0.0f, 0.0f);
	}

	SECTION("Right of the origin")
	{
		RunLookDirTestMat44(10.0f, 0.0f, 0.0f);
	}

	SECTION("Above the origin")
	{
		RunLookDirTestMat44(0.0f, 10.0f, 0.0f);
	}

	SECTION("In front of the origin")
	{
		RunLookDirTestMat44(0.0f, 0.0f, 10.0f);
	}

	SECTION("Left of the origin")
	{
		RunLookDirTestMat44(-10.0f, 0.0f, 0.0f);
	}

	SECTION("Below the origin")
	{
		RunLookDirTestMat44(0.0f, -10.0f, 0.0f);
	}

	SECTION("Behind of the origin")
	{
		RunLookDirTestMat44(0.0f, 0.0f, -10.0f);
	}


	SECTION("Right up and forward from the origin")
	{
		RunLookDirTestMat44(10.0f, 20.0f, 30.0f);
	}


	SECTION("Right up and back from the origin")
	{
		RunLookDirTestMat44(10.0f, 20.0f, -30.0f);
	}


	SECTION("Right down and forward from the origin")
	{
		RunLookDirTestMat44(10.0f, -20.0f, 30.0f);
	}


	SECTION("Right down and back from the origin")
	{
		RunLookDirTestMat44(10.0f, -20.0f, -30.0f);
	}


	SECTION("Left up and forward from the origin")
	{
		RunLookDirTestMat44(-10.0f, 20.0f, 30.0f);
	}


	SECTION("Left up and back from the origin")
	{
		RunLookDirTestMat44(-10.0f, 20.0f, -30.0f);
	}


	SECTION("Left down and forward from the origin")
	{
		RunLookDirTestMat44(-10.0f, -20.0f, 30.0f);
	}


	SECTION("Left down and back from the origin")
	{
		RunLookDirTestMat44(-10.0f, -20.0f, -30.0f);
	}
}

TEST_CASE("LookAt for Mat44 can produce a View matrix at the given position looking at the given position", "[Mat44][ViewMatrix]")
{
	SECTION("At the origin")
	{
		RunLookAtTestMat44(0.0f, 0.0f, 0.0f);
	}

	SECTION("Right of the origin")
	{
		RunLookAtTestMat44(10.0f, 0.0f, 0.0f);
	}

	SECTION("Above the origin")
	{
		RunLookAtTestMat44(0.0f, 10.0f, 0.0f);
	}

	SECTION("In front of the origin")
	{
		RunLookAtTestMat44(0.0f, 0.0f, 10.0f);
	}

	SECTION("Left of the origin")
	{
		RunLookAtTestMat44(-10.0f, 0.0f, 0.0f);
	}

	SECTION("Below the origin")
	{
		RunLookAtTestMat44(0.0f, -10.0f, 0.0f);
	}

	SECTION("Behind of the origin")
	{
		RunLookAtTestMat44(0.0f, 0.0f, -10.0f);
	}


	SECTION("Right up and forward from the origin")
	{
		RunLookAtTestMat44(10.0f, 20.0f, 30.0f);
	}


	SECTION("Right up and back from the origin")
	{
		RunLookAtTestMat44(10.0f, 20.0f, -30.0f);
	}


	SECTION("Right down and forward from the origin")
	{
		RunLookAtTestMat44(10.0f, -20.0f, 30.0f);
	}


	SECTION("Right down and back from the origin")
	{
		RunLookAtTestMat44(10.0f, -20.0f, -30.0f);
	}


	SECTION("Left up and forward from the origin")
	{
		RunLookAtTestMat44(-10.0f, 20.0f, 30.0f);
	}


	SECTION("Left up and back from the origin")
	{
		RunLookAtTestMat44(-10.0f, 20.0f, -30.0f);
	}


	SECTION("Left down and forward from the origin")
	{
		RunLookAtTestMat44(-10.0f, -20.0f, 30.0f);
	}


	SECTION("Left down and back from the origin")
	{
		RunLookAtTestMat44(-10.0f, -20.0f, -30.0f);
	}
}

TEST_CASE("TransformVec3 for Mat44 can produce a Vec3 representation of a 3D vector that was transformed via a given affine transformation matrix", "[Mat44][3D][Vec3][Affine Transformation Matrix]")
{
	SECTION("Translation")
	{
		// Translate by 1 on the x, y, and z axes
		Mat44 translationMatrix = Mat44(
			Vec4::E0(),
			Vec4::E1(),
			Vec4::E2(),
			Vec4::One()
			);

		Vec3 value = Vec3(0.0f, 0.0f, 0.0f);
		Vec3 result = TransformVec3(translationMatrix, value);

		Vec3 expected = Vec3(1.0f, 1.0f, 1.0f);

		RunVec3Test(result, expected);
	}

	SECTION("Rotation")
	{
		// Rotate by PI/2 on the x-axis
		Mat44 rotationMatrix = Mat44(
			Vec4::E0(),
			Vec4(0.0f, 0.0f, 1.0f, 0.0f),
			Vec4(0.0f, -1.0f, 0.0f, 0.0f),
			Vec4::E3()
			);

		Vec3 value = Vec3(0.0f, 0.0f, 1.0f);
		Vec3 result = TransformVec3(rotationMatrix, value);

		Vec3 expected = Vec3(0.0f, -1.0f, 0.0f);

		RunVec3Test(result, expected);
	}

	SECTION("Scale")
	{
		Mat44 scaleMatrix = Mat44(
			Vec4(4.0f, 0.0f, 0.0f, 0.0f),
			Vec4(0.0f, 3.0f, 0.0f, 0.0f),
			Vec4(0.0f, 0.0f, 2.0f, 0.0f),
			Vec4::E3()
			);

		Vec3 value = Vec3(1.0f, 1.0f, 1.0f);
		Vec3 result = TransformVec3(scaleMatrix, value);

		Vec3 expected = Vec3(4.0f, 3.0f, 2.0f);

		RunVec3Test(result, expected);
	}
}