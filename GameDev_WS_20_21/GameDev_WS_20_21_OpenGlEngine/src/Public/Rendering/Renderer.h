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
	
	static void AddRenderSceneCallback(uint32_t id, EngineCallback& callback);
	static void RemoveRenderSceneCallback(uint32_t id);

public:
	static Camera* MainCamera;

private:
	static std::unordered_map < uint32_t, VertexArray*> m_vertexArrays;

	static std::unordered_map < uint32_t, EngineCallback*> RenderSceneCallbacks;
};
