#pragma once
#include "texture.h"
#include <string>
class Animation
{
public:
	Animation(std::string texturePath, unsigned int numFrames);

	Texture* m_texture;
	unsigned int m_numFrames;
};