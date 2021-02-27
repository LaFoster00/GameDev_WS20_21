#include "Rendering/VertexBuffer.h"

#include "DebugTools.h"

VertexBuffer::VertexBuffer(const void* data, uint32_t size)
{
	if (data == nullptr) return;
	GLASSERTCALL(glGenBuffers(1, &m_rendererID));
	GLASSERTCALL(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
	GLASSERTCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
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
