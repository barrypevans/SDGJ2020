#pragma once
#include "component.h"
#include "texture.h"
#include <string>
#include "shader.h"
#include "glm/glm.hpp"

class Renderable : public Component
{
public:
	void SetTexture(std::string texturePath);
	virtual void Update() override;
	virtual void Init() override;
	glm::vec2 GetPpuScale();

	Texture* m_texture;
	bool isUI;
	bool shouldOverrideShader;
	Shader* m_overrideShader;
	int m_layerOrder;

	float userData1;
	float userData2;

	void OverrideShader(std::string f, std::string v = "shaders/quad.vs");
};

