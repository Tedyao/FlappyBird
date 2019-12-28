#include "Texture.h"
#include "vendor/stb_image/stb_Image.h"

Texture::Texture()
	:m_RendererID(0), m_Width(0), m_Height(0), m_BPP(0), m_ImageBuffer(nullptr), m_Path("")
{
}

Texture::Texture(const std::string& path)
	
{
	stbi_set_flip_vertically_on_load(1);
	m_ImageBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);
	GLCall(glGenTextures(1, &m_RendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_ImageBuffer));

	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (m_ImageBuffer)
	{
		stbi_image_free(m_ImageBuffer);
	}

}

Texture::~Texture()
{
	GLCall(glDeleteTextures(0, &m_RendererID));
}

void Texture::bind(unsigned int slot)
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

}

void Texture::unbind()
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
