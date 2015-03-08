#include "math_defs.h"
#include <limits>

namespace gofxmath
{
	float Infinity()
	{
		return std::numeric_limits<float>::infinity();
	}

	float Epsilon()
	{
		return std::numeric_limits<float>::epsilon();
	}

	float FloatMax()
	{
		return std::numeric_limits<float>::max();
	}	
}