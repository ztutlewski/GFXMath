#ifndef MESH_DOT_H
#define MESH_DOT_H
#include "vec2.h"
#include "vec3.h"
namespace gfxengine
{
#define BUFFER_OFFSET(i) ((void*)(i))

	class ColorVertex
	{
	public:
		gfxmath::Vec3 pos;
		gfxmath::Vec3 color;
	};

	class ColorVertexNorm
	{
	public:
		gfxmath::Vec3 pos;
		gfxmath::Vec3 color;
		gfxmath::Vec3 norm;
	};

	class TexturedVertex
	{
	public:
		gfxmath::Vec3 pos;
		gfxmath::Vec2 uv;
	};

	class TexturedVertexNorm
	{
	public:
		gfxmath::Vec3 pos;
		gfxmath::Vec2 uv;
		gfxmath::Vec3 norm;
	};
}

#endif