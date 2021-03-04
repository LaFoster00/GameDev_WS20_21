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

void Renderer::AddRenderSceneCallback(EngineCallback& callback)
{
	if (RenderSceneCallbacks.find(callback.id) == RenderSceneCallbacks.end())
	{
		RenderSceneCallbacks[callback.id] = &callback;
	}
}

void Renderer::RemoveRenderSceneCallback(EngineCallback& callback)
{
	if (RenderSceneCallbacks.find(callback.id) != RenderSceneCallbacks.end())
	{
		RenderSceneCallbacks.erase(callback.id);
	}
}

void Renderer::AddRenderGuiCallback(EngineCallback& callback)
{
	if (RenderGuiCallbacks.find(callback.id) == RenderGuiCallbacks.end())
	{
		RenderGuiCallbacks[callback.id] = &callback;
	}
}

void Renderer::RemoveRenderGuiCallback(EngineCallback& callback)
{
	if (RenderGuiCallbacks.find(callback.id) != RenderGuiCallbacks.end())
	{
		RenderGuiCallbacks.erase(callback.id);
	}
}