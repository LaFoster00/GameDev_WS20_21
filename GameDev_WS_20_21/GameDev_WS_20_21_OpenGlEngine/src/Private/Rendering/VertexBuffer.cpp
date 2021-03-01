#include "Rendering/VertexBuffer.h"

#include "DebugTools.h"
#include "Data/Mesh.h"


VertexBuffer::VertexBuffer(const void* data, uint32_t size)
{
	GLASSERTCALL(glGenBuffers(1, &m_rendererID));
	GLASSERTCALL(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
	GLASSERTCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::VertexBuffer(std::vector<glm::vec3>& positions, std::vector<glm::vec2>& uvs, std::vector<glm::vec3>& normals,
	std::vector<Face>& faces)
{
	std::vector<float> data(faces.size() * 3 * 8);

	for (uint32_t face = 0; face < faces.size();  face++)
	{
		for (uint32_t vertex = 0; vertex < 3; vertex++)
		{
			const uint32_t indexPosition = faces[face].vertices[vertex].x; // index: position
			const uint32_t indexUV = faces[face].vertices[vertex].y; // index: uv
			const uint32_t indexNormal = faces[face].vertices[vertex].z; // index: normal

			const uint32_t currentVertexIndex = face * 24 + vertex * 8;

			const glm::vec3 vertexPosition = positions[indexPosition];
			const glm::vec2 vertexUV = uvs[indexUV];
			const glm::vec3 vertexNormal = normals[indexNormal];
			
			data[currentVertexIndex + 0] = vertexPosition.x;// Position.x
			data[currentVertexIndex + 1] = vertexPosition.y; // Position.y
			data[currentVertexIndex + 2] = vertexPosition.z;// Position.z
			data[currentVertexIndex + 3] = vertexUV.x; // UV.x
			data[currentVertexIndex + 4] = vertexUV.y; // UV.y
			data[currentVertexIndex + 5] = vertexNormal.x; // Normal.x
			data[currentVertexIndex + 6] = vertexNormal.y; // Normal.y
			data[currentVertexIndex + 7] = vertexNormal.z; // Normal.z
		}
	}
	
	GLASSERTCALL(glGenBuffers(1, &m_rendererID));
	GLASSERTCALL(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
	GLASSERTCALL(glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
	GLASSERTCALL(glDeleteBuffers(1, &m_rendererID));
}

void VertexBuffer::Bind() const
{
	GLASSERTCALL(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
}

void VertexBuffer::Unbind() const
{
	GLASSERTCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}