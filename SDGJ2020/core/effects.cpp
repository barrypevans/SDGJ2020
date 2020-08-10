#include "effects.h"
#include "Entity_Controller.h"

Effects* Effects::g_pEffects;


void Effects::Init()
{

}

void Effects::CleanUp()
{

}


float glowingTime;
void Effects::Update()
{
	if (glowTiles.size() > 0)
	{
		glowingTime += Time::g_pTime->GetDeltaTime() * 4;
		for (int i = 0; i < glowTiles.size(); i++)
		{
			glowTiles[i]->GetComponent<Renderable>()->userData1 = glm::min(1.0f, glowingTime);
		}

		if (glowingTime > 3)
		{
			for (int i = 0; i < glowTiles.size(); i++)
			{
				glowTiles[i]->GetComponent<Renderable>()->userData1 = glm::max(0.0f, (glm::min(1.0f, 4 - glowingTime)));
			}

			if (glowingTime > 4)
			{
				for (int i = 0; i < glowTiles.size(); i++)
				{
					Game::g_pGame->DestroyEntity(glowTiles[i]);
				}
				glowTiles.clear();
			}
		}
	}

}

glm::vec2 Grid2Isospace(int posX, int posY)
{
	float x = posX;
	float y = posY;

	glm::vec2 pos;
	pos.x = (x + y) / 2;
	pos.y = ((y / 2) - (x / 2))/2;
	return pos;
};

glm::vec2 offset = glm::vec2(-4.5, 0.05);
void Effects::GlowTilesAt(int x, int y)
{
	glowingTime = 0;

	for (int i = 0; i < 8; i++)
	{
		glowTiles.push_back(Game::g_pGame->CreateEntity());
		//glowTiles[i]->m_position = position + glm::vec2(i * 0.5f, i * 0.25f);
		glowTiles[i]->m_scale = glm::vec2(1.2f, 1.2f);
		glowTiles[i]->AddComponent<Renderable>();
		glowTiles[i]->GetComponent<Renderable>()->OverrideShader("shaders/attackGlow.fs");
		glowTiles[i]->GetComponent<Renderable>()->SetTexture("art/TileGlow.png");

		glowTiles[i]->GetComponent<Renderable>()->userData2 = (float)rand() / RAND_MAX;
	}

	glowTiles[0]->m_position = offset + Grid2Isospace(x + 0,y + 1);
	glowTiles[0]->GetComponent<Renderable>()->m_layerOrder = 2;
	glowTiles[1]->m_position = offset + Grid2Isospace(x + 1,y + 1);
	glowTiles[1]->GetComponent<Renderable>()->m_layerOrder = 3;
	glowTiles[2]->m_position = offset + Grid2Isospace(x + 1,y + 0);
	glowTiles[2]->GetComponent<Renderable>()->m_layerOrder = 4;
	glowTiles[3]->m_position = offset + Grid2Isospace(x + 1,y + -1);
	glowTiles[3]->GetComponent<Renderable>()->m_layerOrder = 5;
	glowTiles[4]->m_position = offset + Grid2Isospace(x + 0,y + -1);
	glowTiles[4]->GetComponent<Renderable>()->m_layerOrder = 4;
	glowTiles[5]->m_position = offset + Grid2Isospace(x +-1,y + -1);
	glowTiles[5]->GetComponent<Renderable>()->m_layerOrder = 3;
	glowTiles[6]->m_position = offset + Grid2Isospace(x +-1,y + 0);
	glowTiles[6]->GetComponent<Renderable>()->m_layerOrder = 2;
	glowTiles[7]->m_position = offset + Grid2Isospace(x +-1,y + 1);
	glowTiles[7]->GetComponent<Renderable>()->m_layerOrder = 1;


}
