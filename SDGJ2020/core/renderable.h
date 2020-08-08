#pragma once
#include "component.h"
#include "texture.h"
#include <string>

class Renderable : public Component
{
public:
	void SetTexture(std::string texturePath);
	virtual void Update() override;
	virtual void Init() override;
	Texture* m_texture;
	bool isUI;
};

