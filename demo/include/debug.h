#ifndef DEBUG_DOT_H
#define DEBUG_DOT_H
#include <string>
#include "ssevec_math_defs.h"

namespace gofxmath
{
	class SseMat44;
	class Mat44;
}

namespace gofxengine
{
	void PrintGofFofXMatrix(const gofxmath::SseMat44& mat);
	void PrintGofFofXMatrix(const gofxmath::Mat44& mat);
	void PrintMat4WithHeader(const std::string& header, const gofxmath::Mat44& toPrint);
	void PrintMat4WithHeader(const std::string& header, const gofxmath::SseMat44& toPrint);
	void PrintSseVecWithHeader(const std::string& header, const gofxmath::SseVec& vec);
}

#endif