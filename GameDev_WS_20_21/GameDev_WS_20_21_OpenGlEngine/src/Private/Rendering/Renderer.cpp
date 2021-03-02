#include "Rendering/Renderer.h"

#include "DebugTools.h"
#include "Rendering/IndexBuffer.h"
#include "Rendering/VertexArray.h"


std::unordered_map < uint32_t, VertexArray*> Renderer::m_vertexArrays;

Camera* Renderer::mainCamera;

void Renderer::Clear()
{
	GLASSERTCALL(glClear(GL_COLOR_BUFFER_BIT));
	GLASSERTCALL(glClear(GL_DEPTH_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer)
{
	vertexArray.Bind();
	indexBuffer.Bind();
	GLASSERTCALL(glDrawElements(GL_TRIANGLES, indexBuffer.GetCount(), GL_UNSIGNED_INT, nullptr));
}
