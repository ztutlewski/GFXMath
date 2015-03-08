#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H

#include <string>
#include <tuple>
#include "objmesh.h"

namespace gofxengine
{
	std::vector<ObjMesh> LoadObj(std::string file);// Load the obj file
	std::vector<ObjMesh> LoadObjSingleIndex(std::string file);// Load the obj file with single-indexing
}
#endif