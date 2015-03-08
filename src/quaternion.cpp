#include "quaternion.h"
#include "vec4.h"

namespace gfxmath
{
	Quaternion Quaternion::Identity()
	{
		static const Quaternion identity(0.0f, 0.0f, 0.0f, 1.0f);
		return identity;
	}

	Quaternion::Quaternion() : Vec4() {}
	Quaternion::Quaternion(float x, float y, float z, float w) : Vec4(x, y, z, w) {}
	Quaternion::Quaternion(const Vec2& xy, const Vec2& zw) : Vec4(xy, zw){}
	Quaternion::Quaternion(const Vec2& xy, float z, float w) : Vec4(xy, z, w){}
	Quaternion::Quaternion(float x, const Vec2& yz, float w) : Vec4(x, yz, w){}
	Quaternion::Quaternion(float x, float y, const Vec2& zw) : Vec4(x, y, zw){}
	Quaternion::Quaternion(float x, const Vec3& yzw) : Vec4(x, yzw){}
	Quaternion::Quaternion(const Vec3& xyz, float w) : Vec4(xyz, w){}
	Quaternion::Quaternion(float xyzw) : Vec4(xyzw){}
}