#include "objmaterial.h"

namespace gofxengine
{
	// Clear this material (resets everything to defaults)
	void ObjMaterial::clear()
	{
		specExp = 0.0f;
		refracIdx = 1.0f;
		alpha = 1.0f;

		ambient[0] = ambient[1] = ambient[2] = 0.0f;
		diffuse[0] = diffuse[1] = diffuse[2] = 0.5f;
		specular[0] = specular[1] = specular[2] = 0.0f;
	}
}