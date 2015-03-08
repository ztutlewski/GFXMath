#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include "objloader.h"
#include "stringutility.h"
#include <unordered_set>

namespace gfxengine
{
	using namespace gfxmath;

	typedef std::tuple<unsigned int, unsigned int, unsigned int> faceTuple;// Simplification of face tuples into a type
	void ParseMtlFile(std::string fileDir);
	bool ParseFace(std::istringstream &sStream, ObjMesh &mesh);

	std::vector<ObjMaterial> materialLibrary;// Material library to be pulled from by various meshes

	// does the given vertex format use texture coordinates?
	__inline bool UsesTextureCoord(VertexFormat vf)
	{
		return vf & 2 > 0;
	}

	// does the given vertex format use normal vectors?
	__inline bool UsesNormalVector(VertexFormat vf)
	{
		return vf & 4 > 0;
	}

	// Makethe given mesh single-indexed
	void MakeSingleIndex(ObjMesh& mesh)
	{
		// If the mesh's vertex format indicates that it has a texture coordinate and a normal vector for every vertex
		if (mesh.vertFormat == VertexFormat::VTN)
		{
			std::unordered_set<unsigned int> usedVertIndices;// Vertex indices that have been used
			std::unordered_map<std::string, faceTuple> usedTuples;// Used tuples of vertex indices, uvs and normals (in that order)
			std::vector<unsigned int> tempFaces;// Temporary vector to contain face vertex indices

			// Iterate over every face index, checking each to ensure that every vertex index 
			for (size_t i = 0; i < mesh.faceIndices.size(); i++)
			{
				unsigned int vertIdx = mesh.faceIndices[i];// The current vertex index
				unsigned int uvIdx = mesh.uvIndices[i];// The current uv index
				unsigned int normIdx = mesh.normIndices[i];// The current normal index

				std::ostringstream convert;// A string output stream used to convert the indices into a tuple
				convert << vertIdx << "/" << uvIdx << "/" << normIdx;
				std::string stringTuple = convert.str();// The string form of the tuple currently being checked

				// If we've never found this exact tuple before
				if (usedTuples.find(stringTuple) == usedTuples.end())
				{
					// If this vertex has never been in another tuple we've found, before
					if (usedVertIndices.find(vertIdx) == usedVertIndices.end())
					{
						usedVertIndices.emplace(vertIdx);
					}
					// Else if this vertex HAS been used before, in another tuple
					else
					{
						// Duplicate the vertex and normal vector at the respective indices (vertIdx and normIdx) at the end of their respective lists
						mesh.vertices.push_back(Vec3(mesh.vertices[vertIdx]));
						mesh.normals.push_back(Vec3(mesh.normals[normIdx]));

						// Update the vertex and normal indices for the current vertex and normal.
						vertIdx = mesh.vertices.size() - 1;
						normIdx = mesh.normals.size() - 1;
					}

					// Save off the vertex index and vertex information, and 
					tempFaces.push_back(vertIdx);
					mesh.vertexInformation.emplace(vertIdx, std::pair<unsigned int, unsigned int>(uvIdx, normIdx));
					usedTuples.emplace(stringTuple, faceTuple(vertIdx, uvIdx, normIdx));
				}
				// Else if we have seen this exact tuple before
				else
				{
					unsigned int faceIdx = std::get<0>(usedTuples[stringTuple]);
					tempFaces.push_back(faceIdx);
				}
			}

			mesh.faceIndices = tempFaces;
		}
	}

	// parse in a face from the given string-stream (triangle)
	bool ParseFace(std::istringstream &sStream, ObjMesh &mesh)
	{
		// Parse face indices
		int v, t, n;

		v = t = n = -1;

		std::string indexTuple;// The index tuple that contains the vertex index, as well as (optionally) a texture coordinate index and a normal vector index

		int numPoints = 0;// Number of points that have been read in, thus far

		// While the stream has not reached the end of the line
		while (!sStream.eof())
		{
			sStream >> indexTuple;

			VertexFormat vFormat = VertexFormat::VTN;
			int numAccepted = sscanf_s(indexTuple.c_str(), "%d/%d/%d", &v, &t, &n);// Try to get the standard vertex/texture coordinate/normal vector (VTN) format

			// If that format failed, try with just the vertex and texture coordinates (VT)
			if (numAccepted == 0)
			{
				vFormat = VertexFormat::VT;
				numAccepted = sscanf_s(indexTuple.c_str(), "%d/%d", &v, &t);

				// If that format failed, try it with the just the vertex and normal vector (VN)
				if (numAccepted == 0)
				{
					vFormat = VertexFormat::VN;
					numAccepted = sscanf_s(indexTuple.c_str(), "%d//%d", &v);

					// IF that failed, try it with just the vertex (V)
					if (numAccepted == 0)
					{
						vFormat = VertexFormat::V;
						numAccepted = sscanf_s(indexTuple.c_str(), "%d", &v);

						// If that failed, this isn't going to work.  Return false.
						if (numAccepted == 0)
						{
							return false;
						}
					}
				}
			}



			mesh.faceIndices.push_back(v - 1);

			// If the vertex format includes texture coordinates
			if (UsesTextureCoord(vFormat))
			{
				mesh.uvIndices.push_back(t - 1);
			}

			// If the vertex format includes normal vectors
			if (UsesNormalVector(vFormat))
			{
				mesh.normIndices.push_back(n - 1);
			}

			mesh.vertFormat = vFormat;
			numPoints++;
		}
		return true;
	}

	// Parse the given .mtl file
	void ParseMtlFile(std::string fileDir)
	{
		ObjMaterial material;

		std::ifstream iStream;
		std::string line;
		std::string lineHeader;

		iStream.open(fileDir.c_str(), std::ifstream::in);
		int mtlCount = 0;

		if (!iStream.good())
			return;

		while (!iStream.eof())
		{
			getline(iStream, line);

			if (line.empty() || line[0] == '#')
				continue;

			std::istringstream sStream(line);
			sStream >> lineHeader;

			if (lineHeader == "newmtl")
			{
				if (mtlCount++ > 0)
				{
					materialLibrary.push_back(material);
					material.clear();
				}

				sStream >> material.name;
			}
			else if (lineHeader == "Ns")
			{
				sStream >> material.specExp;
			}
			else if (lineHeader == "Ka")
			{
				sStream >> material.ambient[0];
				sStream >> material.ambient[1];
				sStream >> material.ambient[2];
			}
			else if (lineHeader == "Kd")
			{
				sStream >> material.diffuse[0];
				sStream >> material.diffuse[1];
				sStream >> material.diffuse[2];
			}
			else if (lineHeader == "Ks")
			{
				sStream >> material.specular[0];
				sStream >> material.specular[1];
				sStream >> material.specular[2];
			}
			else if (lineHeader == "Ni")
			{
				sStream >> material.refracIdx;
			}
			else if (lineHeader == "d")
			{
				sStream >> material.alpha;
			}
			else if (lineHeader == "illum")
			{
				int illumModel;
				sStream >> illumModel;
				material.illum = (IlluminationModel)illumModel;
			}
			else if (lineHeader == "map_Kd")
			{
				std::string map0;
				sStream >> map0;
				if (IsNumber(map0))
				{
					material.colorMap[0] = (float)atof(map0.c_str());
					sStream >> map0;

					if (IsNumber(map0))
					{
						material.colorMap[1] = (float)atof(map0.c_str());
						sStream >> material.colorMap[2];
					}
					else
					{
						material.colorMap[2] = material.colorMap[1] = material.colorMap[0];
						material.colorMapFile = map0;
					}
				}
				else
				{
					material.colorMap[2] = material.colorMap[1] = material.colorMap[0] = 1.0f;
					material.colorMapFile = map0;
				}
			}
		}
	}

	// Load the obj file
	std::vector<ObjMesh> LoadObj(std::string file)
	{
		std::vector<ObjMesh> meshes;// Container to hold the meshes found in the given file
		ObjMesh mesh;// The first mesh

		std::ifstream iStream;// File input stream to handle reading in the file
		std::string line;// The current line being parsed
		std::string lineHeader;// The line's header (used to determine how to parse the rest of the line)

		bool hasSeenObjectHeader = false;// Has the ObjLoader already seen an object header? (if so, any 'o' headers indicate that another mesh needs to be created for the mesh information that follows it)

		iStream.open(file.c_str(), std::ifstream::in);

		// If the stream is no good, return the empty vector.
		if (!iStream.good())
			return meshes;

		// While the stream has not reached the end of the file
		while (!iStream.eof())
		{
			// Read in a line
			getline(iStream, line);

			// If the line is empty, or if it is a comment line, continue.
			if (line.empty() || line[0] == '#')
			{
				continue;
			}

			// Create a string stream with the line, and load up the header to start the process
			std::istringstream sStream(line);
			sStream >> lineHeader;

			// If the line header indicates the line contains vertex position information
			if (lineHeader == "v")
			{
				// Parse vertex coordinates
				float x, y, z;

				sStream >> x;
				sStream >> y;
				sStream >> z;

				mesh.vertices.push_back(Vec3(x, y, z));
			}
			// Else if the line header inidicates the line contains texture coordinate information
			else if (lineHeader == "vt")
			{
				// Parse texture coordinates
				float u, v;

				sStream >> u;
				sStream >> v;

				mesh.uv.push_back(Vec2(u, v));
			}
			// Else if the line header indicates the line contains normal vector information
			else if (lineHeader == "vn")
			{
				// Parse vertex normal
				float x, y, z;

				sStream >> x;
				sStream >> y;
				sStream >> z;

				mesh.normals.push_back(Vec3(x, y, z));

				unsigned int idx = mesh.normals.size() - 1;
			}
			// Else if the lien header indicates that it contains face information
			else if (lineHeader == "f")
			{
				if (!ParseFace(sStream, mesh))
				{
					return meshes;
				}
			}
			// Else if the header indicates the beginning of an object
			else if (lineHeader == "o")
			{
				// If we haven't seen an object header yet, ensure that we know we have, next time.
				if (!hasSeenObjectHeader)
				{
					hasSeenObjectHeader = true;
				}
				// If we have seen an object header before, save the current mesh off and start a new one
				else
				{
					// If the mesh's polygon rendering format hasn't been initiated, set it to smooth.
					if (mesh.polyRenderFormat == PolyRenderFormat::PR_NONE)
						mesh.polyRenderFormat = PolyRenderFormat::SMOOTH;

					meshes.push_back(mesh);
					mesh.clear();
				}
			}
			// Else if the line header indicates a new group should be created, save off the current mesh and start a new one
			else if (lineHeader == "g")
			{
				// If the mesh's polygon rendering format hasn't been initiated, set it to smooth.
				if (mesh.polyRenderFormat == PolyRenderFormat::PR_NONE)
					mesh.polyRenderFormat = PolyRenderFormat::SMOOTH;

				meshes.push_back(mesh);
				mesh.clear();
			}
			// Else if the line header indicates a material library, parse the given mtl directory
			else if (lineHeader == "mtllib")
			{
				mesh.matLibStartIdx = materialLibrary.size();

				std::string fileDir;// The file directory of the material library
				sStream >> fileDir;
				ParseMtlFile(fileDir);
				mesh.matLibEndIdx = materialLibrary.size();
			}
			// Else if the line header indicates that we should use a specific material, look for that material
			else if (lineHeader == "usemtl")
			{
				std::string matName;// The given material's name
				sStream >> matName;

				mesh.matLibOffsetIdx = -1;

				for (int i = mesh.matLibStartIdx; i < mesh.matLibEndIdx; i++)
				{
					if (materialLibrary[i].name == matName)
					{
						mesh.matLibOffsetIdx = i;
						break;
					}
				}

				if (mesh.matLibOffsetIdx == -1)
				{
					std::cout << "There was a problem finding the appropriate material." << std::endl;
				}
			}
			// Else if the line header indicates the shading model we should use (1 = smooth, OFF = flat)
			else if (lineHeader == "s")
			{
				std::string smoothOption;// The smoothing option for this mesh
				sStream >> smoothOption;

				if (smoothOption == "OFF")
				{
					mesh.polyRenderFormat = PolyRenderFormat::FLAT;
				}
				else
				{
					mesh.polyRenderFormat = PolyRenderFormat::SMOOTH;
				}
			}
		}

		// If the mesh's polygon rendering format hasn't been initiated, set it to smooth.
		if (mesh.polyRenderFormat == PolyRenderFormat::PR_NONE)
			mesh.polyRenderFormat = PolyRenderFormat::SMOOTH;

		meshes.push_back(mesh);

		return meshes;
	}

	// Load the obj file with single-indexing
	std::vector<ObjMesh> LoadObjSingleIndex(std::string file)
	{
		std::vector<ObjMesh> meshes = LoadObj(file);// Container to hold the meshes found in the given file

		std::cout << file << std::endl;// Print the mesh's file to the console (debugging purposes only)

		// For each mesh that was found in that file, make them singly-indexed (one vertex index to one texture coordinate and one normal vector)
		for (size_t i = 0; i < meshes.size(); i++)
		{
			ObjMesh mesh = meshes[i];
			MakeSingleIndex(mesh);
			meshes[i] = mesh;
		}

		return meshes;
	}
}