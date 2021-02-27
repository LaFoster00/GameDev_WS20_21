#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <sstream>
#include <algorithm>

#include <gl/glew.h>
#include <glfw/glfw3.h>

#include "Data/Mesh.h"

static Mesh* LoadObj(const char* filePath)
{
	std::vector<glm::vec3> vertexPositions;
	std::vector<glm::vec2> vertexUVs;
	std::vector<glm::vec3> vertexNormals;

	std::vector<uint32_t> vertexPositionIndices;
	std::vector<uint32_t> vertexUvIndices;
	std::vector<uint32_t> vertexNormalIndices;

	std::vector<Vertex> vertices;

	std::stringstream ss;
	std::ifstream inFile(filePath);
	std::string line = "";
	std::string prefix = "";

	glm::vec3 tempVec3;
	glm::vec2 tempVec2;
	uint32_t tempUint = 0;

	
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
			int counter = 0;
			while (ss >> tempUint)
			{
				//Pushing indices
				if (counter == 0)
					vertexPositionIndices.push_back(tempUint);
				else if (counter == 1)
					vertexUvIndices.push_back(tempUint);
				else if (counter == 2)
					vertexNormalIndices.push_back(tempUint);

				// Handling characters
				if (ss.peek() == '/')
				{
					++counter;
					ss.ignore(1, '/');
				}
				else if (ss.peek() == ' ')
				{
					++counter;
					ss.ignore(1, ' ');
				}

				// Reset the counter
				if (counter > 2)
					counter = 0;
			}
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

		}else
		{
			
		}
	}

	//Build final vertex array (mesh)
	vertices.resize(vertexPositionIndices.size(), Vertex());

	for (size_t i = 0; i < vertices.size(); i++)
	{
		vertices[i].location = vertexPositions[vertexPositionIndices[i] - 1];
		vertices[i].normal = vertexNormals[vertexNormalIndices[i] - 1];
		vertices[i].uv = vertexUVs[vertexUvIndices[i] -1 ];
	}

	std::cout << "Nr of verticies: " << vertices.size() << std::endl;
	
	Mesh* importedMesh = new Mesh(vertices, vertexPositionIndices);
	
	return importedMesh;
}