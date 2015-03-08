#ifndef DEBUG_DOT_H
#define DEBUG_DOT_H
#include <string>
#include "ssevec_math_defs.h"

namespace gfxmath
{
	class SseMat44;
	class Mat44;
}

namespace gfxengine
{
	void PrintGofFofXMatrix(const gfxmath::SseMat44& mat);
	void PrintGofFofXMatrix(const gfxmath::Mat44& mat);
	void PrintMat4WithHeader(const std::string& header, const gfxmath::Mat44& toPrint);
	void PrintMat4WithHeader(const std::string& header, const gfxmath::SseMat44& toPrint);
	void PrintSseVecWithHeader(const std::string& header, const gfxmath::SseVec& vec);
}

#endif