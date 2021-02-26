#include "Rendering/IndexBuffer.h"

#include "DebugTools.h"

IndexBuffer::IndexBuffer(const uint32_t* data, uint32_t count)
{
	GLASSERTCCALL(glGenBuffers(1, &m_rendererID));
	GLASSERTCCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));
	GLASSERTCCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
	GLASSERTCCALL(glDeleteBuffers(1, &m_rendererID));
}

void IndexBuffer::Bind() const
{
	GLASSERTCCALL(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
}

void IndexBuffer::Unbind() const
{
	GLASSERTCCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
