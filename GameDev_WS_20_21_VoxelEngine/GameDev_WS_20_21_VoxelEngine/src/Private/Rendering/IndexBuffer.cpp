#include "Rendering/IndexBuffer.h"

#include "DebugTools.h"
#include "Data/Mesh.h"


IndexBuffer::IndexBuffer(const uint32_t* data, uint32_t count)
{
	GLASSERTCALL(glGenBuffers(1, &m_rendererID));
	GLASSERTCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));
	GLASSERTCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GL_STATIC_DRAW));
	m_Count = count;
}

IndexBuffer::IndexBuffer(const std::vector<Face>& faces)
{
	std::vector<uint32_t> indices(faces.size() * 3);

	for (uint32_t i = 0; i < faces.size() * 3; i++)
	{
			indices[i] = i;
	}

	GLASSERTCALL(glGenBuffers(1, &m_rendererID));
	GLASSERTCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));
	GLASSERTCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, faces.size() * 3 * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW));
	m_Count = 3 * faces.size();
}

IndexBuffer::~IndexBuffer()
{
	GLASSERTCALL(glDeleteBuffers(1, &m_rendererID));
}

void IndexBuffer::Bind() const
{
	GLASSERTCALL(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
}

void IndexBuffer::Unbind() const
{
	GLASSERTCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
