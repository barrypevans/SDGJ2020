#include "shader.h"
#include "assert.h"
#include "binary-asset.h"
#include "asset-manager.h"

Shader::Shader(std::string fsPath, std::string vsPath)
{
	BinaryAsset* vertexShaderSourceFile = AssetManager::g_pAssetManager->GetAsset<BinaryAsset>(vsPath.c_str());
	BinaryAsset*  fragmentShaderSourceFile = AssetManager::g_pAssetManager->GetAsset<BinaryAsset>(fsPath.c_str());
	ASSERT(vertexShaderSourceFile, "ERROR: Failed to load vertex shader!");
	ASSERT(fragmentShaderSourceFile, "ERROR: Failed to load fragment shader!");

	// load vert shader
	m_vertShader = glCreateShader(GL_VERTEX_SHADER);
	const char* vertexShaderSource = vertexShaderSourceFile->m_pContents;

	glShaderSource(m_vertShader, 1, &vertexShaderSource, NULL);
	glCompileShader(m_vertShader);
	int  success;
	char infoLog[512];
	glGetShaderiv(m_vertShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(m_vertShader, 512, NULL, infoLog);
		printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n %s\n", infoLog);
	}


	// load frag shader
	const char* fragmentShaderSource = fragmentShaderSourceFile->m_pContents;

	m_fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_fragShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(m_fragShader);
	glGetShaderiv(m_fragShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(m_fragShader, 512, NULL, infoLog);
		printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n %s\n", infoLog);
	}

	// link shader prog
	m_shaderProg = glCreateProgram();

	glAttachShader(m_shaderProg, m_vertShader);
	glAttachShader(m_shaderProg, m_fragShader);
	glLinkProgram(m_shaderProg);
	glGetProgramiv(m_shaderProg, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_shaderProg, 512, NULL, infoLog);
		printf(infoLog);
	}

	glDeleteShader(m_fragShader);
	glDeleteShader(m_vertShader);
}

void Shader::BindShader()
{
	glUseProgram(m_shaderProg);
}
