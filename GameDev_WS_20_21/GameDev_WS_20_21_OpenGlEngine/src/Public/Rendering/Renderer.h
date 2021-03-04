#pragma once

#include <unordered_map>

struct EngineCallback;
class Camera;
class Mesh;
class Shader;
class IndexBuffer;
class VertexArray;

class Renderer
{
public:
	static void Clear();
	static void Draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer);

	static void RenderScene();
	static void RenderGui();
	
	static void AddRenderSceneCallback(EngineCallback& callback);
	static void RemoveRenderSceneCallback(EngineCallback& callback);

	static void AddRenderGuiCallback(EngineCallback& callback);
	static void RemoveRenderGuiCallback(EngineCallback& callback);

public:
	static Camera* MainCamera;

private:
	static std::unordered_map < uint32_t, VertexArray*> m_vertexArrays;

	static std::unordered_map < uint32_t, EngineCallback*> RenderSceneCallbacks;
	static std::unordered_map < uint32_t, EngineCallback*> RenderGuiCallbacks;
};
