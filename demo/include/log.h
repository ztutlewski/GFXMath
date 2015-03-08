#ifndef LOG_DOT_H
#define LOG_DOT_H

#include <string>

#ifdef __MINGW32__
#include <sstream>
#include <string>

template < typename T > 
inline std::string to_string(const T& n)
{
	std::ostringstream stm;
	stm << n;
	return stm.str();
}
#endif

namespace gofxengine
{
	bool RestartGLLog();
	bool GLLog(const std::string& message);
	bool GLLogErr(const std::string& message);
	void LogGLParams();
}

#endif