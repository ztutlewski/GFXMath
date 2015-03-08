#include "vec3.h"
#include "scalar_math.h"
#include "vec2.h"
#include "vec4.h"
#include <iomanip>

namespace gofxmath
{
	Vec3 Vec3::Right()
	{ 
		static const Vec3 right(1.0f, 0.0f, 0.0f);
		return right;
	};

	Vec3 Vec3::Up()
	{
		static const Vec3 up(0.0f, 1.0f, 0.0f);
		return up;
	}

	Vec3 Vec3::Forward()
	{ 
		static const Vec3 forward(0.0f, 0.0f, 1.0f);
		return forward;
	}

	Vec3 Vec3::Left()
	{ 
		static const Vec3 left(-1.0f, 0.0f, 0.0f);
		return left;
	}

	Vec3 Vec3::Down()
	{ 
		static const Vec3 down(0.0f, -1.0f, 0.0f);
		return down;
	}

	Vec3 Vec3::Back()
	{ 
		static const Vec3 back(0.0f, 0.0f, -1.0f);
		return back;
	}

	Vec3 Vec3::One()
	{
		static const Vec3 one(1.0f);
		return one;
	}

	Vec3 Vec3::NegOne()
	{
		static const Vec3 negOne(-1.0f);
		return negOne;
	}

	Vec3 Vec3::Zero()
	{
		static const Vec3 zero(0.0f);
		return zero;
	}

	Vec3::Vec3() : x(0.0f), y(0.0f), z(0.0f) {}
	Vec3::Vec3(float xyz) : x(xyz), y(xyz), z(xyz) {}
	Vec3::Vec3(const Vec2& xy, float z) : x(xy.x), y(xy.y), z(z){}
	Vec3::Vec3(float x, const Vec2& yz) : x(x), y(yz.x), z(yz.y){}
	Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

	std::ostream &operator << (std::ostream& stream, const Vec3& vec)
	{
		std::ios::fmtflags fmtSettings(stream.flags());
		stream << std::setw(3) << std::setprecision(5) << vec.x << " " << vec.y << " " << vec.z;
		stream.flags(fmtSettings);
		return stream;
	}

	std::istream &operator >> (std::istream& stream, Vec3& vec)
	{
		return stream >> vec.x >> vec.y >> vec.z;
	}

	bool operator==(const Vec3& left, const Vec3& right)
	{
		return ApproxEqual(left.x, right.x) && ApproxEqual(left.y, right.y) && ApproxEqual(left.z, right.z);
	}

	bool operator!=(const Vec3& left, const Vec3& right)
	{
		return !(left == right);
	}

	Vec3::operator gofxmath::Vec2() const
	{
		return Vec2(x, y);
	}

	Vec3::operator gofxmath::Vec4() const
	{
		return Vec4(x, y, z, 0.0f);
	}
}