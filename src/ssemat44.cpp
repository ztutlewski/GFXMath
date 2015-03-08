#include "ssemat44.h"

namespace gfxmath
{
	const SseMat44 SseMat44::IDENTITY = SseMat44(Vec4::E0(), Vec4::E1(), Vec4::E2(), Vec4::E3(), MatrixType::IDENTITY);
}