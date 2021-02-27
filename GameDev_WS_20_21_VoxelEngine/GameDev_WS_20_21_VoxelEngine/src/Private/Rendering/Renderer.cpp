#include "Rendering/Renderer.h"

#include <GL/glew.h>

#include "DebugTools.h"
#include "Rendering/IndexBuffer.h"
#include "Rendering/Shader.h"
#include "Rendering/VertexArray.h"

std::unordered_map < uint32_t, VertexArray*> Renderer::m_vertexArrays;
Camera* Renderer::mainCamera;
bool Renderer::m_initialized;

void Renderer::InitRenderer()
{
	if (m_initialized)
	{
		std::cout << "Renderer already initialized" << std::endl;
		return;
	}
	m_initialized = true;
}

void Renderer::Clear()
{
	GLASSERTCALL(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer)
{
	ASSERT(m_initialized && "Renderer isn't initialized! Cant call draw");
	vertexArray.Bind();
	GLASSERTCALL(glDrawElements(GL_TRIANGLES, indexBuffer.GetCount(), GL_UNSIGNED_INT, nullptr));
}

VertexArray* Renderer::AddVertexArray(uint32_t id)
{
	if (m_vertexArrays.find(id) == m_vertexArrays.end())
	{
		m_vertexArrays[id] = new VertexArray;
		return m_vertexArrays[id];
	}

	return nullptr;
}

VertexArray* Renderer::GetVertexArray(uint32_t id)
{
	if (m_vertexArrays.find(id) == m_vertexArrays.end())
	{
		return nullptr;
	}

	return m_vertexArrays[id];
}
