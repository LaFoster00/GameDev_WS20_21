#include "Data\Texture.h"

#include "DebugTools.h"
#include "vendor/stb_image/stb_image.h"

Texture::Texture(const std::string& path) :
	m_rendererID(0),
	m_filePath(path),
	m_LocalBuffer(nullptr),
	m_width(0),
	m_height(0),
	m_bpp(0)
{
	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(path.c_str(), &m_width, &m_height, &m_bpp, 4);
	
	GLASSERTCALL(glGenTextures(1, &m_rendererID));
	GLASSERTCALL(glBindTexture(GL_TEXTURE_2D, m_rendererID));

	GLASSERTCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLASSERTCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLASSERTCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLASSERTCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	
	GLASSERTCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
	GLASSERTCALL(glBindTexture(GL_TEXTURE_2D, 0));

	if (m_LocalBuffer)
	{
		stbi_image_free(m_LocalBuffer);
	}
}

Texture::~Texture()
{
	GLASSERTCALL(glDeleteTextures(1, &m_rendererID));
}

void Texture::Bind(uint32_t slot)
{
	GLASSERTCALL(glActiveTexture(GL_TEXTURE0 + slot));
	GLASSERTCALL(glBindTexture(GL_TEXTURE_2D, m_rendererID));
}

void Texture::Undbind()
{
	GLASSERTCALL(glBindTexture(GL_TEXTURE_2D, 0));
}
