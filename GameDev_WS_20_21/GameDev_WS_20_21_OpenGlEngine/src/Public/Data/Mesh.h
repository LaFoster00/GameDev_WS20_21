#pragma once

#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "Rendering/VertexArray.h"
#include "Rendering/VertexBuffer.h"
#include "Rendering/VertexBufferLayout.h"
#include "Rendering/IndexBuffer.h"

struct Face
{
	glm::ivec3 vertices[3];

	Face()
	{
		vertices[0] = glm::ivec3(0);
		vertices[1] = glm::ivec3(0);
		vertices[2] = glm::ivec3(0);
	}
	
	Face(const Face& f)
	{
		vertices[0] = glm::ivec3(f.vertices[0]);
		vertices[1] = glm::ivec3(f.vertices[1]);
		vertices[2] = glm::ivec3(f.vertices[2]);
	}
};

class Mesh
{
public:
	Mesh(const std::string& filepath, const void* data, uint32_t size, const uint32_t* indices, uint32_t count);
	Mesh(const std::string& filepath, std::vector<glm::vec3>& positions, std::vector<glm::vec2>& uvs, std::vector<glm::vec3>& normals,
		std::vector<Face>& faces);
	~Mesh();

	void Populate(std::vector<glm::vec3>& positions, std::vector<glm::vec2>& uvs, std::vector<glm::vec3>& normals,
		std::vector<Face>& faces);
	
	const VertexArray& GetVertexArray() const;
	const IndexBuffer& GetIndexBuffer() const;
public:
	std::string filepath;

private:
	VertexArray m_meshVertexArray;
	VertexBuffer m_meshVertexBuffer;
	VertexBufferLayout m_meshVertexBufferLayout;
	IndexBuffer m_meshIndexBuffer;
};
