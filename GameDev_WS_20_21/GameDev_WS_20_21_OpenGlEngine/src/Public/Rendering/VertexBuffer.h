#pragma once

#include <cstdint>
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

struct Face;

class VertexBuffer
{
public:
	VertexBuffer(const void* data, uint32_t size);
	VertexBuffer(std::vector<glm::vec3>& positions, std::vector<glm::vec2>& uvs, std::vector<glm::vec3>& normals,
		std::vector<Face>& faces);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
private:
	uint32_t m_rendererID;
};
