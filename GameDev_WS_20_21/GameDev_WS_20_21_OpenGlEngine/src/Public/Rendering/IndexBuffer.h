#pragma once

#include <vector>

struct Face;

class IndexBuffer
{
public:
	IndexBuffer(const uint32_t* data, uint32_t count);
	IndexBuffer(const std::vector<Face>& faces);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline uint32_t GetCount() const
	{
		return m_Count;
	}
private:
	uint32_t m_rendererID;
	int32_t m_Count;
};
