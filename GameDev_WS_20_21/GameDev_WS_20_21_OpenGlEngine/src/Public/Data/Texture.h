#pragma once

#include <string>

class Texture
{
public:
	Texture(const std::string& path);
	~Texture();

	void Bind(uint32_t slot = 0);
	void Undbind();

	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }

private:
	uint32_t m_rendererID;
	std::string m_filePath;
	unsigned char* m_LocalBuffer;
	int m_width, m_height, m_bpp;
};