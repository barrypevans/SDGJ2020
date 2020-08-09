#include "ui.h"
#include "glm/glm.hpp"
#include "time.h"
#include "audio.h"
#include "game-logic-core.h"
#include "effects.h"
Effects* Effects::g_pEffects;


void Effects::Init()
{

}

void Effects::CleanUp()
{

}

void Effects::Update()
{

}

void Effects::GlowTilesAt(glm::vec2 position)
{
	for (int i = 0; i < 8; i++)
	{
		glowTiles.push_back(Game::g_pGame->CreateEntity());
		glowTiles[i]->m_position = glm::vec2(0, i);
		glowTiles[i]->m_scale = glm::vec2(1, 1);
		glowTileRenderables.push_back(glowTiles[i]->AddComponent<Renderable>());
		//glowTileRenderables[i]->OverrideShader
		glowTileRenderables[i]->SetTexture("art/TileGlow.png");
		glowTileRenderables[i]->m_layerOrder = 2;
	}
}
