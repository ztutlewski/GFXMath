#include "vec4.h"
#include "vec2.h"
#include "vec3.h"
#include "quaternion.h"
#include "scalar_math.h"
#include <iomanip>

namespace gfxmath
{
	Vec4 Vec4::E0()
	{
		static const Vec4 e0(1.0f, 0.0f, 0.0f, 0.0f);
		return e0;
	}

	Vec4 Vec4::E1()
	{
		static const Vec4 e1(0.0f, 1.0f, 0.0f, 0.0f);
		return e1;
	}

	Vec4 Vec4::E2()
	{
		static const Vec4 e2(0.0f, 0.0f, 1.0f, 0.0f);
		return e2;
	}

	Vec4 Vec4::E3()
	{
		static const Vec4 e3(0.0f, 0.0f, 0.0f, 1.0f);
		return e3;
	}

	Vec4 Vec4::E(int i)
	{
		static const Vec4 e[4] { E0(), E1(), E2(), E3() };
		return e[i];
	}


	Vec4 Vec4::NegE0()
	{
		static const Vec4 negE0(-1.0f, 0.0f, 0.0f, 0.0f);
		return negE0;
	}

	Vec4 Vec4::NegE1()
	{
		static const Vec4 negE1(0.0f, -1.0f, 0.0f, 0.0f);
		return negE1;
	}

	Vec4 Vec4::NegE2()
	{
		static const Vec4 negE2(0.0f, 0.0f, -1.0f, 0.0f);
		return negE2;
	}

	Vec4 Vec4::NegE3()
	{
		static const Vec4 negE3(0.0f, 0.0f, 0.0f, -1.0f);
		return negE3;
	}

	Vec4 Vec4::NegE(int i)
	{
		static const Vec4 e[4] { E0(), E1(), E2(), E3() };
		return e[i];
	}


	Vec4 Vec4::One()
	{
		static const Vec4 one(1.0f);
		return one;
	}

	Vec4 Vec4::NegOne()
	{
		static const Vec4 negOne(-1.0f);
		return negOne;
	}


	Vec4 Vec4::Zero()
	{
		static const Vec4 zero(0.0f);
		return zero;
	}


	Vec4::Vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
	Vec4::Vec4(float xyzw) : x(xyzw), y(xyzw), z(xyzw), w(xyzw) {}
	Vec4::Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
	Vec4::Vec4(const Vec2& xy, const Vec2& zw) : x(xy.x), y(xy.y), z(zw.x), w(zw.y) {}
	Vec4::Vec4(const Vec2& xy, float z, float w) : x(xy.x), y(xy.y), z(z), w(w) {}
	Vec4::Vec4(float x, const Vec2& yz, float w) : x(x), y(yz.x), z(yz.y), w(w) {}
	Vec4::Vec4(float x, float y, const Vec2& zw) : x(x), y(y), z(zw.x), w(zw.y) {}
	Vec4::Vec4(const Vec3& xyz, float w) : x(xyz.x), y(xyz.y), z(xyz.z), w(w) {}
	Vec4::Vec4(float x, const Vec3& yzw) : x(x), y(yzw.x), z(yzw.y), w(yzw.z) {}

	std::ostream &operator << (std::ostream& stream, const Vec4& vec)
	{
		std::ios::fmtflags fmtSettings(stream.flags());
		stream << std::setw(3) << std::setprecision(5) << vec.x << " " << vec.y << " " << vec.z << " " << vec.w;
		stream.flags(fmtSettings);
		return stream;
	}

	std::istream &operator >> (std::istream& stream, Vec4& vec)
	{
		return stream >> vec.x >> vec.y >> vec.z >> vec.w;
	}

	bool operator==(const Vec4& left, const Vec4& right)
	{
		return ApproxEqual(left.x, right.x) && ApproxEqual(left.y, right.y) && ApproxEqual(left.z, right.z) && ApproxEqual(left.w, right.w);
	}

	bool operator!=(const Vec4& left, const Vec4& right)
	{
		return !(left == right);
	}

    Vec4::operator Vec2() const
    {
        return Vec2(x, y);
    }

    Vec4::operator Vec3() const
    {
        return Vec3(x, y, z);
    }



    Vec4::operator Quaternion() const
    {
        return Quaternion(x, y, z, w);
    }
}
