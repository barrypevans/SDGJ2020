#include "game.h"
#include "renderer.h"
#include "stdio.h"
#include "renderable.h"
#include <GL/glew.h>
#include "asset-manager.h"
#include "assert.h"
#include "camera.h"
#include <algorithm>
#include "glm/gtc/matrix_transform.hpp"
#include "animatable.h"
#include "renderable-digit.h"

Renderer* Renderer::g_pRenderer;

void Renderer::Init()
{
	printf("Renderer Initialized!\n");
	m_defaultShader = new Shader();

	SetupQuad();

}

void Renderer::CleanUp()
{

}

void Renderer::Update()
{

}
/*
void Renderer::JoinRenderQueue(Renderable* renderable)
{
	renderables.push_back(renderable);
}
*/
void Renderer::RenderAllInQueue()
{

	for (int i = 0; i < Game::g_pGame->m_entityList.size(); ++i)
	{
		Renderable* renderable = nullptr;
		if ((renderable=Game::g_pGame->m_entityList[i]->GetComponent<Renderable>()))
			renderables.push_back(renderable);
	}
	
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

	m_defaultShader->BindShader();

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);


	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 6, vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::DrawRenderable(Renderable* renderable)
{
	Shader* shader = m_defaultShader;
	if (renderable->shouldOverrideShader)
	{
		shader = renderable->m_overrideShader;
	}

	ASSERT(shader, "ERROR: SHADER IS NULL!!!!");

	shader->BindShader();

	Animatable* animatable = dynamic_cast<Animatable*>(renderable);
	RenderableDigit* renderableDigit = dynamic_cast<RenderableDigit*>(renderable);
	
	Entity* entity = reinterpret_cast<Entity*>(renderable->m_entity);
	glm::vec2 scale = entity->m_scale;
	if (animatable)
	{
		scale.y *= (float)renderable->m_texture->m_height/
			((float)renderable->m_texture->m_width / static_cast<float>(animatable->GetActiveAnimation()->m_numFrames));
	}
	else
	{
		// correct scale for aspect ratio
		scale.y *= renderable->m_texture->m_aspect;
	}

	// upload camera matrix
	GLuint location = glGetUniformLocation(shader->GetProgram(), "_mvp");
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

	if (animatable)
	{
		GLuint animOffsetLocation = glGetUniformLocation(shader->GetProgram(), "curFrame");
		glUniform1f(animOffsetLocation, animatable->GetCurrentFrame());

		GLuint numFramesLocation = glGetUniformLocation(shader->GetProgram(), "numFrames");
		glUniform1f(numFramesLocation,static_cast<float>(animatable->GetActiveAnimation()->m_numFrames));
	}

	GLuint userdata1location = glGetUniformLocation(shader->GetProgram(), "userData1");
	GLuint userdata2location = glGetUniformLocation(shader->GetProgram(), "userData2");
	glUniform1fv(userdata1location, 1, &renderable->userData1);
	glUniform1fv(userdata2location, 1, &renderable->userData2);


	if (renderable->m_texture)
	{
		GLint texUnitLoc = glGetUniformLocation(shader->GetProgram(), "colorTexture");
		glProgramUniform1i(shader->GetProgram(), texUnitLoc, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, renderable->m_texture->m_textureId);
		glActiveTexture(0);
	}

	if (renderable->m_userTexture)
	{
		GLint texUnitLoc = glGetUniformLocation(shader->GetProgram(), "userTexture");
		glProgramUniform1i(shader->GetProgram(), texUnitLoc, 1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, renderable->m_userTexture->m_textureId);
		glActiveTexture(0);
	}

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::ClearRenderQueue()
{
	renderables.clear();
}




