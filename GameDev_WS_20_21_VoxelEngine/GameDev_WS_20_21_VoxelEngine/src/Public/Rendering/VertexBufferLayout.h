#pragma once

#include <GL/glew.h>

#include <vector>

#include "DebugTools.h"

struct VertexBufferElement
{
	uint32_t type;
	uint32_t count;
	unsigned char normalized;

	static uint32_t GetSizeOfType(uint32_t type)
	{
		switch (type)
		{
			case GL_FLOAT:			return 4;
			case GL_UNSIGNED_INT:	return 4;
			case GL_UNSIGNED_BYTE:	return 1;
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
public:
	VertexBufferLayout() : m_stride(0) {}

	template<typename T>
	void Push(uint32_t count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(uint32_t count)
	{
		m_elements.push_back({GL_FLOAT, count, false });
		m_stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
	}

	template<>
	void Push<uint32_t>(uint32_t count)
	{
		m_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
	}
	
	template<>
	void Push<unsigned char>(uint32_t count)
	{
		m_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
	}

	inline std::vector<VertexBufferElement> GetElemetns() const { return m_elements; }
	inline unsigned int GetStride() const { return m_stride; }
private:
	std::vector<VertexBufferElement> m_elements;
	uint32_t m_stride;
};