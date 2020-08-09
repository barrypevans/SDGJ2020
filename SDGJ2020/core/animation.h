#pragma once
#include "texture.h"
class Animation
{
public:
	Animation(Texture* texture, unsigned int numFrames) :m_texture(texture), m_numFrames(numFrames) {};

	Texture* m_texture;
	unsigned int m_numFrames;
};