#include "game.h"
#include "renderer.h"
#include "stdio.h"
#include "renderable.h"
#include <GL/glew.h>

Renderer* Renderer::g_pRenderer;

void Renderer::Init()
{
	printf("Renderer Initialized!\n");
	

	unsigned int VBO; //Vertex Buffer's ID
	glGenBuffers(1, &VBO);	//Make the buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //Starting using the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //Add my verticies to the buffer

	unsigned int vertexShader; //Vertex Shader's ID
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

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
	//renders all in renderables
}

void Renderer::ClearRenderQueue()
{
	renderables.clear();
}




