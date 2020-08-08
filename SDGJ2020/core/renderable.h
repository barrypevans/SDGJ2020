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
	bool overrideShader;
	std::string vertexShaderPath;
	std::string fragmentShaderPath;
	int m_layerOrder;

	void OverrideShader(std::string f, std::string v = "shaders/quad.vs");
};

