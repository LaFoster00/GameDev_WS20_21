#include "Tools/ObjImporter.h"

#include <fstream>
#include <sstream>
#include <string>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "Data/Mesh.h"

Mesh* LoadObj(const char* filePath)
{
	std::vector<glm::vec3> vertexPositions;
	std::vector<glm::vec2> vertexUVs;
	std::vector<glm::vec3> vertexNormals;

	std::vector<Face> faces;

	std::stringstream ss;
	std::ifstream inFile(filePath);
	std::string line = "";
	std::string prefix = "";

	glm::vec3 tempVec3;
	glm::vec2 tempVec2;

	uint32_t currentFace = 0;

	if (!inFile.is_open())
	{
		throw "ERROR::OBJIMPORTER::Could not open file";
	}

	while (std::getline(inFile, line))
	{
		ss.clear();
		ss.str(line);
		ss >> prefix;

		if (prefix == "v") // vertex position
		{
			ss >> tempVec3.x >> tempVec3.y >> tempVec3.z;
			vertexPositions.push_back(tempVec3);
		}
		else if (prefix == "vt") // vertex position
		{
			ss >> tempVec2.x >> tempVec2.y;
			vertexUVs.push_back(tempVec2);
		}
		else if (prefix == "vn") // vertex position
		{
			ss >> tempVec3.x >> tempVec3.y >> tempVec3.z;
			vertexNormals.push_back(tempVec3);
		}
		else if (prefix == "f")
		{
			faces.resize(1 + currentFace, Face());
			int faceVertexCounter = 0;
			int vertexComponentCounter = 0;
			uint32_t componentIndex = 0;

			while (ss >> componentIndex)
			{
				if (faceVertexCounter > 2)
				{
					throw "Cant import non triangulated Meshes retard!";
				}
				//Retrieving faces
				faces[currentFace].vertices[faceVertexCounter][vertexComponentCounter] = componentIndex - 1; // - 1 because obj files start counting at 1

				// Handling characters
				if (ss.peek() == '/')
				{
					vertexComponentCounter++;
					ss.ignore(1, '/');
				}
				else if (ss.peek() == ' ')
				{
					vertexComponentCounter = 0;
					faceVertexCounter++;
					ss.ignore(1, ' ');
				}
			}
			currentFace++;
		}
		else if (prefix == "#")
		{

		}
		else if (prefix == "o")
		{

		}
		else if (prefix == "s")
		{

		}
		else if (prefix == "use_mtl")
		{

		}
		else
		{

		}
	}

	std::cout << "Nr of verticies: " << vertexPositions.size() << std::endl;

	Mesh* importedMesh = new Mesh(vertexPositions, vertexUVs, vertexNormals, faces);

	return importedMesh;
}
