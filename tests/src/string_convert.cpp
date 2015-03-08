#include "string_convert.h"

#ifdef __MINGW32__
#include <sstream>

template<typename T>
std::string convert(const T& n)
{
	std::ostringstream stm;
	stm << n;
	return stm.str();
}
#define CONVERT_TO_STRING(v) convert((v))
#else
#define CONVERT_TO_STRING(v) std::to_string((v))
#endif

namespace gofxengine
{



	std::string cvt_to_string(int n)
	{
		return CONVERT_TO_STRING(n);
	}

	std::string cvt_to_string(unsigned int n)
	{
		return CONVERT_TO_STRING(n);
	}


	std::string cvt_to_string(long n)
	{
		return CONVERT_TO_STRING(n);
	}

	std::string cvt_to_string(unsigned long n)
	{
		return CONVERT_TO_STRING(n);
	}

	std::string cvt_to_string(long long n)
	{
		return CONVERT_TO_STRING(n);
	}

	std::string cvt_to_string(unsigned long long n)
	{
		return CONVERT_TO_STRING(n);
	}


	std::string cvt_to_string(float n)
	{
		return CONVERT_TO_STRING(n);
	}

	std::string cvt_to_string(double n)
	{
		return CONVERT_TO_STRING(n);
	}


	std::string cvt_to_string(bool n)
	{
		return CONVERT_TO_STRING(n);
	}
}

