#include "Data/Mesh.h"

Mesh::Mesh(const void* data, uint32_t size, const uint32_t* indexBuffer, uint32_t count) : m_meshVertexBuffer(data, size), m_indexBuffer(indexBuffer, count)
{
}

static void* ConvertVertexToBufferData(std::vector<Vertex>& vertices)
{
	std::vector<float> convertedVertices(vertices.size() * 8);
	for (int i = 0; i < vertices.size(); i++)
	{
		convertedVertices[8 * i + 0] = vertices[i].location.x;
		convertedVertices[8 * i + 1] = vertices[i].location.y;
		convertedVertices[8 * i + 2] = vertices[i].location.z;
		convertedVertices[8 * i + 3] = vertices[i].uv.x;
		convertedVertices[8 * i + 4] = vertices[i].uv.y;
		convertedVertices[8 * i + 5] = vertices[i].normal.x;
		convertedVertices[8 * i + 6] = vertices[i].normal.y;
		convertedVertices[8 * i + 7] = vertices[i].normal.z;
	}

	return convertedVertices.data();
}

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices) :
	m_meshVertexBuffer(ConvertVertexToBufferData(vertices), vertices.size() * sizeof(float) * 8),
	m_indexBuffer(indices.data(), indices.size())
{
	m_vertices = vertices;
	
	m_meshVertexBufferLayout.Push<float>(3); // position
	m_meshVertexBufferLayout.Push<float>(2); // uv
	m_meshVertexBufferLayout.Push<float>(3); // normal
	
	m_meshVertexArray.AddBuffer(m_meshVertexBuffer, m_meshVertexBufferLayout);
}

Mesh::~Mesh()
{
	
}
