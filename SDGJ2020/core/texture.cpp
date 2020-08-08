#include "texture.h"
#include "assert.h"
#include <string>

Texture::Texture(unsigned char* data, unsigned int width, unsigned int height, unsigned int numChannels) : m_width(width), m_height(height), m_numChannels(numChannels)
{
	ASSERT(data, "Error: null contents provided to texture asset.");

	unsigned int size = width * height * numChannels;
	m_pData = (char*)malloc(size);

	ASSERT(m_pData, "Error: Failed to allocate memory for texture asset.");
	memcpy(m_pData, data, size);
}

Texture::~Texture()
{
	free(m_pData);
}
