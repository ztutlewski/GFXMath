#ifndef MESH_DOT_H
#define MESH_DOT_H
#include "vec2.h"
#include "vec3.h"
namespace gofxengine
{
#define BUFFER_OFFSET(i) ((void*)(i))

	class ColorVertex
	{
	public:
		gofxmath::Vec3 pos;
		gofxmath::Vec3 color;
	};

	class ColorVertexNorm
	{
	public:
		gofxmath::Vec3 pos;
		gofxmath::Vec3 color;
		gofxmath::Vec3 norm;
	};

	class TexturedVertex
	{
	public:
		gofxmath::Vec3 pos;
		gofxmath::Vec2 uv;
	};

	class TexturedVertexNorm
	{
	public:
		gofxmath::Vec3 pos;
		gofxmath::Vec2 uv;
		gofxmath::Vec3 norm;
	};
}

#endif