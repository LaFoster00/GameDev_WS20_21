#include "Data/Mesh.h"

Mesh::Mesh(const void* data, uint32_t size, const uint32_t* indexBuffer, uint32_t count) :
	m_meshVertexArray(),
	m_meshVertexBuffer(data, size),
	m_meshVertexBufferLayout(),
	m_meshIndexBuffer(indexBuffer, count)
{
	m_meshVertexBufferLayout.Push<float>(3); //Position
	m_meshVertexBufferLayout.Push<float>(2); //UVs
	m_meshVertexBufferLayout.Push<float>(3); //Normal
	m_meshVertexArray.AddBuffer(m_meshVertexBuffer, m_meshVertexBufferLayout);
}

Mesh::Mesh(std::vector<glm::vec3>& positions, std::vector<glm::vec2>& uvs, std::vector<glm::vec3>& normals,
	std::vector<Face>& faces) :
	m_meshVertexArray(),
	m_meshVertexBuffer(positions, uvs, normals, faces),
	m_meshVertexBufferLayout(),
	m_meshIndexBuffer(faces)
	
{
	m_meshVertexBufferLayout.Push<float>(3); //Position
	m_meshVertexBufferLayout.Push<float>(2); //UVs
	m_meshVertexBufferLayout.Push<float>(3); //Normal
	m_meshVertexArray.AddBuffer(m_meshVertexBuffer, m_meshVertexBufferLayout);
}

Mesh::~Mesh()
{
	
}

const VertexArray& Mesh::GetVertexArray() const
{
	return m_meshVertexArray;
}

const IndexBuffer& Mesh::GetIndexBuffer() const
{
	return m_meshIndexBuffer;
}
