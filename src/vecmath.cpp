#include "vecmath.h"
#include <cmath>
#include "scalar_math.h"

namespace gfxmath
{
	Vec2 Vec2Add(const Vec2& first, const Vec2& second)
	{
		Vec2 result;
		result.x = first.x + second.x;
		result.y = first.y + second.y;

		return result;
	}

	Vec3 Vec3Add(const Vec3& first, const Vec3& second)
	{
		Vec3 result;
		result.x = first.x + second.x;
		result.y = first.y + second.y;
		result.z = first.z + second.z;

		return result;
	}

	Vec4 Vec4Add(const Vec4& first, const Vec4& second)
	{
		Vec4 result;
		result.x = first.x + second.x;
		result.y = first.y + second.y;
		result.z = first.z + second.z;
		result.w = first.w + second.w;

		return result;
	}



	Vec2 Vec2Sub(const Vec2& first, const Vec2& second)
	{
		Vec2 result;
		result.x = first.x - second.x;
		result.y = first.y - second.y;

		return result;
	}

	Vec3 Vec3Sub(const Vec3& first, const Vec3& second)
	{
		Vec3 result;
		result.x = first.x - second.x;
		result.y = first.y - second.y;
		result.z = first.z - second.z;

		return result;
	}

	Vec4 Vec4Sub(const Vec4& first, const Vec4& second)
	{
		Vec4 result;
		result.x = first.x - second.x;
		result.y = first.y - second.y;
		result.z = first.z - second.z;
		result.w = first.w - second.w;

		return result;
	}



	Vec2 Vec2MulScalar(const Vec2& vec, float factor)
	{
		Vec2 result;
		result.x = vec.x * factor;
		result.y = vec.y * factor;

		return result;
	}

	Vec3 Vec3MulScalar(const Vec3& vec, float factor)
	{
		Vec3 result;
		result.x = vec.x * factor;
		result.y = vec.y * factor;
		result.z = vec.z * factor;

		return result;
	}

	Vec4 Vec4MulScalar(const Vec4& vec, float factor)
	{
		Vec4 result;
		result.x = vec.x * factor;
		result.y = vec.y * factor;
		result.z = vec.z * factor;
		result.w = vec.w * factor;

		return result;
	}



	Vec2 Vec2DivScalar(const Vec2& vec, float divisor)
	{
		Vec2 result;
		result.x = vec.x / divisor;
		result.y = vec.y / divisor;

		return result;
	}

	Vec3 Vec3DivScalar(const Vec3& vec, float divisor)
	{
		Vec3 result;
		result.x = vec.x / divisor;
		result.y = vec.y / divisor;
		result.z = vec.z / divisor;

		return result;
	}

	Vec4 Vec4DivScalar(const Vec4& vec, float divisor)
	{
		Vec4 result;
		result.x = vec.x / divisor;
		result.y = vec.y / divisor;
		result.z = vec.z / divisor;
		result.w = vec.w / divisor;

		return result;
	}



	Vec2 Vec2Normalize(const Vec2& vec)
	{
		float mag = sqrt((vec.x * vec.x) + (vec.y * vec.y));

		Vec2 result;
		result.x = vec.x / mag;
		result.y = vec.y / mag;

		return result;
	}

	Vec3 Vec3Normalize(const Vec3& vec)
	{
		float oneOverMag = 1.0f / sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
		Vec3 result;
		result.x = vec.x * oneOverMag;
		result.y = vec.y * oneOverMag;
		result.z = vec.z * oneOverMag;

		return result;
	}

	Vec4 Vec4Normalize(const Vec4& vec)
	{
		float mag = sqrt(vec.w * vec.w + vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);

		Vec4 result;
		result.x = vec.x / mag;
		result.y = vec.y / mag;
		result.z = vec.z / mag;
		result.w = vec.w / mag;

		return result;
	}

	Quaternion QuaternionNormalize(const Quaternion& quat)
	{
		float sqrMag = Vec4Dot(quat, quat);
		float mag = sqrt(sqrMag);

		Quaternion result;
		result.x = quat.x / mag;
		result.y = quat.y / mag;
		result.z = quat.z / mag;
		result.w = quat.w / mag;

		return result;
	}


	Vec2 Vec2Negate(const Vec2& vec)
	{
		return Vec2(-vec.x, -vec.y);
	}

	Vec3 Vec3Negate(const Vec3& vec)
	{
		return Vec3(-vec.x, -vec.y, -vec.z);
	}

	Vec4 Vec4Negate(const Vec4& vec)
	{
		return Vec4(-vec.x, -vec.y, -vec.z, -vec.w);
	}


	bool Vec2HasNaN(const Vec2& vec)
	{
		return IsNaN(vec.x) || IsNaN(vec.y);
	}

	bool Vec3HasNaN(const Vec3& vec)
	{
		return IsNaN(vec.x) || IsNaN(vec.y) || IsNaN(vec.z);
	}

	bool Vec4HasNaN(const Vec4& vec)
	{
		return IsNaN(vec.x) || IsNaN(vec.y) || IsNaN(vec.z) || IsNaN(vec.w);
	}
 

	bool Vec2HasInfinite(const Vec2& vec)
	{
		return IsInfinity(vec.x) || IsInfinity(vec.y);
	}

	bool Vec3HasInfinite(const Vec3& vec)
	{
		return IsInfinity(vec.x) || IsInfinity(vec.y) || IsInfinity(vec.z);
	}

	bool Vec4HasInfinite(const Vec4& vec)
	{
		return IsInfinity(vec.x) || IsInfinity(vec.y) || IsInfinity(vec.z) || IsInfinity(vec.w);
	}



	float Vec2Dot(const Vec2& first, const Vec2& second)
	{
		float result = first.x * second.x + first.y * second.y;

		return result;
	}

	float Vec3Dot(const Vec3& first, const Vec3& second)
	{
		float result = (first.x * second.x) + (first.y * second.y) + (first.z * second.z);

		return result;
	}

	float Vec4Dot(const Vec4& first, const Vec4& second)
	{
		float result = (first.x * second.x) + (first.y * second.y) + (first.z * second.z) + (first.w * second.w);

		return result;
	}



	Vec3 Vec3Cross(const Vec3& first, const Vec3& second)
	{
		// k  i  j  k  i  j
		// z0 x0 y0 z0 x0 y0
		// z1 x1 y1 z1 x1 y1
		// 
		// i * y0 * z1 - i * z0 * y1
		// j * z0 * x1 - j * x0 * z1
		// k * x0 * y1 - k * y0 * x1

		Vec3 result;
		result.x = first.y * second.z - first.z * second.y;
		result.y = first.z * second.x - first.x * second.z;
		result.z = first.x * second.y - first.y * second.x;

		return result;
	}

	Quaternion QuaternionMultiply(const Quaternion& q0, const Quaternion& q1)
	{
		Quaternion result;
		result.x = q0.w*q1.x + q0.x*q1.w + q0.y*q1.z - q0.z*q1.y;
		result.y = q0.w*q1.y + q0.y*q1.w + q0.x*q1.z - q0.z*q1.x;
		result.z = q0.w*q1.z + q0.z*q1.w + q0.x*q1.y - q0.y*q1.x;
		result.w = q0.w*q1.w - q0.x*q1.x - q0.y*q1.y - q0.z*q1.z;

		return result;
	}



	Quaternion QuaternionLerp(const Quaternion& qStart, const Quaternion& qEnd, float t)
	{
		float dot = Vec4Dot(qStart, qEnd);
		float tStart = 1.0f - t;
		float tEnd = dot < 0.0f ? -t : t;

		Quaternion result;
		result.x = tStart*qStart.x + tEnd*qEnd.x;
		result.y = tStart*qStart.y + tEnd*qEnd.y;
		result.z = tStart*qStart.z + tEnd*qEnd.z;
		result.w = tStart*qStart.w + tEnd*qEnd.w;

		result = QuaternionNormalize(result);

		return result;
	}


	Quaternion QuaternionFromAxisAngle(const Vec3& axisVec, float angle)
	{
		float halfAngle = angle * 0.5f;
		float cosAngle = CosApprox(halfAngle);
		float sinAngle = SinApprox(halfAngle);

		Quaternion result(
			axisVec.x * sinAngle,
			axisVec.y * sinAngle,
			axisVec.z * sinAngle,
			cosAngle
			);

		return result;
	}


	Quaternion QuaternionFromEuler(const Vec3& angles)
	{
		float halfX = angles.x * 0.5f;
		float halfY = angles.y * 0.5f;
		float halfZ = angles.z * 0.5f;

		float cx = CosApprox(halfX);
		float cy = CosApprox(halfY);
		float cz = CosApprox(halfZ);

		float sx = SinApprox(halfX);
		float sy = SinApprox(halfY);
		float sz = SinApprox(halfZ);

		float szsy = sz * sy;
		float szcy = sz * cy;
		float czsy = cz * sy;
		float czcy = cz * cy;
		
		Quaternion result(
			(czcy * sx) - (szsy * cx),
			(czsy * cx) + (szcy * sx),
			(szcy * cx) - (czsy * sx),
			(czcy * cx) + (szsy * sx)
			);

		return result;
	}
}