#include "Texture.h"

#include <cassert>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


Texture::Texture(const std::string & imagepath)
	:m_imagepath(imagepath)
{
	glGenTextures(1, &m_renderObjectID);
	glBindTexture(GL_TEXTURE_2D, m_renderObjectID);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	m_data = stbi_load(imagepath.c_str(), &m_width, &m_height, &m_nrChannels, 0);
	if (m_data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_data);
		glGenerateTextureMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cerr << "File not found\n";
	}

	stbi_image_free(m_data);
}

Texture::~Texture()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bind(unsigned int slot) const
{
	assert(slot >= 0 && slot <= 32);
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_renderObjectID);
}

void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
