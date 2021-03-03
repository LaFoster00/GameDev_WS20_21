#include "Rendering/Renderer.h"

#include "DebugTools.h"
#include "GameSystems/Callbacks.h"
#include "Rendering/IndexBuffer.h"
#include "Rendering/VertexArray.h"


std::unordered_map < uint32_t, VertexArray*> Renderer::m_vertexArrays;
std::unordered_map < uint32_t, EngineCallback*> Renderer::RenderSceneCallbacks;
std::unordered_map < uint32_t, EngineCallback*> Renderer::RenderGuiCallbacks;

Camera* Renderer::MainCamera;

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

void Renderer::RenderScene()
{
	for (auto renderer_callback : RenderSceneCallbacks)
	{
		renderer_callback.second->callback();
	}
}

void Renderer::RenderGui()
{
	for (auto renderer_callback : RenderGuiCallbacks)
	{
		renderer_callback.second->callback();
	}
}

void Renderer::AddRenderSceneCallback(uint32_t id, EngineCallback& callback)
{
	if (RenderSceneCallbacks.find(id) == RenderSceneCallbacks.end())
	{
		RenderSceneCallbacks[id] = &callback;
	}
}

void Renderer::RemoveRenderSceneCallback(uint32_t id)
{
	if (RenderSceneCallbacks.find(id) != RenderSceneCallbacks.end())
	{
		RenderSceneCallbacks.erase(id);
	}
}

void Renderer::AddRenderGuiCallback(uint32_t id, EngineCallback& callback)
{
	if (RenderGuiCallbacks.find(id) == RenderGuiCallbacks.end())
	{
		RenderGuiCallbacks[id] = &callback;
	}
}

void Renderer::RemoveRenderGuiCallback(uint32_t id)
{
	if (RenderGuiCallbacks.find(id) != RenderGuiCallbacks.end())
	{
		RenderGuiCallbacks.erase(id);
	}
}