#pragma once

class Shader;
class IndexBuffer;
class VertexArray;

class Renderer
{
public:
	void Clear();
	void Draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) const;
};
