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
			glowTileRenderables[i]->userData1 = glm::min(1.0f, glowingTime);
		}

		if (glowingTime > 3)
		{
			for (int i = 0; i < glowTiles.size(); i++)
			{
				glowTileRenderables[i]->userData1 = glm::max(0.0f, (glm::min(1.0f, 4 - glowingTime)));
			}

			if (glowingTime > 4)
			{
				for (int i = 0; i < glowTiles.size(); i++)
				{
					Game::g_pGame->DestroyEntity(glowTiles[i]);
				}
				glowTiles.clear();
				glowTileRenderables.clear();
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
	pos.y = (y / 2) - (x / 2);
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
		glowTileRenderables.push_back(glowTiles[i]->AddComponent<Renderable>());
		glowTileRenderables[i]->OverrideShader("shaders/attackGlow.fs");
		glowTileRenderables[i]->SetTexture("art/TileGlow.png");
		glowTileRenderables[i]->m_layerOrder = 1000;

		glowTileRenderables[i]->userData2 = (float)rand() / RAND_MAX;
	}


	//glowTiles[0]->m_position = Grid2Isospace(0, 0);
	//glowTiles[1]->m_position = Grid2Isospace(0, 1);
	//glowTiles[2]->m_position = Grid2Isospace(99, 99);
	//glowTiles[3]->m_position = Grid2Isospace(99, 99);
	//glowTiles[4]->m_position = Grid2Isospace(99, 99);
	//glowTiles[5]->m_position = Grid2Isospace(99, 99);
	//glowTiles[6]->m_position = Grid2Isospace(99, 99);
	//glowTiles[7]->m_position = Grid2Isospace(99, 99);


	glowTiles[0]->m_position = offset + glm::vec2(0,0);
	glowTiles[1]->m_position = offset + glm::vec2(0, 0);
	glowTiles[2]->m_position = offset + glm::vec2(0, 0);
	glowTiles[3]->m_position = offset + glm::vec2(0, 0);
	glowTiles[4]->m_position = offset + glm::vec2(0, 0);
	glowTiles[5]->m_position = offset + glm::vec2(0, 0);
	glowTiles[6]->m_position = offset + glm::vec2(0, 0);
	glowTiles[7]->m_position = offset + glm::vec2(0, 0);
}
