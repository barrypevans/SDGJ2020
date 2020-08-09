#include "texture.h"
#include "assert.h"
#include <string>
#include <GL/glew.h>

Texture::Texture(unsigned char* data, unsigned int width, unsigned int height, unsigned int numChannels) : m_width(width), m_height(height), m_numChannels(numChannels)
{
	ASSERT(data, "Error: null contents provided to texture asset.");

	unsigned int size = width * height * numChannels;
	m_pData = (char*)malloc(size);

	ASSERT(m_pData, "Error: Failed to allocate memory for texture asset.");
	memcpy(m_pData, data, size);

	m_aspect = static_cast<float>(height) / static_cast<float>(width);

	glGenTextures(1, &m_textureId);
	glBindTexture(GL_TEXTURE_2D, m_textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, numChannels == 4 ? GL_RGBA : GL_RGB, width, height, 0, numChannels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, m_pData);
	glBindTexture(GL_TEXTURE_2D, 0);

}

Texture::~Texture()
{
	free(m_pData);
}
