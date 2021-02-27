#include "Data/Mesh.h"

Mesh::Mesh(const void* data, uint32_t size, const uint32_t* indexBuffer, uint32_t count) :
	m_meshVertexArray(),
	m_meshVertexBuffer(data, size),
	m_meshVertexBufferLayout(),
	m_indexBuffer(indexBuffer, count)
{
	
}

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices) : m_meshVertexArray(), m_meshVertexBufferLayout(), m_meshVertexBuffer(nullptr, 0), m_indexBuffer(nullptr, 0)
{
	std::vector<float> convertedVertices(vertices.size() * 8);
	for (int i=0; i < vertices.size(); i++)
	{
		convertedVertices[i * 8 + 0] = vertices[i].location.x;
		convertedVertices[i * 8 + 1] = vertices[i].location.y;
		convertedVertices[i * 8 + 2] = vertices[i].location.z;
		convertedVertices[i * 8 + 3] = vertices[i].uv.x;
		convertedVertices[i * 8 + 4] = vertices[i].uv.y;
		convertedVertices[i * 8 + 5] = vertices[i].normal.x;
		convertedVertices[i * 8 + 6] = vertices[i].normal.y;
		convertedVertices[i * 8 + 7] = vertices[i].normal.z;
	}
	
	m_meshVertexBuffer = VertexBuffer(convertedVertices.data(), sizeof(float) * convertedVertices.size());
	m_meshVertexBufferLayout.Push<float>(3); // position
	m_meshVertexBufferLayout.Push<float>(2); // uv
	m_meshVertexBufferLayout.Push<float>(3); // normal
	
	m_indexBuffer = IndexBuffer(indices.data(), indices.size());

	m_meshVertexArray.AddBuffer(m_meshVertexBuffer, m_meshVertexBufferLayout);
}

Mesh::~Mesh()
{
}
