#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "scalar_math.h"
#include <iomanip>

namespace gofxmath
{
	Vec2 Vec2::Right()
	{ 
		static const Vec2 right (1.0f, 0.0f);
		return right;
	}

	Vec2 Vec2::Up()
	{ 
		static const Vec2 up(0.0f, 1.0f);
		return up;
	}

	Vec2 Vec2::Left()
	{ 
		static const Vec2 left(-1.0f, 0.0f);
		return left;
	}

	Vec2 Vec2::Down()
	{ 
		static const Vec2 down(0.0f, -1.0f);
		return down;
	}

	Vec2 Vec2::One()
	{ 
		static const Vec2 one(1.0f);
		return one;
	}

	Vec2 Vec2::NegOne()
	{ 
		static const Vec2 negOne(-1.0f);
		return negOne;
	}

	Vec2 Vec2::Zero()
	{ 
		static const Vec2 zero(0.0f);
		return zero;
	}

	Vec2::Vec2() : x(0.0f), y(0.0f) {}
	Vec2::Vec2(float xy) : x(xy), y(xy) {}
	Vec2::Vec2(float x, float y) : x(x), y(y) {}
	

	std::ostream &operator << (std::ostream& stream, const Vec2& vec)
	{
		std::ios::fmtflags fmtSettings(stream.flags());
		stream << std::setw(3) << std::setprecision(5) << vec.x << " " << vec.y;
		stream.flags(fmtSettings);
		return stream;
	}

	std::istream &operator >> (std::istream& stream, Vec2& vec)
	{
		return stream >> vec.x >> vec.y;
	}

	bool operator==(const Vec2& left, const Vec2& right)
	{
		return ApproxEqual(left.x, right.x) && ApproxEqual(left.y, right.y);
	}

	bool operator!=(const Vec2& left, const Vec2& right)
	{
		return !(left == right);
	}

	Vec2::operator gofxmath::Vec3() const
	{
		return Vec3(x, y, 0.0f);
	}

	Vec2::operator gofxmath::Vec4() const
	{
		return Vec4(x, y, 0.0f, 0.0f);
	}
}