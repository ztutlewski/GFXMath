#ifndef OBJ_MATERIAL_DOT_H
#define OBJ_MATERIAL_DOT_H

#include <string>

namespace gofxengine
{
	/* Illumination Models */
	enum IlluminationModel
	{
		COL_ON_AMB_OFF = 0,// Color: On, Ambient: Off
		COL_ON_AMB_ON = 1,// Color: On, Ambient: On
		HIGHLIGHT_ON = 2,// Highlights: On
		R_ON_RAY_ON = 3,// Reflection: On, Raytrace: On
		T_GLASS_ON_R_RAY_ON = 4,// Transparency-Glass: On, Reflection-Raytrace: On
		REFL_FRES_RAY_ON = 5,// Reflection-Fresnel & Reflection-Raytrace: On
		T_REFR_ON_R_FRES_OFF_RAY_ON = 6,// Transparency-Refraction: On, Reflection-fresnel off,Reflection-Raytrace: On
		T_REFR_ON_R_FRES_RAY_ON = 7,// Transparency-Refraction: On, Reflection-Fresnel & Reflection-Raytrace: On
		R_ON_RAY_OFF = 8,// Reflection: On, Raytrace Off
		T_GLASS_ON_R_RAY_OFF = 9,// Transparency-Glass: On, Reflection-Raytrace: Off
		CASTS_SHADOWS_ON_INVISIBLE_SURFS = 10// Casts Shadows On Invisible Surfaces
	};

	/* struct for storing .mat information */
	struct ObjMaterial
	{
	public:
		std::string name;// Name of the material

		float specExp;// Specular exponent
		float refracIdx;// Refraction index
		float alpha;// Alpha (usually transparency, but could be used for other purposes)

		float ambient[3];// Ambient reflectivity
		float diffuse[3];// Diffuse reflectivity
		float specular[3];// Specular reflectivity

		float colorMap[3];// Texture color weights (higher value means higher influence from the texture to the color)
		std::string colorMapFile;// Colormap Texture file
		IlluminationModel illum;// Illumination model
	public:
		// Clear this material
		void clear();
	};
}

#endif