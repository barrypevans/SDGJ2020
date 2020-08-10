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

void Effects::Reset()
{
	for (int i = 0; i < glowTiles.size(); i++)
	{
		Game::g_pGame->DestroyEntity(glowTiles[i]);
	}
	glowTiles.clear();
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

	Entity* currentTile;

	//center
	currentTile = AddAttackGlowTile();
	glowTiles.push_back(currentTile);
	currentTile->m_position = offset + Grid2Isospace(x + 0, y + 0);
	currentTile->GetComponent<Renderable>()->m_layerOrder = 2;


	//top
	if (y != 9)
	{
		currentTile = AddAttackGlowTile();
		glowTiles.push_back(currentTile);
		currentTile->m_position = offset + Grid2Isospace(x + 0, y + 1);
		currentTile->GetComponent<Renderable>()->m_layerOrder = 2;
	}

	//top right
	if (y != 9 && x != 9)
	{
		currentTile = AddAttackGlowTile();
		glowTiles.push_back(currentTile);
		currentTile->m_position = offset + Grid2Isospace(x + 1, y + 1);
		currentTile->GetComponent<Renderable>()->m_layerOrder = 2;
	}

	//right
	if (x != 9)
	{
		currentTile = AddAttackGlowTile();
		glowTiles.push_back(currentTile);
		currentTile->m_position = offset + Grid2Isospace(x + 1, y + 0);
		currentTile->GetComponent<Renderable>()->m_layerOrder = 2;
	}

	//bottom right
	if (y != 0 && x != 9)
	{
		currentTile = AddAttackGlowTile();
		glowTiles.push_back(currentTile);
		currentTile->m_position = offset + Grid2Isospace(x + 1, y + -1);
		currentTile->GetComponent<Renderable>()->m_layerOrder = 2;
	}

	//bottom
	if (y != 0)
	{
		currentTile = AddAttackGlowTile();
		glowTiles.push_back(currentTile);
		currentTile->m_position = offset + Grid2Isospace(x + 0, y + -1);
		currentTile->GetComponent<Renderable>()->m_layerOrder = 2;
	}

	//bottom left
	if (y != 0 && x != 0)
	{
		currentTile = AddAttackGlowTile();
		glowTiles.push_back(currentTile);
		currentTile->m_position = offset + Grid2Isospace(x + -1, y + -1);
		currentTile->GetComponent<Renderable>()->m_layerOrder = 2;
	}

	//left
	if (x != 0)
	{
		currentTile = AddAttackGlowTile();
		glowTiles.push_back(currentTile);
		currentTile->m_position = offset + Grid2Isospace(x + -1, y + 0);
		currentTile->GetComponent<Renderable>()->m_layerOrder = 2;
	}

	//top left
	if (y != 9 && x != 0)
	{
		currentTile = AddAttackGlowTile();
		glowTiles.push_back(currentTile);
		currentTile->m_position = offset + Grid2Isospace(x + -1, y + 1);
		currentTile->GetComponent<Renderable>()->m_layerOrder = 2;
	}

}

Entity* Effects::AddAttackGlowTile()
{
	Entity* e = Game::g_pGame->CreateEntity();
	//glowTiles[i]->m_position = position + glm::vec2(i * 0.5f, i * 0.25f);
	e->m_scale = glm::vec2(1.2f, 1.2f);
	e->AddComponent<Renderable>();
	e->GetComponent<Renderable>()->OverrideShader("shaders/attackGlow.fs");
	e->GetComponent<Renderable>()->SetTexture("art/TileGlow.png");

	e->GetComponent<Renderable>()->userData2 = (float)rand() / RAND_MAX;

	return e;
}
