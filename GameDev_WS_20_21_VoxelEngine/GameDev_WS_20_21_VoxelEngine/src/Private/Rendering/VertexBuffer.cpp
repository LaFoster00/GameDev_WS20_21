#include "Rendering/VertexBuffer.h"

#include "DebugTools.h"

VertexBuffer::VertexBuffer(const void* data, uint32_t size)
{
	GLASSERTCCALL(glGenBuffers(1, &m_rendererID));
	GLASSERTCCALL(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
	GLASSERTCCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
	GLASSERTCCALL(glDeleteBuffers(1, &m_rendererID));
}

void VertexBuffer::Bind() const
{
	GLASSERTCCALL(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
}

void VertexBuffer::Unbind() const
{
	GLASSERTCCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
