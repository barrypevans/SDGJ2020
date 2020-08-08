#pragma once
#include <GL/glew.h>

class Texture
{
public:
	Texture(unsigned char* data, unsigned int width, unsigned int height, unsigned int numChannels);
	~Texture();

	unsigned int m_width, m_height, m_numChannels;
	char* m_pData;
	
	float m_aspect;
	GLuint m_textureId;
};

