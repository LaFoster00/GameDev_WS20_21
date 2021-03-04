#include "Rendering/VertexArray.h"

#include "DebugTools.h"
#include "Rendering/VertexBuffer.h"
#include "Rendering/VertexBufferLayout.h"

VertexArray::VertexArray()
{
	GLASSERTCALL(glGenVertexArrays(1, &m_rendererID));
	GLASSERTCALL(glBindVertexArray(m_rendererID));
}

VertexArray::~VertexArray()
{
	GLASSERTCALL(glDeleteVertexArrays(1, &m_rendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout)
{
	Bind();
	vertexBuffer.Bind();
	const auto& elemtents = layout.GetElements();
	uint32_t offset = 0;
	for (uint32_t i = 0; i < elemtents.size(); i++)
	{
		const auto& element = elemtents[i];
		GLASSERTCALL(glEnableVertexAttribArray(i));
		GLASSERTCALL(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), reinterpret_cast<const void*>(offset)));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VertexArray::Bind() const
{
	GLASSERTCALL(glBindVertexArray(m_rendererID));
}

void VertexArray::Unbind() const
{
	GLASSERTCALL(glBindVertexArray(0));
}
