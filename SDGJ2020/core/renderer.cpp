#include "game.h"
#include "renderer.h"
#include "stdio.h"
#include "renderable.h"
#include <GL/glew.h>
#include "asset-manager.h"
#include "binary-asset.h"
#include "assert.h"
#include "camera.h"
#include <algorithm>
#include "glm/gtc/matrix_transform.hpp"
Renderer* Renderer::g_pRenderer;

void Renderer::Init()
{
	printf("Renderer Initialized!\n");
	
	SetupQuad();

}

void Renderer::CleanUp()
{

}

void Renderer::Update()
{

}

void Renderer::JoinRenderQueue(Renderable* renderable)
{
	renderables.push_back(renderable);
}

void Renderer::RenderAllInQueue()
{
	std::sort(renderables.begin(), renderables.end(), 
		[](const Renderable* a, const Renderable* b)
	{
		return a->m_layerOrder < b->m_layerOrder;
	});

	//renders all in renderables
	for (int i = 0; i < renderables.size(); ++i)
		DrawRenderable(renderables[i]);
}

void Renderer::SetupQuad()
{
	glGenBuffers(1, &VBO);	//Make the buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //Starting using the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //Add my verticies to the buffer

	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	BinaryAsset* vertexShaderSourceFile = AssetManager::g_pAssetManager->GetAsset<BinaryAsset>("shaders/quad.vs");
	ASSERT(vertexShaderSourceFile, "ERROR: Failed to load vertex shader!");
	const char* vertexShaderSource = vertexShaderSourceFile->m_pContents;
	
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n %s\n", infoLog);
	}

	BinaryAsset* fragmentShaderSourceFile = AssetManager::g_pAssetManager->GetAsset<BinaryAsset>("shaders/quad.fs");
	ASSERT(fragmentShaderSourceFile, "ERROR: Failed to load fragment shader!");
	const char* fragmentShaderSource = fragmentShaderSourceFile->m_pContents;
	
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n %s\n", infoLog);
	}

	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		printf(infoLog);
	}

	glUseProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*6, vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::DrawRenderable(Renderable* renderable)
{
	glUseProgram(shaderProgram);

	// correct scale for aspect ratio
	Entity* entity = reinterpret_cast<Entity*>(renderable->m_entity);
	glm::vec2 scale = entity->m_scale;
	scale.y *= renderable->m_texture->m_aspect;

	// upload camera matrix
	GLuint location = glGetUniformLocation(shaderProgram, "_mvp");
	glm::mat4 proj = Camera::g_pCamera->GetOrthographicProjection();
	glm::mat4 view = Camera::g_pCamera->GetCameraTransformation();
	glm::mat4 model = glm::translate(glm::mat4(1.0f),
		glm::vec3(entity->m_position.x,
			entity->m_position.y, 0));
	model *= glm::rotate(glm::mat4(1.0f), entity->m_rotation, glm::vec3(0, 0, 1));
	model *= glm::scale(glm::mat4(1.0f), glm::vec3(scale.x, scale.y, 1));
	
	glm::mat4 MVP = proj;
	if (!renderable->isUI)
		MVP = MVP * view;
	MVP = MVP * model;
	
	glUniformMatrix4fv(location, 1, GL_FALSE, &MVP[0][0]);

	if (renderable->m_texture)
	{
		glActiveTexture(GL_TEXTURE0); 
		glBindTexture(GL_TEXTURE_2D, renderable->m_texture->m_textureId);
	}

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::ClearRenderQueue()
{
	renderables.clear();
}




