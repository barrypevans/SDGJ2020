#pragma once
#include <string>
#include "gl/glew.h"
class Shader
{
public:
	Shader(std::string fsPath = "shaders/quad.fs", std::string vsPath = "shaders/quad.vs");
	void BindShader();
	GLuint GetProgram() { return m_shaderProg; }
	GLuint m_fragShader;
	GLuint m_vertShader;
	GLuint m_shaderProg;
};

