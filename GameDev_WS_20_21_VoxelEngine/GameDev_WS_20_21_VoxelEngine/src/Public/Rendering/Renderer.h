#pragma once
#include <unordered_map>

#include "GameObjects/Components/Camera.h"

class Mesh;
class Shader;
class IndexBuffer;
class VertexArray;

class Renderer
{
public:
	static void Clear();
	static void Draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer);

	static VertexArray* AddVertexArray(uint32_t id);
	static VertexArray* GetVertexArray(uint32_t id);
public:
	static Camera* mainCamera;

private:
	static std::unordered_map < uint32_t, VertexArray*> m_vertexArrays;
};
