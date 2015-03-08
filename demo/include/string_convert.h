#ifndef STRING_CONVERT_DOT_H
#define STRING_CONVERT_DOT_H

#include <string>

namespace gfxengine
{
	std::string cvt_to_string(int n);
	std::string cvt_to_string(unsigned int n);

	std::string cvt_to_string(long n);
	std::string cvt_to_string(unsigned long n);

	std::string cvt_to_string(long long n);
	std::string cvt_to_string(unsigned long long n);

	std::string cvt_to_string(float n);
	std::string cvt_to_string(double n);

	std::string cvt_to_string(bool n);
}

#endif