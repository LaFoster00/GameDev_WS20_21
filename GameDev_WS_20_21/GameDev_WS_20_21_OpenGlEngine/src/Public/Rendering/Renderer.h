#pragma once

#include <unordered_map>

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
	
public:
	static Camera* mainCamera;

private:
	static std::unordered_map < uint32_t, VertexArray*> m_vertexArrays;
};
