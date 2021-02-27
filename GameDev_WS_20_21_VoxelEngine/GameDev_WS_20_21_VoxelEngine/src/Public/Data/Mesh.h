#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>


#include "Rendering/IndexBuffer.h"
#include "Rendering/VertexArray.h"
#include "Rendering/VertexBuffer.h"
#include "Rendering/VertexBufferLayout.h"

struct Vertex
{
	glm::vec3 location;
	glm::vec3 normal;
	glm::vec2 uv;
};

class Mesh
{
public:
	Mesh(const void* data, uint32_t size, const uint32_t* indexBuffer, uint32_t count);
	Mesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);
	~Mesh();

private:
	VertexArray m_meshVertexArray;
	VertexBuffer m_meshVertexBuffer;
	VertexBufferLayout m_meshVertexBufferLayout;
	IndexBuffer m_indexBuffer;
	std::vector<Vertex> m_vertices;
};
