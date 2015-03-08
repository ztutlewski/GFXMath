#include "matmath.h"
#include "vecmath.h"
#if defined(_MSC_VER)
#include <cmath>
#elif defined(__GNUC__) || defined(__MINGW32__)
#include <cstdlib>
#endif

namespace gofxmath
{
	Mat44 MatrixMultiply(const Mat44& left, const Mat44& right)
	{
		Mat44 result;

		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = 0; j < 4; j++)
			{
				for (size_t k = 0; k < 4; k++)
				{
					result[j].vals[i] += left[j].vals[k] * right[k].vals[i];
				}
			}
		}

		result.matrixTypeVal = static_cast<MatrixType>(left.matrixTypeVal | right.matrixTypeVal);
		return result;
	}

	Mat44 MatrixInverse(const Mat44& mat)
	{
		float subDetsR0[6] =
		{
			mat[2].z * mat[3].w - mat[3].z * mat[2].w, // (22 * 33) - (32 * 23)
			mat[2].y * mat[3].w - mat[3].y * mat[2].w, // (21 * 33) - (31 * 23)
			mat[2].y * mat[3].z - mat[3].y * mat[2].z, // (21 * 32) - (31 * 22)
			mat[2].x * mat[3].w - mat[3].x * mat[2].w, // (20 * 33) - (30 * 23)
			mat[2].x * mat[3].z - mat[3].x * mat[2].z, // (20 * 32) - (30 * 22)
			mat[2].x * mat[3].y - mat[3].x * mat[2].y  // (20 * 31) - (30 * 21)
		};

		Mat44 result;

		result[0].x = ((mat[1].y * subDetsR0[0]) - (mat[1].z * subDetsR0[1]) + (mat[1].w * subDetsR0[2]));
		result[1].x = -((mat[1].x * subDetsR0[0]) - (mat[1].z * subDetsR0[3]) + (mat[1].w * subDetsR0[4]));
		result[2].x = ((mat[1].x * subDetsR0[1]) - (mat[1].y * subDetsR0[3]) + (mat[1].w * subDetsR0[5]));
		result[3].x = -((mat[1].x * subDetsR0[2]) - (mat[1].y * subDetsR0[4]) + (mat[1].z * subDetsR0[5]));

		float det = (mat[0].x * result[0].x + mat[0].y * result[1].x + mat[0].z * result[2].x + mat[0].w * result[3].x);


		if (abs(det) < Epsilon())
		{
			result.matrixTypeVal = MatrixType::INVALID;
			return result;
		}
		else
		{
			result.matrixTypeVal = mat.matrixTypeVal;
		}

		float subDetsRest[12] =
		{
			mat[1].z * mat[3].w - mat[3].z * mat[1].w,// 0 (12 * 33) - (32 * 13)
			mat[1].y * mat[3].w - mat[3].y * mat[1].w,// 1 (11 * 33) - (31 * 13)
			mat[1].y * mat[3].z - mat[3].y * mat[1].z,// 2 (11 * 32) - (31 * 12)
			mat[1].x * mat[3].w - mat[3].x * mat[1].w,// 3 (10 * 33) - (30 * 13)
			mat[1].x * mat[3].z - mat[3].x * mat[1].z,// 4 (10 * 32) - (30 * 12)
			mat[1].x * mat[3].y - mat[3].x * mat[1].y,// 5 (10 * 31) - (30 * 11)

			mat[1].z * mat[2].w - mat[2].z * mat[1].w,// 6  (12 * 23) - (22 * 13)
			mat[1].y * mat[2].w - mat[2].y * mat[1].w,// 7  (11 * 23) - (21 * 13)
			mat[1].y * mat[2].z - mat[2].y * mat[1].z,// 8  (11 * 22) - (21 * 12)
			mat[1].x * mat[2].w - mat[2].x * mat[1].w,// 9  (10 * 23) - (20 * 13)
			mat[1].x * mat[2].z - mat[2].x * mat[1].z,// 10 (10 * 22) - (20 * 12)
			mat[1].x * mat[2].y - mat[2].x * mat[1].y // 11 (10 * 21) - (20 * 11)
		};

		float oneOverDet = 1.0f / det;

		result[0].x *= oneOverDet;
		result[1].x *= oneOverDet;
		result[2].x *= oneOverDet;
		result[3].x *= oneOverDet;

		result[0].y = oneOverDet  * -((mat[0].y * subDetsR0[0]) - (mat[0].z * subDetsR0[1]) + (mat[0].w * subDetsR0[2]));
		result[1].y = oneOverDet  *  ((mat[0].x * subDetsR0[0]) - (mat[0].z * subDetsR0[3]) + (mat[0].w * subDetsR0[4]));
		result[2].y = oneOverDet  * -((mat[0].x * subDetsR0[1]) - (mat[0].y * subDetsR0[3]) + (mat[0].w * subDetsR0[5]));
		result[3].y = oneOverDet  *  ((mat[0].x * subDetsR0[2]) - (mat[0].y * subDetsR0[4]) + (mat[0].z * subDetsR0[5]));

		result[0].z = oneOverDet  *  ((mat[0].y * subDetsRest[0]) - (mat[0].z * subDetsRest[1]) + (mat[0].w * subDetsRest[2]));
		result[1].z = oneOverDet  * -((mat[0].x * subDetsRest[0]) - (mat[0].z * subDetsRest[3]) + (mat[0].w * subDetsRest[4]));
		result[2].z = oneOverDet  *  ((mat[0].x * subDetsRest[1]) - (mat[0].y * subDetsRest[3]) + (mat[0].w * subDetsRest[5]));
		result[3].z = oneOverDet  * -((mat[0].x * subDetsRest[2]) - (mat[0].y * subDetsRest[4]) + (mat[0].z * subDetsRest[5]));

		result[0].w = oneOverDet  * -((mat[0].y * subDetsRest[6]) - (mat[0].z * subDetsRest[7]) + (mat[0].w * subDetsRest[8]));
		result[1].w = oneOverDet  *  ((mat[0].x * subDetsRest[6]) - (mat[0].z * subDetsRest[9]) + (mat[0].w * subDetsRest[10]));
		result[2].w = oneOverDet  * -((mat[0].x * subDetsRest[7]) - (mat[0].y * subDetsRest[9]) + (mat[0].w * subDetsRest[11]));
		result[3].w = oneOverDet  *  ((mat[0].x * subDetsRest[8]) - (mat[0].y * subDetsRest[10]) + (mat[0].z * subDetsRest[11]));

		return result;
	}

	float MatrixDeterminant(const Mat44& mat)
	{
		float subDetsR0[6] =
		{
			mat[2].z * mat[3].w - mat[3].z * mat[2].w,
			mat[2].y * mat[3].w - mat[3].y * mat[2].w,
			mat[2].y * mat[3].z - mat[3].y * mat[2].z,
			mat[2].x * mat[3].w - mat[3].x * mat[2].w,
			mat[2].x * mat[3].z - mat[3].x * mat[2].z,
			mat[2].x * mat[3].y - mat[3].x * mat[2].y
		};

		float res[4] = { ((mat[1].y * subDetsR0[0]) - (mat[1].z * subDetsR0[1]) + (mat[1].w * subDetsR0[2])),
			-((mat[1].x * subDetsR0[0]) - (mat[1].z * subDetsR0[3]) + (mat[1].w * subDetsR0[4])),
			((mat[1].x * subDetsR0[1]) - (mat[1].y * subDetsR0[3]) + (mat[1].w * subDetsR0[5])),
			-((mat[1].x * subDetsR0[2]) - (mat[1].y * subDetsR0[4]) + (mat[1].z * subDetsR0[5])) };

		float result = (mat[0].x * res[0] + mat[0].y * res[1] + mat[0].z * res[2] + mat[0].w * res[3]);


		return result;
	}

	Mat44 MatrixTranspose(const Mat44& mat)
	{
		Mat44 result;

		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = 0; j < 4; j++)
			{
				result[i].vals[j] = mat[j].vals[i];
			}
		}

		result.matrixTypeVal = mat.matrixTypeVal;

		return result;
	}

	Mat44 RotationMatrixFromQuaternion(const Quaternion& quat)
	{
		Vec4 qSqr = Vec4((quat.x * quat.x), (quat.y * quat.y), (quat.z * quat.z), (quat.w * quat.w));
		
		float twoX, twoY, twoZ;
		float xy, xz, xw, yz, yw, zw;

		twoX = 2.0f * quat.x;
		twoY = 2.0f * quat.y;
		twoZ = 2.0f * quat.z;

		xy = twoX * quat.y;
		xz = twoX * quat.z;
		xw = twoX * quat.w;

		yz = twoY * quat.z;
		yw = twoY * quat.w;

		zw = twoZ * quat.w;

		float m00 = qSqr.w + qSqr.x - qSqr.y - qSqr.z;
		float m10 = xy + zw;
		float m20 = xz - yw;

		float m01 = xy - zw;
		float m11 = qSqr.w - qSqr.x + qSqr.y - qSqr.z;
		float m21 = yz + xw;

		float m02 = xz + yw;
		float m12 = yz - xw;
		float m22 = qSqr.w - qSqr.x - qSqr.y + qSqr.z;

		//  (ww + xx - yy - zz)		 2(xy + wz)			 2(xz - wy)				0
		//		2(xy - wz)		 (ww - xx + yy - zz)	 2(yz + wx)				0
		//		2(xz + wy)			 2(yz - wx)		 (ww - xx - yy + zz)		0
		//			 0					  0					  0					1

		return Mat44(
			m00,	m01,	m02,	0.0f,
			m10,	m11,	m12,	0.0f,
			m20,	m21,	m22,	0.0f,
			0.0f,	0.0f,	0.0f,	1.0f);
	}

	Mat44 RotationMatrixFromEuler(const Vec3& angles)
	{
		Mat44 result;

		float cosPitch = FastCosApprox(angles.x);
		float cosYaw = FastCosApprox(angles.y);
		float cosRoll = FastCosApprox(angles.z);

		float sinPitch = FastSinApprox(angles.x);
		float sinYaw = FastSinApprox(angles.y);
		float sinRoll = FastSinApprox(angles.z);

		// heading (rotate about y)
		// attitude (rotate about z)
		// bank (rotate about x)
		//
		// ch*ca	-ch*sa*cb + sh*sb	 ch*sa*sb + sh*cb
		// sa		 ca*cb				-ca*sb
		//-sh*ca	 sh*sa*cb + ch*sb	-sh*sa*sb + ch*cb

		result[0].x =  cosYaw * cosRoll;
		result[0].y =  sinRoll;
		result[0].z = -sinYaw * cosRoll;

		result[1].x = -cosYaw   * sinRoll  * cosPitch  + sinYaw * sinPitch;
		result[1].y =  cosRoll  * cosPitch;
		result[1].z =  sinYaw   * sinRoll  * cosPitch  + cosYaw * sinPitch;

		result[2].x =  cosYaw	  * sinRoll * sinPitch   + sinYaw * cosPitch;
		result[2].y = -cosRoll  * sinPitch;
		result[2].z = -sinYaw   * sinRoll * sinPitch   + cosYaw * cosPitch;

		result[3].w = 1.0f;

		return result;
	}

	Mat44 TranslationMatrixFromVec3(const Vec3& vec)
	{
		Mat44 result(	1.0f, 0.0f, 0.0f, vec.x,
						0.0f, 1.0f, 0.0f, vec.y,
						0.0f, 0.0f, 1.0f, vec.z,
						0.0f, 0.0f, 0.0f, 1.0f);

		return result;
	}

	Mat44 ScaleMatrixFromVec3(const Vec3& vec)
	{
		Mat44 result(vec.x, 0.0f, 0.0f, 0.0f,
					 0.0f, vec.y, 0.0f, 0.0f,
					 0.0f, 0.0f, vec.z, 0.0f,
					 0.0f, 0.0f, 0.0f, 1.0f);

		return result;
	}

	Vec3 TransformVec3(const Mat44& mat, const Vec3& vec)
	{
		Vec3 result;
		result.x = (mat[0].x * vec.x) + (mat[1].x * vec.y) + (mat[2].x * vec.z) + mat[3].x;
		result.y = (mat[0].y * vec.x) + (mat[1].y * vec.y) + (mat[2].y * vec.z) + mat[3].y;
		result.z = (mat[0].z * vec.x) + (mat[1].z * vec.y) + (mat[2].z * vec.z) + mat[3].z;

		return result;
	}

	void PerspectiveProjectionMatrix(float near, float far, float fov, float aspect, Mat44& result)
	{
		// [cotFOV		0.0f			  0.0f		 0.0f]
		// [0.0f		cotFOV * aspect	  0.0f		 0.0f]
		// [0.0f		0.0f			 -f/(f-n)	-1.0f]
		// [0.0f		0.0f			 -fn/(f-n)	 0.0f]

		result[0].x = CotApprox(fov * 0.5f);
		result[1].y = result[0].x * aspect;

		result[2].z = -far / (far - near);
		result[2].w = result[2].z * near;
		
		result[3].z = -1.0f;
	}

	Mat44 LookAt(const Vec3& eye, const Vec3& target, const Vec3& up)
	{
		Vec3 dir = Vec3Sub(target, eye);
		return LookDir(eye, dir, up);
	}

	Mat44 LookDir(const Vec3& eye, const Vec3& dir, const Vec3& up)
	{
		Vec3 fwdAxis, rightAxis, upAxis;
		fwdAxis = Vec3Normalize(dir);

		rightAxis = Vec3Normalize(Vec3Cross(fwdAxis, up));

		upAxis = Vec3Cross(rightAxis, fwdAxis);

		Vec3 backAxis = Vec3Negate(fwdAxis);
		Vec3 negativeEye = Vec3Negate(eye);

		float rightDotNegEye	= Vec3Dot(rightAxis, negativeEye);
		float upDotNegEye		= Vec3Dot(upAxis,	 negativeEye);
		float backwardDotNegEye = Vec3Dot(backAxis,  negativeEye);

		//  rx  ry  rz -rDPe
		//  ux	uy  uz -uDPe
		// -dx -dy -dz  dDPe
		//  0   0   0   1

		Mat44 result;
		result[0] = Vec4(rightAxis.x, upAxis.x, backAxis.x, 0.0f);
		result[1] = Vec4(rightAxis.y, upAxis.y, backAxis.y, 0.0f);
		result[2] = Vec4(rightAxis.z, upAxis.z, backAxis.z, 0.0f);
		result[3] = Vec4(rightDotNegEye, upDotNegEye, backwardDotNegEye, 1.0f);

		return result;
	}
}