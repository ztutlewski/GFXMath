#include "ssevec.h"
#include <stdio.h>

using namespace std;

namespace gfxmath
{
	void PrintSseVec2(const SseVec& vec)
	{
		Vec2 vec2 = StoreSseVec2(vec);
		cout << vec2 << endl;
	}

	void PrintSseVec3(const SseVec& vec)
	{
		Vec3 vec3 = StoreSseVec3(vec);
		cout << vec3 << endl;
	}

	void PrintSseVec4(const SseVec& vec)
	{
		Vec4 vec4 = StoreSseVec4(vec);
		cout << vec4 << endl;
	}
}