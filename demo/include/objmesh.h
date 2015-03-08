#ifndef OBJ_MESH_DOT_H
#define OBJ_MESH_DOT_H
#include <vector>
#include <unordered_map>
#include "Vec2.h"
#include "Vec3.h"
#include "objmaterial.h"

namespace gofxengine
{
	/* Types of polygons */
	enum PolyType
	{
		PT_NONE = 0, TRIANGLES = 3, QUADS = 4
	};

	/* Vertex Format Types */
	enum VertexFormat
	{
		VF_NONE = 0,// Default (none) - no mesh should have this.  This is used purely for the sake of debugging/error handling
		V = 1,	// Vertex only
		VT = 3,	// Vertex and texture coordinates only
		VN = 5,	// Vertex and normals only
		VTN = 7		// Vertex, texture coordinates, and normal vector
	};

	/* Polygon Rendering Format Types */
	enum PolyRenderFormat
	{
		PR_NONE,// Default (none) - no mesh should have this.  This is used purely for the sake of debugging/error handling
		FLAT,	// Flat rendering
		SMOOTH	// Smooth rendering
	};

	/* struct for storing .obj information */
	struct ObjMesh
	{
		std::vector<gofxmath::Vec3> vertices;// Vertices for this mesh
		std::vector<gofxmath::Vec2> uv;// UV Texture coordinates for this mesh
		std::vector<gofxmath::Vec3> normals;// Normals for this mesh
		std::vector<unsigned int> faceIndices;// Vertex indices for the faces of this mesh
		std::vector<unsigned int> uvIndices;// UV indices to go with each vertex
		std::vector<unsigned int> normIndices;// Normal indices to go with each vertex
		std::unordered_map<unsigned int, std::pair<unsigned int, unsigned int>> vertexInformation;// Vertex information (used if single-indexing)

		int matLibStartIdx;// The index which the obj file containing this mesh started at, with the material library
		int matLibOffsetIdx;// The exact offset index to get this mesh's material from the library, starting with the starting index
		int matLibEndIdx;// The index which the obj file containing this mesh ended at, with the material library

		VertexFormat vertFormat;// Vertex format type for this mesh
		PolyRenderFormat polyRenderFormat;// Polygon rendering format for this mesh

		// Clear this mesh.
		void clear();
	};
}

#endif